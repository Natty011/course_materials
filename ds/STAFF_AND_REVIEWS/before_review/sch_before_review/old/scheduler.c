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
/*#include "typedefs.h" *//* sleep */
#include "scheduler.h"
#include "pqueue.h"
#include "task.h"
#include "uid.h"

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
	pqueue_t* pq;
	task_t* current_task;
	bool to_stop;
	int to_remove_current;
	 	
};

/***************End of struct and enum declaration *******/

/***************************function declaration**************************/
static int match_func(void *check_data, void *user_param );
static int priority_func(void *check_data, void *user_param );
/***************************End of function declaration******************/


/********************  SchedulerCreate  ****************************/
scheduler_t *SchedulerCreate(void)
{

	scheduler_t* ptr_sch = (scheduler_t*)malloc(sizeof(scheduler_t));
	if(NULL == ptr_sch)
	{
		return NULL;
	}

	ptr_sch->pq =  PQueueCreate(priority_func);
	
	if(NULL == ptr_sch->pq)
	{
		free(ptr_sch);
		ptr_sch = NULL;
		return NULL;
	}
	
	ptr_sch->current_task = NULL; 
	ptr_sch->to_stop = FALSE;
	ptr_sch->to_remove_current = FALSE;
	
	return ptr_sch;
	
}
/*******************priority_func*********************/

static int priority_func(void *check_data, void *user_param )
{
	time_t check_data_priority = TaskGetTimeToRun((task_t*)check_data);
	time_t user_param_priority = TaskGetTimeToRun((task_t*)user_param);
	
	return check_data_priority > user_param_priority;
	
}

/********************  SchedulerIsEmpty  ****************************/
int SchedulerIsEmpty(const scheduler_t *scheduler)
{
	 assert(scheduler);

	 return PQueueIsEmpty(scheduler->pq) && (NULL == scheduler->current_task) ;

}

/********************  SchedulerDestroy  ****************************/
void SchedulerDestroy(scheduler_t *scheduler)
{
	if ( scheduler )
	{
		SchedulerClear(scheduler);
		TaskDestroy(scheduler->current_task);
		PQueueDestroy(scheduler->pq);
		scheduler->pq = NULL;
		free(scheduler);
		scheduler = NULL;		
	}
}
/********************  SchedulerClear  ****************************/
void SchedulerClear(scheduler_t *scheduler)
{
	
	task_t* data = NULL;
	
	assert(scheduler);
	
	while( ! PQueueIsEmpty(scheduler->pq) )
	{	
		data = (task_t*)PQueueDequeue(scheduler->pq);
		TaskDestroy(data);	
	}
	
	scheduler->to_remove_current = TRUE;
	
}
/********************  SchedulerSize  ****************************/

size_t SchedulerSize(const scheduler_t *scheduler)
{
	assert(scheduler);
	
	return PQueueSize(scheduler->pq) + ( NULL != scheduler->current_task );
}


/********************  SchedulerRemove  ****************************/
int SchedulerRemove(scheduler_t *scheduler, ilrd_uid_t task_to_remove)
{
	
	task_t* to_remove = NULL;
	
	assert(scheduler);
	
	if( scheduler->current_task && UIDIsSame(task_to_remove, TaskGetUID(scheduler->current_task) ) )
	{
		scheduler->to_remove_current = TRUE;
		return SUCCESS;
		
	}
	to_remove = (task_t*)PQueueErase( scheduler->pq, match_func , &task_to_remove);
	
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

/*******************SchedulerStop*********************/
void SchedulerStop(scheduler_t *scheduler)
{

	assert(scheduler);
	scheduler->to_stop = TRUE; 
} 
 
/*******************SchedulerAdd*********************/				 
ilrd_uid_t SchedulerAdd(scheduler_t *scheduler,
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
		
	status = PQueueEnqueue(scheduler->pq, task);
		
	if( FAIL == status )
	{
		TaskDestroy(task);
		task = NULL;
		
		return BADUID;
	}
	
	return TaskGetUID(task);
	
}  

/*******************SchedulerRun*********************/				 

int SchedulerRun(scheduler_t *scheduler)
{
	int status = SUCCESS;
	/*task_t* task =  NULL;*/
	time_t time_to_run = 0;
	time_t curr_time = 0;
	time_t time_wait = 0;			
	assert(scheduler);
	

	while( (FALSE == scheduler->to_stop) && (! SchedulerIsEmpty(scheduler)) ) 
	{
		scheduler->current_task = PQueueDequeue(scheduler->pq);
	

		time_to_run = TaskGetTimeToRun(scheduler->current_task );
		
		time_wait = time_to_run - time(NULL);	
		time_wait = time_wait <= 0 ? 0 : time_wait;
				
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
			
			if( PQueueEnqueue(scheduler->pq, scheduler->current_task ) )/* if failed*/
			{
				TaskDestroy(scheduler->current_task );
				scheduler->current_task = NULL;
				return SYSTEM_FAIL;
			}
		}
		else
		{
			TaskDestroy(scheduler->current_task );
			scheduler->current_task = NULL;
			return OPERATION_FAIL;	
		}	
		
		scheduler->current_task = NULL;	
		scheduler->to_remove_current = FALSE;	
	}
	
	if ( scheduler->to_stop == TRUE )
	{	
		return STOPPED;
	}	
	return SUCCESS;
				
}
          
