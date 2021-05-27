///////////////////////////////////////////////////////////////////////////////
//                            Merge Array                                    //
// Created by orpaz on 27/05/2021.                                           //
///////////////////////////////////////////////////////////////////////////////
// Question: Given 2 sorted arrays, A and B, where A is long enough to hold  //
//           the contents of A and B, write a function to copy the contents  //
//           of B into A without using any buffer or additional memory.      //
///////////////////////////////////////////////////////////////////////////////

#include <cstddef>      //size_t
#include <iostream>     //cout
#include <algorithm>    //sort
#include <vector>

using namespace std;

void TestMergeArray();

int main()
{
    TestMergeArray();

    return 0;
}

void MergeArray(int arrayA[], const int arrayB[], size_t lenA, size_t lenB)
{
    size_t AContentLen = lenA - lenB;
    int *a = arrayA + AContentLen - 1;
    const int *b = arrayB + lenB - 1;

    for (int *i = arrayA+lenA-1; i >= arrayA; --i)
    {
        //case all the content of B has been copied to A
        if (b < arrayB)
        {
            return;
        }

        //case there is only content in B left to copy
        else if (a < arrayA)
        {
            while (b >= arrayB)
            {
                *i =*b;
                --i;
                --b;
            }
        }

        //case the content in A is bigger
        else if (*a > *b)
        {
            *i = *a;
            --a;
        }
        //case the content in B is bigger
        else
        {
            *i = *b;
            --b;
        }
    }
}

template <typename T>
bool CmpArrays(T arr1[], T arr2[], size_t len1, size_t len2)
{
    if (len1 != len2)
    {
        return false;
    }
    T *i = arr1;
    T *j = arr2;
    T *endOfArr1 = arr1 + len1;
    while (i < endOfArr1 && *i == *j)
    {
        ++i;
        ++j;
    }

    return (i == endOfArr1);
}
void TestMergeArray()
{
    cout << "TestMergeArray : ";

    size_t numOfTests = 0;
    size_t tests = 0;

    int A1[10] = {1, 2, 3, 4, 5};
    int B1[] = {6, 7, 8, 9, 10};
    int result[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t lenA = sizeof A1 / sizeof A1[0];
    size_t lenB = sizeof B1 / sizeof B1[0];
    size_t lenRes = sizeof result / sizeof result[0];

    MergeArray(A1, B1, lenA, lenB);
    tests += CmpArrays(A1, result, lenA, lenRes);
    ++numOfTests;

    int A2[10] = {6, 7, 8, 9, 10};
    int B2[] = {1, 2, 3, 4, 5};
    lenA = sizeof A2 / sizeof A2[0];
    lenB = sizeof B2 / sizeof B2[0];
    lenRes = sizeof result / sizeof result[0];

    MergeArray(A2, B2, lenA, lenB);
    tests += CmpArrays(A2, result, lenA, lenRes);
    ++numOfTests;

    int A3[10] = {1, 2, 4, 5, 6, 9, 10};
    int B3[] = {3, 7, 8};
    lenA = sizeof A3 / sizeof A3[0];
    lenB = sizeof B3 / sizeof B3[0];
    lenRes = sizeof result / sizeof result[0];

    MergeArray(A3, B3, lenA, lenB);
    tests += CmpArrays(A3, result, lenA, lenRes);
    ++numOfTests;

    lenA = rand() % 1000;
    lenB = rand() % 1000;

    int *randA = new int[lenA + lenB];
    int *randB = new int[lenB];

    for(size_t i = 0; i < lenA; ++i)
    {
        randA[i] = rand();
    }

    for(size_t i = 0; i < lenB; ++i)
    {
        randB[i] = rand();
    }
    sort(randA, randA + lenA);
    sort(randB, randB + lenB);

    MergeArray(randA, randB, (lenA + lenB), lenB);

    bool randTest = true;
    for(size_t i = 1; i < (lenA + lenB); ++i)
    {
        if (randA[i-1] > randA[i])
        {
            randTest = false;
        }
    }
    tests += randTest;
    ++numOfTests;

    if (tests == numOfTests)
    {
        cout << "Success!\n";
        cout << numOfTests << " tests\n";
    }
    else
    {
        cout << "Failure!\n";
        cout << numOfTests - tests << " tests has been failed\n";
    }
}

