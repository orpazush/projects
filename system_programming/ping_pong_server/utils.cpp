/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review : Elimelech  									 *
 * 					Last update : 27.8.20									 *
 ****************************************************************************/

#include <sys/socket.h>
#include <cstring>
#include <unistd.h>

#include "utils.hpp"

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

int RecMsg(int socketFd, int flag, struct sockaddr *clientAddress, socklen_t *sinSize)
{
    char buffer[BUFSIZ];

    int recMsg = recvfrom(socketFd, buffer, sizeof(buffer), flag, clientAddress, sinSize);
    IfErrorPerror(recMsg, "recvfrom");
    if (!recMsg)
    {
        close(socketFd);
        return 1;
    }
    else
    {
        std::cout << buffer << std::endl;
        return 0;
    }
}

void SendToMsg(int socketFd, const char *msg, size_t msgSize, int flag, struct sockaddr *clientAddress, socklen_t sinSize)
{
    int ret = sendto(socketFd, msg, msgSize, flag, clientAddress, sinSize);
    IfErrorPerror(ret, "sendto");
}

int RespondMsg(int socketFd, struct sockaddr *clientAddress, socklen_t *sinSize)
{
    size_t sizeToSend = (!sinSize) ? 0 : *sinSize;
    char buffer[BUFSIZ];

    int recMsg = recvfrom(socketFd, buffer, BUFSIZ, MSG_DONTWAIT, clientAddress, sinSize);
    IfErrorPerror(recMsg, "recv");
    if (!recMsg)
    {
        return 1;
    }
    std::cout << buffer << std::endl;
    SendToMsg(socketFd, "pong", sizeof("pong"), MSG_DONTWAIT, clientAddress, sizeToSend);

    return 0;
}

void Log(FILE *logger, size_t i, const char *msg)
{
    time_t timer = time(NULL);

    fprintf(logger, "%s", ctime(&timer));
    fprintf(logger, "%ld", i);
    fprintf(logger, "%s", " - ");
    fprintf(logger, "%s", msg);
    fprintf(logger, "%c", '\n');
}
