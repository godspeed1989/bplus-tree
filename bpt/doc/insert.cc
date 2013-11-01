// root node maybe modified
insert(root, key, value)
	if key exist
		return root
	if tree empty
		start_new_tree
	leaf = find_leaf(key)
	record = make_record(value)
	if leaf has room
		insert_into_leaf(leaf, key, record)
		return root
	else
		return insert_into_leaf_after_splitting(root, leaf, key, record)
-----------------------------------------------------------------
insert_into_leaf(leaf, key, record)
	find insertion_point
	insert <key,record> to leaf at insertion_point
	leaf->num_keys++
-----------------------------------------------------------------
// leaf must split. new_leaf will insert to parent as a node
insert_into_leaf_after_splitting(root, leaf, key, record)
	find insertion_point
	dup leaf to temp_leaf
	insert <key,record> to temp_leaf at insertion_point
	//splitting
	calculate split point
	copy lower half temp_leaf to leaf
	new_leaf = make_leaf()
	copy upper half temp_leaf to new_leaf
	adjust leaf and new_leaf sibling(pointers[order - 1])
	//insert new_leaf
	return insert_into_parent(root, leaf, new_leaf->keys[0], new_leaf)
-----------------------------------------------------------------
/*
      parent                   parent
      /               ->       /    \
 left_node  new_node     left_node  new_node
*/
insert_into_parent(root, left_node, new_node_key, new_node)
	parent = left_node->parent
	if parent = NIL
		return insert_into_new_root(left, new_node_key, new_node)
	get left_node_index
	if parent->num_keys < order - 1
		return insert_into_node(root, parent, left_node_index, new_node_key, new_node)
	return insert_into_node_after_splitting(root, parent, left_node_index, new_node_key, new_node)
-----------------------------------------------------------------
insert_into_node(root, parent, left_node_index, new_node_key, new_node)
	insert <new_node_key,new_node> to parent at left_node_index
	parent->num_keys++
	return root
-----------------------------------------------------------------
// node must split. new_node will insert to parent
// k_prime go up
insert_into_node_after_splitting(root, old_node, left_node_index, new_node_key, new_node)
	dup old_node->pointers to temp_pointers
	dup old_node->keys to temp_keys
	insert new_node to temp_pointers at left_node_index
	insert new_node_key to temp_keys at left_node_index
	//splitting
	calculate split point
	reconstruct old_node { old_node->num_keys=split-1 }
	k_prime = temp_keys[split - 1]
	new_node = make_node()
	construct new_node { set new_node->parent, child->parent }
	return insert_into_parent(root, old_node, k_prime, new_node)

