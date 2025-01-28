/******************************************************************************
*	Version 1.2
******************************************************************************/
#ifndef __BST_H__             /* __BST_H__ */
#define __BST_H__             /* __BST_H__ */

#include <stddef.h>             /* size_t */

typedef struct bst bst_t;
typedef struct bst_node bst_node_t;
/* May change - do not use it */
typedef struct bst_node *bst_iter_t; 


/******************************************************************************
* 
*   Description: Function to determine sorting method of sorted list
*   Arguments: 	* 'check_data' - current iterator data
*				* 'new_data' - data to be inserted to the list
*   Return: >0   if check_data is bigger than new data
*           <0 smaller  than new data
*           =0  or equal than new data
* 
*/
    typedef int( *cmp_func_t )(void* check_data , void* new_data );
/* 
******************************************************************************/

/******************************************************************************
*   Name: operation_func_t
*   Description: Function callback to modify all elements of the Binary search tree
*   Arguments: 	* 'data' - Node element data
*				* 'user_param' - Optional user parameter 
*   Complexity: O(n)
*   Return: Boolean value (success or fail)
******************************************************************************/
typedef int(*operation_func_t)(void *data, void *user_param);



/******************************************************************************
*
*       Name: BstCreate
*       Description: Create a new Binary search tree
*       Arguments: N\A
*       Complexity: system call complexity
*       Return: pointer to new bst or NULL on failure 
* 
******************************************************************************/
bst_t *BstCreate(cmp_func_t );



/******************************************************************************
*
*       Name: BstDestroy
*       Description: destroys all dynamically alloacated data from the tree.
*       Arguments: 	ptr to the binary search tree to be destroyed.
*       Complexity: O(n) + system call complexity
*       Return: N\A
*       Notes: If 'bst' is NULL, no operations will be performed
* 
******************************************************************************/
void BstDestroy(bst_t *bst);



 /******************************************************************************
*
*       Name: BstInsert
*       Description: creates a node from data and inserts it after the last node
*       Arguments: 	the tree to be insterted into and the data to be inserted into
*       the new node.
*       Complexity: O(log(n))
*       Return: Returns the iterator to the new node in case of success,
*               else, returns BstEnd() on failure
*       Notes:  Undefined behaviour if "bst" is NULL  
* 
******************************************************************************/
bst_iter_t BstInsert(bst_t *bst, const void *new_data);



 /******************************************************************************
*
*       Name: BstRemove
*       Description: Removes a node from the tree.
*       Arguments: 	An iterator to the node to be removed.
*       Complexity: O(log(n))
*       Return: Returns the iterator to the next element
*       Notes:      * Undefined behaviour if "what" is iter to 
*                     Dummy end ( BstEnd() ). Undefined if "what" is not 
*                     in the tree.
* 
******************************************************************************/
bst_iter_t BstRemove(bst_iter_t what);



/******************************************************************************
*
*       Name: BstIsEmpty
*       Description: checks if the tree is empty
*       Arguments: 	The tree to be examined, cast to const.
*       Complexity: O(1)
*       Return: 1 if the tree is empty (aside from the dummy), 0 otherwise.
*       Notes: Undefined behaviour if "bst" is NULL
* 
******************************************************************************/
int BstIsEmpty(const bst_t *bst);



/******************************************************************************
*
*       Name: BstSize
*       Description: counts the number of nodes in the tree
*       Arguments: The tree to be examined
*       Complexity: O(n)
*       Return: the size of the tree.
*       Notes:  undefined behaviour if tree is null.
* 
******************************************************************************/
size_t BstSize(const bst_t *bst);



/******************************************************************************
*
*       Name: BstFind
*       Description: finds an element that is searched for match based on a
*       compare function given by the user.
*       Arguments: 	tree to search in and data for compare function
*       Complexity: O(log(n))
*       Return: returns iter to found element on success, "BSTEnd" iter if not found
*       Notes:  Undefined behavior if bst is NULL
******************************************************************************/
bst_iter_t BstFind(const bst_t *bst, void *data_to_find);


/******************************************************************************
*
*       Name: BstForEach
*       Description: performs a particular operation on each node in the list 
*       within a range of nodes [start, end)
*       Arguments: 	iterators to the start and end of the range. 
*       Complexity: O(n)
*       Return: Success if an action was performed successfully for the entire range,
*               else, fail (TODO stop on first failure)
*       Notes: undefined behaviour if "start" and "end" belongs to different trees 
*              undefined behaviour if "end" is before "start"
*              undefined behaviour is "op_func" is NULL
* 
******************************************************************************/
int BstForEach(bst_iter_t start, bst_iter_t end,
                 operation_func_t op_func, void *user_param);



/******************************************************************************
*
*       Name: BstBegin
*       Description: returns iter to first valid element
*       Arguments: 	* 'const bst_t *bst' - The bst user wishes to create
*                   * iterator for
*       Complexity: O(log(n))
*       Return: returns iterator to the first valid element
*       Notes: * returns iter to BstEnd if tree is empty      
* 			   * undefined behaviour if "tree" is NULL
* 
******************************************************************************/
bst_iter_t BstBegin(const bst_t *bst);



/******************************************************************************
*
*       Name: BstEnd
*       Description: return iterator to the dummy node.
*       Arguments: 	* slist - pointer to the slist
*       Complexity: O(1)
*       Return: return iterator to the end of the tree
*       Notes:      * undefined behaviour if "tree" is NULL
* 
******************************************************************************/
bst_iter_t BstEnd(const bst_t *bst);



/******************************************************************************
*
*       Name: BstNext
*       Description: Gets the next node iterator of the current node
*       Arguments: 	* iterator
*       Complexity: O(log(n))
*       Return: Returns the next node. 
*       Notes: Undefined behaviour if "iter" is iter to Dummy end (BstEnd())
* 
******************************************************************************/
bst_iter_t BstNext(bst_iter_t iter);

/******************************************************************************
*
*       Name: BstPrev
*       Description: Gets the previous node iterator of the current node
*       Arguments: 	* iterator
*       Complexity: O(log(n))
*       Return: Returns the previous node
*       Notes: 
* 
******************************************************************************/
bst_iter_t BstPrev(bst_iter_t iter);

/******************************************************************************
*
*       Name: BstGetData
*       Description: Gets the data of a node
*       Arguments: 	* iterator 
*       Complexity: O(1)
*       Return: Returns the node data
*       Notes: Undefined behaviour if "iter" is iter to Dummy end (BstEnd())
* 
******************************************************************************/
void *BstGetData(bst_iter_t iter);



/******************************************************************************
*
*       Name: is_same_iter
*       Description: Checks if two iterators are pointing to the same node
*       Arguments:  * two iterators.
*       Complexity:  O(1)
*       Return: true if equal, else return false. 
*       Notes:      
*                   
* 
******************************************************************************/
int is_same_iter(bst_iter_t iter1, bst_iter_t iter2);



#endif                          /* __BST_H__ 
