#include <stdio.h>

size_t CalculStr(char *str1, char *str2)
{
	int i = 0;
	int int_value = 0;
	size_t number1 = 0, number2 = 0;
	size_t sum = 0;

	for(i = 0; str1[i]; ++i)
	{
		int_value = str1[i] - '0';	
		number1 *= 10;
		number1 += int_value;
	}

	for(i = 0; str2[i]; ++i)
	{
		int_value = str2[i] - '0';	
		number2 *= 10;
		number2 += int_value;
	}
	
	sum = number1 + number2;

	return sum;
}
	
int main ()
{
	char *str1 = "89545";
	char *str2 = "15484556";
	printf("%lu\n", CalculStr(str1, str2));
}
