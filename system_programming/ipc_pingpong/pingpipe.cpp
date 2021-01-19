//
// Created by orpaz on 20/08/2020.
//
#include <unistd.h>
#include <iostream>

using namespace std;

void WritePipe(int pipefd, const char *message)
{
    if (0 > write(pipefd, message, sizeof(message)))
    {
        throw (runtime_error("write failed\n"));
    };
}

void ReadPipe(int pipefd)
{
    char buffer[1024];
    if (0 > read(pipefd, buffer, 1024))
    {
        throw (runtime_error("read failed\n"));
    }
    cout << buffer << endl;
}

int main()
{
    enum {ERROR = -1};
    enum {READ, WRITE};
    int fdPing[2];
    int fdPong[2];
    if (ERROR == pipe(fdPing) || ERROR == pipe(fdPong))
    {
        throw (runtime_error("pipe failed\n"));
    }

    pid_t responderid = fork();
    if (ERROR == responderid)
    {
        throw (runtime_error("fork failed\n"));
    }
    else if (0 == responderid)
    {
        close(fdPing[WRITE]);
        close(fdPong[READ]);
        for (size_t i = 0; 5 > i; ++i)
        {
            ReadPipe(fdPing[READ]);
            WritePipe(fdPong[WRITE], "pong");
        }
        close(fdPing[READ]);
        close(fdPong[WRITE]);
    }
    else
    {
        close(fdPing[READ]);
        close(fdPong[WRITE]);
        for (size_t i = 0; 5 > i; ++i)
        {
            WritePipe(fdPing[WRITE], "ping");
            ReadPipe(fdPong[READ]);
        }
        close(fdPing[WRITE]);
        close(fdPong[READ]);
    }
}