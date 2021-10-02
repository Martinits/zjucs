#include<iostream>
#include<vector>
#include<cstring>
#include"catalog.hpp"
#include"buffer.hpp"
using namespace std;

// static vector<block> blocks;
static block blocks[block_max_cap];
static int blocks_num=0;

static bool write_block(const string& block_path, uchar* src, int block_num=1){
    // FILE* fp=fopen(file_path.c_str(), "rb");
    // if(fp==NULL) return false;
    // fseek(fp, 0, SEEK_END);
    // int file_size=ftell(fp);
    // int file_blocks=(file_size+block_size-1)/block_size;
    // if(file_blocks<offset_blocks+block_num) return false;
    // uchar tmp[file_size];
    // fseek(fp, 0, SEEK_SET);
    // size_t read_size=fread(tmp, block_size, file_blocks, fp);
    // if(read_size!=file_blocks) return false;
    // fclose(fp);
    // memcpy(tmp+offset_blocks*block_size, src, block_num*block_size);
    FILE* fp=fopen(block_path.c_str(), "wb");
    if(fp==NULL) return false;
    int write_size=fwrite(src, block_size, block_num, fp);
    if(write_size!=block_num) return false;
    fclose(fp);
    return true;
}

static bool write_back(int pos){
    if(!blocks[pos].dirty_bit) return true;
    // BLOCK_POS bp=get_block_pos(blocks[pos].handle);
    // string file_path=get_file_path(bp.first);
    string block_path=get_block_path(blocks[pos].handle);
    uchar tmp[block_size];
    memcpy(tmp, blocks[pos].content, block_size);
    if(!write_block(block_path, tmp)) return false;
    return true;
}

static int replace(){
    float min;
    int minpos=-1;
    for(int i=0;i<blocks_num;i++){
        if(blocks[i].pinned||blocks[i].borrowed) continue;
        float f=blocks[i].used_times*used_times_weight-blocks[i].unused_gap*unused_gap_weight;
        if(minpos==-1||f<min){
            minpos=i;
            min=f;
        }
    }
    if(minpos==-1) return -1;
    if(!write_back(minpos)) return -1;
    // for(int i=minpos;i<block_max_cap-1;i++) blocks[i]=blocks[i+1];
    // blocks_num--;
    return minpos;
}

static int find_block_in_mem(BLOCK_HANDLE bh){
    for(int i=0;i<blocks_num;i++){
        if(blocks[i].handle==bh) return i;
    }
    return NOT_FOUND_IN_MEM;
}

static bool read_block(const string& block_path, uchar* dest, int block_num=1){
    FILE* fin=fopen(block_path.c_str(), "rb");
    if(fin==NULL) return false;
    uchar tmp[block_num*block_size];
    size_t read_size=fread(tmp, block_size, block_num, fin);
    if(read_size!=block_num) return false;
    fclose(fin);
    memcpy(dest, tmp, block_num*block_size);
    return true;
}

static int get_new_block(BLOCK_HANDLE bh){
    int pos=blocks_num;
    if(blocks_num>=block_max_cap){
        pos=replace();
        if(pos==-1) return NOT_FOUND_IN_MEM;
    }else blocks_num++;
    string block_path=get_block_path(bh);
    block newb;
    if(!read_block(block_path, newb.content)) return NOT_FOUND_IN_MEM;
    newb.borrowed=false;
    newb.dirty_bit=false;
    newb.handle=bh;
    newb.unused_gap=0;
    newb.used_times=0;
    newb.pinned=false;
    blocks[pos]=newb;
    return pos;
}

bool buffer_init(){
    blocks_num=0;
    const vector<BLOCK_HANDLE>& last_blocks=get_last_mem_blocks();
    for(int i=0;i<last_blocks.size()&&i<block_max_cap;i++){
        get_new_block(last_blocks[i]);
    }
    return true;
}

pblock get_block(BLOCK_HANDLE bh){
    int pos=find_block_in_mem(bh);
    if(pos==NOT_FOUND_IN_MEM) pos=get_new_block(bh);
    if(pos==NOT_FOUND_IN_MEM/* ||blocks[pos].borrowed */) return NULL;
    blocks[pos].borrowed=true;
    blocks[pos].used_times++;
    for(int i=0;i<blocks_num;i++){
        if(i==pos) blocks[i].unused_gap=0;
        else blocks[i].unused_gap++;
    }
    return blocks[pos].content;
}

bool return_block(BLOCK_HANDLE bh, bool dirty){
    int pos=find_block_in_mem(bh);
    if(pos==NOT_FOUND_IN_MEM) return false;
    blocks[pos].borrowed=false;
    blocks[pos].dirty_bit|=dirty;
    blocks[pos].pinned=false;
    return true;
}

bool pin_block(BLOCK_HANDLE bh){
    int pos=find_block_in_mem(bh);
    if(pos==NOT_FOUND_IN_MEM) return false;
    blocks[pos].pinned=true;
    return true;
}

bool buffer_quit(){
    bool flag=true;
    //write back as last
    vector<BLOCK_HANDLE> tmp;
    for(int i=0;i<blocks_num;i++) tmp.push_back(blocks[i].handle);
    flag&=store_last_mem_blocks(tmp);
    //all blocks not returned is considered dirty
    for(int i=0;i<blocks_num;i++){
        if(blocks[i].dirty_bit||blocks[i].borrowed) flag&=write_back(i);
    }
    blocks_num=0;
    return flag;
}

//catalog
void cat_new_block(FILE_HANDLE fh, BLOCK_HANDLE newbh){
    string fpath=get_block_path(fh, newbh);
    FILE* fp=fopen(fpath.c_str(), "wb");
    fwrite(zero_block, block_size, 1, fp);
    fclose(fp);
}