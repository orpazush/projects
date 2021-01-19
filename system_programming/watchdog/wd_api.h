/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review : Gil Mazliah									 *
 * 					Last update : 6.7.20									 *
 ****************************************************************************/
 #ifndef __WD_API_H__
 #define __WD_API_H__

/*****************************************************************************
 * Function:  MMI                                                            *
 * ------------------------------------------------------------------------- *
 * responsible to promise the execution of the critical section hangs between*
 * it & DNR. the function use the program 'watchdog.out' to monitor that     *
 * the program is running & executing it all instruction. the watchdog       *
 * checks every given 'interval' for indication that the program is still    *
 * running. if after 'num_of_checks' the watchdog doesn't get a life sign    *
 * from the program it will reboot the program from the begining.            *
 * NOTE - The program might doesn't protect cases that something happen to   *
 *        the user's program & the watchdog at the same time.                *
 *      - Befor rebooting signal will be send to make sure the program is    *
 *        terminated.                                                        *
 *                                                                           *
 * num_of_checks: size_t - the number of the checks the program will make    *
 *                         befor rebooting the program.                      *
 * interval: size_t - the interval between every checks                      *
 * argc: int - the argc from the main in the user's program to pass on case  *
 *             reboot is needed.                                             *
 * argv: char ** - the argc from the main in the user's program to pass on   *
 *                 case reboot is needed.                                    *
 *                                                                           *
 * returns: int, (0) on success or (1) if error occured                      *
 ****************************************************************************/

int MMI(size_t num_of_checks, size_t interval, int argc, char *argv[]);

/*****************************************************************************
 * Function:  DNR                                                            *
 * --------------------------------------------------------------------------*
 * End of the critical section. terminate the processes created by MMI & free*
 * all it allocated memory                                                   *
 *                                                                           *
 * returns: none                                                             *
 ****************************************************************************/
void DNR(void);

 #endif /* __WD_API_H__ */
