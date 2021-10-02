#include "interpreter.hpp"
#include"api.hpp"
#include <iostream>
#include <iomanip>
#include <set>
using namespace std;

Instructor::Instructor(string S)
{
	str = S;
	cnt = 0;
}

Instructor::~Instructor()
{
}

string Instructor::Word()//get word
{
	string temp;
	int flag = 0;
	while (cnt < str.length() &&
		!(str[cnt] >= 'A' && str[cnt] <= 'Z' ||
			str[cnt] >= 'a' && str[cnt] <= 'z' ||
			str[cnt] >= '0' && str[cnt] <= '9' ||
			str[cnt] == '_' || str[cnt] == '.' ||
			str[cnt] == '-' || str[cnt] == '\'' ||
			str[cnt] == '*' || str[cnt] == ';' ||
			str[cnt] == '#'))
		cnt++;

	while (cnt < str.length() &&
		((str[cnt] >= 'A' && str[cnt] <= 'Z' ||
			str[cnt] >= 'a' && str[cnt] <= 'z' ||
			str[cnt] >= '0' && str[cnt] <= '9' ||
			str[cnt] == '_' || str[cnt] == '.' ||
			str[cnt] == '-' || str[cnt] == '\'' ||
			str[cnt] == '*' || str[cnt] == '#') || flag))
	{
		if (str[cnt] == '\'')
			flag = 1 - flag;
		temp += str[cnt++];
	}
	return temp;
}

string trim(string s)//delete empty space
{
	int i = 0;
	while (s[i] == ' ')
		i++;
	int j = s.length() - 1;
	while (s[j] == ' ')
		j--;
	return s.substr(i, j - i + 1);
}

string Instructor::Brackets()//get string inside the Brackets
{
	string temp;
	int st = 0;
	int flag = 0;
	while (cnt < str.length() && str[cnt] != '(')
		cnt++;
	do
	{
		if (str[cnt] == '(' && !flag)
			st++;
		if (str[cnt] == ')' && !flag)
			st--;
		if (str[cnt] == '\'')
			flag = 1 - flag;
		temp += str[cnt++];
	} while (cnt < str.length() && st);
	return trim(temp.substr(1, temp.length() - 2));
}

vector<string> splitComma(string S)//get string between Commas
{
	vector<string> vec;
	string::size_type t = 0;
	while (t != string::npos)
	{
		int temp = S.find_first_of(',', t);
		vec.push_back(trim(S.substr(t, temp - t)));
		if (temp != string::npos)
			t = temp + 1;
		else
			t = string::npos;
	}
	return vec;
}

bool Instructor::have_Semicolon()//Semicolon check
{
	while (cnt < str.length() && str[cnt] != ';')
		cnt++;
	if (cnt < str.length()) {
		cnt++;
		return true;
	}
	return false;
}

PRED_OP Instructor::Operator()//get Operator
{
	string temp;
	PRED_OP p;
	while (cnt < str.length() && str[cnt] != '<' && str[cnt] != '>' && str[cnt] != '='&&str[cnt] != '!')
		cnt++;
	while (cnt < str.length() && !(str[cnt] != '<' && str[cnt] != '>' && str[cnt] != '='&&str[cnt] != '!'))
		temp += str[cnt++];
	if (temp == ">")
		p = G;
	else if (temp == ">=")
		p = GE;
	else if (temp == "=")
		p = E;
	else if (temp == "<=")
		p = LE;
	else if (temp == "<")
		p = L;
	else if (temp == "!=" || temp == "<>")
		p = NE;
	else
		cerr << "Operator unavailable!" << endl;
	return p;
}

string Instructor::to_Semicolon()//get until Semicolon
{
	string temp;
	while (cnt < str.length() && str[cnt] != ';')
		temp += str[cnt++];
	cnt--;
	return temp;
}

string Instructor::to_Word()//get logic symbols
{
	string temp;
	while (cnt < str.length() &&
		!(str[cnt] >= 'A' && str[cnt] <= 'Z' ||
			str[cnt] >= 'a' && str[cnt] <= 'z' ||
			str[cnt] >= '0' && str[cnt] <= '9' ||
			str[cnt] == '_' || str[cnt] == '.' ||
			str[cnt] == '-' || str[cnt] == '\'' ||
			str[cnt] == '*' || str[cnt] == '#'))
		temp += str[cnt++];
	return temp;
}

bool Instructor::end()
{
	return cnt == str.length();
}

void execute(string &cmd, int flag)
{
	transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);//change to lower

	Instructor Sp(cmd);
	string wd = Sp.Word();
	if (wd == "create")
	{
		wd = Sp.Word();
		if (wd == "table")
		{
			create_Table(Sp, wd, flag);
			return;
		}
		if (wd == "index")
		{
			create_Index(Sp, wd, flag);
			return;
		}
	}
	if (wd == "insert")
	{
		insert_Record(Sp, wd, flag);
		return;
	}
	if (wd == "select")
	{
		select_Record(Sp, wd, flag);
		return;
	}
	if (wd == "delete")
	{
		delete_Record(Sp, wd, flag);
		return;
	}
	if (wd == "drop")
	{
		string wd = Sp.Word();
		if (wd == "table")
		{
			drop_Table(Sp, wd, flag);
			return;
		}
		if (wd == "index")
		{
			drop_Index(Sp, wd, flag);
			return;
		}
	}
	if (wd == "execfile") {
		exec_file(Sp, wd, flag);
		return;
	}
	cerr << "Syntax error: unknown command." << endl;

	return;
}

void start() {
	while (true) {
		string cmd;
		int flag = 1;
		cout << "MiniSQL >>> ";
		bool finish = false;
		while (finish == false) {
			string tmp;
			getline(cin, tmp);
			int t = tmp.find_first_of(';', 0);
			if (t != string::npos) {
				cmd += tmp.substr(0, t + 1);
				finish = true;
			}
			else {
				cmd += tmp;
				cout << "        >>> ";
			}
		}
		clock_t startTime = clock();
		transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);
		if (cmd == "exit;" || cmd == "quit;") break;
		else if (cmd == "clear;") system("cls");
		else execute(cmd, flag);

	}
}

void dbms_init() {
	api_init();
}

void dbms_quit() {
	api_quit();
}