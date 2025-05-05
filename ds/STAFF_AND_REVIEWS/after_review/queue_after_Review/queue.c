/***************************************
* Author : Natty
* Reviewer : Natan
* Date : 15 / 12 / 2024
* Last update: 15 / 12 / 2024
*****************************************/

#include <assert.h> 	/* assert */
#include <stdlib.h> 	/* malloc, free */
#include "slist.h" 
#include "queue.h" 

#define QueueToSlist(queue) (queue->que)

/****************struct and enum declaration*********************/

struct queue
{

	slist_t* que; 
	
};


/** possible return values **/
typedef enum
{

	SUCCESS,
	OPERATION_FAIL

}slistResult;

/***************End of struct and enum declaration *******/

/***********Functions declaration and definition*******/

/**********End of functions declaration and definition *******/

/********************  QCreate  ****************************/
queue_t *QCreate(void)
{

	queue_t* queue = (queue_t*)malloc(sizeof(queue_t));
	if(NULL == queue)
	{
		return NULL;
	}
	queue->que =  SlistCreate();
	
	if(NULL == queue->que)
	{
		free(queue);
		queue = NULL;
		return NULL;
	}
	
	return queue;
	
}
/********************  QDestroy  ****************************/
void QDestroy(queue_t *queue)
{
	 SlistDestroy(queue->que);
	 free(queue);
}
/********************  QEnqueue  ****************************/
int QEnqueue(queue_t *queue, const void *data)
{
	
	slist_iter_t itr = SlistInsertBefore(QueueToSlist(queue),
						 SlistEnd(QueueToSlist(queue)), data);
						 
	return IsItrEqual(itr, SlistEnd(QueueToSlist(queue)));
}
/********************  QDequeue  ****************************/
void QDequeue(queue_t *queue)
{
	SlistRemove(SlistBegin(QueueToSlist(queue)));
}
/********************  QPeek  ****************************/
void *QPeek(const queue_t *queue)
{
	return SlistGetData(SlistBegin(QueueToSlist(queue)));
}
/********************  QIsEmpty  ****************************/
int QIsEmpty(const queue_t *queue)
{
	return SlistIsEmpty(QueueToSlist(queue));
}
/********************  QSize  ****************************/
size_t QSize(const queue_t *queue)
{
	return SlistCount(QueueToSlist(queue));
}

/********************  QAppend  ****************************/
queue_t *QAppend(queue_t *dest, queue_t *src)
{
	SlistAppend(QueueToSlist(dest), QueueToSlist(src));
	return dest;	
}

