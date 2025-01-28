/***************************************
* Author : Natty
* Reviewer : 
* Date : 27 / 01 / 2025
* Last update: 28 / 01 / 2025
*****************************************/

#include <assert.h> 	/* assert */
#include <stdlib.h> 	/* malloc, free */
#include "bst.h" 

#define 	NodeToIter(x)		((bst_iter_t)x)
#define		IterToNode(x)		((bst_node_t*)x)	

/****************struct and enum declaration*********************/

struct bst
{
	bst_node_t *end;
	cmp_func_t cmp_func;	
};


struct bst_node 
{
	void* data;
	struct bst_node *parent;
	struct bst_node *child[2]; /* child[0] = left, child[1] = right*/
};


/** possible return values **/
typedef enum
{
	
	SUCCESS = 0,
	OPERATION_FAIL = 1
	
}bst_result_t;

typedef enum
{
	
	FALSE = 0,
	TRUE = 1
	
}func_result_t;

typedef enum
{
	
	LEFT = 0,
	RIGHT = 1
	
}child_pose_t;

/***************End of struct and enum declaration *******/

/***********Functions declaration and definition*******/
/*static int CountNodes (void *data, void *user_param);*/

static bst_iter_t BstNodeMax(bst_node_t* node);
static bst_iter_t BstNodeBegin(bst_node_t* node);
/**********End of functions declaration and definition *******/

/********************  BstCreate  ****************************/

bst_t *BstCreate(cmp_func_t sort_func)
{
	
	bst_t bst_p* = (bst_t*)malloc(sizeof(bst_t));

	if(NULL == bst_p)
	{
		return NULL;
	}
	
	bst_p->end = (bst_node_t*)malloc(sizeof(bst_node_t));

	if(NULL == bst_p->end)
	{
		free(bst_p);
		bst_p = NULL;
		return NULL;
	}
	
	bst_p->cmp_func = sort_func;
	bst_p->end->data = bst_p;
	bst_p->end->parent = NULL;
	bst_p->end->child[LEFT] = NULL; /* left child */
	bst_p->end->child[RIGHT] = NULL; /* right child */
	
	return bst_p;
}
/********************  BstDestroy  ****************************/
/* Phases: void BstDestroy(bst_t *bst)
1. Operate BstRemove on each node post -order tree-traversal(walk).
*)	curr_node = bst->end;
*) curr_node = BstBegin ( bst )
*) curr_node_next = NULL;
*) parnt =curr_node->parent;
-- post-order tree traversal --

*)need to find the max of each subtree 
in order not to break the arriving to the root ??

first of all: curr_node is the root or dummy end
if we enter to while the first curr_node is the root
 
while (FALSE == BstIsEmpty(bst) && curr_node != end) 
 { 
 
  curr_node_next = IterToNode(BstNodeBegin(curr_node));
  parnt = curr_node_next->parent;
  child2 = curr_node_next->right_child;
  
    
  if( end == parnt )
  {
  	curr_node = (parnt->left_child)->right_child;
  	continoue;
  }	NEED TO CONTINOUE!! NOT COMPLETED!!
  free(curr_node);
  (parnt->left_child)-> NULL;
  if(NULL != child2) )
  {
  	curr_node = child2;
  }

  
  
  
  
 }
 
 free(curr_node) 
 free(bst)

{ A, B  C, D, E, F, G, H, I, end}
{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
*/

void BstDestroy(bst_t *bst)
{
	
}

/*
static int SortingFunc(void* check_data , void* new_data)
{
	return (*(int*)check_data - *(int*)new_data);
}

if check_data > new_data go to left child
if check_data < new_data go to right child
*/
/********************  BstInsert  ****************************/


bst_iter_t BstInsert(bst_t *bst, const void *new_data)
{
	bst_node_t *new_node = NULL, *parnt = NULL, *curr_node = NULL;
	int res = 0;
	
	assert(bst);
	
	new_node =  (bst_node_t*)malloc(sizeof(bst_node_t));
	
	if(NULL == new_node)
	{
		return NULL;
	}
	
	new_node->data = new_data;
	
	if( TRUE == BstIsEmpty(bst) )
	{
		new_node->parent = bst->end;

		new_node->child[LEFT] = NULL;
		new_node->child[RIGHT] = NULL;
		bst->end->child[LEFT] = new_node;
		 
		return NodeToIter(new_node);
	}
	
	curr_node = BstPrev(bst->end); /* get the root */
	
	while(NULL != curr_node)
	{
		res = cmp_func(curr_node->data, new_data);
		parnt  = curr_node;
		
		if( res > 0 )
		{
			curr_node  = curr_node->child[LEFT]; /* left */
		}
		
		else 
		{
			curr_node = curr_node->child[RIGHT]; /* right */
		}
	}
	
	if( res > 0 )
	{
		parnt->child[LEFT] = new_node;	
	}
	
	else
	{
		parnt->child[RIGHT] = new_node;
	}
	
	new_node->child[LEFT] = NULL;
	new_node->child[RIGHT] = NULL;	
	new_node->data = new_data;
	
	return NodeToIter(new_node);	
}


/********************  BstBegin  ****************************/
bst_iter_t BstBegin(const bst_t *bst)
{
	bst_node_t* curr_node = NULL;	
	
	assert(bst);
	assert(bst->end);
	
	curr_node = bst->end;
	
	if(TRUE == IsEmpty(bst) )
	{
		return NodeToIter(curr_node);
	}
	
	return BstNodeBegin(curr_node);		
}

/********************  BstIsEmpty  ****************************/
BstIsEmpty(const bst_t *bst)
{
	assert(bst);	
	assert(bst->end);
	
	return bst->end ? FALSE : TRUE;	
}
/********************  BstNodeBegin  ****************************/
static bst_iter_t BstNodeBegin(bst_node_t* node)
{
	bst_node_t* curr_node = NULL;
	assert(node);
	
	curr_node = node;
	
	while( NULL != curr_node->child[LEFT] )
	{
		curr_node = curr_node->child[LEFT];
	}
	
	return NodeToIter(curr_node);
}
/********************  BstNext  ****************************/
bst_iter_t BstNext(bst_iter_t iter)
{
	bst_node_t *curr_node = NULL, *parnt = NULL;
	assert( IterToNode(iter) );
	curr_node = IterToNode(iter);
	
	if(  NULL != curr_node->child[RIGHT] ) 
    {
 		return BstNodeBegin(curr_node);
	}
	
	parnt  = curr_node->parent;
	
	while(curr_node != parnt->child[LEFT] )
	{
		curr_node = parnt;
		parnt = curr_node->parent;
	}
	
	return parnt; /*if curr_node is max than return dummy end*/	
}

/********************  BstPrev  ****************************/
bst_iter_t BstPrev(bst_iter_t iter)
{
	bst_node_t *curr_node = NULL, *parnt = NULL;
	
	assert(IterToNode(iter));
	
	curr_node = NodeToIter(iter);
	
	if(NULL != curr_node->child[LEFT] )
	{
		return BstNodeMax( curr_node->child[LEFT] );
	}
	
	parnt = curr_node->parnt;
	/* if the parent is dummy end don't compare to its right child(NULL) */
	while( (NULL != parnt->parent) && (curr_node != parnt->child[RIGHT] ))
	{
		curr_node = parnt;
		parnt = curr_node->parent;
	}
	
	/*if curr_node is min than undefine, return dummy end*/
	return NodeToIter(parnt);
}

/********************  BstNodeMax  ****************************/
static bst_iter_t BstNodeMax(bst_node_t* node)
{
	assert(node);
	
	while(NULL != node->child[RIGHT])
	{
		node = node->child[RIGHT];
	}
	
	return NodeToIter(node);		
}
/********************  BstRemove  ****************************/
/* Phases: bst_iter_t BstRemove(bst_iter_t what)

bst_node_t* curr_node = IterToNode(what);
bst_node_t* curr_node_next = BstNext(what);
bst_node_t* parnt =  curr_node->parent; 
bst_node_t* child1 =  NULL;
bst_node_t* child2 =  NULL;
prepere data: using static functions that gets:
			a) find the noumber of children of a node
			b) find if the the children is left or right child
			
case 1: there are not childes to curr_node( the node is leaf):
									(The node has no children)
	
	
	if(curr_node == parnt->right_child)
	{
		parnt->right_child = NULL;
	}
	
	else
	{
		parnt->left_child = NULL;
	}
	
	free(curr_node);
	curr_node = NULL;
	
	return NodeToIter(curr_node_next);
	
	/* check if there are less then 2 childs-> handle with parant of what
			else = handle the case of 2 children */	
/*			
case 2: the node has one child: replace the node with the child

	(find(left/right) and save(addr) the child of the curr_node)
	child1 = curr_node->left/right child; 
	
	(save what child curr_node is(left/right)) using static function
	(replace the node with the child) 
	parnt-> left/right child = child;

	if(curr_node_next == parnt->right_child)
	{
		parnt->right_child = NULL;
	}
	
	else
	{
		parnt->left_child = NULL;
	}
	
	free(curr_node);
	curr_node= NULL;
	
	case 3: a) The node has two children :
				 the removal should be as below:
			  b)  We go the right child of the node,
	              and then extreme left of that child.
	              i.e: find the begin of the right subtree.
	              
	              if the node that we find has a right child
	              then:
	              b.1) put the parent of the node to point on
	              the right child of the subtree begin
	              b.2) swap the data of the node with the contender
	              		to be remove.
	              b.3) free the subtree begin node.
		
	child1 =  IterToNode(BstNodeBegin(curr_node->right_child));
	(child1 nust be left_child that has only rights childs !!)
	parnt = child1->parent;
	
	curr_node->data = child1->data; ( copy the data)
				
	if( NULL != child1->right_child )
	{
		parnt->left_child = child1->right_child;
	}
	else
	{
		parnt->left_child = NULL;
	}
	
	free(child1);
	child1 = NULL;
	
	 
*/
bst_iter_t BstRemove(bst_iter_t what)
{

}


void *BstGetData(bst_iter_t iter);











