/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review :      						         *
 * 					Last update : 16.8.20									 *
 ****************************************************************************/
#ifndef ILRD_RD8788_THREAD_POOL_HPP
#define ILRD_RD8788_THREAD_POOL_HPP

#if __cplusplus<201103L
#define noexcept throw()
#endif

#include <boost/noncopyable.hpp>
#include <boost/thread.hpp>

#include "waitable_queue.hpp"       //WaitableQueue
#include "p_queue_adapter.hpp"      //PQueueAdapter

namespace ilrd
{
namespace project
{

class ThreadPool: boost::noncopyable
{
public:
    explicit ThreadPool(size_t numOfThreads);
    ~ThreadPool();

    class Task
    {
    public:
        enum priority
        {
            LOW,
            MEDIUM,
            HIGH,
            NUM_OF_PRIORITIES
        };

        explicit Task(priority prio = MEDIUM);
//        virtual ~Task();//default

        bool operator<(const Task &other) const noexcept;
//        void operator()() {};

    private:
        friend class ThreadPool;
        virtual void Execute() =0;
        priority m_priority;
    };

    void AddTask(boost::shared_ptr<Task> newTask);
    void Stop(boost::chrono::milliseconds miliSecToStop);
    void Pause();
    void Resume();
    void SetNumOfThreads(size_t newNumOfThreads);
    size_t GetNumOfThreads() const;

private:
    WaitableQueue<boost::shared_ptr<Task>,
            PQueueAdapter<boost::shared_ptr<Task> > > m_taskQueue;
    std::map<boost::thread::id, boost::thread *> m_threadGroup;
    boost::condition_variable m_ifPause;
    boost::mutex m_groupLock;
    boost::mutex m_TasksLock;
    size_t m_numOfThreads;
    bool m_stop;
    bool m_pause;

    void ExecuteTask();
    void StopExecution(boost::chrono::steady_clock::time_point timeOut);
};


}
} //namespace ilrd
#endif /* ifdef ILRD_RD8788_THREAD_POOL_HPP */