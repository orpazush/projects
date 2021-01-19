//
// Created by orpaz on 10/12/2020.
//

#include <cstddef>          //size_t
#include <cstdlib>          //rand
#include <iostream>
#include <algorithm>

using namespace std;

template <typename T>
void BubbleSort(T toSort[], size_t size)
{
    bool stop = false;

    for(T *i = (toSort + size); toSort < i && stop == false; --i)
    {
        stop = true;
        for (T *j = (toSort+1); j < i; ++j)
        {
            if (*j < *(j-1))
            {
                swap(*j, *(j-1));
                stop = false;
            }
        }
    }
}

template <typename T>
void InsertionSort(T toSort[], size_t size)
{
    T *end = toSort + size;

    for(T *i = (toSort+1); i < end; ++i)
    {
        for (T *j = i; *j < *(j-1); --j)
        {
            swap(*j, *(j-1));
        }
    }
}

template <typename T>
void SelectionSort(T toSort[], size_t size)
{
    T *end = toSort + size;

    for(T *i = toSort; i < end; ++i)
    {
        T min = *i;
        for (T *j = i; j < end; ++j)
        {
            if (min > *j)
            {
                min = *j;
            }
        }
        *i = min;
    }
}

template <typename T>
void CountingSort(T toSort[], size_t size, T maxRange)
{
    T *end = toSort + size;
    T *range = new T[maxRange]();

    for(T *i = toSort; i < end; ++i)
    {
        ++range[*i];
    }

    T *j = toSort;
    for (T i = 0; i < maxRange; ++i)
    {
        while (0 < range[i])
        {
            *j = i;
            ++j;
        }
    }
}


void Test(void(*sorter)(int toSort[], size_t))
{
    const size_t SIZE = 5000;
    size_t errors = 0;
    time_t seed = time(NULL);
    srand(seed);

    int test1[SIZE];

    for (size_t i = 0; i < SIZE; ++i)
    {
        test1[i] = rand() % 100;
    }

    sorter(test1, SIZE);

        if (errors > 0)
    {
        cout << "Fail! with - " << errors << " errors\n";
    }
    else
    {
        cout << "Success!\n";
    }
}

void CountingTest()
{
    const size_t SIZE = 5000;
    size_t errors = 0;
    const int MAX_RANGE = 50;
    time_t seed = time(NULL);
    srand(seed);

    int test1[SIZE];

    for (size_t i = 0; i < SIZE; ++i)
    {
        test1[i] = rand() % MAX_RANGE;
    }

    CountingSort(test1, SIZE, MAX_RANGE);

    if (errors > 0)
    {
        cout << "Fail! with - " << errors << " errors\n";
    }
    else
    {
        cout << "Success!\n";
    }
}

int main()
{
    cout << "BubbleSort test: ";
    Test(BubbleSort);

    cout << "InsertionSort test: ";
    Test(InsertionSort);

    cout << "SelectionSort test: ";
    Test(SelectionSort);

    cout << "CountingSort test: ";
    CountingTest();

    return 0;
}
