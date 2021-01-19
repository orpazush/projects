#include<stdio.h>

int IsPalindrom(const char *str)
{
	int start = 0, end = 0;
	for(end=0; str[end]; end++);
	while(start < end)
	{
		if(str[start] != str[end - 1])
		{
			return 1;
		}		
		++start; 
		--end;
	}
	return 0;	
}

int main()
{
	char str[] = "abc&**&cb";
	printf("%d\n", IsPalindrom(str));
	return 0;
}

