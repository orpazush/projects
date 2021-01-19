/****************************************************************************
 * 						written by : orpaz houta							*
 *						review : Aviv Levanon								*
 * 						Last update : 21.4.20								*
 ***************************************************************************/
#include <string.h>

#include "ca_test_util.h" /* ©️ chanan & aviv */
#include "dllist.h"	/* dllist_t */
#include "sorted_list.h"

#define MAX_SHORT (0x7fff)

void TestSortedListInsert();
void TestSortedListRemove();
void TestSortedListFind();
void TestSortedListForEach();
void TestSortedListFindIf();
void TestSortedListMerge();

/* helper printing function */
void PrintListINT(sorted_list_t *list);
void PrintListCHAR(sorted_list_t *list);

/* functions for testing */
int IsBeforChar(char *data1, char *data2, void *param);
int IsBeforInt(int *data1, int *data2, void *param);
int Multy(int *number, int *multy);
int IsInString(char *check, char *src);
int IsBigger(const int *data, const int *param);

int main()
{
    TestSortedListInsert();
    TestSortedListRemove();
	TestSortedListForEach();
	TestSortedListFind();
	TestSortedListFindIf();
	TestSortedListMerge();

    TEST_SUMMARY();
    return 0;
}

/* used on this test SortedListCreate, SortedListSize, SortedListIsEmpty, 
 * IsBeforInt, SortedListGetData, SortedListDestroy */
void TestSortedListInsert()
{
    sorted_list_t *test_list = SortedListCreate((is_before_func)&IsBeforInt, NULL);
    int test1 = 1, test2 = 2, test3 = 3;
    int test4 = 4, test5 = 5, test6 = 6;
	sortl_iterator_t test_iter = SortedListBegin(test_list);

    INT_TEST(0, SortedListSize(test_list));
	INT_TEST(1, SortedListIsEmpty(test_list));

    SortedListInsert(test_list, &test6);
    INT_TEST(1, SortedListSize(test_list));

    SortedListInsert(test_list, &test3);
    INT_TEST(2, SortedListSize(test_list));

    test_iter = SortedListInsert(test_list, &test4);
    INT_TEST(3, SortedListSize(test_list));

    INT_TEST(test4, *(int *)SortedListGetData(test_iter));

    SortedListInsert(test_list, &test2);
    INT_TEST(4, SortedListSize(test_list));

    SortedListInsert(test_list, &test5);
    INT_TEST(5, SortedListSize(test_list));

    SortedListInsert(test_list, &test1);
    INT_TEST(6, SortedListSize(test_list));

    test_iter = SortedListPrev(SortedListEnd(test_list));
    INT_TEST(test6, *(int *)SortedListGetData(test_iter));

    SortedListDestroy(test_list);
}

/* SortedListRemove, SortedListPopFront, SortedListPopBack, SortedListBegin,
 *SortedListEnd */
void TestSortedListRemove()
{
    sorted_list_t *test_list = SortedListCreate((is_before_func)&IsBeforInt, NULL);
    int test1 = 1, test2 = 2, test3 = 3;
    int test4 = 4, test5 = 5, test6 = 6;
	sortl_iterator_t test_iter = SortedListBegin(test_list);

    INT_TEST(0, SortedListSize(test_list));
	INT_TEST(1, SortedListIsEmpty(test_list));

    test_iter = SortedListInsert(test_list, &test6);
    INT_TEST(1, SortedListSize(test_list));

	SortedListRemove(test_iter);
    INT_TEST(0, SortedListSize(test_list));

	test_iter = SortedListInsert(test_list, &test1);
	SortedListInsert(test_list, &test2);
	SortedListInsert(test_list, &test5);
	SortedListInsert(test_list, &test3);
	SortedListInsert(test_list, &test4);
	INT_TEST(5, SortedListSize(test_list));

	SortedListRemove(test_iter);
	INT_TEST(4, SortedListSize(test_list));

	INT_TEST(2, *(int *)SortedListPopFront(test_list));
	INT_TEST(3, *(int *)SortedListPopFront(test_list));
	INT_TEST(2, SortedListSize(test_list));

	INT_TEST(5, *(int *)SortedListPopBack(test_list));
	INT_TEST(4, *(int *)SortedListPopBack(test_list));

	INT_TEST(1, SortedListIsEmpty(test_list));

    SortedListDestroy(test_list);
}

void TestSortedListForEach()
{
    size_t i = 0;
    sorted_list_t *test_list = SortedListCreate((is_before_func)&IsBeforInt, NULL);
	sortl_iterator_t end_iter = SortedListEnd(test_list);
    int begin_befor;
	int end_befor;
	int array[] = {2,3,4,1,6,5,7,10,8,9};
    int multy = 2, bad_multy = 0xfff;
    int func_res = -1;
	size_t size = -1;
	
    for (i = 0; i < (sizeof(array)/sizeof(array[0])); i++)
    {
        SortedListInsert(test_list, &array[i]);
    }

	begin_befor = *(int *)SortedListGetData(SortedListBegin(test_list));
	end_befor = *(int *)SortedListGetData(SortedListPrev(SortedListEnd(test_list)));
	
	size = (sizeof(array)/sizeof(array[0]));
	INT_TEST(1, (SortedListSize(test_list) == size));

	func_res = SortedListForEach(SortedListBegin(test_list), 
					SortedListEnd(test_list),(operation_func)&Multy, &multy);
	INT_TEST(0, func_res);

	INT_TEST(0, begin_befor == *(int *)SortedListGetData
												(SortedListBegin(test_list)));

	INT_TEST(1, begin_befor * multy == *(int *)SortedListGetData
												(SortedListBegin(test_list)));

	INT_TEST(0, end_befor == *(int *)SortedListGetData(SortedListPrev(end_iter)));

	begin_befor = *(int *)SortedListGetData(SortedListBegin(test_list));
	end_befor = *(int *)SortedListGetData(SortedListPrev(end_iter));

	func_res = SortedListForEach(SortedListBegin(test_list), 
					SortedListEnd(test_list),(operation_func)&Multy, &bad_multy);
	INT_TEST(1, func_res);

	INT_TEST(0, begin_befor == *(int *)SortedListGetData
												(SortedListBegin(test_list)));

	INT_TEST(1, end_befor == *(int *)SortedListGetData(SortedListPrev(end_iter)));

    SortedListDestroy(test_list);
}

void TestSortedListFind()
{
    size_t i = 0;
    sorted_list_t *test_list = SortedListCreate((is_before_func)&IsBeforChar, NULL);
	sortl_iterator_t end_iter = SortedListEnd(test_list);
	sortl_iterator_t test_iter;
	char array[] = "mazal sheyesh otach...";
	char to_find = 'z';
	char not_found = 'b';
	
    for (i = 0; array[i]; i++)
    {
        SortedListInsert(test_list, &array[i]);
    }

	test_iter = SortedListFind(SortedListBegin(test_list), 
						SortedListPrev(end_iter), test_list, &array[1]);
	INT_TEST(0, SortedListIsEqual(test_iter, SortedListPrev(end_iter)));

	test_iter = SortedListFind(SortedListBegin(test_list), 
							SortedListPrev(end_iter), test_list, &array[1]);
	INT_TEST(0, SortedListIsEqual(test_iter, end_iter));

	test_iter = SortedListFind(SortedListBegin(test_list), 
							SortedListPrev(end_iter), test_list, &array[1]);
	INT_TEST(1, (*(char *)SortedListGetData(test_iter) == array[1]));

	test_iter = SortedListFind(SortedListBegin(test_list), 
							SortedListPrev(end_iter), test_list, &array[5]);
	INT_TEST(1, (*(char *)SortedListGetData(test_iter) == array[5]));

	test_iter = SortedListFind(SortedListBegin(test_list), end_iter, 
														test_list, &to_find);
	INT_TEST(1, (*(char *)SortedListGetData(test_iter) == 'z'));

	INT_TEST(1, (*(char *)SortedListPopBack(test_list) == 'z'));
	SortedListPopBack(test_list);
	SortedListPopBack(test_list);

	test_iter = SortedListFind(SortedListBegin(test_list), end_iter, 
														test_list, &not_found);
	INT_TEST(1, SortedListIsEqual(test_iter, end_iter));

	SortedListDestroy(test_list);	
}

void TestSortedListFindIf()
{
    size_t i = 0;
    sorted_list_t *test_list = SortedListCreate((is_before_func)&IsBeforInt, NULL);
	sortl_iterator_t end_iter = SortedListEnd(test_list);
	sortl_iterator_t test_iter;
	int array[20] = {1,555,88,9999,7,32,-58,87,-1};
	int param = 100;
	int bad_param = 0xfffff;
	
    for (i = 0; array[i]; i++)
    {
        SortedListInsert(test_list, &array[i]);
    }

	test_iter = SortedListFindIf(SortedListBegin(test_list), end_iter,
										 (match_func_t)&IsBigger, &param);
	INT_TEST(1, SortedListIsEqual(test_iter, end_iter));

	test_iter = SortedListFindIf(SortedListBegin(test_list), end_iter,
										 (match_func_t)&IsBigger, &array[2]);
	INT_TEST(1, (*(int *)SortedListGetData(test_iter) == array[2]));

	test_iter = SortedListFindIf(SortedListBegin(test_list), end_iter,
										 (match_func_t)&IsBigger, &array[5]);
	INT_TEST(1, (*(int *)SortedListGetData(test_iter) == array[5]));

	SortedListInsert(test_list, &param);
 
	test_iter = SortedListFindIf(SortedListBegin(test_list), end_iter,
										 (match_func_t)&IsBigger, &param);
	INT_TEST(0, SortedListIsEqual(test_iter, end_iter));

	SortedListPopBack(test_list);
	SortedListPopBack(test_list);
	SortedListPopBack(test_list);
	SortedListPopBack(test_list);

	test_iter = SortedListFindIf(SortedListBegin(test_list), end_iter,
										 (match_func_t)&IsBigger, &array[2]);
	INT_TEST(1, SortedListIsEqual(test_iter, end_iter));

	test_iter = SortedListFindIf(SortedListBegin(test_list), end_iter,
										 (match_func_t)&IsBigger, &bad_param);
	INT_TEST(1, SortedListIsEqual(test_iter, end_iter));

	SortedListInsert(test_list, &bad_param);
 
	test_iter = SortedListFindIf(SortedListBegin(test_list), end_iter,
										 (match_func_t)&IsBigger, &bad_param);
	INT_TEST(1, SortedListIsEqual(test_iter, end_iter));

	SortedListDestroy(test_list);	
}

void TestSortedListMerge()
{
    size_t i = 0;
    sorted_list_t *test_list = SortedListCreate((is_before_func)&IsBeforChar, NULL);
    sorted_list_t *test_list2 = SortedListCreate((is_before_func)&IsBeforChar, NULL);
	char array[] = "qwertyuiopaviv";
	char array2[] = "asdfghjklzxcvbnmorpaz";
	
    for (i = 0; array[i]; i++)
    {
        SortedListInsert(test_list, &array[i]);
    }

    for (i = 0; array2[i]; i++)
    {
        SortedListInsert(test_list2, &array2[i]);
    }

    INT_TEST(1, SortedListSize(test_list) == strlen(array));

    INT_TEST(1, SortedListSize(test_list2) == strlen(array2));

	SortedListMerge(test_list, test_list2);

    INT_TEST(1, SortedListSize(test_list) == (strlen(array) + strlen(array2)));

	SortedListDestroy(test_list);	
	SortedListDestroy(test_list2);
}

void PrintListINT(sorted_list_t *list)
{
    sortl_iterator_t print = SortedListBegin(list);
    while (!SortedListIsEqual(print, SortedListEnd(list)))
    {
        printf("%d ", *(int *)SortedListGetData(print));
        print = SortedListNext(print);
    }
    printf("\n");
}

void PrintListCHAR(sorted_list_t *list)
{
    sortl_iterator_t print = SortedListBegin(list);
    while (!SortedListIsEqual(print, SortedListEnd(list)))
    {
        printf("%c", *(char *)SortedListGetData(print));
        print = SortedListNext(print);
    }
    printf("\n");
}

int IsBeforInt(int *data1, int *data2, void *param)
{
	return (*data1 < *data2 && data1 != param);
}

int IsBeforChar(char *data1, char *data2, void *param)
{
	return (*data1 < *data2 && data1 != param);
}

int Multy(int *number, int *multy)
{
	if (MAX_SHORT < (*number * *multy))
	{
		return 1;
	}
	*number *= *multy;

	return 0;
}

int IsBigger(const int *data, const int *param)
{
	if (MAX_SHORT < *param)
	{
		return -1;
	}
	if (MAX_SHORT < *data)
	{
		return -2;
	}
	return (*data == *param);
}












