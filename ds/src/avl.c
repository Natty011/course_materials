/***************************************
* Author : Natty
* Reviewer : Rawan
* Date : 10 / 02 / 2025
* Last update: 15 / 02 / 2025
*****************************************/
#ifdef PRINTS
	#include <stdio.h> 
	#include <math.h> 	
#endif

#include <assert.h> 	/* assert */
#include <stdlib.h> 	/* malloc, free */

#include <stdio.h> 

#include "avl.h" 

#define MAX( a , b )		( ( (a) > (b) ) ? (a) : (b) )
#define UNUSED( var )       ( (void)var )


/***************************** Success / Fail Enum ****************************/

typedef enum
{
	SUCCESS = 0,
	OPERATION_FAIL = 1
	
} result_t;

/******************************************************************************/
/******************************* True / False Enum ****************************/

typedef enum
{
	FALSE = 0,
	TRUE = 1
} bool_t;

/******************************************************************************/
/*************************** Left child / Right child Enum ********************/

typedef enum
{
	LEFT = 0  ,
	RIGHT = 1 ,
	NUMBER_OF_CHILDRENS
	
} child_pose_t;
/******************************************************************************/

typedef enum
{
	
	NO_CHILDS = 0,
	ONE_CHILD = 1,
	TWO_CHILDS = 2
	
} num_of_childs_t;

/******************************************************************************/
/***************************** Management struct ******************************/
struct avl
{
	avl_node_t *root;
	cmp_func_t cmp_func;	
};


struct avl_node 
{
	void* data;
	int height;
	struct avl_node *child[NUMBER_OF_CHILDRENS];
};

/******************************************************************************/
/************************ ststic functions declartions ************************/


static avl_node_t*
RecAVLInsert(avl_node_t* root ,avl_node_t *new_node , cmp_func_t func);

static void RecAVLDestroy(avl_node_t* node);

static void SetHeight( avl_node_t* node ); 
static int BalancedFactor( avl_node_t *node );

static avl_node_t *RightRotate( avl_node_t *node );
static avl_node_t *LeftRotate( avl_node_t *node );
static avl_node_t*
HandleRebalance(avl_node_t *root ,int balance_factor ,int child_balance_factor);

static avl_node_t* 
RecAVLRemove(avl_node_t* root , void *data , cmp_func_t func , void** data_ptr);

static size_t FindNumChilds(avl_node_t* node);


static void RecAVLSize(avl_node_t *node, size_t *size);
static avl_node_t* RecAVLFind(avl_t *tree, avl_node_t *node,
								  	const void *data_to_find );

static void RecAVLForEachPreOrder(avl_node_t *node, op_func_t op_func,
								 				void *user_param, int *res_op);
static void RecAVLForEachPostOrder(avl_node_t *node, op_func_t op_func,
											    void *user_param, int *res_op);
static void RecAVLForEachInOrder(avl_node_t *node, op_func_t op_func,
								 				void *user_param, int *res_op);
#ifdef PRINTS

void *AvlGetData(avl_node_t *node);
void AvlPrintData(avl_node_t *node);
void Pre_Print_Tree_Avl(avl_node_t* root, avl_t *avl, int level);
void Pre_Print_Tree_Avl(avl_node_t* root, avl_t *avl, int level);
void Aux_Pre_Print_Tree_Avl(avl_t *avl, int level);										
#endif

/*******************End Of Static Functions definition************************/

/********************  AVLCreate  ****************************/
avl_t* AVLCreate(cmp_func_t sort_func)
{
	avl_t* avl_p = ( avl_t* )malloc( sizeof(avl_t) );

	if(NULL == avl_p)
	{
		return NULL;
	}
	
	avl_p->cmp_func = sort_func;
	avl_p->root = NULL;
	
	return avl_p;
}

/********************  AVLIsEmpty  ****************************/

int AVLIsEmpty(const avl_t* tree)
{
	assert( tree );
	
	return NULL == tree->root;  
}

/********************  AVLHeight  ****************************/

int AVLHeight(const avl_t* tree)
{
	assert( tree );
	
	return AVLIsEmpty( tree ) ? -1 : tree->root->height ; 
}

/********************  AVLDestroy  ****************************/

static void RecAVLDestroy(avl_node_t* node)
{
	if ( NULL == node )
	{
		return;
	}

	RecAVLDestroy(node->child[LEFT] );
	RecAVLDestroy(node->child[RIGHT] );
	
	node->child[LEFT] = node->child[RIGHT] = NULL;
	
	free( node );
	node = NULL;
}

void AVLDestroy(avl_t* tree)
{	
	if ( NULL != tree )
	{
		RecAVLDestroy( tree->root);
		tree->root = NULL;
		free(tree);
		tree = NULL;
	}

}

/********************  AVLSize  ****************************/

size_t AVLSize(const avl_t* tree)
{
	size_t size = 0;
	assert( tree );
	
	RecAVLSize( tree->root, &size);
	return size;
}

/********************  AVLInsert  ****************************/

int AVLInsert( avl_t* tree, void* data )
{
	avl_node_t *new_node = NULL;

	assert(tree);
	
	new_node = (avl_node_t*)malloc(sizeof(avl_node_t) );
	
	if(NULL == new_node)
	{
		return OPERATION_FAIL;
	}
	new_node->data = data;
	new_node->height = 0;
	new_node->child[LEFT] = new_node->child[RIGHT] = NULL; 

	tree->root = RecAVLInsert( tree->root , new_node , tree->cmp_func );
	SetHeight( tree->root );
	
	return SUCCESS; 
				 
}
static avl_node_t*
RecAVLInsert(avl_node_t* root , avl_node_t *new_node , cmp_func_t func)
{	
	int res = 0 , balance_factor = 0 , child_balance_factor = 0;
	child_pose_t pose_to_move = 0;

	if ( NULL == root )
	{
		return new_node;
	}
	
	res = func( root->data , new_node->data );
	pose_to_move = res < 0; /* ... */
	
	root->child[pose_to_move] = 
	RecAVLInsert( root->child[pose_to_move] , new_node , func );

	SetHeight( root );
	
	balance_factor = BalancedFactor( root );
	
	if ( balance_factor > -2 && balance_factor < 2 )
	{
		return root;
	}
	
	child_balance_factor = BalancedFactor(root->child[(-2 == balance_factor)]);
	
	return HandleRebalance( root , balance_factor , child_balance_factor );	
}
						
/********************  AvlGetDataFind  ****************************/
static void *AvlGetDataFind(avl_node_t *node)
{
	if(NULL == node )
	{
		return NULL;
	}
	
	return node->data;
}

/********************  AVLFind  ****************************/
void *AVLFind(avl_t *tree, const void *data)
{
	avl_node_t *curr_node = NULL;
	assert(tree);
	
	curr_node = tree->root; /* get the root */
	
	return AvlGetDataFind(RecAVLFind(tree, curr_node, data));						 
}
/********************  AVLForEachInOrder  ****************************/
int AVLForEach(avl_t *tree, op_func_t op_func, 
                              void *user_param, int traversal_order)
{
	int op_state = SUCCESS;
	assert(tree);
	assert( op_func);
	
	switch( traversal_order )
	{
		case IN_ORDER:
			RecAVLForEachInOrder(tree->root ,op_func , user_param, &op_state);
			break;
		case PRE_ORDER:
			RecAVLForEachPreOrder(tree->root ,op_func , user_param, &op_state);
			break;
		case POST_ORDER:
			RecAVLForEachPostOrder(tree->root ,op_func , user_param, &op_state);
			break;	
	}
	
	return op_state;
}

/********************  AVLRemove  ****************************/

void AVLRemove(avl_t *tree, void *data)
{
	assert(tree);
	
	tree->root = RecAVLRemove( tree->root , data , tree->cmp_func , NULL );
	
	SetHeight( tree->root );
}


/********************  RecAVLRemove  ****************************/

static avl_node_t* 
RecAVLRemove(avl_node_t* root , void *data , cmp_func_t func , void** data_ptr)
{	
	int res = 0 ,pose_to_move = 0 ,balance_factor = 0 ,child_balance_factor = 0;
	avl_node_t* node_to_return = NULL;
	
	if(NULL == root ) 
	{
		return NULL;
	}
	
	
	if ( NULL == data_ptr )
	{
		res = func( root->data , data );
		
		
		if ( res != 0 )
		{
			pose_to_move = res < 0; /* ... */
			
			root->child[pose_to_move] = 
			RecAVLRemove( root->child[pose_to_move] , data , func , NULL );
		}
		else if ( FindNumChilds( root ) < 2 )
		{
			node_to_return = root->child[root->child[RIGHT] != NULL];
			
			root->child[LEFT] = root->child[RIGHT] = NULL;
			root->data = NULL;
			free( root );
			
			return node_to_return;	
		}
		else
		{
			root->child[RIGHT] = 
			RecAVLRemove( root->child[RIGHT] , data , func , &root->data );
		}
	}
	else
	{
		if ( NULL != root->child[LEFT] )
		{
			root->child[LEFT] = 
			RecAVLRemove( root->child[LEFT] , data , func , data_ptr );
		}
		else
		{
			*data_ptr = root->data;
			node_to_return = root->child[RIGHT];

			root->child[LEFT] = root->child[RIGHT] = NULL;
			root->data = NULL;
			free( root );

			return node_to_return;
		}
	}
	
	SetHeight( root );
	
	balance_factor = BalancedFactor( root );
	
	if ( balance_factor > -2 && balance_factor < 2 )
	{
		return root;
	}
	
	child_balance_factor = BalancedFactor(root->child[(-2 == balance_factor)]);
	
	return HandleRebalance( root , balance_factor , child_balance_factor );
}	

/************************ ststic functions definitions ************************/
/********************  FindNumChilds  ****************************/
static size_t FindNumChilds(avl_node_t* node)
{
	assert(node);
	return ( NULL != node->child[LEFT] ) + ( NULL != node->child[RIGHT] );

}

/* Find the height of an AVL node recursively */
/********************  SetHeight  ****************************/

static void SetHeight( avl_node_t* node ) 
{
	int height_left = 0;
	int height_right = 0;
	assert(node);
	
	height_left = node->child[LEFT] ? node->child[LEFT]->height : -1;
	height_right = node->child[RIGHT] ? node->child[RIGHT]->height : -1;
	
	node->height = MAX( height_left , height_right ) + 1;
}

/********************  RecAVLSize  ****************************/
static void RecAVLSize(avl_node_t *node, size_t *size)
{
	if(NULL != node )
	{
		RecAVLSize(node->child[LEFT],  size);
		RecAVLSize(node->child[RIGHT], size);
		
		++(*size);
	}
}	

/********************  HandleRebalance  ****************************/	

static avl_node_t*
HandleRebalance(avl_node_t *root ,int balance_factor ,int child_balance_factor)
{	
	avl_node_t *new_root = NULL;
	
	/* RR */									
	if( -2 == balance_factor && child_balance_factor <= 0 )
	{			
		new_root =  LeftRotate( root ); 
	}
	/* RL */										
	else if( -2 == balance_factor &&  1 == child_balance_factor )
	{
		root->child[RIGHT] = RightRotate( root->child[RIGHT] );
		new_root = LeftRotate( root );
	}
	/* LL */										
	else if( 2 == balance_factor && child_balance_factor >= 0 )
	{			
		new_root =  RightRotate( root ); 
	}
	/* LR */										
	else if( 2 == balance_factor &&  child_balance_factor == -1  )
	{
		root->child[LEFT] = LeftRotate( root->child[LEFT] );				
		new_root = RightRotate( root );		
	}
	
	SetHeight( root );
	SetHeight( new_root );
	return new_root;					
}

/********************  RightRotate  ****************************/	
static avl_node_t *RightRotate( avl_node_t *node )
{
	avl_node_t *new_root = NULL, *tmp = NULL;
	assert( node );
	
	new_root = node->child[LEFT];
	tmp = new_root->child[RIGHT]; /* save for connect to old root later */
	
	new_root->child[RIGHT] = node;
	node->child[LEFT] = tmp;
	
	SetHeight( node );
	SetHeight( new_root );
	
	return new_root;
}
/********************  RightRotate  ****************************/	
static avl_node_t *LeftRotate( avl_node_t *node )
{
	avl_node_t *new_root = NULL, *tmp = NULL;
	assert( node );
	
	new_root = node->child[RIGHT];
	tmp = new_root->child[LEFT]; /* save for connect to old root later */
	
	new_root->child[LEFT] = node;
	node->child[RIGHT] = tmp;
	
	SetHeight( node );
	SetHeight( new_root );
	
	return new_root;
}

/********************  BalancedFactor  ****************************/	
static int BalancedFactor( avl_node_t *node )
{
	int height_left = 0;
	int height_right = 0;
	assert(node);
	
	height_left = node->child[LEFT] ? node->child[LEFT]->height : -1;
	height_right = node->child[RIGHT] ? node->child[RIGHT]->height : -1;
	
	return height_left - height_right; 
}

/********************  RecAVLFind  ****************************/
static avl_node_t* RecAVLFind(avl_t *tree, avl_node_t *node,
								  	const void *data_to_find )
{
	int what_child = LEFT, res = 0;
	
	assert(tree);
	assert(node);
	
	if( NULL == node )
	{
		return NULL;	
	}
	
	res = tree->cmp_func( node->data, data_to_find );
	what_child = res > 0 ? LEFT : RIGHT;
	
	if( 0 == res )
	{
		return node;
	}

	return RecAVLFind(tree, node->child[what_child], data_to_find);
}
/********************  RecAVLForEachPreOrder  ****************************/

static void RecAVLForEachPreOrder(avl_node_t *node, op_func_t op_func,
								 void *user_param, int *res_op)
{
	assert( op_func);

	if( NULL != node )
	{
		if(SUCCESS == *res_op && OPERATION_FAIL == op_func(node->data, user_param) )
		{
			*res_op =  OPERATION_FAIL;	
		}

		else if ( SUCCESS == *res_op )
		{
			RecAVLForEachPreOrder( node->child[LEFT], op_func, user_param, res_op);
			RecAVLForEachPreOrder( node->child[RIGHT], op_func, user_param, res_op);
		}
	}
}								 

/********************  RecAVLForEachPostOrder  ****************************/
static void RecAVLForEachPostOrder(avl_node_t *node, op_func_t op_func,
								 void *user_param, int *res_op)
{
	assert( op_func);

	if( NULL != node )
	{
		if ( SUCCESS == *res_op )
		{
			RecAVLForEachPostOrder( node->child[LEFT], op_func, user_param, res_op);
			RecAVLForEachPostOrder( node->child[RIGHT], op_func, user_param, res_op);
			
			if(SUCCESS == *res_op &&  OPERATION_FAIL == op_func(node->data, user_param) )
			{
				*res_op =  OPERATION_FAIL;
			}
		}
	}
}		
                          
/********************  RecAVLForEachInOrder  ****************************/
static void RecAVLForEachInOrder(avl_node_t *node, op_func_t op_func,
								 void *user_param, int *res_op)
{
	assert( op_func);

	if( NULL != node )
	{
		if ( SUCCESS == *res_op )
		{
			RecAVLForEachInOrder( node->child[LEFT], op_func, user_param, res_op);
			
			if(SUCCESS == *res_op && OPERATION_FAIL == op_func(node->data, user_param) )
			{
				*res_op =  OPERATION_FAIL;	
			}
	
			RecAVLForEachInOrder( node->child[RIGHT], op_func, user_param, res_op);
		}
	}
}	


#ifdef PRINTS
/********************  AvlGetData  ****************************/
void *AvlGetData(avl_node_t *node)
{
	/*assert( node );*/
	
	if(NULL == node )
	{
		return NULL;
	}
	
	return node->data;
}
/********************  AvlPrintData  ****************************/
void AvlPrintData(avl_node_t *node)
{
	/*assert( node );*/
	
	if(NULL == node )
	{
		printf("%p\n",  AvlGetData(node ) );
		return ;
	}
	
	/*printf("%d(h=%lu)\n",  *(int*)AvlGetData(node ), node->height );*/
}
/********************  Pre_Print_Tree_Avl  ****************************/
void Pre_Print_Tree_Avl(avl_node_t* root, avl_t *avl, int level)
{
	int i = 0;
	/*AvlPrintData( root );*/

	if(NULL != root ) 
	{
		
		for(i = 0; i < level; ++i)
		{
			printf(i == level-1 ? "|-" : "  ");
		}
		AvlPrintData( root );
		
		/*printf("%d\n",  *(int*)BstGetData(NodeToIter(root) ) );*/
		Pre_Print_Tree_Avl(root->child[LEFT], avl, level + 1 );
		Pre_Print_Tree_Avl(root->child[RIGHT], avl, level + 1);
	
	}
	
}

/********************  Aux_Pre_Print_Tree_Avl  ****************************/
void Aux_Pre_Print_Tree_Avl(avl_t *avl, int level)
{
	Pre_Print_Tree_Avl(avl->root , avl, level);

}
#endif




