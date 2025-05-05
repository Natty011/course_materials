/******************************************************************************
*	Version 1.1
******************************************************************************/
#ifndef __PQUEUE_H__    /* __PQUEUE_H__ */
#define __PQUEUE_H__    /* __PQUEUE_H__ */   

#include <stddef.h>     /* size_t       */

#include "sort_list.h"
#include "aux_func.h"

typedef struct pqueue pqueue_t;

/******************************************************************************
* 
*   Description: Function to determine sorting method of sorted list
*   Arguments: 	* 'check_data' - current iterator data
*				* 'new_data' - data to be inserted to the list
*   Return:     * >0 - 'check_data' has lower priority over 'user_param'
*               * =0 - 'check_data' has the same priority as 'user_param'
*               * <0 - 'check_data' has higher priority over 'user_param'
*
*/	typedef cmp_func_t priority_func_t;
/* 
******************************************************************************/

/******************************************************************************
*
*       Description: Creates a priority queue object
*       Arguments: Pointer to a priority function
*       Complexity: Dependant on system complexity
*       Return: A new empty priority queue, returns NULL on failure
*
*/      pqueue_t *PQueueCreate(priority_func_t priority);
/*
******************************************************************************/

/******************************************************************************
*
*       Description: Destroys a priority queue object
*       Arguments: 'pqueue' - The priority queue object to destroy
*       Complexity: Dependant on system complexity
*       Return: N\A
*       Notes: If 'pqueue' is NULL, no operations will be performed
* 
*/      void PQueueDestroy(pqueue_t *pqueue);
/*
******************************************************************************/

/******************************************************************************
*
*       Description: Enqueues data into the priority queue
*       Arguments: 'pqueue' - The priority queue to enqueue to
*       Complexity: O(n)
*       Return: Returns success (0), on failure, returns (1)
*       Notes: Undefined behaviour If 'pqueue' is NULL
* 
*/      int PQueueEnqueue(pqueue_t* pqueue, const void* data);
/*
******************************************************************************/

/******************************************************************************
*
*       Description: Dequeues the highest priority data from the queue
*       Arguments: 'pqueue' - The priority queue to dequeue from
*       Complexity: O(1)
*       Return: The data from the dequeued element
*       Notes: Undefined behaviour If 'pqueue' is NULL
* 
*/      void* PQueueDequeue(pqueue_t* pqueue);
/*
******************************************************************************/

/******************************************************************************
*
*       Description: Get the data of the highest priority element in the queue
*       Arguments: 'pqueue' - The priority queue to peek
*       Complexity: O(1)
*       Return: The data of the highest priority element
*       Notes: Undefined behaviour If 'pqueue' is NULL
* 
*/      void* PQueuePeek(const pqueue_t* pqueue);
/*
******************************************************************************/

/******************************************************************************
*
*       Description: Checks if a priority queue is empty
*       Arguments: 'pqueue' - The priority queue to check
*       Complexity: O(1)
*       Return: Returns 'TRUE' (1) if empty, else returns 'FALSE' (0)
*       Notes: Undefined behaviour If 'pqueue' is NULL
* 
*/      int PQueueIsEmpty(const pqueue_t* pqueue);
/*
******************************************************************************/

/******************************************************************************
*
*       Description: Calculates the size of a priority queue
*       Arguments: 'pqueue' - The priority queue to check
*       Complexity: O(n)
*       Return: Returns the number of elements in the priority queue
*       Notes: Undefined behaviour If 'pqueue' is NULL
* 
*/      size_t PQueueSize(const pqueue_t* pqueue);
/*
******************************************************************************/

/******************************************************************************
*
*       Description: Erases an element from a priority queue
*       Arguments: 'pqueue' - The priority queue to delete from
*       Complexity: O(n)
*       Return: N\A
*       Notes: Undefined behaviour If 'pqueue' is NULL
*              Undefined behaviour If 'match_func' is NULL
* 
*/      void PQueueErase(pqueue_t* pqueue, 
                         match_func_t match_func, const void* user_param);
/*
******************************************************************************/

/******************************************************************************
*
*       Description: Clears all the elements from a priority queue
*       Arguments: 'pqueue' - The priority queue to clear
*       Complexity: O(n)
*       Return: N\A
*       Notes: Undefined behaviour If 'pqueue' is NULL
* 
*/      void PQueueClear(pqueue_t* pqueue);
/*
******************************************************************************/

#endif                  /* __PQUEUE_H__ */
