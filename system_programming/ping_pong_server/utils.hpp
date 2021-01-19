/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review : Elimelech  									 *
 * 					Last update : 27.8.20									 *
 ****************************************************************************/

#ifndef RD8788_UTILS_HPP
#define RD8788_UTILS_HPP

#include <iostream>
#include <cstdio>
#include <netinet/in.h>

enum tcp_status {ERROR = -1, SUCCESS, FAILURE};

inline void IfErrorPerror(int to_check, const char *msg)
{
    if (ERROR == to_check)
    {
        perror(msg);
        throw(std::runtime_error(msg));
    }
}

int CreateTCPSocket();
int CreateUDPSocket();
void SetSockAddr(struct sockaddr_in *Address, uint16_t port, in_addr_t address = INADDR_ANY);
int BindSocket(int socketFd, struct sockaddr_in serverAddress);
int RecMsg(int socketFd, int flag = 0, struct sockaddr *clientAddress = NULL, socklen_t *sinSize = NULL);
void SendToMsg(int socketFd, const char *msg, size_t msgSize, int flag = 0, struct sockaddr *clientAddress = NULL,
                socklen_t sinSize = 0);
int RespondMsg(int socketFd, struct sockaddr *clientAddress = NULL, socklen_t *sinSize = NULL);
void Log(FILE *logger, size_t i, const char *msg);


#endif //RD8788_UTILS_HPP
