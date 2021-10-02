#include<iostream>
#include<map>
#include<queue>
#include<cstring>
#include<algorithm>
#include"catalog.hpp"
#include"buffer.hpp"
using namespace std;

//static
static map<FILE_HANDLE, string> file_path;
// static map<FILE_HANDLE, int> file_block_num;

// static map<BLOCK_HANDLE, BLOCK_POS> block_pos;
// static map<FILE_HANDLE, vector<BLOCK_HANDLE> > block_hd;
static map<BLOCK_HANDLE, FILE_HANDLE> block_hd;
static vector<BLOCK_HANDLE> last_mem_blocks;

static map<INDEX, pair<TABLE, ATTR> > index_table_attr;
static map<INDEX, string> index_name;
static map<INDEX, int> tree_node_size;
static map<INDEX, NODE_HANDLE> tree_head;
static map<INDEX, queue<NODE_POS> > empty_node_space;

static map<NODE_HANDLE, NODE_POS> node_pos;

static map<TABLE, string> table_name;
static map<TABLE, int> table_tuple_size;
static map<TABLE, vector<TUPLE_POS> > table_tuple;
static map<TABLE, vector<ATTR> > table_attr;
static map<TABLE, ATTR> table_pk;
static map<TABLE, queue<TUPLE_POS> > empty_tuple;

static map<ATTR, string> attr_name;
static map<ATTR, bool> attr_unique;
static map<ATTR, bool> attr_notnull;
static map<ATTR, TYPE> attr_type;

static BLOCK_HANDLE alloc_new_block(FILE_HANDLE fh){
    // BLOCK_POS bpos=pair<FILE_HANDLE, FILE_OFFSET>(fh, file_block_num.at(fh));
    // file_block_num.at(fh)++;
    // map<BLOCK_HANDLE, BLOCK_POS>::iterator it;
    // BLOCK_HANDLE max_bh=block_pos.size()?(--block_pos.end())->first:-1;
    // for(it=block_pos.begin();it!=block_pos.end();it++) if(it->first>max_bh) max_bh=it->first;
    // block_pos[++max_bh]=bpos;
    map<BLOCK_HANDLE, FILE_HANDLE>::iterator it;
    BLOCK_HANDLE max_bh=block_hd.size()?(--block_hd.end())->first:-1;
    block_hd[++max_bh]=fh;
    cat_new_block(fh, max_bh);
    //handle
    return max_bh;
}

bool catalog_init(){
    file_path.clear();
    block_hd.clear();
    last_mem_blocks.clear();
    tree_node_size.clear();
    tree_head.clear();
    empty_node_space.clear();
    node_pos.clear();
    index_table_attr.clear();
    index_name.clear();
    table_name.clear();
    table_tuple_size.clear();
    table_tuple.clear();
    table_attr.clear();
    table_pk.clear();
    empty_tuple.clear();
    attr_name.clear();
    attr_unique.clear();
    attr_notnull.clear();
    attr_type.clear();
    FILE *fp=fopen(catalog_file_path.c_str(), "rb");
    if(!fp) return false;
    //file
    int file_num;
    fread(&file_num, sizeof(int), 1, fp);
    for(int i=0;i<file_num;i++){
        FILE_HANDLE fh;
        fread(&fh, sizeof(fh), 1, fp);
        string path;
        while(1){
            char c;
            fread(&c, sizeof(c), 1, fp);
            if(c) path+=c;
            else break;
        }
        file_path[fh]=path;
    }
    //block
    int block_num;
    fread(&block_num, sizeof(block_num), 1, fp);
    for(int i=0;i<block_num;i++){
        BLOCK_HANDLE bh;
        fread(&bh, sizeof(bh), 1, fp);
        FILE_HANDLE fh;
        fread(&fh, sizeof(fh), 1, fp);
        block_hd[bh]=fh;
    }
    int last_block_num;
    fread(&last_block_num, sizeof(last_block_num), 1, fp);
    for(int i=0;i<last_block_num;i++){
        BLOCK_HANDLE bh;
        fread(&bh, sizeof(bh), 1, fp);
        last_mem_blocks.push_back(bh);
    }
    //index
    int index_num;
    fread(&index_num, sizeof(index_num), 1, fp);
    for(int i=0;i<index_num;i++){
        INDEX idx;
        fread(&idx, sizeof(idx), 1, fp);
        pair<TABLE, ATTR> ta;
        fread(&ta.first, sizeof(ta.first), 1, fp);
        fread(&ta.second, sizeof(ta.second), 1, fp);
        index_table_attr[idx]=ta;
        string idx_name;
        while(1){
            char c;
            fread(&c, sizeof(c), 1, fp);
            if(c) idx_name+=c;
            else break;
        }
        index_name[idx]=idx_name;
        int size;
        fread(&size, sizeof(size), 1, fp);
        NODE_HANDLE nh;
        fread(&nh, sizeof(nh), 1, fp);
        tree_node_size[idx]=size;
        tree_head[idx]=nh;
        int empty_num;
        fread(&empty_num, sizeof(empty_num), 1, fp);
        queue<NODE_POS> emp;
        empty_node_space[idx]=emp;
        for(int i=0;i<empty_num;i++){
            NODE_POS nh;
            fread(&nh.first, sizeof(nh.first), 1, fp);
            fread(&nh.second, sizeof(nh.second), 1, fp);
            empty_node_space[idx].push(nh);
        }
    }
    //node
    int node_num;
    fread(&node_num, sizeof(node_num), 1, fp);
    for(int i=0;i<node_num;i++){
        NODE_HANDLE nh;
        NODE_POS npos;
        fread(&nh, sizeof(nh), 1, fp);
        fread(&npos.first, sizeof(npos.first), 1, fp);
        fread(&npos.second, sizeof(npos.second), 1, fp);
        node_pos[nh]=npos;
    }
    //table
    int table_num;
    fread(&table_num, sizeof(table_num), 1, fp);
    for(int i=0;i<table_num;i++){
        TABLE t;
        fread(&t, sizeof(t), 1, fp);
        string tname;
        while(1){
            char c;
            fread(&c, sizeof(c), 1, fp);
            if(c) tname+=c;
            else break;
        }
        table_name[t]=tname;
        int ttsize;
        fread(&ttsize, sizeof(ttsize), 1, fp);
        table_tuple_size[t]=ttsize;
        table_tuple[t]=vector<TUPLE_POS>(0);
        int table_tuple_num;
        fread(&table_tuple_num, sizeof(table_tuple_num), 1, fp);
        for(int i=0;i<table_tuple_num;i++){
            TUPLE_POS tpos;
            fread(&tpos.first, sizeof(tpos.first), 1, fp);
            fread(&tpos.second, sizeof(tpos.second), 1, fp);
            table_tuple[t].push_back(tpos);
        }
        table_attr[t]=vector<ATTR>(0);
        int table_attr_num;
        fread(&table_attr_num, sizeof(table_attr_num), 1, fp);
        for(int i=0;i<table_attr_num;i++){
            ATTR attr;
            fread(&attr, sizeof(attr), 1, fp);
            table_attr[t].push_back(attr);
        }
        ATTR pk;
        fread(&pk, sizeof(pk), 1, fp);
        table_pk[t]=pk;
        empty_tuple[t]=queue<TUPLE_POS>();
        int empty_num;
        fread(&empty_num, sizeof(empty_num), 1, fp);
        for(int i=0;i<empty_num;i++){
            TUPLE_POS tpos;
            fread(&tpos.first, sizeof(tpos.first), 1, fp);
            fread(&tpos.second, sizeof(tpos.second), 1, fp);
            empty_tuple[t].push(tpos);
        }
    }
    //attr
    int attr_num;
    fread(&attr_num, sizeof(attr_num), 1, fp);
    for(int i=0;i<attr_num;i++){
        ATTR attr;
        fread(&attr, sizeof(attr), 1, fp);
        string aname;
        while(1){
            char c;
            fread(&c, sizeof(c), 1, fp);
            if(c) aname+=c;
            else break;
        }
        attr_name[attr]=aname;
        uchar unique;
        fread(&unique, sizeof(unique), 1, fp);
        attr_unique[attr]=unique;
        uchar notnull;
        fread(&notnull, sizeof(notnull), 1, fp);
        attr_notnull[attr]=notnull;
        TYPE tp;
        fread(&tp, sizeof(tp), 1, fp);
        attr_type[attr]=tp;
    }
    fclose(fp);
    return true;
}

void catalog_quit(){
    FILE* fp=fopen(catalog_file_path.c_str(), "wb");
    //file
    int file_num=file_path.size();
    fwrite(&file_num, sizeof(file_num), 1, fp);
    for(map<FILE_HANDLE, string>::iterator it=file_path.begin();it!=file_path.end();it++){
        FILE_HANDLE fh=it->first;
        fwrite(&fh, sizeof(fh), 1, fp);
        char tmp[it->second.length()+1]={0};
        strcpy(tmp, it->second.c_str());
        fwrite(tmp, sizeof(tmp), 1, fp);;
    }
    //block
    int block_num=block_hd.size();
    fwrite(&block_num, sizeof(block_num), 1, fp);
    for(map<BLOCK_HANDLE, FILE_HANDLE>::iterator it=block_hd.begin();it!=block_hd.end();it++){
        BLOCK_HANDLE bh=it->first;
        fwrite(&bh, sizeof(bh), 1, fp);
        FILE_HANDLE fh=it->second;
        fwrite(&fh, sizeof(fh), 1, fp);
    }
    int last_block_num=last_mem_blocks.size();
    fwrite(&last_block_num, sizeof(last_block_num), 1, fp);
    for(vector<BLOCK_HANDLE>::iterator it=last_mem_blocks.begin();it!=last_mem_blocks.end();it++){
        BLOCK_HANDLE bh=*it;
        fwrite(&bh, sizeof(bh), 1, fp);
    }
    //index
    int index_num=index_table_attr.size();
    fwrite(&index_num, sizeof(index_num), 1, fp);
    for(map<INDEX, pair<TABLE, ATTR> >::iterator it=index_table_attr.begin();it!=index_table_attr.end();it++){
        INDEX idx=it->first;
        fwrite(&idx, sizeof(idx), 1, fp);
        pair<TABLE, ATTR> ta=it->second;
        fwrite(&ta.first, sizeof(ta.first), 1, fp);
        fwrite(&ta.second, sizeof(ta.second), 1, fp);
        char tmp[index_name[idx].length()+1]={0};
        strcpy(tmp, index_name[idx].c_str());
        fwrite(tmp, sizeof(tmp), 1, fp);
        int size=tree_node_size[idx];
        fwrite(&size, sizeof(size), 1, fp);
        NODE_HANDLE nh=tree_head[idx];
        fwrite(&nh, sizeof(nh), 1, fp);
        int empty_num=empty_node_space[idx].size();
        fwrite(&empty_num, sizeof(empty_num), 1, fp);
        for(int i=0;i<empty_num;i++){
            NODE_POS nh=empty_node_space[idx].front();
            empty_node_space[idx].pop();
            fwrite(&nh.first, sizeof(nh.first), 1, fp);
            fwrite(&nh.second, sizeof(nh.second), 1, fp);
        }
    }
    //node
    int node_num=node_pos.size();
    fwrite(&node_num, sizeof(node_num), 1, fp);
    for(map<NODE_HANDLE, NODE_POS>::iterator it=node_pos.begin();it!=node_pos.end();it++){
        NODE_HANDLE nh=it->first;
        NODE_POS npos=it->second;
        fwrite(&nh, sizeof(nh), 1, fp);
        fwrite(&npos.first, sizeof(npos.first), 1, fp);
        fwrite(&npos.second, sizeof(npos.second), 1, fp);
    }
    //table
    int table_num=table_name.size();
    fwrite(&table_num, sizeof(table_num), 1, fp);
    for(map<TABLE, string>::iterator it=table_name.begin();it!=table_name.end();it++){
        TABLE t=it->first;
        fwrite(&t, sizeof(t), 1, fp);
        char tmp[it->second.length()+1]={0};
        strcpy(tmp, it->second.c_str());
        fwrite(tmp, sizeof(tmp), 1, fp);
        fwrite(&table_tuple_size[t], sizeof(table_tuple_size[t]), 1, fp);
        int table_tuple_num=table_tuple[t].size();
        fwrite(&table_tuple_num, sizeof(table_tuple_num), 1, fp);
        for(int i=0;i<table_tuple_num;i++){
            TUPLE_POS tpos=table_tuple[t][i];
            fwrite(&tpos.first, sizeof(tpos.first), 1, fp);
            fwrite(&tpos.second, sizeof(tpos.second), 1, fp);
        }
        int table_attr_num=table_attr[t].size();
        fwrite(&table_attr_num, sizeof(table_attr_num), 1, fp);
        for(int i=0;i<table_attr_num;i++){
            ATTR attr=table_attr[t][i];
            fwrite(&attr, sizeof(attr), 1, fp);
        }
        fwrite(&table_pk[t], sizeof(table_pk[t]), 1, fp);
        int empty_num=empty_tuple[t].size();
        fwrite(&empty_num, sizeof(empty_num), 1, fp);
        for(int i=0;i<empty_num;i++){
            TUPLE_POS tpos=empty_tuple[t].front();
            empty_tuple[t].pop();
            fwrite(&tpos.first, sizeof(tpos.first), 1, fp);
            fwrite(&tpos.second, sizeof(tpos.second), 1, fp);
        }
    }
    //attr
    int attr_num=attr_name.size();
    fwrite(&attr_num, sizeof(attr_num), 1, fp);
    for(map<ATTR, string>::iterator it=attr_name.begin();it!=attr_name.end();it++){
        ATTR attr=it->first;
        fwrite(&attr, sizeof(attr), 1, fp);
        char tmp[it->second.length()+1]={0};
        strcpy(tmp, it->second.c_str());
        fwrite(tmp, sizeof(tmp), 1, fp);
        uchar unique=attr_unique[attr]?0x01:0x00;
        fwrite(&unique, sizeof(unique), 1, fp);
        uchar notnull=attr_notnull[attr]?0x01:0x00;
        fwrite(&notnull, sizeof(notnull), 1, fp);
        fwrite(&attr_type[attr], sizeof(attr_type[attr]), 1, fp);
    }
    //end
    fclose(fp);
    file_path.clear();
    block_hd.clear();
    last_mem_blocks.clear();
    tree_node_size.clear();
    tree_head.clear();
    empty_node_space.clear();
    node_pos.clear();
    index_table_attr.clear();
    index_name.clear();
    table_name.clear();
    table_tuple_size.clear();
    table_tuple.clear();
    table_attr.clear();
    table_pk.clear();
    empty_tuple.clear();
    attr_name.clear();
    attr_unique.clear();
    attr_notnull.clear();
    attr_type.clear();
}

//metadata
string get_table_name(TABLE t){
    if(table_name.count(t)<=0) return string("");
    return table_name[t];
}

TABLE get_table_handle(string tname){
    map<TABLE, string>::iterator it;
    for(it=table_name.begin();it!=table_name.end();it++){
        if(it->second==tname) return it->first;
    }
    return NULL_TABLE;
}

const vector<TUPLE_POS>& get_table_tuple(TABLE t){
    return table_tuple.at(t);
}

int get_tuple_num(TABLE t){
    if(table_tuple.count(t)<=0) return -1;
    return table_tuple[t].size();
}

const vector<TUPLE_POS>& get_tuple_pos(TABLE t){
    return table_tuple.at(t);
}

int get_tuple_size(TABLE t){
    if(table_tuple_size.count(t)<=0) return 0;
    return table_tuple_size[t];
}

const vector<ATTR>& get_table_attr(TABLE t){
    return table_attr.at(t);
}

ATTR get_table_pk(TABLE t){
    if(table_pk.count(t)<=0) return NULL_ATTR;
    return table_pk[t];
}

int size_of_type(TYPE tp){
    if(tp==INT) return sizeof(int);
    if(tp==FLOAT) return sizeof(float);
    return tp-CHAR_1+2;
}

string get_attribute_name(ATTR attr){
    if(attr_name.count(attr)<=0) return string("");
    return attr_name[attr];
}

ATTR get_attribute_handle(TABLE t, string atname){
    if(table_attr.count(t)<=0) return NULL_ATTR;
    map<ATTR, string>::iterator it;
    for(it=attr_name.begin();it!=attr_name.end();it++){
        if(it->second==atname){
            vector<ATTR>::iterator itt=find(table_attr[t].begin(), table_attr[t].end(), it->first);
            if(itt!=table_attr[t].end()) return it->first;
        }
    }
    return NULL_ATTR;
}

TYPE get_attribute_type(ATTR attr){
    return attr_type.at(attr);
}

bool is_attr_unique(ATTR attr){
    if(attr_unique.count(attr)<=0) return false;
    return attr_unique[attr];
}

bool is_attr_notnull(ATTR attr){
    if(attr_notnull.count(attr)<=0) return false;
    return attr_notnull[attr];
}

string get_index_name(INDEX idx){
    if(index_name.count(idx)<=0) return string("");
    return index_name[idx];
}

INDEX get_index_handle(string idx_name){
    map<INDEX, string>::iterator it;
    for(it=index_name.begin();it!=index_name.end();it++){
        if(it->second==idx_name) return it->first;
    }
    return NULL_INDEX;
}

INDEX get_index_handle(TABLE t, ATTR attr){
    map<INDEX, pair<TABLE, ATTR> >::iterator it;
    for(it=index_table_attr.begin();it!=index_table_attr.end();it++){
        if(it->second==pair<TABLE, ATTR>(t, attr)) return it->first;
    }
    return NULL_INDEX;
}

ATTR get_index_attr(INDEX idx){
    if(index_table_attr.count(idx)<=0) return NULL_ATTR;
    return index_table_attr[idx].second;
}

bool drop_index_catalog(INDEX idx){
    if(index_table_attr.count(idx)<=0) return false;
    tree_node_size.erase(idx);
    tree_head.erase(idx);
    empty_node_space.erase(idx);
    index_table_attr.erase(idx);
    index_name.erase(idx);
    return true;
}

TABLE get_index_table(INDEX idx){
    if(index_table_attr.count(idx)<=0) return NULL_ATTR;
    return index_table_attr[idx].first;
}

INDEX alloc_new_index(string idx_name, TABLE t, ATTR attr, int sizeof_node){
    if(sizeof_node<0) return NULL_INDEX;
    INDEX idx=get_index_handle(t, attr);
    if(idx!=NULL_INDEX) return NULL_INDEX;
    idx=index_table_attr.size()?(--index_table_attr.end())->first:-1;
    // map<INDEX, pair<TABLE, ATTR> >::iterator it;
    // for(it=index_table_attr.begin();it!=index_table_attr.end();it++){
    //     if(it->first>idx) idx=it->first;
    // }
    idx++;
    index_name[idx]=idx_name;
    index_table_attr[idx]=pair<TABLE, ATTR>(t, attr);
    tree_node_size[idx]=sizeof_node;
    tree_head[idx]=NULL_NODE_HANDLE;
    empty_node_space[idx]=queue<NODE_POS>();
    return idx;
}

//record
static TABLE alloc_table_handle(){
    map<TABLE, string>::iterator it;
    TABLE max_t=table_name.size()?(--table_name.end())->first:-1;
    // for(it=table_name.begin();it!=table_name.end();it++){
    //     if(it->first>max_t) max_t=it->first;
    // }
    max_t++;
    return max_t;
}

static void alloc_attr_handle(vector<ATTR>& dst, int num){
    map<ATTR, string>::iterator it;
    ATTR max=attr_name.size()?(--attr_name.end())->first:-1;
    // for(it=attr_name.begin();it!=attr_name.end();it++){
    //     if(it->first>max) max=it->first;
    // }
    for(int i=0;i<num;i++) dst.push_back(++max);
}

TABLE create_table(const string& tname, const vector<string>& aname, const vector<TYPE>& atype, const int& pk, const vector<bool>& unique, const vector<bool>& notnull){
    if(get_table_handle(tname)!=NULL_TABLE) return NULL_TABLE;
    TABLE t=alloc_table_handle();
    if(t==NULL_TABLE) return t;
    table_name[t]=tname;
    int tuple_size=0;
    for(int i=0;i<atype.size();i++) tuple_size+=size_of_type(atype[i]);
    table_tuple_size[t]=tuple_size;
    table_tuple[t]=vector<TUPLE_POS>(0);
    table_attr[t]=vector<ATTR>(0);
    alloc_attr_handle(table_attr[t], aname.size());
    table_pk[t]=table_attr[t][pk];
    empty_tuple[t]=queue<TUPLE_POS>();
    for(int i=0;i<table_attr[t].size();i++){
        ATTR ai=table_attr[t][i];
        attr_name[ai]=aname[i];
        attr_unique[ai]=unique[i];
        attr_notnull[ai]=notnull[i];
        attr_type[ai]=atype[i];
    }
    return t;
}

bool drop_table(TABLE t){
    table_name.erase(t);
    table_tuple_size.erase(t);
    table_tuple.erase(t);
    table_pk.erase(t);
    empty_tuple.erase(t);
    vector<ATTR>& at=table_attr[t];
    for(int i=0;i<at.size();i++){
        attr_name.erase(at[i]);
        attr_unique.erase(at[i]);
        attr_notnull.erase(at[i]);
        attr_type.erase(at[i]);
    }
    table_attr.erase(t);
    return true;
}

TUPLE_POS alloc_tuple_pos(TABLE t){
    if(table_tuple.count(t)<=0) return NULL_TUPLE_POS;
    if(empty_tuple.at(t).empty()){
        BLOCK_HANDLE bh=alloc_new_block(table_file_handle);
        for(int i=0;i<block_size/get_tuple_size(t);i++) empty_tuple.at(t).push(TUPLE_POS(bh, i));
    }
    TUPLE_POS tpos=empty_tuple.at(t).front();
    empty_tuple.at(t).pop();
    table_tuple.at(t).push_back(tpos);
    return tpos;
}

bool delete_tuple(TABLE t, TUPLE_POS tpos){
    if(table_tuple.count(t)<=0) return false;
    vector<TUPLE_POS>::iterator it=find(table_tuple[t].begin(), table_tuple[t].end(), tpos);
    if(it==table_tuple[t].end()) return false;
    table_tuple[t].erase(it);
    empty_tuple[t].push(tpos);
    return true;
}

//buffer
static string get_file_path(FILE_HANDLE fh){
    if(file_path.count(fh)>0) return file_path[fh];
    else return string("");
}

string get_block_path(BLOCK_HANDLE bh){
    if(block_hd.count(bh)<=0) return string("");
    FILE_HANDLE fh=block_hd[bh];
    if(fh!=index_file_handle&&fh!=table_file_handle) return string("");
    char tmp[20];
    sprintf(tmp, "block%04d.blk", bh);
    return get_file_path(fh)+tmp;
}

string get_block_path(FILE_HANDLE fh, BLOCK_HANDLE bh){
    if(block_hd.count(bh)<=0) return string("");
    if(fh!=index_file_handle&&fh!=table_file_handle) return string("");
    char tmp[20];
    sprintf(tmp, "block%04d.blk", bh);
    return get_file_path(fh)+tmp;
}

const vector<BLOCK_HANDLE>& get_last_mem_blocks(){
    return last_mem_blocks;
}

bool store_last_mem_blocks(vector<BLOCK_HANDLE>& src){
    last_mem_blocks=src;
    return true;
}

//index
NODE_HANDLE get_tree_head_handle(INDEX idx){
    if(tree_head.count(idx)>0) return tree_head[idx];
    else return NULL_NODE_HANDLE;
}

NODE_POS get_node_pos(NODE_HANDLE nh){
    if(node_pos.count(nh)>0) return node_pos[nh];
    else return NULL_NODE_POS;
}

int get_node_size(INDEX idx){
    if(tree_node_size.count(idx)>0) return tree_node_size[idx];
    else return 0;
}

static NODE_POS alloc_node_pos(INDEX idx){
    if(empty_node_space.count(idx)<=0) return NULL_NODE_POS;
    if(empty_node_space[idx].empty()){
        BLOCK_HANDLE bh=alloc_new_block(index_file_handle);
        for(int i=0;i<block_size/get_node_size(idx);i++) empty_node_space[idx].push(NODE_POS(bh, i));
    }
    NODE_POS ret=empty_node_space[idx].front();
    empty_node_space[idx].pop();
    return ret;
}

NODE_HANDLE alloc_node_handle(INDEX idx){
    map<NODE_HANDLE, NODE_POS>::iterator it;
    NODE_HANDLE max_nh=node_pos.size()?(--node_pos.end())->first:-1;
    // for(it=node_pos.begin();it!=node_pos.end();it++) if(it->first>max_nh) max_nh=it->first;
    max_nh++;
    node_pos[max_nh]=alloc_node_pos(idx);
    return max_nh;
}

bool set_tree_head(INDEX idx, NODE_HANDLE nh){
    if(tree_head.count(idx)<=0) return false;
    if(nh!=NULL_NODE_HANDLE&&node_pos.count(nh)<=0) return false;
    tree_head[idx]=nh;
    return true;
}

bool erase_node(INDEX idx, NODE_HANDLE nh){
    if(node_pos.count(nh)<=0) return false;
    empty_node_space[idx].push(node_pos[nh]);
    node_pos.erase(nh);
    return true;
}


// int main(){
//     file_path[catalog_file_handle]=catalog_file_path;
//     file_path[table_file_handle]=table_file_path;
//     file_path[index_file_handle]=index_file_path;
//     block_hd.clear();
//     last_mem_blocks.clear();
//     tree_node_size.clear();
//     tree_head.clear();
//     empty_node_space.clear();
//     node_pos.clear();
//     index_table_attr.clear();
//     index_name.clear();
//     table_name.clear();
//     table_tuple_size.clear();
//     table_tuple.clear();
//     table_attr.clear();
//     table_pk.clear();
//     empty_tuple.clear();
//     attr_name.clear();
//     attr_unique.clear();
//     attr_notnull.clear();
//     attr_type.clear();
//     catalog_quit();
//     // FILE* fp=fopen(index_file_path.c_str(), "wb");
//     // fclose(fp);
//     // fp=fopen(table_file_path.c_str(), "wb");
//     // fclose(fp);
//     // catalog_init();
// }