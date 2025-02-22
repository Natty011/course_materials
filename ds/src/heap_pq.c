/***************************************
* Author : Natty
* Reviewer : Rawan
* Date : 22 / 02 / 2025
* Last update: 22 / 02 / 2025
*****************************************/
#ifdef PRINTS
	#include <stdio.h> 
#endif

#include <assert.h> 	/* assert */
#include <stdlib.h> 	/* malloc, free */

#include "heap_pq.h" 
#include "heap.h" 

#include "aux_func.h"
#define UNUSED( var )       ( (void*)var )

/****************struct and enum declaration*********************/

struct heap_pq
{
	heap_t *heap; 	
};

typedef enum
{
	
	FALSE = 0,
	TRUE = 1
	
}func_result_t;

/***************End of struct and enum declaration *******/

/********************  PQueueCreate  ****************************/
heap_pq_t *HeapPQueueCreate(priority_func_t priority)
{
	void* param = NULL;
	heap_pq_t* ptr_pqueue = (heap_pq_t*)malloc(sizeof(heap_pq_t));
	
	assert(priority);
	
	if(NULL == ptr_pqueue)
	{
		return NULL;
	}
	
	ptr_pqueue->heap =  HeapCreate( UNUSED(param), priority);
	
	if(NULL == ptr_pqueue->heap)
	{
		free(ptr_pqueue);
		ptr_pqueue = NULL;
		return NULL;
	}
	return ptr_pqueue;
}

/********************  PQueueDestroy  ****************************/
void HeapPQueueDestroy(heap_pq_t *pqueue)
{
	assert(pqueue);
	
	if(	 NULL == pqueue )
	{
		return;
	}
	HeapDestroy(pqueue->heap);
	
	pqueue->heap = NULL;
	free(pqueue);
	pqueue = NULL;
}


/********************  SortlistIsEmpty  ****************************/
int HeapPQueueIsEmpty(const heap_pq_t *pqueue)
{
	 assert(pqueue);	
	 return HeapIsEmpty(pqueue->heap);
}

/********************  PQueueSize  ****************************/
size_t HeapPQueueSize(const heap_pq_t *pqueue)
{
	
	assert(pqueue);			
	return HeapSize(pqueue->heap);

}
/********************  PQueuePeek  ****************************/
void *HeapPQueuePeek(const heap_pq_t *pqueue)
{
	assert(pqueue);
	return HeapPeek(pqueue->heap);	
}

/********************  PQueueEnqueue  ****************************/
int HeapPQueueEnqueue(heap_pq_t *pqueue, const void *data)
{	
	assert(pqueue);
	assert(pqueue->heap);

	return HeapPush(pqueue->heap, data );	
}

/********************  PQueueEnqueue  ****************************/
void *HeapPQueueDequeue(heap_pq_t *pqueue)
{
	void* deta = NULL;
	assert(pqueue);

	deta = HeapPeek( pqueue->heap ) ;
	HeapPop(pqueue->heap);	

	/* return NULL if Heap is Empty */
	return deta;
}

/********************  PQueueClear  ****************************/
void HeapPQueueClear(heap_pq_t* pqueue)
{	
	assert(pqueue);
	assert(pqueue->heap);
				
	while(! HeapIsEmpty( pqueue->heap) )
	{
		HeapPop(pqueue->heap);	
	}
}

/********************  PQueueErase  ****************************/
void* HeapPQueueErase(heap_pq_t* pqueue, match_func_t match_func,
				 const void* user_param)
{		
	void* data = NULL;
		
	assert(pqueue);	
	assert(match_func);

	data = HeapRemove(pqueue->heap, match_func, (void*)user_param );	
	
	return data;
		
}				 


