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

int destroy_check_avl = SUCCESS; /* extern */

/***************End of struct and enum declaration *******/

/***********Functions declaration*******/
static void AuxAVLDestroy(avl_node_t *node);
static void AuxAVLInsert(avl_t *tree, avl_node_t *par, avl_node_t *curr_node,
						 int res, avl_node_t *new_node, void* new_data);

#ifdef PRINTS
void *AvlGetData(avl_node_t *node);
void AvlPrintData(avl_node_t *node);

void Pre_Print_Tree_Avl(avl_node_t* root, avl_t *avl, int level);
void Aux_Pre_Print_Tree_Avl(avl_t *avl, int level);
#endif
/**********End of functions declaration *******/

/***********Static Functions definition*******/


/***********End Of Static Functions definition*******/

/********************  AuxAVLDestroy  ****************************/
static void AuxAVLDestroy(avl_node_t *node)
{
	if(NULL != node )
	{
		AuxAVLDestroy(node->child[LEFT] );
		AuxAVLDestroy(node->child[RIGHT] );
		/*node->child[LEFT] = node->child[RIGHT] = NULL;*/
		free( node );
		node = NULL;

	}
}

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
/*
size_t AVLSize(const avl_t* tree)
{
	assert( tree );
}
*/
/********************  AuxAVLInsert  ****************************/
static void AuxAVLInsert(avl_t *tree,  avl_node_t *par ,avl_node_t *curr_node,
						int res, avl_node_t *new_node, void* new_data)
{	
	assert( tree );

	if(NULL == curr_node ) 
	{
		
		if( AVLIsEmpty(tree) )
		{
			tree->root = new_node;
		}
		
		else  
		{
			par->child[res < 0] = new_node;	
		}

		new_node->child[LEFT] = NULL;
		new_node->child[RIGHT] = NULL;
		new_node->height = 0;	
	
		return;
	}	
	
	res = tree->cmp_func( curr_node->data, new_data );

	AuxAVLInsert(tree, curr_node, curr_node->child[res < 0], res,
				  new_node,  new_data );
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
	
	printf("%d\n",  *(int*)AvlGetData(node ) );
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


/*
static void AuxAVLDestroy(avl_node_t *node)
{
	assert ( node );
	
	if(NULL != node )
	{
		AuxAVLDestroy(node->child[LEFT] );
		AuxAVLDestroy(node->child[RIGHT] );
		
		free( node );
		node = NULL;
	}
}

*/







