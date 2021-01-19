/****************************************************************************
 * 						written by : orpaz houta							*
 *						review : Aviv Levanon								*
 * 						Last update : 21.4.20								*
 ***************************************************************************/

#include <stddef.h> /* size_t */
#include <malloc.h> /* malloc */
#include <assert.h>	/* assert */

#include "dllist.h"	/* dllist_t */
#include "sorted_list.h"


struct sorted_list
{
	is_before_func sort;
	dllist_t *container;
	void *param;
};

static sortl_iterator_t CreateSLIterator(const sorted_list_t *list);



sorted_list_t *SortedListCreate(is_before_func func, void *param)
{
	sorted_list_t *list = NULL;

	assert(func);

	list = (sorted_list_t *)malloc(sizeof(sorted_list_t));
	if (!list)
	{
#ifndef NDEBUG
		perror("SortedListCreate in creating list: ");
#endif
		return NULL;
	}

	list->container = DLListCreate();
	if (!list->container)
	{
		free(list);
		list = NULL;
		return NULL;
	}
	list->sort = func;
	list->param = param;

	return list;
}

void SortedListDestroy(sorted_list_t *list)
{
	DLListDestroy(list->container);
	list->container =NULL;

	free(list);
	list = NULL;
}

sortl_iterator_t SortedListInsert(sorted_list_t *list, void* data)
{
	sortl_iterator_t new;

	assert(list);

	new = CreateSLIterator((const sorted_list_t *)list);

	for (;!SortedListIsEqual(new, SortedListEnd(list)) &&
		list->sort(SortedListGetData(new), data, list->param);
		new = SortedListNext(new));

	new.sort_iter = DLListInsert(new.sort_iter, data);
	if (new.sort_iter == DLListEnd(list->container))
	{
		return SortedListEnd(list);
	}
	return new;
}

sortl_iterator_t SortedListRemove(sortl_iterator_t iterator)
{
	assert(iterator.sort_iter);

	iterator.sort_iter = (DLListRemove(iterator.sort_iter));

	return iterator;
}

size_t SortedListSize(const sorted_list_t *list)
{
	assert(list);

	return DLListSize(list->container);
}

int SortedListIsEmpty(const sorted_list_t *list)
{
	assert(list);

	return DLListIsEmpty(list->container);
}

void *SortedListGetData(sortl_iterator_t iterator)
{
	assert(iterator.sort_iter);

	return DLListGetData(iterator.sort_iter);
}

sortl_iterator_t SortedListBegin(const sorted_list_t *list)
{
	assert(list);

	return CreateSLIterator(list);
}

sortl_iterator_t SortedListEnd(const sorted_list_t *list)
{
	sortl_iterator_t end;

	assert(list);

	end = CreateSLIterator(list);
	end.sort_iter = DLListEnd(list->container);

	return end;
}

sortl_iterator_t SortedListNext(sortl_iterator_t iterator)
{
	assert(iterator.sort_iter);

	iterator.sort_iter = DLListNext(iterator.sort_iter);

	return iterator;
}

sortl_iterator_t SortedListPrev(sortl_iterator_t iterator)
{
	assert(iterator.sort_iter);

	iterator.sort_iter = DLListPrev(iterator.sort_iter);

	return iterator;
}

int SortedListIsEqual(sortl_iterator_t iterator1, sortl_iterator_t iterator2)
{
	assert(iterator1.sort_iter);
	assert(iterator2.sort_iter);

	return DLListIsSameIterator(iterator1.sort_iter, iterator2.sort_iter);
}

void *SortedListPopFront(sorted_list_t *list)
{
	assert(list);

	return DLListPopFront(list->container);
}

void *SortedListPopBack(sorted_list_t *list)
{
	assert(list);

	return DLListPopBack(list->container);
}

int SortedListForEach(sortl_iterator_t from, sortl_iterator_t to,
											operation_func operate, void *param)
{
	assert(operate);
	assert(from.sort_iter);
	assert(to.sort_iter);
	assert(from.list == to.list);

	return DLListForEach(from.sort_iter, to.sort_iter, operate, param);
}

sortl_iterator_t SortedListFind(sortl_iterator_t from, sortl_iterator_t to,
										sorted_list_t *list, void *data_to_find)
{
	sortl_iterator_t seek = from;

	assert(list);
	assert(from.sort_iter);
	assert(to.sort_iter);
	assert(from.list == to.list);

	for (;!SortedListIsEqual(seek, to) &&
		list->sort(SortedListGetData(seek), data_to_find, list->param);
		seek = SortedListNext(seek));

	if (!list->sort(data_to_find, SortedListGetData(seek), list->param))
	{
		return seek;
	}
	return to;
}

sortl_iterator_t SortedListFindIf(sortl_iterator_t from, sortl_iterator_t to,
											match_func_t is_match, void *param)
{
	sortl_iterator_t seek;

	assert(from.sort_iter);
	assert(to.sort_iter);
	assert(is_match);
	assert(from.list == to.list);

    seek.sort_iter = DLListFind(from.sort_iter, to.sort_iter, is_match, param);

	return seek;
}

void SortedListMerge(sorted_list_t *list1, sorted_list_t *list2)
{
	sortl_iterator_t where = SortedListBegin(list1);
	sortl_iterator_t from = SortedListBegin(list2);
	sortl_iterator_t to = from;

	assert(list1);
	assert(list2);
	assert(list1->sort == list2->sort);

	while (!SortedListIsEmpty(list2))
	{
		for (; !SortedListIsEqual(where, SortedListEnd(list1)) &&
			!list1->sort(SortedListGetData(from), SortedListGetData(where),
																list1->param);
			where = SortedListNext(where));

		if (SortedListIsEqual(where, SortedListEnd(list1)))
		{
			to = SortedListEnd(list2);
		}

		for (; !SortedListIsEqual(to, SortedListEnd(list2)) &&
			list1->sort(SortedListGetData(to), SortedListGetData(where),
																 list2->param);
			to = SortedListNext(to));

		DLListSplice(where.sort_iter, from.sort_iter, to.sort_iter);
		from = to;
	}
}

static sortl_iterator_t CreateSLIterator(const sorted_list_t *list)
{
	sortl_iterator_t new;
	new.sort_iter = DLListBegin(list->container);

#ifndef NDEBUG
	new.list = (sorted_list_t *)list;
#endif
	return new;
}
