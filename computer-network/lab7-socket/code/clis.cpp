#include"clis.h"
#include"package.h"
#include<iostream>

using namespace std;

typedef unsigned char uchar;

typedef vector<string> clis;

static void print_client_list(const clis& clilist, int tab){
    for(int j=0;j<tab;j++) cout << " ";
    cout << "No.    " << "IP                  "  << endl;
    for(int i=0;i<clilist.size();i++){
        for(int j=0;j<tab;j++) cout << " ";
        printf("%-7d%-20s\n", i+1, clilist[i].c_str());
    }
}

void print_client_list(const vector<uchar>& dat, int from, uint len, int tab){
    int k=from;
    clis clilist;
    while(k<len){
        string ip_port;
        while(k<len && dat[k]!=0) ip_port+=dat[k++];
        if(k<len) clilist.push_back(ip_port); 
        k++;
    }
    print_client_list(clilist, tab);
}

uchar *write_client_list(uint* len, const vector<struct client> &clients){
    vector<uchar> dat;
    for(int i=0;i<clients.size();i++){
        string buf="";
        buf+=inet_ntoa(clients[i].sockaddr.sin_addr.s_addr);
        buf+=":";
        char tmp[10];
        sprintf(tmp, "%d", ntohs(clients[i].sockaddr.sin_port));
        buf+=tmp;
        for(int j=0;j<buf.length();j++) dat.push_back(buf[j]);
        dat.push_back(0);
    }
    uchar* dest=(uchar*)malloc(sizeof(uchar)*dat.size());
    for(int i=0;i<dat.size();i++) dest[i]=dat[i];
    *len=dat.size();
    return dest;
}

inline char* inet_ntoa(const in_addr_t& ip) throw() {
	struct in_addr ret;
	ret.s_addr=ip;
	return inet_ntoa(ret);
}