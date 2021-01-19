#include <stdio.h> /* printf */

/****************************************************************
*								*
*			little or big endian check		*
*	orpaz houta						*
*	30/3/2020						*
*	reviewd by malu gerkol					*
*								*
****************************************************************/

int main()
{
	unsigned int any_small_number = 10;
	char *endian = (char *)&any_small_number;

	if(*endian)
	{
		printf("this is a little endian\n");
		printf("%d\n", *endian);
	}
	else
	{
		printf("this is a big endian\n");
	}

	return 0;
}
