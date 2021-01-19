/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review : 									 *
 * 					Last update : 27.8.20									 *
 ****************************************************************************/

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>

#include "utils.hpp"


int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "ERROR, no port provided\n");
        return (FAILURE);
    }

    int socketFd = CreateUDPSocket();

    int broadcast = 1;
    if(ERROR == setsockopt(socketFd, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast)))
    {
        perror("setsockopt");
        close(socketFd);

        return (FAILURE);
    }

    uint16_t port = atoi(argv[1]);
    struct sockaddr_in recivedAddr = {0};
    SetSockAddr(&recivedAddr, port, INADDR_BROADCAST);

    char MSG[] = "everyone who listen";
    SendToMsg(socketFd, MSG, sizeof(MSG), 0, (sockaddr *)&recivedAddr, sizeof(recivedAddr));
    socklen_t bufsize = 0;
    RecMsg(socketFd, 0, (sockaddr *)&recivedAddr, &bufsize);

    close(socketFd);

    return (SUCCESS);
}
