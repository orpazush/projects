/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review :      						                     *
 * 					Last update : 15.9.20									 *
 ****************************************************************************/

#include "reactor.hpp"

#include "demultiplexer.hpp"            //MonitorEvents
#include "logger.hpp"                   //LOG_..

using namespace std;                    //cout

namespace ilrd
{
namespace project
{

namespace reactor_details
{

Demultiplexer::MODE Reac2DemuxMode(Reactor::MODE mode)
{
    switch (mode)
    {
        case Reactor::READ:
            return Demultiplexer::READ;
        case Reactor::WRITE:
            return Demultiplexer::WRITE;
        case Reactor::EXCEPT:
            return Demultiplexer::EXCEPT;
    }
}

}//reactor_details

using namespace reactor_details;

void Reactor::Add(int fd, Reactor::MODE fd_mode, handler_t m_handleFunc)
{
    key_t key(fd, Reac2DemuxMode(fd_mode));
    if (!m_eventHandlerMap.insert(make_pair(key, m_handleFunc)).second)
    {
        LOG_WARNING("handler wasn't inserted because key is already exist");
    } else
    {
        LOG_INFO("handler is added");
        m_keysVector.push_back(key);
    }
}

void Reactor::Remove(int fd, Reactor::MODE fd_mode) noexcept
{
    key_t key(fd, Reac2DemuxMode(fd_mode));
    vector_pair_t::iterator iter;
    iter = find(m_keysVector.begin(), m_keysVector.end(), key);
    if (iter == m_keysVector.end())
    {
        LOG_INFO("requested key to remove is not in m_keysVector");
    } else
    {
        m_keysVector.erase(iter);
        m_eventHandlerMap.erase(key);
        LOG_INFO("handler is removed");
    }
}

void Reactor::Run()
{
    m_stopflag = true;
    Demultiplexer demulty;
    while (m_stopflag)
    {
        vector_pair_t activeHandles = demulty.MonitorEvents(m_keysVector);

        for (vector_pair_t::iterator iter = activeHandles.begin();
             iter != activeHandles.end() && m_stopflag; ++iter)
        {
            map_t::iterator handler = m_eventHandlerMap.find(*iter);
            if (handler == m_eventHandlerMap.end())
            {
                LOG_INFO("handler was removed before been activate");
            } else
            {
                handler->second();
            }
        }
    }
}

void Reactor::Stop() noexcept
{
    m_stopflag = false;
}

}//project
}//ilrd

