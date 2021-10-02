#include "utils.h"

using namespace std;

extern SETTING settings;

void verbose(string msg){
    static int info_cnt=0, err_cnt=0;
    if(settings.verbose){
        cout << "[\033[32mINFO\033[0m] " << ++info_cnt  << ": " << msg << endl;
    }
}

void error_exit(string msg, bool isFatal, int exit_code){
    if(isFatal) cerr << "[\033[31mFATAL ERROR\033[0m] " << msg << endl;
    else cerr << "[\033[33mERROR\033[0m] " << msg << endl;
    exit(exit_code);
}