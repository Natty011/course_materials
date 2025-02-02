/***************************************
* Author : Natty
* Reviewer : Matan
* Date : 27 / 01 / 2025
* Last update: 02 / 02 / 2025
*****************************************/
#ifdef PRINTS
#include <stdio.h> 	
#endif

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
	struct bst_node* child[2]; /* child[0] = left, child[1] = right*/
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

int destroy_check = SUCCESS; /* extern */

/***************End of struct and enum declaration *******/

/***********Functions declaration*******/
static bst_iter_t BstNodeMax(bst_node_t* node);
static bst_iter_t BstNodeBegin(bst_node_t* node);
static int FindNumChilds(bst_node_t* node);
static int IsChildExist(bst_node_t* node, int child_pos);
static int IsLeftChild(bst_node_t* parnt, bst_node_t* child);
#ifdef PRINTS
void Pre_Print_Tree(bst_node_t* root, bst_t *bst, int level);
void Aux_Pre_Print_Tree(bst_t *bst, int level);
#endif
/**********End of functions declaration *******/

/***********Static Functions definition*******/

/********************  IsLeftChild  ****************************/
static int IsLeftChild(bst_node_t* parnt, bst_node_t* child)
{
	assert(parnt);
	assert(child);
	return child == parnt->child[LEFT];
	
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

/********************  BstNodeMax  ****************************/
/*	
	Find the end of node's sub tree 
*/
static bst_iter_t BstNodeMax(bst_node_t* node)
{
	assert(node);
	
	while(NULL != node->child[RIGHT])
	{
		node = node->child[RIGHT];
	}
	
	return NodeToIter(node);		
}

/********************  BstNodeBegin  ****************************/
/*	
	Find the begin of node's sub tree 
*/
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
/***********End Of Static Functions definition*******/

/********************  BstCreate  ****************************/
bst_t *BstCreate(cmp_func_t sort_func)
{
	bst_t *bst_p = (bst_t*)malloc(sizeof(bst_t));

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
	bst_p->end->data = NULL;
	bst_p->end->parent = NULL;
	bst_p->end->child[LEFT] = NULL; /* left child */
	bst_p->end->child[RIGHT] = NULL; /* right child */
	
	return bst_p;
}
/********************  BstDestroy  ****************************/
void BstDestroy(bst_t *bst)
{
	bst_node_t *curr_node = NULL, *curr_node_next = NULL;
	
	if(NULL == bst)
	{
		return;
	}
	
	assert(bst->end);
	curr_node = IterToNode(BstBegin(bst));
	
	while( curr_node != bst->end)
	{
		curr_node = BstNodeBegin(curr_node);
		curr_node_next = IterToNode(BstRemove(NodeToIter(curr_node) ));
		curr_node = curr_node_next;
	}
	
	if( TRUE != BstIsEmpty(bst) )
	{
	   destroy_check = OPERATION_FAIL;
	}
	free(bst->end);
	bst->end = NULL;
	
	free(bst);
	bst = NULL;
}

/********************  BstInsert  ****************************/
bst_iter_t BstInsert(bst_t *bst, const void *new_data)
{
	bst_node_t *new_node = NULL, *parnt = NULL, *curr_node = NULL;
	int res = 0, what_child = LEFT;
	
	assert(bst);
	
	new_node =  (bst_node_t*)malloc(sizeof(bst_node_t));
	
	if(NULL == new_node)
	{
		return NULL;
	}
	
	new_node->data = (void*)new_data;
	parnt = bst->end;

	curr_node = (bst->end)->child[LEFT]; /* get the root */
	
	while( !BstIsEmpty(bst) && NULL != curr_node)
	{
		res = bst->cmp_func(curr_node->data, (void*)new_data);
		parnt  = curr_node;
		
		if( res > 0 )
		{
			curr_node  = curr_node->child[LEFT]; /* left */
			what_child = LEFT;
		}
		
		else if ( res < 0 )
		{
			curr_node = curr_node->child[RIGHT]; /* right */
			what_child = RIGHT;
		}
	}
	
	parnt->child[what_child] = new_node;
	new_node->child[LEFT] = NULL;
	new_node->child[RIGHT] = NULL;
	new_node->parent = parnt;	
	
	return NodeToIter(new_node);	
}

/********************  BstBegin  ****************************/
bst_iter_t BstBegin(const bst_t *bst)
{
	bst_node_t* curr_node = NULL;	
	
	assert(bst);
	assert(bst->end);
	
	curr_node = bst->end;
	
	if(TRUE == BstIsEmpty(bst) )
	{
		return NodeToIter(curr_node);
	}
	
	return BstNodeBegin(curr_node);		
}
/********************  BstIsEmpty  ****************************/
int BstIsEmpty(const bst_t *bst)
{
	assert(bst);	
	assert(bst->end);
	
	return bst->end->child[LEFT] ? FALSE : TRUE;	
}

/********************  BstNext  ****************************/
bst_iter_t BstNext(bst_iter_t iter)
{
	bst_node_t *curr_node = NULL, *parnt = NULL;
	assert( IterToNode(iter) );

	curr_node = IterToNode(iter);
	
	parnt  = curr_node->parent;
	
	if( NULL == parnt ) /* iter is dummy end */
	{
		return iter;
	}
	
	if( NULL != curr_node->child[RIGHT] ) 
    {
 		return BstNodeBegin(curr_node->child[RIGHT]);
	}
	
	while( curr_node != parnt->child[LEFT] )
	{
		curr_node = parnt;
		parnt = curr_node->parent;
	}
	
	return NodeToIter(parnt); /*if curr_node is max than return dummy end*/	
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
	
	parnt = curr_node->parent;
	/* if the parent is dummy end don't compare to its right child(NULL) */
	while( (NULL != parnt->parent) && (curr_node != parnt->child[RIGHT] ))
	{
		curr_node = parnt;
		parnt = curr_node->parent;
	}
	/*if curr_node is min than undefine, return dummy end*/
	return NodeToIter(parnt);
}

/********************  BstRemove  ****************************/

bst_iter_t BstRemove(bst_iter_t what)
{
	bst_node_t *curr_node = NULL, *parnt = NULL, 
			 *curr_node_next = NULL, *l_child = NULL;
	
	int what_child = LEFT, what_son = LEFT;
	 
	assert(IterToNode(what));
	curr_node = IterToNode(what);
	parnt = curr_node->parent;
	assert( parnt ); /* check if curr_node is a dummy end */
	curr_node_next = BstNext(what);
	
	/* case 1: The node has no childs */
	
	if( NO_CHILDS == FindNumChilds(curr_node) )
	{
		
		if(IsLeftChild(parnt, curr_node) )
		{
			parnt->child[LEFT] = NULL; 
		}									
		else
		{
			parnt->child[RIGHT] = NULL;	
		}
							
		free(curr_node);
		curr_node = NULL;
		
		return NodeToIter(curr_node_next);
	}
	
	/* case 2: the node has one child:
				 replace the node with the child */
	if( ONE_CHILD == FindNumChilds(curr_node ) )
	{
		what_child = IsLeftChild(parnt, curr_node) ? LEFT: RIGHT;
		what_son = IsChildExist(curr_node, LEFT) ? LEFT : RIGHT;
		
		parnt->child[what_child] = curr_node->child[what_son];	
		curr_node->child[what_son]->parent = parnt;	
		
		free(curr_node);
		curr_node = NULL;
		
		return NodeToIter(curr_node_next);
	}
	
	/* case 3: The node has two children:  */
	if(  TWO_CHILDS == FindNumChilds(curr_node ) )
	{
		l_child =  IterToNode(BstNodeBegin(curr_node->child[RIGHT]));
		parnt = l_child->parent;
		
		what_child = IsLeftChild(parnt, l_child) ? LEFT: RIGHT;
		
		curr_node->data = l_child->data;
		
		/* l_child must be left_child that has only rights childs */
		if(	IsChildExist(l_child, RIGHT) )
		{
			parnt->child[what_child] = l_child->child[RIGHT];
			l_child->child[RIGHT]->parent = parnt;
		}
		
		else
		{
			parnt->child[what_child] = NULL;
		}
		
		free( l_child );
		l_child = NULL;
	}
	
	return NodeToIter(curr_node); /* case 3 */
}		
/********************  BstGetData  ****************************/
void *BstGetData(bst_iter_t iter)
{
	assert( IterToNode(iter) );
	return IterToNode(iter)->data;
}
/********************  is_same_iter  ****************************/
int BstIsIterSame(bst_iter_t iter1, bst_iter_t iter2)
{
	assert( IterToNode(iter1) );
	assert( IterToNode(iter2) );
	
	return IterToNode(iter1) == IterToNode(iter2) ;
}

/********************  BstEnd  ****************************/
bst_iter_t BstEnd(const bst_t *bst)
{
	assert(bst);
	return bst->end;
}

/********************  BstFind  ****************************/
bst_iter_t BstFind(const bst_t *bst, void *data_to_find)
{
	bst_node_t *curr_node = NULL;
	int res = 0;
	
	assert(bst);
	
	if(TRUE == BstIsEmpty(bst))
	{
		return IterToNode(bst->end);
	}
	
	curr_node = bst->end->child[LEFT]; /* get the root */
	
	while( NULL != curr_node)
	{
		res = bst->cmp_func(curr_node->data, data_to_find);
		
		if( res > 0 )
		{
			curr_node  = curr_node->child[LEFT]; /* left */
		}
		
		else if( res < 0 )
		{
			curr_node = curr_node->child[RIGHT]; /* right */
		}
		
		else
		{
			return NodeToIter(curr_node); 
		}
	}
		
	return IterToNode(bst->end);
}

/********************  BstSize  ****************************/
size_t BstSize(const bst_t *bst)
{
	bst_iter_t curr_iter = NULL;	
	size_t size = 0;
	
	assert(bst);
	assert(bst->end);
	
	if( TRUE == BstIsEmpty(bst) ) 
	{
		return size;
	}
	curr_iter = BstBegin( bst ); 
	while(( NULL != IterToNode(curr_iter)->parent) && 
			 bst->end != IterToNode( curr_iter  ) ) 
	{
		++size;
		curr_iter = BstNext( curr_iter );
	}
	
	return size;
}
/********************  BstForEach  ****************************/
int BstForEach(bst_iter_t start, bst_iter_t end,
                 operation_func_t op_func, void *user_param)
{
	int op_state = SUCCESS;
	 
	assert(IterToNode(start));
	assert(IterToNode(end));
	assert( op_func);

	while( !BstIsIterSame(start, end) )
	{
		if ( OPERATION_FAIL == op_func( BstGetData(start), user_param ) )
		{
			op_state = OPERATION_FAIL;
			break;
		}
		
		start = BstNext(start);
	}
	
	return op_state;
}                 

/********************  Pre_Print_Tree  ****************************/
#ifdef PRINTS
void Pre_Print_Tree(bst_node_t* root, bst_t *bst, int level)
{
	int i = 0;
	if(NULL != root ) 
	{
		for(i = 0; i < level; ++i)
		{
			printf(i == level-1 ? "|-" : "  ");
		}
		printf("%d\n",  *(int*)BstGetData(NodeToIter(root) ) );
		Pre_Print_Tree(root->child[LEFT], bst, level + 1 );
		Pre_Print_Tree(root->child[RIGHT], bst, level + 1);
	}

}

/********************  Aux_Pre_Print_Tree  ****************************/
void Aux_Pre_Print_Tree(bst_t *bst, int level)
{
	Pre_Print_Tree(bst->end->child[LEFT] , bst, level);

}
#endif


