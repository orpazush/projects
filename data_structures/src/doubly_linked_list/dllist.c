/****************************************************************************
 *					written by : Orpaz Houta								*
 * 					review : Tali Rephael									*
 * 					Last update : 19.4.20									*
 ***************************************************************************/

#include <malloc.h>	/* malloc */
#include <assert.h>	/* assert */

#include "dllist.h"

#define SUCCESS (0)
#define ERROR (1)
#define MATCH (1)

typedef struct dllist_node
{
	void *data;
	iterator_t prev;
	iterator_t next;
}node_t;

struct dllist
{
	iterator_t front;
	iterator_t rear;
};

/* Gil I'm totally converted */
void DLListConnect(iterator_t iterator1, iterator_t iterator2);

iterator_t CreateIterator(void);


dllist_t *DLListCreate(void)
{
	dllist_t *list = (dllist_t *)malloc(sizeof(dllist_t));
	if (!list)
	{
#ifndef NDEBUG
		perror("malloc error in creating list: ");
#endif
		return NULL;
	}
	list->front = CreateIterator();
	if (!list->front)
	{
		free(list);
		list = NULL;

		return NULL;
	}
	list->rear = CreateIterator();
	if (!list->rear)
	{
		free(list);
		list = NULL;

		free(list->front);
		list->front = NULL;

		return NULL;
	}

	DLListConnect(list->front, list->rear);

	return list;
}

void DLListDestroy(dllist_t *list)
{
	iterator_t to_free = DLListBegin(list);

	while (!DLListIsSameIterator(to_free, DLListEnd(list)))
	{
		to_free = DLListRemove(to_free);
	}
	free(list->front);
	list->front = NULL;

	free(list->rear);
	list->rear = NULL;

	free(list);
	list = NULL;
}

iterator_t DLListInsert(iterator_t where, void *data)
{
	iterator_t new;

	assert (where);
	assert (data);

	new = CreateIterator();

	if (!new)
	{
		while(DLListNext(where))
		{
			where = DLListNext(where);
		}
		return where;
	}
	DLListSetData(new, data);
	DLListConnect(DLListPrev(where), new);
	DLListConnect(new, where);

	return new;
}

iterator_t DLListRemove(iterator_t who)
{
	iterator_t next = NULL;

	assert(who);

	next = DLListNext(who);

	DLListConnect(DLListPrev(who), next);

	who->data = NULL;

	free(who);
	who = NULL;

	return next;
}

int DLListIsEmpty(const dllist_t *list)
{
	assert (list);

	return (DLListIsSameIterator(DLListBegin(list), DLListEnd(list)));
}

size_t DLListSize(const dllist_t *list)
{
	size_t size = 0;
	iterator_t to_count = DLListBegin(list);

	assert (list);

	while (to_count != DLListEnd(list))
	{
		to_count = DLListNext(to_count);
		++size;
	}
	return size;
}

iterator_t DLListBegin(const dllist_t *list)
{
	assert (list);

	return list->front->next ;
}

iterator_t DLListEnd(const dllist_t *list)
{
	assert (list);

	return list->rear;
}

iterator_t DLListNext(iterator_t iterator)
{
	assert(iterator);

	return iterator->next;
}

iterator_t DLListPrev(iterator_t iterator)
{
	assert(iterator);

	return iterator->prev;
}

int DLListIsSameIterator(iterator_t iterator1, iterator_t iterator2)
{
	assert(iterator1);
	assert(iterator2);

	return (iterator1 == iterator2);
}

void *DLListGetData(iterator_t iterator)
{
	assert (iterator);

	return iterator->data;
}

void DLListSetData(iterator_t iterator, void *data)
{
	assert (iterator);
	assert (data);

	iterator->data = data;
}

void *DLListPopFront(dllist_t *list)
{
	void *peek = NULL;

	assert(list);

	peek = DLListGetData(DLListBegin(list));
	DLListRemove(DLListBegin(list));

	return peek;
}

void *DLListPopBack(dllist_t *list)
{
	void *peek = NULL;

	assert (list);

	peek = DLListGetData(DLListPrev(DLListEnd(list)));
	DLListRemove(DLListPrev(DLListEnd(list)));

	return peek;
}

iterator_t DLListPushFront(dllist_t *list, void *data)
{
	assert (list);
	assert (data);

	return DLListInsert(DLListBegin(list), data);
}

iterator_t DLListPushBack(dllist_t *list, void *data)
{
	assert (list);

	return DLListInsert(DLListEnd(list), data);
}

iterator_t DLListFind(iterator_t from, iterator_t to,
									match_func_t is_match, const void *param)
{
	iterator_t to_match = from;

	assert(from);
	assert(to);

	while (!DLListIsSameIterator(to_match, to))
	{
		if (MATCH == is_match(DLListGetData(to_match), param))
		{
			return to_match;
 		}
		to_match = DLListNext(to_match);
 	}
	return to;
}

int DLListForEach(iterator_t from, iterator_t to, action_func_t action,
				  void *param)
{
	iterator_t to_operate_on = from;
	int status = SUCCESS;

	assert(from);
	assert(to);
	assert(param);

	while (!DLListIsSameIterator(to_operate_on, to) && SUCCESS == status)
	{
		status = action(DLListGetData(to_operate_on), param);
		to_operate_on = DLListNext(to_operate_on);
	}

	return status;
}

iterator_t DLListSplice(iterator_t where, iterator_t from, iterator_t to)
{
	iterator_t to_prev = DLListPrev(to);

	assert(from);
	assert(to);
	assert(where);

	DLListConnect(DLListPrev(from), to);
	DLListConnect(DLListPrev(where), from);
	DLListConnect(to_prev, where);

	return where;
}

int DLListMultiFind(iterator_t from, iterator_t to, match_func_t is_match,
									const void *param, dllist_t *found_list)
{
	iterator_t to_match = from;
	int match = 0;

	assert(from);
	assert(to);
	assert(found_list);

	while (!DLListIsSameIterator(to_match,to))
	{
		match = is_match(DLListGetData(to_match), param);
		if (match)
		{
			if (DLListEnd(found_list) == DLListPushBack(found_list,
													 DLListGetData(to_match)))
			{
				return ERROR;
			}
		}
		else if (0 < match)
		{
			return match;
		}
		to_match = DLListNext(to_match);
	}
	return SUCCESS;
}


/* function for my use in nodes */
void DLListConnect(iterator_t iterator1, iterator_t iterator2)
{
	iterator2->prev = iterator1;
	iterator1->next = iterator2;
}

iterator_t CreateIterator(void)
{
	node_t *new = (node_t *)malloc(sizeof(node_t));
	if (!new)
	{
#ifndef NDEBUG
		perror("malloc error in creating list: ");
#endif
		return NULL;
	}
	new->data = NULL;
	new->prev = NULL;
	new->next = NULL;

	return new;
}
