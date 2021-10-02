#include<iostream>
#include<sstream>
#include<vector>
#include<map>
#include<algorithm>
#include<cstring>
#include<cmath>
#include"catalog.hpp"
#include"index.hpp"
#include"buffer.hpp"
#include"record.hpp"
using namespace std;

enum PROP {NONLEAF, LEAF};
const int MAX_CHARN_VIRTUAL_NODES=10;

template<class T>
void swap(T* a, T* b){
    T tmp=*a;
    *a=*b;
    *b=tmp;
}

template<class T>
class treenode{
public:
    PROP prop;
    int chd_num;
    NODE_HANDLE children[3], sibling, father;
    TUPLE_POS pos[3];
    int ele_num;
    T ele[3];
    treenode():prop(LEAF), ele_num(0), chd_num(0), sibling(NULL_NODE_HANDLE), father(NULL_NODE_HANDLE){}
    bool push_ele(T, TUPLE_POS=NULL_TUPLE_POS);
    bool push_chd(NODE_HANDLE);
};

template<class T>
bool treenode<T>::push_ele(T t, TUPLE_POS tpos){
    if(prop==LEAF&&ele_num>=3||prop==NONLEAF&&ele_num>=2) return false;
    ele[ele_num]=t;
    if(prop==LEAF&&tpos!=NULL_TUPLE_POS) pos[ele_num]=tpos;
    ele_num++;
    if(ele_num==2&&ele[0]>ele[1]){
        swap(ele+0, ele+1);
        if(prop==LEAF){
            TUPLE_POS tmp=pos[0];
            pos[0]=pos[1];
            pos[1]=tmp;
        }
    }else if(ele_num==3){
        if(ele[0]>ele[2]){
            swap(ele+0, ele+2);
            if(prop==LEAF){
                TUPLE_POS tmp=pos[0];
                pos[0]=pos[2];
                pos[2]=tmp;
            }
        }
        if(ele[1]>ele[2]){
            swap(ele+1, ele+2);
                if(prop==LEAF){
                TUPLE_POS tmp=pos[1];
                pos[1]=pos[2];
                pos[2]=tmp;
            }
        }
    }
    return true;
}

template<class T>
bool treenode<T>::push_chd(NODE_HANDLE nh){
    if(prop==LEAF||chd_num>=3) return false;
    children[chd_num++]=nh;
    return true;
}

static vector<BLOCK_HANDLE> pinned_blocks;
static vector<bool> pinned_blocks_dirty;
static map<NODE_HANDLE, BLOCK_HANDLE> node_in_pinned_blocks;


typedef struct _charn_virtual_node{
    treenode<string> node;
    NODE_HANDLE nh;
    pblock pb;
    bool valid;
}charn_virtual_node;

charn_virtual_node charn_nodes[MAX_CHARN_VIRTUAL_NODES];

template<class T>
static int find(T* a, int n, T t){
    for(int i=0;i<n;i++) if(a[i]==t) return i;
    return -1;
}

template<class T>
static treenode<T>* get_node(INDEX idx, NODE_HANDLE nh){
    if(idx==NULL_INDEX||nh==NULL_NODE_HANDLE) return NULL;
    NODE_POS npos=get_node_pos(nh);
    if(npos==NULL_NODE_POS) return NULL;
    // vector<NODE_HANDLE>::iterator it=find(charn_nodes_handle.begin(), charn_nodes_handle.end(), nh);
    // if(it!=charn_nodes_handle.end()) return (treenode<T>*)(&(charn_nodes[it-charn_nodes_handle.begin()]));
    for(int i=0;i<sizeof(charn_nodes)/sizeof(charn_nodes[0]);i++){
        if(charn_nodes[i].valid&&charn_nodes[i].nh==nh) 
            return (treenode<T>*)(&(charn_nodes[i].node));
    }
    pblock pb=get_block(npos.first);
    if(find(pinned_blocks.begin(), pinned_blocks.end(), npos.first)==pinned_blocks.end()){
        if(!pin_block(npos.first)) return NULL;
        pinned_blocks.push_back(npos.first);
        pinned_blocks_dirty.push_back(false);
    }
    node_in_pinned_blocks[nh]=npos.first;
    int offset=npos.second*get_node_size(idx);
    if(offset>block_size) return NULL;
    pb+=offset;
    TYPE tp=get_attribute_type(get_index_attr(idx));
    switch(tp){
        case INT: return (treenode<T>*)pb;
        case FLOAT: return (treenode<T>*)pb;
        default:{
            if(tp>CHAR_255) return NULL;
            int *pt=(int*)pb;
            PROP p=(PROP)*pt;
            pt++;
            int cnum=*pt;
            pt++;
            NODE_HANDLE nnh[5];
            for(int i=0;i<5;i++) nnh[i]=(NODE_HANDLE)(*pt++);
            TUPLE_POS ppos[3];
            for(int i=0;i<3;i++){
                ppos[i].first=(BLOCK_HANDLE)(*pt++);
                ppos[i].second=(BLOCK_OFFSET)(*pt++);
            }
            int elnum=*pt++;
            char* pc=(char*)pt;
            char e[3][tp-CHAR_1+2];
            for(int i=0;i<3;i++){
                for(int j=0;j<tp-CHAR_1+2;j++) e[i][j]=*pc++;
            }
            treenode<string> tmp;
            tmp.prop=p;
            tmp.chd_num=cnum;
            tmp.children[0]=nnh[0];
            tmp.children[1]=nnh[1];
            tmp.children[2]=nnh[2];
            tmp.sibling=nnh[3];
            tmp.father=nnh[4];
            tmp.pos[0]=ppos[0];
            tmp.pos[1]=ppos[1];
            tmp.pos[2]=ppos[2];
            tmp.ele_num=elnum;
            tmp.ele[0]=e[0];
            tmp.ele[1]=e[1];
            tmp.ele[2]=e[2];
            for(int i=0;i<sizeof(charn_nodes)/sizeof(charn_nodes[0]);i++){
                if(!charn_nodes[i].valid){
                    charn_nodes[i].node=tmp;
                    charn_nodes[i].nh=nh;
                    charn_nodes[i].pb=pb;
                    charn_nodes[i].valid=true;
                    return (treenode<T>*)(&(charn_nodes[i].node));
                }
            }
            cout << "WARNING!! VIRTUAL_CHARN_NODES' SPACE NOT ENOUGH!!!" << endl;
        }
    }
    return NULL;
}

static bool set_node_dirty(NODE_HANDLE nh){
    if(node_in_pinned_blocks.count(nh)<=0) return false;
    BLOCK_HANDLE bh=node_in_pinned_blocks[nh];
    vector<BLOCK_HANDLE>::iterator it=find(pinned_blocks.begin(), pinned_blocks.end(), bh);
    if(it==pinned_blocks.end()) return false;
    pinned_blocks_dirty[it-pinned_blocks.begin()]=true;
    return true;
}

static bool return_node(INDEX idx){
    TYPE tp=get_attribute_type(get_index_attr(idx));
    for(int i=0;i<sizeof(charn_nodes)/sizeof(charn_nodes[0]);i++){
        if(!charn_nodes[i].valid) continue;
        set_node_dirty(charn_nodes[i].nh);
        int *p=(int*)(charn_nodes[i].pb);
        *p=(int)(charn_nodes[i].node.prop);
        p++;
        *p=charn_nodes[i].node.chd_num;
        p++;
        for(int j=0;j<3;j++){
            *p=(int)(charn_nodes[i].node.children[j]);
            p++;
        }
        *p=(int)(charn_nodes[i].node.sibling);
        p++;
        *p=(int)(charn_nodes[i].node.father);
        p++;
        for(int j=0;j<3;j++){
            *p=(int)(charn_nodes[i].node.pos[j].first);
            p++;
            *p=(int)(charn_nodes[i].node.pos[j].second);
            p++;
        }
        *p=(int)(charn_nodes[i].node.ele_num);
        p++;
        char *c=(char*)p;
        for(int j=0;j<3;j++){
            strcpy(c, charn_nodes[i].node.ele[j].c_str());
            for(int k=charn_nodes[i].node.ele[j].size();k<tp-CHAR_1+2;k++) c[k]=0;
            c+=tp-CHAR_1+2;
        }
    }    
    bool flag=true;
    for(int i=0;i<pinned_blocks.size();i++) 
        flag&=return_block(pinned_blocks[i], pinned_blocks_dirty[i]);
    pinned_blocks.clear();
    pinned_blocks_dirty.clear();
    node_in_pinned_blocks.clear();
    for(int i=0;i<sizeof(charn_nodes)/sizeof(charn_nodes[0]);i++) charn_nodes[i].valid=false;
    return flag;
}

static bool return_node(INDEX idx, NODE_HANDLE nh){
    TYPE tp=get_attribute_type(get_index_attr(idx));
    for(int i=0;i<sizeof(charn_nodes)/sizeof(charn_nodes[0]);i++){
        if(charn_nodes[i].valid&&charn_nodes[i].nh==nh){
            set_node_dirty(charn_nodes[i].nh);
            int *p=(int*)(charn_nodes[i].pb);
            *p=(int)(charn_nodes[i].node.prop);
            p++;
            *p=charn_nodes[i].node.chd_num;
            p++;
            for(int j=0;j<3;j++){
                *p=(int)(charn_nodes[i].node.children[j]);
                p++;
            }
            *p=(int)(charn_nodes[i].node.sibling);
            p++;
            *p=(int)(charn_nodes[i].node.father);
            p++;
            for(int j=0;j<3;j++){
                *p=(int)(charn_nodes[i].node.pos[j].first);
                p++;
                *p=(int)(charn_nodes[i].node.pos[j].second);
                p++;
            }
            *p=(int)(charn_nodes[i].node.ele_num);
            p++;
            char *c=(char*)p;
            for(int j=0;j<3;j++){
                strcpy(c, charn_nodes[i].node.ele[j].c_str());
                for(int k=charn_nodes[i].node.ele[j].size();k<tp-CHAR_1+2;k++) c[k]=0;
                c+=tp-CHAR_1+2;
            }
            charn_nodes[i].valid=false;
        }
    }
    if(node_in_pinned_blocks.count(nh)>0){
        BLOCK_HANDLE bh=node_in_pinned_blocks[nh];
        node_in_pinned_blocks.erase(nh);
        map<NODE_HANDLE, BLOCK_HANDLE>::iterator it;
        for(it=node_in_pinned_blocks.begin();it!=node_in_pinned_blocks.end();it++) if(it->second==bh) break;
        vector<BLOCK_HANDLE>::iterator itt=find(pinned_blocks.begin(), pinned_blocks.end(), bh);
        if(itt==pinned_blocks.end()) return false;
        int i=itt-pinned_blocks.begin();
        if(it==node_in_pinned_blocks.end()){
            return_block(pinned_blocks[i], pinned_blocks_dirty[i]);
            pinned_blocks.erase(pinned_blocks.begin()+i);
            pinned_blocks_dirty.erase(pinned_blocks_dirty.begin()+i);
        }
    }
    return true;
}

template<class T>
static bool store_node(INDEX idx, treenode<T>* p, NODE_HANDLE nh){
    if(idx==NULL_INDEX||nh==NULL_NODE_HANDLE) return false;
    NODE_POS npos=get_node_pos(nh);
    if(npos==NULL_NODE_POS) return false;
    TYPE tp=get_attribute_type(get_index_attr(idx));
    if(tp==INT||tp==FLOAT){
        treenode<T>* dst=get_node<T>(idx, nh);
        if(!dst) return false;
        // *dst=*p;
        memcpy(dst, p, get_node_size(idx));
        set_node_dirty(nh);
        return true;
    }else{
        pblock pb=get_block(npos.first);
        if(find(pinned_blocks.begin(), pinned_blocks.end(), npos.first)==pinned_blocks.end()){
            if(!pin_block(npos.first)) return false;
            pinned_blocks.push_back(npos.first);
            pinned_blocks_dirty.push_back(false);
        }
        node_in_pinned_blocks[nh]=npos.first;
        int offset=npos.second*get_node_size(idx);
        if(offset>block_size) return false;
        pb+=offset;
        for(int i=0;i<sizeof(charn_nodes)/sizeof(charn_nodes[0]);i++){
            if(!charn_nodes[i].valid){
                charn_nodes[i].node=*(treenode<string>*)p;
                charn_nodes[i].nh=nh;
                charn_nodes[i].pb=pb;
                charn_nodes[i].valid=true;
                set_node_dirty(nh);
                return true;
            }
        }
        cout << "WARNING!! VIRTUAL_CHARN_NODES' SPACE NOT ENOUGH!!!" << endl;
        set_node_dirty(nh);
        return false;
    }
}

template<class T>
static bool delete_node(INDEX idx, NODE_HANDLE nh){
    for(int i=0;i<sizeof(charn_nodes)/sizeof(charn_nodes[0]);i++){
        if(charn_nodes[i].valid&&charn_nodes[i].nh==nh) charn_nodes[i].valid=false;
    }
    if(node_in_pinned_blocks.count(nh)>0){
        BLOCK_HANDLE bh=node_in_pinned_blocks[nh];
        node_in_pinned_blocks.erase(nh);
        map<NODE_HANDLE, BLOCK_HANDLE>::iterator it;
        for(it=node_in_pinned_blocks.begin();it!=node_in_pinned_blocks.end();it++) if(it->second==bh) break;
        if(it==node_in_pinned_blocks.end()){
            vector<BLOCK_HANDLE>::iterator itt=find(pinned_blocks.begin(), pinned_blocks.end(), bh);
            if(itt==pinned_blocks.end()) return false;
            int i=itt-pinned_blocks.begin();
            return_block(pinned_blocks[i], pinned_blocks_dirty[i]);
            pinned_blocks.erase(pinned_blocks.begin()+i);
            pinned_blocks_dirty.erase(pinned_blocks_dirty.begin()+i);
        }
    }
    return erase_node(idx, nh);
}

template<class T>
static treenode<T>* bp_find_leaf(INDEX idx, NODE_HANDLE& nh_head, T t, NODE_HANDLE& n){
    treenode<T>* p=get_node<T>(idx, nh_head);
    NODE_HANDLE nh=nh_head;
    while(p&&p->prop==NONLEAF){
        if(t<p->ele[0]){
            NODE_HANDLE tmp=p->children[0];
            return_node(idx, nh);
            p=get_node<T>(idx, nh=tmp);
        }else if(p->ele_num==2&&t>=p->ele[1]){
            NODE_HANDLE tmp=p->children[2];
            return_node(idx, nh);
            p=get_node<T>(idx, nh=tmp);
        }else{
            NODE_HANDLE tmp=p->children[1];
            return_node(idx, nh);
            p=get_node<T>(idx, nh=tmp);
        }
    }
    n=nh;
    return p;
}

template<class T>
static TUPLE_POS bp_find(INDEX idx, T t){
    NODE_HANDLE nh_head=get_tree_head_handle(idx);
    if(nh_head==NULL_NODE_HANDLE) return NULL_TUPLE_POS;
    NODE_HANDLE nh_p;
    treenode<T>* p=bp_find_leaf<T>(idx, nh_head, t, nh_p);
    if(!p) return NULL_TUPLE_POS;
    int it=find<T>(p->ele, p->ele_num, t);
    TUPLE_POS ret=(it==-1)?NULL_TUPLE_POS:p->pos[it];
    return_node(idx);
    return ret;
}

template<class T>
static bool bp_insert(INDEX idx, T t, TUPLE_POS tpos){
    NODE_HANDLE nh_head=get_tree_head_handle(idx);
    if(nh_head==NULL_NODE_HANDLE){
        treenode<T>* head=new treenode<T>;
        head->prop=LEAF;
        head->push_ele(t, tpos);
        NODE_HANDLE nh=alloc_node_handle(idx);
        set_tree_head(idx, nh);
        if(store_node(idx, head, nh)){
            delete head;
            return return_node(idx);
        }else{
            return_node(idx);
            return false;
        }
    }
    NODE_HANDLE nh_leaf;
    treenode<T>* leaf=bp_find_leaf<T>(idx, nh_head, t, nh_leaf);
    if(!leaf){
        return_node(idx);
        return false;
    }
    int it=find<T>(leaf->ele, leaf->ele_num, t);
    if(it!=-1){
        return_node(idx);
        return false;
    }
    set_node_dirty(nh_leaf);
    if(leaf->push_ele(t, tpos)) return return_node(idx);
    T tmp_ele[4]={leaf->ele[0], leaf->ele[1], leaf->ele[2], t};
    TUPLE_POS tmp_pos[4]={leaf->pos[0], leaf->pos[1], leaf->pos[2], tpos};
    for(int i=2;i>=0&&tmp_ele[i]>tmp_ele[i+1];i--){
        swap(tmp_ele+i, tmp_ele+i+1);
        swap(tmp_pos+i, tmp_pos+i+1);
    }
    leaf->ele_num=0;
    leaf->push_ele(tmp_ele[0], tmp_pos[0]);
    leaf->push_ele(tmp_ele[1], tmp_pos[1]);
    treenode<T> *c1=leaf;
    treenode<T> *c2=new treenode<T>;
    NODE_HANDLE nh_c1=nh_leaf, nh_c2=alloc_node_handle(idx);
    c2->prop=LEAF;
    c2->push_ele(tmp_ele[2], tmp_pos[2]);
    c2->push_ele(tmp_ele[3], tmp_pos[3]);
    c2->sibling=c1->sibling;
    c1->sibling=nh_c2;
    T upgoing=c2->ele[0];
    NODE_HANDLE nh_p=c1->father;
    treenode<T> *p=get_node<T>(idx, nh_p);
    NODE_HANDLE tmp_chd[4];
    while(1){
        if(!p){
            treenode<T> *tmp=new treenode<T>;
            NODE_HANDLE nh_tmp=alloc_node_handle(idx);
            tmp->prop=NONLEAF;
            tmp->push_chd(nh_c1);
            tmp->push_chd(nh_c2);
            tmp->push_ele(upgoing);
            c1->father=c2->father=nh_tmp;
            set_tree_head(idx, nh_tmp);
            bool f=store_node(idx, c2, nh_c2);
            f&=store_node(idx, tmp, nh_tmp);
            delete tmp;
            delete c2;
            if(f) return return_node(idx);
            else{
                return_node(idx);
                return false;
            }
        }else{
            return_node(idx, nh_c1);
            set_node_dirty(nh_p);
            int i, k;
            for(i=0;i<p->ele_num;i++) tmp_ele[i]=p->ele[i];
            tmp_ele[i++]=upgoing;
            for(k=0;k<p->chd_num;k++) tmp_chd[k]=p->children[k];
            tmp_chd[k]=nh_c2;
            for(int j=i-2;j>=0&&tmp_ele[j]>tmp_ele[j+1];j--){
                swap(tmp_ele+j, tmp_ele+j+1);
                swap(tmp_chd+j+1, tmp_chd+j+2);
            }
            p->ele_num=0;
            p->chd_num=0;
            p->push_ele(tmp_ele[0]);
            if(i==2) p->push_ele(tmp_ele[1]);
            p->push_chd(tmp_chd[0]);
            p->push_chd(tmp_chd[1]);
            if(i==2) p->push_chd(tmp_chd[2]);
            c2->father=nh_p;
            bool f=store_node(idx, c2, nh_c2);
            delete c2;
            if(i==2){
                if(f) return return_node(idx);
                else{
                    return_node(idx);
                    return false;
                }
            }
            //split
            return_node(idx, nh_c2);
            treenode<T>* p2=new treenode<T>;
            NODE_HANDLE nh_p2=alloc_node_handle(idx);
            p2->prop=NONLEAF;
            p2->push_ele(tmp_ele[2]);
            p2->push_chd(tmp_chd[2]);
            p2->push_chd(tmp_chd[3]);
            treenode<T>* ch2=get_node<T>(idx, tmp_chd[2]), *ch3=get_node<T>(idx, tmp_chd[3]);
            set_node_dirty(tmp_chd[2]);
            set_node_dirty(tmp_chd[3]);
            ch2->father=nh_p2;
            ch3->father=nh_p2;
            return_node(idx, tmp_chd[2]);
            return_node(idx, tmp_chd[3]);
            p2->sibling=p->sibling;
            p->sibling=nh_p2;
            upgoing=tmp_ele[1];
            c1=p;
            nh_c1=nh_p;
            c2=p2;
            nh_c2=nh_p2;
            p=get_node<T>(idx, nh_p=p->father);
        }
    }
    return_node(idx);
    return true;
}

template<class T>
static void index_trouble_fix(INDEX idx, NODE_HANDLE start, T trouble_ele, T new_ele){
    treenode<T>* up=get_node<T>(idx, start);
    NODE_HANDLE nh_up=start;
    while(up){
        int fd=find(up->ele, up->ele_num, trouble_ele);
        if(fd!=-1){
            set_node_dirty(nh_up);
            up->ele[fd]=new_ele;
            return_node(idx, nh_up);
            break;
        }
        NODE_HANDLE tmp=up->father;
        return_node(idx, nh_up);
        up=get_node<T>(idx, nh_up=tmp);
    }
}

template<class T>
static bool bp_delete(INDEX idx, T t){
    NODE_HANDLE nh_head=get_tree_head_handle(idx);
    if(nh_head==NULL_NODE_HANDLE){
        return_node(idx);
        return false;
    }
    NODE_HANDLE nh_leaf;
    treenode<T>* leaf=bp_find_leaf<T>(idx, nh_head, t, nh_leaf);
    int it=find(leaf->ele, leaf->ele_num, t);
    if(it==-1){
        return_node(idx);
        return false;
    }
    set_node_dirty(nh_leaf);
    bool index_trouble=(it==0);
    //erase
    for(int i=it;i<leaf->ele_num-1;i++){
        leaf->ele[i]=leaf->ele[i+1];
        leaf->pos[i]=leaf->pos[i+1];
    }
    leaf->ele_num--;
    if(leaf->ele_num==0){
        bool f=delete_node<T>(idx, nh_leaf);
        set_tree_head(idx, NULL_NODE_HANDLE);
        if(f) return return_node(idx);
        else{
            return_node(idx);
            return false;
        }
    }
    T least_in_leaf=leaf->ele[0];
    if(leaf->father==NULL_NODE_HANDLE) return return_node(idx);
    if(leaf->ele_num==2){
        if(index_trouble) index_trouble_fix(idx, leaf->father, t, least_in_leaf);
        return return_node(idx);
    }
    treenode<T> *f;
    NODE_HANDLE tmp_sib;
    vector<T> tmp_ele;
    map<T, TUPLE_POS> tmp_pos;
    vector<NODE_HANDLE> tmp_chd;
    bool leafcase=true;
    NODE_HANDLE nh_p_father=leaf->father, nh_p_ch0=NULL_NODE_HANDLE, nh_p=nh_leaf;
    return_node(idx, nh_leaf);
    while(1){
        f=get_node<T>(idx, nh_p_father);
        set_node_dirty(nh_p_father);
        if(!leafcase&&!f){
            set_tree_head(idx, nh_p_ch0);
            get_node<T>(idx, nh_p_ch0)->father=NULL_NODE_HANDLE;
            set_node_dirty(nh_p_ch0);
            bool f=delete_node<T>(idx, nh_p);
            if(f) return return_node(idx);
            else{
                return_node(idx);
                return false;
            }
        }
        tmp_ele.clear();
        tmp_chd.clear();
        tmp_pos.clear();
        tmp_sib=get_node<T>(idx, f->children[f->chd_num-1])->sibling;
        return_node(idx, f->children[f->chd_num-1]);
        for(int i=0;i<f->chd_num;i++){
            treenode<T>* chd=get_node<T>(idx, f->children[i]);
            for(int i=0;i<chd->ele_num;i++) tmp_ele.push_back(chd->ele[i]);
            if(leafcase) for(int i=0;i<chd->ele_num;i++) tmp_pos[chd->ele[i]]=chd->pos[i];
            else for(int i=0;i<chd->chd_num;i++) tmp_chd.push_back(chd->children[i]);
            return_node(idx, f->children[i]);
        }
        if(tmp_ele.size()==(leafcase?3:1)){
            treenode<T>* ch0=get_node<T>(idx, f->children[0]);
            set_node_dirty(f->children[0]);
            if(!leafcase){
                treenode<T>* ch1=get_node<T>(idx, f->children[1]);
                for(int i=0;i<ch1->chd_num;i++){
                    get_node<T>(idx, ch1->children[i])->father=f->children[0];
                    set_node_dirty(ch1->children[i]);
                    return_node(idx, ch1->children[i]);
                }
                return_node(idx, f->children[1]);
            }
            delete_node<T>(idx, f->children[1]);
            ch0->sibling=tmp_sib;
            ch0->ele_num=0;
            ch0->chd_num=0;
            for(int i=0;i<tmp_ele.size();i++) ch0->push_ele(tmp_ele[i]);
            if(leafcase) for(int i=0;i<tmp_pos.size();i++) ch0->pos[i]=tmp_pos[ch0->ele[i]];
            else for(int i=0;i<tmp_chd.size();i++) ch0->push_chd(tmp_chd[i]);
            if(leafcase){
                if(index_trouble&&f->ele[0]==t) index_trouble=false;
            }else{
                if(index_trouble&&f->ele[0]==t){
                    ch0->push_ele(least_in_leaf);
                    index_trouble=false;
                }else ch0->push_ele(f->ele[0]);
            }
            return_node(idx, f->children[0]);
            f->ele_num=0;
            NODE_HANDLE nnhh=f->children[0];
            f->chd_num=0;
            f->push_chd(nnhh);
            nh_p=nh_p_father;
            nh_p_father=f->father;
            nh_p_ch0=f->children[0];
            return_node(idx, nh_p);
        }else{
            bool case22, case23, case34, case3, case4;
            if(!leafcase){
                if(index_trouble){
                    int it=find(f->ele, f->ele_num, t);
                    if(it!=-1) f->ele[it]=least_in_leaf;
                    else index_trouble_fix(idx, f->father, t, least_in_leaf);
                }
                case22=tmp_ele.size()==2&&f->chd_num==2;
                case23=tmp_ele.size()==2&&f->chd_num==3;
                case34=tmp_ele.size()==3||tmp_ele.size()==4;
                case3=tmp_ele.size()==3;
                case4=tmp_ele.size()==4;
                for(int i=0;i<f->ele_num;i++) tmp_ele.push_back(f->ele[i]);
                sort(tmp_ele.begin(), tmp_ele.end());
            }
            int tmp_keys[3]={0};
            if(leafcase&&tmp_ele.size()==5||!leafcase&&case23){
                delete_node<T>(idx, f->children[2]);
                get_node<T>(idx, f->children[1])->sibling=tmp_sib;
                set_node_dirty(f->children[1]);
                return_node(idx, f->children[1]);
                f->chd_num--;
            }
            if(leafcase){
                if(tmp_ele.size()==4||tmp_ele.size()==6) tmp_keys[0]=2;
                else if(tmp_ele.size()==5||tmp_ele.size()==7) tmp_keys[0]=3;
                else return return_node(idx);
            }else{
                if(case22||case3) tmp_keys[0]=2;
                else if(case23||case4) tmp_keys[0]=3;
                else return return_node(idx);
            }
            tmp_keys[1]=tmp_keys[2]=2;
            treenode<T> *ch[3];
            ch[0]=get_node<T>(idx, f->children[0]);
            set_node_dirty(f->children[0]);
            ch[1]=get_node<T>(idx, f->children[1]);
            set_node_dirty(f->children[1]);
            bool flag=leafcase&&tmp_ele.size()>=6||!leafcase&&case34;
            if(flag){
                ch[2]=get_node<T>(idx, f->children[2]);
                set_node_dirty(f->children[2]);
            }
            for(int i=0, tmp_cnt=0;i<(flag?3:2);i++){
                ch[i]->ele_num=0;
                ch[i]->chd_num=0;
                for(int j=0;j<tmp_keys[i];j++){
                    if(leafcase) ch[i]->push_ele(tmp_ele.at(tmp_cnt), tmp_pos[tmp_ele.at(tmp_cnt)]);
                    else{
                        ch[i]->push_chd(tmp_chd.at(tmp_cnt));
                        get_node<T>(idx, tmp_chd.at(tmp_cnt))->father=f->children[i];
                        set_node_dirty(tmp_chd.at(tmp_cnt));
                        return_node(idx, tmp_chd.at(tmp_cnt));
                    }
                    tmp_cnt++;
                }
            }
            if(!leafcase){
                ch[0]->push_ele(tmp_ele.at(0));
                if(case23||case4) ch[0]->push_ele(tmp_ele.at(1));
                ch[1]->push_ele(tmp_ele.at((case22||case3)?2:3));
                if(case34) ch[2]->push_ele(tmp_ele.at(case3?4:5));
            }
            if(leafcase&&index_trouble&&nh_leaf==f->children[0]) index_trouble_fix(idx, f->father, t, least_in_leaf);
            f->ele_num=0;
            if(leafcase){
                f->push_ele(ch[1]->ele[0]);
                if(tmp_ele.size()==6||tmp_ele.size()==7) f->push_ele(ch[2]->ele[0]);
            }else{
                if(case3){
                    f->push_ele(tmp_ele.at(1));
                    f->push_ele(tmp_ele.at(3));
                }else if(case4){
                    f->push_ele(tmp_ele.at(2));
                    f->push_ele(tmp_ele.at(4));
                }else f->push_ele(tmp_ele.at(case22?1:2));
            }
            return return_node(idx);
        }
        leafcase=false;
    }
    return return_node(idx);
}

bool index_init(){
    pinned_blocks.clear();
    pinned_blocks_dirty.clear();
    node_in_pinned_blocks.clear();
    for(int i=0;i<sizeof(charn_nodes)/sizeof(charn_nodes[0]);i++) charn_nodes[i].valid=false;
    return buffer_init();
}

void index_quit(){
    // return_node(idx);
    buffer_quit();
}

INDEX create_index(string idx_name, TABLE t, ATTR attr){
    TYPE tp=get_attribute_type(attr);
    int nodesize;
    if(tp==INT) nodesize=sizeof(treenode<int>);
    else if(tp==FLOAT) nodesize=sizeof(treenode<float>);
    else nodesize=sizeof(treenode<int>)-3*sizeof(int)+3*(tp-CHAR_1+2);
    INDEX idx=alloc_new_index(idx_name, t, attr, nodesize);
    if(idx==NULL_INDEX) return NULL_INDEX;
    //insert
    const vector<TUPLE_POS>& tps=get_tuple_pos(t);
    TUPLE tuple;
    const vector<ATTR>& attrs=get_table_attr(t);
    vector<ATTR>::const_iterator it=find(attrs.begin(), attrs.end(), attr);
    if(it==attrs.end()) return NULL_INDEX;
    int attr_pos=it-attrs.begin();
    for(int i=0;i<tps.size();i++){
        get_tuple(t, tps[i], tuple);
        switch(tp){  
            case INT: bp_insert<int>(idx, tuple[attr_pos].size()?stoi(tuple[attr_pos]):NULL_INT, tps[i]); break;
            case FLOAT: bp_insert<float>(idx, tuple[attr_pos].size()?stof(tuple[attr_pos]):NULL_FLOAT, tps[i]); break;
            default: bp_insert<string>(idx, tuple[attr_pos], tps[i]); break;
        }
        return_block(tps[i].first, false);
    }
    return idx;
}

bool find_index(INDEX idx, const string& val){
    TYPE tp=get_attribute_type(get_index_attr(idx));
    TUPLE_POS ans;
    switch(tp){
        case INT: ans=bp_find<int>(idx, val.size()?stoi(val):NULL_INT); break;
        case FLOAT: ans=bp_find<float>(idx, val.size()?stof(val):NULL_FLOAT); break;
        default: ans=bp_find<string>(idx, val); break;
    }
    return ans==NULL_TUPLE_POS;
} 

template<class T>
static bool select_index_tree(TABLE t, INDEX idx, ATTR idx_attr, T min, bool min_start, bool isE, const vector<PRED>& pred, TEMP_TABLE& ttable){
    NODE_HANDLE nh_head=get_tree_head_handle(idx);
    if(nh_head==NULL_NODE_HANDLE) return false;
    NODE_HANDLE dum;
    treenode<T>* leaf;
    int i;
    if(min_start){
        leaf=get_node<T>(idx, nh_head);
        while(leaf->prop==NONLEAF) leaf=get_node<T>(idx, leaf->children[0]);
        i=0;
    }else{
        leaf=bp_find_leaf<T>(idx, nh_head, min, dum);
        if(!leaf) return false;
        for(i=0;i<leaf->ele_num;i++) if(leaf->ele[i]>=min) break;
        if(i==leaf->ele_num) leaf=get_node<T>(idx, leaf->sibling);
        if(isE&&leaf->ele[i]!=min) return false;
    }
    const vector<ATTR>& attrs=get_table_attr(t);
    ttable.attr=attrs;
    ttable.tuples.clear();
    vector<int> attr_pos;
    vector<TYPE> tp;
    for(int i=0;i<pred.size();i++){
        vector<ATTR>::const_iterator it=find(attrs.begin(), attrs.end(), pred[i].left);
        if(it==attrs.end()) attr_pos.push_back(-1);
        else attr_pos.push_back(it-attrs.begin());
        tp.push_back(get_attribute_type(pred[i].left));
    }
    bool end=false;
    while(leaf){
        for(;i<leaf->ele_num;i++){
            TUPLE tuple;
            bool f=true;
            get_tuple(t, leaf->pos[i], tuple);
            for(int i=0;i<pred.size()&&f;i++){
                if(attr_pos[i]==-1) continue;
                string s=tuple[attr_pos[i]];
                switch(tp[i]){
                    case INT:  f&=pred_cmp<int>(s.size()?stoi(s):NULL_INT, pred[i].op, pred[i].right.size()?stoi(pred[i].right):NULL_INT); break;
                    case FLOAT: {
                        if(pred[i].op==E){
                            f&=fabs((s.size()?stof(s):NULL_FLOAT)-(pred[i].right.size()?stof(pred[i].right):NULL_FLOAT))<=1e-6;
                        }else if(pred[i].op==NE){
                            f&=fabs((s.size()?stof(s):NULL_FLOAT)-(pred[i].right.size()?stof(pred[i].right):NULL_FLOAT))>1e-6;
                        }else f&=pred_cmp<float>(s.size()?stof(s):NULL_FLOAT, pred[i].op, pred[i].right.size()?stof(pred[i].right):NULL_FLOAT); break;
                    }
                    default: f&=pred_cmp<string>(s, pred[i].op, pred[i].right); break;
                }
                if(pred[i].left==idx_attr&&!f){
                    end=true;
                    break;
                }
            }
            if(f) ttable.tuples.push_back(tuple);
            return_block(leaf->pos[i].first, false);
            if(end) break;
        }
        if(end) break;
        leaf=get_node<T>(idx, leaf->sibling);
        i=0;
    }
    return true;
}

bool select_index(INDEX idx, const vector<PRED>& pred, TEMP_TABLE& ttable){
    ttable.attr.clear();
    ttable.tuples.clear();
    ATTR attr=get_index_attr(idx);
    TABLE t=get_index_table(idx);
    int i;
    for(i=0;i<pred.size();i++) if(pred[i].left==attr) break;
    if(i==pred.size()) return false;
    bool isE=pred[i].op==E||pred[i].op==GE;
    bool min_start=pred[i].op==LE||pred[i].op==L;
    TYPE tp=get_attribute_type(attr);
    bool ret=true;
    switch(tp){
        case INT: ret&=select_index_tree<int>(t, idx, attr, pred[i].right.size()?stoi(pred[i].right):NULL_INT, min_start, isE, pred, ttable); break;
        case FLOAT: ret&=select_index_tree<float>(t, idx, attr, pred[i].right.size()?stof(pred[i].right):NULL_FLOAT, min_start, isE, pred, ttable); break;
        default: ret&=select_index_tree<string>(t, idx, attr, pred[i].right, min_start, isE, pred, ttable); break;
    }
    return return_node(idx)&&ret;
}

bool insert_index(INDEX idx, const string& val, TUPLE_POS tpos){
    TYPE tp=get_attribute_type(get_index_attr(idx));
    switch(tp){
        case INT: return bp_insert<int>(idx, val.size()?stoi(val):NULL_INT, tpos);
        case FLOAT: return bp_insert<float>(idx, val.size()?stof(val):NULL_FLOAT, tpos);
        default: return bp_insert<string>(idx, val, tpos);
    }
    return false;
}

bool delete_index(INDEX idx, const string& val){
    // if(flag){
    //     set_tree_head(idx, NULL_NODE_HANDLE);
    //     return true;
    // }
    TYPE tp=get_attribute_type(get_index_attr(idx));
    switch(tp){
        case INT: return bp_delete<int>(idx, val.size()?stoi(val):NULL_INT);
        case FLOAT: return bp_delete<float>(idx, val.size()?stof(val):NULL_FLOAT);
        default: return bp_delete<string>(idx, val);
    }
    return false;
}

bool drop_index(INDEX idx){
    return drop_index_catalog(idx);
}

// // testers
// template<class T>
// static void level_order(INDEX idx){
//     if(idx==NULL_INDEX) return;
//     NODE_HANDLE head=get_tree_head_handle(idx);
//     if(head==NULL_NODE_HANDLE){
//         cout << "empty tree" << endl;
//         return;
//     }
//     treenode<T>* tree=get_node<T>(idx, head);
//     NODE_HANDLE nhtree=head;
//     while(1){
//         if(tree->prop==LEAF) break;
//         treenode<T>* p=tree;
//         NODE_HANDLE nhp=nhtree, tree_ch0=tree->children[0];
//         while(p){
//             cout << '[';
//             int i=0;
//             for(i=0;i<p->ele_num-1;i++) cout << p->ele[i] << ',';
//             cout << p->ele[i] << ']';
//             NODE_HANDLE tmp=p->sibling;
//             return_node(idx, nhp);
//             p=get_node<T>(idx, nhp=tmp);
//         }
//         cout << endl;
//         tree=get_node<T>(idx, nhtree=tree_ch0);
//     }
//     stringstream opt;
//     while(tree){
//         cout << '[';
//         int i=0;
//         for(i=0;i<tree->ele_num-1;i++) cout << tree->ele[i] << ',';
//         cout << tree->ele[i] << ']';
//         //pos
//         // opt << '[';
//         // for(i=0;i<tree->ele_num-1;i++){
//         //     opt << '(' << tree->pos[i].first << ',' << tree->pos[i].second << "),";
//         // }
//         // opt << '(' << tree->pos[i].first << ',' << tree->pos[i].second << ")]";
//         NODE_HANDLE tmp=tree->sibling;
//         return_node(idx, nhtree);
//         tree=get_node<T>(idx, nhtree=tmp);
//     }
//     cout << endl;// << opt.str() << endl;
//     return_node(idx);
// }

// int main(){
//     std::ios::sync_with_stdio(false);
//     catalog_init();
//     index_init();
//     vector<string> attrname;
//     vector<TYPE> type;
//     int pk;
//     vector<bool> uniq, nn;
//     attrname.push_back("id");
//     attrname.push_back("name");
//     attrname.push_back("score");
//     type.push_back(INT);
//     type.push_back(CHAR_12);
//     type.push_back(FLOAT);
//     pk=0;
//     uniq.push_back(true);
//     uniq.push_back(true);
//     uniq.push_back(false);
//     nn.push_back(true);
//     nn.push_back(false);
//     nn.push_back(false);
//     TABLE t=create_table("stu", attrname, type, pk, uniq, nn);
//     INDEX idx=create_index("sth", t, get_attribute_handle(t, "name"));
//     for(int i=1;i<=10000;i++){
//         stringstream ss;
//         ss << i;
//         string s;
//         ss>>s;
//         insert_index(idx, "name"+s, TUPLE_POS(i, i));
//     }
//     for(int i=1;i<=10000;i++){        
//         stringstream ss;
//         ss << i;
//         string s;
//         ss>>s;
//         // if(i==9){
//         //     cout << endl;
//         // }
//         delete_index(idx, "name"+s);
//         // level_order<string>(idx);
//     }
//     level_order<string>(idx);
//     // index_quit();
//     // catalog_quit();
// }