/***************************************
* Author : Natty
* Reviewer : 
* Date : 15 / 02 / 2025
* Last update: 15 / 02 / 2025
*****************************************/
#ifdef PRINTS
#include <stdio.h> 	
#endif

#include <assert.h> 	/* assert */
#include <stdlib.h> 	/* malloc, free */
#include "avl.h" 

#define MIN(a, b)		((a > b ) ? b : a )
#define MAX(a, b)		((a > b ) ? a : b )
/****************struct and enum declaration*********************/

struct avl
{
	avl_node_t *root;
	cmp_func_t cmp_func;	
};


struct avl_node 
{
	void* data;
	size_t height;
	struct avl_node *child[2]; /* child[0] = left, child[1] = right*/
};

/** possible return values **/
typedef enum
{
	SUCCESS = 0,
	OPERATION_FAIL = 1
	
}avl_result_t;

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

typedef enum
{
	
	REMOVE = 0,
	INSERT = 2
	
}op_type_t;

int destroy_check_avl = SUCCESS; /* extern */

/***************End of struct and enum declaration *******/

/***********Functions declaration*******/
static void AuxAVLDestroy(avl_node_t *node);
static void AuxAVLInsert(avl_t *tree, avl_node_t *parent, avl_node_t *curr_node,
						 int res, avl_node_t *new_node, void* new_data);

/*static int IsLeftChild(avl_node_t* parent, avl_node_t* child);*/
static int FindNumChilds(avl_node_t* node);
static int IsChildExist(avl_node_t* node, int child_pos);
static void	SetHeight(avl_node_t* node, int child_pos, op_type_t op );
static size_t GetHeight( avl_node_t* node);
static void AuxAVLSize(avl_node_t *node, size_t *size);
static avl_node_t* AuxAVLFind(avl_t *tree, avl_node_t *node,
								  	const void *data_to_find );

static void AuxAVLForEachPreOrder(avl_node_t *node, op_func_t op_func,
								 void *user_param, int *res_op);
static void AuxAVLForEachPostOrder(avl_node_t *node, op_func_t op_func,
								 void *user_param, int *res_op);
static void AuxAVLForEachInOrder(avl_node_t *node, op_func_t op_func, 
								void *user_param, int *res_op);
								
static void *AvlGetDataFind(avl_node_t *node);																 								 
static void AuxAVLRemove0Child(avl_t *tree,  avl_node_t *parent, avl_node_t
								 *curr_node, int res, void* data_to_remove);								  	
#ifdef PRINTS
void *AvlGetData(avl_node_t *node);
void AvlPrintData(avl_node_t *node);

void Pre_Print_Tree_Avl(avl_node_t* root, avl_t *avl, int level);
void Aux_Pre_Print_Tree_Avl(avl_t *avl, int level);
#endif
/**********End of functions declaration *******/

/*****************Static Functions definition*********************************/

/********************  AuxAVLDestroy  ****************************/
static void AuxAVLDestroy(avl_node_t *node)
{
	if(NULL != node )
	{
		AuxAVLDestroy(node->child[LEFT] );
		AuxAVLDestroy(node->child[RIGHT] );
		
		node->child[LEFT] = node->child[RIGHT] = NULL;
		free( node );
		node = NULL;

	}
}

/********************  IsLeftChild  ****************************/
/*
static int IsLeftChild(avl_node_t* parent, avl_node_t* child)
{
	assert(parent);
	assert(child);
	return child == parent->child[LEFT];
	
}
*/
/********************  FindNumChilds  ****************************/
static int FindNumChilds(avl_node_t* node)
{
	assert(node);
	return IsChildExist(node, LEFT) + IsChildExist(node, RIGHT);

}
/********************  IsChildExist  ****************************/
static int IsChildExist(avl_node_t* node, int child_pos)
{
	assert(node);
	return  LEFT == child_pos ? NULL != node->child[LEFT] :
								NULL != node->child[RIGHT]; 
}
/********************  SetHeight  ****************************/
static void	SetHeight(avl_node_t* node, int child_pos, op_type_t op )
{
			  
    	/*op = (size_t)op;*/
	switch( FindNumChilds( node ) )
	{

		case 0:
			node->height +=	(1 * ((size_t)op - 1 )) ;
			break;
			
		case 1:
			printf("IsChildExist(node, child_pos) = %d, child_pos = %d \n", 
			IsChildExist(node, child_pos), child_pos);
			node->height +=	IsChildExist(node, child_pos) * ((size_t)op - 1 ) ; 
			break;	
		
		case 2:
			op = (size_t)INSERT;
			node->height = MAX( GetHeight( node->child[LEFT]) , 
								GetHeight( node->child[RIGHT]) )
								 +  (op - 1 );
			break;
	}
	
		printf(" FindNumChilds( node )= %d\n", FindNumChilds( node ) );	  				  			  
		printf(" GetHeight(node) = %lu\n", GetHeight(node));
}

/********************  GetHeight  ****************************/
static size_t GetHeight( avl_node_t* node)
{
	assert(node);
	return node->height;
}


/********************  AuxAVLSize  ****************************/
static void AuxAVLSize(avl_node_t *node, size_t *size)
{
	if(NULL != node )
	{
		AuxAVLSize(node->child[LEFT],  size);
		AuxAVLSize(node->child[RIGHT], size);
		
		++(*size);
	}
}	

/********************  AuxAVLInsert  ****************************/
static void AuxAVLInsert(avl_t *tree,  avl_node_t *parent ,avl_node_t *curr_node,
						int res, avl_node_t *new_node, void* new_data)
{	
	
	int what_child = LEFT;
	
	assert( tree );

	if(NULL == curr_node ) 
	{
		
		if( AVLIsEmpty(tree) )
		{
			tree->root = new_node;
		}
		
		else  
		{
			what_child = res > 0 ? LEFT : RIGHT;
			parent->child[what_child] = new_node;	
		}

		new_node->child[LEFT] = NULL;
		new_node->child[RIGHT] = NULL;
		new_node->height = 0;	
	
		return;
	}	
	
	res = tree->cmp_func( curr_node->data, new_data );
	what_child = res > 0 ? LEFT : RIGHT;
	
	/*SetHeight( curr_node, what_child, INSERT );*/
	
	AuxAVLInsert(tree, curr_node, curr_node->child[what_child], res,
				  new_node,  new_data );
				  
	SetHeight( curr_node, what_child, INSERT );			  
}	

/********************  AuxAVLFind  ****************************/
static avl_node_t* AuxAVLFind(avl_t *tree, avl_node_t *node,
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

	return AuxAVLFind(tree, node->child[what_child], data_to_find);
}
/********************  AuxAVLForEachPreOrder  ****************************/
static void AuxAVLForEachPreOrder(avl_node_t *node, op_func_t op_func,
								 void *user_param, int *res_op)
{
	assert( op_func);

	if( NULL != node )
	{
		if(SUCCESS == *res_op && OPERATION_FAIL == op_func(node->data, user_param) )
		{
			/*
			puts("Pre");
			AvlPrintData( node);
			*/
			*res_op =  OPERATION_FAIL;	
		}

		else if ( SUCCESS == *res_op )
		{
			AuxAVLForEachPreOrder( node->child[LEFT], op_func, user_param, res_op);
			AuxAVLForEachPreOrder( node->child[RIGHT], op_func, user_param, res_op);
		}
	}
}								 

/********************  AuxAVLForEachPostOrder  ****************************/
static void AuxAVLForEachPostOrder(avl_node_t *node, op_func_t op_func,
								 void *user_param, int *res_op)
{
	assert( op_func);

	if( NULL != node )
	{
		if ( SUCCESS == *res_op )
		{
			AuxAVLForEachPostOrder( node->child[LEFT], op_func, user_param, res_op);
			AuxAVLForEachPostOrder( node->child[RIGHT], op_func, user_param, res_op);
			
			if(SUCCESS == *res_op &&  OPERATION_FAIL == op_func(node->data, user_param) )
			{
				/*
				puts("Post");
				AvlPrintData( node);
				*/
				*res_op =  OPERATION_FAIL;
			}
		}
	}
}		
                          
/********************  AuxAVLForEachInOrder  ****************************/
static void AuxAVLForEachInOrder(avl_node_t *node, op_func_t op_func,
								 void *user_param, int *res_op)
{
	assert( op_func);

	if( NULL != node )
	{
		if ( SUCCESS == *res_op )
		{
			AuxAVLForEachInOrder( node->child[LEFT], op_func, user_param, res_op);
			
			if(SUCCESS == *res_op && OPERATION_FAIL == op_func(node->data, user_param) )
			{
				/*
				puts("In");
				AvlPrintData( node);
				*/
				*res_op =  OPERATION_FAIL;	
			}
	
			AuxAVLForEachInOrder( node->child[RIGHT], op_func, user_param, res_op);
		}
	}
}		

/*******************End Of Static Functions definition************************/

/********************  AVLCreate  ****************************/
avl_t *AVLCreate(cmp_func_t sort_func)
{
	avl_t *avl_p = (avl_t*)malloc(sizeof(avl_t));

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
	return NULL == tree->root ; 
}
/********************  AVLHeight  ****************************/
size_t AVLHeight(const avl_t* tree)
{
	assert( tree );
	return AVLIsEmpty( tree ) ? 0 : tree->root->height ; 
}

/********************  AVLDestroy  ****************************/
void AVLDestroy(avl_t *tree)
{
	avl_node_t* curr_node = NULL;
	assert( tree );
	curr_node = tree->root ;
	
	if( NULL != curr_node )
	{
		AuxAVLDestroy( curr_node );
	}

	tree->root = NULL;
	/*
	if( TRUE != AVLIsEmpty(tree) )
	{
	   destroy_check_avl = OPERATION_FAIL;
	}
	*/
	free(tree);
	tree = NULL;
	
}

/********************  AVLSize  ****************************/

size_t AVLSize(const avl_t* tree)
{
	size_t size = 0;
	assert( tree );
	
	AuxAVLSize( tree->root, &size);
	return size;
}



/********************  AVLInsert  ****************************/
int AVLInsert(avl_t *tree, void *data)
{
	avl_node_t *parent = NULL;
	avl_node_t *new_node = NULL, *curr_node = NULL;

	assert(tree);
	
	new_node =  (avl_node_t*)malloc(sizeof(avl_node_t));
	
	if(NULL == new_node)
	{
		return OPERATION_FAIL;
	}
	new_node->data = (void*)data;

	
	curr_node = tree->root; /* get the root */
	parent = curr_node;
	AuxAVLInsert(tree, parent, curr_node, 0, new_node, (void*)data);
	/*AvlPrintData( new_node );*/
	/*AvlPrintData( tree->root );*/
	return SUCCESS; 
				 
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
	
	return AvlGetDataFind(AuxAVLFind(tree, curr_node, data));
								 
}
/********************  AVLForEachInOrder  ****************************/
int AVLForEachInOrder(avl_t *tree, op_func_t op_func, 
                              void *user_param, int traversal_order)
{
	int op_state = SUCCESS;
	assert(tree);
	assert( op_func);
	
	switch( traversal_order )
	{
	
		case IN_ORDER:
			AuxAVLForEachInOrder(tree->root, op_func, user_param, &op_state);
			break;
		case PRE_ORDER:
			AuxAVLForEachPreOrder(tree->root, op_func, user_param, &op_state);
			break;
		case POST_ORDER:
			AuxAVLForEachPostOrder(tree->root, op_func, user_param, &op_state);
			break;	
	}

	return op_state;
}

/********************  AVLRemove  ****************************/

void AVLRemove(avl_t *tree, void *data)
{
	avl_node_t *curr_node = NULL, *parent = NULL;
	assert(tree);
	
	curr_node = tree->root; /* get the root */
	
	curr_node = AuxAVLFind(tree, curr_node, data);
	AvlPrintData( curr_node);
	if( NULL == curr_node ) /* there is no such data*/
	
	{
		return;
	}
	curr_node = tree->root; /* get the root */
	
	parent = curr_node;
	
	switch( FindNumChilds(curr_node) )
	{
		case NO_CHILDS:
			AuxAVLRemove0Child(tree, parent, curr_node, 0, data);
			break;
			
		case ONE_CHILD:
			AuxAVLRemove0Child(tree, parent, curr_node, -1, data);
			break;
		case TWO_CHILDS:
			AuxAVLRemove0Child(tree, parent, curr_node, -1, data);
			break;	
	}
	/*AvlPrintData( curr_node);*/
	/*curr_node = NULL;*/
}

/********************  AuxAVLRemove0Child  ****************************/
static void AuxAVLRemove0Child(avl_t *tree,  avl_node_t *parent, avl_node_t
								 *curr_node, int res, void* data_to_remove)
{	
	int what_child = LEFT;
	assert( tree );

	if(NULL == curr_node ) 
	{
		return;
	}
	
	AvlPrintData( curr_node);
	AvlPrintData( parent);
	
	res = tree->cmp_func( curr_node->data, data_to_remove );
	
	what_child = res > 0 ? LEFT : RIGHT;
	/*
	printf("what_child = %d\n", what_child);
	printf("res = %d\n", res);
	*/
	if( 0 == res ) /* the node to remove */
	{
		res = tree->cmp_func(parent->data, curr_node->data );
		what_child = res > 0 ? LEFT : RIGHT;
		
		if( tree->root ==  curr_node)
		{
			tree->root = NULL;
		}
		
		else  
		{
			AvlPrintData( curr_node);
			AvlPrintData( parent);
			parent->child[what_child] = NULL;
		}
		
		curr_node->height = 0;
		free( curr_node );
		curr_node = NULL;
	
		return;
	}
	
	/*
	res = tree->cmp_func( curr_node->data, new_data );
	what_child = res > 0 ? LEFT : RIGHT;
	*/
	/*SetHeight( curr_node, what_child, INSERT );*/
	
	AuxAVLRemove0Child(tree, curr_node, curr_node->child[what_child],
						 res, data_to_remove );
						 
	AvlPrintData( curr_node);
	/*
	printf("IsChildExist(curr_node, what_child) = %d, what_child = %d \n", 
			IsChildExist(curr_node, what_child), what_child);
	printf(" FindNumChilds( curr_node )= %d\n", FindNumChilds( curr_node ) );
	*/	  				  			  
	SetHeight( curr_node, what_child, REMOVE );	  
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
	
	printf("%d(h=%lu)\n",  *(int*)AvlGetData(node ), node->height );
}
/********************  Pre_Print_Tree_Avl  ****************************/
void Pre_Print_Tree_Avl(avl_node_t* root, avl_t *avl, int level)
{
	int i = 0;
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







