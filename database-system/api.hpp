#pragma once

#include <climits>
#include<iostream>
#include <iomanip>
#include<vector>
#include<map>
#include "interpreter.hpp"
#include<set>
#include"catalog.hpp"

#define INT_WD 10
#define FLT_WD 16
using namespace std;

void api_init();

void create_Table(Instructor &Sp, string &wd, int flag);

void create_Index(Instructor &Sp, string &wd, int flag);

void insert_Record(Instructor &Sp, string &wd, int flag);

void drop_Table(Instructor &Sp, string &wd, int flag);

void drop_Index(Instructor &Sp, string &wd, int flag);

void delete_Record(Instructor &Sp, string &wd, int flag);

void select_Record(Instructor &Sp, string &wd, int flag);

void exec_file(Instructor &Sp, string &wd, int flag);

void api_quit();