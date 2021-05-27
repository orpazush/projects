//
// Created by orpaz on 23/02/2021.
//

#include <cstddef>
#include <iostream>

void TestCutRod();


int main()
{
    TestCutRod();

    return 0;
}


int CutRod(int prices[], int rodLength)
{
    int *max_prices = new int[rodLength];
    int left = 0;
    int right = 0;

    for (int i = 0; i < rodLength; ++i)
    {
        max_prices[i] = prices[i];
        for (left = 0, right = i-1; left <= right; ++left, --right)
        {
            int currPrice = max_prices[left]+max_prices[right];
            if (currPrice > max_prices[i])
            {
                max_prices[i] = currPrice;
            }
        }
    }

    return max_prices[rodLength-1];
}

void TestCutRod()
{
    std::cout << "TestCutRod : ";

    size_t tests = 0;
    size_t numOfTests = 0;

    int prices1[] = {1, 5, 8, 9, 10, 17, 17, 20};
    int prices2[] = {3, 5, 8, 9, 10, 17, 17, 20};

    tests += (22 == CutRod(prices1, (sizeof(prices1)/sizeof(prices1[0]))));
    ++numOfTests;

    tests += (24 == CutRod(prices2, (sizeof(prices2)/sizeof(prices2[0]))));
    ++numOfTests;

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
