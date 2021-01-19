#include <stdio.h>

#include "atoi.h"

/****************************************************************
*		implement itoa and atoi				*
*		orpaz houta					*	
*		cr by malu gerkol				*
*		27.3.2020					*
****************************************************************/

#define ASCII_ZERO (48)		/* to convert the ascii value to his int value */
#define ASCII_NINE (57) 	/* to close the area for only ascii numbers */
#define DECIMAL_BASE (10) 	/* to convert to decimal */

char base_index[] = {'0','1','2','3','4','5','6','7','8','9','a','b',
			'c','d','e','f','g','h','i','j','k','l','m','n',
			'o','p','q','r','s','t','u','v','w','x','y','z'};

int Atoi(const char *string_number)
{
	int number_value = 0, char_number = 0;
	int i = 0;
	
	if(string_number[0] == '-')
	{
		i++;		
	}

	for(; string_number[i] && (string_number[i] < ASCII_NINE); i++)
	{
		number_value *= DECIMAL_BASE;
		char_number = string_number[i] - ASCII_ZERO;
		number_value += char_number;
	}
	if(string_number[0] == '-')
	{
		number_value = (-number_value);		
	}

	return number_value;
}

char *ItoaDecimal(int number, char *return_string)
{
	int size = 0, tmp_number = 0; 
	int i = 0, if_minus = 0;

	if(number < 0)
	{
		return_string[0] = '-';
		if_minus = 1;
		number = -number;
	}
	
	tmp_number = number;

	for(size = 0; tmp_number > 0; tmp_number /= DECIMAL_BASE, size ++);
	
	size -= 1; 

	for(i = (size + if_minus); i >= if_minus; number /= DECIMAL_BASE, --i)
	{
		tmp_number = number % DECIMAL_BASE;
		tmp_number += ASCII_ZERO;
		return_string[i] = tmp_number;
	}
	return_string[size + 1] = '\0';
	
	return return_string;
}

char *Itoa(int number, char *return_string, int base)
{
	int size = 0, tmp_number = 0, i = 0; 
	
	if(base == 10)
	{
		return ItoaDecimal(number, return_string);
	}

	else
	{
		tmp_number = number;

		for(size = 0; tmp_number > 0; tmp_number /= base, size ++);
		
		for(i = (size - 1); i >= 0; number /= base, --i)
		{
			tmp_number = number % base;
			return_string[i] = base_index[tmp_number];
		}
		return_string[size] = '\0';
	}

	return return_string;
}




