/******************************************************************************
*	Version 0.4
******************************************************************************/
#ifndef __SCHEDULER_H__     /* __SCHEDULER_H__  */
#define __SCHEDULER_H__     /* __SCHEDULER_H__  */

#include "uid.h"

typedef struct scheduler scheduler_t;

/******************************************************************************
*
*       Description: Creates a scheduler object
*       Arguments:
*       Complexity: Dependent on the system conplexity
*       Return: An empty scheduler, return NULL on failure
*       Note: If 'scheduler' is NULL no operation will be performed
*
*/      scheduler_t *SchedulerCreate(void);
/*
******************************************************************************/

/******************************************************************************
*
*       Description: Destroies scheduler object.
*       Arguments: The scheduler to be destroyed. 
*       Complexity: 
*       Return: AAA
*       Note: If 'scheduler' is NULL no operation will be performed
*
*/      void SchedulerDestroy(scheduler_t *scheduler);
/*
******************************************************************************/

/* OLD NOTES: */
/* if fails - returns BADUID */
/* operation returns : success( finished),not_finished ( should repeat), fail */
/******************************************************************************
*
*       Description: Add a new task to the scheduler 
*       Arguments: scheduler - the scheduler data structure
*                  op_func - the task function
*                  user_param - the user parameter for the op_func
*                  interval_in_sec - the time interval which the task will run in
*       Complexity: O(n)
*       Return: Returns the new task's unique id,
*               If creation failed, returns BADUID
*       Note: Operation function return statuses:
*               * 0 = Repeat (The task is set to repeat again)
*               * 1 = Finished (The task has finished it's work)
*               * -1 = Failed (The task has encountered a failure)
*
*/      ilrd_uid_t SchedulerAdd(scheduler_t *scheduler,
                                int (*op_func)(void *user_param),
                                void *user_param, size_t interval_in_sec);
/*
******************************************************************************/

/* OLD NOTES: */
/*scheduler_t struct status "to remove": 0 for don't remove, 1 for remove
/******************************************************************************
*
*       Description: Remove a spcific task from scheduer according to UID.
*       Arguments: pointer to scheduler and UID of task to remove/
*       Complexity: O(n)
*       Return: Returns success (0), on failure (task not found), returns fail (1)
*       Note: 
*
*/      int SchedulerRemove(scheduler_t *scheduler, ilrd_uid_t task_to_remove);
/*
******************************************************************************/

/* OLD NOTES: */
/* -3 operation_fail
  -2 system fail
  0  succuss
  -1 stopped 
*/
/******************************************************************************
*
*       Description: Runs the scheduler
*       Arguments: 'scheduler' - The scheduler object
*       Complexity: N\A
*       Return: * 0 = Success
*               * -1 = Stopped
*               * -2 = System failed
*               * -3 = Task operation failed
*       Notes: * The scheduler will run all the tasks that the user added
*                before-hand
*              * The function will keep running the tasks until stopped by
*                a certain failure (system failure or operation failure) or
*                by the 'SchedulerStop' function called from a task
*              * Once the scheduler has stopped, it can be re-run
*              * When a task fails while running, it will be removed from the
*                task list and the scheduler will stop (returns 'Task operation failed')
*              * Undefined if 'scheduler' is NULL
*
*/      int SchedulerRun(scheduler_t *scheduler);
/*
******************************************************************************/

/******************************************************************************
*
*       Description: the function stop to run the scheduler/
*       Arguments: pointer to scheduler
*       Complexity: O(1)
*       Return: -
*       Note:
*
*/      void SchedulerStop(scheduler_t *scheduler);
/*
******************************************************************************/

/******************************************************************************
*
*       Description: AAA
*       Arguments: AAA
*       Complexity: AAA
*       Return: AAA
*       Note: AAA
*
*/      size_t SchedulerSize(const scheduler_t *scheduler);
/*
******************************************************************************/

/******************************************************************************
*
*       Description: Checks if the Scheduler is empty
*       Arguments: a const pointer to the scheduler
*       Complexity: o(1)
*       Return: 1 if the scheduler is empty, 0 otherwise
*       Note: n\a
*
*/      int SchedulerIsEmpty(const scheduler_t *scheduler);
/*
******************************************************************************/

/******************************************************************************
*
*       Description: AAA
*       Arguments: AAA
*       Complexity: AAA
*       Return:
*       Note: Undefind behavior if scheduler is empty
*
*/      void SchedulerClear(scheduler_t *scheduler);
/*
******************************************************************************/

#endif                      /* __SCHEDULER_H__  */
