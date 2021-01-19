#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void RmSpaces(char *str)
{
	int i = 0, j = 0;
	int length = 0;
	char *str_dup = NULL;

	for(length = 0; str[length]; ++length);
	str_dup = strdup(str);
	
	while (str_dup[j] == ' ' || str_dup[j] == '\t')
	{
		j++;
	}

	while (str_dup[length - 1] == ' ' || str_dup[length - 1] == '\t')
	{
		--length;
	}

	while(str_dup[j] < str_dup[length])
	{
		if (str_dup[j] == ' ')
		{
			if (str_dup[j + 1] == ' ');
			++j;
		}
		str[i] = str_dup[j];
		++i;
		++j;
	}

	str[i] = '\0';	
}

int main()
{
	char str[]= "why  there i  s  so many     spases here    ?";
 	printf("%lu", strlen(str));
	
	RmSpaces(str);

	printf("%s\n", str);
	
	return 0;
}
