/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review : chanan komar     						         *
 * 					Last update : 16.8.20									 *
 ****************************************************************************/
#include <exception>
#include <iostream>     //cout

#include "ood.hpp"

using namespace std;

using namespace ilrd;

int main(int argc, char const *argv[])
{
    if (1 > argc)
    {
        throw (logic_error("no path was specified"));
    }
    Directory dir1(argv[1]);
    dir1.DisplayName();

    return 0;
}
