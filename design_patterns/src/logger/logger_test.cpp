/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review : Gil Steinberg     						         *
 * 					Last update : 7.10.20									 *
 ****************************************************************************/

#include <iostream>
#include "logger.hpp"

using namespace ilrd;
using namespace project;
using namespace std;

int main()
{
    cout << "test" << endl;
    Singleton<Logger>::GetInstance()->Log("wow", Logger::INFO);
    sleep(2);
    Singleton<Logger>::GetInstance()->Log("it's working", Logger::INFO);

    LOG_DEBUG("debug");
    LOG_ERROR("error");
    LOG_WARNING("warning");
    LOG_INFO("info");

    Singleton<Logger>::GetInstance()->SetLevel(Logger::WARNING);

    LOG_DEBUG("debug");
    LOG_ERROR("error");
    LOG_WARNING("warning");
    LOG_INFO("info");

    return 0;
}
