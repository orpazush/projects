/****************************************************************************
 *					written by : Orpaz Houta								*
 * 					review : Tali Rephael									*
 * 					Last update : 19.4.20									*
 ***************************************************************************/
#include <stdio.h>	/* printf */

#include "dllist.h"

#define FAIL (1) 		/* status */
#define SUCCESS (0)		/* status */

int SanityTest();

int is_int_match(const void *data, const void *param);
int DivisibleBy(void *data, void *param);

int main()
{
	printf("****************START TESTING***********************\n");
	SanityTest() ? printf("test failed\n") : printf("all tests succeeded!:)\n");
	printf("*****************END TESTING************************\n");

	return 0;
}

int SanityTest()
{
	dllist_t *list = DLListCreate();
	dllist_t *list2 = DLListCreate();
	int status = SUCCESS;
	size_t size = 0;
	iterator_t insert = NULL;
	int data[100];
	int i = 0, j = 0, param_int = 122, foreach = 2;
	iterator_t find = NULL;
	int *param = &param_int;

	for (i = 0, j = 2; i < 40; i++, j += 10)
	{
		data[i] = j;
	}

	if (!list)
	{
		status = FAIL;
		printf("DLListCreate FAIL\n");
	}

	if (!DLListIsEmpty(list))
	{
		status = FAIL;
		printf("DLListIsEmpty FAIL when empty\n");
	}

	if (DLListSize(list))
	{
		status = FAIL;
		printf("DLListSize FAIL when empty\n");
	}
	insert = DLListInsert(DLListEnd(list), &data[0]);
	if (DLListBegin(list) != insert)
	{
		status = FAIL;
		printf("DLListInsert FAIL from begin\n");
	}
	DLListRemove(DLListBegin(list));

	if (!DLListIsEmpty(list))
	{
		status = FAIL;
		printf("DLListRemove FAIL\n");
	}

	for (i = 0; i < 10; i++)
	{
		DLListPushFront(list, &data[i]);
	}

	size = DLListSize(list);
	if (10 != size)
	{
		status = FAIL;
		printf("DLListPushFront FAIL\n");
	}

	for (i = 0; i < 20; i++)
	{
		DLListPushBack(list2, &data[i]);
	}

	if (20 != DLListSize(list2))
	{
		status = FAIL;
		printf("DLListPushBack FAIL\n");
	}

	find = DLListFind(DLListBegin(list2), DLListEnd(list2), is_int_match, param);
	if (122 != *(int *)DLListGetData(find))
	{
		status = FAIL;
		printf("DLListFind FAIL when there match\n");
	}

	param = &j;
	find = DLListFind(DLListBegin(list2), DLListEnd(list2), is_int_match, param);
	if (DLListEnd(list2) != find)
	{
		status = FAIL;
		printf("DLListFind when no match FAIL\n");
	}
	param = &foreach;
	status = DLListForEach(DLListBegin(list2), DLListEnd(list2),
	 					   DivisibleBy, param);
	{
		if (0 != status)
		{
			status = FAIL;
			printf("DLListForEach FAIL\n");
		}
	}

	DLListSplice(DLListBegin(list), DLListBegin(list2), DLListEnd(list2));
	if (30 != DLListSize(list))
	{
		status = FAIL;
		printf("DLListSplice FAIL\n");
	}

	while (!DLListIsEmpty(list2))
	{
		DLListPopFront(list2);
	}

	if (!DLListIsEmpty(list2))
	{
		status = FAIL;
		printf("DLListPopFront FAIL\n");
	}

	while (!DLListIsEmpty(list))
	{
		DLListPopFront(list);
	}

	if (!DLListIsEmpty(list))
	{
		status = FAIL;
		printf("DLListPopBack FAIL\n");
	}

	DLListDestroy(list);
	DLListDestroy(list2);

	return status;
}

int is_int_match(const void *data, const void *param)
{
	return (*(int *)data == *(int *)param);
}

int DivisibleBy(void *data, void *param)
{
	if (NULL == data || NULL == param)
	{
		return FAIL;
	}
	*(int *)data /= *(int *)param;

	return SUCCESS;
}
