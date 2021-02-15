/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review :      						         *
 * 					Last update : 16.8.20									 *
 ****************************************************************************/
#include <sys/socket.h>
#include <netinet/in.h>             //INADDR_ANY
#include <cstdio>                   //BUFSIZ
#include <iostream>

#include "udp_socket.hpp"

using namespace ilrd;
using namespace project;

int main()
{
    UDPSocket UDP(5555);
    struct sockaddr_in serverAddress = {AF_INET, 5555, INADDR_ANY, 0};

    char buffer[BUFSIZ];
    socklen_t sinSize = sizeof(serverAddress);

    for (size_t i = 0; i < 3; ++i)
    {
        sendto(UDP.GetFd(), "ping", sizeof("ping"), MSG_DONTWAIT,
               reinterpret_cast<const sockaddr *>(&serverAddress), sinSize);
        recvfrom(UDP.GetFd(), buffer, sizeof(buffer), 0,
                 reinterpret_cast<sockaddr *>(&serverAddress), &sinSize);
        sleep(2);
        std::cout << buffer << std::endl;
    }
}
