/******************************************************************************
*	Version 1.0
******************************************************************************/
#ifndef __CBUFFER_H__   /* __CBUFFER_H__  */
#define __CBUFFER_H__   /* __CBUFFER_H__  */

#include <stddef.h>     /* size_t       */

typedef struct cbuffer cbuffer_t;

/******************************************************************************
*
*       Name: CBufferCreate
*       Description: Creates a circular buffer data structure object
*       Arguments: capacity - in Bytes
*       Complexity: Dependant on system call complexity
*       Return: A newly initialized 'cbuffer_t' struct or NULL  
*               if allocation fails
* 
******************************************************************************/
cbuffer_t *CBufferCreate(size_t capacity);

/******************************************************************************
*
*       Name: CBufferDestroy
*       Description: Destroys a circular buffer data structure 
*       Arguments: cbuffer - The circular buffer object to destroy
*       Complexity: Dependant on system call complexity
*       Return: N/A
*       Notes: if 'cbuffer' is a NULL no operations will be performed
* 
******************************************************************************/
void CBufferDestroy(cbuffer_t *cbuffer);

/******************************************************************************
*
*       Name: CBufferRead
*       Description: Reads a given number of Bytes from the buffer and into
*       Dest.
*       Arguments: The buffer to be read from, the array to read into, and 
*       the number of bytes to read.
*       Complexity: O(n)
*       Return: Number of bytes read
*       Notes: N\A
* 
******************************************************************************/
size_t CBufferRead(cbuffer_t *src, char *dest, size_t n);


/******************************************************************************
*
*       Name: CBufferWrite
*       Description: BBBBBB
*       Arguments: dest - the buffer that is written to.
*                  src - the memory we want to write from.
*                  n - the amount of bytes we want to write.
*       Complexity: O(n)
*       Return: Number of bytes written
*       Notes: how do we return that something went wrong?
* 
******************************************************************************/
size_t CBufferWrite(cbuffer_t *dest, const char *src, size_t n);

/******************************************************************************
*
*       Name: CBufferIsEmpty
*       Description: BBBBBB
*       Arguments: CCCCC
*       Complexity: O(1)
*       Return: EEEEEE
*       Notes: FFFFFF
* 
******************************************************************************/
int CBufferIsEmpty(const cbuffer_t *cbuffer);

/******************************************************************************
*
*       Name: CBufferCapacity
*       Description: BBBBBB
*       Arguments: CCCCC
*       Complexity: DDDDDDD
*       Return: EEEEEE
*       Notes: FFFFFF
* 
******************************************************************************/
size_t CBufferBuffSiz(const cbuffer_t *cbuffer);

/******************************************************************************
*
*       Name: CBufferFreeSpace
*       Description: the function return how much empty space is left in the buffer.
*       Arguments:  cbuffer - The circular buffer object.
*       Complexity: O(1)
*       Return: EEEEEE
*       Notes: FFFFFF
* 
******************************************************************************/
size_t CBufferFreeSpace(const cbuffer_t *cbuffer);

#endif                  /* __CBUFFER_H__  */
