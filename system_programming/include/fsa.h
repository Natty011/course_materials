/******************************************************************************
*	Version 1.0
*   Last update: 14.01.2025     08:59
******************************************************************************/
#ifndef __FSA_API__     /* __FSA_API__  */
#define __FSA_API__     /* __FSA_API__  */

#include <stddef.h>     /* size_t       */

typedef struct fsa fsa_t;

/****************************הצ**************************************************
*
*       Description: Suggets the size of the user's allocation
*       Arguments: Number of blocks wanted, size of each block.
*       Complexity: O(1)
*       Return: Number of bytes needed.
*       Note: 
*
*/      size_t FSASuggestSize(size_t num_of_blocks, size_t size_of_block);
/*
******************************************************************************/

/******************************************************************************
*
*       Description: Initializes the fixed-size block memory pool
*       Arguments: Pointer to dynamicly allocated memory area, size of memory 
*                  area in bytes, size of block wanted.
*       Complexity: O(n)
*       Return: Pointer to a handle for memory pool.
*               Returns NULL if there is not enough space for one block.
*       Note: 
*
*/      fsa_t* FSAInit(void* mem_area, size_t mem_size, size_t size_of_block);
/*
******************************************************************************/

/******************************************************************************
*
*       Description: Allocates a block from the memory pool
*       Arguments: Handle for memory pool.
*       Complexity: O(1)
*       Return: Pointer to first free block.
*               Returns NULL if there is not enough space for another
*               allocation.
*       Note: 
*
*/      void* FSAAlloc(fsa_t* fsa);
/*
******************************************************************************/

/******************************************************************************
*
*       Description: Frees a memory block from the memory pool
*       Arguments: Handle for memory pool, pointer to block to free.
*       Complex	ity: O(1)
*       Return: N/A
*       Note: If "block" is NULL - nothing occurs.
*             If "block" is already freed - undefined behaviour.
*
*/      void FSAFree(fsa_t* fsa, void* block);
/* 
******************************************************************************/

/******************************************************************************
*
*       Description: Counts the number of free blocks in the memory pool
*       Arguments: Handle for memory pool.
*       Complexity: O(n)
*       Return: Number of free blocks in pool.
*       Note: 
*
*/      size_t FSACountFree(const fsa_t* fsa);
/*
******************************************************************************/

#endif                  /* __FSA_API__  */
