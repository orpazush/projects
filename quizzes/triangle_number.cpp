//
// Created by orpaz on 29/12/2020.
//

#include <cstddef>
#include <algorithm>
#include <iostream>

void TestTriangleNumbers();

int main()
{
    TestTriangleNumbers();

    return 0;
}


size_t TrianglesNumber(size_t numbers[], size_t sizeOfNumbers)
{
    size_t result = 0;
    size_t *endOfNumbers = numbers+sizeOfNumbers;

    std::sort(numbers, endOfNumbers);

    size_t *thirdSide = numbers+2;

    for (size_t *firstSide = numbers;
         thirdSide < endOfNumbers;
         ++firstSide, thirdSide = firstSide+2)
    {
        for (size_t *secondSide = firstSide+1;
             thirdSide < endOfNumbers;
             ++secondSide, thirdSide = secondSide+1)
        {
            size_t sumOfTwo = *firstSide + *secondSide;
            for (thirdSide = secondSide+1;
                 *thirdSide < sumOfTwo && thirdSide < endOfNumbers;
                 ++thirdSide)
            {
                ++result;
            }
        }
    }

    return (result);
}

void TestTriangleNumbers()
{
    std::cout << "TestTriangleNumbers : ";

    size_t numOfTests = 0;
    size_t tests = 0;

    size_t test1[] = {2, 4, 3, 2};
    tests += (3 == TrianglesNumber(test1, sizeof(test1)/sizeof(test1[0])));
    ++numOfTests;

    size_t test2[] = {2, 4, 3, 2, 5, 7, 4, 3, 9, 11, 19, 1};
    tests += (49 == TrianglesNumber(test2, sizeof(test2)/sizeof(test2[0])));
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