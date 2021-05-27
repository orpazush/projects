//
// Created by orpaz on 02/03/2021.
//

#include <iostream>

void TestDivide();

int main()
{
    TestDivide();

    return 0;
}


int Divide(int divident, int divisor)
{
    if (divisor == 0 || divident == 0)
    {
        return 0;
    }
    bool isNegative = ((divident < 0 && divisor > 0) || (divident > 0 && divisor < 0));

    divident = (0 > divident) ? divident *-1 : divident;
    divisor = (0 > divisor) ? divisor *-1 : divisor;

    int result = 0;

    while (divident >= divisor)
    {
        int num = 0;
        while (divident >= (divisor << num))
        {
            ++num;
        }
        --num;
        divident -= divisor << num;
        result += 1 << num;
    }

    if (isNegative)
    {
        result = 0 - result;
    }

    return result;
}

void TestDivide()
{
    std::cout << "TestDivide : ";

    size_t numOfTests = 0;
    size_t tests = 0;

    tests += (9 == Divide(100, 11));
    ++numOfTests;

    tests += (-9 == Divide(-100, 11));
    ++numOfTests;

    tests += (9 == Divide(-100, -11));
    ++numOfTests;

    tests += (9 == Divide(81, 9));
    ++numOfTests;

    tests += (22 == Divide(1852, 84));
    ++numOfTests;

    tests += (0 == Divide(2, 10));
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