/******************************************************************************
*						CREATED BY:	                     	      *
*						CREATED ON: 01/09/2020               			      *
*				   		REVIEWER:          				  *
******************************************************************************/
#ifndef ILRD_RD8788_SCOPE_LOCK_HPP
#define ILRD_RD8788_SCOPE_LOCK_HPP

#include <boost/core/noncopyable.hpp>

namespace ilrd
{
template <typename T>
class ScopeLock : private boost::noncopyable
{
public:
    explicit ScopeLock(T *lock);
    ~ScopeLock();

private:
    T *m_lock;
};

template<typename T>
ScopeLock<T>::ScopeLock(T *lock) : m_lock(lock)
{
    m_lock->lock();
}

template<typename T>
ScopeLock<T>::~ScopeLock()
{
    m_lock->unlock();
}

} // namespace ilrd

#endif // ILRD_RD8788_SCOPE_LOCK_HPP__