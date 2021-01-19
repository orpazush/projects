/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review : Izik Avinoam									 *
 * 					Last update : 22.6.20									 *
 ****************************************************************************/
#define _XOPEN_SOURCE 700	/* storage size of struct sigaction */

#include <stdio.h>      	/* printf */
#include <unistd.h>    		/* fork */
#include <sys/wait.h>   	/* waitpid */
#include <signal.h>     	/* SIGUSR1 */

#define ERROR (-1)

typedef struct sigaction sigaction_t;
enum flags
{
    PING,
    PONG
};

sig_atomic_t flag = 2;

void PingHandler(int signal_number);
void PongHandler(int signal_number);

int main()
{
    int exit_status = 0;
    pid_t parent_pid = getpid();
    pid_t child_pid = 0;
	sigaction_t ping;
	sigaction_t pong;
	ping.sa_handler = PingHandler;
	pong.sa_handler = PongHandler;
	sigaction(SIGUSR1, &ping, NULL);
    sigaction(SIGUSR2, &pong, NULL);


    while (1)
    {
        child_pid = fork();

        if (ERROR == child_pid)
        {
            perror("\nerror in creating a new process\n");
            return (ERROR);
        }

        else if (!child_pid)
        {
            if (PING == flag)
            {
				sleep(1);
                printf("ping\n");
                kill(parent_pid, SIGUSR2);
            }

            return 0;
        }

        else
        {
            kill(child_pid, SIGUSR1);
            pause();
            if (PONG == flag)
            {
				sleep(1);
                printf("pong\n");
            }
            waitpid(child_pid, &exit_status, 0);
        }
    }

    return (exit_status);
}

void PingHandler(int signal_number)
{
    (void)signal_number;
    flag = PING;
}

void PongHandler(int signal_number)
{
    (void)signal_number;
    flag = PONG;
}
