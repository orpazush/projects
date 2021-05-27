///////////////////////////////////////////////////////////////////////////////
//                           Find Duplicates                                 //
// Created by orpaz on 27/05/2021.                                           //
///////////////////////////////////////////////////////////////////////////////
// Question: Given an array of integers where each value 1 <= x <= len(array)//
//           write a function that finds all the duplicates in the array.    //
///////////////////////////////////////////////////////////////////////////////

#include <cstddef>      //size_t
#include <iostream>     //cout
#include <vector>       //vector

using namespace std;

//TODO make a better tests
void TestFindDuplicates();

int main()
{
    TestFindDuplicates();

    return 0;
}

// time complex O(N), memory complex O(N)
std::vector<int> FindDuplicates(const int array[], size_t arrayLen)
{
    int *intsAmount = new int[arrayLen+1];
    const int *endOfArray = array + arrayLen;

    vector<int> duplicates;
    for (const int *i = array; i < endOfArray; ++i)
    {
        if (intsAmount[*i] == 1)
        {
            duplicates.push_back(*i);
        }
        ++intsAmount[*i];
    }

    return duplicates;
}

void TestFindDuplicates()
{
    cout << "TestFindDuplicates : ";

    size_t numOfTests = 0;
    size_t tests = 0;

    int test1[] = {1, 2, 3};
    vector<int> result1;
    tests += (result1 == FindDuplicates(test1, sizeof test1 / sizeof test1[0]));
    ++numOfTests;

    int test2[] = {1, 2, 2};
    vector<int> result2;
    result2.push_back(2);
    tests += (result2 == FindDuplicates(test2, sizeof test2 / sizeof test2[0]));
    ++numOfTests;

    int test3[] = {3, 3, 3};
    vector<int> result3;
    result3.push_back(3);
    tests += (result3 == FindDuplicates(test3, sizeof test3 / sizeof test3[0]));
    ++numOfTests;

    int test4[] = {2, 1, 2, 1};
    vector<int> result4;
    result4.push_back(2);
    result4.push_back(1);
    tests += (result4 == FindDuplicates(test4, sizeof test4 / sizeof test4[0]));
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

