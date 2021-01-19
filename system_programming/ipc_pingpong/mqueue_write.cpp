//
// Created by orpaz on 21/08/2020.
//

#include <sys/ipc.h>    //ftok, IPC_CREAT
#include <sys/msg.h>    //msgsnd
#include <iostream>     //throw, runtime_error
#include <cstring>      //strcpy

int main()
{
    enum {ERROR = -1};
    const char *PATH = "mqueue_write.cpp";

    struct msgBuffer
    {
        long mesg_type;
        char mesg_text[50];
    }message;
    message.mesg_type = 1;
    strcpy(message.mesg_text, "if you wont the money you should");

    key_t uniquKey = ftok(PATH, 88);
    int messageId = msgget(uniquKey, 0666 | IPC_CREAT);
    if(ERROR == msgsnd(messageId, &message, sizeof(message), 0))
    {
        throw (std::runtime_error("msgsnd failed\n"));
    }

    strcpy(message.mesg_text, "talk with your brothers");
    if(ERROR == msgsnd(messageId, &message, sizeof(message), 0))
    {
        throw (std::runtime_error("msgsnd failed\n"));
    }

    strcpy(message.mesg_text, "I love my kitchen");
    if(ERROR == msgsnd(messageId, &message, sizeof(message), 0))
    {
        throw (std::runtime_error("msgsnd failed\n"));
    }

    return 0;
}