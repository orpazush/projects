
/******************************************************************************
 *                          code by : Orpaz Hout                              *
 *                        review by :                                         *
 *                      coding date - 21-09-2020                              *
 ******************************************************************************/

#ifndef ILRD_RD8788_TIMER_HPP
#define ILRD_RD8788_TIMER_HPP

#include <boost/chrono.hpp>             //itimerspec
#include <boost/function.hpp>           //function
#include <boost/core/noncopyable.hpp>   //noncopyable

#include "reactor.hpp"                  //itimerspec

namespace ilrd
{
namespace project
{

class Timer : private boost::noncopyable
{
public:
    typedef boost::chrono::seconds seconds;
    typedef boost::chrono::nanoseconds nanoseconds;

    explicit Timer(Reactor &reactor,
                   const boost::function<void(void)> &eventHandler);

    ~Timer();

    void Arm(seconds newTimerVal);

    void
    Arm(boost::chrono::time_point<boost::chrono::steady_clock> newTimerVal);

    void Disarm();

    nanoseconds TimeLeft() const;

private:
    Reactor &m_reactor;
    const boost::function<void(void)> m_eventHandler;
    int m_timerFd;
};

}//project
}//ilrd
#endif /* ifdef ILRD_RD8788_TIMER_HPP */

