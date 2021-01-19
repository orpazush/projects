/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review : Dorit Gerstenfeld								 *
 * 					Last update : 28.6.20									 *
 ****************************************************************************/
#include <sys/types.h>  /* key_t */
#include <sys/ipc.h>    /* ftok */
#include <sys/sem.h>    /* SETVAL, struct sembuf, SEM_UNDO, GETVAL  */
#include <stdio.h>      /* scanf, printf */
#include <string.h>     /* strtok */
#include <stdlib.h>     /* strtol */

#define ERROR (-1)
#define SEM_MAN_FAIL (1)

static void _RunSem();

int main(int argc, char const *argv[])
{
    int semid = 0;
    key_t key = 0;
    int sem_value = 0;

    if (2 > argc)
    {
        fprintf(stderr, "\nERROR, no file name was entered\n");
        return (SEM_MAN_FAIL);
    }

    key = ftok(argv[argc - 1], 'J');
    if (ERROR == key)
    {
        perror("\nftok");
        return (SEM_MAN_FAIL);
    }

    semid = semget(key, 1, 0660 | IPC_CREAT);
    if (ERROR == semid)
    {
        perror("\nsemget failed");
        return (SEM_MAN_FAIL);
    }

    if (ERROR == semctl(semid, 0, SETVAL, 10))
    {
        perror("\nsemctl SETVAL");
        return (SEM_MAN_FAIL);
    }

    sem_value = semctl(semid, 0, GETVAL, NULL);
    if (ERROR == sem_value)
    {
        perror("\nsemctl GETVAL");
        return (SEM_MAN_FAIL);
    }
    printf("current sem value: %d\n", sem_value);

    _RunSem(semid);

    if (ERROR == semctl(semid, 0, IPC_RMID))
    {
        perror("\nsemctl IPC_RMID: ");
    }

    return (0);
}

static void _RunSem(int semid)
{
    char input[BUFSIZ] = {0};
    struct sembuf sem_buf[1];
    char *operation = 0;
    char *amount = NULL;
    size_t number = 0;
    char *undo = NULL;
    int sem_value = 0;

    scanf("%[^\n]%*c", input);
    sem_buf[0].sem_num = 0;

    while ('X' != *input)
    {
        operation = strtok(input, " ");
        amount = strtok(NULL, " ");

        if(!amount || ('D' != *operation && 'U' != *operation))
        {
            printf ("bad input");
            return;
        }
        undo = strtok(NULL, " ");

        number = atol(amount);

        if ('D' == *operation)
        {
            sem_buf[0].sem_op = -number;
            if (undo && 0 == strcmp(undo, "undo"))
            {
                sem_buf[0].sem_flg = SEM_UNDO;
            }
        }

        else if ('U' == *operation)
        {
            sem_buf[0].sem_op = number;
            if (undo && 0 == strcmp(undo, "undo"))
            {
                sem_buf[0].sem_flg = SEM_UNDO;
            }
        }
        if (ERROR == semop (semid, sem_buf, 1))
        {
            perror("\nsemop: ");
            return;
        }
        sem_value = semctl(semid, 0, GETVAL, NULL);

        printf("current sem value: %d\n", sem_value);

        scanf("%[^\n]%*c", input);
    }
}
