#ifndef __GP__BPT__
#define __GP__BPT__


#include <string.h>


#define M  8

/*
struct data_node
{
    int key ;
    char *value ;
    void *next ;
} ;
*/

typedef unsigned char u8;
typedef unsigned int  u32;

typedef struct _bpt_node
{
    u8      is_leaf;
    u8      is_root;
    u32     key_num;    // num of children
    u32     key[ M ];
    // if this is a leaf, pointer[] is the data
    // if this is a node, pointer[] points to children
    void    * pointer[ M + 1 ];
    struct  _bpt_node * father;
}bpt_node;

#define EXPORT
#define bpt_get_value(node)   (node->pointer[0])

extern bpt_node * root;
extern u32 node_count;
extern u32 splite_count;

extern void initial_bpt();

extern u8 insert_in_bpt( u32 key , void *value );
extern u8 delete_in_bpt( u32 key );

extern void *query_in_bpt( u32 key );

#endif
