#include <stdio.h>

/********************************************************
*	comparison of values within multiple arrays	*
*		orpaz houta				*
*		code review by malu gerkol		*	
*		31.03.2020				*
*							*
********************************************************/

# define ascii 256

void ThreeCharArray(char arr1[], char arr2[], char arr3[],
			 size_t len_arr1, size_t len_arr2, size_t len_arr3)
{
	unsigned int ascii_table[ascii];
	unsigned int i = 0;
	unsigned int value_exist = 0, exist_in_two = 0, in_two_no_three = 0;

	for(i = 0; i < len_arr1; i++)
	{
		value_exist = (unsigned int)arr1[i];
		ascii_table[value_exist] = 1;
	}	
	
	for(i = 0; i < len_arr2; i++)
	{
		exist_in_two = (unsigned int)arr2[i];	
	
		if(ascii_table[exist_in_two] == 1)
		{
			ascii_table[exist_in_two] = 2;
		}
	}
	
	for(i = 0; i < len_arr3; i++)
	{
		in_two_no_three = (unsigned int)arr3[i];
		
		if(ascii_table[in_two_no_three] == 2)
		{
			ascii_table[in_two_no_three] = 0;
		}
	}
	
	for(i = 0; i < ascii; i++)
	{ 
		if(ascii_table[i] == 2)
		{
			printf("%c,",(char)i);
		}
	}
	printf("\n");
}

int main()
{
	char arr1[] = {'a','b','c','d','e','f','g','h','i','j','k'};
	char arr2[] = {'a','b','c','d','e','l','m','n','o','p','q'};
	char arr3[] = {'a','c','f','g','h','i','j','k'};
	
	ThreeCharArray(arr1, arr2, arr3, 11, 11, 8);

	return 0;
}	
