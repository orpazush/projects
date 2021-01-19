//
// Created by orpaz on 25/08/2020.
//

#include <cstdio>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdlib>

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
    SetSockAddr(&serverAddress, PORT);

    BindSocket(socketFd, serverAddress);

    struct sockaddr clientAddress = {0};
    socklen_t sinSize = sizeof(clientAddress);

    for (size_t i = 0; i < 10; ++i)
    {
        RecMsg(socketFd, &clientAddress, &sinSize);
        SendToMsg(socketFd, "pong", sizeof("pong"), &clientAddress, sinSize);
        sleep(1);
    }

    close(socketFd);

    return 0;
}