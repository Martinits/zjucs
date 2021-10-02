#pragma once

#include <climits>
#include "catalog.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <map>
using namespace std;

void execute(string &cmd, int flag);

void start();

class Instructor
{
	string str;
	int cnt;
public:
	Instructor(string S);
	~Instructor();
	string Word();
	string Brackets();
	bool have_Semicolon();
	PRED_OP Operator();
	string to_Semicolon();
	string to_Word();
	bool end();
};

vector<string> splitComma(string S);
string trim(string s);

void dbms_init();
void dbms_quit();