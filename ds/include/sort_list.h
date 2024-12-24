/******************************************************************************
*	Version 3.6
******************************************************************************/
#ifndef __SORT_LIST_H__    
#define __SORT_LIST_H__    

#include <stddef.h>     /* size_t */
#include "dlist.h"

typedef struct sort_list sort_list_t;

/* might be changed, do not use it */
typedef struct sort_list_iter
{
    dlist_iter_t iter;
    
    #ifndef NDEBUG
        sort_list_t* list;
    #endif
} sort_list_iter_t;


/******************************************************************************
* 
*   Description: Function to determine sorting method of sorted list
*   Arguments: 	* 'check_data' - current iterator data
*				* 'new_data' - data to be inserted to the list
*   Return: >0 , <0 , =0 if check_data is bigger(after), smaller(before) or equal than new data
* 
*/
#ifndef __CMP_FUNC_T__   
#define __CMP_FUNC_T__
    typedef int( *cmp_func_t )(void* check_data , void* new_data );
#endif /* __CMP_FUNC_T__ */
/* 
******************************************************************************/

/******************************************************************************
* 
*   Description: Function callback for finding elements in a linked list
*   Arguments: 	* 'check_data' - Node element data to check
*				* 'user_param' - Optional user parameter
*   Return: Boolean value ( true = 1 or false = 0 )
* 
*/  
#ifndef __MATCH_FUNC_T__   
#define __MATCH_FUNC_T__
	typedef int( *match_func_t )(void* check_data , void* user_param );
#endif /* __MATCH_FUNC_T__ */
/* 
******************************************************************************/

/******************************************************************************
* 
*   Description: Function callback to modify all elements of the linked list
*   Arguments: 	* 'data' - Node element data
*				* 'user_param' - Optional user parameter 
*   Complexity: O(n)
*   Return: Boolean value ( success = 0 or fail = 1 )
* 
*/  
#ifndef __OPERATION_FUNC_T__   
#define __OPERATION_FUNC_T__
	typedef int( *operation_func_t )(void* data , void* user_param );
#endif /* __OPERATION_FUNC_T__ */
/*
******************************************************************************/


/******************************************************************************
*
*       Description: Creates a doubly linked list object
*       Arguments: Pointer to sort function provided by user.
*       Complexity: System dependant.
*       Return: A new empty sorted list  object on success or NULL
*       on failure.
* 
* 
*/   sort_list_t* SortlistCreate( cmp_func_t sort_func );
/*
******************************************************************************/

/******************************************************************************
*
*       Description: Destroys a sorted list object
*       Arguments: 'sort_list' - Sorted list object to delete
*       Complexity: O(n)
*       Return: None
*       Notes: If 'sort_list' is NULL, no operations will be performed
* 
*/      void SortlistDestroy( sort_list_t* sort_list );
/*
******************************************************************************/

/******************************************************************************
*
*       Description: Counts amount of valid elements in list.
*       Arguments: sort_list - pointer to sorted list
*       Complexity: O(n)
*       Return: size_t - amount of valid elements in list. 0 when empty.
*       Notes: Undefined behaviour if sort_list is NULL.
* 
*/    size_t SortlistSize(const sort_list_t* sort_list);
/* 
******************************************************************************/

/******************************************************************************
*
*       Description: Checks if list is empty or not.
*       Arguments: sort_list - pointer to sorted list.
*       Complexity: O(1)
*       Return: true = 1 for empty and false = 0 otherwise.
*       Notes: Undefined behaviour If 'sort_list' is NULL
* 
*/      int SortlistIsEmpty(const sort_list_t* sort_list);
/* 
******************************************************************************/

/******************************************************************************
*
*       Description: Makes iterator pointing to next of head
*       Arguments: sort_list - pointer to sorted list
*       Complexity: O(1)
*       Return: Undefined behaviour If 'sort_list' is NULL
*               returns SRLEnd() in case of empty list
* 
*/      sort_list_iter_t SortlistBegin(const sort_list_t* sort_list);
/* 
******************************************************************************/


/******************************************************************************
*
*       Description: Make iterator pointing to tail.
*       Arguments: sort_list - pointer to list
*       Complexity: O(1)
*       Return: iter to dummy node of sort_list.
*               Undefined behaviour If 'sort_list' is NULL. 
*
*/      sort_list_iter_t SortlistEnd(const sort_list_t* sort_list);
/* 
******************************************************************************/

/******************************************************************************
*
*       Description: Makes iterator to the node next of iter.
*       Arguments: iter - iterator to the current node in the dlist	
*       Complexity: O(1)
*       Return: return iterator to the next node in the dlist
*       Notes: If applied on SortlistEnd(), will return NULL.
* 
*/      sort_list_iter_t SortlistNext(sort_list_iter_t iter);
/* 
******************************************************************************/

/******************************************************************************
*
*       Description: Makes iterator to the node before iter.
*       Arguments: iter - iterator to the current node in the dlist	
*       Complexity: O(1)
*       Return :  iterator to the previous node in the dlist
*       Notes: undefined behaviour If applied on SortlistBegin()
* 
*/      sort_list_iter_t SortlistPrev(sort_list_iter_t iter);
/* 
******************************************************************************/

/******************************************************************************
*
*       Description: Checks if two iterators are equal or not.
*       Arguments: iter1, iter2.
*       Complexity: O(1)
*       Return: return true = 1 if the iterators are equal, and false = 0 otherwise
* 
*/      int SortlistIterIsEqual( sort_list_iter_t iter1 , sort_list_iter_t iter2 );
/* 
******************************************************************************/

/******************************************************************************
*
*       Description: Returns the data of an iterator
*       Arguments: 'iter' - The current iterator
*       Complexity: O(1)
*       Return: Undefined behaviour if "iter" is iter to Dummy end (SRLEnd())
* 
*/      void* SortlistGetData( sort_list_iter_t iter );
/* 
******************************************************************************/

/******************************************************************************
*
*       Description: Inserts an element into a sorted list
*       Arguments: 'sort_list' - The sorted list to insert to
*       Complexity: O(n)
*       Return: iter to new element added to the list, or 
*       sort_list end if insertion failed* 
* 
*/      sort_list_iter_t SortlistInsert( sort_list_t* sort_list ,const void *data );
/*
******************************************************************************/

/******************************************************************************
*
*       Description: Removes a node from a sorted list
*       Arguments: 'what' - The iterator to remove
*       Complexity: O(1)
*       Return: Returns the next iterator after the 'what' iterator
*       Notes: Undefined behaviour if "what" is iter to 
*                     Dummy end ( SRLEnd() ).
*/      sort_list_iter_t SortlistRemove( sort_list_iter_t what );
/*
******************************************************************************/

/******************************************************************************
*
*       Description: Remove the first element from the list
*       Arguments: 'dlist' - Pointer to the list
*       Complexity: O(1)
*       Return: void* data of current iterator
*       Note: Undefined behaviour if list is empty
* 
*/      void* SortlistPopFront( sort_list_t* sort_list );
/* 
******************************************************************************/

/******************************************************************************
*
*       Description: Remove the last element from the list 
*       Arguments: 'dlist' - Pointer to the list
*       Complexity: O(1) 
*       Return: void* data of current iterator
*       Note: Undefined behaviour if list is empty

*/      void* SortlistPopBack( sort_list_t* sort_list );
/* 
******************************************************************************/ 

/******************************************************************************
*
*       Description: Applies a user specific operation function on all of
*       the sorted list's element's data within the range [start, end).
*       Arguments: 'start', 'end' are iterators indicating the start and the
*       end of the range to search.
*       'op_func' user created function used to run on all the element's data
*       'user_param' user parameter for the operation function
*       Complexity: O(n)
*       Return: Success (0) if an action was performed successfully for the
*               entire range, else returns failure (1).
*       Notes:  undefined behaviour if "start" and "end" belongs to other lists
*               undefined behaviour if "end" is before "start"
*               undefined behaviour if "op_func" is NULL
* 
*/      int SortlistForEach( sort_list_iter_t start, sort_list_iter_t end,
                          operation_func_t op_func , void* user_param );
/* 
******************************************************************************/
                    
/******************************************************************************
*
*       Description: Finds the first element where it's data successfully
*                    matched with 'match_func' within the range [start, end).
*       Arguments: 'start', 'end' are iterators indicating the start and the
*       end of the range to search.
*       'match_func' user created function used to find the elements
*       'user_param' user parameter for the match function
*       Complexity: O(n)
*       Return: returns iter to found element on success, "end" iter on fail
*       Notes:  undefined behaviour if "start" and "end" belongs to other lists 
*               undefined behaviour if "end" is before "start"
*               undefined behaviour if "match_func" is NULL
* 
* 
*/      sort_list_iter_t SortlistFindIf( sort_list_iter_t start, sort_list_iter_t end,
                                match_func_t match_func , void* user_param );
/* 
******************************************************************************/

/******************************************************************************
*
*       Description: Finds the first element where it's data successfully
*                    matched with 'match_func' within the range [start, end).
*       Arguments: 'start', 'end' are iterators indicating the start and the
*       end of the range to search. NOT INCLUDING END!
*       'user_param' user parameter for the match function
*       Complexity: O(n)
*       Return: returns iter to found element on success, "end" iter on fail
*       Notes:  undefined behaviour if "start" and "end" belongs to other lists 
*               undefined behaviour if "end" is before "start"
* 
* 
*/      sort_list_iter_t SortlistFind( sort_list_t* sort_list , sort_list_iter_t start ,
                                        sort_list_iter_t end , void* user_param );
/* 
******************************************************************************/

/******************************************************************************
*
*       Description: Combines two sorted lists together
*       Arguments: * 'dest' - The destination list
*                  * 'src' - The source list
*       Complexity: O(n)
*       Return: N\A
*       Note: Undefined behaviour if dest & src are same list.
*/      void SortlistMerge( sort_list_t *dest , sort_list_t *src );
/* 
******************************************************************************/

#endif /* __DLIST_H__      */
