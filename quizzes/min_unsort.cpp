
#include <iostream>
#include <algorithm>
#include "ca_test_util.hpp"

using namespace std;

static const size_t SIZE = 5000;
void TestHardCoded();
void TestRandom();
bool MinUnsort(int arr[], size_t size, size_t *begin, size_t *end);

int main()
{
    TestHardCoded();
    TestRandom();

    TEST_SUMMARY();
}

bool MinUnsort(int arr[], size_t size, size_t *beginIdx, size_t *endIdx)
{
    int *i = arr + 1;
    int *begin = arr;
    int *end = arr + size - 1;

    for (i = arr + 1; *i >= *begin && i <= end; ++i)
    {
        ++begin;
    }

    if (begin != arr)
    {
        while (i <= end)
        {
            while (*i < *(begin - 1) && begin != arr)
            {
                --begin;
            }
            ++i;
        }
    }

    for (i = end - 1; *i <= *end && i >= begin; --i)
    {
        --end;
    }

    if (end != (arr + size - 1))
    {
        while (i >= begin)
        {
            while (*i > *(end + 1) && end != (arr + size - 1))
            {
                ++end;
            }
            --i;
        }
    }

    *beginIdx = begin - arr;
    *endIdx = end - arr;

    return (*beginIdx == *endIdx);
}

void TestHardCoded()
{
    size_t begin = 0;
    size_t end = 0;
    size_t size = 0;

    int arr[] = {1, 2, 3, 3, 9, 8, 7, 6, 5};
    size = sizeof(arr) / sizeof(int);
    MinUnsort(arr, size, &begin, &end);
    BOOL_TEST((begin == 4));
    BOOL_TEST((end == 8));

    int arr1[] = {1, 2, 3, 9, 8, 7, 6, 1};
    size = sizeof(arr1) / sizeof(int);
    MinUnsort(arr1, size, &begin, &end);
    BOOL_TEST((begin == 1));
    BOOL_TEST((end == 7));

    int arr2[] = {1, 2, 3, 9, 8, 7, 6, 1, 2, 3, 11, 12, 13};
    size = sizeof(arr2) / sizeof(int);
    MinUnsort(arr2, size, &begin, &end);
    BOOL_TEST((begin == 1));
    BOOL_TEST((end == 9));

    int arr3[] = {1, 2, 3, 4, 5, 6, 7, 8};
    size = sizeof(arr3) / sizeof(int);
    BOOL_TEST(MinUnsort(arr3, size, &begin, &end));
}

void TestRandom()
{
    time_t t;
    srand((unsigned) time(&t));
    size_t i = 0;
    size_t begin = 0;
    size_t end = 0;

    for (size_t j = 0; j < 10; ++j)
    {
        size_t size = (rand() % (SIZE - 100)) + 100;
        size_t firstRange = rand() % 100;
        size_t middleRange = (rand() % (size - firstRange)) + firstRange;

        int arr[SIZE] = {0};
        int copyArr[SIZE] = {0};
        for (i = 0; i < firstRange; ++i)
        {
            arr[i] = i;
        }
        for ( ; i < middleRange; ++i)
        {
            arr[i] = rand() % size;
        }
        arr[i] = (rand() % 100) + size - 100;
        for (++i; i < size; ++i)
        {
            arr[i] = arr[i - 1] + 1;
        }

        copy(arr, arr + size, copyArr);

        if(!MinUnsort(arr, size, &begin, &end))
        {
            sort((arr + begin), (arr + end + 1));
            sort((copyArr + begin + 1), (copyArr + end));
        }
        cout << "first index: " << begin << endl;
        cout << "last index: " << end << endl;
        BOOL_TEST(is_sorted(arr, (arr + size)));
        BOOL_TEST(!(is_sorted(copyArr, copyArr + size)));
    }
}
