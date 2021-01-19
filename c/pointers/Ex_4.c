#include <stdio.h>

void SwapPointers(int **ppa, int **ppb)
{
    	int *temp = NULL;
	temp = *ppa;
   	*ppa = *ppb;
  	*ppb = temp;
}

int main()
{
	int a = 1, b = 5;
	int *pa = &a;
	int *pb = &b;
	SwapPointers(&pa, &pb);
	printf("%d, %d\n", *pa, *pb);

	return 0;
}
