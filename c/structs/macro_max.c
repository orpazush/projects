#include <stdio.h> 

/********************************************************
*		implement macro max			*
*		orpaz houta				*
*		code review by omer hefetz		*	
*		28.03.2020				*
*							*
********************************************************/

/* MACRO that give the bigger number between 2 numbers */
#define MAX2(a, b) (((a) > (b)) ? (a) : (b))

/* MACRO that give the bigger number between 3 numbers */
#define MAX3(a, b, c) (MAX2(MAX2((a), (b)), (c)))


int main()
{
	printf("%f\n",MAX2(10.1,11));
	printf("\n%d\n",MAX3(584,9,-8));
	
	return 0;
}














