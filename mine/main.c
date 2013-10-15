#include "bpt.h"
#include <stdio.h>

void print_bpt(bpt_node* node)
{
    u32 i;
    if(!node -> is_leaf) // node
    {    
        printf("n%p[shape=box,label=\"", node);
        for(i = 0; i < node->key_num; ++i)
            printf(" %d ", node->key[i]);
        printf( "\"];\n");
        // pointer[0..key_num] points to children
        for(i = 0; i <= node->key_num; ++i)
        {
            print_bpt(node->pointer[i]);
            printf(" n%p->n%p;\n", node, node->pointer[i]);
        }
    }
    else // is a leaf
    {
        printf("n%p[shape=box,label=\"", node);
        // pointer[1..key_num] points the data
        for(i = 0; i < node->key_num; ++i)
        {
            printf("%d-%d\\n", node->key[i], (u32)node->pointer[i+1]);
        }
        printf( "\"];\n");
        if(node->pointer[0])
            printf(" n%p->n%p;//sibling\n", node, node->pointer[0]);
    }
}

void dump_all()
{
    printf("digraph {\n");
    printf("graph[ordering=\"out\"];\n");
    printf("node[fontcolor=\"#990000\",shape=box];\n");
    print_bpt(root);
    printf("}\n");
}

int main()
{
    u32 i;
    initial_bpt();

    for(i = 0; i < M*10; ++i)
        insert_in_bpt(i, (void*)(i<<1));
    for(i = 0; i < M*10; i+=2)
        delete_in_bpt(i);

    dump_all();

    return 0;
}
