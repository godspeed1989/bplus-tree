#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "bpt.h"
#include "bpt_util.h"
#include "bpt_find.h"
#include "bpt_insert.h"
#include "bpt_delete.h"

int main( int argc, char ** argv )
{
	int i;
	node * root = NULL;

	for(i = 0; i < 40; i++)
		root = insert(root, i, i*10);

	for(i = 0; i < 40; i+=2)
		root = delete(root, i);
	
	print_tree_file(root);
	destroy_tree(root);
	return 0;
}
