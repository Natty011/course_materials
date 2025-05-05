/***************************************
* Author : Natty
* Reviewer : Chen
* Date : 17 / 12 / 2024
* Last update: 18 / 12 / 2024
*****************************************/

#include <assert.h> 	/* assert 		*/
#include <stdlib.h> 	/* malloc, free */
#include <string.h> 	/* memcpy 		*/
#include "cbuffer.h" 

#define OFFSETOF(TYPE, ELEMENT) ((size_t)&(((TYPE *)0)->ELEMENT))
#define MIN(a, b)  (((a) > (b)) ? (b) : (a)) 

/****************struct and enum declaration*********************/

struct cbuffer
{

	size_t capacity; 
	size_t front;
	size_t current_size;
	char arr[1]; 
	
};

/***************End of struct and enum declaration *******/

/***********Functions declaration and definition*******/
static void UpdateCurrSize(cbuffer_t *cbuffer, size_t bytes);
/**********End of functions declaration and definition *******/

/********************  CBufferCreate  ****************************/

cbuffer_t *CBufferCreate(size_t capacity)
{

	size_t padding = sizeof(cbuffer_t) - OFFSETOF(cbuffer_t, arr);
	size_t cap_to_alloc = capacity - padding;
	
	cbuffer_t* cbuffer = (cbuffer_t*)malloc(sizeof(cbuffer_t) + cap_to_alloc);
	
	if(NULL == cbuffer)
	{
		return NULL;
	}
	
	cbuffer->capacity = capacity;
	cbuffer->front = 0;
	cbuffer->current_size = 0;
	
	return cbuffer;
	
}

/********************  CBufferDestroy  ****************************/
void CBufferDestroy(cbuffer_t *cbuffer)
{
	if(NULL == cbuffer)
	{
		return;
	}
	
	free(cbuffer);
	cbuffer = NULL;
	 
}

/********************  CBufferIsEmpty  ****************************/
int CBufferIsEmpty(const cbuffer_t *cbuffer)
{
	assert(cbuffer);
	return 	0 == cbuffer->current_size;
}

/********************  CBufferBuffSiz  ****************************/
size_t CBufferBuffSiz(const cbuffer_t *cbuffer)
{
	assert(cbuffer);
	return 	cbuffer->capacity;
}
/********************  CBufferFreeSpace  ****************************/
size_t CBufferFreeSpace(const cbuffer_t *cbuffer)
{
	assert(cbuffer);
	return cbuffer->capacity - cbuffer->current_size;
}

/********************  CBufferRead  ****************************/

/**********************************************************
Note: The first memcpy handles data copy till buffer end, and
	   second one handles data copy from buffer beginning.

***********************************************************/ 
size_t CBufferRead(cbuffer_t *src, char *dest, size_t n)
{

	size_t remainder = 0;
	size_t bytes_to_read = 0;
	
	if ( CBufferBuffSiz(src) == CBufferFreeSpace(src) ||  0 == n )
	{
		return 0;	
	}

	assert(src);
	assert(dest);	
		
	n = MIN(n, src->current_size);
	bytes_to_read = MIN(n, CBufferBuffSiz(src) - src->front);
	remainder = n - bytes_to_read;
	
	memcpy(dest, src->arr + src->front, bytes_to_read);	
	
	UpdateCurrSize(src, -bytes_to_read);	
	src->front = (src->front + bytes_to_read) % CBufferBuffSiz(src);

	memcpy(dest+ bytes_to_read, src->arr + src->front, remainder);	

	UpdateCurrSize(src, -remainder);	
	src->front = (src->front + remainder) % CBufferBuffSiz(src);

	return n;
	
}

/********************  CBufferWrite  ****************************/

/**********************************************************
Note: The first memcpy handles data copy till buffer end, and
	   second one handles data copy from buffer beginning.

***********************************************************/ 

size_t CBufferWrite(cbuffer_t *dest, const char *src, size_t n)
{
	size_t remainder = 0;
	size_t bytes_to_write = 0;
	size_t rear = 0;
	
	if ( 0 == CBufferFreeSpace(dest) ||  0 == n )
	{
		return 0;	
	}

	assert(src);
	assert(dest);
	
	rear = ( dest->front + dest->current_size )%CBufferBuffSiz(dest);
	n = MIN(n, CBufferFreeSpace(dest));
	bytes_to_write = MIN(n, CBufferBuffSiz(dest) - rear);
	remainder = n - bytes_to_write;

	memcpy(dest->arr + rear, src, bytes_to_write);
	
	UpdateCurrSize(dest, bytes_to_write);	
	rear = ( dest->front + dest->current_size )%CBufferBuffSiz(dest);

	memcpy(dest->arr + rear, src + bytes_to_write, remainder);	
	
	UpdateCurrSize(dest, remainder);
				
	return n;
}


static void UpdateCurrSize(cbuffer_t *cbuffer, size_t bytes)
{
	assert(cbuffer);
	cbuffer->current_size += bytes;		
}


