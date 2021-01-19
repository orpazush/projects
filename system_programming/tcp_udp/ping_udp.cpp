/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review : Elimelech  									 *
 * 					Last update : 27.8.20									 *
 ****************************************************************************/

#include <cstdio>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdlib>
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

    int socketFd = CreateUDPSocket();
    struct sockaddr_in serverAddress = {0};

    if (2 < argc)
    {
        in_addr_t ip = inet_addr(argv[2]);
        SetSockAddr(&serverAddress, PORT, ip);
    }
    else
    {
        SetSockAddr(&serverAddress, PORT);
    }

    socklen_t sinSize = sizeof(serverAddress);

    for (size_t i = 0; i < 10; ++i)
    {
        SendToMsg(socketFd, "ping", sizeof("ping"),
                  (struct sockaddr *)&serverAddress, sinSize);
        RecMsg(socketFd, (struct sockaddr *)&serverAddress, &sinSize);
        sleep(1);
    }

    close(socketFd);

    return 0;
}