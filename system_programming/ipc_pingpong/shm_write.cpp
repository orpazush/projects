//
// Created by orpaz on 23/08/2020.
//

#include <sys/shm.h>    //shmget, shmat, SHM_RDONLY
#include <cstring>      //strcpy
#include <stdio.h>      //perror
#include <fcntl.h>      //S_IRUSR

int main()
{
    key_t uniquKey = ftok("shm_write.cpp", 88);
    if (-1 == uniquKey)
    {
        perror("ftok:");
    }
    int shmId = shmget(uniquKey, 555, S_IRUSR | S_IWUSR | IPC_CREAT);
    if (-1 == shmId)
    {
        perror("shmId:");
    }
    char *shmAddress = static_cast<char *>(shmat(shmId, 0, 0));
    strcpy(shmAddress, "I love to share!");

    shmdt(shmAddress);

    return (0);
}