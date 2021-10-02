#include<vector>
#include"package.h"
#include"clis.h"
#include<iostream>

using namespace std;

uchar* get_pack(uint *packlen, uint type, in_addr_t to, const uchar* content, uint content_len){
	return get_pack(packlen, type, 0, to, content, content_len);
}

uchar* get_pack(uint *packlen, uint type, in_addr_t from, in_addr_t to, const uchar* content, uint content_len){
    if(content==NULL) content_len=0;
    *packlen=GET_PACK_LEN(content_len);
	uchar *pack=(uchar*)malloc(sizeof(uchar)*(*packlen));
    uchar *tmp=pack;
	uint *len=(uint*)tmp;
    *len=*packlen;
    tmp+=sizeof(package::len);
    uint *ptype=(uint*)tmp;
    *ptype=type;
    tmp+=sizeof(package::type);
    in_addr_t *pfrom=(in_addr_t*)tmp;
    *pfrom=from;
    tmp+=sizeof(package::from);
    in_addr_t *pto=(in_addr_t*)tmp;
    *pto=to;
    tmp+=sizeof(package::to);
    for(int i=0;i<content_len;i++) tmp[i]=content[i];
    return pack;
}

void vector_push(vector<uchar> &v, uchar* array, int len){
	for(int i=0;i<len;i++) v.push_back(array[i]);
}

int is_full_pack(vector<uchar>& dat){
	uchar tmp[4];
	tmp[0]=dat[0];
	tmp[1]=dat[1];
	tmp[2]=dat[2];
	tmp[3]=dat[3];
	uint *plen=(uint*)tmp;
	return dat.size()>=(*plen) ? *plen : -1;
}

void print_pack(uchar* pack, uint packlen){
    cout << packlen << ": ";
    for(int i=0;i<packlen;i++) printf("%02x", pack[i]);
    cout << endl;
}