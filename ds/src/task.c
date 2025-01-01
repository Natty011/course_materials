/***************************************
* Author : Natty
* Reviewer : Chen
* Date : 01 / 01 / 2025
* Last update: 01 / 01 / 2025
*****************************************/

#include <assert.h> 	/* assert */
#include <stdlib.h> 	/* malloc, free */
#include "task.h"
#include "scheduler.h"

/****************struct and enum declaration*********************/

/** possible return values **/

typedef enum
{
	
	FALSE = 0,
	TRUE = 1
	
}func_result_t;

typedef enum
{
	FAIL = -1,	
	FINISHED = 0,
	SHOULD_REPEAT = 1 /* not finished */
	
}task_result_t;


struct task
{
	int (*func)(void* param);
	void* param;
	ilrd_uid_t uid;
	time_t time_to_execute;
	
};


/***************End of struct and enum declaration *******/

/********************  TaskCreate  ****************************/
task_t * TaskCreate(int (*op_func)(void *user_param),
					 void *user_param, size_t interval_in_sec)
{

	task_t* ptr_task = (task_t*)malloc(sizeof(task_t));
	
	assert(op_func);
	
	if(NULL == ptr_task)
	{
		return NULL;
	}
	
	ptr_task->func = op_func;
	
	ptr_task->param = user_param;
	
	ptr_task->uid = UIDCreate();
	
	ptr->time_to_execute = time(NULL) + interval_in_sec;
	
	return ptr_task;
	
}
/********************  TaskDestroy  ****************************/
void TaskDestroy(task_t *task)
{

	assert(task);
	
	if(	 NULL == task )
	{
		return;
	}
	
	free(task);
	task = NULL;	
}
/********************  TaskGetUID  ****************************/
ilrd_uid_t TaskGetUID(const task_t *task)
{

	assert(task);
	
	return task->uid;

}
/********************  TaskGetTimeToRun  ****************************/
time_t TaskGetTimeToRun(const task_t *task)
{
	assert(task);
	
	return task->time_to_execute;
	
}

/********************  TaskSetTimeToRun  ****************************/
void TaskSetTimeToRun(task_t *task)
{
	task->time_to_execute = time(NULL) + + interval_in_sec;
}

/********************  TaskRun  ****************************/
int TaskRun(task_t *task)
{
	return task->func(task->param);
}
		 


