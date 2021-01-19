/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review :  Yana Gorikhovski 						         *
 * 					Last update : 5.10.20									 *
 ****************************************************************************/
#ifndef ILRD_RD8788_SINGLETON_HPP
#define ILRD_RD8788_SINGLETON_HPP

#include <boost/noncopyable.hpp>    // noncopyable
#include <boost/atomic.hpp>         // barrier
#include <stdexcept>                // throw
#include <boost/thread/mutex.hpp>   // mutex

#include "scope_lock.hpp"
#include "../src/logger/logger.hpp"


namespace ilrd
{
namespace project
{

template <typename T>
class Singleton : private boost::noncopyable
{
public:
    static T* GetInstance();
private:
//    Singleton(); //default
//    ~Singleton(); //default
    static void CleanUp();

    static boost::atomic<T*> m_instance;
    static boost::atomic<bool> m_isDestroyed;
    static boost::mutex m_mutex;
};

/* ---------------------------init Static Variable--------------------------- */
template <typename T>
boost::atomic<bool> Singleton<T>::m_isDestroyed(false);

template <typename T>
boost::atomic<T*> Singleton<T>::m_instance;

template <typename T>
boost::mutex Singleton<T>::m_mutex;

/* -------------------------------Static Methods----------------------------- */
template<typename T>
T* Singleton<T>::GetInstance()
{
    T* temp = m_instance/*.load(boost::memory_order_relaxed)*/;
    boost::atomic_thread_fence(boost::memory_order_acquire);
    if (NULL == temp)
    {
        if (false == m_isDestroyed)
        {
            ScopeLock<boost::mutex> s_lock(&m_mutex);

            temp = m_instance/*.load(boost::memory_order_relaxed)*/;
            if (NULL == temp)
            {
                temp = new T;
                boost::atomic_thread_fence(boost::memory_order_release);
                m_instance.store(temp, boost::memory_order_relaxed);
                atexit(CleanUp);
            }
        }
        
        else
        {
            throw std::runtime_error("Instance does not exist");
        }
    }
    return (temp);
}

template <typename T>
void Singleton<T>::CleanUp()
{
    delete m_instance;
    m_instance = 0;
    m_isDestroyed = true;
}

}   //namespace project
}   // namespace ilrd
#endif //ILRD_RD8788_SINGLETON_HPP


