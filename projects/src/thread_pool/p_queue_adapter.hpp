/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review :      						         *
 * 					Last update : 16.8.20									 *
 ****************************************************************************/
#ifndef ILRD_RD8788_P_QUEUE_ADAPTER_HPP
#define ILRD_RD8788_P_QUEUE_ADAPTER_HPP

#include <queue>                //priority_queue
#include "p_queue_adapter.hpp"

namespace ilrd
{
namespace project
{

template<typename T>
class PQueueAdapter
{
public:
//    PQueueAdapter();
//    ~PQueueAdapter();

    const T &front() const;
    void push(const T &);
    void pop();
    bool empty() const;

private:
    std::priority_queue <T> m_container;
};

template<typename T>
const T &PQueueAdapter<T>::front() const
{
    return m_container.top();
}

template<typename T>
void PQueueAdapter<T>::push(const T &toPush)
{
    m_container.push(toPush);
}

template<typename T>
void PQueueAdapter<T>::pop()
{
    m_container.pop();
}

template<typename T>
bool PQueueAdapter<T>::empty() const
{
    return m_container.empty();
}
//PQueueAdapter


}//project
}//ilrd

#endif //ILRD_RD8788_P_QUEUE_ADAPTER_HPP

