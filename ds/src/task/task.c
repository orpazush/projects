/****************************************************************************
 *						code by : orpaz Houta								*
 *						review by : Gil S									*
 *						coding date : 28->4->20								*
 ***************************************************************************/

#include <unistd.h>	/* sleep, time_t */
#include <malloc.h>	/* malloc */
#include <assert.h>	/* assert */

#include "task.h"
#include "uid.h"

struct task
{
	ilrd_uid_t task_id;
	size_t interval;
	action_func call_func;
	void *func_param;
	time_t run_time;
};


task_t *TaskCreateTask(action_func call_func, size_t interval, void *param)
{
	task_t *new = (task_t *)malloc(sizeof(task_t));
	if (!new)
	{
#ifndef NDEBUG
		perror("TaskCreateTask: ");
#endif
		return NULL;
	}
	new->task_id = UIDCreate();
	new->run_time = 0;
	new->interval = interval;
	new->call_func = call_func;
	new->func_param = param;

	return new;
}


void TaskDestroy(task_t *task)
{
	task->func_param = NULL;

	free(task);
	task = NULL;
}


time_t TaskGetTime(task_t *task)
{
	assert(task);

	return task->run_time;
}


ilrd_uid_t TaskGetUID(task_t *task)
{
	assert(task);

	return task->task_id;
}


int Taskexecute(task_t *task)
{
	assert(task);

	return task->call_func(task->func_param);
}


void TaskUpdateTime(task_t *task)
{
	task->run_time = time(NULL) + task->interval;
}


void TaskPause(task_t *task)
{
/*	printf("sleep %ld\n",TaskGetTime(task) - time(NULL));*/
	if (0 < (TaskGetTime(task) - time(NULL)))
	{
		while(sleep(TaskGetTime(task) - time(NULL)));
	}
}
