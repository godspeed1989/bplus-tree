// root node maybe modified
delete(root, key)
	record = find(root, key)
	leaf = find_leaf(root, key)
	if record not NIL and leaf not NILL
		root = delete_entry(root, leaf, key, record)
		free recode
	return root
-----------------------------------------------------------------
delete_entry(root, node, key, pointer)
	node = remove_entry_from_node(node, key, pointer)
	if node is root
		return adjust_root(root)
	// Determine minimum allowable size of node
	min_keys = n->is_leaf ? cut(order - 1) : cut(order) - 1;
	if node->num_keys >= min_keys
		return root
	// node falls below minimum
	// find appropriate neighbor node with which to coalesce
	neighbor_index = get_left_neighbor_index(node)
	// find key in parent between node and neighbor
	k_prime_index = (neighbor_index == -1) ? 0 : neighbor_index;
	k_prime = node->parent->keys[k_prime_index]
	neighbor = (neighbor_index == -1) ? node->parent->pointers[1] : 
		node->parent->pointers[neighbor_index]

	capacity = n->is_leaf ? order : order - 1
	// merge when entries lower capacity 
	if neighbor->num_keys + node->num_keys < capacity
		return coalesce_nodes(root, node, neighbor, neighbor_index, k_prime)
	else
		return redistribute_nodes(root, node, neighbor, neighbor_index, k_prime_index, k_prime)
-----------------------------------------------------------------
// remove a <key, pointer> pair
remove_entry_from_node(node, key, pointer)
	find and remove the key
	find , free and remove the pointer
	node->num_keys--
	set unused pointers to NULL
-----------------------------------------------------------------
// find nearest neighbor to the left, return -l for leftmost
get_left_neighbor_index(node)
	parent = node->parent
	find where parent->pointer[i] == node
	return (i - 1)
-----------------------------------------------------------------
adjust_root(root)
	if root->num_keys > 0
		return root
	// If it has a child, promote the first (only) child as new root
	if !root->is_leaf
		new_root = root->pointers[0];
		new_root->parent = NULL;
	else
		new_root = NULL
	return new_root
-----------------------------------------------------------------
// merge the node with left neighbor
// neighbor->num_keys + node->num_keys < capacity
coalesce_nodes(root, node, neighbor, neighbor_index, k_prime)
	// neighbor at left of node
	if neighbor_index == -1
		swap(neighbor, node)
	/*      parent
	        /    \
	   neighbor   node     */
	neighbor_insertion_index = neighbor->num_keys
	split = false
	// not a leaf
	if !node->is_leaf
		neighbor->keys[neighbor_insertion_index] = k_prime
		neighbor->num_keys++
		n_end = node->num_keys
		// neighbor cannot fit in all node
		if node->num_keys + neighbor->num_keys >= order
			split = true
			n_end = cut(order) - 2
		n_start = 0
		// from node to neighbor
		for i=neighbor_insertion_index+1,j=0; j < n_end; i++,j++
			neighbor->keys[i] = node->keys[j]
			neighbor->pointers[i] = node->pointers[j]
			neighbor->num_keys++
			node->num_keys--
			n_start++
		// pointers always one more than keys
		neighbor->pointers[i] = node->pointers[j]
		if split
			new_k_prime = node->keys[n_start]
			for i=0,j=n_start+1; i<node->num_keys; i++,j++
				node->keys[i] = node->keys[j]
				node->pointer[i] = node->pointers[j]
			node->pointers[i] = node->pointers[j]
			node->num_keys--
		for i=0; i < neighbor->num_keys+1; i++
			neighbor->pointers[i]->parent = neighbor
	// is a leaf
	else
		for i=neighbor_insertion_index,j=0; j<node->num_keys; i++,j++
			neighbor->keys[i] = node->keys[j]
			neighbor->pointers[i] = node->pointers[j]
			neighbor->num_keys++
		// sibling
		neighbor->pointers[order-1] = node->pointers[order-1]
	if !split
		root = delete_entry(root, node->parent, k_prime, node)
		free node content
	else
		for i=0; i<node->parent->num_keys; i++
			if node->parent->pointers[i+1] == node
				node->parent->keys[i] = new_k_prime;
	return root
-----------------------------------------------------------------
// redistribute entries node and neighbor
// neighbor->num_keys + node->num_keys >= capacity
redistribute_nodes(root, node, neighbor, neighbor_index, k_prime_index, k_prime)
	// node has left neighbor
	if neighbor_index != -1
		// make space at node left end
		if !node->is_leaf
			node->pointers[node->num_keys+1] = node->pointers[node->num_keys]
		for i=node->num_keys; i>0; i--
			node->keys[i] = node->keys[i-1]
			node->pointers[i] = node->pointers[i-1]
		// pull left neighbor last key-pointer pair to node left end
		if !node->is_leaf
			node->pointers[0] = neighbor->pointers[neighbor->num_keys]
			node->pointers[0]->parent = node
			neighbor->pointers[neighbor->num_keys] = NULL
			node->keys[0] = k_prime //node->parent->keys[k_prime_index]
			node->parent->keys[k_prime_index] = neighbor->keys[neighbor->num_keys - 1]
		else
			node->pointers[0] = neighbor->pointers[neighbor->num_keys - 1]
			neighbor->pointers[neighbor->num_keys-1] = NULL
			node->keys[0] = neighbor->keys[neighbor->num_keys-1]
			node->parent->keys[k_prime_index] = node->keys[0]
	// node is leftmost child, neighbor is the right neighbor
	else
		// move neighbor's leftmost key-pointer pair to node rightmost
		if node->is_leaf
			node->keys[node->num_keys] = neighbor->keys[0]
			node->pointers[node->num_keys] = neighbor->pointers[0]
			node->parent->keys[k_prime_index] = neighbor->keys[1];
		else
			node->keys[node->num_keys] = k_prime //node->parent->keys[k_prime_index]
			node->pointers[node->num_keys+1] = neighbor->pointers[0]
			node->pointers[node->num_keys+1]->parent = node
			node->parent->keys[k_prime_index] = neighbor->keys[0]
		for i=0; i < neighbor->num_keys; i++
			neighbor->keys[i] = neighbor->keys[i + 1]
			neighbor->pointers[i] = neighbor->pointers[i+1]
		if !node->is_leaf
			neighbor->pointers[i] = neighbor->pointers[i + 1]
	// node has one more key and pointer, heighbor has one fewer
	node->num_keys++
	neighbor->num_keys--
	return root

