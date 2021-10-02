#include<iostream>
#include<fstream>
#include<sstream>
#include<cstring>
#include<vector>
#include<unistd.h>
#include<signal.h>
#include<sys/types.h> 
#include<fcntl.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/shm.h>

using namespace std;

#define BUF_SIZE (2048)

int server_sock;
struct sockaddr_in server_sockaddr;
string server_name="Martinit's http server";
string serverip="";
vector<pid_t> children;
vector<int> sockets;

typedef unsigned char uchar;
typedef unsigned int uint;

#define REQ_TYPE_GET (0)
#define REQ_TYPE_POST (1)

struct http_req{
    int req_type;
    string url;
    string http_version;
    vector< pair<string, string> > req_heads;
    string data;
};

struct http_ack{
    string http_version;
    string code;
    string code_description;
    vector< pair<string, string> > heads;
    char *data;
    int datalen;
};

static void server_exit(int exitcode){
    for(int i=0;i<children.size();i++) kill(children[i], SIGINT);
    for(int i=0;i<sockets.size();i++) close(sockets[i]);
    exit(exitcode);
}

void error_exit(const string& info, int exitcode=1){
	cerr << "ERROR: " << info << endl;
    server_exit(exitcode);
}

void server_exit_shell(int signo){
    cout << endl << "Ctrl-C from user, exiting....." << endl;
    server_exit(0);
}

void child_sig_handle(int signo){
    if(signo==SIGINT) exit(0);
}

void vector_push(vector<uchar> &v, uchar* array, int len){
    v.resize(v.size()+len);
	for(int i=0;i<len;i++) v.push_back(array[i]);
}

int find_http_head(string &dat, int last_recv){
    int rn=dat.find("\r\n\r\n", last_recv);
    if(rn==string::npos) return -1;
    int pack_begin;
    if((pack_begin=dat.rfind("GET ", rn-4))==string::npos) pack_begin=dat.rfind("POST ", rn-5);
    return (pack_begin==string::npos) ? -1 : pack_begin;
}

char* make_http_pack(int* len, http_ack pack){
    string ack_pack;
    ack_pack+=pack.http_version;
    ack_pack+=" ";
    ack_pack+=pack.code;
    ack_pack+=" ";
    ack_pack+=pack.code_description;
    ack_pack+="\r\n";
    for(int i=0;i<pack.heads.size();i++){
        ack_pack+=pack.heads[i].first;
        ack_pack+=": ";
        ack_pack+=pack.heads[i].second;
        ack_pack+="\r\n";
    }
    ack_pack+="\r\n";
    for(int i=0;i<pack.datalen;i++) ack_pack+=pack.data[i];
    char *ret=(char*)malloc(sizeof(char)*ack_pack.length());
    for(int i=0;i<ack_pack.length();i++) ret[i]=ack_pack[i];
    *len=ack_pack.length();
    return ret;
}

int check_login(string s){
    int pos=s.find('&');
    if(pos==string::npos) return 0;
    string login=s.substr(0, pos);
    string pass=s.substr(pos+1);
    if(login.find("login=")!=0) return 0;
    if(pass.find("pass=")!=0) return 0;
    login=login.substr(strlen("login="));
    pass=pass.substr(strlen("pass="));
    return login == "3180104939" && pass == "123456";
}

int process_http_pack(int client_sock, http_req &pack){
    http_ack ack;
    int inst_close=0;
    if(pack.url[0]=='/') pack.url=pack.url.substr(1);
    if(pack.url=="favicon.ico") pack.url="html/img/favicon.ico";
    ack.http_version="HTTP/1.1";
    ack.heads.push_back(pair<string, string>("Server", server_name));
    if(pack.req_type==REQ_TYPE_GET){
        FILE *fp=fopen(pack.url.c_str(), "rb");
        if(fp==NULL){
            ack.code="404";
            ack.code_description="Resource not found";
            ack.heads.clear();
            ack.data=NULL;
            ack.datalen=0;
            inst_close=1;
        }else{
            fseek(fp, 0, SEEK_END);
            int flen=ftell(fp);
            char *buf=(char*)malloc(sizeof(char)*flen);
            rewind(fp);
            int readlen=fread(buf, 1, flen, fp);
            buf[readlen]=0;
            ack.data=buf;
            ack.datalen=readlen;
            ack.code="200";
            ack.code_description="OK";
            if(pack.url.substr(0, 3)=="txt") ack.heads.push_back(pair<string, string>("Content-Type", "text/plain"));
            else if(pack.url.substr(0, 8)=="html/img") ack.heads.push_back(pair<string, string>("Content-Type", "image/png"));
            else if(pack.url.substr(0, 4)=="html") ack.heads.push_back(pair<string, string>("Content-Type", "text/html"));
            char tmp[10];
            sprintf(tmp, "%d", readlen);
            ack.heads.push_back(pair<string, string>("Content-Length", tmp));
            fclose(fp);
            inst_close= pack.url.substr(0, 3)=="txt" ? 1 : 0;
        }
    }else if(pack.req_type==REQ_TYPE_POST){
        if(pack.url=="html/dopost"){
            ack.code="200";
            ack.code_description="OK";
            ack.heads.push_back(pair<string, string>("Content-Type", "text/html"));
            if(check_login(pack.data)) ack.data=(char *)"<html><body>Login Successfully</body></html>";
            else ack.data=(char *)"<html><body>Login Failed</body></html>";
            ack.datalen=strlen(ack.data);
            char tmp[10];
            sprintf(tmp, "%d", ack.datalen);
            ack.heads.push_back(pair<string, string>("Content-Length", tmp));
            inst_close=1;
        }else{
            ack.code="404";
            ack.code_description="Resource not found";
            ack.heads.clear();
            ack.data=NULL;
            ack.datalen=0;
            inst_close=1;
        }
    }else return 0;
    int len;
    char *http_pack=make_http_pack(&len, ack);
    int sendlen=send(client_sock, http_pack, len, 0);
    if(sendlen==len){
        if(inst_close){
            cout << "Child exiting, closing socket......" << endl;
            close(client_sock);
            exit(0);
        }
        return 1;
    }else return 0;
}

int try_read_http(int client_sock, string &dat, int http_head){
    if(http_head==-1) return 0;
    //try read
    http_req pack;
    int i=0;
    if(dat.substr(0, 4)=="GET "){
        pack.req_type=REQ_TYPE_GET;
        i=4;
    }else if(dat.substr(0, 5)=="POST "){
        pack.req_type=REQ_TYPE_POST;
        i=5;
    }else return 0;
    int pos = dat.find(' ', i);
    if(pos==string::npos) return 0;
    pack.url=dat.substr(i, pos-i);
    i=pos+1;
    
    pos=dat.find("\r\n", i);
    if(pos==string::npos) return 0;
    pack.http_version=dat.substr(i, pos-i);
    i=pos+2;

    while(1){
        pos=dat.find("\r\n", i);
        if(pos==string::npos) return 0;
        if(pos==i) break;
        string line=dat.substr(i, pos-i);
        i=pos+2;
        pos=line.find(": ");
        if(pos==string::npos) return 0;
        pair<string, string> head;
        head.first=line.substr(0, pos);
        head.second=line.substr(pos+2);
        pack.req_heads.push_back(head);
    }
    i+=2;

    int flag=-1;
    for(int j=0;j<pack.req_heads.size();j++){
        if(pack.req_heads[j].first=="Content-Length"){
            flag=j;
            break;
        }
    }
    if(flag!=-1){
        int datalen=atoi(pack.req_heads[flag].second.c_str());
        pack.data=dat.substr(i, datalen);
        i+=datalen;
    }

    //if success process
    if(!process_http_pack(client_sock, pack)) return 0;

    //cut dat
    dat=dat.substr(i);
    cout << "Send one pack" << endl;

    //return success or not
    return 1;
}

void child(int client_sock){
    static string dat;
	char buf[BUF_SIZE];
    int last_recv=-1;
    int http_head=-1;
	while(1){
		memset(buf, 0, sizeof(buf));
		ssize_t bytes;
        bytes=recv(client_sock, buf, sizeof(buf)-1, 0);
		if(bytes>0){
            last_recv=dat.length();
            buf[bytes]=0;
            dat+=buf;
            if(http_head==-1) http_head=find_http_head(dat, last_recv);
            if(http_head!=-1) try_read_http(client_sock, dat, http_head);
        }
	}
}

string get_local_ip(){
    FILE *fp=popen("ifconfig | grep 192.168.31. | awk \'{ print $2 }\'", "r");
    char buf[100];
    fgets(buf, sizeof(buf), fp);
    buf[strlen(buf)-1]=0;
	string ret=buf;
    return ret;
}

void init(){
    cout << "Server initializing......";
    signal(SIGINT, server_exit_shell);
    serverip=get_local_ip();
    server_sock=socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    memset(&server_sockaddr, 0, sizeof(server_sockaddr));
    server_sockaddr.sin_family=PF_INET;
    server_sockaddr.sin_addr.s_addr=inet_addr(serverip.c_str());
    server_sockaddr.sin_port=htons(4939);
    bind(server_sock, (struct sockaddr*)&server_sockaddr, sizeof(server_sockaddr));
    listen(server_sock, 20);
    children.clear();
    cout << "Done" << endl;
    cout << "Server " << inet_ntoa(server_sockaddr.sin_addr) << ':' << ntohs(server_sockaddr.sin_port) << " is running......" << endl;
}

int main(){
    init();
    while(1){
        struct sockaddr_in client_sockaddr;
        socklen_t socklen=sizeof(client_sockaddr);
        memset(&client_sockaddr, 0, sizeof(client_sockaddr));
        int client_sock=-1;
        while(client_sock==-1){
            cout << "Waiting for new clients......" << endl;
            client_sock=accept(server_sock, (struct sockaddr*)&client_sockaddr, &socklen);
        }
        cout << "Connection to " << inet_ntoa(client_sockaddr.sin_addr) << ':' << ntohs(client_sockaddr.sin_port) << " established." << endl;
        pid_t pid=fork();
        if(pid==0){
            signal(SIGINT, child_sig_handle);
            child(client_sock);
            exit(0);
        }else if(pid>0){
            children.push_back(pid);
            sockets.push_back(client_sock);
        }else error_exit("Cannot create a child process.");
    }
}