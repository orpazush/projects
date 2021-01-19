/******************************************************************************
 *                          code by : Orpaz Houta                             *
 *                        review by :                                         *
 *                      coding date - 22-09-2020                              *
 ******************************************************************************/

#ifndef ILRD_RD8788_SCHEDULER_HPP
#define ILRD_RD8788_SCHEDULER_HPP

#include <boost/chrono.hpp>            // steady_clock, time_point, nanoseconds
#include <boost/core/noncopyable.hpp>  // boost::noncopyable
#include <boost/function.hpp>          // boost::function
#include <queue>                       // priority_queue

#include "timer.hpp"                   // Timer
#include "ilrd_details.hpp"            // noexcept

namespace ilrd
{
namespace project
{


class Scheduler : private boost::noncopyable
{
public:
    typedef boost::chrono::steady_clock::time_point time_point_t;
    typedef boost::function<void(void)> func_t;

    explicit Scheduler(Reactor &reactor);
//    ~Scheduler(); //default

    void Add(func_t func, time_point_t activationTime,
             Timer::nanoseconds interval);
    void Add(func_t func, time_point_t activationTime);
    void Clear() noexcept;

private:
    class Task
    {
    public:
        explicit Task(func_t func, Timer::nanoseconds interval,
                      time_point_t nextActivationTime);
//        ~Task(); //default

        time_point_t GetActivationTime() const noexcept;
        void SetActivationTime();
        Timer::nanoseconds GetInterval() const noexcept;
        void Execute();
        bool operator<(const Task &other) const;

    private:
        func_t m_func;
        Timer::nanoseconds m_interval;
        time_point_t m_nextActivationTime;
    };//class Task

    void ActivateNextTask();

    Timer m_timer;
    std::priority_queue<Task> m_tasks;
};


}//project
}//namespace ilrd

#endif /* ifdef ILRD_RD8788_SCHEDULER_HPP */
