/******************************************************************************
*	Version 0.15
*   Last Updated:   12/2/2025
*                   13:51
******************************************************************************/
#ifndef __AVL_H__		/* __AVL_H__    */
#define __AVL_H__		/* __AVL_H__    */

#include <stddef.h>		/* size_t		*/

typedef struct avl avl_t;
typedef struct avl_node avl_node_t;
/***************************************
* Traversal type enum used in 'ForEach'
***************************************/
enum avl_traversal_order
{
    IN_ORDER = 0,
    PRE_ORDER = 1,
    POST_ORDER = 2
};

/******************************************************************************
* 
*   Description: Function to compare two data values
*   Arguments: 	* 'check_data' - Current node data
*   			* 'new_data' - Data to compare to
*   Return: Comparison value
*           >0  - 'check_data' is larger than 'new_data'
*           <0  - 'check_data' is smaller than 'new_data'
*           ==0 - 'check_data' is equal to 'new_data'
* 
*/
    typedef int(*cmp_func_t)(const void* check_data, const void* new_data);
/* 
******************************************************************************/

/******************************************************************************
* 
*   Description: Function callback to modify all elements of the linked list
*   Arguments: 	* 'data' - Node element data
*	            * 'user_param' - Optional user parameter 
*   Return: Boolean value ( success = 0 or fail = 1 )
* 
*
*/  typedef int(*op_func_t)(void* data, void* user_param);
/*
******************************************************************************/

/******************************************************************************
*
*       Description: Creates an 'AVL' tree
*       Arguments: 'cmp_func' - Function to determine order of the tree
*       Return: New AVL tree, or NULL if failed 
* 
*/      avl_t *AVLCreate(cmp_func_t cmp_func);
/*
******************************************************************************/

/******************************************************************************
*
*       Description: Destroys an AVL tree
*       Arguments: 'tree' - Tree to destroy
*       Return: N\A
*       Notes: If 'tree' is NULL, no operation will be performed
* 
*/      void AVLDestroy(avl_t *tree);
/*
******************************************************************************/

/******************************************************************************
*
*       Description: Removes a node from the AVL tree
*       Arguments: 'tree' - Tree to remove data from
*                  'data' - Data to use with comparison function to find node
*       Return: N\A
*       Complexity: O(log n)
* 
*/      void AVLRemove(avl_t *tree, void *data);
/*
******************************************************************************/

/******************************************************************************
*
*       Description: Inserts a new node in the AVL tree
*       Arguments: 'tree' - Tree to insert the data to
*                  'data' - Data to insert into the new node
*       Return: SUCCESS (0) or FAILURE (1)
*       Complexity: O(log n)
*       Notes
* 
*/      int AVLInsert(avl_t *tree, void *data);
/*
******************************************************************************/

/******************************************************************************
*
*       Description: Get the full height of the AVL tree
*       Arguments: 'tree' - Tree to measure
*       Return: Height of the tree
*       Complexity: O(1)
* 
*/      size_t AVLHeight(const avl_t* tree);
/*
******************************************************************************/

/******************************************************************************
*
*       Description: Get the size of the AVL tree
*       Arguments: 'tree' - Tree to measure
*       Return: Number of nodes in the AVL tree
*       Complexity: O(n)
* 
*/      size_t AVLSize(const avl_t* tree);
/*
******************************************************************************/

/******************************************************************************
*
*       Description: Check if AVL tree is empty or not
*       Arguments: 'tree' - Tree to check
*       Return: TRUE (1) if empty, FALSE (0) if not
*       Complexity: O(1)
* 
*/      int AVLIsEmpty(const avl_t* tree);
/*
******************************************************************************/

/******************************************************************************
*
*       Description: Finds data in tree
*       Arguments: 'tree' - The tree to search
*                  'data' - Data to use with the comparison function
*       Return: Returns the node data as is if successful, or NULL
*       Complexity: O(log n)
* 
*/      void *AVLFind(avl_t *tree, const void *data);
/*
******************************************************************************/

/******************************************************************************
*
*       Description: Iterates over every node of an AVL tree
*       Arguments: 'tree' - The tree to iterate on
*                  'op_func' - Operation function to execute on the node data
*                  'user_param' - Optional user parameter
*                  'order' - Traversal method through the tree
*       Return: SUCCESS (0) or FAILURE (1) if an execution has failed
*       Notes: 'traversal_order' uses 'enum avl_traversal_order' to pick the
*              traversal method of the for-each's iterations
* 
*/      int AVLForEachInOrder(avl_t *tree, op_func_t op_func, 
                              void *user_param, int traversal_order);
/*
******************************************************************************/

#endif                   /* __AVL_H__	*/

#ifdef PRINTS
/*
void Pre_Print_Tree(bst_node_t* root, bst_t *bst, int level);
void Aux_Pre_Print_Tree(bst_t *bst, int level);
*/
void *AvlGetData(avl_node_t *node);
void AvlPrintData(avl_node_t *node);
#endif
