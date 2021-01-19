/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review : Omer Hefetz									 *
 * 					Last update : 4.5.20									 *
 ****************************************************************************/
#include <assert.h>	/* assert */
#include "fsa.h"
#include "ca_test_util.h" 	/* ©️ chanan & aviv */


void TestInit();


int main()
{
	TestInit(); 

    TEST_SUMMARY();

    return 0;
}


void TestInit()
{
	fsa_t *test_segment = NULL;
	fsa_t *TestAllocator = NULL;
	size_t test_capacity = 0;
	size_t count_free = 0;
	int *alloc_int = NULL;
	float *alloc_float = NULL;
	size_t *alloc_array[10];
	int i = 0;

	test_capacity = FSASuggestSize(10, 8);
	INT_TEST(168, test_capacity);

	test_capacity = FSASuggestSize(10, 5);
	INT_TEST(168, test_capacity);

	test_capacity = FSASuggestSize(10, 20);
	INT_TEST(328, test_capacity);

	test_segment = (fsa_t *)malloc(test_capacity);

	TestAllocator = FSAInit(test_segment, test_capacity, 20);

	count_free = FSACountFree(TestAllocator);
	INT_TEST(10, count_free);

	alloc_int = (int *)FSAAlloc(TestAllocator);
	*alloc_int = 987;
	INT_TEST(9, FSACountFree(TestAllocator));

	alloc_float = (float *)FSAAlloc(TestAllocator);
	*alloc_float = -855564;
	INT_TEST(8, FSACountFree(TestAllocator));

	FSAFree(alloc_int);
	INT_TEST(9, FSACountFree(TestAllocator));

	FSAFree(alloc_float);
	INT_TEST(10, FSACountFree(TestAllocator));

	for (i = 0; i < 10; i++)
	{
		alloc_array[i] = FSAAlloc(TestAllocator);
	}
	INT_TEST(0, FSACountFree(TestAllocator));

	for (i = 0; i < 10; i++)
	{
		FSAFree(alloc_array[i]);
	}
	INT_TEST(10, FSACountFree(TestAllocator));
	

	free(test_segment);
	test_segment = NULL;
}

