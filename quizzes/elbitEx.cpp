//
// Created by orpaz on 27/12/2020.
//

#include <cstddef>
#include <iostream>

void TestSmallestWithSameNumDigits();
void TestLargestOnsSequence();
void TestMissingNum();
void TestMissingTwoNum();


int main()
{
    TestSmallestWithSameNumDigits();
    TestLargestOnsSequence();
    TestMissingNum();
    TestMissingTwoNum();

    return 0;
}

int SmallestWithSameNumDigits(int number)
{
    int result = 1;
    int copy = number;

    while (number)
    {
        result *= 10;
        number /= 10;
    }

    return (0 > copy) ? (result-1)*-1 : result / 10;
}

size_t LargestOnsSequence(int num)
{
    size_t maxSequence = 0;
    size_t currSequence = 0;

    if (num < 0)
    {
        num *= -1;
    }

    while (num)
    {
        const int BIT_MASK = 1;
        currSequence = (num & BIT_MASK) ? currSequence + 1 : 0;
        if (currSequence > maxSequence)
        {
            maxSequence = currSequence;
        }
        num >>= 1;
    }

    return maxSequence;
}

int MissingNum(int arr[], size_t range)
{
    int xorArr = 0;
    int xorRange = range;

    for (int i = 0; i < range; ++i)
    {
        xorArr ^= arr[i];
        xorRange ^= i;
    }

    return (xorRange ^ xorArr);
}

void MissingTwoNum(int arr[], int range, int *num1, int *num2)
{
    int sumArr = 0;
    int sizeArr = range - 1;

    int sumRange = range;
    sumRange += range-1;

    for (int i = 0; i < sizeArr; ++i)
    {
        sumArr += arr[i];
        sumRange += i;
    }

    int bisector = (sumRange - sumArr) / 2;
    int sumLowerArr = -bisector;
    int sumLowerRange = 0;
    int sumUpperArr = 0;
    int sumUpperRange = range;

    for (int i = 0; i < bisector; ++i)
    {
        sumLowerRange += i;
    }

    for (int i = bisector+1; i < range; ++i)
    {
        sumUpperRange += i;
    }

    int *endOfArr = arr + sizeArr;
    for (int *i = arr; i < endOfArr; ++i)
    {
        if (bisector > *i)
        {
            sumLowerArr += *i;
        }
        else
        {
            sumUpperArr += *i;
        }
    }
    *num1 = sumLowerRange - sumLowerArr;
    *num2 = sumUpperRange - sumUpperArr;
}

void TestMissingTwoNum()
{
    std::cout << "MissingTwoNum : ";

    size_t tests = 0;
    size_t numOfTests = 0;
    const size_t RANGE = 9;
    const size_t SIZE_ARR = RANGE - 1;

    int arr1[SIZE_ARR] = {0, 2, 8, 9, 5, 7, 4, 3};
    int arr2[SIZE_ARR+1] = {6, 2, 0, 9, 5, 1, 4, 3, 10};

    int num1 = 0;
    int num2 = 0;

    MissingTwoNum(arr1, RANGE, &num1, &num2);
    tests += (1 == num1);
    ++numOfTests;
    std::cout << num1 << std::endl;
    tests += (6 == num2);
    ++numOfTests;
    std::cout << num2 << std::endl;

    MissingTwoNum(arr2, RANGE+1, &num1, &num2);
    tests += (7 == num1);
    std::cout << num1 << std::endl;
    ++numOfTests;
    tests += (8 == num2);
    ++numOfTests;
    std::cout << num2 << std::endl;

    if (tests == numOfTests)
    {
        std::cout << "Success!\n";
    }
    else
    {
        std::cout << "Failure!\n";
        std::cout << numOfTests - tests << " tests has been failed\n";
    }
}

void TestMissingNum()
{
    std::cout << "MissingNum : ";

    size_t tests = 0;
    size_t numOfTests = 0;
    const size_t range = 9;

    int arr1[range] = {1, 2, 8, 9, 5, 7, 4, 3, 0};
    int arr2[range] = {6, 2, 8, 9, 5, 7, 4, 3, 0};

    tests += (6 == MissingNum(arr1, range));
    ++numOfTests;
//    std::cout << MissingNum(arr1, range) << std::endl;

    tests += (1 == MissingNum(arr2, range));
    ++numOfTests;
//    std::cout << MissingNum(arr2, range) << std::endl;

    if (tests == numOfTests)
    {
        std::cout << "Success!\n";
    }
    else
    {
        std::cout << "Failure!\n";
    }
}

void TestSmallestWithSameNumDigits()
{
    std::cout << "SmallestWithSameNumDigits : ";

    size_t tests = 0;
    tests += (1000 == SmallestWithSameNumDigits(4568));
    tests += (1000 == SmallestWithSameNumDigits(1000));
    tests += (10 == SmallestWithSameNumDigits(12));
    tests += (10 == SmallestWithSameNumDigits(99));
    tests += (-999999 == SmallestWithSameNumDigits(-100000));
    tests += (-999 == SmallestWithSameNumDigits(-313));

    if (tests == 6)
    {
        std::cout << "Success!\n";
    }
    else
    {
        std::cout << "Failure!\n";
    }
}

void TestLargestOnsSequence()
{
    std::cout << "LargestOnsSequence : ";

    size_t tests = 0;
    size_t numOfTests = 0;

    tests += (3 == LargestOnsSequence(7));
    ++numOfTests;

    tests += (3 == LargestOnsSequence(-7));
    ++numOfTests;

    tests += (4 == LargestOnsSequence(146391));
    ++numOfTests;

    tests += (12 == LargestOnsSequence(0xFFF0FA));
    ++numOfTests;

    tests += (1 == LargestOnsSequence(0xAAAAAAA));
    ++numOfTests;

    tests += (31 == LargestOnsSequence(0x7FFFFFFF));
    ++numOfTests;

    tests += (31 == LargestOnsSequence(-0x7FFFFFFF));
    ++numOfTests;

    tests += (3 == LargestOnsSequence(0x7777));
    ++numOfTests;

    if (tests == numOfTests)
    {
        std::cout << "Success!\n";
    }
    else
    {
        std::cout << "Failure!\n";
    }
}