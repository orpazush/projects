#include <stdio.h>
#include "BitWiseEx.h" 

/**********************************************************************
	
			tricks with bits
	orpaz houta
	25/3/2020
	reviewd by Tali Raphael

**********************************************************************/

int main()
{
	unsigned int x = 16;
	unsigned int y = 3;
	int swap1 = 8, swap2 = 42;
	int *ptr_x = NULL, *ptr_y = NULL;
	int arr[] = {2,5,6,7,8,9,25,38,95};

	ptr_x  = &swap1;
	ptr_y = &swap2;
	
	printf("%ld\n", PowTwo(x,y));
	printf("%d\n", IsPowLoop(x));
	printf("%d\n", IsPowTwo(x));
	printf("%d\n", AddOne(20));
	SetOfThree(arr,9);
	printf("%u\n", ByteMirrorLoop(58));
	printf("%u\n", ByteMirror(58));
	printf("%d\n", SixAndTwoOn(32));
	printf("%d\n", SixOrTwoOn(32));
	printf("%d\n", SwapBits('c'));
	printf("%d\n", DivisibleBySixteen(49));
	SwapVariables(ptr_x, ptr_y);
	printf("%d, %d\n",swap1, swap2);
	printf("%d\n", SetBitsLoop(21));
	printf("%d\n", SetBits(7));	

	return 0;
}

