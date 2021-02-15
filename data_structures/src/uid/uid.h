/****************************************************************************
 * 						written by : orpaz houta							*
 *						review : Chanan Komer								*
 * 						Last update : 25.4.20								*
 ***************************************************************************/

#ifndef __UID_H__ 
#define __UID_H__ 

#include <time.h>		/* time_t */
#include <sys/types.h>	/* pid_t */

typedef struct ilrd_uid ilrd_uid_t;

struct ilrd_uid
{
	size_t counter;
	pid_t pid;
	time_t time;
};

/*
 * Function:  UIDCreate
 * --------------------
 * creates a new uid
 *
 * returns: ilrd_uid_t, the new uid
 */
ilrd_uid_t UIDCreate(void);


/*
 * Function:  UIDIsSame
 * --------------------
 * compares between two given 'uid1' and 'uid2'
 *
 * uid1: ilrd_uid_t, uid to be compare
 *
 * uid1: ilrd_uid_t, uid to be compare
 *
 * returns: int, 1 if they are equal, 0 otherwise
 */
int UIDIsSame(ilrd_uid_t uid1, ilrd_uid_t uid2);


/* bad uid to be compared with */
extern ilrd_uid_t g_bad_ilrd_uid;

#endif /* ifdef __UID_H__ */ 
/* (╯°□°）╯︵ ┻━┻ */
