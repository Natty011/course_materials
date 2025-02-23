/******************************************************************************
*	Version 1.2
*   Last Updated:   19/2/2025
*                   18:10
******************************************************************************/
#ifndef __HEAP_H__      /* __HEAP_H__      */
#define __HEAP_H__      /* __HEAP_H__      */

#include <stddef.h>     /* size_t	       */
#include "aux_func.h"

typedef struct heap heap_t;

/******************************************************************************
* 
*   Description:
* 
*       Comparison function to compare two data values , using the 'param'
*       that was provided when creating the heap.
* 
*   Arguments:
* 
*       * 'check_data' - Current node data.
*       * 'new_data'   - Data to compare to.
*       * 'param'      - A parameter that was provided in the cerate 
*                      function and will be sent as an argument to the
*                      comparison function on each insertion of a new element.
* 
*   Return value:
* 
*       >0 - If the 'check_data' needs to be positioned above
*            the 'new_data' being examined.
* 
*       <0 - If the 'check_data' needs to be positioned below
*            the 'new_data' being examined.
*   
*   Notes: 
*	
*		* Undefined behaviour if comparison return 0;
*/
typedef int
(*expand_cmp_func_t)(void* check_data ,void* new_data, void* param);
/*(*expand_cmp_func_t)(const void* check_data ,const void* new_data, void* param);*/

/* 
******************************************************************************/
/******************************************************************************
*
*   Description: 
* 
*       Create An instance of a heap.
*    
*   Arguments: 
* 
*       * 'cmp_func' - Comparison function As described above
*       * 'param'    - will be sent as an argument to the comparison function
*                    on each insertion of a new element.
* 
*   Return value: 
* 
*       * Pointer to the heap instance.
* 
*   Complexity:
* 
*       * O(1) ( system dependent ).
* 
*/      heap_t* HeapCreate( void* param , expand_cmp_func_t cmp_func );
/*
******************************************************************************/
/******************************************************************************
*
*   Description: 
*   
*       Destroys An instance of a heap.
* 
*   Arguments: 
* 
*       * 'heap' - Heap to destroy.
* 
*   Return value: 
* 
*       * returns void.
*      
*   Complexity: 
*       
*       * O(1) ( system dependent ).
*       
*   Notes: 
*       * If 'heap' is 'NULL' no operations will be performed.
* 
*/      void HeapDestroy( heap_t* heap );
/*
*******************************************************************************
*
*   Description: 
* 
*       Insert an element into the heap.
* 
*   Arguments: 
* 
*       * 'heap' - Heap to Insert the data into.
*       * 'data' - data to Insert.
* 
*   Return value: 
*   
*       * 0 - SUCCESS.
*       * otherwise - FAILURE ( insertion failed ).
* 
*   Complexity: 
*       
*       * Amortized complexity - O(log n).
*       * Worst case complexity - O( n ).
* 
*   Notes:
*   
*       * Undefined behaviour if 'heap' or 'data' is 'NULL'.
* 
*/      int HeapPush( heap_t* heap , const void* data );
/*
******************************************************************************/

/******************************************************************************
*
*   Description: 
*           
*       Pops the top element from the heap.
* 
*   Arguments:
*       
*       * 'heap' - Heap to pop the element from
*   
*   Return value: 
*       
*       * returns void.
* 
*   Complexity: 
*           
*       * Best case - O(log n).
* 
*   Notes: 
*           
*       * Undefined behaviour if 'heap' is 'NULL'.
* 
*/      void HeapPop( heap_t* heap );
/*
*******************************************************************************
*
*   Description: 
*
*       Remove an element from the heap.
*
*   Arguments: 
* 
*       * 'heap'       - Heap to remove the data from.
*       * 'match_func' - A function that returns a boolean value indicating
                         whether the data being checked is the data to remove.
*       * 'param'      - Parameter used to determine whether the data being
                         checked is the data to remove.
*
*   Return value:  
        
        * Returns the data removed from the heap.
*
*   Complexity: 
*   
*       * Best case - O( n ).    
*
*   Notes:
*        
*       * Undefined behaviour if 'heap' or 'match_func' are 'NULL'.
* 
*/      void* HeapRemove( heap_t* heap , match_func_t match_func , void* param );
/*
******************************************************************************/
/******************************************************************************
*
*   Description: 
*       
*       Get access to the top element in the heap.
* 
*   Arguments: 
*       
*       'heap' - Heap to get data from.
* 
*   Return value:
* 
*       * pointer of the top element.
* 
*   Complexity:
*       
*       Best case - O(1).
* 
*   Notes: 
*       
*       Undefined behaviour if 'heap' is 'NULL'.
* 
*/      void* HeapPeek( const heap_t* heap );
/*
******************************************************************************/
/******************************************************************************
*
*   Description: 
*       
*       Return the number of elements in the heap.
*       
*   Arguments: 
*       
*       'heap' - Heap to meassure
*       
*   Return value: 
*       
*       * Number of elements in the heap.
*       
*   Complexity: 
*   
*       Best case - O(1).
* 
*   Notes: 
*       
*       Undefined behaviour if 'heap' is 'NULL'.
* 
*/      size_t HeapSize( const heap_t* heap );
/*
******************************************************************************/

/******************************************************************************
*
*   Description: 
*       
*       Return whether the heap is empty.
* 
*   Arguments: 
*
*       * 'heap' - Heap to check.
* 
*   Return value: 
*       
*       * 1 - (TRUE) if empty.
*       * 0 - (FALSE) if not.
* 
*   Complexity: 
*       
*       * Best case - O(1).
* 
*   Notes: 
*   
*       * Undefined behaviour if 'heap' is 'NULL'.
* 
*/      int HeapIsEmpty(const heap_t *heap);
/*
******************************************************************************/

#endif                  /* __HEAP_H__      */

#ifdef PRINTS
    void PrintArray( heap_t* heap );
#endif