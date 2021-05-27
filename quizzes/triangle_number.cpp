//
// Created by orpaz on 29/12/2020.
//

#include <cstddef>
#include <algorithm>
#include <iostream>

using namespace std;

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

    for (size_t *thirdSide = numbers+2; thirdSide < endOfNumbers; ++thirdSide)
    {
        size_t *firstSide = numbers;
        size_t *secondSide = thirdSide-1;
        while (firstSide < secondSide)
        {
            if ((*firstSide + *secondSide) > *thirdSide)
            {
                result += (secondSide - firstSide);
                --secondSide;
            }
            else
            {
                ++firstSide;
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