/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review :      						                     *
 * 					Last update : 15.9.20									 *
 ****************************************************************************/
#include <cstdio>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdlib>
#include <cstring>
#include <iostream>

#include "utils.hpp"

using namespace std;

int main()
{
    uint16_t port = 2024;
    srand(time(NULL));
    int socketFd[4] = {0};
    struct sockaddr_in serverAddress[4];

    for (size_t i = 0; i < 4; ++i, ++port)
    {
        socketFd[i] = CreateUDPSocket();
        memset(serverAddress + i, 0, sizeof(struct sockaddr_in));
        SetSockAddr((serverAddress + i), port);

        socklen_t sinSize = sizeof(serverAddress[i]);
        char buffer[BUFSIZ];
        cout << "in port:" << port << endl;
        sprintf(buffer, "%d", port);
        SendToMsg(socketFd[i], buffer, 10, 0, (struct
                sockaddr *)(serverAddress + i), sinSize);
        size_t sleepTime = (rand() % 3);
        sleep(sleepTime);
    }

    return 0;
}
