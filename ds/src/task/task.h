/****************************************************************************
 *						code by : orpaz Houta								*
 *						review by : Gil S									*
 *						coding date : 28.4.20								*
 ***************************************************************************/
#ifndef __TASK_H__
#define __TASK_H__

#include <unistd.h> /* time_t */

#include "uid.h"
#include "scheduler.h"

typedef struct task task_t;


/*****************************************************************************
 * Function: TaskCreateTask | time complexity O(1)							 *
 * ------------------------------------------------------------------------- *
 * creates a new task and initial it's details								 *
 *																			 *
 * call_func: action_func, a user's function to execute 					 *
 * interval: size_t, the amount of time in seconds to wait between executions*
 * param: void *, param to be used by the action_func 						 *
 *																			 *
 * task: task_t *, pointer to the task 										 *
 ****************************************************************************/
task_t *TaskCreateTask(action_func call_func, size_t interval, void *param);


/*****************************************************************************
 * Function: TaskDestroy | time complexity O(1)     						 *
 * ------------------------------------------------------------------------- *
 * destroy the given 'task' 												 *
 *																			 *
 * task: task_t *, pointer to the task 										 *
 *																			 *
 * returns: NONE															 *
 ****************************************************************************/
void TaskDestroy(task_t *task);


/*****************************************************************************
 * Function: TaskGetTime | time complexity O(1) 							 *
 * ------------------------------------------------------------------------- *
 * task: task_t *, pointer to the task 										 *
 *																			 *
 * returns: the time of  												 	 *
 ****************************************************************************/
time_t TaskGetTime(task_t *task);


/*****************************************************************************
 * Function: TaskGetUID | time complexity O(1) 								 *
 * ------------------------------------------------------------------------- *
 * task: task_t *, pointer to the task 									 	 *
 *											 								 *
 * returns: the uniqu identifier of a given 'task'							 *
 *****************************************************************************/
ilrd_uid_t TaskGetUID(task_t *task);


/*****************************************************************************
 * Function: TaskCmp | time complexity O(1) 								 *
 * ------------------------------------------------------------------------- *
 * compares the time to be execute of two given tasks						 *
 *																			 *
 * task1: task_t *, pointer to task to compare 								 *
 * task2: task_t *, pointer to the to compare 								 *
 *																			 *
 * returns: int, (+) 'task1' should be execute first 						 *
 * 				 (-) 'task2' should be execute first						 *
 *				 (0) they are even 											 *
 ****************************************************************************/
int TaskCmp(task_t *task1, task_t *task2);


/*****************************************************************************
 * Function: Taskexecute | time complexity O(1) 							 *
 * ------------------------------------------------------------------------- *
 * execute a given 'task'													 *
 *																			 *
 * task: task_t *, pointer to the task 										 *
 *																			 *
 * returns: SUCCESS or FAIL (0 or 1)										 *
 ****************************************************************************/
int Taskexecute(task_t *task);


/*****************************************************************************
 * Function: TaskUpdateTime | time complexity O(1) 								 *
 * ------------------------------------------------------------------------- *
 * update the time that the task should be execute to the next execution	 *
 *																			 *
 * task: task_t *, pointer to the task 										 *
 *											 								 *
 * returns: NONE															 *
 *****************************************************************************/
void TaskUpdateTime(task_t *task);


/*****************************************************************************
 * Function: TaskPause | time complexity O(n) 								 *
 * ------------------------------------------------------------------------- *
 * pause the execution of a given task the amount of time left to her execution*
 *																			 *
 * task: task_t *, pointer to the task 										 *
 *											 								 *
 * returns: NONE															 *
 *****************************************************************************/
void TaskPause(task_t *task);

#endif
