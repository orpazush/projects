/****************************************************************************
 * 						written by : orpaz houta							*
 *						review : chanan komar								*
 * 						Last update : 12.4.20								*
 ***************************************************************************/

#include <malloc.h>	/* malloc */
#include <assert.h>	/* assert */
#include "sllist.h"

typedef struct sllist_node
{
	void *data;
	iterator_t next;
}node_t;

struct list
{
	iterator_t head;
	iterator_t tail;
};

list_t *SLListCreate(void)
{
	list_t *list = (list_t *)malloc(sizeof(struct list));
	 iterator_t dummy = (node_t *)malloc(sizeof(node_t));
	
	if (NULL == list || NULL == dummy)
	{
#ifndef NDEBUG
		perror("malloc error in creating list: ");
#endif
		return NULL;
	}
	dummy->data = &list->tail;
	dummy->next = NULL;

	list->head = dummy;
	list->tail = dummy;
	
	return list;
}

void SLListDestroy(list_t *list)
{
	 iterator_t to_free = list->head;
	 iterator_t next_to_free = NULL;
	
	assert (NULL != list);

	while (to_free)
	{
		next_to_free = to_free->next;
		free(to_free);
		to_free = next_to_free;
	}
	free(list);
	list = NULL;
}

iterator_t SLListInsert(iterator_t where, void *data)
{
	iterator_t new_node = (iterator_t)malloc(sizeof(struct sllist_node));
	
	assert (NULL != where && NULL != data);

	if (NULL == new_node)
	{
#ifndef NDEBUG
		perror("malloc error in creating new node: ");
#endif
		return NULL;
	}
	new_node->next = where->next;
	where->next = new_node;

	new_node->data = where->data;
	where->data = data;
	
	/* update the tail */
	if (NULL == new_node->next)
	{
		*(iterator_t *)new_node->data = new_node;
	}
	return where;
}

iterator_t SLListRemove(iterator_t who)
{
	iterator_t to_free = who->next;
	
	assert(NULL != who);

	/* protecting my tail */
	if (NULL == who->next)
	{
		return NULL;
	}
	who->data = who->next->data;
	who->next = who->next->next;

	/* update iterator tail */
	if (NULL == who->next)
	{
		*(iterator_t *)who->data = who;
	}
	free(to_free);

	return who;
}

iterator_t SLListBegin(const list_t *list)
{
	assert (list);

	return list->head;
}

iterator_t SLListEnd(const list_t *list)
{
	assert (list);

	return list->tail;
}

int SLListIterIsEqual(const iterator_t iterator1, const iterator_t iterator2)
{
	return (iterator1 == iterator2);
}

iterator_t SLListNext(const iterator_t iterator)
{
	return iterator->next;
}

void *SLListGetData(const iterator_t iterator)
{
	return iterator->data;
}

void SLListSetData(iterator_t iterator, void *data)
{
	iterator->data = data;
}

iterator_t SLListFind(const iterator_t from, const iterator_t to, 
										match_func_t is_match, void *param)
{
	iterator_t to_match = from;
 
	while (!(SLListIterIsEqual(to_match, to)))
	{
		if (is_match(SLListGetData(to_match), param))
		{
			return to_match;
		}
		to_match = SLListNext(to_match);
	}
	return to;
}

size_t SLListCount(const list_t *list)
{
	size_t count = 0;
	iterator_t to_count = SLListBegin(list);

	assert (list);

	while (!SLListIterIsEqual(to_count, SLListEnd(list)))
	{
		to_count = SLListNext(to_count);
		count++;
	}
	return count;
}

int SLListForEach(iterator_t from, iterator_t to, action_func_t
													is_action, void *param)
{
	iterator_t to_operate_on = from;

	for (; !SLListIterIsEqual(to_operate_on, to);
		 						to_operate_on = SLListNext(to_operate_on))
	{
		if (is_action(SLListGetData(to_operate_on), param))
		{
			return FAILURE;
		}
	}
	return SUCCESS;
}

int SLListIsEmpty(const list_t *list)
{
	assert (list);

	return SLListIterIsEqual(SLListBegin(list), SLListEnd(list));
}

void SLListAppend(list_t *list1, list_t *list2)
{
	assert(list1 && list2);

	list1->tail->next = list2->head->next;
	list1->tail->data = list2->head->data;
	list2->tail->data = &list1->tail;
	list1->tail = list2->tail;

	free(list2->head);
	free(list2);
}



