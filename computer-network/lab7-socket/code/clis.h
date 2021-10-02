#ifndef _CLIS_H_
#define _CLIS_H_

#include<iostream>
#include<vector>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include"package.h"

using namespace std;

#define CLIENT_NAME_MAX_LEN 10

struct client{
    int sock;
    struct sockaddr_in sockaddr;
    pid_t pid;
};

char* inet_ntoa(const in_addr_t& ip) throw();

void print_client_list(const vector<uchar>& dat, int from, uint len, int tab=0);

uchar *write_client_list(uint* len, const vector<struct client> &clients);

#endif