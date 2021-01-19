#include <stdio.h>

#include "atoi.h"

/****************************************************************
*		implement itoa and atoi				*
*		orpaz houta					*	
*		cr by malu gerkol				*
*		27.3.2020					*
****************************************************************/

#define MAX_STRING 100

int main()
{
	int num = 16;
	char string[MAX_STRING];
	char *string_atoi = "-123hek456";

	printf("%s\n", ItoaDecimal(num, string));
	printf("%s\n", Itoa(num, string, 2));
	printf("%d\n", Atoi(string_atoi));

	return 0;
}

