/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review :      						         *
 * 					Last update : 21.10.20									 *
 ****************************************************************************/
#ifndef ILRD_RD8788_DISPATCHER_HPP
#define ILRD_RD8788_DISPATCHER_HPP

#include <boost/noncopyable.hpp>    // noncopyable
#include <vector>                   // vector

namespace ilrd
{
namespace project
{


template <typename MESSAGE>
class Dispatcher : boost::noncopyable
{
public:
    explicit Dispatcher();
    ~Dispatcher();

    void NotifyAll(const MESSAGE &msg);

    class Listener
    {
    public:
        explicit Listener(Dispatcher &dispatcher);
        virtual ~Listener();

    private:
        friend class Dispatcher<MESSAGE>;

        virtual void AcceptMessage(const MESSAGE &msg)=0;
        void DetachDispatcher();
        virtual void ExtendDetachDispatcher();

        Dispatcher<MESSAGE> &m_dispatcher;
    };

private:
    void Add(Listener *listener);
    void Remove(const Listener *listener);

    std::vector<Listener*> m_listeners;
};//Dispatcher

template<typename MESSAGE>
Dispatcher<MESSAGE>::Listener::Listener(Dispatcher &dispatcher) :
        m_dispatcher(dispatcher)
{
    m_dispatcher.Add(this);
}

template<typename MESSAGE>
Dispatcher<MESSAGE>::Listener::~Listener()
{
    DetachDispatcher();
    m_dispatcher.Remove(this);
}

template<typename MESSAGE>
void Dispatcher<MESSAGE>::Listener::DetachDispatcher()
{
    ExtendDetachDispatcher();
}

template<typename MESSAGE>
void Dispatcher<MESSAGE>::Listener::ExtendDetachDispatcher()
{
//    empty
}

template<typename MESSAGE>
Dispatcher<MESSAGE>::~Dispatcher()
{
    typename std::vector<Listener*>::iterator i;
    for (i = m_listeners.begin(); i != m_listeners.end(); ++i)
    {
        *i->DetachDispatcher();
    }

    m_listeners.clear();
}

template<typename MESSAGE>
void Dispatcher<MESSAGE>::Add(Dispatcher::Listener *listener)
{
    m_listeners.push_back(listener);
}

template<typename MESSAGE>
void Dispatcher<MESSAGE>::Remove(const Dispatcher::Listener *listener)
{
    typename std::vector<Listener*>::iterator i;
    for (i = m_listeners.begin(); i != m_listeners.end(); ++i)
    {
        if (*i == listener)
        {
            m_listeners.insert(i, m_listeners.back());
            m_listeners.pop_back();
            return;
        }
    }
}

template<typename MESSAGE>
void Dispatcher<MESSAGE>::NotifyAll(const MESSAGE &msg)
{
    typename std::vector<Listener*>::iterator i;
    for (i = m_listeners.begin(); i != m_listeners.end(); ++i)
    {
        *i->AcceptMessage(msg);
    }
}

template<typename MESSAGE>
Dispatcher<MESSAGE>::Dispatcher()
{
//empty
}


} // namespace project
} // namespace ilrd


#endif //ILRD_RD8788_DISPATCHER_HPP
