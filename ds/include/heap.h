/******************************************************************************
*	Version 0.0
*   Last Updated:   1/1/1970
*                   00:00
******************************************************************************/
#ifndef __HEAP_H__      /* __HEAP_H__      */
#define __HEAP_H__      /* __HEAP_H__      */

#include <stddef.h>     /* size_t	       */
#include "aux_func.h"

typedef struct heap heap_t;

/******************************************************************************
*
*       Description: Create a heap object
*       Arguments: 'cmp_func' - Comparison function for heap data
*       Return: The new heap object
*       Complexity: Dependent on system complexity
* 
*/      heap_t *HeapCreate(cmp_func_t cmp_func);
/*
******************************************************************************/

/******************************************************************************
*
*       Description: Destroys a heap object
*       Arguments: 'heap' - Heap to destroy
*       Return: N\A
*       Complexity: Dependant on system complexity
*       Notes: If 'heap' is 'NULL' no operations will be performed
* 
*/      void HeapDestroy(heap_t *heap);
/*
******************************************************************************/

/******************************************************************************
*
*       Description: Pushes an element into the heap
*       Arguments: 'heap' - Heap to push the data into
*       Return: SUCCESS (0) or FAILURE (1) if insertion failed
*       Complexity: O(log n)
*       Notes: Undefined behaviour if 'heap' or 'data' is 'NULL'
* 
*/      int HeapPush(heap_t *heap, const void *data);
/*
******************************************************************************/

/******************************************************************************
*
*       Description: Pops the first element from the heap
*       Arguments: 'heap' - Heap to pop the element from
*       Return: N\A
*       Complexity: O(log n)
*       Notes: Undefined behaviour if 'heap' is 'NULL'
* 
*/      void HeapPop(heap_t *heap);
/*
******************************************************************************/

/******************************************************************************
*
*       Description: Remove an element from the heap
*       Arguments: * 'heap' - Heap to remove the data from
*                  * 'param' - Data to remove from the heap
*       Return: N\A
*       Complexity: O(log n)
*       Notes: Undefined behaviour if 'heap' or 'data' are 'NULL'
* 
*/      void HeapRemove(heap_t *heap, void *param, match_func_t match_func);
/*
******************************************************************************/
/******************************************************************************
*
*       Description: Get the data of the first element in the heap
*       Arguments: 'heap' - Heap to get data from
*       Return: Data pointer of the first element
*       Complexity: O(1)
*       Notes: Undefined behaviour if 'heap' is 'NULL'
* 
*/      void *HeapPeek(const heap_t *heap);
/*
******************************************************************************/
/******************************************************************************
*
*       Description: Return the size of the heap
*       Arguments: 'heap' - Heap to meassure
*       Return: Size of the heap
*       Complexity: O(1)
*       Notes: Undefined behaviour if 'heap' is 'NULL'
* 
*/      size_t HeapSize(const heap_t *heap);
/*
******************************************************************************/

/******************************************************************************
*
*       Description: Return whether the heap is empty
*       Arguments: 'heap' - Heap to check
*       Return: TRUE (1) if empty, FALSE (0) if not
*       Complexity: O(1)
*       Notes: Undefined behaviour if 'heap' is 'NULL'
* 
*/      int HeapIsEmpty(const heap_t *heap);
/*
******************************************************************************/

#endif                  /* __HEAP_H__      */
