/****************************************************************************
 * 						written by: Orpaz Houta								*
 * 						review: Alex Sevostyanov							*
 * 						Last update: 26.4.20 								*
 ***************************************************************************/
#include <stddef.h> /* size_t */
#include <malloc.h> /* malloc */
#include <assert.h>	/* assert */

#include "sorted_list.h"	/* sorted_list_t */
#include "pqueue.h"			/* pqueue_t */


struct pqueue
{
	sorted_list_t *sorted_list;
	cmp_func Compare;
};

int IsBeforPQ(const void *data1, const void *data2, const void *param)
{
	return (0 <= ((pqueue_t *)param)->Compare(data1, data2));
}

pqueue_t *PQueueCreate(cmp_func cmp)
{
	pqueue_t *new = NULL;

    assert(cmp);

	new = (pqueue_t *)malloc(sizeof(pqueue_t));
	if (!new)
	{
#ifndef NDEBUG
		perror("malloc error in PQueueCreate:");
#endif
		return NULL;
	}
	new->sorted_list = SortedListCreate(IsBeforPQ, new);
	if (!new->sorted_list)
	{
#ifndef NDEBUG
		perror("malloc error in SortedListCreate:");
#endif
		free(new);
		new = NULL;

		return NULL;
	}

	new->Compare = cmp;

	return new;
}

void PQueueDestroy(pqueue_t *pqueue)
{
	assert(pqueue);

	SortedListDestroy(pqueue->sorted_list);
	pqueue->sorted_list =NULL;

	free(pqueue);
	pqueue = NULL;
}

int EnPQueue(pqueue_t *pqueue, void *data)
{
	assert (pqueue);

	return SortedListIsEqual(SortedListInsert(pqueue->sorted_list, data),
										 SortedListEnd(pqueue->sorted_list));
}

void DePQueue(pqueue_t *pqueue)
{
	assert (pqueue);

	SortedListPopFront(pqueue->sorted_list);
}

void *PQueuePeek(const pqueue_t *pqueue)
{
	assert (pqueue);

	return SortedListGetData(SortedListBegin(pqueue->sorted_list));
}

size_t PQueueSize(const pqueue_t *pqueue)
{
	assert (pqueue);

	return SortedListSize(pqueue->sorted_list);
}

int PQueueIsEmpty(const pqueue_t *pqueue)
{
	assert (pqueue);

	return SortedListIsEmpty(pqueue->sorted_list);
}

void PQueueClear(pqueue_t *pqueue)
{
	assert (pqueue);

	while (!PQueueIsEmpty(pqueue))
	{
		DePQueue(pqueue);
	}
}

void *PQueueErase(pqueue_t *pqueue, is_match_func is_match, void *param)
{
	void *peek = NULL;

	assert (pqueue);

	peek = SortedListGetData(SortedListFindIf(SortedListBegin
				(pqueue->sorted_list), SortedListEnd(pqueue->sorted_list),
														 is_match, param));
	if (peek != SortedListGetData(SortedListEnd(pqueue->sorted_list)))
	{
		SortedListRemove(SortedListFindIf(SortedListBegin(pqueue->sorted_list),
						 SortedListEnd(pqueue->sorted_list), is_match, param));
	}
	return peek;
}
