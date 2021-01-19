/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review : Izik Avinoam									 *
 * 					Last update : 22.6.20									 *
 ****************************************************************************/
#define _XOPEN_SOURCE 700   /* storage size of struct sigaction */

#include <stdio.h>      /* printf */
#include <unistd.h>     /* fork, getpid */
#include <sys/wait.h>   /* waitpid */
#include <signal.h>     /* SIGUSR1 SIGUSR2 */

#define ERROR (-1)
#define PONG (1)

typedef struct sigaction sigaction_t;


sig_atomic_t pong_flag = 0;

void PongHandler(int signal_number);

int main()
{
    int exit_status = 0;
    pid_t child_pid = 0;
    char *arg_list[] = {"./pingpong", NULL};
    sigaction_t pong = {0};
    pong.sa_handler = PongHandler;
    sigaction(SIGUSR2, &pong, NULL);

    while (1)
    {
        child_pid = fork();

        if (ERROR == child_pid)
        {
            perror("\nfork: ");
            return (ERROR);
        }

        else if (!child_pid)
        {
            if (ERROR == execvp("./pingpong", arg_list))
            {
                perror("\nexecvp: ");

                return (ERROR);
            }
        }

        else
        {
            sleep(1);
            kill(child_pid, SIGUSR1);
            pause();

            if (PONG == pong_flag)
            {
                printf("pong\n");
            }
            waitpid(child_pid, &exit_status, 0);
        }
    }

    return (exit_status);
}

void PongHandler(int signal_number)
{
    (void)signal_number;
    pong_flag = PONG;
}
