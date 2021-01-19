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
#include <cstring>

#include "utils.hpp"

static void Quit(FILE *logger, size_t numOfActives);
static int AcceptNewClient(int TcpSocket);
static int RespondStdin();
static void RespondUdp(int UdpSocket);
static void SetFdInSet(int newFd, fd_set *activeSet,int *maXfd,size_t *setSize);
static void UnsetFd(int fdToUnset, fd_set *activeSet, size_t *setSize);
inline int Max(int a, int b);

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "ERROR, no port provided\n");
        return (FAILURE);
    }
    const uint16_t PORT = atoi(argv[1]);

/*-------------------- open logger ------------------*/
    FILE *logger = fopen("./server_logger", "a");

/*----------- prepare UDP server socket -------------*/
    int FdUdp = CreateUDPSocket();

    struct sockaddr_in serverUdpAddress = {0, 0, 0, 0};
    SetSockAddr(&serverUdpAddress, PORT);

    BindSocket(FdUdp, serverUdpAddress);

/*----------- prepare TCP server socket -------------*/
    const int BACKLOG = 10;

    int FdTcp = CreateTCPSocket();

    int optVal = 1;
    int ret = setsockopt(FdTcp, SOL_SOCKET, SO_REUSEADDR, &optVal, sizeof(optVal));
    IfErrorPerror(ret, "setsockopt");

    struct sockaddr_in serverAddress = {0, 0, 0, 0};
    SetSockAddr(&serverAddress, PORT);
    BindSocket(FdTcp, serverAddress);

/*----------- two proccesses to deal requests ----------*/
    ret = listen(FdTcp, BACKLOG);
    IfErrorPerror(ret, "listen");

    int maxFd = 0;
    size_t num_of_actives = 0;

    fd_set activeClients = {0}, readyClients = {0};
    FD_ZERO (&activeClients);
    SetFdInSet(FdTcp, &activeClients, &maxFd, &num_of_actives);
    SetFdInSet(FdUdp, &activeClients, &maxFd, &num_of_actives);
    SetFdInSet(STDIN_FILENO, &activeClients, &maxFd, &num_of_actives);

    size_t counter = 0;
    while (1)
    {
        struct timeval interval = {7, 0};
        readyClients = activeClients;
        int num_of_readys = select((maxFd + 1), &readyClients, 0, 0,
                                    &interval);
        IfErrorPerror(num_of_readys, "select");
        if (!num_of_readys)
        {
            Log(logger, counter, "nothing happen in the last 7 seconds");
            ++counter;
        }

        if (FD_ISSET(STDIN_FILENO, &readyClients))
        {
            if (1 == RespondStdin())
            {
                Quit(logger, num_of_actives);
                return SUCCESS;
            }
            --num_of_readys;
        }

        for (int fd = 1; 0 < num_of_readys; ++fd)
        {
            if (FD_ISSET(fd, &readyClients))
            {
                if (fd == FdUdp)
                {
                    RespondUdp(fd);
                }

                else if (fd == FdTcp)
                {
                    int newClient = AcceptNewClient(fd);
                    SetFdInSet(newClient, &activeClients, &maxFd,
                               &num_of_actives);
                }

                else
                {
                    if (1 == RespondMsg(fd))
                    {
                        UnsetFd(fd, &activeClients, &num_of_actives);
                    }
                }
                --num_of_readys;
            }
        }
    }

    return (SUCCESS);
}

static void Quit(FILE *logger, size_t numOfActives)
{
    Log(logger, 0, "quit");
    for (size_t i = 1; i < numOfActives; ++i)
    {
        close(i);
    }
    fclose(logger);
}

static int AcceptNewClient(int TcpSocket)
{
    struct sockaddr clientAddr = {0, 0, 0, 0};
    socklen_t sinSize = sizeof(struct sockaddr_in);
    int newClient = accept(TcpSocket, &clientAddr, &sinSize);
    IfErrorPerror(newClient, "accept");

    return newClient;
}

int RespondStdin()
{
    char buffer[BUFSIZ];
    ssize_t recMsg = read(STDIN_FILENO, buffer, BUFSIZ);
    IfErrorPerror(recMsg, "read");

    if (0 == strcmp(buffer, "ping\n"))
    {
        std::cout << "pong" << std::endl;
    }
    return (0 == strcmp(buffer, "quit\n")) ? 1 : 0;
}

static void RespondUdp(int UdpSocket)
{
    struct sockaddr clientAddress = {0, 0, 0, 0};
    socklen_t sinSize = sizeof(clientAddress);
    RespondMsg(UdpSocket, &clientAddress, &sinSize);
}

void SetFdInSet(int newFd, fd_set *activeSet, int *maXfd, size_t *setSize)
{
    FD_SET(newFd, activeSet);
    *maXfd = Max(*maXfd, newFd);
    ++*setSize;
}

int Max(int a, int b)
{
    return ((a > b) ? a : b);
}

void UnsetFd(int fdToUnset, fd_set *activeSet, size_t *setSize)
{
    FD_CLR(fdToUnset, activeSet);
    close(fdToUnset);
    --*setSize;
}
