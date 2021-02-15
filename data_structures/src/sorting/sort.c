/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review : Gilio & shachar						         *
 * 					Last update : 9.6.20									 *
 ****************************************************************************/
#include <stddef.h> /* size_t */
#include <malloc.h> /* malloc */
#include <assert.h> /* assert */

#include "sort.h"

#define CONTINUE (1)
#define STOP (0)
#define MERGE_SUCCESS (0)
#define MALLOC_FAIL (1)
#define NOT_IN_ARRAY (-1)

#ifndef NDEBUG
#define PRINT_ERROR(str) fprintf(stderr, "ERROR( %s : %d ) -- %s\n",\
								 __FILE__, __LINE__ - 6, str)
#else
#define PRINT_ERROR(str)
#endif

/*-----------------------------static functions-------------------------------*/
static void _Swap(int *a, int *b);
static void _RadixCountingSort(int to_sort[], size_t array_size, size_t digit);
static int _Merge(int to_merge[], int middle, int array_size);
static void _SwapBytes(void *a, void *b, size_t bytes);
static int _RecurSearch(int sorted_array[], int to_find, int left, int right);
/*----------------------------------------------------------------------------*/

/*-----------------------------Sort Functions---------------------------------*/
void BubbleSort(int to_sort[], size_t array_size)
{
    int *i = to_sort;
    int *end_array = to_sort + array_size;
    int stop_sort = CONTINUE;

	assert(to_sort);

    while (stop_sort != STOP)
    {
        stop_sort = STOP;
        for (i = to_sort; (i + 1) < end_array; ++i)
        {
            if(*i > *(i + 1))
            {
                _Swap(i, (i + 1));
                stop_sort = CONTINUE;
            }
        }
		--end_array;
    }
}

void InsertSort(int to_sort[], size_t array_size)
{
    int *i = NULL, *j = NULL;
	int *end = to_sort + array_size;

	assert(to_sort);

    for (i = (to_sort + 1); i < end; ++i)
    {
        for (j = i; to_sort < j && (*j < *(j - 1)); --j)
        {
            _Swap(j, (j - 1));
        }
    }
}

void SelectionSort(int to_sort[], size_t array_size)
{
    size_t i = 0, j = 0;
    size_t min = 0;

	assert(to_sort);

    for (i = 0; i < array_size; ++i)
    {
        for (min = i, j = (i + 1); j < array_size; ++j)
        {
            min = (to_sort[min] < to_sort[j]) ? min : j;
        }

        _Swap(&to_sort[min], &to_sort[i]);
    }
}

void CountingSort(int to_sort[], size_t array_size, size_t max_range)
{
    size_t i = 0, j = 0;
    int *position = NULL;

	assert(to_sort);

	position = (int *)calloc((max_range + 1), sizeof(int));
	if (!position)
	{
		PRINT_ERROR("calloc");
	    return;
	}
    for (i = 0; i < array_size; ++i)
    {
        ++position[to_sort[i]];
    }

	for (i = 0; i < array_size; ++i)
	{
		while (0 == position[j])
		{
			++j;
		}

		to_sort[i] = j;
		--position[j];
	}

	free(position);
	position = NULL;

/*
/    int *copy = NULL;

	copy = (int *)calloc(array_size, sizeof(int));
	if (!copy)
	{
		PRINT_ERROR("calloc");

		free(position);
		position = NULL;

		return;
	}
/
position[0] = -1;

    // for (i = 0; i < max_range; ++i)
    // {
    //     position[i + 1] += position[i];
    // }
	//
	//

    // for (i = (array_size - 1); 0 <= (int)i; --i)
    // {
    //     copy[position[to_sort[i]]] = to_sort[i];
    //     position[to_sort[i]]--;
    // }
	//
    // for (i = 0; i < array_size; ++i)
    // {
    //     to_sort[i] = copy[i];
    // }

	//
    // free(copy);
    // copy = NULL;
	*/
}

void RadixSort(int to_sort[], size_t array_size, size_t digits)
{
    size_t curr_digit = 0;

	assert(to_sort);

    for (curr_digit = 1; 0 < digits; curr_digit *=10, --digits)
    {
        _RadixCountingSort(to_sort, array_size, curr_digit);
    }
}

int MergeSort(int to_sort[], size_t array_size)
{
    int status = MERGE_SUCCESS;
    size_t left_size = (array_size / 2);
    size_t right_size = (array_size - left_size);

    assert(to_sort);

    if (2 < array_size)
    {
        status = MergeSort((to_sort), left_size);
        if (!status)
        {
            status = MergeSort((to_sort + left_size), right_size);
        }
    }

    return ((!status) ? _Merge(to_sort, left_size, array_size) : status);
}

void QuickSort(void *base, size_t size, size_t bytes, compare_t cmp)
{
    char *arr = (char *)base;

    int i = 0;
    int pivot = size - 1;

    if (size < 2)
    {
        return;
    }

    while (i <= pivot)
    {
        if(0 > cmp(&arr[pivot * bytes], &arr[i * bytes]))
        {
            _SwapBytes(&arr[i * bytes], &arr[(pivot * bytes) - bytes], bytes);
            _SwapBytes(&arr[pivot * bytes],&arr[(pivot * bytes) - bytes],bytes);
            --pivot;
        }
        else
        {
            ++i;
        }
    }

    QuickSort(arr, pivot , bytes, cmp);
    QuickSort(&arr[(pivot * bytes) + bytes], (size - pivot - 1) , bytes, cmp);
}
/*----------------------------------------------------------------------------*/

/*-------------------------------Binary Searchs-------------------------------*/
int IterBinarySearch(int sorted_array[], size_t array_size, int to_find)
{
    size_t left = 0;
    size_t right = array_size;
    size_t middle = 0;

    assert(sorted_array);

    while (left < right)
    {
        middle = ((right + left) / 2);

        if (sorted_array[middle] == to_find)
        {
            return (middle);
        }

        else if (sorted_array[middle] < to_find)
        {
            left = ++middle;
        }

        else
        {
            right = middle;
        }
    }

    return (NOT_IN_ARRAY);
}

int RecurBinarySearch(int sorted_array[], size_t array_size, int to_find)
{
    assert(sorted_array);

	return (_RecurSearch(sorted_array, to_find, 0, (array_size - 1)));

}
/*----------------------------------------------------------------------------*/


/*-----------------------------Static Definitions-----------------------------*/
static void _RadixCountingSort(int to_sort[], size_t array_size, size_t digit)
{
    size_t i = 0;
    int relevant_digit = 0;
    int *copy = NULL;
    int base[10] = {0};

	assert(to_sort);

	copy = (int *)calloc(array_size, sizeof(int));
	if (!copy)
	{
#ifndef NDEBUG
		perror("_RadixCountingSort in copy: ");
#endif
	}

    for (i = 0; i < array_size; ++i)
    {
        relevant_digit = ((to_sort[i]/digit) % 10);
        ++base[relevant_digit];
    }
    base[0]--;
    for (i = 0; i < 9; ++i)
    {
        base[i + 1] += base[i];
    }
    for (i = (array_size - 1); 0 <= (int)i; --i)
    {
        relevant_digit = ((to_sort[i]/digit) % 10);
        copy[base[relevant_digit]] = to_sort[i];
        base[relevant_digit]--;
    }
    for (i = 0; i < array_size; ++i)
    {
        to_sort[i] = copy[i];
    }

    free(copy);
    copy = NULL;
}

static void _Swap(int *a, int *b)
{
    int temp = 0;

    temp = *a;
    *a = *b;
    *b = temp;
}

static int _Merge(int to_merge[], int middle, int array_size)
{
	int i = 0;
	int left = 0;
	int right = middle;
	int *copy_array;

	assert(to_merge);

	copy_array = (int *)malloc(sizeof(int) * array_size);
	if (!copy_array)
	{
		PRINT_ERROR("malloc failed in _Merge");

		return (MALLOC_FAIL);
	}

	while (left < middle && right < array_size)
	{
		if (to_merge[left] < to_merge[right])
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

	return (MERGE_SUCCESS);
}

/* swaps a given number of 'bytes' between two elements pointed by 'a' & 'b' */
static void _SwapBytes(void *a, void *b, size_t bytes)
{
	unsigned char temp = 0;
	unsigned char *byte_a = NULL;
	unsigned char *byte_b = NULL;

	assert(a);
	assert(b);

	byte_a = (unsigned char *)a;
	byte_b = (unsigned char *)b;

	for ( ; bytes; --bytes, ++byte_a, ++byte_b)
	{
		temp = *byte_a;
		*byte_a = *byte_b;
		*byte_b = temp;
	}
}

static int _RecurSearch(int sorted_array[], int to_find, int left, int right)
{
    int middle = ((left + right) / 2);

    assert(sorted_array);

    if (left > right)
    {
        return (NOT_IN_ARRAY);
    }

    else if (sorted_array[middle] == to_find)
    {
        return (middle);
    }

    else if (sorted_array[middle] < to_find)
    {
        return (_RecurSearch(sorted_array, to_find, ++middle, right));
    }

    else
    {
        return (_RecurSearch(sorted_array, to_find, left, middle));
    }
}
/*----------------------------------------------------------------------------*/
