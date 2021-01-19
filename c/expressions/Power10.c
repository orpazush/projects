#include<stdio.h>

float pow10(int n)
{
	int i;
	float res=1;
	if (n<0)
	{
		n = -n;
		for(i=0; i<n; i++)
		{
			res *= 1.0/10;
		}
	}
	else
	{
		for(i=0; i<n; i++)
		{
			res *= 10;
		}
	}
	return res;
}
int main ()
{
	int n;
	scanf("%d", &n);
	printf("%f",pow10(n));
	return 0;
}
