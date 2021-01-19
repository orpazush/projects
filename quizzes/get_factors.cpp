//
// Created by orpaz on 01/12/2020.
//

#include <iostream>
#include <cstring>
#include <cstdlib>

int *GetFactors(const int arr[], size_t size);
int *NoDivisionGetFactor(const int arr[], size_t size);
int *NaiveGetFactors(const int arr[], size_t size);

void NoZerosTest();
void OneZeroTest();
void MoreThenOneZeroTest();
void RandomValuesTest();


const size_t RANDOM_SIZE = 5000;

int main()
{
    NoZerosTest();
    OneZeroTest();
    MoreThenOneZeroTest();
    RandomValuesTest();

    return 0;
}

void NoZerosTest()
{
    std::cout << "\nNoZerosTest:\n";

    const size_t SIZE = 5;
    size_t naiveErrors = 0;
    size_t noDivisionErrors = 0;
    size_t withDivisionErrors = 0;

    int arr[SIZE] = {1, 2, 3, 4, 5};
    int result[SIZE] = {120, 60, 40, 30, 24};

    int *test1 = NaiveGetFactors(arr, SIZE);
    int *test2 = GetFactors(arr, SIZE);
    int *test3 = NoDivisionGetFactor(arr, SIZE);

    for (size_t i = 0; i < SIZE; ++i)
    {
        naiveErrors += (test1[i] != result[i]);
        withDivisionErrors += (test2[i] != result[i]);
        noDivisionErrors += (test3[i] != result[i]);
    }

    std::cout << "NaiveGetFactors : ";
    naiveErrors > 0 ? std::cout << "failure!\n" : std::cout << "success!\n";
    std::cout << "GetFactors : ";
    withDivisionErrors > 0 ? std::cout << "failure!\n" : std::cout << "success!\n";
    std::cout << "NoDivisionGetFactor : ";
    noDivisionErrors > 0 ? std::cout << "failure!\n" : std::cout << "success!\n";

    delete [] test1;
    delete [] test2;
    delete [] test3;
}

void OneZeroTest()
{
    std::cout << "\nOneZeroTest:\n";

    const size_t SIZE = 5;
    size_t naiveErrors = 0;
    size_t noDivisionErrors = 0;
    size_t withDivisionErrors = 0;

    int arr[SIZE] = {1, 2, 3, 0, 5};
    int result[SIZE] = {0, 0, 0, 30, 0};

    int *test1 = NaiveGetFactors(arr, SIZE);
    int *test2 = GetFactors(arr, SIZE);
    int *test3 = NoDivisionGetFactor(arr, SIZE);

    for (size_t i = 0; i < SIZE; ++i)
    {
        naiveErrors += (test1[i] != result[i]);
        withDivisionErrors += (test2[i] != result[i]);
        noDivisionErrors += (test3[i] != result[i]);
    }

    std::cout << "NaiveGetFactors : ";
    naiveErrors > 0 ? std::cout << "failure!\n" : std::cout << "success!\n";
    std::cout << "GetFactors : ";
    withDivisionErrors > 0 ? std::cout << "failure!\n" : std::cout << "success!\n";
    std::cout << "NoDivisionGetFactor : ";
    noDivisionErrors > 0 ? std::cout << "failure!\n" : std::cout << "success!\n";

    delete [] test1;
    delete [] test2;
    delete [] test3;

}

void MoreThenOneZeroTest()
{
    std::cout << "\nMoreThenOneZeroTest:\n";

    const size_t SIZE = 5;

    size_t naiveErrors = 0;
    size_t noDivisionErrors = 0;
    size_t withDivisionErrors = 0;

    int arr[SIZE] = {1, 0, 3, 0, 5};
    int result[SIZE] = {0, 0, 0, 0, 0};

    int *test1 = NaiveGetFactors(arr, SIZE);
    int *test2 = GetFactors(arr, SIZE);
    int *test3 = NoDivisionGetFactor(arr, SIZE);

    for (size_t i = 0; i < SIZE; ++i)
    {
        naiveErrors += (test1[i] != result[i]);
        withDivisionErrors += (test2[i] != result[i]);
        noDivisionErrors += (test3[i] != result[i]);
    }

    std::cout << "NaiveGetFactors : ";
    naiveErrors > 0 ? std::cout << "failure!\n" : std::cout << "success!\n";
    std::cout << "GetFactors : ";
    withDivisionErrors > 0 ? std::cout << "failure!\n" : std::cout << "success!\n";
    std::cout << "NoDivisionGetFactor : ";
    noDivisionErrors > 0 ? std::cout << "failure!\n" : std::cout << "success!\n";

    delete [] test1;
    delete [] test2;
    delete [] test3;
}


void RandomValuesTest()
{
    std::cout << "\nRandomValuesTest:\n";

    size_t noDivisionErrors = 0;
    size_t withDivisionErrors = 0;

    time_t t;
    srand((unsigned) time(&t));

    int arr[RANDOM_SIZE];

    for (size_t i = 0; i < RANDOM_SIZE; ++i)
    {
        arr[i] = rand();
    }

    int *result = NaiveGetFactors(arr, RANDOM_SIZE);
    int *test2 = GetFactors(arr, RANDOM_SIZE);
    int *test3 = NoDivisionGetFactor(arr, RANDOM_SIZE);

    for (size_t i = 0; i < RANDOM_SIZE; ++i)
    {
        withDivisionErrors += (test2[i] != result[i]);
        noDivisionErrors += (test3[i] != result[i]);
    }

    std::cout << "GetFactors : ";
    withDivisionErrors > 0 ? std::cout << "failure!\n" : std::cout << "success!\n";
    std::cout << "NoDivisionGetFactor : ";
    noDivisionErrors > 0 ? std::cout << "failure!\n" : std::cout << "success!\n";

    delete [] result;
    delete [] test2;
    delete [] test3;
}


int *GetFactors(const int arr[], size_t size)
{
    int *result = new int[size];
    memset(result, 0, sizeof(int) * size);
    const int *endOfArr = arr + size;

    int factor = 1;
    for (const int *i = arr; i < endOfArr; ++i)
    {
        factor *= *i;
    }

    if (factor == 0)
    {
        int *factorsWithoutFirstZero = result;
        const int *i = arr;
        factor = 1;

        while (*i != 0)
        {
            factor *= *i;
            ++i;
            ++factorsWithoutFirstZero;
        }

        *factorsWithoutFirstZero = factor;
        ++i;

        while (i < endOfArr)
        {
            *factorsWithoutFirstZero *= *i;
            ++i;
        }
    }

    else
    {
        for (size_t i = 0; i < size; ++i)
        {
            result[i] = factor / arr[i];
        }
    }

    return result;
}

int *NoDivisionGetFactor(const int arr[], size_t size)
{
    int *result = new int[size];
    int *afterFactors = new int[size];
    int beforeFactors = 1;

    *(afterFactors + size - 1) = 1;
    for (size_t i = size - 1; 0 < i; --i)
    {
        afterFactors[i - 1] = (arr[i] * afterFactors[i]);
    }

    for (size_t i = 0; i < size; ++i)
    {
        result[i] = beforeFactors * afterFactors[i];
        beforeFactors *= arr[i];
    }

    delete[] afterFactors;

    return (result);
}

int *NaiveGetFactors(const int arr[], size_t size)
{
    int *result = new int[size];
    const int *endOfArr = arr + size;

    for (size_t i = 0; i < size; ++i)
    {
        size_t j = 0;
        result[i] = 1;

        while (j < i)
        {
            result[i] *= arr[j];
            ++j;
        }
        ++j;
        while (j < size)
        {
            result[i] *= arr[j];
            ++j;
        }
    }
    return result;
}
