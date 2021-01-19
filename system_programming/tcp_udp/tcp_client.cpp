/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review : 									 *
 * 					Last update : 27.8.20									 *
 ****************************************************************************/

#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "tcp_udp_utils.hpp"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "ERROR, no port provided\n");
        return (FAILURE);
    }

    const uint16_t PORT = atoi(argv[1]);

    int socketFd = CreateTCPSocket();

    struct sockaddr_in serverAddr = {0};
    if (2 < argc)
    {
        in_addr_t ip = inet_addr(argv[2]);
        SetSockAddr(&serverAddr, PORT, ip);
    }
    else
    {
        SetSockAddr(&serverAddr, PORT);
    }

    int ret = connect(socketFd, (struct sockaddr *)&serverAddr, sizeof(struct sockaddr));
    IfErrorPerror(ret, "connect");

    for (size_t i = 0; i < 10; ++i)
    {
        RecMsg(socketFd);
        SendToMsg(socketFd, "pong", sizeof("pong"));
    }
    close(socketFd);

    return 0;
}