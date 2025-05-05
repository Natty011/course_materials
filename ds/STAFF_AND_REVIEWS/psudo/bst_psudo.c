/***************************************
* Author : Natty
* Reviewer : 
* Date : 27 / 01 / 2025
* Last update: 27 / 01 / 2025
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

/***************End of struct and enum declaration *******/

/***********Functions declaration and definition*******/
static int CountNodes (void *data, void *user_param);
/**********End of functions declaration and definition *******/

/********************  BstCreate  ****************************/
/* Phases: bst_t *BstCreate(cmp_func_t )
1. Allocate dinnamiclly bst struct( bst_p), check if succedded.
2. allocated dinnamically dummy end node, check if succedded.
3. initialized the members of the struct:
 *) end->data = bst_p; end->parent = NULL(prev);  end->child[i] = NULL;
 	
 *)cmp_func ->data = sort_func
4. return the pointer to the allocatad struct ( bst_p). 

*/
bst_t *BstCreate(cmp_func_t )
{

}
/********************  BstDestroy  ****************************/
/* Phases: void BstDestroy(bst_t *bst)
1. Operate BstRemove on each node in -order tree-traversal(walk).
*) curr_node = BstBegin ( bst )
*) curr_node_next = NULL
-- in-order tree traversal --
while (curr_node != end) 
 {
  curr_node_next = BstBegin(curr_node);
  free(curr_node);
  curr_node = curr_node_next;
  
 }
 
 free(current_node) 
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
/* Phases: bst_iter_t BstInsert(bst_t *bst, const void *new_data)
1.
  bst_node_t new_node = NULL, parant = NULL;
  int res = 0;

2.  allocate new_node and check if succeeded, initialize his members:	
	new_node =  (bst_node_t*)malloc(sizeof(bst_node_t));
	
*) if  (TRUE == IsEmpty(bst)) end->left_child = new_node;
{
	new_node->parent = end;
	new_node->data = new_data;
	return new_node;
}

*) get the root node:  curr_node = BstPrev( end );

while(NULL != curr_node)
{
	res = cmp_func( curr_node->data, new_data);
	
	if
  		res > 0 then

  			parant = curr_node ;
  			curr_node = curr_node->left_child;
  			 
  	else
  		   	parant = curr_node ;
  			curr_node = curr_node->right_child;
	
} 

3. 
	
	if(res > 0)     
		parent->left_child = new_node;
		new_node->data = new_data;

		
	else 			
		parent->right_child = new_node;
		new_node->data = new_data;


4. new_node->child = {NULL, NULL}
5. return new_node;
		
*/

bst_iter_t BstInsert(bst_t *bst, const void *new_data)
{

}


/********************  BstBegin  ****************************/
/* Phases:bst_iter_t BstBegin(const bst_t *bst)
{
1. 
	bst_node_t* curr_node = NULL;
		
*) assert(node); assert(bst);		
*) curr_node = bst->end;
*) assert(curr_node);

if(TRUE == IsEmpty(bst) )
	{
		return NodeToIter(curr_node);
	}
	
2. return BstNodeBegin(curr_node);
	
}
*/

bst_iter_t BstBegin(const bst_t *bst)
{
	
		
}



/********************  BstIsEmpty  ****************************/
/* Phases: int BstIsEmpty(const bst_t *bst)
1. 
	bst_node_t* curr_node = NULL;
		
*)  assert(bst);		
*) curr_node = bst->end;
*) assert(curr_node);

if(NULL == curr_node->left_child )
	{
		return FALSE;
	}
	
2. return TRUE;
	
*/
BstIsEmpty(const bst_t *bst)
{


}
/********************  BstNodeBegin  ****************************/
/* Phases:bst_iter_t BstNodeBegin(bst_node_t* node)
1. 
	
*)start from the root
*)get left_child until arrive to null, return that child(minimum).
assert(node);
bst_node_t* curr_node = node;

while( NULL != curr_node->left_child)
{
	curr_node = curr_node->left_child;
}

	return NodeToIter(curr_node);
*/
static bst_iter_t BstNodeBegin(bst_node_t* node)
{
	
	

}

/********************  BstNext  ****************************/
/* Phases:bst_iter_t BstNext(bst_iter_t iter)
case 1: there is a right child to the iter->
	 return the  BstNodeBegin(right_child):
	 
*)	bst_node_t* curr_node = NULL, mother = NULL;
*)  assert(iter);
*) mother  = curr_node-> parent;

*)    curr_node = NodeToIter(iter);

    if(  NULL != curr_node->right_child ) 
    {
 		return BstNodeBegin(curr_node);
	}
	
case 2: there is a no right child to the iter:	
	
		while(curr_node  != mother->left_child)
		{
			curr_node = mother ; 
			mother = curr_node->parent;	
		}

		return mother; /*if curr_node is max than return dummy end*/

*/

bst_iter_t BstNext(bst_iter_t iter)
{

}

/********************  BstPrev  ****************************/
/* Phases:bst_iter_t BstPrev(bst_iter_t iter)
case 1: there is a left child to the iter->

	  return the  BstNodeMax(left_child):
	 
*)	bst_node_t* curr_node = NULL, mother = NULL;
*)  assert(iter);
 
  *) curr_node = NodeToIter(iter);

    if(  NULL != curr_node->left_child )
    {
 		return BstNodeMax(curr_node);
	}
	
case 2: there is a no left child to the iter:	
	

		while( ( NULL != mother->parent) curr_node  != mother->right_child)
		{
			curr_node = mother ; 
			mother = curr_node->parent;	
		}
		
	 	/*if curr_node is min than undefine, return dummy end*/
		return mother; 

*/

bst_iter_t BstPrev(bst_iter_t iter)
{

}

/********************  BstNodeMax  ****************************/
/*Find the max value of a specific subtree brunch*/
/* Phases:bst_iter_t BstNodeMax(bst_node_t* node)
1. 
	
*)start from the node
*)get right_child until arrive to null, return that child(maximum).
assert(node);
bst_node_t* curr_node = node;

while( NULL != curr_node->right_child)
{
	curr_node = curr_node->right_child;
}

	return NodeToIter(curr_node);
*/
static bst_iter_t BstNodeMax(bst_node_t* node)
{
	
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
	
	case 3.1: a) The node has two children :
			  b) but one of the children has no children of its own:
			  c) replace the node with the child that has no children


	(find which child of curr_node has no children (left/right)
		 and save(addr) that child)
	child_wo_children = curr_node->left/right child; 
	
	(save what child curr_node is(left/right)) using static function
	(replace the node with the child) 
	parnt-> left/right child = child_wo_children;
				
	free(curr_node);
	curr_node = NULL;
	
	case 3.2: a) The node has two children :
			  b) both children have children:
			  c) replace the node with the node that has the next highest key
	 
*/
bst_iter_t BstRemove(bst_iter_t what)
{

}


if(curr_node == parent->right_child)
	{
		parent->right_child = curr_node_next;
	}
	
	else
	{
		parent->left_child = curr_node_next;
	}


























