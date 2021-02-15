/******************************************************************************
*						CREATED BY:	                     	      *
*						CREATED ON: 01/09/2020               			      *
*				   		REVIEWER:          				  *
******************************************************************************/

#include <boost/thread/mutex.hpp>
#include <boost/thread.hpp>
#include <iostream>
#include <exception>

#include "scope_lock.hpp"

using namespace ilrd;
using namespace boost;

mutex gs_locker;

void CountWithoutLock()
{
    for (size_t i = 0; i < 100; ++i)
    {
        std::cout << i << " ";
    }
    std::cout << "\n";
}

void CountWithLock()
{
    ScopeLock <mutex> blockGuard(&gs_locker);
    for (size_t i = 0; i < 100; ++i)
    {
        std::cout << i << " ";
//        if (i == 30)
//        {
//            throw std::runtime_error("reach 30");
//        }
    }
    std::cout << "\n";
}

int main()
{
    std::cout << "3 threads counting to 30 without Scopelock\n";
    thread thread1(CountWithoutLock), thread2(CountWithoutLock),
            thread3(CountWithoutLock);

    thread1.join();
    thread2.join();
    thread3.join();

    try
    {
        std::cout << "now the threads using Scopelock\n";
        thread thread4(CountWithLock), thread5(CountWithLock),
                thread6(CountWithLock);

        thread4.join();
        thread5.join();
        thread6.join();
    }

    catch (std::exception&)
    {
        std::cout << "exep\n";
        sleep(10);
        ;
    }

    return 0;
}

