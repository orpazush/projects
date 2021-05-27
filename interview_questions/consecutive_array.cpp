///////////////////////////////////////////////////////////////////////////////
//                            Consecutive Array                              //
// Created by orpaz on 27/05/2021.                                           //
///////////////////////////////////////////////////////////////////////////////
// Question: Given an unsorted array, find the length of the longest         //
//           sequence of consecutive numbers in the array.                   //
///////////////////////////////////////////////////////////////////////////////

#include <cstddef>      //size_t
#include <iostream>     //cout
#include <algorithm>    //sort

using namespace std;

void TestConsecutiveArray();

int main()
{
    TestConsecutiveArray();

    return 0;
}

// time complex: O(N*log(N))
size_t ConsecutiveArray(int array[], size_t arrayLen)
{
    int *endOfArray = array + arrayLen;
    sort(array, endOfArray);

    size_t longestSequence = 0;
    size_t currSequence = 1;
    int *formerInt = array;

    for (int *i = array + 1; i < endOfArray; ++i)
    {
        if (*i == (*formerInt + 1))
        {
            ++currSequence;
        }

        else if (*i > *formerInt)
        {
            if (longestSequence < currSequence)
            {
                longestSequence = currSequence;
            }
            currSequence = 1;
        }

        formerInt = i;
    }

    return ((longestSequence < currSequence) ? currSequence : longestSequence);
}

void TestConsecutiveArray()
{
    cout << "TestConsecutiveArray : ";

    size_t numOfTests = 0;
    size_t tests = 0;

    int test1[] = {4, 2, 1, 6, 5};
    tests += (3 == ConsecutiveArray(test1, sizeof test1 / sizeof test1[0]));
    ++numOfTests;

    int test2[] = {1, 2, 2};
    tests += (2 == ConsecutiveArray(test2, sizeof test2 / sizeof test2[0]));
    ++numOfTests;

    int test3[] = {5, 5, 1, 3, 3, 3};
    tests += (1 == ConsecutiveArray(test3, sizeof test3 / sizeof test3[0]));
    ++numOfTests;

    int test4[] = {9, 7, 1, 1, 2, 8, 4, 5, 6, 3, 6, -1, 5};
    tests += (9 == ConsecutiveArray(test4, sizeof test4 / sizeof test4[0]));
    ++numOfTests;

    if (tests == numOfTests)
    {
        cout << "Success!\n";
    }
    else
    {
        cout << "Failure!\n";
    }


}

