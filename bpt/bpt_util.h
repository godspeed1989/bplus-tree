

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

/* Traces the path from the root to a leaf, searching by key.
 * Returns the leaf containing the given key.
 */
node * find_leaf( node * root, int key )
{
	int i = 0;
	node * c = root;
	if (c == NULL)
	return c;
	while (!c->is_leaf)
	{
		i = 0;
		while (i < c->num_keys)
		{
			if (key < c->keys[i])
			break;
			i++;
		}
		c = (node *)c->pointers[i];
	}
	return c;
}

/* Finds and returns the record to which a key refers. */
record * find( node * root, int key )
{
	int i = 0;
	node * c = find_leaf( root, key );
	if (c == NULL) return NULL;
	for (i = 0; i < c->num_keys; i++)
	if (c->keys[i] == key)
	{
		return (record *)c->pointers[i];
	}
	return NULL;
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

int cut( int length )
{
	if (length % 2 == 0)
		return length/2;
	else
		return length/2 + 1;
}
