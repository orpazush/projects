/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review : 									 *
 * 					Last update : 27.8.20									 *
 ****************************************************************************/

#ifndef TCP_UDP_TCP_UDP_UTILS_HPP
#define TCP_UDP_TCP_UDP_UTILS_HPP

#include <iostream>
#include <cstdio>

enum tcp_status {ERROR = -1, SUCCESS, FAILURE};

inline void IfErrorPerror(int to_check, const char *msg)
{
    if (ERROR == to_check)
    {
        perror(msg);
        throw(std::runtime_error("msg"));
    }
}

int CreateTCPSocket();
int CreateUDPSocket();
void SetSockAddr(struct sockaddr_in *Address, uint16_t port, in_addr_t address = INADDR_ANY);
int BindSocket(int socketFd, struct sockaddr_in serverAddress);
void RecMsg(int socketFd, struct sockaddr *clientAddress, socklen_t *sinSize);
void RecMsg(int socketFd);
void SendToMsg(int socketFd, const char *msg, size_t msgSize, struct sockaddr *clientAddress, socklen_t sinSize);
void SendToMsg(int socketFd, const char *msg, size_t msgSize);

#endif //TCP_UDP_TCP_UDP_UTILS_HPP
