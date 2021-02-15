/****************************************************************************
 * 						written by : orpaz houta							*
 *						review : Chanan Komer								*
 * 						Last update : 25.4.20								*
 ***************************************************************************/
#include <stdio.h>	/* printf */

#include "uid.h"

#define FAIL (1) 		/* status */
#define SUCCESS (0)		/* status */

int SanityTest();

int main() 
{ 
	printf("****************START TESTING***********************\n");
	SanityTest() ? printf("test failed\n") : printf("all tests succeeded!:)\n");
	printf("*****************END TESTING************************\n");

	return 0; 
} 
 
int SanityTest()
{
	typedef struct settlement
	{
		ilrd_uid_t uid;
		char* name;
	}settlement_t;

	int status = SUCCESS;
	size_t i = 0;
	char *settlements[] = {"ateret", "talmon", "dolev", "ofra", "psagot"};
	settlement_t binyamin[100];
	
	for (i = 0; sizeof(settlements)/sizeof(settlements[0]) > i ; ++i)
	{
		binyamin[i].name = settlements[i];
		binyamin[i].uid = UIDCreate();
	}
	for (i = 0; i < 5; ++i)
	{
		if (UIDIsSame(binyamin[i].uid, g_bad_ilrd_uid))
		{
			status = FAIL;
			printf("UIDCreate FAIL\n");
		}
	}
	binyamin[4].uid = g_bad_ilrd_uid;

	for (i = 0; i < 6 && !UIDIsSame(binyamin[i].uid, g_bad_ilrd_uid); ++i);

	if (6 == i)
	{
		status = FAIL;			
		printf("UIDIsSame FAIL\n");
	}

	if (4 != i)
	{
		status = FAIL;			
		printf("UIDIsSame FAIL\n");
	}

	return status;
}














