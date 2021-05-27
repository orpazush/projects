//
// Created by orpaz on 02/03/2021.
//

#include <iostream>         //cout

using namespace std;

void TestMultiply();

int main()
{
    TestMultiply();
    
    return 0;
}


int Multiply(int num1, int num2)
{
    const int MASK = 1;
    bool isNegative = ((num1 < 0 && num2 > 0) || (num1 > 0 && num2 < 0));

    num1 = (0 > num1) ? 0 - num1 : num1;
    num2 = (0 > num2) ? 0 - num2 : num2;

    int result = 0;

    if (num2 > num1)
    {
        std::swap(num1, num2);
    }

    while (num2)
    {
        if (num2 & MASK)
        {
            result += num1;
        }
        num1 <<= 1;
        num2 >>= 1;
    }

    if (isNegative)
    {
        result = 0 - result;
    }

    return result;
}

bool TestMulty(int num1, int num2)
{
    return ((num1 * num2) == (Multiply(num1, num2)));
}

void TestMultiply()
{
    std::cout << "TestMultiply : ";

    size_t numOfTests = 20;
    size_t tests = 0;

    for (size_t i = 0; i < numOfTests; ++i)
    {
        int num1 = rand();
        int num2 = rand();
        tests += TestMulty(num1, num2);
    }

    tests += (-900 == Multiply(-100, 9));
    ++numOfTests;

    tests += (-900 == Multiply(100, -9));
    ++numOfTests;

    tests += (900 == Multiply(-100, -9));
    ++numOfTests;

    tests += ((22 * 84) == Multiply(22, 84));
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