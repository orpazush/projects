/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review : chanan komar     						         *
 * 					Last update : 16.8.20									 *
 ****************************************************************************/
#ifndef ILRD_RD8788_COMMUNICATOR_HPP
#define ILRD_RD8788_COMMUNICATOR_HPP

#include <cstddef>               // size_t
#include <boost/noncopyable.hpp> // noncopyable

#include "udp_socket.hpp"        //UDPSocket
#include "vdr_protocol.hpp"      //ReplyPtr, RequestPtr..

namespace ilrd
{
namespace project
{

class Communicator : private boost::noncopyable
{
public:
    explicit Communicator(int localPort, const char *remoteIp, int remotePort);
//    ~Communicator();//default

    RequestPtr Receive();
    void Send(ReplyPtr reply);
    int GetFD() const;

private:
    UDPSocket m_socket;
    sockaddr_in m_remoteAddr;

    void SetRemoteAddr(const char *remoteIp, int remotePort);
};//Communicator

}//project
}// namespace ilrd

#endif //ILRD_RD8788_COMMUNICATOR_HPP
