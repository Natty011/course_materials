/***************************************
* Author : Natty
* Reviewer : 
* Date : 01 / 01 / 2025
* Last update: 01 / 01 / 2025
*****************************************/
#include <stdio.h> 	
#include <assert.h> 	/* assert */
#include <stdlib.h> 	/* malloc, free */
#include "scheduler.h"
#include "pqueue.h"
#include "task.h"

/*const ilrd_uid_t BADUID = {0, 0, 0, {0} };*/
/****************struct and enum declaration*********************/

/* -3 operation_fail
  -2 system_fail
  0  succuss
  -1 stopped 
*/

/** possible return values **/
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
	
	FALSE = 0,
	TRUE = 1
	
}func_result_t;

struct scheduler
{
	pqueue_t* pq;
	task_t* current_task;
	status_t status;
	int to_remove_current;
	 	
};

static int match_func(void *check_data, void *user_param );
/***************End of struct and enum declaration *******/

int main()
{
	puts("=================================================");
	return 0;

}

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
	
	ptr_sch->current_task = { 0 }; /* BADUID */
	ptr_sch->status = SUCCESS;
	ptr_sch->to_remove_current = 0;
	
	return ptr_sch;
	
}
/*******************priority_func*********************/

static int priority_func(void *check_data, void *user_param )
{
	time_t check_data_priority = *(time_t*)check_data;
	time_t user_param_priority = *(time_t*)user_param;
	
	if(check_data_priority > user_param_priority)
	{
		return -1; 
	}
	
	else if(check_data_priority == user_param_priority)
	{
		return 0;
	}
	
	else
	{
		return 1;
	}
		
}

/********************  SchedulerIsEmpty  ****************************/
int SchedulerIsEmpty(const scheduler_t *scheduler)
{
	 assert(scheduler);
	 
	 return PQueueIsEmpty(scheduler->pq) && (NULL == scheduler->current_task);

}

/********************  SchedulerDestroy  ****************************/
void SchedulerDestroy(scheduler_t *scheduler)
{
	 assert(scheduler);

	 if(!SchedulerIsEmpty(scheduler))
	 {
	 	SchedulerClear(scheduler);
	 }
	 
	 free(scheduler->pq);
	 scheduler->pq = NULL;
	
	 free(scheduler);
	 scheduler = NULL;
	  
}
/********************  SchedulerClear  ****************************/
void SchedulerClear(scheduler_t *scheduler)
{
	assert(scheduler);
	
	PQueueClear(scheduler->pq);	

	scheduler->to_remove_current =	( NULL != scheduler->current_task );

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
	
	task_t* to_remove = {0};
	
	assert(scheduler);
	
	
	to_remove = scheduler->current_task;
	
	if( UIDIsSame(task_to_remove, to_remove->UID ) )
	{
		scheduler->to_remove_current = TRUE;
		return SUCCESS;
		
	}
	
	else if(PQueueIsEmpty(scheduler->pq))
	{
		return FAIL;	
	}
	
	else
	{

		{
		
			PQueueErase(scheduler->pq, match_func , &task_to_remove);
			return SUCCESS;
			
		}
	
	}
	
}

/*******************match_function*********************/

static int match_func(void *check_data, void *user_param )
{

	return UIDIsSame(TaskGetUID((task_t*)check_data), *user_param );

}


				 

