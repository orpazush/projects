/****************************************************************************
* 					written by : orpaz houta								*
* 					review : Yonathan Bardugo								*
*					Last update : 23.5.20 									*
****************************************************************************/
#include <stdio.h>	/* printf*/

#include "fsm.h"

#define FAIL (1) 		/* status */
#define SUCCESS (0)		/* status */

int SanityTest(void);

int main()
{
	printf("****************START TESTING ***********************\n");
	SanityTest() ? printf("test failed\n") : printf("all tests succeeded!:)\n");
	printf("****************END TESTING ***********************\n");

	return 0;
}

int SanityTest(void)
{
	int status = SUCCESS;
	char *addtest = "9+9+254+3+1";
	char *subtest = "634-21-10";
	char *multest = "300/25*-12";
	char *divtest = "2/10+10";
	char *partest = "(9+9)*3+1";
	char *unarytest = "25*-12+40";
	char *extrplustest = "9++8++-12";
	double result = 0;

	Calculate(&result, addtest);
	if(result != 276)
	{
		status = FAIL;
		printf("Add FAIL\n");
	}
	Calculate(&result, subtest);
	if(result != 603)
	{
		status = FAIL;
		printf("Sub FAIL\n");
	}

	Calculate(&result, multest);
	if(result != -144)
	{
		status = FAIL;
		printf("multiply FAIL\n");
	}

	Calculate(&result, divtest);
	if(result != 10.2)
	{
		status = FAIL;
		printf("divisible FAIL\n");
	}

	Calculate(&result, partest);
	if(result != 55)
	{
		status = FAIL;
		printf("parenthes FAIL\n");
	}

	Calculate(&result, unarytest);
	if(result != -260)
	{
		status = FAIL;
		printf("unary FAIL\n");
	}
	Calculate(&result, extrplustest);
	if(result != 5)
	{
		status = FAIL;
		printf("tod FAIL\n");
	}

	return status;
}
