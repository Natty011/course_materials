/***************************************
* Author : Natty
* Reviewer : Michael
* Date : 26 / 12 / 2024
* Last update: 26 / 12 / 2024
*****************************************/

#include <assert.h> 	/* assert */
#include <stdlib.h> 	/* malloc, free */
#include "pqueue.h" 

/****************struct and enum declaration*********************/

struct pqueue
{
	sort_list_t* pq_list; 	
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

	pqueue_t* ptr_pqueue = (pqueue_t*)malloc(sizeof(pqueue_t));
	
	assert(priority);
	
	if(NULL == ptr_pqueue)
	{
		return NULL;
	}
	
	ptr_pqueue->pq_list =  SortlistCreate(priority);
	
	if(NULL == ptr_pqueue->pq_list)
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
	SortlistDestroy(pqueue->pq_list);
	
	pqueue->pq_list = NULL;
	free(pqueue);
	pqueue = NULL;
}

/********************  SortlistIsEmpty  ****************************/
int PQueueIsEmpty(const pqueue_t *pqueue)
{
	 assert(pqueue);	
	 return SortlistIsEmpty(pqueue->pq_list);

}

/********************  PQueueSize  ****************************/
size_t PQueueSize(const pqueue_t *pqueue)
{
	
	assert(pqueue);			
	return SortlistSize(pqueue->pq_list);

}
/********************  PQueuePeek  ****************************/
void *PQueuePeek(const pqueue_t *pqueue)
{
	assert(pqueue);
	return SortlistGetData(SortlistBegin(pqueue->pq_list));	
}

/********************  PQueueEnqueue  ****************************/
int PQueueEnqueue(pqueue_t *pqueue, const void *data)
{
	sort_list_iter_t sort_itr = {0};
	
	assert(pqueue);
	assert(pqueue->pq_list);

	sort_itr = SortlistInsert(pqueue->pq_list, data );	
							 
	return SortlistIterIsEqual(sort_itr, SortlistEnd(pqueue->pq_list));	

}

/********************  PQueueEnqueue  ****************************/
void *PQueueDequeue(pqueue_t *pqueue)
{
	assert(pqueue);	
	return SortlistPopFront(pqueue->pq_list);
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
void PQueueErase(pqueue_t* pqueue, match_func_t match_func,
				 const void* user_param)
{
	sort_list_iter_t sort_itr = {0};	
		
	assert(pqueue);	
	assert(match_func);

	sort_itr = SortlistBegin(pqueue->pq_list);
		
	if( PQueueIsEmpty(pqueue) )
	{
		return;
	}
	
	sort_itr = SortlistFindIf(sort_itr, SortlistEnd(pqueue->pq_list),
								match_func, (void*)user_param);
		
	SortlistRemove(sort_itr);
		
}				 


