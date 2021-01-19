/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review : Gil Mazliah									 *
 * 					Last update : 6.7.20									 *
 ****************************************************************************/
#define _XOPEN_SOURCE 700   /* storage size of struct sigaction */

#include <stdio.h>          /* printf */
#include <signal.h>         /* SIGUSR1, SIGUSR2 */
#include <unistd.h>         /* fork, execvp, getppid */
#include <stdlib.h>         /* atol */
#include <semaphore.h>      /* sem_t, sem_init, sem_wait.. */
#include <fcntl.h>          /* O_CREAT */
#include <sys/stat.h>       /* For mode constants */

#include <pthread.h>        /* pthread_t */

#include "wd_utils.h"       /* sor_param_t */


#define UNUSED(x)           ((void)x)
#define WATCHDOG_FAIL       (1)
#define WATCHDOG_SUCCESS    (0)
#define ERROR               (1)

/*---------------------------Static Functions--------------------------------*/
static int RebootClientApp(pid_t *keeper_pid, char *arg_list[]);
static void KeeperIsAlive(int signal_number);
static void TerminateWatchdog(int signal_number);
/*---------------------------------------------------------------------------*/

/*---------------------------Global Variables--------------------------------*/
sig_atomic_t sg_keeper_signals_counter = 0;
sig_atomic_t sg_terminate_watchdog = 0;
/*---------------------------------------------------------------------------*/

int main(int argc, char *argv[])
{
    pid_t keeper_pid = 0;
    sor_param_t sor_wd = {0};
    sigaction_t keeper_is_alive = {0};
    sigaction_t termination = {0};
    size_t interval = 0;

    UNUSED(argc);

    printf("\ni'm watchdog");/* delete.. */

    setenv("watchdog_exist", "value", 0);

    keeper_is_alive.sa_handler = KeeperIsAlive;
    sigaction(SIGUSR1, &keeper_is_alive, NULL);

    termination.sa_handler = TerminateWatchdog;
    sigaction(SIGUSR2, &termination, NULL);

    keeper_pid = getppid();
    interval = atol(getenv("interval_for_watchdog_program"));

    sor_wd.pid = &keeper_pid;
    sor_wd.counter = &sg_keeper_signals_counter;
    sor_wd.terminate = &sg_terminate_watchdog;
    sor_wd.checks = atol(getenv("num_of_checks_for_watchdog_program"));
    sor_wd.reboot_func = RebootClientApp;
    sor_wd.arg_list = argv;
    sor_wd.to_print = "woof";
    sor_wd.wait_sem = sem_open("/active_keeper", O_CREAT, 0644, 0);
    sor_wd.post_sem = sem_open("/active_watchdog", O_CREAT, 0644, 0);
    sor_wd.cs_sem = sem_open("/everything_is_ready", O_CREAT, 0644, 0);
    if (SEM_FAILED == sor_wd.wait_sem || SEM_FAILED == sor_wd.post_sem
        || SEM_FAILED == sor_wd.cs_sem)
    {
        perror("sem_open");

        return (WATCHDOG_FAIL);
    }

    if (0 != StartCommunicate(interval, &sor_wd, SignalOrReboot))
    {
        return (WATCHDOG_FAIL);
    }

    return (WATCHDOG_SUCCESS);
}

/*---------------------------Static Defintions-------------------------------*/
/* handler to reset the 'sg_keeper_signals_counter' when signal arrieves
   from the keeper indicating it's still running */
static void KeeperIsAlive(int signal_number)
{
    UNUSED(signal_number);
    sg_keeper_signals_counter = 0;
}

/* handler to set 'sg_terminate_watchdog', when DNR signals to terminate the
   keeper */
static void TerminateWatchdog(int signal_number)
{
    UNUSED(signal_number);
    sg_terminate_watchdog = TERMINATE_PROCESS;
}

/* creates a new process to execute the client app program with 'arg_list'
   as it's arguments */
static int RebootClientApp(pid_t *keeper_pid, char *arg_list[])
{
    *keeper_pid = fork();

    printf("\nrestart user program"); /* delete */
    if ((-1) == *keeper_pid)
    {
        /* try again & if it doesn't work, return ERROR */
        sleep(2);
        *keeper_pid = fork();
        if ((-1) == *keeper_pid)
        {
            perror("fork");

            return (1);
        }
    }

    /* turn to execute the 'watchdog' */
    else if (!*keeper_pid)
    {
        if ((-1) == execvp(arg_list[0], arg_list))
        {
            perror("\nexecvp");

            return (1);
        }
    }

    return (0);
}
