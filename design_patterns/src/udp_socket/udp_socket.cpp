/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review :      						         *
 * 					Last update : 16.8.20									 *
 ****************************************************************************/
#include <sys/socket.h>
#include <netinet/in.h>             //INADDR_ANY

#include "ilrd_details.hpp"         //IfErrorPerror

#include "udp_socket.hpp"

namespace ilrd
{
namespace project
{

using namespace ilrd_details;
UDPSocket::UDPSocket(int port) :
        m_fdSocket(socket(AF_INET, SOCK_DGRAM, 0))
{
    LOG_DEBUG("UDPSocket is build");

    IfErrorPerror(m_fdSocket, "socket");
    const sockaddr_in sockAddrIn = {AF_INET, htons(port), INADDR_ANY, 0};
    IfErrorPerror(bind(m_fdSocket, reinterpret_cast<const sockaddr *>
    (&sockAddrIn), sizeof(sockAddrIn)), "bind");
}

UDPSocket::~UDPSocket()
{
    close(m_fdSocket);
}

int UDPSocket::GetFd() const
{
    return (m_fdSocket);
}

}//project
}//ilrd