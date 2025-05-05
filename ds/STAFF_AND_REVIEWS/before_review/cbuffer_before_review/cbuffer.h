/******************************************************************************
*	Version 1.0
******************************************************************************/
#ifndef __CBUFFER_H__   /* __CBUFFER_H__  */
#define __CBUFFER_H__   /* __CBUFFER_H__  */

#include <stddef.h>     /* size_t         */

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
*       Notes: undefined behaviour if src is empty
* 
******************************************************************************/
size_t CBufferRead(cbuffer_t *src, void *dest, size_t n);


/******************************************************************************
*
*       Name: CBufferWrite
*       Description: the function writes to the following free spot in the 
*                    buffer, if there are no n bytes to write to we will
*                    write what we can.
*       Arguments: dest - the buffer that is written to.
*                  src - the memory we want to write from.
*                  n - the amount of bytes we want to write.
*       Complexity: O(n)
*       Return: Number of bytes written
*       Notes: undefined behaviour if dest is full
* 
******************************************************************************/
size_t CBufferWrite(cbuffer_t *dest, const void *src, size_t n);

/******************************************************************************
*
*       Name: CBufferIsEmpty
*       Description: checks if the circular buffer is empty.
*       Arguments: 'cbuffer' - The buffer struct.
*       Complexity: O(1)
*       Return: Returns 'TRUE' (1) if empty, 'FALSE' (0) if not
*       Notes: Undefined behaviour if "cbuffer" is NULL
* 
******************************************************************************/
int CBufferIsEmpty(const cbuffer_t *cbuffer);

/******************************************************************************
*
*       Name: CBufferBufSiz
*       Description: Returns the byte capacity of the buffer
*       Arguments: * 'cbuffer' - The buffer struct
*       Complexity: O(1)
*       Return: Buffer capacity in bytes
*       Notes: Undefined behaviour if 'cbuffer' is NULL
* 
******************************************************************************/
size_t CBufferBufSiz(const cbuffer_t *cbuffer);

/******************************************************************************
*
*       Name: CBufferFreeSpace
*       Description: the function return how much free space is left in the
*                                                          buffer in bytes.
*       Arguments:  cbuffer - The circular buffer object.
*       Complexity: O(1) 
*       Return: return how much free space is left in the buffer in bytes.
*       Notes: 
* 
******************************************************************************/
size_t CBufferFreeSpace(const cbuffer_t *cbuffer);

#endif                  /* __CBUFFER_H__  */
