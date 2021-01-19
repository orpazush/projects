/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review : Izik Avinoam									 *
 * 					Last update : 22.6.20									 *
 ****************************************************************************/
#define _XOPEN_SOURCE 700   /* storage size of struct sigaction */

#include <stdio.h>      /* printf */
#include <unistd.h>     /* getppid */
#include <signal.h>     /* SIGUSR1 */
#include <stdlib.h>     /* atoi */

static void Ping_handler (int signal_number);


int main(int argc, const char *argv[])
{
	int ping_pid = atoi(argv[1]);
	struct sigaction ping;
	argc = argc;

   	ping.sa_handler = &Ping_handler;
   	ping.sa_flags = SA_SIGINFO;
   	sigaction (SIGUSR1, &ping, NULL);

   	while (1)
   	{
   		kill(ping_pid, SIGUSR2);
  		pause();
  		sleep(1);

   		printf("pong\n");
   	}

	return 0;
}

static void Ping_handler (int signal_number)
{
	(void)signal_number;

	return;
}
