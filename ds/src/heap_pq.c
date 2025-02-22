/***************************************
* Author : Natty
* Reviewer : Michael
* Date : 26 / 12 / 2024
* Last update: 26 / 12 / 2024
*****************************************/
#ifdef PRINTS
	#include <stdio.h> 
#endif

#include <assert.h> 	/* assert */
#include <stdlib.h> 	/* malloc, free */

#include "pqueue.h" 
#include "heap.h" 

#include "aux_func.h"
#define UNUSED( var )       ( (void*)var )

/****************struct and enum declaration*********************/

struct pqueue
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
pqueue_t *PQueueCreate(priority_func_t priority)
{
	void* param = NULL;
	pqueue_t* ptr_pqueue = (pqueue_t*)malloc(sizeof(pqueue_t));
	
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
void PQueueDestroy(pqueue_t *pqueue)
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
int PQueueIsEmpty(const pqueue_t *pqueue)
{
	 assert(pqueue);	
	 return HeapIsEmpty(pqueue->heap);
}

/********************  PQueueSize  ****************************/
size_t PQueueSize(const pqueue_t *pqueue)
{
	
	assert(pqueue);			
	return HeapSize(pqueue->heap);

}
/********************  PQueuePeek  ****************************/
void *PQueuePeek(const pqueue_t *pqueue)
{
	assert(pqueue);
	return HeapPeek(pqueue->heap);	
}

/********************  PQueueEnqueue  ****************************/
int PQueueEnqueue(pqueue_t *pqueue, const void *data)
{	
	assert(pqueue);
	assert(pqueue->heap);

	return HeapPush(pqueue->heap, data );	
}

/********************  PQueueEnqueue  ****************************/
void *PQueueDequeue(pqueue_t *pqueue)
{
	void* deta = NULL;
	assert(pqueue);
	
	deta = HeapPeek( pqueue->heap ) ;
	HeapPop(pqueue->heap);	

	/* return NULL if Heap is Empty */
	return deta;
}

/********************  PQueueClear  ****************************/
void PQueueClear(pqueue_t* pqueue)
{
	sort_list_iter_t sort_itr = {0};
	
	assert(pqueue);
	assert(pqueue->pq_list);
	
	sort_itr = SortlistBegin(pqueue->pq_list);	
			
	while(!SortlistIterIsEqual(SortlistEnd(pqueue->pq_list), sort_itr ) )
	{
		sort_itr = SortlistRemove(sort_itr);
	}
}

/********************  PQueueErase  ****************************/
void* PQueueErase(pqueue_t* pqueue, match_func_t match_func,
				 const void* user_param)
{
	sort_list_iter_t sort_itr = {0};
		
	void* data = NULL;
		
	assert(pqueue);	
	assert(match_func);

	sort_itr = SortlistBegin(pqueue->pq_list);
		
	if( PQueueIsEmpty(pqueue) )
	{
		return NULL;
	}
	
	sort_itr = SortlistFindIf(sort_itr, SortlistEnd(pqueue->pq_list),
								match_func, (void*)user_param);
	
	data = SortlistGetData(sort_itr);	
	SortlistRemove(sort_itr);
	
	return data;
		
}				 


