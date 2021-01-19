/********************************************************
*		implement macro max			*
*		orpaz houta				*
*		Reviewer‎‏ omer hefetz			*	
*		Date: 26.03.2019, 17:00                 *
*						        *
********************************************************/

#include<stdio.h> /* printf */


/* macro to return the number of bytes that th variable takes */

#define SIZEOF_VAR(var) ((char *)(&var+1)-(char *)(&var))
 
int main()
{
	struct x
{
	int i;
	char c;
	double d;
	short s;
}card;

	printf("the size of variable a in bytes = %ld\n",SIZEOF_VAR(card));
	
	return 0;
}

