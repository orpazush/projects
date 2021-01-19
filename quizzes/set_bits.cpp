//
// Created by orpaz on 15/12/2020.
//
#include <iostream>

using namespace std;

bool IsBitsSetInRow(int number)
{
    return (number & (number >> 1));
}

int main()
{
    int tests = 0;

    tests += !IsBitsSetInRow(1);
    tests += !IsBitsSetInRow(2);
    tests += !IsBitsSetInRow(4);
    tests += !IsBitsSetInRow(5);
    tests += !IsBitsSetInRow(32);

    tests += IsBitsSetInRow(3);
    tests += IsBitsSetInRow(6);
    tests += IsBitsSetInRow(7);
    tests += IsBitsSetInRow(31);
    tests += IsBitsSetInRow(-31);
    tests += IsBitsSetInRow(-64);

    if (tests == 11)
    {
        cout << "Success!\n";
    } else
    {
        cout << "Fail\n";
    }
    return 0;
}
