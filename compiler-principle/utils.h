#pragma once

#include <iostream>
#include <ostream>

using namespace std;

class SETTING{
public:
    string input_file_name;
    string output_file_name_noext;
    bool verbose;
    bool emit_ll;
    bool emit_tree;
    bool emit_asm;
    bool emit_obj;
    bool emit_exe;
    string crt_lib_path="/lib/x86_64-linux-gnu/";
    string dl_path="/lib64/ld-linux-x86-64.so.2";
};

void verbose(string info);

void error_exit(string msg, bool isFatal = false, int exit_code = 1);