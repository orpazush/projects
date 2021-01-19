#include <iostream>
#include <boost/bind.hpp>
#include <cstdio>

#include "reactor.hpp"
#include "utils.hpp"

using namespace ilrd;
using namespace std;
using namespace project;

int CreateUDPServer(uint16_t port);
void Stop(Reactor *toStop);
void RespondStdin();
void PrintMsg(int fd);

int main()
{
    boost::function<void(void)> Res = RespondStdin;
    Reactor reek;
    boost::function<void(void)> stop = boost::bind(Stop, &reek);
    boost::function<void(void)> read[4];
    uint16_t port = 2024;

    int readerFd[4] = {0};
    for(size_t i = 0; i < 4; i++)
    {
        readerFd[i] = CreateUDPServer(port);
        read[i] = boost::bind(PrintMsg, readerFd[i]);
        reek.Add(readerFd[i], Reactor::READ, read[i]);
        ++port;
    }
    reek.Add(STDIN_FILENO, Reactor::READ, stop);
    reek.Run();
    reek.Remove(readerFd[0], Reactor::READ);
    reek.Remove(readerFd[1], Reactor::READ);
    reek.Run();

    return 0;
}

int CreateUDPServer(uint16_t port)
{
    int FdUdp = CreateUDPSocket();

    struct sockaddr_in serverUdpAddress = {0, 0, 0, 0};
    SetSockAddr(&serverUdpAddress, port);

    BindSocket(FdUdp, serverUdpAddress);

    return FdUdp;
}


void Stop(Reactor *toStop)
{
    char buffer[BUFSIZ];
    read(STDIN_FILENO, buffer, BUFSIZ);
    toStop->Stop();
}

void RespondStdin()
{
    char buffer[BUFSIZ];
    ssize_t recMsg = read(STDIN_FILENO, buffer, BUFSIZ);
    if (-1 == recMsg)
    {
        perror("read");
    }

    if (0 == strcmp(buffer, "ping\n"))
    {
        std::cout << "pong" << std::endl;
    }
}

void PrintMsg(int fd)
{
    char buffer[BUFSIZ];
    ssize_t recMsg = read(fd, buffer, BUFSIZ);
    if (-1 == recMsg)
    {
        perror("read");
    }

    std::cout << "message is port: " << buffer << std::endl;
    std::cout << "fd: " << fd << std::endl;
}
