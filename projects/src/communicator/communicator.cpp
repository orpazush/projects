/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review : chanan komar     						         *
 * 					Last update : 16.8.20									 *
 ****************************************************************************/
#include <arpa/inet.h>          //inet_pton

#include "ilrd_details.hpp"     //IfErrorPerror

#include "communicator.hpp"

namespace ilrd
{
namespace project
{

using namespace ilrd_details;

/* ---------------------------------Ctor & Dtor----------------------------- */
Communicator::Communicator(int localPort, const char *remoteIp, int remotePort) :
        m_socket(localPort)
{
    LOG_DEBUG("communicator is build");
    SetRemoteAddr(remoteIp, remotePort);
}

/* -------------------------------Public Methods---------------------------- */
RequestPtr Communicator::Receive()
{
    LOG_DEBUG("communicator Received request");
    RequestPtr request = CreateRequestPtr();

    socklen_t len = sizeof(sockaddr_in);
    size_t numOfRedBytes = recvfrom(m_socket.GetFd(), request.get(), REQUEST_SIZE,
                                    MSG_DONTWAIT, reinterpret_cast<sockaddr *>
                                    (&m_remoteAddr), &len);
    IfErrorPerror(numOfRedBytes, "recvfrom");

//    sockaddr_in senderAddr = {0, 0, 0, 0};
//    m_masterAddr = senderAddr;//TODO
//    if (senderAddr.sin_addr.s_addr != m_masterAddr.sin_addr.s_addr
//        || senderAddr.sin_port != m_masterAddr.sin_port)
//    {
//        LOG_INFO("request arrived from unrecognized source");
//        throw (std::domain_error("message is not from domain"));//not sure
//        if necessary
//    }
//
    if (numOfRedBytes < REQUEST_HEADER_SIZE)
    {
        LOG_ERROR("communicator received an incomplete request");
        throw (std::length_error("incomplete request"));
    }
    *request = Ntoh(*request);

    return request;
}

void Communicator::Send(ReplyPtr reply)
{
    LOG_DEBUG("communicator send reply");
    IfErrorPerror(sendto(m_socket.GetFd(), reply.get(),
                         GetReplySize(reply->requestType),  0,
                         reinterpret_cast<const sockaddr *>(&m_remoteAddr),
                         sizeof(m_remoteAddr)), "sendto");
}
int Communicator::GetFD() const
{
    return m_socket.GetFd();
}

/* -------------------------------Private Methods---------------------------- */
void Communicator::SetRemoteAddr(const char *remoteIp, int remotePort)
{
    m_remoteAddr.sin_family = AF_INET;
    inet_pton(AF_INET, remoteIp, &m_remoteAddr.sin_addr.s_addr);
    m_remoteAddr.sin_port = htons(remotePort);
}

}//project
}// namespace ilrd
