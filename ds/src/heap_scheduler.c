/***************************************
* Author : Natty
* Reviewer : Chen
* Date : 01 / 01 / 2025
* Last update: 01 / 01 / 2025
*****************************************/
#include <stdio.h> 	
#include <assert.h> 	/* assert */
#include <stdlib.h> 	/* malloc, free */
#include <unistd.h>

#include "heap_scheduler.h"
#include "heap_pq.h"
#include "task.h"
#include "uid.h"

#define UNUSED( var )       ( (void)var );

typedef enum
{

	OPERATION_FAIL = -3,
	SYSTEM_FAIL = -2,
	STOPPED = -1,
	SUCCESS = 0,
	FAIL = 1
		
}status_t;

typedef enum
{
	FAIL_FROM_RUN = -1,	
	FINISHED = 0,
	SHOULD_REPEAT = 1 /* not finished */
	
}task_result_t;

typedef enum 
{
	
	FALSE = 0,
	TRUE = 1
	
}bool;

struct scheduler
{
	heap_pq_t* pq;
	task_t* current_task;
	bool to_stop;
	int to_remove_current;
	 	
};

/***************End of struct and enum declaration *******/

/***************************function declaration**************************/
static int match_func(void *check_data, void *user_param );
static int priority_func(void *check_data, void *user_param, void* param );
/***************************End of function declaration******************/

/********************  HeapSchedulerCreate  ****************************/
scheduler_t *HeapSchedulerCreate(void)
{

	scheduler_t* ptr_sch = (scheduler_t*)malloc(sizeof(scheduler_t));
	/*scheduler_t* ptr_sch = (scheduler_t*)calloc(1, sizeof(scheduler_t));*/

	if(NULL == ptr_sch)
	{
		return NULL;
	}

	ptr_sch->pq =  HeapPQueueCreate(priority_func);
	
	if(NULL == ptr_sch->pq)
	{
		free(ptr_sch);
		ptr_sch = NULL;
		return NULL;
	}
	
	ptr_sch->current_task = NULL; /* NULL if scheduler is not running */
	ptr_sch->to_stop = FALSE;
	ptr_sch->to_remove_current = FALSE;
	
	return ptr_sch;
	
}
/*******************priority_func*********************/

static int priority_func(void *check_data, void *user_param , void* param)
{
	
	time_t check_data_priority = TaskGetTimeToRun((task_t*)check_data);
	time_t user_param_priority = TaskGetTimeToRun((task_t*)user_param);
	UNUSED( param );

	return -1 * (check_data_priority > user_param_priority);
	
}

/********************  HeapSchedulerIsEmpty  ****************************/
int HeapSchedulerIsEmpty(const scheduler_t *scheduler)
{
	 assert(scheduler);

	 return HeapPQueueIsEmpty(scheduler->pq) && (NULL == scheduler->current_task) ;

}

/********************  HeapSchedulerDestroy  ****************************/
void HeapSchedulerDestroy(scheduler_t *scheduler)
{
	if ( scheduler )
	{
		HeapSchedulerClear(scheduler);
		TaskDestroy(scheduler->current_task);
		HeapPQueueDestroy(scheduler->pq);
		scheduler->pq = NULL;
		free(scheduler);
		scheduler = NULL;		
	}
}
/********************  HeapSchedulerClear  ****************************/
void HeapSchedulerClear(scheduler_t *scheduler)
{
	
	task_t* data = NULL;
	
	assert(scheduler);
	
	while( ! HeapPQueueIsEmpty(scheduler->pq) )
	{	
		data = (task_t*)HeapPQueueDequeue(scheduler->pq);
		TaskDestroy(data);	
	}
	
	scheduler->to_remove_current = TRUE;
	
}
/********************  HeapSchedulerSize  ****************************/

size_t HeapSchedulerSize(const scheduler_t *scheduler)
{
	assert(scheduler);
	
	return HeapPQueueSize(scheduler->pq) + ( NULL != scheduler->current_task );
}


/********************  HeapSchedulerRemove  ****************************/
int HeapSchedulerRemove(scheduler_t *scheduler, ilrd_uid_t task_to_remove)
{
	
	task_t* to_remove = NULL;
	
	assert(scheduler);
	
	if( scheduler->current_task && UIDIsSame(task_to_remove,
		 TaskGetUID(scheduler->current_task) ) )
	{
		scheduler->to_remove_current = TRUE;
		return SUCCESS;
		
	}
	
	to_remove = (task_t*)HeapPQueueErase( scheduler->pq, match_func ,
									 &task_to_remove);
	
	if ( NULL != to_remove )
	{
		TaskDestroy( to_remove );	
		to_remove = NULL;
		return SUCCESS;
	}
	else
	{
		return FAIL;
	}
}

/*******************match_function*********************/

static int match_func(void *check_data, void *user_param )
{
	return UIDIsSame(TaskGetUID((task_t*)check_data),
					 *(ilrd_uid_t*)user_param );
}

/*******************HeapSchedulerStop*********************/
void HeapSchedulerStop(scheduler_t *scheduler)
{

	assert(scheduler);
	scheduler->to_stop = TRUE; 
} 
 
/*******************HeapSchedulerAdd*********************/				 
ilrd_uid_t HeapSchedulerAdd(scheduler_t *scheduler,
                        int (*op_func)(void *user_param),
                        void *user_param, size_t interval_in_sec)
{

	
	task_t* task =  NULL;
	int status = SUCCESS;

	assert(scheduler);

	task =  TaskCreate(op_func, user_param, interval_in_sec);
	
	if(  NULL == task )
	{
		return BADUID;
	}
		
	status = HeapPQueueEnqueue(scheduler->pq, task);
		
	if( FAIL == status )
	{
		TaskDestroy(task);
		task = NULL;
		
		return BADUID;
	}
	
	return TaskGetUID(task);
	
}  

/*******************HeapSchedulerRun*********************/				 

int HeapSchedulerRun(scheduler_t *scheduler)
{
	int status = SUCCESS;

	time_t time_to_run = 0;

	time_t time_wait = 0;			
	assert(scheduler);
	

	scheduler->to_stop = FALSE;
		
	while( (FALSE == scheduler->to_stop) && (! HeapSchedulerIsEmpty(scheduler)) ) 
	{
		scheduler->current_task = HeapPQueueDequeue(scheduler->pq);
	

		time_to_run = TaskGetTimeToRun(scheduler->current_task );
	
		do
		{
			time_wait = time_to_run > time(NULL) ? time_to_run - time(NULL) : 0;

		}
		while ( sleep(time_wait) );
		
		status = TaskRun(scheduler->current_task );
	
		if ( TRUE == scheduler->to_remove_current ) status = FINISHED;
			
		if(FINISHED == status)
		{
			TaskDestroy(scheduler->current_task );
			scheduler->to_remove_current = FALSE;
		}		
		else if ( SHOULD_REPEAT == status )
		{
			TaskSetTimeToRun(scheduler->current_task );	
			
			/* if failed*/
			if( HeapPQueueEnqueue(scheduler->pq, scheduler->current_task ) )
			{
				TaskDestroy(scheduler->current_task );
				scheduler->current_task = NULL;
				return SYSTEM_FAIL;
			}
		}
		else /* OPERATION_FAIL case */
		{
			TaskDestroy(scheduler->current_task );
			scheduler->current_task = NULL;
			return OPERATION_FAIL;	
		}	
		
		scheduler->current_task = NULL;	
		scheduler->to_remove_current = FALSE;	
	}
	
	if ( TRUE == scheduler->to_stop )
	{	
		scheduler->to_stop = FALSE;
		return STOPPED;
	}	
	return SUCCESS;
				
}
          
