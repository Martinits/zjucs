#ifndef _PACKAGE_H_
#define _PACKAGE_H_

#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>

using namespace std;

typedef unsigned char uchar;
typedef unsigned int uint;
#define CONTENT_SIZE(tot_len) (tot_len-sizeof(uint)*2-sizeof(in_addr_t)*2)
#define CONTENT_MAX_LEN (CONTENT_SIZE(1024))
#define GET_PACK_LEN(content_len) (content_len+sizeof(uint)*2+sizeof(in_addr_t)*2)
#define LEN_OFFSET (0)
#define TYPE_OFFSET (sizeof(package::len))
#define FROM_OFFSET (TYPE_OFFSET+sizeof(package::type))
#define TO_OFFSET (FROM_OFFSET+sizeof(package::from))
#define CONTENT_OFFSET (TO_OFFSET+sizeof(package::to))

#define PACKTYPE_GETTIME     (3)
#define PACKTYPE_GETNAME     (4)
#define PACKTYPE_GETCLIENT   (5)
#define PACKTYPE_SENDMSG     (6)
#define PACKTYPE_ACKTIME     (7)
#define PACKTYPE_ACKNAME   (8)
#define PACKTYPE_ACKCLIENT   (9)
#define PACKTYPE_DISCONNECT  (10)

struct package{
    uint len;
    uint type;
    in_addr_t from;
    in_addr_t to;
    uchar content[CONTENT_MAX_LEN];
};

uchar* get_pack(uint* packlen, uint type, in_addr_t to, const uchar* content=NULL, uint content_len=0);

uchar* get_pack(uint *packlen, uint type, in_addr_t from, in_addr_t to, const uchar* content=NULL, uint content_len=0);

void vector_push(vector<uchar> &v, uchar* array, int len);

int is_full_pack(vector<uchar>& dat);

void print_pack(uchar* pack, uint packlen);

#endif