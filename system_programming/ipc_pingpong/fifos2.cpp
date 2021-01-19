//
// Created by orpaz on 21/08/2020.
//
#include <fcntl.h>  //O_WRONLY, O_RDONLY
#include <unistd.h> //open, close

#include "fifos.hpp"

int main()
{
    const char *PING_PATH = "/tmp/pingfifo";
    const char *PONG_PATH = "/tmp/pongfifo";

    int fdRead = open(PING_PATH, O_RDONLY);
    int fdWrite = open(PONG_PATH, O_WRONLY);
    for (size_t i = 0; 5 > i; ++i)
    {
        ReadFifo(fdRead);
        WriteFifo(fdWrite, "pong");
    }

    close(fdWrite);
    close(fdRead);

    return (0);
}
