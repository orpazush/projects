//
// Created by orpaz on 07/03/2021.
//

#include <vector>           //vector
#include <algorithm>        //sort
#include <iostream>

using namespace std;

void TestSumThree();

int main()
{
    TestSumThree();

    return 0;
}

struct Triplet
{
    int first;
    int second;
    int third;
};

vector<Triplet>SumThree(int numbers[], size_t numbersSize)
{
    int *endOfNunbers = numbers + numbersSize;
    sort(numbers, endOfNunbers);
    vector<Triplet> result;

    for (int *third = endOfNunbers - 1; third > numbers && 0 < *third; --third)
    {
        int missingNum = 0 - *third;
        int *first = numbers;
        int *second = third - 1;
        while (first < second)
        {
            int sumOfTwo = *first + *second;
            if (sumOfTwo == missingNum)
            {
                Triplet newTriplet = {*first, *second, *third};
                result.push_back(newTriplet);
                --second;
            }
            else if (sumOfTwo < missingNum)
            {
                ++first;
            }
            else
            {
                --second;
            }
        }
    }

    return result;
}

void TestSumThree()
{
    cout << "TestSumThree : ";

    size_t numOfTests = 0;
    size_t tests = 0;

    int test1[] = {-1, 0, 1, 2, -1, -4};
    vector<Triplet> result = SumThree(test1, sizeof(test1)/sizeof(test1[0]));
    tests += (result[1].first == -1);
    ++numOfTests;
    tests += (result[1].second == 0);
    ++numOfTests;
    tests += (result[1].third == 1);
    ++numOfTests;

    tests += (result[0].first == -1);
    ++numOfTests;
    tests += (result[0].second == -1);
    ++numOfTests;
    tests += (result[0].third == 2);
    ++numOfTests;

    if (tests == numOfTests)
    {
        cout << "Success!\n";
    }
    else
    {
        cout << "Failure!\n";
        cout << numOfTests - tests << " tests has been failed\n";
    }

}
