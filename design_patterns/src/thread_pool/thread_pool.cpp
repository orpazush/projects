/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					Last update : 13.10.20									 *
 ****************************************************************************/

#include <boost/thread.hpp>           //boost::thread
#include <boost/bind.hpp>
#include <iostream>
#include <csignal>                    //sigaction, SIGUSR1..

#include "../../include/logger.hpp"               //LOG_..
#include "thread_pool.hpp"

namespace ilrd
{
namespace project
{

static void InterruptExec(int signal_number);

class BadApple : public ThreadPool::Task//TODO
{
public:
    BadApple();

private:
    void Execute();
};

//NUM_OF_PRIORITIES is the highest priority//TODO
BadApple::BadApple() : ThreadPool::Task(NUM_OF_PRIORITIES)
{
//    empty
}

void BadApple::Execute()
{
    throw (BadApple());
}

////////////////////////////ThreadPool Methods ////////////////////////////////

ThreadPool::ThreadPool(size_t numOfThreads) : m_numOfThreads(numOfThreads),
                                              m_stop(false), m_pause(false)
{
    for (size_t i = 0; i < numOfThreads; ++i)
    {
        boost::thread *newThread = new boost::thread(&ThreadPool::ExecuteTask, this);
        m_threadGroup[newThread->get_id()] = newThread;
    }

    //puts interruption point so when a thread is in the middle of execution it
    //will get immediately to the interruption point and throw
    struct sigaction stopExecution = {0};
    stopExecution.sa_handler = InterruptExec;
    sigaction(SIGUSR1, &stopExecution, 0);
}

ThreadPool::~ThreadPool()
{
    std::cout << "~ThreadPool\n";
    m_stop = true;
    boost::mutex::scoped_lock lock(m_groupLock);

    std::map<boost::thread::id, boost::thread *>::iterator i;
    for(i = m_threadGroup.begin(); i != m_threadGroup.end(); ++i)
    {
        i->second->interrupt();
    }

    for(i = m_threadGroup.begin(); i != m_threadGroup.end(); ++i)
    {
        i->second->join();
    }
    lock.unlock();

    m_threadGroup.clear();
    std::cout << "thread pool is clear\n";
}

void ThreadPool::AddTask(boost::shared_ptr<Task> newTask)
{
    m_taskQueue.Push(newTask);
}

size_t ThreadPool::GetNumOfThreads() const
{
    return (m_numOfThreads);
}

void ThreadPool::SetNumOfThreads(size_t newNumOfThreads)
{
    if (newNumOfThreads > m_numOfThreads)
    {
        boost::mutex::scoped_lock lock(m_groupLock);
        while (m_numOfThreads < newNumOfThreads)
        {
            boost::thread *newThread =
                    new boost::thread(&ThreadPool::ExecuteTask, this);

            m_threadGroup[newThread->get_id()] = newThread;
            ++m_numOfThreads;
        }
    }
    else
    {
        while (m_numOfThreads > newNumOfThreads)
        {
            boost::shared_ptr<BadApple>badApple(new BadApple());
            AddTask(badApple);
            --m_numOfThreads;
        }
    }
}

void ThreadPool::Stop(boost::chrono::milliseconds miliSecToStop)
{
    boost::chrono::steady_clock::time_point timeout
            (boost::chrono::steady_clock::now() + miliSecToStop);
    boost::thread stop(&ThreadPool::StopExecution, this, timeout);
}

void ThreadPool::Pause()
{
    LOG_DEBUG("pause");
    m_pause = true;
}

void ThreadPool::Resume()
{
    LOG_DEBUG("resume now");
    m_pause = false;
    m_ifPause.notify_all();
}

/////////////////////////////////Task Methods//////////////////////////////////
ThreadPool::Task::Task(ThreadPool::Task::priority priority) : m_priority(priority)
{
    //empty
}

bool ThreadPool::Task::operator<(const ThreadPool::Task &other) const noexcept
{
    return (m_priority < other.m_priority);
}

////////////////////////////ThreadPool Private Methods/////////////////////////
//every thread in the ThreadPool is executing this task
void ThreadPool::ExecuteTask()
{
    boost::shared_ptr<Task> task;

    while (!m_stop)//TODO
    {
        try
        {
            boost::unique_lock<boost::mutex> lock(m_tasksLock);
            while (m_pause)
            {
                m_ifPause.wait(lock);
            }
            lock.unlock();
            m_taskQueue.Pop(task);
            task->Execute();
        }
        //case a BadApple is thrown after SetNumOfThreads to smaller amount
        //of threads, to remove the thread
        catch (BadApple&)
        {
            boost::thread::id thisId = boost::this_thread::get_id();
            boost::mutex::scoped_lock lock(m_groupLock);
            m_threadGroup.find(thisId)->second->detach();
            m_threadGroup.erase(thisId);
            lock.unlock();
            LOG_ERROR("thread is removed");//TODO

            return;
        }
        catch (boost::thread_interrupted&)
        {
            LOG_INFO("thread stopped by SIGUSR1");
        }
        catch (std::exception&)
        {
            LOG_ERROR("task failure");//TODO
        }
    }
}

void ThreadPool::StopExecution(boost::chrono::steady_clock::time_point timeOut)
{
    //block until the time to stop arrived
    boost::this_thread::sleep_until(timeOut);

    //acquire the m_tasksLock so.. TODO
    boost::mutex::scoped_lock lockTask(m_tasksLock);

    //clear the m_taskQueue
    LOG_DEBUG("clear tasks\n");
    boost::shared_ptr<Task> garbage(new BadApple());
    AddTask(garbage);

//    while (false != m_taskQueue.Pop(garbage, boost::chrono::nanoseconds(5000)))
    while (false != m_taskQueue.Pop(garbage))
    {
//        empty
    }
    lockTask.unlock();

    boost::mutex::scoped_lock lockGroup(m_groupLock);

    LOG_DEBUG("interrupting all threads\n");
    std::map<boost::thread::id, boost::thread *>::iterator i;
    for(i = m_threadGroup.begin(); i != m_threadGroup.end(); ++i)
    {
        i->second->interrupt();
        pthread_kill(i->second->native_handle(), SIGUSR1);
    }
    lockGroup.unlock();
}

static void InterruptExec(int signal_number)
{
    (void)signal_number;
    boost::this_thread::interruption_point();
}

}//project
}//ilrd
