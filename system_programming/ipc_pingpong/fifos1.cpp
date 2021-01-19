//
// Created by orpaz on 21/08/2020.
//
#include <unistd.h>     //open, close
#include <stdio.h>      //remove
#include <sys/stat.h>   //mkfifo, S_IRWXU
#include <fcntl.h>      //O_WRONLY, O_RDONLY

#include "fifos.hpp"

int main()
{
    const char *PING_PATH = "/tmp/pingfifo";
    const char *PONG_PATH = "/tmp/pongfifo";

    if (-1 == mkfifo(PING_PATH, S_IRUSR | S_IWUSR) || -1 == mkfifo(PONG_PATH, S_IRUSR | S_IWUSR))
    {
        remove(PING_PATH);
        remove(PONG_PATH);
        throw (std::runtime_error("mkfifo failed"));
    }

    int fdWrite = open(PING_PATH, O_WRONLY);
    int fdRead = open(PONG_PATH, O_RDONLY);
    for (size_t i = 0; 5 > i; ++i)
    {
        WriteFifo(fdWrite, "ping");
        ReadFifo(fdRead);
        sleep(3);
    }
    close(fdWrite);
    close(fdRead);
    remove(PING_PATH);
    remove(PONG_PATH);

    return (0);
}