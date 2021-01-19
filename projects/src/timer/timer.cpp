/******************************************************************************
 *							CREATED BY: Orpaz                                 *
 *							CREATED ON: 21-09-2020  			 			  *
 *							REVIEWER: 	 					                  *
 ******************************************************************************/

#include <sys/timerfd.h>
#include <boost/bind.hpp>

#include "ilrd_details.hpp"
#include "timer.hpp"

/* (╯°□°）╯︵ ┻━┻ */
namespace ilrd
{
namespace project
{

using namespace ilrd_details;
namespace timer_details
{
static void WrapHandler(const boost::function<void(void)> &eventHandler,
                        int timerFd)
{
    char buf[BUFSIZ];
    IfErrorPerror(read(timerFd, buf, BUFSIZ), "read");
    eventHandler();
}
}//timer_details

using namespace timer_details;

const static int BILION = 1000000000;
const static int MIN_NANO = 5000;

Timer::Timer(Reactor &reactor, const boost::function<void(void)> &eventHandler)
        : m_reactor(reactor), m_eventHandler(eventHandler)
{
    m_timerFd = timerfd_create(CLOCK_MONOTONIC, 0);
    IfErrorPerror(m_timerFd, "timerfd_create");
    boost::function<void(void)> Handler =
            boost::bind(WrapHandler, m_eventHandler, m_timerFd);

    m_reactor.Add(m_timerFd, Reactor::READ, Handler);
}

Timer::~Timer()
{
    m_reactor.Remove(m_timerFd, Reactor::READ);
    close(m_timerFd);
}

void Timer::Arm(Timer::seconds newTimerVal)
{
    struct itimerspec newTime = {{0, 0},
                                 {0, 0}};
    newTime.it_value.tv_sec = newTimerVal.count();

    IfErrorPerror(timerfd_settime(m_timerFd, 0, &newTime, NULL),
                  "timerfd_settime");
}

void Timer::Arm(boost::chrono::time_point<boost::chrono::steady_clock>
                newTimerVal)
{
    boost::chrono::steady_clock::duration nano =
            newTimerVal - boost::chrono::steady_clock::now();

    seconds secs = boost::chrono::duration_cast<seconds>(nano);
    nano -= secs;

    itimerspec new_value = {0, 0, secs.count(), nano.count()};

    if (0 >= new_value.it_value.tv_sec)
    {
        new_value.it_value.tv_sec = 0;
        if (new_value.it_value.tv_nsec <= MIN_NANO)
        {
            new_value.it_value.tv_nsec = MIN_NANO;
        }
    }
    IfErrorPerror(timerfd_settime(m_timerFd, 0, &new_value, 0),
                  "timerfd_settime");
}

void Timer::Disarm()
{
    struct itimerspec timeToStop = {{0, 0},
                                    {0, 0}};

    IfErrorPerror(timerfd_settime(m_timerFd, 0, &timeToStop, 0),
                  "timerfd_settime");
}

Timer::nanoseconds Timer::TimeLeft() const
{
    struct itimerspec currTime = {{0, 0},
                                  {0, 0}};
    IfErrorPerror(timerfd_gettime(m_timerFd, &currTime), "timerfd_gettime");

    nanoseconds timeLeft(
            (currTime.it_value.tv_sec * BILION) + currTime.it_value.tv_nsec);

    return timeLeft;
}

}//project
}//ilrd
