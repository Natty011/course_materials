/******************************************************************************
*	Version 0.2
******************************************************************************/
#ifndef __TASK_H__      /* __TASK_H__  */
#define __TASK_H__      /* __TASK_H__  */

#include <time.h>
#include "uid.h"

/*
Private API Example, this API does not have to be shared
*/

typedef struct task task_t;

task_t * TaskCreate(int (*op_func)(void *user_param), void *user_param, size_t interval_in_sec);
void TaskDestroy(task_t *task);
/*  returns : success(0 = finished),not_finished (1 = should repeat), ( -1 = fail) */
int TaskRun(task_t *task);
ilrd_uid_t TaskGetUID(const task_t *task);
time_t TaskGetTimeToRun(const task_t *task);
void TaskSetTimeToRun(task_t *task);

#endif                  /* __TASK_H__  */
