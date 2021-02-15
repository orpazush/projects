/****************************************************************************
 * 						written by : orpaz houta							*
 *						review : Chanan Komer								*
 * 						Last update : 25.4.20								*
 ***************************************************************************/

#include <unistd.h> /* getpid */

#include "uid.h"

ilrd_uid_t g_bad_ilrd_uid = {0, 0, 0};

ilrd_uid_t UIDCreate(void)
{
	ilrd_uid_t new = {0, 0, 0};
	static size_t counter = 0;

	new.counter = counter;
	new.pid = getpid();
	new.time = time(NULL);

	++counter;

	return new;
}

int UIDIsSame(ilrd_uid_t uid1, ilrd_uid_t uid2)
{
    return (uid1.counter == uid2.counter 
            && uid1.pid  == uid2.pid 
            && uid1.time == uid2.time);
}

