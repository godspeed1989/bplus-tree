

/* give the height of the tree, which length in number of edges */
int height( node * root )
{
	int height = 0;
	node * c = root;
	while (!c->is_leaf)
	{
		c = c->pointers[0];
		height++;
	}
	return height;
}

/* give the length in edges of the path from any node to the root */
int path_to_root( node * root, node * child )
{
	int length = 0;
	node * c = child;
	while (c != root)
	{
		c = c->parent;
		length++;
	}
	return length;
}

node * make_node( void )
{
	node * new_node;
	new_node = malloc(sizeof(node));
	assert(new_node);
	// keys: order - 1
	new_node->keys = malloc( (order - 1) * sizeof(int) );
	assert(new_node->keys);
	// pointers: order
	new_node->pointers = malloc( order * sizeof(void *) );
	assert(new_node->pointers);
	new_node->is_leaf = false;
	new_node->num_keys = 0;
	new_node->parent = NULL;
	new_node->next = NULL;
	return new_node;
}

record * make_record(int value)
{
	record * new_record = (record *)malloc(sizeof(record));
	assert (new_record);
	new_record->value = value;
	return new_record;
}

node * make_leaf( void )
{
	node * leaf = make_node();
	leaf->is_leaf = true;
	return leaf;
}


int cut( int length )
{
	if (length % 2 == 0)
		return length/2;
	else
		return length/2 + 1;
}

node * queue = NULL;

void enqueue( node * new_node ) {
	node * c;
	if (queue == NULL) {
		queue = new_node;
		queue->next = NULL;
	}
	else {
		c = queue;
		while(c->next != NULL) {
			c = c->next;
		}
		c->next = new_node;
		new_node->next = NULL;
	}
}

node * dequeue( void ) {
	node * n = queue;
	queue = queue->next;
	n->next = NULL;
	return n;
}

void print_tree_file( node * root )
{
	FILE *fp;
	time_t tim;
	struct tm *at;
	char filename[64];

	node * n = NULL;
	int i = 0;

	time(&tim);
	at = localtime(&tim);
	strftime(filename, 63, "%Y%m%d%H%M%S.dot", at);
	fp = fopen(filename, "w");
	if( fp == NULL ) {
		printf("open %s error\n", filename);
		return;
	}
	fprintf(fp, "digraph {\n");
	fprintf(fp, "graph[ordering=\"out\"];\n");
	fprintf(fp, "node[fontcolor=\"#990000\",shape=plaintext];\n");
	fprintf(fp, "edge[arrowsize=0.6,fontsize=6];\n");
	if( root == NULL ) {
		fprintf(fp, "null[shape=box]\n");
		return;
	}
	queue = NULL;
	enqueue(root);
	while ( queue != NULL ) {
		n = dequeue();
		fprintf(fp, "n%p[label=\"", n);
		for (i = 0; i < n->num_keys; i++) {
			fprintf(fp, " %d ", n->keys[i]);
		}
		fprintf(fp, "\",shape=box];\n");
		if (!n->is_leaf) {
			for (i = 0; i <= n->num_keys; i++) {
				fprintf(fp, " n%p -> n%p;\n", n, n->pointers[i]);
				enqueue(n->pointers[i]);
			}
		}
		else {
			if(n->pointers[order - 1])
				fprintf(fp, " n%p -> n%p[constraint=false];\n", n, n->pointers[order - 1]);
		}
	}
	fprintf(fp, "}\n");
	fclose(fp);
}
