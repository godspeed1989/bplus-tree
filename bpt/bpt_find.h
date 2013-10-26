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
