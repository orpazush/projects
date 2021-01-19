/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review : Chanan Komar      						         *
 * 					Last update : 7.10.20									 *
 ****************************************************************************/
#ifndef __ILRD_RD8788_WAITABLEQUEUE_H__
#define __ILRD_RD8788_WAITABLEQUEUE_H__

#include <queue>                       // queue
#include <boost/noncopyable.hpp>       // noncopyable
#include <boost/chrono.hpp>            // nanoseconds
#include <boost/thread/mutex.hpp>      // boost::mutex
#include <boost/thread/condition.hpp>  // boost::condition

namespace ilrd
{
namespace project
{

template <class T, class Container = std::queue<T> >
class WaitableQueue : private boost::noncopyable
{
public:
//    explicit WaitableQueue() //DEFAULT;
//    ~WaitableQueue() //DEFAULT;

    void Push(const T& data);

    void Pop(T &out);
    bool Pop(T &out, boost::chrono::nanoseconds timeout);

    bool IsEmpty() const;

private:
    Container m_container;
    mutable boost::mutex m_mutex;
    boost::condition_variable m_pushSignal;
};

template<class T, class Container>
void WaitableQueue<T, Container>::Push(const T &data)
{
    boost::unique_lock<boost::mutex> lock(m_mutex);
    m_container.push(data);
    lock.unlock();
    m_pushSignal.notify_one();
}

template<class T, class Container>
void WaitableQueue<T, Container>::Pop(T &out)
{
    boost::unique_lock<boost::mutex> lock(m_mutex);
    while (m_container.empty())
    {
        m_pushSignal.wait(lock);
    }
    out = m_container.front();
    m_container.pop();
}

template<class T, class Container>
bool WaitableQueue<T, Container>::Pop(T &out, boost::chrono::nanoseconds timeout)
{
    boost::unique_lock<boost::mutex> lock(m_mutex);
    boost::chrono::steady_clock::time_point wakeUpTime =
            boost::chrono::steady_clock::now() + timeout;
    while (m_container.empty())
    {
        if (boost::cv_status::timeout == m_pushSignal.wait_until(lock,
                                                                 wakeUpTime))
        {
            return (false);
        }
    }
    out = m_container.front();
    m_container.pop();

    return (true);
}

template<class T, class Container>
bool WaitableQueue<T, Container>::IsEmpty() const
{
    boost::unique_lock<boost::mutex> lock(m_mutex);
    return (m_container.empty());
}

}//project
}//ilrd

#endif // __ILRD_RD8788_WAITABLEQUEUE_H__
