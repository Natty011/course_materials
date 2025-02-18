/***************************************
* Author : Natty
* Reviewer : 
* Date : 10 / 02 / 2025
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

#define UNUSED( var )       ( (void)var )
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

/***********Global*******/
int balanced_broken = FALSE;
/***********Global*******/

/***************End of struct and enum declaration *******/

/***********Functions declaration*******/
static void AuxAVLDestroy(avl_node_t *node);
static avl_node_t * AuxAVLInsert(avl_t *tree, avl_node_t *parent, avl_node_t *curr_node,
						 int res, avl_node_t *new_node, void* new_data, op_type_t op);

static int IsLeftChild(avl_node_t* parent, avl_node_t* child);
static int FindNumChilds(avl_node_t* node);
static int IsChildExist(avl_node_t* node, int child_pos);
static size_t SetHeight(avl_node_t* node, int child_pos, op_type_t op );
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
					 
static avl_node_t *AuxAVLRemove(avl_t *tree,  avl_node_t *parent, avl_node_t
								 *curr_node, int res,
								  void* data_to_remove, op_type_t op);
								 
static avl_node_t* AvlNodeMax(avl_node_t **parent, avl_node_t* curr_node);	

static int BalancedFactor(avl_t *tree, avl_node_t *curr_node);
static int GetChildHeight(avl_node_t *node, int child_pos);

static avl_node_t *RightRotate(avl_t *tree, avl_node_t *y, int what_child, op_type_t op);
static avl_node_t *LeftRotate(avl_t *tree, avl_node_t *x, int what_child, op_type_t op);
static avl_node_t *HandleRebalance( avl_t *tree,  avl_node_t *parent
						 ,avl_node_t *curr_node, int what_child, op_type_t op);

/*size_t avl_node_height( avl_node_t *node ); */
						 
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

static int IsLeftChild(avl_node_t* parent, avl_node_t* child)
{
	assert(parent);
	/*assert(child);*/
	return child == parent->child[LEFT];
	
}

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

/* Find the height of an AVL node recursively */
/********************  SetHeight  ****************************/

static size_t SetHeight( avl_node_t *node, int child_pos, op_type_t op ) 
{
	
	size_t height_left = 0;
	size_t height_right = 0;

	assert(node);
	UNUSED( op );
	UNUSED( child_pos );

	if( node->child[LEFT] ) height_left = SetHeight( node->child[LEFT],  child_pos, op);
	if( node->child[RIGHT] ) height_right = SetHeight( node->child[RIGHT],  child_pos, op );
	puts("set_heiht_start");
	AvlPrintData( node);
	if (0  == FindNumChilds( node ) )
	{
		node->height = 0 ;
		return node->height;


	}
	node->height = height_right > height_left ? ++height_right : ++height_left;
	AvlPrintData( node);

	puts("set_heiht_end");

	return node->height;

	/*return height_right > height_left ? ++height_right : ++height_left;*/
}

/********************  SetHeight  ****************************/
/*
static void	SetHeight(avl_node_t* node, int child_pos, op_type_t op )
{
	assert(node);
	UNUSED( op );

	int height_left = 0;
	int height_right = 0;

	switch( FindNumChilds( node ) )
	{
		case 0:
			node->height = 0 ;
			break;
			
		case 1:
			printf("child_pos = %d \n", child_pos);
			node->height = (node->child[child_pos])->height + 1;
			break;	
		
		case 2:
			op = (size_t)INSERT;
			node->height = MAX( GetHeight( node->child[LEFT]) , 
								GetHeight( node->child[RIGHT]) )  +  1;
			break;
	}
}
*/
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
static avl_node_t * AuxAVLInsert(avl_t *tree,  avl_node_t *parent ,
         avl_node_t *curr_node, int res, avl_node_t *new_node,
          void* new_data,  op_type_t op)
{	
	int what_child = LEFT;
	avl_node_t *x = NULL;
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
	
		return new_node;
	}	
	
	res = tree->cmp_func( curr_node->data, new_data );
	what_child = res > 0 ? LEFT : RIGHT;

	x = AuxAVLInsert(tree, curr_node, curr_node->child[what_child], res,
				  new_node,  new_data, op );
	/*AvlPrintData( x);*/
	
	if(NULL != x && x->child[ !what_child ] == curr_node &&
		x != tree->root)
	{
					/*
					puts("find_INSERT_START");
					printf("what_child = %d \n", what_child);
					AvlPrintData( x);
					AvlPrintData( x->child[ !what_child ]);
					AvlPrintData( x->child[ what_child ]);

					AvlPrintData( parent);
					AvlPrintData( parent->child[!what_child]);
					AvlPrintData( parent->child[what_child]);
						*/
					/*parent->child[!what_child] = x;*/
					/* HANDLE RR parent*/
					if ( RIGHT == what_child &&
						x->child[ !what_child ] == parent->child[what_child] )
					{
						parent->child[what_child] = x;
					}
					else
					{
						parent->child[!what_child] = x;

					}
/*
					AvlPrintData( curr_node);
					AvlPrintData( parent);
					
					puts("find_INSERT_END");
*/					

	}
	  
	/*AvlPrintData( curr_node);		  */
	SetHeight( curr_node, what_child, op );
	/*AvlPrintData( curr_node->child[what_child]);*/
	/*printf(" BalancedFactor(curr_node)= %d\n " ,BalancedFactor(tree, curr_node) );*/
	/*
	printf(" BalancedFactor(curr_node->child[what_child])= %d\n " 
				,BalancedFactor(tree, curr_node->child[what_child]) );
				*/
	/*AvlPrintData( curr_node->child[what_child]);		*/
	/*printf(" BalancedFactor(curr_node)= %d\n " ,BalancedFactor(tree, curr_node) );*/
	/*AvlPrintData( curr_node);	*/
	/*printf(" BalancedFactor(parent)= %d\n " ,BalancedFactor(tree, parent) );*/
	/*AvlPrintData( parent);*/
	/*puts("hi111");	*/

	/*puts("hi1111");	*/
			/*SetHeight( curr_node, what_child, INSERT );*/
	return HandleRebalance( tree, parent, curr_node, what_child, op);
		/*SetHeight( curr_node, what_child, INSERT );*/
		/*SetHeight( curr_node, what_child, INSERT );*/
			/*			AvlPrintData( x);*/
						/*	AvlPrintData( grandmiser);*/
	
	
	/*
	if(balanced_broken)
	{
				puts("broken");
					balanced_broken = FALSE;
						AvlPrintData( grandmiser);
	}
		*/
	/*printf("after_HandleRebalance\n");*/
	/*grandmiser->child[LEFT] = parent;	 */ 
}
						 
/********************  HandleRebalance  ****************************/	
static avl_node_t *HandleRebalance( avl_t *tree, avl_node_t *parent
						 ,avl_node_t *curr_node, int what_child, op_type_t op)
{

	/*int perent_balance = 0, curr_node_balanced = 0;*/
	avl_node_t *x = NULL;
	assert( tree );
	assert( parent );
	/*assert( curr_node );*/
	printf("op = %d \n", op);
	/*
	if( NULL == parent )
	{
		return NULL;
	
	}
	*/
	if( NULL == curr_node )
	{
		return NULL;
	
	}

	/* RL */										
	if( -2 == BalancedFactor(tree, parent) && 
			 1 == BalancedFactor(tree, curr_node))
	{

			puts("RL");
			x = RightRotate(tree, curr_node, what_child, op);
				/*AvlPrintData( x);*/
			/*	AvlPrintData( parent);	*/
				parent->child[RIGHT] = x;

				/*SetHeight( parent, RIGHT, INSERT );*/
		/*	Aux_Pre_Print_Tree_Avl(tree, 0);*/
				/*		puts("hi11");	*/
		/*	printf(" BalancedFactor(parent)= %d\n " ,BalancedFactor(tree, parent) );*/
						/*AvlPrintData( parent);*/
						curr_node = x;
						
						Aux_Pre_Print_Tree_Avl(tree, 0);				
	}
	/* RR */									
	if( -2 >= BalancedFactor(tree, parent) && 
				 (-1 == BalancedFactor(tree, curr_node) || 
				 (0 == BalancedFactor(tree, curr_node))  ) )
	{
			puts("RR");
			
			puts("hi11112322");
					AvlPrintData( parent);
					AvlPrintData( parent->child[LEFT]);

					AvlPrintData( curr_node);
					AvlPrintData( curr_node->child[what_child]);

							puts("h1111213i2");	
				/*
				return RightRotate( parent, RIGHT );
				*/
				
		x = LeftRotate(tree, parent, RIGHT, op ); 
		/*grandmiser->child[LEFT] = x;*/
					/*puts("hi11112322");*/
					/*AvlPrintData( grandmiser);*/
							/*	puts("h1111213i2");	*/

							
			/*tree->root->child[LEFT] = x;*/
			
			return x;
	}

	/* LR */										
	if( 2 == BalancedFactor(tree, parent) && 
			 -1 == BalancedFactor(tree, curr_node))
	{

			puts("LR");
			x = LeftRotate(tree, curr_node, what_child, op);
				
				parent->child[LEFT] = x;

						curr_node = x;
						
						Aux_Pre_Print_Tree_Avl(tree, 0);
									puts("END_LR");				
	}
/*|| (0 == BalancedFactor(tree, curr_node)) */
	/* LL */										
	if( 2 == BalancedFactor(tree, parent) && 
				 (1 == BalancedFactor(tree, curr_node) 
				 || (0 == BalancedFactor(tree, curr_node))) )
	{
			puts("LL");
				
		x = RightRotate(tree, parent, LEFT, op ); 

			return x;
	}
	
	
	return x;	
					
}

/********************  RightRotate  ****************************/	
static avl_node_t *RightRotate(avl_t *tree, avl_node_t *y, int what_child, op_type_t op)
{
	avl_node_t *x = NULL, *tree_x_child = NULL;
	assert( y );
	puts("RightRotate");
	x = y->child[what_child]; /*what_child --> LEFT ? */
	tree_x_child = x->child[RIGHT];
	
	AvlPrintData( x);
	AvlPrintData( y);
		
	x->child[RIGHT] = y;
	y->child[what_child] = tree_x_child;
	/*
	if( op == REMOVE )
	{
		SetHeight( y, what_child, INSERT );
	}
	else 
	{
		SetHeight( y, what_child, REMOVE );	
		SetHeight( y, what_child, REMOVE );
	}
	*/
	
	SetHeight( y, what_child, REMOVE );
	/*	SetHeight( x, RIGHT, INSERT );*/
	SetHeight( x, RIGHT, op );
	/*AvlPrintData( y->child[what_child]);	*/	
	/*
	if( op == REMOVE )
	{
		SetHeight( y, LEFT, INSERT );
	}
	else 
	{
		SetHeight( y, LEFT, op );
	}
	*/	
	/*SetHeight( y, what_child, INSERT );*/
	if( y == tree->root )
	{
		puts("y_is_root_RightRotate");
		tree->root = x;
			SetHeight( y, what_child, REMOVE );
		/*SetHeight( curr_node, what_child, INSERT );*/
	}
	puts("END_RightRotate");
	return x;


}
/********************  LeftRotate  ****************************/	
static avl_node_t *LeftRotate(avl_t *tree, avl_node_t *x, int what_child, op_type_t op)
{
	avl_node_t *y = NULL, *tree_y_child = NULL;
	assert( x );
		UNUSED( op );
					puts("LeftRotate");
	printf("what_child = %d \n" , what_child);				
	y = x->child[what_child]; /*what_child --> LEFT ? */
	AvlPrintData( x);
	AvlPrintData( y);

	AvlPrintData( y);

	tree_y_child = y->child[LEFT];

	AvlPrintData( tree_y_child);
		AvlPrintData( y);
	y->child[LEFT] = x;
	x->child[what_child] = tree_y_child;
/*	IsLeftChild(x, tree_y_child);*/
	/*SetHeight( x, !IsLeftChild(x, tree_y_child), REMOVE );*/
	/*SetHeight( y, LEFT, INSERT );*/
	/*SetHeight( x, what_child, INSERT );*/
	
	/*SetHeight( y, LEFT, INSERT );*/
		/*SetHeight( x, what_child, REMOVE );*/
		/*SetHeight( y, LEFT, op );*/

	SetHeight( x, what_child, INSERT );
	SetHeight( y, LEFT, INSERT );
	/*
	if( op == REMOVE )
	{
		SetHeight( y, LEFT, INSERT );
	}
	else 
	{
		SetHeight( y, LEFT, op );
	}
	*/	
	AvlPrintData( y->child[LEFT]);		
	if( x == tree->root )
	{
		tree->root = y;
		SetHeight( x, what_child, REMOVE );
	}
				puts("END_LeftRotate");
	return y;
}
/********************  BalancedFactor  ****************************/	
static int BalancedFactor(avl_t *tree, avl_node_t *node)
{
	assert(tree);
	assert(node);
	
	return GetChildHeight(node, LEFT) - GetChildHeight(node, RIGHT);
	
}
/********************  GetChildHeight  ****************************/
static int GetChildHeight(avl_node_t *node, int child_pos)
{
	assert(node);
	return IsChildExist(node, child_pos) ? (int)GetHeight(node->child[child_pos]) : -1;

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
	AuxAVLInsert(tree, parent, curr_node, 0, new_node, (void*)data, INSERT);
	
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
	
	parent = curr_node;
	AuxAVLRemove(tree, parent, tree->root, 0, data, REMOVE);	

}

/********************  AuxAVLRemove  ****************************/
static avl_node_t *AuxAVLRemove(avl_t *tree,  avl_node_t *parent, avl_node_t
								 *curr_node, int res, 
								 void* data_to_remove, op_type_t op)
{	
	int what_child = LEFT, what_son = LEFT;
	avl_node_t *next_child = NULL, *parent2 = NULL;
	avl_node_t *x = NULL, *y = NULL;
	
	assert( tree );

	if(NULL == curr_node ) 
	{
		return NULL;
	}
	puts("ENTER_AUX_REMOVE");

	AvlPrintData( curr_node);
	AvlPrintData( parent);
	
	res = tree->cmp_func( curr_node->data, data_to_remove );
	
	what_child = res > 0 ? LEFT : RIGHT;
	
	printf("what_child = %d\n", what_child);
	printf("res = %d\n", res);
/*
	if (tree->root != curr_node)
	{
		parent->child[what_child] = next_child->child[LEFT];
	}
*/
	

	if( 0 == res ) /* the node to remove */
	{
	
		if (tree->root == curr_node)
			{
				parent = curr_node;

				/*parent->child[what_child] = next_child->child[LEFT];*/
			}
		res = tree->cmp_func(parent->data, curr_node->data );
		what_child = res > 0 ? LEFT : RIGHT;
		what_son = IsChildExist(curr_node, LEFT) ? LEFT : RIGHT;
		puts("ENTER_to_switch_remove");

		printf("what_child = %d\n", what_child);
		printf("res = %d\n", res);
		printf(" FindNumChilds(curr_node) = %d\n",  FindNumChilds(curr_node));

		switch(  FindNumChilds(curr_node) )
		{
			case NO_CHILDS:

				if( tree->root ==  curr_node)
				{
					tree->root = NULL;
				}
				
				else  
				{
					parent->child[what_child] = NULL;
					/*SetHeight( parent, !what_child, REMOVE );*/
				}

				free( curr_node );
				curr_node = NULL;

				break;
				
			case ONE_CHILD:

				if( tree->root ==  curr_node)
				{
					tree->root = curr_node->child[what_son];
				}
				
				else  
				{
					parent->child[what_child] = curr_node->child[what_son];
				}
				
				free( curr_node );
				curr_node = NULL;
				
				break;	
		
			case TWO_CHILDS:

			if (tree->root == curr_node)
			{
				parent = curr_node;

				/*parent->child[what_child] = next_child->child[LEFT];*/
			}
				/*AvlPrintData( next_child);*/
				AvlPrintData( curr_node);
				printf("IsLeftChild(parent, curr_node)_1 = %d\n",IsLeftChild(parent, curr_node));	

				AvlPrintData( parent);
				/*next_child = AvlNodeMax(&curr_node, curr_node->child[LEFT]);*/
				parent2 = curr_node;
				next_child = AvlNodeMax(&parent2, curr_node->child[LEFT]);
				what_child = IsLeftChild(parent2, next_child) ? LEFT: RIGHT;
				printf("IsLeftChild(parent2, next_child) = %d\n",IsLeftChild(parent2, next_child));	
				printf("what_child = %d\n",what_child);		
	
				AvlPrintData( next_child);
				AvlPrintData( curr_node);
				AvlPrintData( parent);

				AvlPrintData( parent2);
				
				curr_node->data = next_child->data;
				/*
				if (tree->root == curr_node)
				{
				parent = curr_node;

				}

				*/
				parent2->child[what_child] = next_child->child[LEFT];
				free(next_child);
				next_child = NULL;
				/*SetHeight( parent2, LEFT, REMOVE );*/

				SetHeight( curr_node, LEFT, REMOVE );

				if (tree->root == curr_node)
				{
					/*curr_node = curr_node->child[LEFT ];*/

					AvlPrintData( curr_node->child[LEFT ]);

					y = HandleRebalance( tree, curr_node->child[LEFT ],
							 (curr_node->child[LEFT ])->child[LEFT ], LEFT, op);
					puts("hii");
					AvlPrintData( y);

					curr_node->child[LEFT] = y;
					
				}
				else
				{
					y = HandleRebalance( tree, curr_node, curr_node->child[!what_child ], what_child, op);
					puts("hiiiiiiii+no_root");
					AvlPrintData( y);
					AvlPrintData( curr_node);
					AvlPrintData( parent);
					printf("IsLeftChild(parent, curr_node)_2 = %d\n",IsLeftChild(parent, curr_node));	
					what_child = IsLeftChild(parent, curr_node) ? LEFT: RIGHT;

					parent->child[what_child] = y;


				}
				/*SetHeight( curr_node, LEFT, REMOVE );*/
				break;
		}
		return curr_node;
	
		/*return curr_node ? curr_node: NULL;*/
	}
	

	x = AuxAVLRemove(tree, curr_node, curr_node->child[what_child],
						 res, data_to_remove, op );
	puts("what_x_return");
	AvlPrintData( x);
	AvlPrintData( curr_node);
	AvlPrintData( parent);
	

	printf("what_child = %d \n", what_child);
			 
	AvlPrintData( x);
		/*AvlPrintData( x->child[ !what_child ]);*/
		/*AvlPrintData( x->child[ what_child ]);*/

		AvlPrintData( parent);
		/*
		AvlPrintData( parent->child[!what_child]);
		AvlPrintData( parent->child[what_child]);
		*/
	if(NULL != x && x->child[ !what_child ] == curr_node->child[ what_child ] &&
	x != tree->root)
{
		puts("find_REMOVE_START");
		printf("what_child = %d \n", what_child);
		AvlPrintData( x);
		/*
		AvlPrintData( x->child[ !what_child ]);
		AvlPrintData( x->child[ what_child ]);
*/
		AvlPrintData( parent);
		/*
		AvlPrintData( parent->child[!what_child]);
		AvlPrintData( parent->child[what_child]);
*/
				/*parent->child[!what_child] = x;*/
				/* HANDLE RR parent*/
		
				if ( RIGHT == what_child &&
					x->child[ !what_child ] == curr_node->child[what_child] )
				{
					curr_node->child[what_child] = x;
				}
				else
				{
					curr_node->child[!what_child] = x;
		
				}		
				/*		
		if ( RIGHT == what_child &&
			x->child[ !what_child ] == parent->child[what_child] )
		{
			parent->child[what_child] = x;
		}
		else
		{
			parent->child[!what_child] = x;

		}
*/
		
			/*parent->child[!what_child] = x;*/


				AvlPrintData( curr_node);
				AvlPrintData( parent);
				puts("find_REMOVE_END");
				

}
	/*				 	  				  			  
	SetHeight( curr_node, what_child, op );
	puts("curr_node");
	AvlPrintData( curr_node);
	puts("curr_node->child[!what_child ]");
	AvlPrintData( curr_node->child[!what_child ]);
	puts("parent");	
	AvlPrintData( parent);	
	*/
	y = HandleRebalance( tree, curr_node, curr_node->child[!what_child ], what_child, op);
	puts("what_y_return");
	AvlPrintData( y);
	AvlPrintData( curr_node);

	return y;

}	

/*********************  AvlNodeMax  ****************************/
/*	
	Find the Max of node's sub tree 
*/
static avl_node_t* AvlNodeMax(avl_node_t **parent, avl_node_t* curr_node)
{
	assert(curr_node);
	assert(parent);
	assert(*parent);	

	if( NULL != curr_node->child[RIGHT] )
	{
		*parent = curr_node;
		curr_node = curr_node->child[RIGHT];
		AvlNodeMax( parent, curr_node);
		
		SetHeight( *parent, RIGHT, REMOVE );	
	}
	
	return curr_node;
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







