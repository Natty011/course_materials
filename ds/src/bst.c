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

/***************End of struct and enum declaration *******/

/***********Functions declaration and definition*******/
/*static int CountNodes (void *data, void *user_param);*/

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
	bst_p->end->child[0] = NULL; /* left child */
	bst_p->end->child[1] = NULL; /* right child */
	
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
/*Phases: bst_iter_t BstInsert(bst_t *bst, const void *new_data)
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
	bst_node_t* new_node = NULL, parnt = NULL, curr_node = NULL;
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

		new_node->child[0] = NULL;
		new_node->child[1] = NULL;
		bst->end->child[0] = new_node;
		 
		return NodeToIter(new_node);
	}
	
	curr_node = BstPrev(bst->end); /* get the root */
	
	while(NULL != curr_node)
	{
		res = cmp_func(curr_node->data, new_data);
		parnt  = curr_node;
		
		if( res > 0 )
		{
			curr_node  = curr_node->child[0]; /* left */
		}
		
		else 
		{
			curr_node = curr_node->child[1]; /* right */
		}
	}
	
	if( res > 0 )
	{
		parnt->child[0] = new_node;
		
	}
	
	else
	{
		parnt->child[1] = new_node;
	}
	
	new_node->child[0] = NULL;
	new_node->child[1] = NULL;	
	new_node->data = new_data;
	
	return NodeToIter(new_node);	
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











