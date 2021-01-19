//
// Created by orpaz on 30/12/2020.
//

#include <cstddef>
#include <cstring>
#include <iostream>

void TestBinaryStringToInt();

int main()
{
    TestBinaryStringToInt();

    return 0;
}


int BinaryStringToInt(const char *string)
{
    size_t stringLen = strlen(string);
    const char *endOfString = string + stringLen;
    int result = 0;
    for (const char *i = string; i < endOfString; ++i)
    {
        int currentBit = *i - '0';
        result *= 2;
        result += currentBit;
    }

    return result;
}

void TestBinaryStringToInt()
{
    std::cout << "TestBinaryStringToInt : ";

    size_t numOfTests = 0;
    size_t tests = 0;

    tests += (5 == BinaryStringToInt("101"));
    ++numOfTests;

    tests += (49 == BinaryStringToInt("110001"));
    ++numOfTests;

    tests += (1013 == BinaryStringToInt("1111110101"));
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