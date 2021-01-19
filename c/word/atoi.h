#ifndef __ATOI_H__
#define __ATOI_H__

/****************************************************************
*		implement itoa and atoi				*
*		orpaz houta					*	
*		cr by malu gerkol				*
*		31.3.2020					*
****************************************************************/


/* implementation of the function atoi which converts a string to an int  */

int Atoi(const char *string_number);


/* implementation of the function itoa which recieves an int converts him to any
base from 2 to 36 and returns the result in string by pointer 'return_string' */

char *Itoa(int number, char *return_string, int base);


/* the same us Itoa but converts only to decimal base */

char *ItoaDecimal(int number, char *return_string);

#endif

