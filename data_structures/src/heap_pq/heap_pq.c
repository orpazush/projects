/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review : Gil Steinberg  						         *
 * 					Last update : 9.6.20									 *
 *---------------------------------------------------------------------------*
 * Priority Queue is more specialized data structure than Queue.             *
 * Like ordinary queue, priority queue has same method but with a major      *
 * difference. In Priority queue items are ordered by key value so that      *
 * item with the lowest value of key is at front and item with the highest   *
 * value of key is at rear or vice versa. So we're assigned priority to item *
 * based on its key value. Lower the value, higher the priority. Following   *
 * are the principal methods of a Priority Queue.                            *
 ****************************************************************************/

#include <stddef.h> /* size_t */
#include <malloc.h> /* malloc */
#include <assert.h>	/* assert */

#include "heap.h"   /* heap_t */
#include "heap_pq.h"	/* heap_pq_t */


struct heap_pq
{
	heap_t *container;
	cmp_func compare;
};

#ifndef NDEBUG
#define PRINT_ERROR(str) fprintf(stderr, "ERROR( %s : %d ) -- %s\n",\
                                 __FILE__, __LINE__, str)
#else
#define PRINT_ERROR(str)
#endif


heap_pq_t *HeapPQCreate(cmp_func cmp)
{
	heap_pq_t *new = NULL;

    assert(cmp);

    new = (heap_pq_t *)malloc(sizeof(heap_pq_t));
	if (!new)
	{
		PRINT_ERROR("malloc error in HeapPQCreate");

		return (NULL);
	}

    new->container = HeapCreate(cmp);
    if (!new->container)
	{
		PRINT_ERROR("malloc error in HeapPQCreate");

        free(new);
        new = NULL;

		return (NULL);
	}

	new->compare = cmp;

	return (new);
}

void HeapPQDestroy(heap_pq_t *heap_pq)
{
	assert(heap_pq);

	HeapDestroy(heap_pq->container);
	heap_pq->container = NULL;
	heap_pq->compare = NULL;

	free(heap_pq);
	heap_pq = NULL;
}

int HeapEnPQ(heap_pq_t *heap_pq, void *data)
{
	assert(heap_pq);

	return (HeapPush(heap_pq->container, data));
}

void HeapDePQ(heap_pq_t *heap_pq)
{
	assert(heap_pq);

	HeapPop(heap_pq->container);
}

void *HeapPQPeek(const heap_pq_t *heap_pq)
{
	assert(heap_pq);

	return (HeapPeek(heap_pq->container));
}

size_t HeapPQSize(const heap_pq_t *heap_pq)
{
	assert(heap_pq);

	return (HeapSize(heap_pq->container));
}

int HeapPQIsEmpty(const heap_pq_t *heap_pq)
{
	assert(heap_pq);

	return (HeapIsEmpty(heap_pq->container));
}

void HeapPQClear(heap_pq_t *heap_pq)
{
	assert(heap_pq);

	while (!HeapPQIsEmpty(heap_pq))
	{
		HeapDePQ(heap_pq);
	}
}

void *HeapPQErase(heap_pq_t *heap_pq, is_match_func is_match, void *param)
{
	assert(heap_pq);

	return (HeapRemove(heap_pq->container, is_match, param));
}
