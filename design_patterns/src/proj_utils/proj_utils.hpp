/*******************************************************************************
 *                  written by: Izik Avinoam                                   *
 *                  review:                                           *
 *                  Last update: -2020                                    *
 *                  Approve date: -2020                                   *
 *                                                                             *
 *******************************************************************************/
#ifndef ILRD_RD8788_PROJ_UTILS
#define ILRD_RD8788_PROJ_UTILS

#if __cplusplus<201103L
#define noexcept throw()
#define DEFAULT {}
#else
#define DEFAULT =default
#endif

#define UNUSED(x) (x = x)

namespace ilrd
{
namespace project
{

typedef bool (*test_func_t)();
// extra functions
bool PrintsRequested(char toPrint);
void RunTest(const char *test_name, test_func_t test, size_t sleepTime);

// print with colors
void PrintRed(const char *text);
void PrintGreen(const char *text);
void PrintYellow(const char *text);
void PrintBlue(const char *text);
void PrintMagenta(const char *text);
void PrintCyan(const char *text);

// get time in format
void GetTime(char *current_time);



} //namespace project
} //namespace ilrd

#endif // ILRD_RD8788_PROJ_UTILS

