/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review : Izik Avinoam									 *
 * 					Last update : 22.6.20									 *
 ****************************************************************************/
#define _XOPEN_SOURCE 700   /* storage size of struct sigaction */

#include <stdio.h>      /* printf */
#include <unistd.h>     /* getppid */
#include <signal.h>     /* SIGUSR1 */

#define PING (1)

sig_atomic_t ping_flag = 0;

void PingHandler(int signal_number);

int main()
{
     struct sigaction ping = {0};
     ping.sa_handler = PingHandler;
     sigaction(SIGUSR1, &ping, NULL);

     pause();

     if (PING == ping_flag)
     {
         printf("ping\n");
         sleep(1);
         kill(getppid(), SIGUSR2);
     }

     return (0);
}

void PingHandler(int signal_number)
{
    (void)signal_number;
    ping_flag = PING;
}
