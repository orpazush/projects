/****************************************************************************
 *						code by : orpaz Houta								*
 *						review by : Gil Steinberg							*
 *						coding date : 11.6.20								*
 ***************************************************************************/
#ifndef __HEAP_SCHEDULER_H__
#define __HEAP_SCHEDULER_H__

#include "uid.h"

typedef struct heap_scheduler heap_scheduler_t;

/*****************************************************************************
 * Function: a user's function 												 *
 * ------------------------------------------------------------------------- *
 * an operation to be execute when it in the heap_scheduler					 *
 *																			 *
 * param: void *, some information the function could need 					 *
 *																			 *
 * returns: SUCCESS or FAIL (0 or 1)										 *
 *****************************************************************************/
typedef int (*action_func_t)(void *param);


/*****************************************************************************
 * Function: HeapSchdCreate | time complexity O(1)							 *
 * ------------------------------------------------------------------------- *
 * creates a new empty heap_scheduler 										 *
 *																			 *
 * returns: heap_scheduler_t *, pointer to the heap_scheduler                *
 * or NULL in case of error                                                  *
 *****************************************************************************/
 heap_scheduler_t *HeapSchdCreate(void);


/*****************************************************************************
 * Function: HeapSchdDestroy | time complexity O(n) 						 *
 * ------------------------------------------------------------------------- *
 * destroy the given 'sch' and frees all its allocated memory				 *
 *																			 *
 * sch: heap_scheduler_t *, pointer to the heap_scheduler					 *
 *																			 *
 * returns: NONE															 *
 *****************************************************************************/
 void HeapSchdDestroy(heap_scheduler_t *sch);


/*****************************************************************************
 * Function: HeapSchdRun 						 							 *
 * ------------------------------------------------------------------------- *
 * activate the given 'sch' end execute every task in it at the right time   *
 * NOTE - after calling 'HeapSchdRun' it will stop only in two cases,    	 *
 *		  1. all the tasks in it was removed and the container is empty		 *
 *		  2. the function 'HeapSchdStop' is executed						 *
 *		  it's the user's responsibility to add the function 'HeapSchdStop'  *
 *		  into the heap_scheduler befor activate it, otherwise it might 	 *
 *		  cause an infinite loop. 											 *
 *																			 *
 * sch: heap_scheduler_t *, pointer to the heap_scheduler					 *
 *																			 *
 * returns: NONE															 *
 *****************************************************************************/
 void HeapSchdRun(heap_scheduler_t *sch);


/*****************************************************************************
 * Function: HeapSchdStop | time complexity O(1) 							 *
 * ------------------------------------------------------------------------- *
 * Stops the execution of a given heap_scheduler 'sch'. After the call the   *
 * HeapSchdStop all the tasks and wait for instructions. This function does  *
 * not remove the tasks from the 'sch'. 									 *
 * NOTE - Its the user's responsibility to add it to the 'sch' befor 		 *
 * 		  calling 'HeapSchdRun'												 *
 *																			 *
 * sch: heap_scheduler_t *, pointer to the heap_scheduler					 *
 *											 								 *
 * returns: NONE															 *
 *****************************************************************************/
 void HeapSchdStop(heap_scheduler_t *sch);


/*****************************************************************************
 * Function: HeapSchdAdd | time complexity O(n) | memory complexity O(1) 	 *
 * ------------------------------------------------------------------------- *
 * add a new task to the the given heap_scheduler 'sch'						 *
 *																			 *
 * sch: heap_scheduler_t *, pointer to the heap_scheduler 					 *
 * call_func: action_func_t, a user's function to be execute 				 *
 * interval: size_t, the amount of time in seconds to wait between executions*
 * param: void *, param to be used by the action_func_t 					 *
 *																			 *
 * ilrd_uid_t: task_id, the identifier of the new task 						 *
 *****************************************************************************/
 ilrd_uid_t HeapSchdAdd(heap_scheduler_t *sch, action_func_t action,
						size_t interval, void *param);


/*****************************************************************************
 * Function: HeapSchdRemove | time complexity O(n) 							 *
 * ------------------------------------------------------------------------- *
 * seeks a specific task according to it's uid 'task_id'					 *
 * and erase it from the given 'heap_scheduler' container					 *
 * NOTE - should be added to the schedular when desire to stop execution 	 *
 * 		  of specific task													 *
 *																			 *
 * heap_scheduler: const heap_scheduler_t *, pointer to the heap_scheduler   *
 * ilrd_uid_t: task_id, the identifier of the task to be removed			 *
 *																			 *
 * returns: SUCCESS or FAIL (0 or 1)										 *
 *****************************************************************************/
 int HeapSchdRemove(heap_scheduler_t *sch, ilrd_uid_t task_id);


/*****************************************************************************
 * Function: HeapSchdSize | time complexity O(n) 							 *
 * ------------------------------------------------------------------------- *
 * counts the number of different tasks in a given 'sch' container 			 *
 *																			 *
 * sch: const heap_scheduler_t *, pointer to the heap_scheduler 			 *
 *																			 *
 * returns: size_t, the number of elements in the 'heap_scheduler' container *
 *****************************************************************************/
 size_t HeapSchdSize(const heap_scheduler_t *sch);


/*****************************************************************************
 * Function: HeapSchdIsEmpty | time complexity O(1) 						 *
 * ------------------------------------------------------------------------- *
 * checks whether a given 'sch' is empty of tasks   						 *
 *																			 *
 * heap_scheduler: const heap_scheduler_t *, pointer to the heap_scheduler 	 *
 *																			 *
 * returns: int, return 1 if empty and 0 if not								 *
 *****************************************************************************/
 int HeapSchdIsEmpty(const heap_scheduler_t *sch);


/*****************************************************************************
 * Function: HeapSchdClear | time complexity O(n) 							 *
 * ------------------------------------------------------------------------- *
 * gets heap_scheduler 'sch' and removes all its tasks until it's empty		 *
 * 																			 *
 * heap_scheduler: const heap_scheduler_t *, pointer to the heap_scheduler 	 *
 *																			 *
 * returns: NONE															 *
 *****************************************************************************/
 void HeapSchdClear(heap_scheduler_t *sch);


#endif /* ifdef __HEAP_SCHEDULER_H__ */
