#include"interpreter.hpp"
#include<iostream>
#include<fstream>
using namespace std;

int main(){
    // fstream fout(".\\out.txt", ios::out);
    // cout.rdbuf(fout.rdbuf());
    // std::ios::sync_with_stdio(false);
    dbms_init();
    start();
    dbms_quit();
}