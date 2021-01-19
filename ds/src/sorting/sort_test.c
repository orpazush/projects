/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review : Gilio & shachar						         *
 * 					Last update : 9.6.20									 *
 ****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ca_test_util.h"
#include "sort.h"

#define SIZE (100)
#define MAX_RANGE (1000000)
#define SEVEN_DIGITS (10000000)

void TestBubble();
void TestInsert();
void TestSelection();
void TestCounting();
void TestRadixSort();
void TestMerge();
void TestQSort();
void TestQuick();
void TestBinarySearch();

static int CmpQsort(const void * a, const void * b);

int main()
{
	TestInsert();
	TestBubble();
    TestSelection();
    TestCounting();
    TestRadixSort();
	TestMerge();
    TestQSort();
	TestQuick();
	TestBinarySearch();

    TEST_SUMMARY();

    return 0;
}

void TestInsert()
{
    size_t i = 0;
    int array[SIZE];
    time_t seed = time(0);
    clock_t befor = 0, after = 0;
    srand(seed);

    for (i = 0 ; i < SIZE ; i++)
    {
        array[i] = rand();
    }

    befor = clock();
    InsertSort(array, SIZE);
    after = clock();
    for (i = 0; i < SIZE - 1; i++)
    {
        BOOL_TEST (array[i] <= array[i + 1]);
    }

    printf("InsertSort time: %f\n", (double)(after - befor)/CLOCKS_PER_SEC);
}

void TestBubble()
{
    size_t i = 0;
    int array[SIZE];
    time_t seed = time(0);
    clock_t befor = 0, after = 0;
    srand(seed);

    for (i = 0 ; i < SIZE ; i++)
    {
        array[i] = rand();
    }
    befor = clock();
    BubbleSort(array, SIZE);
    after = clock();

    for (i = 0; i < SIZE - 1; i++)
    {
        BOOL_TEST (array[i] <= array[i + 1]);
    }
    printf("BubbleSort time: %f\n", (double)(after - befor)/CLOCKS_PER_SEC);
}

void TestSelection()
{
    size_t i = 0;
    int array[SIZE];
    time_t seed = time(0);
    clock_t befor = 0, after = 0;
    srand(seed);

    for (i = 0 ; i < SIZE ; i++)
    {
        array[i] = rand();
    }
    befor = clock();
    SelectionSort(array, SIZE);
    after = clock();

    for (i = 0; i < SIZE - 1; i++)
    {
        BOOL_TEST (array[i] <= array[i + 1]);
    }
    printf("SelectionSort time: %f\n", (double)(after - befor)/CLOCKS_PER_SEC);
}

void TestCounting()
{
    size_t i = 0;
    int array[SIZE];
    time_t seed = time(0);
    clock_t befor = 0, after = 0;
    srand(seed);

    for (i = 0 ; i < SIZE ; i++)
    {
        array[i] = (rand() % MAX_RANGE) + 1;
    }
    befor = clock();
    CountingSort(array, SIZE, MAX_RANGE);
    after = clock();

    for (i = 0; i < SIZE - 1; i++)
    {
        BOOL_TEST (array[i] <= array[i + 1]);
    }
    printf("CountingSort time: %f\n", (double)(after - befor)/CLOCKS_PER_SEC);
}

void TestRadixSort()
{
    size_t i = 0;
    int array[SIZE];
    time_t seed = time(0);
    clock_t befor = 0, after = 0;
    srand(seed);

    for (i = 0 ; i < SIZE ; i++)
    {
        array[i] = (rand() % SEVEN_DIGITS);
    }
    befor = clock();
    RadixSort(array, SIZE, 7);
    after = clock();

    for (i = 0; i < SIZE - 1; i++)
    {
        BOOL_TEST (array[i] <= array[i + 1]);
    }
    printf("RadixSort time: %f\n", (double)(after - befor)/CLOCKS_PER_SEC);
}

void TestMerge()
{
	size_t i = 0;
	int array[SIZE];
	int status = 0;
	time_t seed = time(0);
	clock_t befor = 0, after = 0;
	srand(seed);

	for (i = 0 ; i < SIZE ; i++)
	{
		array[i] = rand();
	}
	befor = clock();
	status = MergeSort(array, SIZE);
	after = clock();

	if (!status)
	{
		for (i = 0; i < SIZE - 1; i++)
		{
			BOOL_TEST (array[i] <= array[i + 1]);
		}
	}

	printf("MergeSort time: %f\n", (double)(after - befor)/CLOCKS_PER_SEC);
}

void TestQuick()
{
	size_t i = 0;
	int array[SIZE];
	int status = 0;
	clock_t befor = 0, after = 0;

	for (i = 0 ; i < SIZE ; i++)
	{
		array[i] = (rand() % MAX_RANGE);
	}

	befor = clock();
	QuickSort(array, SIZE, sizeof(int), CmpQsort);
	after = clock();

	if (!status)
	{
		for (i = 0; i < (SIZE - 1); i++)
		{
			BOOL_TEST (array[i] <= array[i + 1]);
		}
	}

	printf("QuickSort time: %f\n", (double)(after - befor)/CLOCKS_PER_SEC);
}

void TestQSort()
{
    size_t i = 0;
    int array[SIZE];
    time_t seed = time(0);
    clock_t befor = 0, after = 0;
    srand(seed);

    for (i = 0 ; i < SIZE ; i++)
    {
        array[i] = rand();
    }
    befor = clock();
    qsort(array, SIZE, sizeof(int), CmpQsort);
    after = clock();

    for (i = 0; i < SIZE - 1; i++)
    {
        BOOL_TEST (array[i] <= array[i + 1]);
    }
    printf("qsort time: %f\n", (double)(after - befor)/CLOCKS_PER_SEC);
}

void TestBinarySearch()
{
	size_t i = 0;
	int j = 0;
	int array[SIZE];
	int not_in_array = (SIZE + 11);

	for (i = 0 ; i < SIZE ; i++)
	{
		array[i] = (i + 10);
	}

	for (i = 0 ; i < SIZE ; j = (rand() % SIZE), ++i)
	{
		INT_TEST(j, IterBinarySearch(array, SIZE, array[j]));
	}
	INT_TEST(-1, IterBinarySearch(array, SIZE, not_in_array));

	for (i = 0 ; i < SIZE ; j = (rand() % SIZE), ++i)
	{
		INT_TEST(j, RecurBinarySearch(array, SIZE, array[j]));
	}
	INT_TEST(-1, RecurBinarySearch(array, SIZE, not_in_array));
}

static int CmpQsort(const void *a, const void *b)
{
   return ( *(int *)a - *(int *)b );
}
