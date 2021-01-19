#include <stdio.h> 

#include "mem.h"

/****************************************************************
*	implementation of memset, memmove & memcpy		*
*		orpaz houta					*	
*		cr by malu gerkol				*
*		31.3.2020					*
****************************************************************/

int main()
{
	char str1[] = "i can't do this anymore";
	char str2[] = "please make it stop";
	int arr1[] = {1,5,8,9,6,5,4,2,8,6,5,6,5,3};
	int arr2[] = {20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20};

	MemSet(str1 + 2, '.', 18);
	printf("%s\n", str1);
	printf("%p\n", str1);
	MemCpy(str2, str1, 9);
	printf("%s\n", str2);
	printf("%s\n", str1);
	MemMove(str2, str1, 17);
	printf("%s\n", str2);
	MemSet(arr1 + 3, 0, (sizeof(int) * 16));
	PrintArray(arr1, 20);
	MemMove(arr1, arr2, 6);
	PrintArray(arr1, sizeof(arr1)/sizeof(arr1[0]));

	return 0;
}

