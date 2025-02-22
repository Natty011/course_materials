/******************************************************************************
*	Version 1.1
******************************************************************************/
#ifndef __PQUEUE_H__    /* __PQUEUE_H__ */
#define __PQUEUE_H__    /* __PQUEUE_H__ */   

#include <stddef.h>     /* size_t       */

#include "heap.h"
#include "aux_func.h"

typedef struct heap_pq heap_pq_t;

/******************************************************************************
* 
*   Description: Function to determine sorting method of sorted list
*   Arguments: 	* 'check_data' - current iterator data
*				* 'new_data' - data to be inserted to the list
*   Return:     * >0 - 'check_data' has lower priority over 'user_param'
*               * =0 - 'check_data' has the same priority as 'user_param'
*               * <0 - 'check_data' has higher priority over 'user_param'
*
*/	typedef expand_cmp_func_t priority_func_t;
/* 
******************************************************************************/

/******************************************************************************
*
*       Description: Creates a priority queue object
*       Arguments: Pointer to a priority function
*       Complexity: Dependant on system complexity
*       Return: A new empty priority queue, returns NULL on failure
*
*/      heap_pq_t *HeapPQueueCreate(priority_func_t priority);
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
*/      void HeapPQueueDestroy(heap_pq_t *pqueue);
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
*/      int HeapPQueueEnqueue(heap_pq_t* pqueue, const void* data);
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
*/      void* HeapPQueueDequeue(heap_pq_t* pqueue);
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
*/      void* HeapPQueuePeek(const heap_pq_t* pqueue);
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
*/      int HeapPQueueIsEmpty(const heap_pq_t* pqueue);
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
*/      size_t HeapPQueueSize(const heap_pq_t* pqueue);
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
*/      void* HeapPQueueErase(heap_pq_t* pqueue, 
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
*/      void HeapPQueueClear(heap_pq_t* pqueue);
/*
******************************************************************************/

#endif                  /* __PQUEUE_H__ */
