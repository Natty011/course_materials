/******************************************************************************
*	Version 1.2
******************************************************************************/
#ifndef __SLIST_H__             /* __SLIST_H__ */
#define __SLIST_H__             /* __SLIST_H__ */

#include <stddef.h>             /* size_t */

typedef struct slist slist_t;
typedef struct slist_node slist_node_t;
/* May change - do not use it */
typedef struct slist_node *slist_iter_t; 


/******************************************************************************
*   Name: match_func_t
*   Description: Function callback for finding elements in a linked list
*   Arguments: 	* 'check_data' - Node element data to check
*				* 'user_param' - Optional user parameter
*   Return: Boolean value (true or false)
******************************************************************************/
typedef int(*match_func_t)(void *check_data, void *user_param );

/******************************************************************************
*   Name: operation_func_t
*   Description: Function callback to modify all elements of the linked list
*   Arguments: 	* 'data' - Node element data
*				* 'user_param' - Optional user parameter 
*   Complexity: O(n)
*   Return: Boolean value (success or fail)
******************************************************************************/
typedef int(*operation_func_t)(void *data, void *user_param);



/******************************************************************************
*
*       Name: SlistCreate
*       Description: Create a new singly linked list
*       Arguments: N\A
*       Complexity: depends on malloc
*       Return: Ptr to a new 'slist_t' struct
*       Notes:  return NULL if malloc fails
* 
******************************************************************************/
slist_t *SlistCreate(void);



/******************************************************************************
*
*       Name: SlistDestroy
*       Description: frees all dynamically alloacated data from the list.
*       Arguments: 	ptr to the list to be freed
*       Complexity: Complexity of free
*       Return: N\A
*       Notes: If 'slist' is NULL, no operations will be performed
* 
******************************************************************************/
void SlistDestroy(slist_t *slist);



 /******************************************************************************
*
*       Name: SlistInsertBefore
*       Description: creates a node from data and inserts it before a 
*       node given via iterator.
*       Arguments: 	the list to be insterted into, an iterator to the node 
*       before which we wish to insert, and the data to be inserted into the new
*       node.
*       Complexity: O(1)
*       Return: Returns the iterator to the new node in case of success,
*               else, returns SlistEnd() on failure
*       Notes:      Undefined behaviour if 'where' is not in the list.
* 
******************************************************************************/
slist_iter_t SlistInsertBefore(slist_t *slist, slist_iter_t where, const void *new_data);



 /******************************************************************************
*
*       Name: SlistRemove
*       Description: Removes a node from the list.
*       Arguments: 	An iterator to the node to be removed.
*       Complexity: O(1)
*       Return: Returns the iterator to the next element
*       Notes:      * Undefined behaviour if "what" is iter to 
*                     Dummy end ( SlistEnd() ). Undefined if "what" is not 
*                     in the list.
* 
******************************************************************************/
slist_iter_t SlistRemove(slist_iter_t what);



/******************************************************************************
*
*       Name: SlistIsEmpty
*       Description: checks if the list is empty
*       Arguments: 	The list to be examined, cast to const.
*       Complexity: O(1)
*       Return: 1 if the list is empty (aside from the dummy), 0 otherwise.
*       Notes: Undefined behaviour if "slist" is NULL
* 
******************************************************************************/
int SlistIsEmpty(const slist_t *slist);



/******************************************************************************
*
*       Name: SlistCount
*       Description: counts the number of nodes in the list
*       Arguments: The list to be examined
*       Complexity: Implamentation based!
*       Return: the size of the list.
*       Notes:  undefined behaviour if list is null.
* 
******************************************************************************/
size_t SlistCount(const slist_t *slist);



/******************************************************************************
*
*       Name: SlistFind
*       Description: finds an element that is searched for match based on a
*       match function given by the user.
*       Arguments: 	an iterators to the start and end of the desired serach range
*       a pointer to a match function (returns int, accepts data for comparison in 
*       void*), and data to perform comparison with.
*       Complexity: O(n)
*       Return: returns iter to found element on success, "end" iter on fail
*       Notes:  undefined behaviour if "start" and "end" belongs to different lists 
*               undefined behaviour if "end" is before "start"
*               undefined behaviour if "op_func" is NULL
* 
******************************************************************************/
slist_iter_t SlistFind(slist_iter_t start, slist_iter_t end,
                       match_func_t match_function, void *user_param);



/******************************************************************************
*
*       Name: SlistForEach
*       Description: performs a particular operation on each node in the list 
*       within a range of nodes.
*       Arguments: 	iterators to the start and end of the range. 
*       Complexity: O(n)
*       Return: Success if an action was performed successfully for the entire range,
*               else, fail.
*       Notes: undefined behaviour if "start" and "end" belongs to different lists 
*              undefined behaviour if "end" is before "start"
*              undefined behaviour is "op_func" is NULL
* 
******************************************************************************/
int SlistForEach(slist_iter_t start, slist_iter_t end,
                 operation_func_t op_func, void *user_param);



/******************************************************************************
*
*       Name: SlistBegin
*       Description: returns iter to first valid element
*       Arguments: 	* 'const slist_t *slist' - The list user wishes to create
*                   * iterator for
*       Complexity: O(1)
*       Return: returns iterator to the first valid element
*       Notes: * returns iter to SlistEnd if list is empty      
* 			   * undefined behaviour if "slist" is NULL
* 
******************************************************************************/
slist_iter_t SlistBegin(const slist_t *slist);



/******************************************************************************
*
*       Name: SlistEnd
*       Description: return iterator to the dummy node.
*       Arguments: 	* slist - pointer to the slist
*       Complexity: O(1)
*       Return: return iterator to the end of the list
*       Notes:      * undefined behaviour if "slist" is NULL
* 
******************************************************************************/
slist_iter_t SlistEnd(const slist_t *slist);



/******************************************************************************
*
*       Name: SlistNext
*       Description: Gets the next node iterator of the current node
*       Arguments: 	* iterator
*       Complexity: O(1)
*       Return: Returns the next node
*       Notes: Undefined behaviour if "what" is iter to Dummy end (SlistEnd())
* 
******************************************************************************/
slist_iter_t SlistNext(slist_iter_t iter);



/******************************************************************************
*
*       Name: SlistGetData
*       Description: Gets the data of a node
*       Arguments: 	* iterator 
*       Complexity: O(1)
*       Return: Returns the node data
*       Notes: Undefined behaviour if "what" is iter to Dummy end (SlistEnd())
* 
******************************************************************************/
void *SlistGetData(slist_iter_t iter);



/******************************************************************************
*
*       Name: SlistSetData
*       Description: Insert the data to the node given by the iterator
*       Arguments: 	* iter - iterator which the data need to be added to
*					* data - the data to be added
*       Complexity: O(1)
*       Return: Nothing
*       Notes: Undefined behaviour if "what" is iter to Dummy end (SlistEnd())
* 
******************************************************************************/
void SlistSetData(slist_iter_t iter, void *data);



/******************************************************************************
*
*       Name: IsItrEqual
*       Description: Checks if two iterators are pointing to the same node
*       Arguments:  * two iterators.
*       Complexity:  O(1)
*       Return: true if equal, else return false. 
*       Notes:      
*                   
* 
******************************************************************************/
int IsItrEqual(slist_iter_t iter1, slist_iter_t iter2);

/******************************************************************************
*
*       Name: SlistAppend
*       Description: Appends two slist together
*       Arguments:  * 'dest' - The main slist object
*                   * 'src' - The concatinated slist , 
*       Complexity: O(1)
*       Return: Returns the start of the slist ('dest')
*       Notes: Undefined behaviour if 'slist' is a NULL object
*              src remains a valid empty slist.
******************************************************************************/

void SlistAppend(slist_t *dest, slist_t *src);


#endif                          /* __SLIST_H__ */
