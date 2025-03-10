/******************************************************************************
*	Version         0.2
*   Last Update:    15/01/25    17:17
******************************************************************************/
#ifndef __SIMPLE_SHELL__     /* __SIMPLE_SHELL__  */
#define __SIMPLE_SHELL__     /* __SIMPLE_SHELL__  */

#include <stddef.h>     /* size_t       */


/******************************************************************************
*
*       Description: Initializes the variable size memory pool
*       Arguments: * 'mem_area' - Pointer to the start of the memory area
*                  * 'mem_size' - The size of memory pool to create
*       Complexity: O(1)

*       Note: 
*
*/      
/*
******************************************************************************/

/******************************************************************************
*
*       Description: Allocates a specific sized chunk in the memory pool
*       Arguments: * 'vsa' - The memory pool
*                  * 'chunk_size' - The size of the chunk to allocate
*       Complexity: O(n)
*       Return: pointer to allocated chunck or NULL if full
*       Note: 
*
*/      
******************************************************************************/

/******************************************************************************
*
*       Description: Frees a chunk in the memory pool
*       Arguments:
*       Complexity: O(1)
*       Return: N\A
*       Note:   Undefined behavior if 'chunk_to_free' is already free.
*               If 'chunk_to_free' is NULL, nothing happens.
*
*/      
/*
******************************************************************************/

/******************************************************************************
*
*       Description: Returns the size of the largest chunk available in -
*                    the memory pool
*       Arguments: 'vsa' - The memory pool
*       Complexity: O(n)
*       Return: 
*       Note: 
*
*/     
/*
******************************************************************************/

#endif                  /* __SIMPLE_SHELL__  */
