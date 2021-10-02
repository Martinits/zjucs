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
#include"package.h"
#include"clis.h"

using namespace std;

int FUNC_BEGIN=__LINE__;
#define CONNECT     (1)
#define DISCONNECT  (2)
#define GETTIME     (3)
#define GETNAME     (4)
#define GETCLIENT   (5)
#define SENDMSG     (6)
#define QUIT        (0)
int FUNC_NUM=(__LINE__)-(FUNC_BEGIN)-2;

#define BUF_SIZE (2048)

int client_sock=-1;

bool connected=false;
struct sockaddr_in server_sockaddr;
string ip_port="";
pid_t child_pid=-1;

inline bool isdigit_string(const string& s){
	for(int i=0;i<s.size();i++){
		if(!isdigit(s[i])) return false;
	}
	return true;
}

void error_exit(const string& info, int ret_code=1){
	cerr << "ERROR: " << info << endl;
	if(connected) kill(child_pid, SIGKILL);
	exit(ret_code);
}

void disconnect(bool quiet){
	if(!connected){
		if(!quiet) cout << "No connection established!" << endl;
		return;
	}
	if(!quiet) cout << "Disconnecting " << ip_port << "......";
	uint packlen;
    uchar* pack=get_pack(&packlen, PACKTYPE_DISCONNECT, server_sockaddr.sin_addr.s_addr);
	if(send(client_sock, pack, packlen, 0)!=packlen){
		cout << "Failed" << endl;
		return;
	}
	kill(child_pid, SIGKILL);
	child_pid=-1;
	close(client_sock);
	connected=0;
	if(!quiet) cout << "Done" << endl;
}

void client_exit_shell(int signo){
    cout << endl << "Ctrl-C from user, exiting....." << endl;
	disconnect(1);
    exit(0);
}

void init(){
	signal(SIGINT, client_exit_shell);
	memset(&server_sockaddr, 0, sizeof(server_sockaddr));
}

void welcome(){
    cout << "***********************************" << endl;
    cout << "*                                 *" << endl;
    cout << "*   welcome to client interface   *" << endl;
    cout << "*                                 *" << endl;
    cout << "***********************************" << endl << endl;
}

int menu(){
    cout << endl << "***  MENU  ***" << endl;
    cout << "1. connect" << endl;
    if(connected){
        cout << "2. disconnect" << endl;
        cout << "3. get time" << endl;
        cout << "4. get name" << endl;
        cout << "5. get client list" << endl;
        cout << "6. send message" << endl;
    }
    cout << "0. quit" << endl << endl;
	cout << "Choose one to continue, using the number: >";
	bool flag;
	while(1){
		string buf;
		getline(cin, buf);
		flag=isdigit_string(buf);
		int ret=-1;
		if(flag){
			ret=atoi(buf.c_str());
			if(ret<0 || ret>(connected ? FUNC_NUM : 1)) flag=false;
		}
		if(!flag){
			cout << "Invalid input!!! Try again: >";
			continue;
		}
		return ret;
	}
}

void print_pack(vector<uchar>& dat, uint len){
	uchar *buf=(uchar*)malloc(sizeof(uchar)*len);
	uint i;
	for(i=0;i<len;i++) buf[i]=dat[i];
	
	//dat print
	int k=sizeof(package::len);
	uint type;
	in_addr_t from, to;
	uchar *content=(uchar*)malloc(sizeof(uchar)*CONTENT_SIZE(len));
	uchar *tmp=(uchar*)&type;
	for(int j=0;j<sizeof(type);j++) tmp[j]=dat[k++];
	tmp=(uchar*)&from;
	for(int j=0;j<sizeof(type);j++) tmp[j]=dat[k++];
	tmp=(uchar*)&to;
	for(int j=0;j<sizeof(type);j++) tmp[j]=dat[k++];
	switch(type){
		case PACKTYPE_SENDMSG:{
			cout << endl << "[MESSAGE] From " << (from==server_sockaddr.sin_addr.s_addr ? "server" : inet_ntoa(from)) << ":" << endl;
			cout << "          ";
			for(int j=k;j<len;j++) cout << dat[j];
			cout << endl;
			break;
		}
		case PACKTYPE_ACKTIME:{
			cout << endl << "[ACK] Time from server:" << endl;
			cout << "      ";
			for(int j=k;j<len;j++) cout << dat[j];
			cout << endl;
			break;
		}
		case PACKTYPE_ACKNAME:{
			cout << endl << "[ACK] Name from server:" << endl;
			cout << "      ";
			for(int j=k;j<len;j++) cout << dat[j];
			cout << endl;
			break;
		}
		case PACKTYPE_ACKCLIENT:{
			cout << endl << "[ACK] Client list from server:" << endl;
			print_client_list(dat, k, len, 6);
			cout << endl;
			break;
		}
	}
	free(buf);
	int remain=dat.size()-len;
	buf=(uchar*)malloc(sizeof(uchar)*remain);
	int bufi=0;
	for(;i<dat.size();i++) buf[bufi++]=dat[i];
	dat.clear();
	vector_push(dat, buf, remain);
	free(buf);
}

void child_recv_pack(){
	static vector<uchar> dat;
	uchar buf[BUF_SIZE];
	while(1){
		memset(buf, 0, sizeof(buf));
		ssize_t bytes=recv(client_sock, buf, sizeof(buf), 0);
		if(bytes>0) vector_push(dat, buf, bytes);
		uint len=is_full_pack(dat);
		if(len>=0) print_pack(dat, len);
	}
}

bool get_ip_port(const string &buf, in_addr_t *ip, in_port_t *port){
	in_addr_t ipint=0xffffffffU;
	in_port_t portint=0;
	int pos=buf.find_first_of(':');
	bool flag=true;
	if(pos==string::npos){
		ipint=inet_addr(buf.c_str());
		if(ipint == 0xffffffffU) flag=false;
		else{
			if(ip) *ip=ipint;
			if(port) *port=0;
			return true;
		}
	}else{
		string ip=buf.substr(0, pos), port=buf.substr(pos+1);
		ipint=inet_addr(ip.c_str());
		if(ipint == 0xffffffffU) flag=false;
		if(!isdigit_string(port)) flag=false;
		portint=htons(atoi(port.c_str()));
		if(portint<1024) flag=false;
	}
	if(flag){
		if(ip) *ip=ipint;
		if(port) *port=portint;
		return true;
	}else return false;
}

void connect(){
	if(connected){
		cout << "An connection to " << ip_port << " has been establish." << endl;
		return;
	}
	client_sock=socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(client_sock==-1) error_exit("Cannot get a socket.");
	cout << "Please enter server IP address and port like '[IP]:[PORT]'" << endl;
	cout << "                  (use port greater than 1023 for safety): >";
	in_addr_t ipint=0xffffffffU;
	in_port_t portint=0;
	string buf;
	getline(cin, buf);
	if(!get_ip_port(buf, &ipint, &portint)){
		cout << "Invalid input!!!" << endl;
		return;
	}
	struct sockaddr_in server_tmp;
	memset(&server_tmp, 0, sizeof(server_tmp));
    server_tmp.sin_family=PF_INET;
    server_tmp.sin_addr.s_addr=ipint;
    server_tmp.sin_port=portint;
	string ip_port_tmp;
	stringstream ss;
	ss << inet_ntoa(ipint) << ":" <<  ntohs(portint);
	ss >> ip_port_tmp;
	cout << "Connecting " << ip_port_tmp << " ......";
	if(connect(client_sock, (struct sockaddr*)&server_tmp, sizeof(server_tmp))==-1) error_exit("Cannot connect to "+ip_port_tmp+".");
	connected=true;
	server_sockaddr=server_tmp;
	ip_port=ip_port_tmp;
	cout << "Done" << endl;
	pid_t pid=fork();
	if(pid==0){
		child_recv_pack();
		exit(0);
	}else if(pid>0){
		child_pid=pid;
	}else error_exit("Cannot create a child process.");
}

void gettime(){
	uint packlen;
	uchar* pack=get_pack(&packlen, PACKTYPE_GETTIME, server_sockaddr.sin_addr.s_addr);
	cout << "Sending " << packlen << " bytes to server to get time......"; 
	if(send(client_sock, pack, packlen, 0)==packlen) cout << "Done" << endl;
	else cout << "Failed" << endl;
}

void getname(){
	uint packlen;
	uchar* pack=get_pack(&packlen, PACKTYPE_GETNAME, server_sockaddr.sin_addr.s_addr);
	cout << "Sending " << packlen << " bytes to server to get name......"; 
	if(send(client_sock, pack, packlen, 0)==packlen) cout << "Done" << endl;
	else cout << "Failed" << endl;
}

void getclient(){
	uint packlen;
	uchar* pack=get_pack(&packlen, PACKTYPE_GETCLIENT, server_sockaddr.sin_addr.s_addr);
	cout << "Sending " << packlen << " bytes to server to get client list......"; 
	if(send(client_sock, pack, packlen, 0)==packlen) cout << "Done" << endl;
	else cout << "Failed" << endl;
}

void sendmsg(){
	cout << "Please enter destination IP: >";
	in_addr_t destip=0xffffffffU;
	string buf;
	getline(cin, buf);
	if(!get_ip_port(buf, &destip, NULL)){
		cout << "Invalid input!!!" << endl;
		return;
	}
	cout << "Enter the message you want to send, end with ENTER: >";
	buf="";
	getline(cin, buf);
	uint packlen;
	uchar* pack=get_pack(&packlen, PACKTYPE_SENDMSG, destip, (const uchar*)buf.c_str(), buf.length());
	cout << "Sending " << packlen << " bytes message to " << inet_ntoa(destip) << "......"; 
	if(send(client_sock, pack, packlen, 0)==packlen) cout << "Done" << endl;
	else cout << "Failed" << endl;
}

int main(){
    init();
    welcome();
	while(1){
        int choice=menu();
		switch(choice){
			case CONNECT: connect(); break;
			case DISCONNECT: disconnect(0); break;
			case GETTIME: gettime(); break;
			case GETNAME: getname(); break;
			case GETCLIENT: getclient(); break;
			case SENDMSG: sendmsg(); break;
			case QUIT:
				if(connected) disconnect(0);
				cout << endl << "Bye!" << endl << endl;
				return 0;
			default: break;
		}
    }
}