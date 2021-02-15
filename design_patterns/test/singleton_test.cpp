/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review :  Yana Gorikhovski 						         *
 * 					Last update : 5.10.20									 *
 ****************************************************************************/

#include <iostream>

#include <boost/thread/mutex.hpp>
#include <boost/thread.hpp>

#include "singleton.hpp"

using namespace ilrd::project;
using namespace std;

using boost::mutex;
using boost::thread;

void ThreadTest(int start, int end);

class GetInstanceAfterDeleteChecker
{
public:
    ~GetInstanceAfterDeleteChecker();
};

GetInstanceAfterDeleteChecker::~GetInstanceAfterDeleteChecker()
{
    try
    {
        Singleton<int>::GetInstance();
    }
    catch (std::runtime_error &r)
    {
        std::cout << r.what() << std::endl;
        if(strcmp(r.what(), "GetInstance after Delete"))
        {
            std::cout << "FAILURE" << std::endl;
        }
        else
        {
            std::cout << "SUCCESS" << std::endl;
        }
    }
}

/* ------------------------------------------------------------------------- */

int *g_ptr = Singleton<int>::GetInstance();
int *g_ptr1 = Singleton<int>::GetInstance();
GetInstanceAfterDeleteChecker check_destruction;

/* ------------------------------------------------------------------------- */

int main()
{
    thread thread1(ThreadTest, 0, 50);
    thread thread2(ThreadTest, 50, 100);
    thread thread3(ThreadTest, 100, 150);
    thread thread4(ThreadTest, 150, 200);

    fork();
    fork();
    thread1.join();
    thread2.join();
    thread3.join();
    thread4.join();

    cout << "end of test" << endl;
    return 0;
}

/* ------------------------------------------------------------------------- */

void ThreadTest(int start, int end)
{
    for (int i = start; i < end; ++i)
    {
        int *ptr = Singleton<int>::GetInstance();
        *ptr = i;
        if ((ptr != g_ptr) || (ptr != g_ptr1))
        {
            cout << "not the same address" << endl;
        }
    }
}