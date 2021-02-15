/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review : Gil Mazliah									 *
 * 					Last update : 6.7.20									 *
 ****************************************************************************/
#include <stdio.h>  /* printf */
#include <unistd.h> /* sleep */
#include "wd_api.h" /* MMI, DNR */

int main(int argc, char *argv[])
{
    size_t i = 0;

    MMI(5, 2, argc, argv);

    for (i = 0; i < 20; ++i)
    {
        printf("\n%ld", i);
        sleep(1);
    }

    DNR();

    return (0);
}
