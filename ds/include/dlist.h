/******************************************************************************
*	Version 2.1
******************************************************************************/
#ifndef __DLIST_H__     /* __DLIST_H__      */
#define __DLIST_H__     /* __DLIST_H__      */

#include <stddef.h>     /* size_t           */
#include "aux_func.h"

typedef struct dlist dlist_t;

/* might be changed, do not use it */
typedef struct dlist_node* dlist_iter_t;

/******************************************************************************
*
*       Description: Creates a doubly linked list object
*       Arguments: N\A
*       Complexity:
*       Return: A new empty doubly linked list object
* 
* 
*/      dlist_t* DListCreate( void );
/*
******************************************************************************/

/******************************************************************************
*
*       Description: Destroys a doubly linked list object
*       Arguments: 'dlist' - Doubly linked list object to delete
*       Complexity: Dependant on system call complexity
*       Return: None
*       Notes: If 'dlist' is NULL, no operations will be performed
* 
*/      void DListDestroy( dlist_t* dlist );
/*
******************************************************************************/

/******************************************************************************
*
*       Description: 
*       Arguments: 
*       Complexity: O(n)
*       Return: Undefined behaviour If 'dlist' is NULL
* 
*/      size_t DListCount(const dlist_t* dlist );
/* 
******************************************************************************/

/******************************************************************************
*
*       Description: 
*       Arguments: 
*       Complexity: O(1)
*       Return: Undefined behaviour If 'dlist' is NULL
* 
*/      int DListIsEmpty( const dlist_t* dlist );
/* 
******************************************************************************/

/******************************************************************************
*
*       Description: 
*       Arguments: 
*       Complexity: O(1)
*       Return: Undefined behaviour If 'dlist' is NULL
*               returns DListEnd() in case of empty list
* 
*/      dlist_iter_t DListBegin( const dlist_t* dlist );
/* 
******************************************************************************/


/******************************************************************************
*
*       Description: 
*       Arguments: 
*       Complexity: O(n)
*       Return: Undefined behaviour If 'dlist' is NULL. 
*               iter to dummy node of dlist.
* 
*/      dlist_iter_t DListEnd( const dlist_t* dlist );
/* 
******************************************************************************/

/******************************************************************************
*
*       Description: return iterator to the next node in the dlist
*       Arguments: iter - iterator to the current node in the dlist	
*       Complexity: O(1)
*       Return: return iterator to the next node in the dlist
*       Notes: Undefined behaviour if "iter" is iter to Dummy end (DlistEnd())
* 
*/      dlist_iter_t DListNext(dlist_iter_t iter );
/* 
******************************************************************************/

/******************************************************************************
*
*       Description: 
*       Arguments: iter - iterator to the current node in the dlist	
*       Complexity: O(1)
*       Return :  iterator to the previous node in the dlist
*       Notes: Undefined behaviour if "iter" is iter to first element (DlistBegin()). 
* 
*/      dlist_iter_t DListPrev(dlist_iter_t iter );
/* 
******************************************************************************/

/******************************************************************************
*
*       Description: 
*       Arguments: 
*       Complexity: O(1)
*       Return: return 1 if the iterators are equal, and 0 otherwise
* 
*/      int DListIterIsEqual(dlist_iter_t iter1,  dlist_iter_t iter2 );
/* 
******************************************************************************/

/******************************************************************************
*
*       Description: 
*       Arguments: 
*       Complexity: O(1)
*       Return: Undefined behaviour if "iter" is iter to Dummy end (DlistEnd())
* 
*/      void* DListGetData( dlist_iter_t iter );
/* 
******************************************************************************/

/******************************************************************************
*
*       Name: DlistSetData
*       Description: Insert the data to the node given by the iterator
*       Arguments: 	* iter - iterator which the data need to be added to
*					* data - the data to be added
*       Complexity: O(1)
*       Return: Nothing
*       Notes: Undefined behaviour if "what" is iter to Dummy end (DlistEnd())
*       
*/      void DListSetData(dlist_iter_t iter, const void *data);
/* 
******************************************************************************/

/******************************************************************************
*
*       Description: 
*       Arguments: 
*       Complexity: O(1)
*       Return: iter to new element or DListEnd on failure
*               undefined behaviour if "dlist" is NULL or "where" doesn't 
*               belong to "dlist" 
* 
*/      dlist_iter_t DListInsertBefore( dlist_t* dlist , dlist_iter_t where,
                                        const void *data );
/*
******************************************************************************/

/******************************************************************************
*
*       Description: Removes a node from a linked list
*       Arguments: 'what' - The iterator to remove
*       Complexity: O(1)
*       Return: Returns the next iterator after the 'what' iterator
*       Notes: Undefined behaviour if "what" is iter to 
*                     Dummy end ( DlistEnd() ). Undefined if "what" is not 
 *                    in the list.
*/      dlist_iter_t DListRemove( dlist_iter_t what );
/*
******************************************************************************/

/******************************************************************************
*
*       Description: pushes a node to the start of the list
*       Arguments: dlist - the list to push to 
*                  data - pointer for data to enter
*       Complexity: O(1)
*       Return: 1- if succeeded , 0 - if failed 
* 
*/      dlist_iter_t DListPushFront( dlist_t* dlist , const void* data );
/*
******************************************************************************/

/******************************************************************************
*
*       Description: Adds a node to the end of the list
*       Arguments: 'dlist' - The list to push the element to
*                  'data' - Data of the new node
*       Complexity: O(1)
*       Return: iter to new element or DListEnd on failure
* 
*/      dlist_iter_t DListPushBack( dlist_t* dlist , const void* data );
/*
******************************************************************************/

/******************************************************************************
*
*       Description: Remove the first element from the list
*       Arguments: 'dlist' - Pointer to the list
*       Complexity: O(1)
*       Return: void* data of current iterator
* 
*/      void *DListPopFront( dlist_t* dlist );
/* 
******************************************************************************/

/******************************************************************************
*
*       Description: Remove the last element from the list 
*       Arguments: 'dlist' - Pointer to the list
*       Complexity: O(1) 
*       Return: void* data of current iterator
* 
*/      void *DListPopBack( dlist_t* dlist );
/* 
******************************************************************************/ 

/******************************************************************************
*
*       Description: Applies a user specific operation function on all of
*       the linked list's element's data
*       Arguments: 'start', 'end' are iterators indicating the start and the
*       end of the range to search.
*       'op_func' user created function used to run on all the element's data
*       'user_param' user parameter for the operation function
*       Complexity: O(n)
*       Return: Success (1) if an action was performed successfully for the
*               entire range, else returns failure (0).
*       Notes:  undefined behaviour if "start" and "end" belongs to other lists
*               undefined behaviour if "end" is before "start"
*               undefined behaviour if "op_func" is NULL
* 
*/    int DListForEach( dlist_iter_t start , dlist_iter_t end ,
                        operation_func_t op_func , void* user_param );
/* 
******************************************************************************/
                    
/******************************************************************************
*
*       Description: Finds the first element where it's data successfully
*                    matched with 'match_func'
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
*/       dlist_iter_t DListFind( dlist_iter_t start , dlist_iter_t end ,
                                 match_func_t match_func , void* user_param );
/* 
******************************************************************************/

/******************************************************************************
*
*       Description: Applies find on every element in range [start:end) and
*       inserts them to new_dlist.
*       Arguments: 'start', 'end' are iterators indicating the start and the
*       end of the range to search.
*       'match_func' user created function used to find the elements
*       'user_param' user parameter for the match function
*       'match_dlist' created by the user for the matched nodes to be inserted
*       Complexity: O(n)
*       Return: int, SUCCESS 0 / FAILED (did not check every element) 1
*       Notes:  undefined behaviour if "start" and "end" belongs to other lists
*               undefined behaviour if "end" is before "start"
*               undefined behaviour if "match_func" is NULL
* 
* 
*/      int DListMultiFind( dlist_iter_t start , dlist_iter_t end ,
                            match_func_t match_func , void* user_param ,
                            dlist_t* match_dlist );
/* 
******************************************************************************/

/******************************************************************************
*
*       Description: Inserts [from:to) before where.
*       Arguments: 'where' - The position to insert the splice into
*       'from', 'to' the specified splice to move to the list
*       Complexity: O(1)
*       Return: DListPrev(where) ---end of the original insrted slice --- 
*
*/       dlist_iter_t DListSplice ( dlist_iter_t where , dlist_iter_t from ,
                                    dlist_iter_t to );
                          
/******************************************************************************/

#endif /* __DLIST_H__      */
