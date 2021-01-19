/****************************************************************************
 *                   written by :orpaz houta								*
 *                   review : Gil Mazliah (Gilio):)							*
 *                   Last update : 12.4.20									*
 ***************************************************************************/

#include <stddef.h> /* size_t */
#include <malloc.h> /* malloc, free */
#include <assert.h>	/* assert */

#include "sllist.h" /* list_t */
#include "queue.h"

struct queue
{
	list_t *list;
};

queue_t *QueueCreate(void)
{
	queue_t *queue = (queue_t *)malloc(sizeof(queue_t));
	if (!queue)
	{
#ifndef NDEBUG
		perror("malloc error in creating queue:");
#endif
		return NULL;
	}
	queue->list = SLListCreate();
	return queue;
}

void QueueDestroy(queue_t *queue)
{
	SLListDestroy(queue->list);
	free(queue);	
}

int EnQueue(queue_t *queue, void *data)
{
	assert (NULL != queue);

	return (!(SLListInsert(SLListEnd(queue->list), data)));
}

void DeQueue(queue_t *queue)
{
	assert (NULL != queue);

	SLListRemove(SLListBegin(queue->list));
}

void *QueuePeek(const queue_t *queue)
{
	assert (NULL != queue);

	return SLListGetData(SLListBegin(queue->list));
}

size_t QueueSize(const queue_t *queue)
{
	assert (NULL != queue);

	return SLListCount(queue->list);
}

int QueueIsEmpty(const queue_t *queue)
{
	assert (NULL != queue);

	return SLListIsEmpty(queue->list);
}

void QueueAppend(queue_t *queue1, queue_t *queue2)
{
	assert (NULL != queue1);

	SLListAppend(queue1->list, queue2->list);
	free(queue2);
	queue2 = NULL;
}




