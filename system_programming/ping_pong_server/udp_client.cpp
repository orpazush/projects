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

#include "utils.hpp"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "ERROR, no port provided\n");
        return (FAILURE);
    }

    const uint16_t PORT = atoi(argv[1]);

    int socketFd = CreateUDPSocket();
    struct sockaddr_in serverAddress = {0, 0, 0, 0};

    if (2 < argc)
    {
        in_addr_t ip = inet_addr(argv[2]);
        SetSockAddr(&serverAddress, PORT, ip);
    }
    else
    {
        SetSockAddr(&serverAddress, PORT);
    }

    FILE *logger = fopen("./UDP_client_logger", "a");

    size_t counter = 0;
    socklen_t sinSize = sizeof(serverAddress);
    srand(time(NULL));

    for (size_t i = (rand()%8)+3; i < 10; ++i, ++counter)
    {
        SendToMsg(socketFd, "ping", sizeof("ping"), MSG_DONTWAIT, (struct sockaddr *)&serverAddress, sinSize);
        Log(logger, i, "send ping to server");
        RecMsg(socketFd, 0, (struct sockaddr *)&serverAddress, &sinSize);
        size_t sleepTime = (rand()%8)+3;
        sleep(sleepTime);
    }

    fclose(logger);
    close(socketFd);

    return 0;
}