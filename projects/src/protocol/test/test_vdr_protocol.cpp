#include <iostream>
#include <string>

#include <cassert>

#include "vdr_protocol.hpp"

#define expect(x) if (!(x)) {return false;}

using std::cout;
using std::endl;
using namespace ilrd;

bool success = true;

inline void RUN_TEST(bool test, const char* test_name)
{
    if (!test) {
        cout << test_name << ": " << "\33[1;31m" << "FAILURE" << "\33[0m" << endl;
        success = false;
    }
}

bool Test1(void)
{


    return (true);
}

int main(void)
{
    RUN_TEST(Test1(), "");

    if (success) {
        cout << "\33[32;1m" << "SUCCESS" << "\33[0m" << endl;
    }

    return (0);
}
