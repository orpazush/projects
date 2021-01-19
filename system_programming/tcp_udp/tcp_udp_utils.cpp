/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review : 									 *
 * 					Last update : 27.8.20									 *
 ****************************************************************************/

#include <sys/socket.h>
#include <netinet/in.h>

#include "tcp_udp_utils.hpp"

int CreateTCPSocket()
{
    int socketFd = socket(AF_INET, SOCK_STREAM, 0);
    IfErrorPerror(socketFd, "socket");

    return socketFd;
}

int CreateUDPSocket()
{
    int socketFd = socket(AF_INET, SOCK_DGRAM, 0);
    IfErrorPerror(socketFd, "socket");

    return socketFd;
}

void SetSockAddr(struct sockaddr_in *Address, uint16_t port, in_addr_t address)
{
    Address->sin_family = AF_INET;
    Address->sin_port = htons(port);
    Address->sin_addr.s_addr = address;
}

int BindSocket(int socketFd, struct sockaddr_in serverAddress)
{
    int ret = bind(socketFd, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
    IfErrorPerror(ret, "bind");

    return SUCCESS;
}

void RecMsg(int socketFd, struct sockaddr *clientAddress, socklen_t *sinSize)
{
    char buffer[BUFSIZ];

    int recMsg = recvfrom(socketFd, buffer, sizeof(buffer), 0, clientAddress, sinSize);
    IfErrorPerror(recMsg, "recvfrom");

    std::cout << buffer << std::endl;
}

void RecMsg(int socketFd)
{
    char buffer[BUFSIZ];

    int recMsg = recv(socketFd, buffer, BUFSIZ, 0);
    IfErrorPerror(recMsg, "recv");

    std::cout << buffer << std::endl;
}

void SendToMsg(int socketFd, const char *msg, size_t msgSize, struct sockaddr *clientAddress, socklen_t sinSize)
{
    int ret = sendto(socketFd, msg, msgSize, 0, clientAddress, sinSize);
    IfErrorPerror(ret, "sendto");
}


void SendToMsg(int socketFd, const char *msg, size_t msgSize)
{
    int ret = send(socketFd, msg, msgSize, 0);
    IfErrorPerror(ret, "sendto");
}

