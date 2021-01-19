//
// Created by orpaz on 12/01/2021.
//

#include <cstddef>
#include <iostream>

//quarters (25 cents), dimes (10 cents), nickels (5
//cents) and pennies (1 cent),

void TestChangeOptions();
void TestRecurChange();

int main()
{
    TestRecurChange();
    TestChangeOptions();

    return 0;
}


size_t ChangeOptions(size_t num)
{
    const size_t QUARTER = 25;
    const size_t DIME = 10;
    const size_t NICKEL = 5;

    size_t result = 0;
    for (size_t quarters = 0; quarters <= num; quarters += QUARTER)
    {
        for (size_t dimes = quarters; dimes <= num; dimes += DIME)
        {
            for (size_t nickles = dimes; nickles <= num; nickles += NICKEL)
            {
                ++result;
            }
        }
    }

    return result;
}

size_t RecurChange(int num, size_t maxCoin = 25)
{
    const size_t QUARTER = 25;
    const size_t DIME = 10;
    const size_t NICKEL = 5;

    int result = 0;

    if (0 > num)
    {
        return 0;
    }

    result += RecurChange((num - QUARTER), QUARTER);
    if (maxCoin >= DIME)
    {
       result += RecurChange((num - DIME), DIME);
    }
    if (maxCoin >= NICKEL)
    {
        result += RecurChange((num - NICKEL), NICKEL);
    }

    return (result + 1);
}

void TestChangeOptions()
{
    std::cout << "TestChangeOptions : ";

    size_t numOfTests = 0;
    size_t testScore = 0;

    testScore += (4 == ChangeOptions(11));
    ++numOfTests;

    testScore += (4 == ChangeOptions(10));
    ++numOfTests;

    testScore += (13 == ChangeOptions(25));
    ++numOfTests;

    testScore += (9 == ChangeOptions(20));
    ++numOfTests;

    testScore += (9 == ChangeOptions(22));
    ++numOfTests;

    testScore += (2 == ChangeOptions(5));
    ++numOfTests;
//
//    std::cout << ChangeOptions(25) << std::endl;
//    std::cout << ChangeOptions(50) << std::endl;
//    std::cout << ChangeOptions(75) << std::endl;

    if (testScore == numOfTests)
    {
        std::cout << "Success!\n";
        std::cout << numOfTests << " tests has been succeed\n";
    }
    else
    {
        std::cout << "Failure!\n";
        std::cout << numOfTests - testScore << " tests has been failed\n";
    }

}

void TestRecurChange()
{
    std::cout << "TestRecurChange : ";

    size_t numOfTests = 0;
    size_t testScore = 0;

    testScore += (4 == RecurChange(11));
    ++numOfTests;

    testScore += (4 == RecurChange(10));
    ++numOfTests;

    testScore += (13 == RecurChange(25));
    ++numOfTests;

    testScore += (9 == RecurChange(20));
    ++numOfTests;

    testScore += (9 == RecurChange(22));
    ++numOfTests;

    testScore += (2 == RecurChange(5));
    ++numOfTests;

    if (testScore == numOfTests)
    {
        std::cout << "Success!\n";
        std::cout << numOfTests << " tests has been succeed\n";
    }
    else
    {
        std::cout << "Failure!\n";
        std::cout << numOfTests - testScore << " tests has been failed\n";
    }

}
