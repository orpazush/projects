//
// Created by orpaz on 21/08/2020.
//
#include <iostream>

void WriteFifo(int fifoFd, const char *message)
{
    write(fifoFd, message, sizeof(message));
}

void ReadFifo(int fifoFd)
{
    char buffer[1024];
    read(fifoFd, buffer, 1024);
    std::cout << buffer << std::endl;
}

#ifndef IPC_FIFOS_H
#define IPC_FIFOS_H


class fifos {

};


#endif //IPC_FIFOS_H
