/****************************************************************************
 *                   written by :  orpaz houta								*
 *                   review : chanan komar									*
 *                   Last update : 12.4.20									*
 ***************************************************************************/

#include <stdio.h> /* printf */

#include "sllist.h"

int Matchingchars(const void *data, void *param);
int DeleteSpecificChar(void *data, void *param);
void PrintListChar(const list_t *list);

int main()
{
	iterator_t i = NULL, find = NULL;
	list_t *new_list = NULL;
	list_t *list2 = NULL;
	char a = 'a', b = 'v', c = 'l', d = 'r', e = 'n', f= 'u', g = '.';
	char *p_find = &b;
	char *p_foreach = &g;
	int j = 0;

	new_list = SLListCreate();
	printf("is empty when create? : %d\n", SLListIsEmpty(new_list));
	/* trying to set when empty */
	SLListSetData(SLListBegin(new_list), &g);
	/*trying to remove when empty*/
	SLListRemove(SLListBegin(new_list));
	printf("count when empty: %ld\n", SLListCount(new_list));
	/* inserting the list elements of type char */
	SLListInsert(SLListBegin(new_list), &b);
	SLListInsert(SLListBegin(new_list), &a);
	SLListInsert(SLListEnd(new_list), &a);
	SLListInsert(SLListEnd(new_list), &c);
	SLListInsert(SLListEnd(new_list), &a);
	SLListInsert(SLListEnd(new_list), &b);
	SLListInsert(SLListEnd(new_list), &a);
	SLListInsert(SLListEnd(new_list), &d);
	SLListInsert(SLListEnd(new_list), &e);
	SLListInsert(SLListEnd(new_list), &f);
	SLListInsert(SLListEnd(new_list), &g);
	SLListInsert(SLListEnd(new_list), &g);
	SLListInsert(SLListEnd(new_list), &g);
	
	printf("is empty after insert? : %d\n", SLListIsEmpty(new_list));

	printf("list after insert from both end and begin: ");	
	PrintListChar(new_list);

	printf("isequal (first member and second): %d\n", SLListIterIsEqual
				(SLListBegin(new_list), SLListNext(SLListBegin(new_list))));

	printf("count after insert: %ld\n", SLListCount(new_list));

	find = SLListFind(SLListBegin(new_list), SLListEnd(new_list), 
													Matchingchars, p_find);
	printf("find v: %c\n", *(char *)SLListGetData(find));
	
	printf("is foreach succeed: %d\n", SLListForEach(SLListBegin(new_list), 
						SLListEnd(new_list), DeleteSpecificChar, p_foreach));

	printf("list after turning every '.' to 'z' with for each: ");

	find = SLListFind(SLListBegin(new_list), SLListEnd(new_list), 
												Matchingchars, p_foreach);
	printf("is '.' found after foreach: %c\n", *(char *)SLListGetData(find));

	SLListRemove(SLListBegin(new_list));
	printf("list after remove first element: ");	
	PrintListChar(new_list);

	SLListSetData(SLListBegin(new_list), &c);
	printf("list after setting first element to 'l': ");	
	PrintListChar(new_list);
	/* remove all the elements in the list*/
	
	list2 = SLListCreate();

	i = SLListBegin(list2);
	for (j = 0; j < 7; j++)
	{
		SLListInsert(i, &b);
		i = SLListNext(i);		
	}

	printf("list2: ");	
	PrintListChar(list2);
	
	SLListAppend(new_list, list2);

	printf("list1 after append: ");
	PrintListChar(new_list);

	i = SLListBegin(new_list); 
	while (i != NULL)
	{
		i = SLListRemove(i);
	}
	printf("count after remove all: %ld\n", SLListCount(new_list));

	printf("is empty after remove all elements? %d\n", SLListIsEmpty(new_list));

	SLListDestroy(new_list);

	return 0;
}

int Matchingchars(const void *data, void *param)
{
	return !(*(char *)data == *(char *)param);
}

int DeleteSpecificChar(void *data, void *param)
{
	if(data == NULL || param == NULL)
	{
		return FAILURE;
	}
	if(*(char *)data == *(char *)param)
  	{  
    	*(char *)data = 'z';
	}
  	return SUCCESS;
}

void PrintListChar(const list_t *list)
{
	iterator_t i = SLListBegin(list);

	while (SLListNext(i) != SLListEnd(list))
	{
		printf("%c",*(char *)SLListGetData(i));
		i = SLListNext(i);
	}
	printf("\n");
}
