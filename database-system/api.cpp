#include<iostream>
#include<fstream>
#include"api.hpp"
#include"index.hpp"
#include"record.hpp"
using namespace std;
void api_init() {
	bool ret;
	ret = catalog_init();
	if (ret == false) {
		cerr << "initialization failed!" << endl;
		exit(0);
	}
	ret = index_init();
	if (ret == false) {
		cerr << "initialization failed!" << endl;
		exit(0);
	}
	ret = record_init();
	if (ret == false) {
		cerr << "initialization failed!" << endl;
		exit(0);
	}
	return;
}

void create_Table(Instructor &Sp, string &wd, int flag) {
	vector<string>aname;
	vector<TYPE>atype;
	int pk;
	vector<bool>uniq;
	vector<bool>nnull;

	string tableName = Sp.Word();

	string primary = "";
	if (tableName == "")//check table name
	{
		cerr << "Syntax error: Table name required!" << endl;
		return;
	}

	string ins = Sp.Brackets();

	if (ins == "")//check attributes
	{
		cerr << "Syntax error: Attributes required!" << endl;
		return;
	}

	vector<string> attrAndType = splitComma(ins);

	for (auto it : attrAndType)
	{
		if (it == "")//empty attr
		{
			cerr << "Syntax error: Syntax error arround ',' " << endl;
			return;
		}
		Instructor tempSp(it);
		string attrName = tempSp.Word();
		if (attrName == "primary")//primary key
		{
			if (primary != "")//primary key already exist
			{
				cerr << "Syntax error: Multi primary keys!" << endl;
				return;
			}

			wd = tempSp.Word();

			if (wd != "key")
			{
				cerr << "Syntax error: Unknown specifier \"" << wd << "\"!" << endl;
				return;
			}
			primary = tempSp.Brackets();
			break;
		}

		string attrType = tempSp.Word();
		int type;
		if (attrType == "char")//check attribute type
		{
			try {
				int k = stoi(tempSp.Brackets());
				if (k > 255) {
					cerr << "Syntax error: Input length exceeds defined length!" << endl;
					return;
				}
				type = CHAR_1 + k - 1;
			}//char size
			catch (...)
			{
				cerr << "Syntax error: Syntax error arround \"char\"!" << endl;
				return;
			}
		}
		else if (attrType == "int")
			type = INT;
		else if (attrType == "float")
			type = FLOAT;
		else
		{
			cerr << "Syntax error: Unknown attribute type \"" + attrType + "\"!" << endl;
			return;
		}

		bool notNull = false;
		bool unique = false;

		while ((wd = tempSp.Word()) != "")//check attr restrictions
		{
			if (wd == "notnull") notNull = true;
			else if (wd == "unique") unique = true;
			else if (wd == "primary")
			{
				if (primary != "")
				{
					cerr << "Syntax error: Multi primary keys!" << endl;
					return;
				}
				primary = wd;
			}
			else
			{
				cerr << "Syntax error: Unknown specifier \"" << wd << "\"!" << endl;
				return;
			}
		}
		aname.push_back(attrName);
		atype.push_back((TYPE)type);
		uniq.push_back(unique);
		nnull.push_back(notNull);
	}

	set<string> checkName;//check if attr_name is unique
	for (int i = 0; i < aname.size(); ++i)
	{
		if (aname[i] == primary)
			pk = i, nnull[i] = true, uniq[i] = true;//primary key
		if (!checkName.count(aname[i]))
			checkName.insert(aname[i]);//unique
		else
		{
			cerr << "Syntax error: Multidefined attribute \"" << wd << "\"!" << endl;//not unique
			return;
		}
	}

	if (!Sp.have_Semicolon())//check Semicolon
	{
		cerr << "Syntax error: Expected ';' !" << endl;
		return;
	}
	clock_t startTime = clock();

	TABLE tt = create_table(tableName, aname, atype, pk, uniq, nnull);//create table
	if (tt == NULL_TABLE) {
		cerr << "Internal error: create table failed!" << endl;
		return;
	}
	if (primary != "") {
		INDEX idx = create_index("Default", tt, get_attribute_handle(tt, primary));//create index for PK
		if (idx == NULL_INDEX) {
			cerr << "Internal error: create index failed!" << endl;
			return;
		}
	}
	string time = to_string((int)((clock() - startTime) * 1000 / CLOCKS_PER_SEC)) + " ms";

	if (flag != -1)
		cout << "create table succuess in " << time << "." << endl;
	return;
}

void drop_Table(Instructor &Sp, string &wd, int flag) {
	string tableName = Sp.Word();
	if (!Sp.have_Semicolon())//check Semicolon
	{
		cerr << "Syntax error: Expected ';' !" << endl;
		return;
	}
	clock_t startTime = clock();
	TABLE t = get_table_handle(tableName);
	vector<ATTR>tmp = get_table_attr(t);
	for (int i = 0; i < tmp.size(); i++) {
		INDEX ind = get_index_handle(t, tmp[i]);
		if (ind != -1)
			drop_index(ind);
	}
	bool dp = drop_table(t);//drop table
	string time = to_string((int)((clock() - startTime) * 1000 / CLOCKS_PER_SEC)) + " ms";


	if (dp == false) {
		cerr << "Internal error: drop table failed!" << endl;
		return;
	}
	if (flag != -1)
		cout << "drop table succuess in " << time << "." << endl;
	return;
}

void create_Index(Instructor &Sp, string &wd, int flag) {
	string indexName = Sp.Word();//get index name
	wd = Sp.Word();
	if (wd != "on")
	{
		cerr << "Syntax error: \"ON\" expected !" << endl;
		return;
	}
	string tableName = Sp.Word();//get table name

	string attrName = Sp.Brackets();//get attr name

	clock_t startTime = clock();
	TABLE tt = get_table_handle(tableName);
	ATTR attr = get_attribute_handle(tt, attrName);
	bool is = is_attr_unique(attr);
	if (get_index_handle(tt, attr) == -1) {
		if (is == true)
			create_index(indexName, tt, get_attribute_handle(tt, attrName));//create index
		else {
			cerr << "Syntax error: Index MUST be created on a unique attribute!" << endl;
			return;
		}
	}
	else {
		cerr << "Syntax error: Index already exists!" << endl;
		return;
	}
	string time = to_string((int)((clock() - startTime) * 1000 / CLOCKS_PER_SEC)) + " ms";

	if (flag != -1)
		cout << "Index created successfully in " << time << "." << endl;

	return;
}

void drop_Index(Instructor &Sp, string &wd, int flag) {
	string indexName = Sp.Word();
	if (!Sp.have_Semicolon())//check Semicolon
	{
		cerr << "Syntax error: Expected ';' !" << endl;
		return;
	}

	INDEX ind = get_index_handle(indexName);
	clock_t startTime = clock();
	if (ind != -1) {
		drop_index(ind);//drop index
	}
	else {
		cerr << "Syntax error: No such index!" << endl;
		return;
	}
	string time = to_string((int)((clock() - startTime) * 1000 / CLOCKS_PER_SEC)) + " ms";

	if (flag != -1)
		cout << "Index dropped successfully in " << time << "." << endl;
	return;
}

void insert_Record(Instructor &Sp, string &wd, int flag) {
	string tableName;
	wd = Sp.Word();
	if (wd != "into")//grammar check
	{
		cerr << "Syntax error: 'INTO' expected !" << endl;
		return;
	}

	tableName = Sp.Word();
	wd = Sp.Word();
	if (wd != "values")//grammar check
	{
		cerr << "Syntax error: 'VALUES' expected !" << endl;
		return;
	}

	wd = Sp.Brackets();
	int cnt = 0;
	bool noAttrName = false;
	bool hasAttrName = false;

	TABLE T_handle = get_table_handle(tableName);//get table_handle

	vector<string> values = splitComma(wd);
	vector<ATTR> tmp = get_table_attr(T_handle);
	if (values.size() != tmp.size()) {
		cerr << "Syntax error: Enough attributes needed!" << endl;
		return;
	}
	vector<string>val;
	for (auto it : values)
	{
		Instructor tempSp(it);
		string str1 = tempSp.Word();
		TYPE tp = get_attribute_type(tmp[cnt]);
		if (str1 == "null") {
			if (is_attr_notnull(tmp[cnt]) == true) {
				cerr << "Syntax error: Attribute(s) must not be NULL!" << endl;
				return;
			}
			else if (tp == INT) {
				string str2 = "";
				val.push_back(str2);
				cnt++;
			}
			else if (tp == FLOAT) {
				string str2 = "";
				val.push_back(str2);
				cnt++;
			}
			else {
				string str2 = "";
				val.push_back(str2);
				cnt++;
			}
		}
		else if (str1[0] == '\'') {
			if (tp == INT || tp == FLOAT) {
				cerr << "Syntax error: Wrong type of value(s)." << endl;
				return;
			}
			if (str1.length() > (tp - CHAR_1 + 1)) {
				cerr << "Syntax error: Attribute out of range." << endl;
				return;
			}
			string str2 = str1.substr(1, str1.length() - 2);
			val.push_back(str2);
			cnt++;
		}
		else {
			char st = 'a';
			for (int i = 0; i < str1.length(); i++) {
				st = str1[i];
				if (st == '.')
					break;
			}
			if (st == '.') {
				if (tp == INT) {
					cerr << "Syntax error: Wrong type of value(s)." << endl;
					return;
				}
			}
			val.push_back(str1);
			cnt++;
		}
	}

	if (!Sp.have_Semicolon())//check Semicolon
	{
		cerr << "Syntax error: Expected ';' !" << endl;
		return;
	}
	//unique
	for (int i = 0; flag != -1 && i < tmp.size(); i++) {
		if (tmp[i] == get_table_pk(T_handle)) {
			INDEX tp = get_index_handle(T_handle, tmp[i]);
			bool suc1 = find_index(tp, val[i]);
			if (suc1 == false) {
				cerr << "Syntax error: Primary key needs to be unique!" << endl;
				return;
			}
		}
		else {
			if (is_attr_unique(tmp[i]) == true) {
				INDEX tp = get_index_handle(T_handle, tmp[i]);
				if (tp == -1) {
					bool suc2 = find_record(T_handle, tmp[i], val[i]);
					if (suc2 == false) {
						cerr << "Syntax error: Attribute needs to be unique!" << endl;
						return;
					}
				}
				else {
					bool suc2 = find_index(tp, val[i]);
					if (suc2 == false) {
						cerr << "Syntax error: Attribute needs to be unique!" << endl;
						return;
					}
				}
			}
		}
	}

	clock_t startTime = clock();

	TUPLE_POS tps = insert_record(T_handle, val);//insert record
	for (int i = 0; i < tmp.size(); i++) {
		INDEX tp = get_index_handle(T_handle, tmp[i]);
		if (tp != -1)
			insert_index(tp, val[i], tps);
	}

	string time = to_string((int)((clock() - startTime) * 1000 / CLOCKS_PER_SEC)) + " ms";

	if (flag != -1)
		cout << "Record inserted succuessfully in " << time << "." << "1 row(s) affected." << endl;

	return;
}

void delete_Record(Instructor &Sp, string &wd, int flag) {

	wd = Sp.Word();
	if (wd != "from")//grammar check
	{
		cerr << "Syntax error: \"FROM\" is expected !" << endl;
		return;
	}
	string tableName = Sp.Word();//get table name
	TABLE t = get_table_handle(tableName);
	vector<PRED> pred;
	struct PRED vec;
	wd = Sp.Word();
	if (wd == "where")
	{
		string cond = Sp.to_Semicolon();//get where statement
		Instructor tempSp(cond);
		string tmp = tempSp.to_Word();
		while (!tempSp.end())
		{
			string str1, str3;
			PRED_OP p;
			ATTR tp;
			str1 = tempSp.Word();
			if (str1 == "") break;
			if (str1 == "and")
			{
				tmp = tempSp.to_Word();
				continue;
			}
			tp = get_attribute_handle(t, str1);
			if (tp == NULL_ATTR) {
				cerr << "Syntax error: Attribute not found." << endl;
				return;
			}
			p = tempSp.Operator();
			str3 = tempSp.Word();
			vec.left = tp;
			vec.op = p;
			TYPE y = get_attribute_type(tp);
			if (y != INT && y != FLOAT)
				str3 = str3.substr(1, str3.length() - 2);
			vec.right = str3;
			pred.push_back(vec);
		}
	}
	if (!Sp.have_Semicolon())
	{
		cerr << "Syntax error: Expected ';' !" << endl;
		return;
	}
	TEMP_TABLE set;
	clock_t startTime = clock();
	bool suc1 = delete_record(t, pred, set);
	bool suc2;
	INDEX idx;
	for (int i = 0; i < set.attr.size(); i++) {
		idx = get_index_handle(t, set.attr[i]);
		for (int j = 0; j < set.tuples.size(); j++) {
			if (idx != -1) {
				suc2 = delete_index(idx, set.tuples[j][i]);
			}
		}
	}


	string time = to_string((int)((clock() - startTime) * 1000 / CLOCKS_PER_SEC)) + " ms";

	if (flag != -1)
		cout << "Record deleted succuessfully in " << time << "." << set.tuples.size() << " row(s) affected." << endl;
	return;
}

void select_Record(Instructor &Sp, string &wd, int flag) {
	vector<string> Attr1;//ATTR temp;
	while (wd != "from" && wd != "")
	{
		wd = Sp.Word();
		if (wd != "from") {
			Attr1.push_back(wd);
		}
	}
	if (wd == "")
	{
		cerr << "Syntax error: \"FROM\" is expected !" << endl;
		return;
	}
	string tableName = Sp.Word();//get table name
	TABLE t = get_table_handle(tableName);
	if (t == NULL_TABLE) {
		cerr << "Syntax error: Table not found!" << endl;
		return;
	}
	vector<ATTR>Pos = get_table_attr(t);
	vector<ATTR>Attr;
	vector<int>pos;
	if (Attr1[0] == "*") {
		Attr = get_table_attr(t);
	}
	else {
		for (int i = 0; i < Attr1.size(); i++) {
			if (get_attribute_handle(t, Attr1[i]) == NULL_ATTR) {
				cerr << "Syntax error:Attribute not found!" << endl;
				return;
			}
			else
				Attr.push_back(get_attribute_handle(t, Attr1[i]));
		}
	}

	for (int i = 0; i < Attr.size(); i++) {
		for (int j = 0; j < Pos.size(); j++) {
			if (Attr[i] == Pos[j])
				pos.push_back(j);
		}
	}
	vector<PRED>pred;
	struct PRED vec;
	wd = Sp.Word();
	if (wd == "where")
	{
		string cond = Sp.to_Semicolon();//get where statement
		Instructor tempSp(cond);
		string tmp = tempSp.to_Word();
		while (!tempSp.end())
		{
			string str1, str3;
			PRED_OP p;
			ATTR tp;
			str1 = tempSp.Word();
			if (str1 == "") break;
			if (str1 == "and")
			{
				tmp = tempSp.to_Word();
				continue;
			}
			tp = get_attribute_handle(t, str1);
			if (tp == NULL_ATTR) {
				cerr << "Syntax error: Attribute not found." << endl;
				return;
			}
			p = tempSp.Operator();
			str3 = tempSp.Word();
			vec.left = tp;
			vec.op = p;
			TYPE y = get_attribute_type(tp);
			if (y != INT && y != FLOAT)
				str3 = str3.substr(1, str3.length() - 2);
			vec.right = str3;
			pred.push_back(vec);
		}
	}
	if (!Sp.have_Semicolon())// Semicolon check
	{
		cerr << "Syntax error: Expected ';'" << endl;
		return;
	}

	if (Attr.size() == 0)
	{
		cerr << "Syntax error: No attribute is selected." << endl;
		return;
	}

	clock_t startTime = clock();

	INDEX idx = NULL_INDEX;
	for (int i = 0; i < pred.size(); i++) {
		if (get_index_handle(t, pred[i].left) != NULL_INDEX && pred[i].op != NE) {
			idx = get_index_handle(t, pred[i].left);
			break;
		}
	}
	TEMP_TABLE set;
	bool suc;
	if (idx == NULL_INDEX) {
		suc = select_record(t, pred, set);
	}
	else
		suc = select_index(idx, pred, set);

	string time = to_string((int)((clock() - startTime) * 1000 / CLOCKS_PER_SEC)) + " ms";

	int cntr = 0;
	vector<int>width;
	if (set.tuples.size() == 0)
		cout << "No result found!." << endl;
	else {
		cout << "      ||";
		cntr += 8;
		for (int i = 0; i < Attr.size(); i++) {
			TYPE tmp = get_attribute_type(Attr[i]);
			string st = get_attribute_name(Attr[i]);
			int wd;
			if (tmp == INT)
				wd = INT_WD;
			else if (tmp == FLOAT)
				wd = FLT_WD;
			else
				wd = tmp + 3;
			width.push_back(wd);
			cout << setiosflags(ios::left) << setw(wd) << st;
			cout << "||";
			cntr += (wd + 2);
		}
		cout << endl;
		int cp = 1;
		for (int i = 0; i < set.tuples.size(); i++) {
			cout << setiosflags(ios::left) << setw(6) << cp++;
			cout << "||";
			for (int j = 0; j < Attr.size(); j++) {
				cout << setiosflags(ios::left) << setw(width[j]) << set.tuples[i][pos[j]];
				cout << "||";
			}
			cout << endl;
		}
		for (int p = 0; p < cntr; p++)
			cout << "-";
		cout << endl;
	}

	if (flag != -1)
		cout << "Record selected succuessfully in " << time << "." << set.tuples.size() << " row(s) affected." << endl;
	return;
}

void exec_file(Instructor &Sp, string &wd, int flag) {
	clock_t startTime = clock();
	string fileName = trim(Sp.to_Semicolon());
	ifstream fin(fileName);
	if (!Sp.have_Semicolon())
	{
		cerr << "Syntax error: Expected ';'" << endl;
		return;
	}
	if (!fin.good())
	{
		cerr << "Syntax error: File \"" + fileName + "\" does not exist." << endl;
		return;
	}
	int l = 0;

	while (!fin.eof())
	{
		string str;
		getline(fin, str);
		int t = str.find_first_of("--", 0);
		if (t != string::npos) {
			str = str.substr(0, t);
		}
		t = str.find_first_of(';', 0);
		if (t != string::npos) {
			str = str.substr(0, t + 1);
		}
		int ptr = 0;
		for (int i = 0; i < str.length(); i++) {
			if (str[i] != ' ')
				ptr = 1;
		}
		if (ptr == 1) {
			execute(str, -1);
			l++;
		}
	}
	string time = to_string((int)((clock() - startTime) * 1000 / CLOCKS_PER_SEC)) + " ms";

	if (flag != -1)
		cout << "Execfile successfully in " << time << ". " << l << " instrctions executed." << endl;
	return;
}

void api_quit() {
	record_quit();
	index_quit();
	catalog_quit();
	exit(0);
}
