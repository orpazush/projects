/****************************************************************************
* 					written by : orpaz houta								*
* 					review : Izik Avinoam	  								*
*					Last update : 12.7.20 									*
****************************************************************************/
#include <stdio.h>      /* printf */
#include <malloc.h>     /* malloc */
#include <assert.h>     /* assert */
#include <stdlib.h>     /* qsort */
#include <string.h>     /* strlen */
#include <unistd.h>     /* sleep */

#include <pthread.h>    /* pthread_t */

#include "ca_test_util.h" 	/* ©️ chanan & aviv */


/*---------------------------Macros & Typedef---------------------------------*/
#ifndef NDEBUG
#define PRINT_ERROR(str) fprintf(stderr, "ERROR( %s : %d ) -- %s\n",\
__FILE__, __LINE__ , str)
#else
#define PRINT_ERROR(str)
#endif

#define NUM_OF_THREADS        	(32)	/* can be only a power of two */
#define NUM_OF_DICTS          	(5)
#define NUMBER_OF_WORDS       	(102305)
#define SIZE_BIG_DATA    	  	(NUMBER_OF_WORDS * NUM_OF_DICTS)
#define REMINDER 		   	  	(SIZE_BIG_DATA % NUM_OF_THREADS)
#define CONTINUE 				(1)
#define STOP 					(0)

#define THREAD_RANGE(threads)	(SIZE_BIG_DATA / threads)
#define UNUSED(x)           	((void)x)
#define ARRAY_SIZE(x, y) 		((x == y)\
					 			 ? THREAD_RANGE(NUM_OF_THREADS) + (REMINDER)\
					 			 : THREAD_RANGE(NUM_OF_THREADS))

typedef void *(*thread_func_t)(void *param);
/*----------------------------------------------------------------------------*/

/*----------------------------Main Static Functions---------------------------*/
static char *_CreateDictionary();
static int _InitBigData(char *dictionary);
static void _ShuffleData(void);
static void _SortByThreads(thread_func_t sort);
static void _MergeSortByThreads(void);
static void _Test();
/*------------------------------Sort Functions--------------------------------*/
static void *_QuickSort(void *param);
static void *_SelectionSort(void *param);
static void *_InsertSort(void *param);
static void *_BubbleSort(void *param);
static void *_MergeSort(void *param);
/*------------------------------Help Functions--------------------------------*/
static int _CmpWords(const void *a, const void *b);
static int _RandCmp(const void *a, const void *b);
static void *_Merge(char **to_merge, size_t middle, size_t array_size);
static void _Swap(char **a, char **b);
/*----------------------------------------------------------------------------*/

/*------------------------------Global VAriable-------------------------------*/
static char **sg_big_data = NULL;
static size_t sg_num_of_threads = NUM_OF_THREADS;
static size_t sg_merge_range = THREAD_RANGE(NUM_OF_THREADS);
/*----------------------------------------------------------------------------*/


int main()
{
    char *dictionary = NULL;
	clock_t befor = 0, after = 0;

	printf("number of threads: %d\n", NUM_OF_THREADS);

    dictionary = _CreateDictionary();
    if (!dictionary)
    {
        PRINT_ERROR("_CreateDictionary");

        return (1);
    }

	if (_InitBigData(dictionary))
	{
		return (1);
	}

/*--------------------------------_InsertSort---------------------------------*/
	_ShuffleData();

	befor = clock();

	_SortByThreads(_InsertSort);
	_MergeSortByThreads();

	after = clock();

	printf("_InsertSort time: %f\n", (double)(after - befor)/CLOCKS_PER_SEC);

/*-------------------------------_SelectionSort-------------------------------*/
	_ShuffleData();

	befor = clock();

	_SortByThreads(_SelectionSort);
	_MergeSortByThreads();

	after = clock();

	printf("_SelectionSort time: %f\n", (double)(after - befor)/CLOCKS_PER_SEC);

/*---------------------------------_QuickSort---------------------------------*/
	_ShuffleData();

	befor = clock();

	_SortByThreads(_QuickSort);
	_MergeSortByThreads();

	after = clock();

	printf("_QuickSort time: %f\n", (double)(after - befor)/CLOCKS_PER_SEC);

/*-------------------------------_BubbleSort---------------------------------*/
	_ShuffleData();

	befor = clock();

	_SortByThreads(_BubbleSort);
	_MergeSortByThreads();

	after = clock();

	printf("_BubbleSort time: %f\n", (double)(after - befor)/CLOCKS_PER_SEC);

/*----------------------------------------------------------------------------*/
	_Test();

	printf("\n");
	TEST_SUMMARY();

	free(dictionary);
	dictionary = NULL;

    free(sg_big_data);
    sg_big_data = NULL;

    return (0);
}

/*-----------------------------Static Definitions----------------------------*/
static char *_CreateDictionary(void)
{
    char *dictionary = NULL;
    FILE *words = NULL;
    char *to_return = NULL;
	size_t size_of_dict = 0;

    words = fopen("/usr/share/dict/american-english", "r");
    if (!words)
    {
        PRINT_ERROR("fopen");

        return (NULL);
    }

    /* to find the size of the dictionary to know how much memory to allocate */
    fseek(words, 0, SEEK_END);
    size_of_dict = ftell(words);
    rewind(words);

    dictionary = (char *)malloc(size_of_dict * sizeof(char));
    if (!dictionary)
    {
        PRINT_ERROR("malloc when create dictionary");

        return (NULL);
    }
    to_return = dictionary;

    while (EOF != fscanf(words, "%s", dictionary))
    {
        dictionary += (strlen(dictionary) + 1);
    }

    fclose(words);

    return (to_return);
}

static int _InitBigData(char *dictionary)
{
    size_t i = 0;
    size_t j = 0;
    char *new_word = dictionary;

    sg_big_data = malloc(sizeof(char *) * NUMBER_OF_WORDS * NUM_OF_DICTS);
    if (!sg_big_data)
    {
        PRINT_ERROR("malloc fail on sg_big_data");

        return (1);
    }

    for (i = 0; i < NUM_OF_DICTS; ++i)
    {
        for (j = 0; j < NUMBER_OF_WORDS; ++j)
        {
			sg_big_data[(i * NUMBER_OF_WORDS) + j] = new_word;
            new_word = new_word + (strlen(new_word) + 1);
        }

        new_word = dictionary;
    }

    printf("sg_big_data size: %ld\n", ((i - 1) * NUMBER_OF_WORDS) + j);

    return (0);
}

static void _ShuffleData(void)
{
	size_t i = 0;

	for (i = 0; i < 10; ++i)
	{
		qsort(sg_big_data, SIZE_BIG_DATA, sizeof(char *), _RandCmp);
	}
}

static void _SortByThreads(thread_func_t sort)
{
	size_t i = 0;
	pthread_t sorter_id[NUM_OF_THREADS] = {0};

	for(i = 0; i < NUM_OF_THREADS; ++i)
	{
		while (pthread_create(sorter_id + i, NULL, sort, (void *)i));
	}

	for (i = 0; i < NUM_OF_THREADS; ++i)
	{
		pthread_join(sorter_id[i], NULL);
	}
}

static void _MergeSortByThreads(void)
{
	size_t i = 0;
	pthread_t sorter_id[NUM_OF_THREADS / 2] = {0};
	sg_num_of_threads = NUM_OF_THREADS;
	sg_merge_range = THREAD_RANGE(NUM_OF_THREADS);

	while (sg_num_of_threads /= 2)
	{
		sg_merge_range *= 2;

		for(i = 0; i < sg_num_of_threads; ++i)
		{
			while (pthread_create(sorter_id + i, NULL, _MergeSort,
				   sg_big_data + (i * sg_merge_range)));
		}

		for (i = 0; i < sg_num_of_threads; ++i)
		{
			pthread_join(sorter_id[i], NULL);
		}
	}
}

static void _Test()
{
	size_t i = 0;

	for (i = 0; i < SIZE_BIG_DATA - 1; i++)
	{
		if (0 < strcmp(sg_big_data[i], sg_big_data[i + 1]))
		{
			printf("%s\n", sg_big_data[i]);
			printf("%s\n", sg_big_data[i + 1]);
			printf("%ld\n", i);
		}
		INT_TEST(1, (0 >= strcmp(sg_big_data[i], sg_big_data[i + 1])));
	}
}
/*----------------------------------------------------------------------------*/

static void *_QuickSort(void *param)
{
	char **base = sg_big_data + ((size_t)param * THREAD_RANGE(NUM_OF_THREADS));
	/* the last thread should handle the reminder */
	size_t size = ARRAY_SIZE((size_t)param, (NUM_OF_THREADS - 1));

    qsort(base, size, sizeof(char *), _CmpWords);

    return (NULL);
}

static void *_MergeSort(void *param)
{
	/* the last thread should handle the reminder */
	char **last = sg_big_data + SIZE_BIG_DATA - sg_merge_range - REMINDER;
	size_t array_size = (param != last)	? sg_merge_range
										: sg_merge_range + (REMINDER);

	size_t middle = (sg_merge_range / 2);

	assert(param);

	return _Merge(param, middle, array_size);
}

static void *_BubbleSort(void *param)
{
	/* the last thread should handle the reminder */
	size_t i = 0;
	int stop_sort = CONTINUE;
	char **to_sort = sg_big_data + ((size_t)param * THREAD_RANGE(NUM_OF_THREADS));
	size_t array_size = ARRAY_SIZE((size_t)param, NUM_OF_THREADS - 1);

	assert(param);

    array_size -= 1;
    for (; 0 < array_size && stop_sort != STOP; --array_size)
    {
        stop_sort = STOP;
        for (i = 0; i < array_size; ++i)
        {
            if(0 < strcmp(to_sort[i], to_sort[i + 1]))
            {
                _Swap(to_sort + i, (to_sort + i + 1));
                stop_sort = CONTINUE;
            }
        }
    }

    return (NULL);
}

static void *_InsertSort(void *param)
{
	/* the last thread should handle the reminder */
	size_t i = 0, j = 0;
	char **to_sort = sg_big_data + ((size_t)param * THREAD_RANGE(NUM_OF_THREADS));
	size_t array_size = ARRAY_SIZE((size_t)param, NUM_OF_THREADS - 1);

	assert(param);

    for (i = 1; i < array_size; ++i)
    {
        for (j = i; 0 < j && (0 < strcmp(to_sort[j - 1], to_sort[j])); --j)
        {
            _Swap(to_sort + j, (to_sort + j - 1));
        }
    }

	return (NULL);
}

static void *_SelectionSort(void *param)
{
    size_t i = 0, j = 0;
    size_t min = 0;
	char **to_sort = sg_big_data + ((size_t)param * THREAD_RANGE(NUM_OF_THREADS));
	size_t array_size = ARRAY_SIZE((size_t)param, NUM_OF_THREADS - 1);

	assert(param);

    for (i = 0; i < array_size; ++i)
    {
        for (min = i, j = (i + 1); j < array_size; ++j)
        {
            min = (0 < strcmp(to_sort[j], to_sort[min]) ? min : j);
        }

        _Swap(to_sort + min, to_sort + i);
    }

	return (NULL);
}
/*----------------------------------------------------------------------------*/

static int _RandCmp(const void *a, const void *b)
{
    UNUSED(a);
    UNUSED(b);

    return ((rand() % 91) - 45);
}

static int _CmpWords(const void *a, const void *b)
{
    return strcmp(*(char **)a, *(char **)b);
}

static void *_Merge(char **to_merge, size_t middle, size_t array_size)
{
	size_t i = 0;
	size_t left = 0;
	size_t right = middle;
	char **copy_array = NULL;

	copy_array = (char **)calloc(array_size, sizeof(char *));
	if (!copy_array)
	{
		PRINT_ERROR("malloc failed in _Merge");

		return (NULL);
	}

	while (left < middle && right < array_size)
	{
		if (0 > strcmp(to_merge[left], to_merge[right]))
		{
			copy_array[i] = to_merge[left];
			++left;
		}

		else
		{
			copy_array[i] = to_merge[right];
			++right;
		}
		++i;
	}

	for ( ; left < middle; ++i, ++left)
	{
		copy_array[i] = to_merge[left];
	}

	for ( ; right < array_size; ++i, ++right)
	{
		copy_array[i] = to_merge[right];
	}

	for (i = 0; i < array_size; ++i)
	{
		to_merge[i] = copy_array[i];
	}

	free(copy_array);
	copy_array = NULL;

	return (NULL);
}

static void _Swap(char **a, char **b)
{
	char *temp = NULL;

	assert(a);
	assert(b);

	temp = *a;
	*a = *b;
	*b = temp;
}
/*----------------------------------------------------------------------------*/
