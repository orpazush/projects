/****************************************************************************
 *						code by : orpaz Houta								*
 *						review by : Gil Steinberg							*
 *						coding date : 11.6.20								*
 ***************************************************************************/
#include <malloc.h> 		/* malloc */
#include <assert.h>			/* assert */
#include <unistd.h>			/* sleep, size_t*/

#include "task.h"			/* task_t */
#include "heap_pq.h"		/* heap_pq_t */

#include "heap_scheduler.h"

struct heap_scheduler
{
	heap_pq_t *container;
	task_t *save_task;
	int state;
};

#define HEAP_SCHD_SUCCESS (0)
#define HEAP_SCHD_FAIL (1)

#define RUN (0)
#define STOP (1)

static void HeapSchdInit(heap_scheduler_t *sch);
static int HeapSchdCmpTask(const void *task1, const void *task2);
static int HeapSchdIsMatch(const void *task, const void *uid);

heap_scheduler_t *HeapSchdCreate(void)
{
	heap_scheduler_t *new = (heap_scheduler_t *)malloc(sizeof(heap_scheduler_t));
	if (!new)
	{
#ifndef NDEBUG
		perror("HeapSchdCreate");
#endif
		return NULL;
	}

	new->container = HeapPQCreate(HeapSchdCmpTask);
	if (!new->container)
	{
#ifndef NDEBUG
		perror("HeapPQCreate");
#endif
		free(new);
		new = NULL;
		return NULL;
	}

	new->save_task = NULL;
	new->state = RUN;
	return new;
}

void HeapSchdDestroy(heap_scheduler_t *sch)
{
	assert(sch);

	HeapSchdClear(sch);

	HeapPQDestroy(sch->container);
	sch->container = NULL;

	free(sch);
	sch = NULL;
}

ilrd_uid_t HeapSchdAdd(heap_scheduler_t *sch, action_func action,
					   size_t interval, void *param)
{
	task_t *new = NULL;

	assert(sch);
	assert(action);
	assert(param);

	new = TaskCreateTask(action, interval, param);
	if (!new || HEAP_SCHD_FAIL == HeapEnPQ(sch->container, new))
	{
		TaskDestroy(new);
		return g_bad_ilrd_uid;
	}

	return TaskGetUID(new);
}

int HeapSchdRemove(heap_scheduler_t *sch, ilrd_uid_t task_id)
{
	void *to_free = 0;

	assert(sch);

	to_free = HeapPQErase(sch->container, HeapSchdIsMatch, &task_id);
	if (!to_free)
	{
		return HEAP_SCHD_FAIL;
	}
	TaskDestroy(to_free);

	return HEAP_SCHD_SUCCESS;
}

void HeapSchdRun(heap_scheduler_t *sch)
{
	int exec_stat = HEAP_SCHD_SUCCESS;

	assert(sch);

	sch->state = RUN;

	HeapSchdInit(sch);	/* updates time of all the tasks to solve situation that
						   passed time between add and run.. */
	while (STOP != sch->state && !HeapSchdIsEmpty(sch))
	{
		sch->save_task = HeapPQPeek(sch->container);
		HeapDePQ(sch->container);
		TaskPause(sch->save_task);

		exec_stat = Taskexecute(sch->save_task);
		if (HEAP_SCHD_SUCCESS == exec_stat)
		{
			TaskUpdateTime(sch->save_task);
			HeapEnPQ(sch->container, sch->save_task);
		}
		else
		{
			TaskDestroy(sch->save_task);
		}
	}
}

void HeapSchdStop(heap_scheduler_t *sch)
{
	assert(sch);

	sch->state = STOP;
}

size_t HeapSchdSize(const heap_scheduler_t *sch)
{
	assert(sch);

	return HeapPQSize(sch->container);
}

int HeapSchdIsEmpty(const heap_scheduler_t *sch)
{
	assert(sch);

	return HeapPQIsEmpty(sch->container);
}

void HeapSchdClear(heap_scheduler_t *sch)
{
	assert(sch);

	while (!HeapSchdIsEmpty(sch))
	{
        sch->save_task = HeapPQPeek(sch->container);
        TaskDestroy(sch->save_task);
        HeapDePQ(sch->container);
	}
}

static int HeapSchdCmpTask(const void *task1, const void *task2)
{
	return (TaskGetTime((task_t *)task2) - TaskGetTime((task_t *)task1));
}

static int HeapSchdIsMatch(const void *task, const void *uid)
{
	return UIDIsSame(TaskGetUID((task_t *)task), *(ilrd_uid_t *)uid);
}

static void HeapSchdInit(heap_scheduler_t *sch)
{
	sch->save_task = HeapPQPeek(sch->container);

	while (0 == TaskGetTime(sch->save_task))
	{
		TaskUpdateTime(sch->save_task);
		HeapDePQ(sch->container);
		HeapEnPQ(sch->container, sch->save_task);
		sch->save_task = HeapPQPeek(sch->container);
	}
}
