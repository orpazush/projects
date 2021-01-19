//
// Created by orpaz on 21/08/2020.
//

#include <sys/ipc.h>    //ftok, IPC_CREAT
#include <sys/msg.h>    //msgsnd
#include <iostream>     //throw, runtime_error
#include <errno.h>      //ENOMSG, errno

int main()
{
    enum {ERROR = -1};
    struct msgBuffer
    {
        long mesg_type;
        char mesg_text[50];
    }message;

    const char *PATH = "mqueue_write.cpp";
    key_t uniquKey = ftok(PATH, 88);
    int messageId = msgget(uniquKey, 0666 | IPC_CREAT);
    if(ERROR == msgrcv(messageId, &message, sizeof(message), 1, IPC_NOWAIT))
    {
        if (ENOMSG == errno)
        {
            msgctl(messageId, IPC_RMID, 0);
            return 0;
        }
        throw (std::runtime_error("msgrcv failed\n"));
    }

    std::cout << message.mesg_text <<std::endl;

    return 0;
}