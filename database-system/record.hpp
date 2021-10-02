#pragma once

#include <climits>
#include<iostream>
#include<map>
#include<vector>
using namespace std;

bool record_init();
bool find_record(TABLE, ATTR, const string&);
bool select_record(TABLE, const vector<PRED>&, TEMP_TABLE&);
TUPLE_POS insert_record(TABLE, const vector<string>&);
bool delete_record(TABLE, const vector<PRED>&, TEMP_TABLE&);
void record_quit();

void get_tuple(TABLE, TUPLE_POS, TUPLE&);

template<class T>
bool pred_cmp(T t, PRED_OP op, T val){
    switch(op){
        case E:  return t==val;
        case NE: return t!=val;
        case GE: return t>=val;
        case LE: return t<=val;
        case G:  return t>val;
        case L:  return t<val;
        default: return false;
    }
}
