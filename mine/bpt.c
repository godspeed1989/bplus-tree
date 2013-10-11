
#include "bpt.h"
#include <stdlib.h>
#include <stdio.h>

bpt_node * root;

u32 node_count;
u32 splite_count ;

static bpt_node *new_bpt_node()
{
    node_count ++ ;

    bpt_node *p = (bpt_node *)malloc(sizeof(bpt_node));
    p -> is_leaf = 0;
    p -> is_root = 0;
    p -> key_num = 0;
    p -> pointer[ 0 ] = NULL;
    p -> father = NULL;
    return p ;
}

EXPORT
void initial_bpt()
{
    root = new_bpt_node();
    root -> is_root = 1;
    root -> is_leaf = 1;
    node_count = 0;
    splite_count = 0;
}

static bpt_node * find_leaf( u32 key )
{
    u32 i;
    bpt_node *node = root;
    while ( !node -> is_leaf )
    {
        for ( i = 0 ; i <= node -> key_num ; ++ i )
        {
            if( i == node -> key_num || key < node -> key[ i ] )
            {
                node = ( bpt_node *) node -> pointer[ i ];
                break;
            }
        }
    }
    return node;
}

static void insert_in_node( bpt_node *node , u32 key , void *value );

static void split( bpt_node *node )
{
    splite_count ++ ;
    bpt_node *nodd = new_bpt_node() ;
    u32 i, mid_key = node -> key[ M / 2 ] ;

    nodd -> key_num = M - M / 2 - 1 ;
    for ( i = 0 ; i < nodd -> key_num ; i ++ )
    {
        nodd -> key[ i ] = node -> key[ i + ( M / 2 + 1 ) ] ;
        nodd -> pointer[ i ] = node -> pointer[ i + ( M / 2 + 1 ) ] ;
    }
    nodd -> pointer[ nodd -> key_num ] = node -> pointer[ M ] ;
    node -> key_num = M / 2 ;

    if ( node -> is_leaf )
    {
        node -> key_num ++ ;
        nodd -> pointer[ 0 ] = node -> pointer[ 0 ] ;
        node -> pointer[ 0 ] = nodd ;
        nodd -> is_leaf = 1 ;
        mid_key = node -> key[ M / 2 + 1 ] ;
    }

    if ( node -> is_root )
    {
        node -> is_root = 0 ;
        root = new_bpt_node() ;
        root -> is_root = 1 ;
        root -> key[ 0 ] = mid_key ;
        root -> pointer[ 0 ] = node ;
        root -> pointer[ 1 ] = nodd ;
        root -> key_num = 1 ;

        node -> father = nodd -> father = root ;
    }
    else
    {
        nodd -> father = node -> father ;
        insert_in_node( ( bpt_node * ) node -> father , mid_key , ( void *) nodd ) ;
    }
}

static void insert_in_node( bpt_node *node , u32 key , void *value )
{
    u32 i, x = 0;
    // find insert position
    while ( x < node -> key_num && node -> key[ x ] < key )
        ++ x;
    // get the key space
    for ( i = node -> key_num ; i > x ; -- i )
        node -> key[ i ] = node -> key[ i - 1 ];
    // get the pointer space
    for ( i = node -> key_num + 1 ; i > x + 1 ; -- i )
        node -> pointer[ i ] = node -> pointer[ i - 1 ];

    node -> key[ x ] = key;
    node -> pointer[ x + 1 ] = value;
    node -> key_num ++;

    if ( node -> key_num == M ) // need to split
        split( node ) ;
}

static void delete_in_node( bpt_node *node , u32 key, u32 x)
{
    u32 i;
    //TODO: free node -> pointer[ x ]
    // recycle the key space
    for ( i = x ; i < node -> key_num - 1 ; ++ i )
        node -> key[ i ] = node -> key[ i + 1 ];
    // recycle the pointer space
    for ( i = x ; i < node -> key_num ; ++ i )
        node -> pointer[ i ] = node -> pointer[ i + 1 ];
    node -> key_num --;
    //TODO: rebalance tree, make sure each leaf at least have M/2 dats
}

#define if_key_existed(key) \
        bpt_node *leaf = find_leaf( key );          \
        u32 i;                                      \
        for ( i = 0 ; i < leaf -> key_num ; ++i )   \
            if ( key == leaf -> key[ i ] )

EXPORT
u8 insert_in_bpt( u32 key , void *value )
{
    if_key_existed(key)
    {
        fprintf(stderr, "key %d existed\n", key);
        return 1;
    }
    insert_in_node( leaf , key , value );
    return 0;
}

EXPORT
u8 delete_in_bpt( u32 key )
{
    if_key_existed(key)
    {
        delete_in_node( leaf , key, i );
        return 0;
    }
    fprintf(stderr, "key %d doesn't exist\n", key);
    return 1;
}

EXPORT
void *query_in_bpt( u32 key )
{
    if_key_existed(key)
    {
        return leaf -> pointer[i + 1];
    }
    return NULL ;
}

