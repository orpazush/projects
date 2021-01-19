//
// Created by orpaz on 02/11/2020.
//

#include <iostream>
#include <cstdio>

using namespace std;

void FindTwoPower(size_t number)
{
    int *toPrint = new int[(number / 3) + 1];
    toPrint[0] = 1;
    size_t length = 1;
    int Double = 0;
    size_t remain = 0;

    for (size_t i = 0; i < number; ++i)
    {
        for (size_t j = 0; j < length; ++j)
        {
            Double = (toPrint[j] * 2) + remain;
            toPrint[j] = (Double % 10);
            remain = (Double / 10);
        }
        if (Double / 10)
        {
            ++toPrint[length];
            ++length;
            remain = 0;
        }
    }

    while (length)
    {
        cout << toPrint[length - 1];
        --length;
    }
    cout << endl;
}

int main()
{
    FindTwoPower(2000);

    return 0;
}