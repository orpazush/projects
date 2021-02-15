/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review : Gil Mazliah									 *
 * 					Last update : 6.7.20									 *
 ****************************************************************************/
#define _XOPEN_SOURCE 700   /* storage size of struct sigaction */

#include <stdio.h>          /* printf */
#include <sys/wait.h>       /* waitpid */
#include <signal.h>         /* SIGUSR1 */
#include <unistd.h>         /* fork, execvp, sleep */
#include <semaphore.h>      /* sem_t, sem_open, sem_wait.. */
#include <fcntl.h>          /* O_CREAT */
#include <stdlib.h>         /* getenv, setenv */
#include <sys/stat.h>       /* For mode constants */

#include <pthread.h>        /* pthread_t */

#include "wd_utils.h"       /* sor_param_t, reboot_func_t.. */

/*-------------------------Macros & Struct-----------------------------------*/
#define MMI_SUCCESS      (0)
#define MMI_FAIL         (1)
#define ERROR            (-1)
#define UNUSED(x)        ((void)x)


typedef struct dog_keeper
{
    size_t interval;
    sor_param_t *sor_param;
}dog_keeper_t;
/*---------------------------------------------------------------------------*/

/*---------------------------Static Functions--------------------------------*/
static void *_DogKeeper(void *dk_struct);
static void _DogIsAlive(int signal_number);
static void _TerminateKeeper(int signal_number);
static int _CreateWatchdog(pid_t *watchdog_pid, char *arg_list[]);
static void _SetEnvSizeT(const char *name, size_t to_set);
/*---------------------------------------------------------------------------*/

/*---------------------------Global Variables--------------------------------*/
sig_atomic_t sg_barking_counter = 0;
sig_atomic_t sg_terminate_keeper = 0;
pthread_t sg_dog_keeper_id = 0;
/*---------------------------------------------------------------------------*/

int MMI(size_t num_of_checks, size_t interval, int argc, char *argv[])
{
    pid_t watchdog_pid = 0;
    sor_param_t sor_keeper = {0};
    sigaction_t dog_is_alive = {0};
    sigaction_t termination = {0};
    dog_keeper_t dk_struct = {0};

    UNUSED(argc);
    printf("\nim mmi");

    _SetEnvSizeT("interval_for_watchdog_program", interval);
    _SetEnvSizeT("num_of_checks_for_watchdog_program", num_of_checks);

    dog_is_alive.sa_handler = _DogIsAlive;
    sigaction(SIGUSR1, &dog_is_alive, NULL);

    termination.sa_handler = _TerminateKeeper;
    sigaction(SIGUSR2, &termination, NULL);

    sor_keeper.pid = &watchdog_pid;
    sor_keeper.counter = &sg_barking_counter;
    sor_keeper.terminate = &sg_terminate_keeper;
    sor_keeper.checks = num_of_checks;
    sor_keeper.reboot_func = _CreateWatchdog;
    sor_keeper.arg_list = argv;
    sor_keeper.to_print = "gooddog";/* delete */
    sor_keeper.wait_sem = sem_open("/active_watchdog", O_CREAT, 0644, 0);
    sor_keeper.post_sem = sem_open("/active_keeper", O_CREAT, 0644, 0);
    sor_keeper.cs_sem = sem_open("/everything_is_ready", O_CREAT, 0644, 0);
    if (SEM_FAILED == sor_keeper.wait_sem || SEM_FAILED == sor_keeper.post_sem
        || SEM_FAILED == sor_keeper.cs_sem)
    {
        perror("sem_open");

        return (MMI_FAIL);
    }

    dk_struct.sor_param = &sor_keeper;
    dk_struct.interval = interval;

    /* checks if the watchdog is already exist */
    if (NULL == getenv("watchdog_exist"))
    {
        /* case there isn't a whachdog yet, create it */
        if (ERROR == _CreateWatchdog(sor_keeper.pid, argv))
        {
            return (MMI_FAIL);
        }
    }

    else
    {
        /* case the whachdog exist, update it pid */
        *sor_keeper.pid = getppid();
    }

    while (pthread_create(&sg_dog_keeper_id, NULL, _DogKeeper, &dk_struct));
    while (0 != sem_wait(sor_keeper.cs_sem));

    return (MMI_SUCCESS);
}

void DNR(void)
{
    kill(getpid(), SIGUSR2);

    pthread_join(sg_dog_keeper_id, NULL);
}

/*---------------------------WD_Utils Defintions-----------------------------*/
int SignalOrReboot(void *sor_param)
{
    sor_param_t *sor = (sor_param_t *)sor_param;

    if (*sor->counter == sor->checks)
    {
        *sor->counter = 0;

    /* make sure the uncommunicating thread is terminate and then reboot it */
        kill(*sor->pid, SIGKILL);
        sor->reboot_func(sor->pid, sor->arg_list);
        printf("\nopen sem after reboot");

        /* wait until the other process is ready */
        sem_post(sor->post_sem);
        while (0 != sem_wait(sor->wait_sem));
    }

    else
    {
        printf("\n%s", sor->to_print);
        kill(*sor->pid, SIGUSR1);
        ++*sor->counter;
    }

    /* when the terminate is changed, this task will return unsuccess, so it
       will be delete from the 'schd_communication' and it stop run */
	return (*sor->terminate);
}

int StartCommunicate(size_t interval, sor_param_t *sor_param,
                     action_func_t reboot_func)
{
    heap_scheduler_t *schd_communication = HeapSchdCreate();

    /* try again after a few second & if it doesn't work return */
    if (!schd_communication)
    {
        sleep(2);
        schd_communication = HeapSchdCreate();
        if (!schd_communication)
        {
            return (1);
        }
    }

    HeapSchdAdd(schd_communication, reboot_func, interval, sor_param);

    /* release the other process and wait until the other will do the same
       so they will be synchronized */
    sem_post(sor_param->post_sem);
    printf("\nopen sem");   /* delete */
    while (0 != sem_wait(sor_param->wait_sem));

    /* after the both keeper & watchdog is ready, one of them will let the
       critical section of the user program to continue */
    if (getppid() == *sor_param->pid)
    {
/*        sem_post(sor_param->cs_sem);*/
        printf("\nopen user's sem");   /* delete */
    }

    HeapSchdRun(schd_communication);

    printf("\nexit after getting SIGUSR2\n"); /* delete */

    HeapSchdDestroy(schd_communication);

    return (0);
}
/*---------------------------------------------------------------------------*/

/*---------------------------Static Defintions-------------------------------*/
/* communicating with the watchdog & responsible to terminate it */
static void *_DogKeeper(void *dk_struct)
{
    dog_keeper_t *dk = (dog_keeper_t *)dk_struct;

    StartCommunicate(dk->interval, dk->sor_param, SignalOrReboot);

    /* after normal termination by signal from DNR send signal to terminate
       the watchdog and wait for it if the watcdog isn't the parent */
    kill(*dk->sor_param->pid, SIGUSR2);

    if (*dk->sor_param->pid != getppid())
    {
        waitpid(*dk->sor_param->pid, NULL, 0);
    }

    sem_close(dk->sor_param->wait_sem);
    sem_close(dk->sor_param->post_sem);
    sem_close(dk->sor_param->cs_sem);

    return (NULL);
}

/* handler to reset the 'sg_barking_counter' when signal arrieves from the
   watchdog indicating it's still running */
static void _DogIsAlive(int signal_number)
{
    UNUSED(signal_number);
    sg_barking_counter = 0;
}

/* handler to set 'sg_terminate_keeper', when DNR signals to terminate the
   keeper */
static void _TerminateKeeper(int signal_number)
{
    UNUSED(signal_number);
    sg_terminate_keeper = TERMINATE_PROCESS;
}

/* creates a new process to execute the watchdog.out program with 'arg_list'
   as it's arguments */
static int _CreateWatchdog(pid_t *watchdog_pid, char *arg_list[])
{
    *watchdog_pid = fork();
    if (ERROR == *watchdog_pid)
    {
        /* try again & if it doesn't work, return ERROR */
        sleep(2);
        *watchdog_pid = fork();
        if (ERROR == *watchdog_pid)
        {
            perror("\nfork");
        }

        return (ERROR);
    }

    /* execute the 'watchdog' program */
    else if (!*watchdog_pid)
    {
        if (ERROR == execvp("./watchdog.out", arg_list))
        {
            perror("\nexecvp");

            return (ERROR);
        }
    }

    return (0);
}

/* gets a variable of type size_t and sets a new enviroment variable
   responding to 'name' and it's value is 'to_set' after converted to string */
static void _SetEnvSizeT(const char *name, size_t to_set)
{
    char buffer[100] = {0};

    sprintf(buffer, "%ld", to_set);

    setenv(name, buffer, 0);/* ENOMEM */
}
