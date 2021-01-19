/****************************************************************************
 *						code by : orpaz Houta								*
 *						review by : Gil S									*
 *						coding date : 28.4.20								*
 ***************************************************************************/
#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

#include "uid.h"

typedef struct scheduler scheduler_t;


/*****************************************************************************
 * Function: a user's function 												 *
 * ------------------------------------------------------------------------- *
 * an operation to be execute when it in the scheduler						 *
 *																			 *
 * param: void *, some information the function could need 					 *
 *																			 *
 * returns: SUCCESS or FAIL (0 or 1)										 *
 *****************************************************************************/
typedef int (*action_func)(void *param);


/*****************************************************************************
 * Function: SchdCreate | time complexity O(1)								 *
 * ------------------------------------------------------------------------- *
 * creates a new empty scheduler 											 *
 *																			 *
 * returns: scheduler_t *, pointer to the scheduler or NULL in case of error *
 *****************************************************************************/
 scheduler_t *SchdCreate(void);


/*****************************************************************************
 * Function: SchdDestroy | time complexity O(n) 							 *
 * ------------------------------------------------------------------------- *
 * destroy the given 'sch' and frees all its allocated memory				 *
 *																			 *
 * sch: scheduler_t *, pointer to the scheduler								 *
 *																			 *
 * returns: NONE															 *
 *****************************************************************************/
 void SchdDestroy(scheduler_t *sch);


/*****************************************************************************
 * Function: SchdRun 						 								 *
 * ------------------------------------------------------------------------- *
 * activate the given scheduler end execute every task in it at the right time
 * NOTE - after calling 'SchdRun' it will stop only in two cases,    		 *
 *		  1. all the tasks in it was removed and the container is empty		 *
 *		  2. the function 'SchdStop' is executed							 *
 *		  it's the user's responsibility to add the function 'SchdStop' into *
 *		  the scheduler befor activate it, otherwise it might cause an		 *
 *		  infinite loop. 													 *
 *																			 *
 * sch: scheduler_t *, pointer to the scheduler								 *
 *																			 *
 * returns: NONE															 *
 *****************************************************************************/
 void SchdRun(scheduler_t *sch);


/*****************************************************************************
 * Function: SchdStop | time complexity O(1) 								 *
 * ------------------------------------------------------------------------- *
 * Stops the execution of a given scheduler 'sch'. After the call the sch 	 *
 * stop all the tasks and wait for instructions. This function does not 	 *
 * remove the tasks from the 'sch'. 										 *
 * NOTE - Its the user's responsibility to add it to the 'sch' befor 		 *
 * 		  calling 'SchdRun'													 *
 *																			 *
 * sch: scheduler_t *, pointer to the scheduler								 *
 *											 								 *
 * returns: NONE															 *
 *****************************************************************************/
 void SchdStop(scheduler_t *sch);


/*****************************************************************************
 * Function: SchdAdd | time complexity O(n) | memory complexity O(1) 		 *
 * ------------------------------------------------------------------------- *
 * add a new task to the the given scheduler 'sch'							 *
 *																			 *
 * sch: scheduler_t *, pointer to the scheduler 							 *
 * call_func: action_func, a user's function to be execute 					 *
 * interval: size_t, the amount of time in seconds to wait between executions*
 * param: void *, param to be used by the action_func 						 *
 *																			 *
 * ilrd_uid_t: task_id, the identifier of the new task 						 *
 *****************************************************************************/
 ilrd_uid_t SchdAdd(scheduler_t *sch, action_func action, size_t interval,
																 void *param);


/*****************************************************************************
 * Function: SchdRemove | time complexity O(n) 								 *
 * ------------------------------------------------------------------------- *
 * seeks a specific task according to it's uid 'task_id'					 *
 * and erase it from the given 'scheduler' container						 *
 * NOTE - should be added to the schedular when desire to stop execution 	 *
 * 		  of specific task													 *
 *																			 *
 * scheduler: const scheduler_t *, pointer to the scheduler 				 *
 * ilrd_uid_t: task_id, the identifier of the task to be removed			 *
 *																			 *
 * returns: SUCCESS or FAIL (0 or 1)										 *
 *****************************************************************************/
 int SchdRemove(scheduler_t *sch, ilrd_uid_t task_id);


/*****************************************************************************
 * Function: SchdSize | time complexity O(n) 								 *
 * ------------------------------------------------------------------------- *
 * counts the number of different tasks in a given 'sch' container 			 *
 *																			 *
 * sch: const scheduler_t *, pointer to the scheduler 						 *
 *																			 *
 * returns: size_t, the number of elements in the 'scheduler' container 	 *
 *****************************************************************************/
 size_t SchdSize(const scheduler_t *sch);


/*****************************************************************************
 * Function: SchdIsEmpty | time complexity O(1) 							 *
 * ------------------------------------------------------------------------- *
 * checks whether a given scheduler is empty of tasks 						 *
 *																			 *
 * scheduler: const scheduler_t *, pointer to the scheduler 				 *
 *																			 *
 * returns: int, return 1 if empty and 0 if not								 *
 *****************************************************************************/
 int SchdIsEmpty(const scheduler_t *sch);


/*****************************************************************************
 * Function: SchdClear | time complexity O(n) 								 *
 * ------------------------------------------------------------------------- *
 * gets scheduler 'sch' and removes all its tasks until it's empty			 *
 * 																			 *
 * scheduler: const scheduler_t *, pointer to the scheduler 				 *
 *																			 *
 * returns: NONE															 *
 *****************************************************************************/
 void SchdClear(scheduler_t *sch);


#endif /* ifdef __SCHEDULER_H__ */
