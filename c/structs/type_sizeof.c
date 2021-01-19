/****************************************************************
*			implement macro max			*
*			orpaz houta				*
*			Reviewer‎‏ omer hefetz			*	
*			26.03.2019                		*
*							        *
****************************************************************/

#include<stdio.h>

/* macro that recieve variable and return the number of bytes it uses */

#define SIZEOF_TYPE(data_type) ((char*)((data_type*)2 + 1) - (char*)2)

int main()
{
	printf("the type size is %ld\n", SIZEOF_TYPE(double));

	return 0;
}

