//
// Created by orpaz on 23/08/2020.
//

#include <sys/shm.h>    //shmget, shmat, SHM_RDONLY
#include <iostream>     //cout
#include <fcntl.h>      //O_WRONLY, O_RDONLY

int main()
{
    key_t uniquKey = ftok("shm_write.cpp", 88);
    int shmId = shmget(uniquKey, 555, S_IRUSR);
    char *shmAddress = static_cast<char *>(shmat(shmId, NULL, SHM_RDONLY));
    std::cout << shmAddress << std::endl;

    shmdt(shmAddress);

    return (0);
}