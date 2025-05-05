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

	
queue_t* SlistToQueue(slist_t* slist)
{
	return (queue_t*)slist;
}

slist_t* QueueToSlist(queue_t* queue) 
{
	return (slist_t*)queue;

}

/**********End of functions declaration and definition *******/

/********************  QCreate  ****************************/
queue_t *QCreate(void)
{

	queue_t* que = SlistToQueue(SlistCreate());
	return que;
	
}
/********************  QDestroy  ****************************/
void QDestroy(queue_t *queue)
{
	 SlistDestroy(QueueToSlist(queue));
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
	return SlistGetData(SlistBegin(QueueToSlist((queue_t*)queue)));
}
/********************  QIsEmpty  ****************************/
int QIsEmpty(const queue_t *queue)
{
	return SlistIsEmpty(QueueToSlist((queue_t*)queue));
}
/********************  QSize  ****************************/
size_t QSize(const queue_t *queue)
{
	return SlistCount(QueueToSlist((queue_t*)queue));
}

/********************  QAppend  ****************************/
queue_t *QAppend(queue_t *dest, queue_t *src)
{
	SlistAppend(QueueToSlist(dest), QueueToSlist(src));
	return dest;	
}

