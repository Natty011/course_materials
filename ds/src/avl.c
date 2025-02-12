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
typedef struct avl_node avl_node_t;

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


/**********End of functions declaration *******/

/***********Static Functions definition*******/


/***********End Of Static Functions definition*******/

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

/********************  AuxAVLDestroy  ****************************/
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
	
	if( TRUE != AVLIsEmpty(tree) )
	{
	   destroy_check_avl = OPERATION_FAIL;
	}
	
	free(tree);
	tree = NULL;
	
}	





