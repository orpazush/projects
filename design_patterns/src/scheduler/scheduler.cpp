/******************************************************************************
 *                          code by : Orpaz Houta                             *
 *                        review by :                                         *
 *                      coding date - 22-09-2020                              *
 ******************************************************************************/

#include <boost/bind.hpp>           //bind

#include "logger.hpp"               //LOG_..

#include "scheduler.hpp"

namespace ilrd
{
namespace project
{

Scheduler::Scheduler(Reactor &reactor) :
        m_timer(reactor, boost::bind(&Scheduler::ActivateNextTask, this))
{
    LOG_DEBUG("Scheduler is created");
}

void Scheduler::Add(func_t func, time_point_t activationTime,
                    Timer::nanoseconds interval)
{
    Task newTask(func, interval, activationTime);
    m_tasks.push(newTask);
    if (m_tasks.top().GetActivationTime() >= activationTime)
    {
        m_timer.Arm(activationTime);
    }
    LOG_DEBUG("new task added to Scheduler");
}

void Scheduler::Add(func_t func, time_point_t activationTime)
{
    Add(func, activationTime, Timer::nanoseconds(0));
}

void Scheduler::Clear() noexcept
{
    m_timer.Disarm();

    while (!m_tasks.empty())
    {
        m_tasks.pop();
    }
    LOG_DEBUG("Scheduler is clear now");
}

void Scheduler::ActivateNextTask()
{
    Task currTask(m_tasks.top());
    currTask.Execute();
    m_tasks.pop();

    if (Timer::nanoseconds(0) != currTask.GetInterval())
    {
        currTask.SetActivationTime();
        m_tasks.push(currTask);
    }

    if (!m_tasks.empty())
    {
        m_timer.Arm(m_tasks.top().GetActivationTime());
    }
}

Scheduler::Task::Task(func_t func, Timer::nanoseconds interval,
                      time_point_t m_nextActivationTime) :
        m_func(func), m_interval(interval),
        m_nextActivationTime(m_nextActivationTime)
{
    //empty
}

Scheduler::time_point_t Scheduler::Task::GetActivationTime() const noexcept
{
    return (m_nextActivationTime);
}

Timer::nanoseconds Scheduler::Task::GetInterval() const noexcept
{
    return (m_interval);
}

void Scheduler::Task::SetActivationTime()
{
    m_nextActivationTime = (m_interval + boost::chrono::steady_clock::now());
}

void Scheduler::Task::Execute()
{
    m_func();
}

bool Scheduler::Task::operator<(const Task &other) const
{
    return (m_nextActivationTime > other.m_nextActivationTime);
}

}//project
}//namespace ilrd