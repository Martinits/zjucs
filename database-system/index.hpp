#pragma once

#include <climits>
#include<iostream>
#include<vector>
#include"catalog.hpp"
using namespace std;

bool index_init();
void index_quit();

INDEX create_index(string idx_name, TABLE t, ATTR attr);
bool find_index(INDEX idx, const string& val);
bool select_index(INDEX idx, const vector<PRED>& pred, TEMP_TABLE& ttable);
bool insert_index(INDEX idx, const string& val, TUPLE_POS tpos);
bool delete_index(INDEX idx, const string& val);
bool drop_index(INDEX idx);
