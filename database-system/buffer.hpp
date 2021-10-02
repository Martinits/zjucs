#pragma once
#include <climits>
#include<iostream>
#include"catalog.hpp"
#define NOT_FOUND_IN_MEM (-1)

static const int block_size=4096;
static const int block_max_cap=10;
static const float used_times_weight=0.5;
static const float unused_gap_weight=1.0-used_times_weight;

typedef unsigned char uchar;
typedef uchar* pblock;
typedef struct _block{
    uchar content[block_size];
    BLOCK_HANDLE handle;
    bool dirty_bit;
    bool borrowed;
    int used_times;
    int unused_gap;
    bool pinned;
}block;

const pblock zero_block[block_size]={0};

bool buffer_init();

pblock get_block(BLOCK_HANDLE bh);

bool return_block(BLOCK_HANDLE bh, bool dirty);

bool pin_block(BLOCK_HANDLE bh);

bool buffer_quit();

//catalog
void cat_new_block(FILE_HANDLE fh, BLOCK_HANDLE newbh);