/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review :      						                     *
 * 					Last update : 15.9.20									 *
 ****************************************************************************/

#ifndef ILRD_RD8788_REACTOR_HPP
#define ILRD_RD8788_REACTOR_HPP

#include <vector>                       //vector
#include <map>                          //map
#include <boost/core/noncopyable.hpp>   //noncopyable
#include <boost/function.hpp>           //boost::function
#include "ilrd_details.hpp"             //noexcept

#include "demultiplexer.hpp"

namespace ilrd
{
namespace project
{

namespace reactor_details
{
typedef std::pair<int, Demultiplexer::MODE> key_t;
typedef std::vector<key_t> vector_pair_t;
typedef boost::function<void(void)> handler_t;
typedef std::map<key_t, handler_t> map_t;
} //reactor_details

class Reactor : private boost::noncopyable
{
public:
    enum MODE
    {
        READ,
        WRITE,
        EXCEPT
    };
//    explicit Reactor();// default
//    ~Reactor();        //default

    void Add(int fd, MODE fd_mode, reactor_details::handler_t m_handleFunc);
    void Remove(int fd, MODE fd_mode) noexcept;
    void Run();
    void Stop() noexcept;

private:
    reactor_details::map_t m_eventHandlerMap;
    reactor_details::vector_pair_t m_keysVector;
    bool m_stopflag;

    void activateHandler();
}; //Reactor

} //project
} //ilrd

#endif /* ifdef ILRD_RD8788_REACTOR_HPP */
