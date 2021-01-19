#include <stdio.h>
#include <assert.h> /* assert */
#include <limits.h> /* CHAR_BIT */

#include "bitarray.h"

/****************************************************************
*	functions to use on bitarray of 64 bits			*
*								*
*		orpaz houta					*	
*		code review by niz the wiz			*
*		1.4.2020					*
****************************************************************/

int main()
{
	bit_array_t il = 5;
	bit_array_t after_func = 0;
	char string_bin[65] = "thank you itzik";
	
	
	printf("befor:\n%s\n", BitArrToString(il, string_bin));

	after_func = BitArrSetAll(il);
	printf("after setall:\n%s\n", BitArrToString(after_func, string_bin));

	after_func = BitArrResetAll(il);
	printf("after resetall:\n%s\n", BitArrToString(after_func, string_bin));

	after_func = BitArrSetOn(il,2);
	printf("after seton:\n%s\n", BitArrToString(after_func, string_bin));

	after_func = BitArrSetOff(il,5);
	printf("after setoff:\n%s\n", BitArrToString(after_func, string_bin));

	after_func = BitArrSetBit(il, 1, 0);
	printf("after setbit:\n%s\n", BitArrToString(after_func, string_bin));

	after_func = BitArrFlip(il);
	printf("after flip:\n%s\n", BitArrToString(after_func, string_bin));

	after_func = BitArrFliptBit(il, 8);
	printf("after flipbit:\n%s\n", BitArrToString(after_func, string_bin));

	after_func = BitArrRotR(il, 8);
	printf("after rotr:\n%s\n", BitArrToString(after_func, string_bin));

	after_func = BitArrRotL(il, 8);
	printf("after rotl:\n%s\n", BitArrToString(after_func, string_bin));

	printf("counton: %ld\n", BitArrCountOn(il));

	printf("counton using lut: %ld\n", BitArrCountOnLUT(il));

	printf("countoff: %ld\n", BitArrCountOff(il));
	
	printf("get value: %d\n", BitArrGetVal(il, 9));
	
	printf("befor mirror:\n%s\n", BitArrToString(il, string_bin));

	after_func = BitArrMirror(il);
	printf("after mirror:\n%s\n", BitArrToString(after_func, string_bin));

	after_func = BitArrMirrorLUT(il);
	printf("after mirror using lut:\n%s\n", BitArrToString(after_func, string_bin));

	return 0;
}
