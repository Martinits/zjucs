#include<iostream>
#include<vector>
#include<sstream>
#include<algorithm>
#include<cmath>
#include"catalog.hpp"
#include"record.hpp"
#include"buffer.hpp"
using namespace std;

bool record_init(){
    return true;
}

void get_tuple(TABLE t, TUPLE_POS tpos, TUPLE& tuple){
    tuple.clear();
    pblock blk=get_block(tpos.first);
    pin_block(tpos.first);
    int tp_size=get_tuple_size(t);
    blk+=tp_size*tpos.second;
    const vector<ATTR>& attr=get_table_attr(t);
    stringstream ss;
    string s;
    for(int i=0;i<attr.size();i++){
        TYPE tp=get_attribute_type(attr[i]);
        int n=size_of_type(tp);
        s="";
        ss.clear();
        ss.str("");
        if(tp==INT){
            int *p=(int*)blk;
            if(*p==NULL_INT) s="";
            else{
                ss << *p;
                ss >> s;
            }
        }else if(tp==FLOAT){
            float *p=(float*)blk;
            if(*p==NULL_FLOAT) s="";
            else{
                ss << *p;
                ss >> s;
            }
        }else{
            char *c=(char*)blk;
            char tmp[tp-CHAR_1+2];
            for(int j=0;j<tp-CHAR_1+2;j++) tmp[j]=c[j]; 
            tmp[tp-CHAR_1+1]=0;
            s=tmp;
        }
        tuple.push_back(s);
        blk+=n;
    }
}

bool find_record(TABLE t, ATTR attr, const string& val){
    const vector<TUPLE_POS>& tposs=get_table_tuple(t);
    const vector<ATTR>& attrs=get_table_attr(t);
    int attr_pos;
    vector<ATTR>::const_iterator it=find(attrs.begin(), attrs.end(), attr);
    if(it==attrs.end()) return false;
    else attr_pos=it-attrs.begin();
    TYPE tp=get_attribute_type(attr);
    bool sign=true;
    for(int i=0;i<tposs.size();i++){
        TUPLE tuple;
        get_tuple(t, tposs[i], tuple);
        switch(tp){
            case INT: sign=((tuple[attr_pos].size()?stoi(tuple[attr_pos]):NULL_INT)!=(val.size()?stoi(val):NULL_INT)); break;
            case FLOAT: sign=((tuple[attr_pos].size()?stof(tuple[attr_pos]):NULL_FLOAT)!=(val.size()?stof(val):NULL_FLOAT)); break;
            default: sign=(tuple[attr_pos]!=val); break;
        }
        return_block(tposs[i].first, false);
        if(!sign) break;
    }
    return sign;
}

bool select_record(TABLE t, const vector<PRED>& pred, TEMP_TABLE& ttable){
    ttable.attr.clear();
    ttable.tuples.clear();
    const vector<TUPLE_POS>& tposs=get_table_tuple(t);
    const vector<ATTR>& attrs=get_table_attr(t);
    ttable.attr=attrs;
    vector<int> attr_pos;
    vector<TYPE> tp;
    for(int i=0;i<pred.size();i++){
        vector<ATTR>::const_iterator it=find(attrs.begin(), attrs.end(), pred[i].left);
        if(it==attrs.end()) attr_pos.push_back(-1);
        else attr_pos.push_back(it-attrs.begin());
        tp.push_back(get_attribute_type(pred[i].left));
    }
    for(int i=0;i<tposs.size();i++){
        TUPLE tuple;
        bool f=true;
        get_tuple(t, tposs[i], tuple);
        for(int i=0;i<pred.size()&&f;i++){
            string s=tuple[attr_pos[i]];
            switch(tp[i]){
                case INT:   f&=pred_cmp<int>(s.size()?stoi(s):NULL_INT, pred[i].op, pred[i].right.size()?stoi(pred[i].right):NULL_INT); break;
                case FLOAT: {
                    if(pred[i].op==E){
                        f&=fabs((s.size()?stof(s):NULL_FLOAT)-(pred[i].right.size()?stof(pred[i].right):NULL_FLOAT))<=1e-6;
                    }else if(pred[i].op==NE){
                        f&=fabs((s.size()?stof(s):NULL_FLOAT)-(pred[i].right.size()?stof(pred[i].right):NULL_FLOAT))>1e-6;
                    }else f&=pred_cmp<float>(s.size()?stof(s):NULL_FLOAT, pred[i].op, pred[i].right.size()?stof(pred[i].right):NULL_FLOAT); break;
                }
                default: f&=pred_cmp<string>(s, pred[i].op, pred[i].right); break;
            }
        }
        return_block(tposs[i].first, false);
        if(f) ttable.tuples.push_back(tuple);
    }
    return true;
}

TUPLE_POS insert_record(TABLE t, const TUPLE& tuple){
    TUPLE_POS tpos=alloc_tuple_pos(t);
    if(tpos==NULL_TUPLE_POS) return tpos;
    const vector<ATTR>& attrs=get_table_attr(t);
    pblock blk=get_block(tpos.first);
    blk+=tpos.second*get_tuple_size(t);
    for(int i=0;i<tuple.size();i++){
        TYPE tp=get_attribute_type(attrs[i]);
        switch(tp){
            case INT:{
                int* p=(int*)blk;
                *p=tuple[i].size()?stoi(tuple[i]):NULL_INT;
                break;
            }
            case FLOAT:{
                float* p=(float*)blk;;
                *p=tuple[i].size()?stof(tuple[i]):NULL_FLOAT;
                break;
            }
            default:{
                char* p=(char*)blk;
                int j;
                for(j=0;j<tuple[i].size();j++) p[j]=tuple[i][j];
                for(;j<tp-CHAR_1+2;j++) p[j]=0;
                p[tp-CHAR_1+1]=0;
                break;
            }
        }
        blk+=size_of_type(tp);
    }
    return_block(tpos.first, true);
    return tpos;
}

bool delete_record(TABLE t, const vector<PRED>& pred, TEMP_TABLE& ttable){
    ttable.attr.clear();
    ttable.tuples.clear();
    const vector<TUPLE_POS>& tposs=get_table_tuple(t);
    const vector<ATTR>& attrs=get_table_attr(t);
    ttable.attr=attrs;
    vector<int> attr_pos;
    vector<TYPE> tp;
    for(int i=0;i<pred.size();i++){
        vector<ATTR>::const_iterator it=find(attrs.begin(), attrs.end(), pred[i].left);
        if(it==attrs.end()) attr_pos.push_back(-1);
        else attr_pos.push_back(it-attrs.begin());
        tp.push_back(get_attribute_type(pred[i].left));
    }
    for(int i=0;i<tposs.size();i++){
        TUPLE tuple;
        bool f=true;
        get_tuple(t, tposs[i], tuple);
        for(int j=0;j<pred.size();j++){
            string s=tuple[attr_pos[j]];
            switch(tp[j]){
                case INT:   f&=pred_cmp<int>(s.size()?stoi(s):NULL_INT, pred[j].op, pred[j].right.size()?stoi(pred[j].right):NULL_INT); break;
                case FLOAT: {
                    if(pred[j].op==E){
                        f&=fabs((s.size()?stof(s):NULL_FLOAT)-(pred[j].right.size()?stof(pred[j].right):NULL_FLOAT))<=1e-6;
                    }else if(pred[j].op==NE){
                        f&=fabs((s.size()?stof(s):NULL_FLOAT)-(pred[j].right.size()?stof(pred[j].right):NULL_FLOAT))>1e-6;
                    }else f&=pred_cmp<float>(s.size()?stof(s):NULL_FLOAT, pred[j].op, pred[j].right.size()?stof(pred[j].right):NULL_FLOAT); break;
                }
                default: f&=pred_cmp<string>(s, pred[j].op, pred[j].right); break;
            }
        }
        return_block(tposs[i].first, false);
        if(f){
            ttable.tuples.push_back(tuple);
            if(!delete_tuple(t, tposs[i])) return false;
            i--;
        }
    }
    return true;
}

void record_quit(){

}