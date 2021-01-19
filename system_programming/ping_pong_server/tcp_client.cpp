/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review : Elimelech  									 *
 * 					Last update : 27.8.20									 *
 ****************************************************************************/

#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
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


    struct sockaddr_in serverAddr = {0, 0, 0, 0};
    if (2 < argc)
    {
        in_addr_t ip = inet_addr(argv[2]);
        SetSockAddr(&serverAddr, PORT, ip);
    }
    else
    {
        SetSockAddr(&serverAddr, PORT);
    }

    FILE *logger = fopen("./TCP_client_logger", "a");

    int socketFd = CreateTCPSocket();
    int ret = connect(socketFd, (struct sockaddr *)&serverAddr, sizeof(struct sockaddr));
    IfErrorPerror(ret, "connect");

    size_t counter = 0;
    srand(time(NULL));
    for (size_t i = (rand()%8)+3; 0 < i; --i, ++counter)
    {
        SendToMsg(socketFd, "ping", sizeof("ping"));
        Log(logger, counter, "send ping to server");
        if (RecMsg(socketFd))
        {
            fclose(logger);
            close(socketFd);
            return 0;
        }

        size_t sleepTime = (rand()%8)+3;
        sleep(sleepTime);
    }

    fclose(logger);
    close(socketFd);

    return 0;
}