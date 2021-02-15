/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review : chanan komar     						         *
 * 					Last update : 16.8.20									 *
 ****************************************************************************/

#ifndef ILRD_RD8788_UDP_SOCKET_HPP
#define ILRD_RD8788_UDP_SOCKET_HPP

#include <boost/noncopyable.hpp>    // noncopyable

namespace ilrd
{
namespace project
{
class UDPSocket : private boost::noncopyable
{
public:
    explicit UDPSocket(int port);
    ~UDPSocket();

    int GetFd() const;

private:
    int m_fdSocket;
};

}//project
}//ilrd

#endif //ILRD_RD8788_UDP_SOCKET_HPP