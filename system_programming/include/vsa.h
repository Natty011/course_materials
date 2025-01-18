/******************************************************************************
*	Version         0.2
*   Last Update:    15/01/25    17:17
******************************************************************************/
#ifndef __VSA_API__     /* __VSA_API__  */
#define __VSA_API__     /* __VSA_API__  */

#include <stddef.h>     /* size_t       */

typedef struct vsa vsa_t;

/******************************************************************************
*
*       Description: Initializes the variable size memory pool
*       Arguments: * 'mem_area' - Pointer to the start of the memory area
*                  * 'mem_size' - The size of memory pool to create
*       Complexity: O(1)

*       Note: 
*
*/      vsa_t *VSAInit(void *mem_area, size_t mem_size);
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
*/      void *VSAAlloc(vsa_t *vsa, size_t chunk_size_in_bytes);
/*
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
*/      void VSAFree(void *chunk_to_free);
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
*/      size_t VSALargestChunkAvailable(vsa_t *vsa);
/*
******************************************************************************/

#endif                  /* __VSA_API__  */
