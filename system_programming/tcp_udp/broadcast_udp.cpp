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

    int broadcast = 1;
    if(ERROR == setsockopt(socketFd, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast)))
    {
        perror("setsockopt");
        close(socketFd);

        return (FAILURE);
    }

    struct sockaddr_in recivedAddr = {0};
    SetSockAddr(&recivedAddr, PORT, INADDR_BROADCAST);

    char MSG[] = "everyone who listen";
    SendToMsg(socketFd, MSG, sizeof(MSG), (sockaddr *)&recivedAddr, sizeof(recivedAddr));
    socklen_t bufsize = 0;
    RecMsg(socketFd, (sockaddr *)&recivedAddr, &bufsize);
//
//    char recvBuffer[50] = "";
//    socklen_t recvBufferlen = sizeof(recvBuffer);
//    recvfrom(socketFd, recvBuffer, recvBufferlen, 0, (sockaddr *)&recivedAddr, &recvBufferlen);
//    std::cout << "Received message :" << recvBuffer << std::endl;

    close(socketFd);

    return (SUCCESS);
}

