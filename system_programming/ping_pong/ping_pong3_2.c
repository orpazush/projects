/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review : Izik Avinoam									 *
 * 					Last update : 22.6.20									 *
 ****************************************************************************/
#define _XOPEN_SOURCE 700   /* storage size of struct sigaction */

#include <stdio.h>      /* printf */
#include <sys/wait.h>   /* waitpid */
#include <signal.h>     /* SIGUSR1 SIGUSR2 */
#include <unistd.h>     /* pause */

static void Pong_handler (int signal, siginfo_t *pong_info, void *context);

static sig_atomic_t pong_pid = 0;

int main()
{
	struct sigaction pong = {0};

	pong.sa_sigaction = &Pong_handler;
	pong.sa_flags = SA_SIGINFO;

	sigaction (SIGUSR2, &pong, NULL);

	while (1)
	{
		pause();
		sleep(1);

		printf("ping\n");
		kill(pong_pid, SIGUSR1);
	}

	return 0;
}

static void Pong_handler (int signal, siginfo_t *pong_info, void *context)
{
	(void)signal;
	(void)context;

	if (pong_info)
	{
		pong_pid = pong_info->si_pid;
	}

	return;
}
