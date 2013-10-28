
#define order 8

#define true  1
#define false 0
#define bool  int

typedef struct node
{
	// node: array of nodes corresponding to keys
	// leaf: with a maximum of order-1 key-pointer
	//       The last pointer points to the leaf to the right
	void ** pointers;
	int * keys;
	struct node * parent;
	bool is_leaf;
	int num_keys;
	struct node * next; // Used for queue.
} node;

typedef struct record
{
	int value;
} record;

