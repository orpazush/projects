/*******************************************************************************
 *                  written by: Izik Avinoam                                   *
 *                  review:                                           *
 *                  Last update: 24-09-2020                                    *
 *                  Approve date: -2020                                   *
 *                                                                             *
 *******************************************************************************/

#include <iostream> // cout
#include <cstdio>   // printf()
#include <unistd.h> // sleep()

#include "proj_utils.hpp"

namespace ilrd
{
namespace project
{

void PrintRed(const char *text)
{
    std::cout << "\033[31m" << text << "\033[0m";
}

void PrintGreen(const char *text)
{
    std::cout << "\033[32m" << text << "\033[0m";
}

void PrintYellow(const char *text)
{
    std::cout << "\033[33m" << text << "\033[0m";
}

void PrintBlue(const char *text)
{
    std::cout << "\033[34m" << text << "\033[0m";
}

void PrintMagenta(const char *text)
{
    std::cout << "\033[35m" << text << "\033[0m";
}

void PrintCyan(const char *text)
{
    std::cout << "\033[36m" << text << "\033[0m";
}

bool PrintsRequested(char toPrint)
{
    return ('y' == toPrint);
}

typedef bool (*test_func_t)();
void RunTest(const char *test_name, test_func_t test, size_t sleepTime)
{
    bool resultOfTest = test();
    printf("%-30s:\t", test_name);
    resultOfTest ? PrintGreen("PASSED\n") : PrintRed("FAILED\n");
    sleep(sleepTime);
}


void GetTime(char *current_time)
{
    time_t rawtime;
    tm *timeinfo = NULL;

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(current_time, 26, "%H:%M:%S %d/%m/%Y ", timeinfo);
}

} //namespace project
} //namespace ilrd
