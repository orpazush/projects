/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review :     						         *
 * 					Last update : 3.9.20									 *
 ****************************************************************************/
#ifndef ILRD_RD8788_SHARED_PTR_HPP
#define ILRD_RD8788_SHARED_PTR_HPP

#include  <cstddef> //size_t


namespace ilrd
{

template<typename T1>
class SharedPtr
{
public:
    explicit SharedPtr(T1 *p = NULL);
    ~SharedPtr();
    SharedPtr(const SharedPtr<T1> &other);
    template<typename T2>
    SharedPtr(const SharedPtr<T2> &other);
    SharedPtr<T1> &operator=(const SharedPtr<T1> &other);
    template<typename T2>
    SharedPtr<T1> &operator=(const SharedPtr<T2> &other);
    T1 &operator*() const;
    T1 *operator->() const;

private:
    template<typename> friend class SharedPtr;
    template<typename T2>
    void Swap(SharedPtr<T2> &other);
    T1 *m_ptr;
    size_t *m_counter;
};

template<typename T1>
SharedPtr<T1>::SharedPtr(T1 *p) : m_ptr(p), m_counter(new size_t(0))
{
    // empty
}

template<typename T1>
SharedPtr<T1>::~SharedPtr()
{
    if (0 < *m_counter)
    {
        --*m_counter;
    }
    else
    {
        delete m_ptr;
        delete m_counter;
        m_ptr = 0;
        m_counter = 0;
    }
}

template<typename T1>
SharedPtr<T1>::SharedPtr(const SharedPtr<T1> &other) : m_ptr(other.m_ptr),
                                                    m_counter(other.m_counter)
{
    ++(*m_counter);
}

template<typename T1>
template<typename T2>
SharedPtr<T1>::SharedPtr(const SharedPtr<T2> &other) : m_ptr(other.m_ptr),
                                                    m_counter(other.m_counter)
{
    ++(*m_counter);
}

template<typename T1>
SharedPtr<T1> &SharedPtr<T1>::operator=(const SharedPtr<T1> &other)
{
    SharedPtr<T1> tmp(other);
    Swap(tmp);

    return (*this);
}

template<typename T1>
template<typename T2>
SharedPtr<T1> &SharedPtr<T1>::operator=(const SharedPtr<T2> &other)
{
    SharedPtr<T2> tmp(other);
    Swap(tmp);

    return (*this);
}

template<typename T1>
T1 &SharedPtr<T1>::operator*() const
{
    return (*m_ptr);
}

template<typename T1>
T1 *SharedPtr<T1>::operator->() const
{
    return (m_ptr);
}

template<typename T1>
template<typename T2>
void SharedPtr<T1>::Swap(SharedPtr<T2> &other)
{
    T1 *temp = m_ptr;
    m_ptr = reinterpret_cast<T1 *>(other.m_ptr);
    other.m_ptr = temp;

    size_t *temp_counter = m_counter;
    m_counter = other.m_counter;
    other.m_counter = temp_counter;

} // namespace ilrd
}
#endif //ifdef ILRD_RD8788_SHARED_PTR_HPP
