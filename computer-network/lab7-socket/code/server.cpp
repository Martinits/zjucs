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

int server_sock;
struct sockaddr_in server_sockaddr;
string servername="HOST SERVER";
string serverip="";

#define SHM_KEY (4939)
int shmid=-1;
#define SHM1_SIZE (sizeof(int)+100*sizeof(struct client))
#define SHM_TMP_SIZE (2000)
#define SHM_SIZE (SHM1_SIZE+SHM_TMP_SIZE)
struct client *shmaddr;

int shm_get_client_num(const struct client *shmaddr){
    int *num=(int*)shmaddr;
    return *num;
}

struct client shm_get_client(struct client* shmaddr, int pos){
    int num=shm_get_client_num(shmaddr);
    struct client* tmp=(struct client *)((int*)shmaddr+1);
    return tmp[pos];
}

vector<struct client> shm_get_clients(const struct client* shmaddr){
    int num=shm_get_client_num(shmaddr);
    struct client* tmp=(struct client *)((int*)shmaddr+1);
    vector<struct client> l;
    for(int i=0;i<num;i++) l.push_back(tmp[i]);
    return l;
}

void shm_add_client(struct client* shmaddr, const struct client& cli){
    int num=shm_get_client_num(shmaddr);
    struct client* tmp=(struct client *)((int*)shmaddr+1);
    if((sizeof(int)+(num+1)*sizeof(struct client))<=SHM1_SIZE) tmp[num]=cli;
    *(int*)shmaddr=num+1;
}

void shm_erase_client(struct client* shmaddr, int pos){
    int num=shm_get_client_num(shmaddr);
    struct client* tmp=(struct client *)((int*)shmaddr+1);
    if(pos<0 || pos>=num) return;
    for(int i=pos;i<num-1;i++) tmp[i]=tmp[i+1];
    memset(&(tmp[num-1]), 0, sizeof(tmp[num-1]));
    *(int*)shmaddr=num-1;
}

int shm_find_ip(const struct client* shmaddr, const in_addr_t& key){
    int num=shm_get_client_num(shmaddr);
    struct client* tmp=(struct client *)((int*)shmaddr+1);
    for(int i=0;i<num;i++) if(tmp[i].sockaddr.sin_addr.s_addr==key) return i;
    return -1;
}

int shm_find_pid(const struct client* shmaddr, const pid_t& pid){
    int num=shm_get_client_num(shmaddr);
    struct client* tmp=(struct client *)((int*)shmaddr+1);
    for(int i=0;i<num;i++) if(tmp[i].pid==pid) return i;
    return -1;
}

void disconnect(int pos, int is_server_exit){
    cout << "Disconnecting " << inet_ntoa(shm_get_client(shmaddr, pos).sockaddr.sin_addr) << ":" << ntohs(shm_get_client(shmaddr, pos).sockaddr.sin_port) << " ......";
    if(is_server_exit) kill(shm_get_client(shmaddr, pos).pid, SIGINT);
    close(shm_get_client(shmaddr, pos).sock);
    shm_erase_client(shmaddr, pos);
    cout << "Done" << endl;
}

static void server_exit(int exitcode){
    for(int i=0;i<shm_get_client_num(shmaddr);i++) disconnect(i, 1);
    close(server_sock);
    exit(exitcode);
}

void error_exit(const string& info, int exitcode=1){
	cerr << "ERROR: " << info << endl;
    server_exit(exitcode);
}

void signal_handle(int sig, siginfo_t *siginfo, void *p){
    static int last_ctrlz=0;
    if(sig==SIGINT){
        int pos=shm_find_pid(shmaddr, siginfo->si_pid);
        if(pos!=-1){
            cout << "Child exiting....." << endl;
            disconnect(pos, 0);
        }else{
            cout << endl << "Ctrl-C from user, exiting....." << endl;
            server_exit(0);
        }
    }else if(sig==SIGUSR1){
        int pos=shm_find_pid(shmaddr, siginfo->si_pid);
        if(pos!=-1){
            uint packlen;
            uchar *pack;
            uchar *tmp=(uchar*)shmaddr+SHM1_SIZE;
            packlen=*(uint*)tmp;
            pack=tmp+sizeof(packlen);
            in_addr_t to=*(in_addr_t*)(pack+TO_OFFSET);
            int ret=send(shm_get_client(shmaddr, shm_find_ip(shmaddr, to)).sock, pack, packlen, 0);
            ((uchar*)shmaddr)[SHM_SIZE-1]=ret;
        }
    }
}

void server_exit_shell(int signo){
    if(signo!=SIGINT) return;
    cout << endl << "Ctrl-C from user, exiting....." << endl;
    server_exit(0);
}

void process_pack(int shmid, int client_sock, struct client cli, uchar* pack, uint packlen){
    uint type=*(uint*)(pack+TYPE_OFFSET);
    const struct client *shmaddr=(struct client*)shmat(shmid, 0, 0);
    switch(type){
        case PACKTYPE_GETTIME:{
            char buf[100];  
            FILE *pf=popen("date", "r");
            fgets(buf, sizeof(buf), pf);
            pclose(pf);
            buf[strlen(buf)-1]=0;
            uint packlen;
	        uchar* pack=get_pack(&packlen, PACKTYPE_ACKTIME, server_sockaddr.sin_addr.s_addr, cli.sockaddr.sin_addr.s_addr, (uchar*)buf, strlen(buf));
            cout << "Sending " << packlen << " bytes time message to " << inet_ntoa(cli.sockaddr.sin_addr.s_addr) << "......"; 
            if(send(client_sock, pack, packlen, 0)==packlen) cout << "Done" << endl;
            else cout << "Failed" << endl;
            break;
        }
        case PACKTYPE_GETNAME:{
            uint packlen;
	        uchar* pack=get_pack(&packlen, PACKTYPE_ACKNAME, server_sockaddr.sin_addr.s_addr, cli.sockaddr.sin_addr.s_addr, (uchar*)servername.c_str(), servername.length());
            cout << "Sending " << packlen << " bytes name message to " << inet_ntoa(cli.sockaddr.sin_addr.s_addr) << "......"; 
            if(send(client_sock, pack, packlen, 0)==packlen) cout << "Done" << endl;
            else cout << "Failed" << endl;
            break;
        }
        case PACKTYPE_GETCLIENT:{
            uint content_len;
            uchar* content=write_client_list(&content_len, shm_get_clients(shmaddr));
            uint packlen;
	        uchar* pack=get_pack(&packlen, PACKTYPE_ACKCLIENT, server_sockaddr.sin_addr.s_addr, cli.sockaddr.sin_addr.s_addr, (uchar*)content, content_len);
            cout << "Sending " << packlen << " bytes clients message to " << inet_ntoa(cli.sockaddr.sin_addr.s_addr) << "......"; 
            if(send(client_sock, pack, packlen, 0)==packlen) cout << "Done" << endl;
            else cout << "Failed" << endl;
            break;
        }
        case PACKTYPE_SENDMSG:{
            in_addr_t to=*(in_addr_t*)(pack+TO_OFFSET);
            if(to==server_sockaddr.sin_addr.s_addr){
                cout << endl << "[MESSAGE] From " << inet_ntoa(cli.sockaddr.sin_addr.s_addr) << ":" << endl;
                cout << "          ";
                for(int j=CONTENT_OFFSET;j<packlen;j++) cout << pack[j];
                cout << endl;
                break;
            }else{
                int pos=shm_find_ip(shmaddr, to);
                if(pos==-1){
                    cout << "Received a message package with an unconnected destination: " << inet_ntoa(to) << ", dump it." << endl;
                    string content="Destination ";
                    content+=inet_ntoa(to);
                    content+=" does not exist!!!";
                    uint packlen;
	                uchar* pack=get_pack(&packlen, PACKTYPE_SENDMSG, server_sockaddr.sin_addr.s_addr, cli.sockaddr.sin_addr.s_addr, (uchar*)content.c_str(), content.length());
                    cout << "Noticing " << inet_ntoa(cli.sockaddr.sin_addr.s_addr) << "......"; 
                    if(send(client_sock, pack, packlen, 0)==packlen) cout << "Done" << endl;
                    else cout << "Failed" << endl;
                }else{
                    in_addr_t *pfrom=(in_addr_t*)(pack+FROM_OFFSET);
                    *pfrom=cli.sockaddr.sin_addr.s_addr;
                    cout << "Transponding " << packlen << " bytes message from " << inet_ntoa(cli.sockaddr.sin_addr.s_addr) << " to " << inet_ntoa(to) << "......"; 
                    uchar *tmp=(uchar*)shmaddr+SHM1_SIZE;
                    memset(tmp, 0, SHM_TMP_SIZE);
                    *(uint*)tmp=packlen;
                    tmp+=sizeof(packlen);
                    for(int i=0;i<packlen;i++) tmp[i]=pack[i];
                    kill(getppid(), SIGUSR1);
                    while(((uchar*)shmaddr)[SHM_SIZE-1]==0) usleep(1);
                    int ret=((uchar*)shmaddr)[SHM_SIZE-1];
                    memset((uchar*)shmaddr+SHM1_SIZE, 0, SHM_TMP_SIZE);
                    if(ret==packlen){
                        cout << "Done" << endl;
                        string content="Successfully send message to ";
                        content+=inet_ntoa(to);
                        uint packlen;
	                    uchar* pack=get_pack(&packlen, PACKTYPE_SENDMSG, server_sockaddr.sin_addr.s_addr, cli.sockaddr.sin_addr.s_addr, (uchar*)content.c_str(), content.length());
                        cout << "Noticing " << inet_ntoa(cli.sockaddr.sin_addr.s_addr) << "......"; 
                        if(send(client_sock, pack, packlen, 0)==packlen) cout << "Done" << endl;
                        else cout << "Failed" << endl;
                    }else{
                        cout << "Failed" << endl;
                        string content="Send message to ";
                        content+=inet_ntoa(to);
                        content+=" failed";
                        uint packlen;
	                    uchar* pack=get_pack(&packlen, PACKTYPE_SENDMSG, server_sockaddr.sin_addr.s_addr, cli.sockaddr.sin_addr.s_addr, (uchar*)content.c_str(), content.length());
                        cout << "Noticing " << inet_ntoa(cli.sockaddr.sin_addr.s_addr) << "......"; 
                        if(send(client_sock, pack, packlen, 0)==packlen) cout << "Done" << endl;
                        else cout << "Failed" << endl;
                    }
                }
            }
            break;
        }
        case PACKTYPE_DISCONNECT:{
            kill(getppid(), SIGINT);
            break;
        }
    }
}

void child_sig_handle(int signo){
    if(signo==SIGINT) exit(0);
}

void child(int shmid, int client_sock, struct client cli){
    uint packlen;
	uchar* pack=get_pack(&packlen, PACKTYPE_SENDMSG, server_sockaddr.sin_addr.s_addr, cli.sockaddr.sin_addr.s_addr, (uchar*)"Hello", 5);
    send(client_sock, pack, packlen, 0);

    static vector<uchar> dat;
	uchar buf[BUF_SIZE];
	while(1){
		memset(buf, 0, sizeof(buf));
		ssize_t bytes;
        while((bytes=recv(client_sock, buf, sizeof(buf), 0))==-1);
		if(bytes>0) vector_push(dat, buf, bytes);
		uint len=is_full_pack(dat);
		if(len>=0){
            uchar *tmp=(uchar*)malloc(sizeof(uchar)*len);
            for(int i=0;i<len;i++) tmp[i]=dat[i]; 
            process_pack(shmid, client_sock, cli, tmp, len);
            free(tmp);
            int remain=dat.size()-len;
            tmp=(uchar*)malloc(sizeof(uchar)*remain);
            for(int i=len;i<dat.size();i++) tmp[i-len]=dat[i];
            dat.clear();
            vector_push(dat, tmp, remain);
            free(tmp);
            cout << dat.size();
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

    struct sigaction act;
    act.sa_flags=SA_SIGINFO;
    sigemptyset(&act.sa_mask);
    act.sa_sigaction=signal_handle;
    sigaction(SIGINT, &act, NULL);
    sigaction(SIGUSR1, &act, NULL);
    shmid=shmget(SHM_KEY, SHM_SIZE, 0644|IPC_CREAT);
    if(shmid==-1) error_exit("Cannot create shared memory.");
    shmaddr=(struct client*)shmat(shmid, 0, 0);
    memset(shmaddr, 0, sizeof(SHM_SIZE));
    serverip=get_local_ip();
    server_sock=socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    memset(&server_sockaddr, 0, sizeof(server_sockaddr));
    server_sockaddr.sin_family=PF_INET;
    server_sockaddr.sin_addr.s_addr=inet_addr(serverip.c_str());
    server_sockaddr.sin_port=htons(4939);
    bind(server_sock, (struct sockaddr*)&server_sockaddr, sizeof(server_sockaddr));
    listen(server_sock, 20);
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
        cout << "Connection to " << inet_ntoa(client_sockaddr.sin_addr.s_addr) << ':' << ntohs(client_sockaddr.sin_port) << " established." << endl;
        pid_t pid=fork();
        if(pid==0){
            signal(SIGINT, child_sig_handle);
            struct client cli;
            cli.pid=pid;
            cli.sock=client_sock;
            cli.sockaddr=client_sockaddr;
            int shmid=shmget(SHM_KEY, SHM_SIZE, 0666);
            if(shmid==-1){
                cerr << "Child cannot get shared memory." << endl;
                exit(1);
            }
            child(shmid, client_sock, cli);
            exit(0);
        }else if(pid>0){
            struct client cli;
            cli.pid=pid;
            cli.sock=client_sock;
            cli.sockaddr=client_sockaddr;
            shm_add_client(shmaddr, cli);            
        }else error_exit("Cannot create a child process.");
    }
}