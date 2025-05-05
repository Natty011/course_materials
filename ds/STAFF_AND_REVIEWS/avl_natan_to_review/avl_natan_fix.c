/******************************************************************************
*
*	Aouther:	Natan Yunger
*	Review:		Natty Levi
*	Date:		12/02/25
*
*******************************************************************************/

#include <stdlib.h> 	/* calloc, free, size_t */
#include <assert.h> 	/* assert */

#ifndef NDEBUG
	#include<stdio.h>
#endif

#include "avl.h"

#define LEFT_OR_RIGHT(func, node, check)	(func(node->data, check) > 0) ?\
																 LEFT : RIGHT
#define MAX(a, b)							(((a) > (b)) ? (a) : (b))
#define HEIGHT(node)						((node) ? node->height : -1)
#define NEW_HEIGHT(node)					MAX(HEIGHT(node->children[LEFT]),\
											 HEIGHT(node->children[RIGHT])) + 1

typedef enum
{
	LEFT = 0,
	RIGHT = 1,
	CHILDREN
} direction_t;

typedef enum
{
	NONE = 0,
	LL = 1,
	RR = 2,
	LR = 3,
	RL = 4
} rot_t;

enum
{
	SUCCESS = 0,
	FAIL = 1
};

typedef struct avl_node
{
	void* data;
	long height;
	struct avl_node* children[CHILDREN];
}  avl_node_t;

struct avl
{
	avl_node_t* root;
	cmp_func_t cmp_func;
};

static avl_node_t* Rotate(avl_node_t* node, direction_t direction);
static rot_t WhichRotation(avl_node_t* node);
static avl_node_t* DoRotation(avl_node_t* node, rot_t rotate);
static avl_node_t* CreateNode(void* data);
static int Count(void *data, void *user_param);
static avl_node_t* LeftMost(avl_node_t* node);

#ifndef NDEBUG
void PrintSpace( size_t n );

void _PrintTree( avl_node_t* node , size_t h);

void PrintTree( avl_t* avl );
#endif

/******************************************************************************
static functions that recieve a pointer to a node, and operete on the tree 
rooted at it, recursively:													*/

static void RecSubtreeDestroy(avl_node_t* root);
static avl_node_t* RecInsertToSubtree(avl_node_t* root, avl_node_t* new_node,
									 cmp_func_t cmp_func);
static avl_node_t* RecRemoveFromSubtree(avl_node_t* root, void* data,
														 cmp_func_t cmp_func);
static void* RecFindInSubtree(avl_node_t* root, void* data, cmp_func_t cmp_func);

static int RecSubtreeForEachInOrder(avl_node_t *root, op_func_t op_func,
															 void *user_param);
static int RecSubtreeForEachPreOrder(avl_node_t *root, op_func_t op_func,
															 void *user_param);
static int RecSubtreeForEachPostOrder(avl_node_t *root, op_func_t op_func,
															 void *user_param);

/******************************************************************************/

/************************************Create************************************/
avl_t* AVLCreate(cmp_func_t cmp_func)
{
	/* create avl */
	avl_t* tree = (avl_t*)calloc(1, sizeof(avl_t));
	
	/* if allocation failed - return NULL */
	if (!tree)
	{
		return NULL;
	}
	
	tree->cmp_func = cmp_func;
	
	return tree;
}

/************************************Destroy***********************************/
void AVLDestroy(avl_t* tree)
{
	if (tree)
	{
		RecSubtreeDestroy(tree->root);
		tree->root = NULL;
		
		free(tree);
		tree = NULL;
	}
}

static void RecSubtreeDestroy(avl_node_t* root)
{
	/* stop condition */
	if (NULL == root)
	{
		return;
	}
	
	/* destroy left subtree */
	RecSubtreeDestroy(root->children[LEFT]);
	root->children[LEFT] = NULL;
	
	/* destroy right subtree */
	RecSubtreeDestroy(root->children[RIGHT]);
	root->children[RIGHT] = NULL;
	
	free(root);
	root = NULL;
}

/************************************Insert************************************/
int AVLInsert(avl_t* tree, void* data)
{	
	/* create new node */
	avl_node_t* new_node = CreateNode(data);
	
	assert(tree);
	
	/* if allocation failed - return 1 */
	if (!new_node)
	{
		return FAIL;
	}
	
	tree->root = RecInsertToSubtree(tree->root, new_node, tree->cmp_func);
	return SUCCESS;
}
static avl_node_t* RecInsertToSubtree(avl_node_t* root, avl_node_t* new_node,
															 cmp_func_t cmp_func)
{
	direction_t direction = LEFT;		/* 'LEFT' is 0 */
	rot_t rotate = NONE;
	
	/* stop condition */
	if (!root)
	{
		root = new_node;
		return root;
	}
	
	direction = LEFT_OR_RIGHT(cmp_func, root, new_node->data);
	root->children[direction] =
				 RecInsertToSubtree(root->children[direction], new_node, cmp_func);
	
	rotate = WhichRotation(root);
	return DoRotation(root, rotate);
}

/************************************Remove************************************/
void AVLRemove(avl_t *tree, void *data)
{
	assert(tree);
	tree->root = RecRemoveFromSubtree(tree->root, data, tree->cmp_func);
}

static avl_node_t* RecRemoveFromSubtree(avl_node_t* root, void* data,
														 cmp_func_t cmp_func)
{
	direction_t direction = LEFT;		/* 'LEFT' is 0 */
	rot_t rotate = NONE;
	
	avl_node_t* child = NULL;
	avl_node_t* next = NULL;
	
	if (NULL == root)
	{
		return root;
	}
	
	if (0 == cmp_func(root->data, data))
	{
		/* if root has less then two children */
		if (!(root->children[LEFT] && root->children[RIGHT]))
		{
			child = root->children[LEFT] ? root->children[LEFT] :
														 root->children[RIGHT];
			free(root);
			root = NULL;
			return child;
		}
		
		/* if root has two children */
		next = LeftMost(root->children[RIGHT]);
		root->data = next->data;
		next->data = data;
		root->children[RIGHT] =
			 RecRemoveFromSubtree(root->children[RIGHT], (void*)data, cmp_func);
/*		return root;*/
		rotate = WhichRotation(root);
		return DoRotation(root, rotate);
	}
	
	direction = LEFT_OR_RIGHT(cmp_func, root, data);
	child = RecRemoveFromSubtree(root->children[direction], (void*)data, cmp_func);
	
	root->children[direction] = child;
	
	rotate = WhichRotation(root);
	return DoRotation(root, rotate);
}

/******************************* small functions ******************************/
size_t AVLHeight(const avl_t* tree)
{
	assert(tree);
	return tree->root ? tree->root->height : 0;
}

size_t AVLSize(const avl_t* tree)
{
	/* ForEach(static counting function) */
	size_t counter = 0;
	assert(tree);
	
	AVLForEach((avl_t*)tree, Count, &counter, PRE_ORDER);
	return counter;
}

int AVLIsEmpty(const avl_t* tree)
{
	assert(tree);
	return NULL == tree->root;
}

/*************************************Find*************************************/
void* AVLFind(avl_t* tree, const void* data)
{
	cmp_func_t cmp_func = NULL;
	
	assert(tree);
	
	cmp_func = tree->cmp_func;
	return RecFindInSubtree(tree->root, (void*)data, cmp_func);
}

static void* RecFindInSubtree(avl_node_t* root, void* data, cmp_func_t cmp_func)
{
	direction_t direction = LEFT;		/* 'LEFT' is 0 */
	
	/* stop condition 1 */
	if (NULL == root)
	{
		return NULL;
	}
	
	/* stop condition 2 */
	if (0 == cmp_func(root->data, data))
	{
		return root->data;
	}
	
	direction = LEFT_OR_RIGHT(cmp_func, root, data);
	return RecFindInSubtree(root->children[direction], (void*)data, cmp_func);
}

/***********************************ForEach************************************/
int AVLForEach(avl_t *tree, op_func_t op_func, void *user_param,
															 int traversal_order)
{
	assert(tree);
	assert(op_func);
	
	if (tree->root)
	{
		switch (traversal_order)
		{
			case IN_ORDER:		/* left subtree --> node --> right subtree */
				return RecSubtreeForEachInOrder(tree->root, op_func, user_param);
			
			case PRE_ORDER:		/* node --> left subtree --> right subtree */
				return RecSubtreeForEachPreOrder(tree->root, op_func, user_param);
			
			case POST_ORDER:	/* left subtree --> right subtree --> node */
				return RecSubtreeForEachPostOrder(tree->root, op_func, user_param);
		}
	}
	
	return SUCCESS;
}

static int RecSubtreeForEachInOrder(avl_node_t* root, op_func_t op_func,
															 void* user_param)
{
	int res = SUCCESS;

	/* ForEach(left subtree) */
	if (!res && root->children[LEFT])
	{
		res = RecSubtreeForEachInOrder(root->children[LEFT], op_func, user_param);
	}
	
	/* op_func(node) */
	if (!res)
	{
		res = op_func(root->data, user_param);
	}
	
	/* ForEach(right subtree) */
	if (!res && root->children[RIGHT])
	{
		res = RecSubtreeForEachInOrder(root->children[RIGHT], op_func, user_param);
	}
	
	return res;
}

static int RecSubtreeForEachPreOrder(avl_node_t* root, op_func_t op_func,
															 void* user_param)
{
	int res = SUCCESS;
	
	/* op_func(node) */
	if (!res)
	{
		res = op_func(root->data, user_param);
	}
	
	/* ForEach(left subtree) */
	if (!res && root->children[LEFT])
	{
		res = RecSubtreeForEachPreOrder(root->children[LEFT], op_func, user_param);
	}
	
	/* ForEach(right subtree) */
	if (!res && root->children[RIGHT])
	{
		res = RecSubtreeForEachPreOrder(root->children[RIGHT], op_func, user_param);
	}
	
	return res;
}

static int RecSubtreeForEachPostOrder(avl_node_t* root, op_func_t op_func,
															 void* user_param)
{
	int res = SUCCESS;
	
	/* ForEach(left subtree) */
	if (!res && root->children[LEFT])
	{
		res = RecSubtreeForEachPostOrder(root->children[LEFT], op_func, user_param);
	}
	
	/* ForEach(right subtree) */
	if (!res && root->children[RIGHT])
	{
		res = RecSubtreeForEachPostOrder(root->children[RIGHT], op_func, user_param);
	}
	
	/* op_func(node) */
	if (!res)
	{
		res = op_func(root->data, user_param);
	}
	
	return res;
}

/*************************** other static functions ***************************/

static avl_node_t* CreateNode(void* data)
{
	/* create new node */
	avl_node_t* node = (avl_node_t*)calloc(1, sizeof(avl_node_t));
	
	/* if allocation failed - return 1 */
	if (!node)
	{
		return NULL;
	}
	
	/* initialize node */
	node->data = data;
	
	return node;
}

static int Count(void *data, void *user_param)
{
	(void)data;
	++*(size_t*)user_param;
	
	return SUCCESS;
}

static avl_node_t* LeftMost(avl_node_t* node)
{
	if (!node->children[LEFT])
	{
		return node;
	}
	
	return LeftMost(node->children[LEFT]);
}

static avl_node_t* DoRotation(avl_node_t* node, rot_t rotate)
{
	switch (rotate)
	{
		case NONE:
			node->height = NEW_HEIGHT(node);
			return node;
		
		case LL:
			return Rotate(node, LEFT);
		
		case RR:
			return Rotate(node, RIGHT);
		
		case LR:
			node->children[LEFT] = Rotate(node->children[LEFT], LEFT);
			return Rotate(node, RIGHT);
		
		case RL:
			node->children[RIGHT] = Rotate(node->children[RIGHT], RIGHT);
			return Rotate(node, LEFT);
	}
	return NULL;
}

static avl_node_t* Rotate(avl_node_t* node, direction_t direction)
{
	avl_node_t* new_node = node->children[!direction];
	avl_node_t* temp = new_node->children[direction];
	
	new_node->children[direction] = node;
	node->children[!direction] = temp;
	node->height = NEW_HEIGHT(node);
	new_node->height = NEW_HEIGHT(new_node);
	return new_node;
}

static rot_t WhichRotation(avl_node_t* node)
{
	int diff = HEIGHT(node->children[LEFT]) - HEIGHT(node->children[RIGHT]);
	
	if ((diff <= 1) && (diff >= -1))
	{
		return NONE;
	}
	
	if (diff < -1)
	{
		if (HEIGHT(node->children[RIGHT]->children[LEFT]) <
								 HEIGHT(node->children[RIGHT]->children[RIGHT]))
		{
			return LL;
		}
		
		else
		{
			return RL;
		}
	}
	
	else	/* if (diff > 1) */
	{
		if (HEIGHT(node->children[LEFT]->children[RIGHT]) <
								 HEIGHT(node->children[LEFT]->children[LEFT]))
		{
			return RR;
		}
		
		else
		{
			return LR;
		}
	}
}

/***************************** printing functions *****************************/
#ifndef NDEBUG
void PrintSpace( size_t n )
{
	size_t i = 0;
	for ( i = 0; i < n ; ++i )
	{
		putchar(' ');
	}
} 

void _PrintTree( avl_node_t* node , size_t h)
{
	if ( NULL == node )
	{
		return;
	}
	_PrintTree( node->children[RIGHT] , h +1);
	PrintSpace( 4*h );
	printf("%d\n" , *(int*)node->data );
	_PrintTree( node->children[LEFT] , h +1  );
}

void PrintTree( avl_t* avl )
{
	_PrintTree( avl->root, AVLHeight(avl) );
}
#endif
















