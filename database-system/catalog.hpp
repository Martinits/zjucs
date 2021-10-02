#pragma once

#include <climits>
#include<iostream>
#include<vector>
using namespace std;

const string catalog_file_path=".\\data\\catalog.data";
const string index_file_path=".\\data\\index\\";
const string table_file_path=".\\data\\table\\";

typedef int TABLE;
const TABLE NULL_TABLE=-1; 
typedef int ATTR;
const ATTR NULL_ATTR=-1;
typedef int INDEX;
const INDEX NULL_INDEX=-1;

#define NULL_INT INT_MAX
#define NULL_FLOAT __FLT_MAX__

enum TYPE{
    NULL_TYPE,
    INT,
    FLOAT,
    CHAR_1,
    CHAR_2,
    CHAR_3,
    CHAR_4,
    CHAR_5,
    CHAR_6,
    CHAR_7,
    CHAR_8,
    CHAR_9,
    CHAR_10,
    CHAR_11,
    CHAR_12,
    CHAR_13,
    CHAR_14,
    CHAR_15,
    CHAR_16,
    CHAR_17,
    CHAR_18,
    CHAR_19,
    CHAR_20,
    CHAR_21,
    CHAR_22,
    CHAR_23,
    CHAR_24,
    CHAR_25,
    CHAR_26,
    CHAR_27,
    CHAR_28,
    CHAR_29,
    CHAR_30,
    CHAR_31,
    CHAR_32,
    CHAR_33,
    CHAR_34,
    CHAR_35,
    CHAR_36,
    CHAR_37,
    CHAR_38,
    CHAR_39,
    CHAR_40,
    CHAR_41,
    CHAR_42,
    CHAR_43,
    CHAR_44,
    CHAR_45,
    CHAR_46,
    CHAR_47,
    CHAR_48,
    CHAR_49,
    CHAR_50,
    CHAR_51,
    CHAR_52,
    CHAR_53,
    CHAR_54,
    CHAR_55,
    CHAR_56,
    CHAR_57,
    CHAR_58,
    CHAR_59,
    CHAR_60,
    CHAR_61,
    CHAR_62,
    CHAR_63,
    CHAR_64,
    CHAR_65,
    CHAR_66,
    CHAR_67,
    CHAR_68,
    CHAR_69,
    CHAR_70,
    CHAR_71,
    CHAR_72,
    CHAR_73,
    CHAR_74,
    CHAR_75,
    CHAR_76,
    CHAR_77,
    CHAR_78,
    CHAR_79,
    CHAR_80,
    CHAR_81,
    CHAR_82,
    CHAR_83,
    CHAR_84,
    CHAR_85,
    CHAR_86,
    CHAR_87,
    CHAR_88,
    CHAR_89,
    CHAR_90,
    CHAR_91,
    CHAR_92,
    CHAR_93,
    CHAR_94,
    CHAR_95,
    CHAR_96,
    CHAR_97,
    CHAR_98,
    CHAR_99,
    CHAR_100,
    CHAR_101,
    CHAR_102,
    CHAR_103,
    CHAR_104,
    CHAR_105,
    CHAR_106,
    CHAR_107,
    CHAR_108,
    CHAR_109,
    CHAR_110,
    CHAR_111,
    CHAR_112,
    CHAR_113,
    CHAR_114,
    CHAR_115,
    CHAR_116,
    CHAR_117,
    CHAR_118,
    CHAR_119,
    CHAR_120,
    CHAR_121,
    CHAR_122,
    CHAR_123,
    CHAR_124,
    CHAR_125,
    CHAR_126,
    CHAR_127,
    CHAR_128,
    CHAR_129,
    CHAR_130,
    CHAR_131,
    CHAR_132,
    CHAR_133,
    CHAR_134,
    CHAR_135,
    CHAR_136,
    CHAR_137,
    CHAR_138,
    CHAR_139,
    CHAR_140,
    CHAR_141,
    CHAR_142,
    CHAR_143,
    CHAR_144,
    CHAR_145,
    CHAR_146,
    CHAR_147,
    CHAR_148,
    CHAR_149,
    CHAR_150,
    CHAR_151,
    CHAR_152,
    CHAR_153,
    CHAR_154,
    CHAR_155,
    CHAR_156,
    CHAR_157,
    CHAR_158,
    CHAR_159,
    CHAR_160,
    CHAR_161,
    CHAR_162,
    CHAR_163,
    CHAR_164,
    CHAR_165,
    CHAR_166,
    CHAR_167,
    CHAR_168,
    CHAR_169,
    CHAR_170,
    CHAR_171,
    CHAR_172,
    CHAR_173,
    CHAR_174,
    CHAR_175,
    CHAR_176,
    CHAR_177,
    CHAR_178,
    CHAR_179,
    CHAR_180,
    CHAR_181,
    CHAR_182,
    CHAR_183,
    CHAR_184,
    CHAR_185,
    CHAR_186,
    CHAR_187,
    CHAR_188,
    CHAR_189,
    CHAR_190,
    CHAR_191,
    CHAR_192,
    CHAR_193,
    CHAR_194,
    CHAR_195,
    CHAR_196,
    CHAR_197,
    CHAR_198,
    CHAR_199,
    CHAR_200,
    CHAR_201,
    CHAR_202,
    CHAR_203,
    CHAR_204,
    CHAR_205,
    CHAR_206,
    CHAR_207,
    CHAR_208,
    CHAR_209,
    CHAR_210,
    CHAR_211,
    CHAR_212,
    CHAR_213,
    CHAR_214,
    CHAR_215,
    CHAR_216,
    CHAR_217,
    CHAR_218,
    CHAR_219,
    CHAR_220,
    CHAR_221,
    CHAR_222,
    CHAR_223,
    CHAR_224,
    CHAR_225,
    CHAR_226,
    CHAR_227,
    CHAR_228,
    CHAR_229,
    CHAR_230,
    CHAR_231,
    CHAR_232,
    CHAR_233,
    CHAR_234,
    CHAR_235,
    CHAR_236,
    CHAR_237,
    CHAR_238,
    CHAR_239,
    CHAR_240,
    CHAR_241,
    CHAR_242,
    CHAR_243,
    CHAR_244,
    CHAR_245,
    CHAR_246,
    CHAR_247,
    CHAR_248,
    CHAR_249,
    CHAR_250,
    CHAR_251,
    CHAR_252,
    CHAR_253,
    CHAR_254,
    CHAR_255,
    // VARCHAR,
};

typedef vector<string> TUPLE;
struct _TEMP_TABLE{
    vector<ATTR> attr;
    vector<TUPLE> tuples;
};
typedef struct _TEMP_TABLE TEMP_TABLE;
typedef TEMP_TABLE SEL_RESULT;

enum PRED_OP{G, GE, E, NE, LE, L};
struct PRED{
    ATTR left;
    PRED_OP op;
    string right;
};

typedef int FILE_HANDLE;
const FILE_HANDLE NULL_FILE_HANDLE=-1;
typedef int FILE_OFFSET;
const FILE_HANDLE NULL_FILE_OFFSET=-1;

const FILE_HANDLE catalog_file_handle=0;
const FILE_HANDLE table_file_handle=1;
const FILE_HANDLE index_file_handle=2;

typedef int BLOCK_HANDLE;
const BLOCK_HANDLE NULL_BLOCK_HANDLE=-1;
typedef int BLOCK_OFFSET;
const BLOCK_OFFSET NULL_BLOCK_OFFSET=-1;

typedef int NODE_HANDLE;
const NODE_HANDLE NULL_NODE_HANDLE=-1;

// typedef int TREE_HANDLE;
// const TREE_HANDLE NULL_TREE_HANDLE=-1;

// typedef pair<FILE_HANDLE, FILE_OFFSET> BLOCK_POS;
// const BLOCK_POS NULL_BLOCK_POS=pair<FILE_HANDLE, FILE_OFFSET>(NULL_FILE_HANDLE, NULL_FILE_OFFSET);

typedef pair<BLOCK_HANDLE, BLOCK_OFFSET> TUPLE_POS;
const TUPLE_POS NULL_TUPLE_POS=pair<BLOCK_HANDLE, BLOCK_OFFSET>(NULL_BLOCK_HANDLE, NULL_BLOCK_OFFSET);

typedef pair<BLOCK_HANDLE, BLOCK_OFFSET> NODE_POS;
const NODE_POS NULL_NODE_POS=pair<BLOCK_HANDLE, BLOCK_OFFSET>(NULL_BLOCK_HANDLE, NULL_BLOCK_OFFSET);

bool catalog_init();
void catalog_quit();

//metadata
string get_table_name(TABLE t);
TABLE get_table_handle(string tname);
const vector<TUPLE_POS>& get_table_tuple(TABLE t);
int get_tuple_num(TABLE t);
const vector<TUPLE_POS>& get_tuple_pos(TABLE t);
int get_tuple_size(TABLE t);
const vector<ATTR>& get_table_attr(TABLE t);
ATTR get_table_pk(TABLE t);

int size_of_type(TYPE tp);
string get_attribute_name(ATTR attr);
ATTR get_attribute_handle(TABLE t, string atname);
TYPE get_attribute_type(ATTR attr);
bool is_attr_unique(ATTR attr);
bool is_attr_notnull(ATTR attr);

string get_index_name(INDEX idx);
INDEX get_index_handle(string idx_name);
INDEX get_index_handle(TABLE t, ATTR attr);
ATTR get_index_attr(INDEX idx);
bool drop_index_catalog(INDEX idx);
TABLE get_index_table(INDEX idx);
INDEX alloc_new_index(string idx_name, TABLE t, ATTR attr, int sizeof_node);

//record
TABLE create_table(const string& tname, const vector<string>& aname, const vector<TYPE>& atype, const int& pk, const vector<bool>& unique, const vector<bool>& notnull);
bool drop_table(TABLE t);
TUPLE_POS alloc_tuple_pos(TABLE t);
bool delete_tuple(TABLE t, TUPLE_POS tpos);

//buffer
string get_block_path(BLOCK_HANDLE bh);
string get_block_path(FILE_HANDLE fh, BLOCK_HANDLE bh);
const vector<BLOCK_HANDLE>& get_last_mem_blocks();
bool store_last_mem_blocks(vector<BLOCK_HANDLE>& src);

//index
NODE_HANDLE get_tree_head_handle(INDEX idx);
NODE_POS get_node_pos(NODE_HANDLE nh);
int get_node_size(INDEX idx);
NODE_HANDLE alloc_node_handle(INDEX idx);
bool set_tree_head(INDEX idx, NODE_HANDLE nh);
bool erase_node(INDEX idx, NODE_HANDLE nh);
