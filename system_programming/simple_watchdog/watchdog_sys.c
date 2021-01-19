/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review : Aviv Levanon									 *
 * 					Last update : 21.6.20									 *
 ****************************************************************************/
#include <stdio.h>     /* printf */
#include <stdlib.h>     /* system */

#define SYSTEM_ERROR (-1)

int main()
{
    int return_value = 0;

    return_value = system("./dummy");

    if (SYSTEM_ERROR == return_value)
    {
        printf("\nerror in creating new process\n");
    }

    return (return_value);
}
