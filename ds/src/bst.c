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

typedef enum
{
	
	NO_CHILDS = 0,
	ONE_CHILD = 1,
	TWO_CHILDS = 2
	
}nume_of_childs_t;

/***************End of struct and enum declaration *******/

/***********Functions declaration*******/
/*static int CountNodes (void *data, void *user_param);*/

static bst_iter_t BstNodeMax(bst_node_t* node);
static bst_iter_t BstNodeBegin(bst_node_t* node);
static int FindNumChilds(bst_node_t* node);
static int IsChildExist(bst_node_t* node, int child_pos);
static IsLeftChild(bst_node_t* parnt, bst_node_t* child);
static IsRightChild(bst_node_t* parnt, bst_node_t* child);
/**********End of functions declaration *******/

/***********Static Functions definition*******/

/********************  IsLeftChild  ****************************/
static IsLeftChild(bst_node_t* parnt, bst_node_t* child)
{
	assert(parnt);
	assert(child);
	return Child == parnt->child[LEFT];
	
}
/********************  IsRihtChild  ****************************/
static IsRihtChild(bst_node_t* parnt, bst_node_t* child)
{
	assert(parnt);
	assert(child);
	return Child == parnt->child[RIGHT];
}
/********************  FindNumChilds  ****************************/
static int FindNumChilds(bst_node_t* node)
{
	assert(node);
	return IsChildExist(node, LEFT) + IsChildExist(node, RIGHT);

}
/********************  IsChildExist  ****************************/
static int IsChildExist(bst_node_t* node, int child_pos)
{
	assert(node);
	return  LEFT == child_pos ? NULL != node->child[LEFT] :
								NULL != node->child[RIGHT]; 
}

/***********End Of Static Functions definition*******/

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
	new_node->parent = parnt;	
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
	
bst_iter_t BstRemove(bst_iter_t what)
{
	bst_node_t *curr_node = NULL, *parnt = NULL, 
			 *curr_node_next = NULL, *l_child = NULL;
	
	assert(IterToNode(what));
	
	parnt = curr_node->parent;
	assert( parnt ); /* check if curr_node is a dummy end */
	curr_node_next = BstNext(what);
	
	/* case 1: The node has no childs */
	
	if( NO_CHILDS == FindNumChilds(curr_node) )
	{
		IsLeftChild(parnt, curr_node) ? parnt->child[LEFT] = NULL:
										parnt->child[RIGHT] = NULL;
										
		free(curr_node);
		curr_node = NULL;
		
		return NodeToIter(curr_node_next);
	
	}
	
	/* case 2: the node has one child:
				 replace the node with the child */
	if( ONE_CHILD == FindNumChilds(curr_node ) )
	{
	
		if( IsChildExist(curr_node, LEFT) )
		{
			IsLeftChild(parnt, curr_node) ?
							 parnt->child[LEFT] = curr_node->child[LEFT]:
							 parnt->child[RIGHT] = curr_node->child[LEFT];
		}
		else
		{
			IsLeftChild(parnt, curr_node) ?
							 parnt->child[LEFT] = curr_node->child[RIGHT]:
							 parnt->child[RIGHT] = curr_node->child[RIGHT];	
		}
		
		 
		free(curr_node);
		curr_node = NULL;
		
		return NodeToIter(curr_node_next);
	}
	
	/* case 3: The node has two children:  */
	
	if(  TWO_CHILDS == FindNumChilds(curr_node ) )
	{
		l_child =  IterToNode(BstNodeBegin(curr_node->child[RIGHT]));
		parnt = l_child->parent;
		curr_node->data = l_child->data;
		
		/* l_child must be left_child that has only rights childs */
		if(	IsChildExist(l_child, RIGHT) )
		{
			parnt->child[LEFT] = l_child->child[RIGHT];
			
		}
		
		else
		{
			parnt->child[LEFT] = NULL;
		}
		
		free( l_child );
		l_child = NULL;
		
		return NodeToIter(curr_node);
	}
	
}		
/********************  BstGetData  ****************************/
void *BstGetData(bst_iter_t iter)
{
	assert( IterToNode(iter) );
	assert( NULL == IterToNode(iter)->parent ); /* check if dummy*/
	
	return IterToNode(iter)->data;
}

int is_same_iter(bst_iter_t iter1, bst_iter_t iter2)
{
	assert( IterToNode(iter1) );
	assert( IterToNode(iter2) );
	
	return IterToNode(iter1) == IterToNode(iter2) ;
}











