#include <iostream>
#include "logger.hpp"

using namespace std;

int main()
{
    LOG_DEBUG("1");
    LOG_INFO("2");
    LOG_WARNING("3");
    LOG_ERROR("4");

    return 0;
}
