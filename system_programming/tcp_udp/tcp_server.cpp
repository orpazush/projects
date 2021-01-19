/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review : 									 *
 * 					Last update : 27.8.20									 *
 ****************************************************************************/

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <cstdlib>
#include <pthread.h>

#include "tcp_udp_utils.hpp"

static void *ConnectClient(void *param);


int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "ERROR, no port provided\n");
        return (FAILURE);
    }

    const uint16_t PORT = atoi(argv[1]);
    const int BACKLOG = 10;

    int socketFd = CreateTCPSocket();

    struct sockaddr_in serverAddress = {0};
    SetSockAddr(&serverAddress, PORT);
    BindSocket(socketFd, serverAddress);

    int ret = listen(socketFd, BACKLOG);
    IfErrorPerror(ret, "listen");

    struct sockaddr clientAddr = {0};
    socklen_t sinSize = sizeof(struct sockaddr_in);
    pthread_t clientHandler[BACKLOG] = {0};

    for (size_t i = 0; i < BACKLOG; ++i)
    {
        int newSockFd = accept(socketFd, &clientAddr, &sinSize);
        IfErrorPerror(newSockFd, "accept");

        while (pthread_create((clientHandler + i), 0, ConnectClient, reinterpret_cast<void *>(newSockFd)));
    }

    for (size_t i = 0; i < BACKLOG; ++i)
    {
        pthread_join(clientHandler[i], 0);
    }

    close(socketFd);

    return SUCCESS;
}


static void *ConnectClient(void *param)
{
    size_t cast_param = reinterpret_cast<size_t>(param);
    int socketFd = static_cast<int>(cast_param);
    for (size_t i = 0; i < 10; ++i)
    {
        SendToMsg(socketFd, "ping", sizeof("ping"));
        RecMsg(socketFd);
        sleep(1);
    }
    close(socketFd);

    return 0;
}