/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review : Gil Mazliah									 *
 * 					Last update : 6.7.20									 *
 ****************************************************************************/
#ifndef __WD_UTILS_H__
#define __WD_UTILS_H__

#include <stdatomic.h>      /* sig_atomic_t */

#include "heap_scheduler.h" /* heap_scheduler_t, HeapSchdCreate.. */


#define TERMINATE_PROCESS (1)


typedef int (*reboot_func_t)(pid_t *pid_to_update, char *arg_list[]);
typedef struct sigaction sigaction_t;

/* sor stand for Signal Or Reboot */
typedef struct sor_param
{
    pid_t *pid;                 /* pid of the process to signal to */
    sig_atomic_t *counter;      /* grows every time signal is send & reset when
                                   signal arrives. used to count unresponded
                                   checks */
    sig_atomic_t *terminate;    /* when it set, the process will be terminated */
    int checks;                 /* number of unresponded checks befor reboot */
    reboot_func_t reboot_func;  /* function to reboot the unresponding process */
    char **arg_list;            /* keeps the user's program arguments to pass
                                   when it rebooted */
    char *to_print;             /* can be delete after */
    sem_t *post_sem;            /* allow the other waiting process to continue */
    sem_t *wait_sem;            /* wait until the other process is ready */
    sem_t *cs_sem;              /* allow the critical section to continue After
                                   both the keeper & the watchdog are ready */
}sor_param_t;


/* this is the task which puts in the schedular. responsible to send signal
   to 'pid' every 'interval' seconds or reboot the other process with
   'reboot_func' if no signal arrived in the last 'checks' times.
   if 'terminate' is set (case SIGUSR2 arrived) this task will return
   unsuccess and will be delete from the scheduler & it will be stop running */
int SignalOrReboot(void *param);

/* creates a scheduler & add it the 'communicate_task' (SignalOrReboot),
   by that it creates communication between the watchdog & the keeper.
   the scheduler will start running only if the both keeper & watchdog
   are ready. and will stop only if SIGUSR2 is arrived. if ended normally
   by SIGUSR2 it will free it's allocated memory */
int StartCommunicate(size_t interval, sor_param_t *sor_param,
                     action_func_t communicate_task);

#endif /* __WD_UTILS_H__ */
