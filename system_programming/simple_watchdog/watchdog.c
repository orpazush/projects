/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review : Aviv Levanon									 *
 * 					Last update : 21.6.20									 *
 ****************************************************************************/
#include <stdio.h>      /* printf */
#include <unistd.h>     /* fork */
#include <sys/wait.h>   /* waitpid, pid_t */

#define EXECVP_ERROR (-1)

int main()
{
    char *arg_list[] = {"./dummy", NULL};
    pid_t child_pid = 0;
    int exit_status = 0;

    while (1)
    {
        child_pid = fork();

        if (0 > child_pid)
        {
            printf("error in creating the child");
        }

        if (child_pid)
        {
            waitpid(child_pid, &exit_status, 0);
            printf("\nexit code of my child: %d\n", WEXITSTATUS(exit_status));
        }

        else
        {
            if (EXECVP_ERROR == execvp("./dummy", arg_list))
            {
                perror("execvp: ");
                return (EXECVP_ERROR);
            }
        }
    }

    return 0;
}
