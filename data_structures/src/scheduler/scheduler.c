/****************************************************************************
 *						code by : orpaz Houta								*
 *						review by : Gil S									*
 *						coding date : 28.4.20								*
 ***************************************************************************/
#include <malloc.h> /* malloc */
#include <assert.h>	/* assert */
#include <unistd.h>	/* sleep, size_t*/

#include "scheduler.h"
#include "task.h"
#include "pqueue.h"

struct scheduler
{
	pqueue_t *container;
	task_t *save_task;
	int state;
};

#define SUCCESS (0)
#define FAILURE (1)

#define RUN (0)
#define STOP (1)

static void SchdInit(scheduler_t *sch);
static int SchdCmpTask(const void *task1, const void *task2);
static int SchdIsMatch(const void *task, const void *uid);

scheduler_t *SchdCreate(void)
{
	scheduler_t *new = (scheduler_t *)malloc(sizeof(scheduler_t));
	if (!new)
	{
#ifndef NDEBUG
		perror("SchdCreate: ");
#endif
		return NULL;
	}

	new->container = PQueueCreate(SchdCmpTask);
	if (!new->container)
	{
#ifndef NDEBUG
		perror("PQueueCreate: ");
#endif
		free(new);
		new = NULL;
		return NULL;
	}

	new->save_task = NULL;
	new->state = 0;
	return new;
}


void SchdDestroy(scheduler_t *sch)
{
	assert(sch);

	SchdClear(sch);

	PQueueDestroy(sch->container);
	sch->container = NULL;

	free(sch);
	sch = NULL;
}


ilrd_uid_t SchdAdd(scheduler_t *sch, action_func action, size_t interval,
																void *param)
{
	task_t *new = NULL;

	assert(sch);
	assert(action);
	assert(param);

	new = TaskCreateTask(action, interval, param);
	if (!new || FAILURE == EnPQueue(sch->container, new))
	{
		TaskDestroy(new);
		return g_bad_ilrd_uid;
	}

	return TaskGetUID(new);
}


int SchdRemove(scheduler_t *sch, ilrd_uid_t task_id)
{
	void *to_free = 0;

	assert(sch);

	to_free = PQueueErase(sch->container, SchdIsMatch, &task_id);
	if (!to_free)
	{
		return FAILURE;
	}
	TaskDestroy(to_free);

	return SUCCESS;
}


void SchdRun(scheduler_t *sch)
{
	int exec_stat = SUCCESS;
	assert(sch);
	sch->state = RUN;

	SchdInit(sch);	/* update time of all the tasks to solve situation that
						passed time between add and run.. */
	printf("size: %ld, ", SchdSize(sch));
	while (STOP != sch->state && !SchdIsEmpty(sch))
	{
		sch->save_task = PQueuePeek(sch->container);
		DePQueue(sch->container);
		TaskPause(sch->save_task);

		exec_stat = Taskexecute(sch->save_task);
		if (SUCCESS == exec_stat)
		{
			TaskUpdateTime(sch->save_task);
			EnPQueue(sch->container, sch->save_task);
		}
		else
		{
			TaskDestroy(sch->save_task);
		}
	}
}

void SchdStop(scheduler_t *sch)
{
	assert(sch);

	sch->state = STOP;
}

size_t SchdSize(const scheduler_t *sch)
{
	assert(sch);

	return PQueueSize(sch->container);
}

int SchdIsEmpty(const scheduler_t *sch)
{
	assert(sch);

	return PQueueIsEmpty(sch->container);
}


void SchdClear(scheduler_t *sch)
{
	assert(sch);

	while (!SchdIsEmpty(sch))
	{
        sch->save_task = PQueuePeek(sch->container);
        TaskDestroy(sch->save_task);
        DePQueue(sch->container);
	}
}


static int SchdCmpTask(const void *task1, const void *task2)
{
	return (TaskGetTime((task_t *)task2) - TaskGetTime((task_t *)task1));
}


static int SchdIsMatch(const void *task, const void *uid)
{
	return UIDIsSame(TaskGetUID((task_t *)task), *(ilrd_uid_t *)uid);
}


static void SchdInit(scheduler_t *sch)
{
	sch->save_task = PQueuePeek(sch->container);

	while (0 == TaskGetTime(sch->save_task))
	{
		TaskUpdateTime(sch->save_task);
		DePQueue(sch->container);
		EnPQueue(sch->container, sch->save_task);
		sch->save_task = PQueuePeek(sch->container);
	}
}
