#include <stdio.h>
#include "BitWiseEx.h"

/**********************************************************************
	
			tricks with bits
	orpaz houta
	25/3/2020
	reviewd by Tali Raphael

**********************************************************************/

#define MASK_SET 1

/*************************1************************/
long PowTwo(unsigned int x, unsigned int y)
{
	long result;

	return result = x << y;
}

/*************************2************************/
int IsPowLoop(unsigned int n)
{
	unsigned int i = 1;

	while(i < 32)
	{
		if(n == i)
		{
			return 1;	
		}
		i <<= MASK_SET;
	}
	
	return 0;
}

/*************************3*************************/
int IsPowTwo(unsigned int n)
{
	return n && (!(n & (n - MASK_SET)));
}

/************************4**************************/
int AddOne(int n)
{
	int i;

	for(i = 0; n & 1; i++)
	{
		n >>= MASK_SET;
	}
	n |= 1;
	n <<= i;
	
	return n;
}	

/************************5**************************/
void SetOfThree(int arr[], int arr_size)
{
	int count = 0, tmp = 0;
	int i = 0;

	for(i = 0; i < arr_size; i++)
	{
		tmp = arr[i];
		
		while(tmp)
		{
			count += tmp & 1;
			tmp >>= 1;
		}

		if(count == 3)
		{
			printf("%d, ", arr[i]);
		}
	}	
}

/*************************6*************************/
unsigned int ByteMirrorLoop(unsigned int num) 
{  
	unsigned int mirror = 0, i = 0; 

	for (i = 0; i < 8; i++) 
	{
		if(num & (1 << i)) 
		{
			mirror |= (1 << (7 - i));
		}
	}

	return mirror; 
} 

/*************************7*************************/ 
unsigned int ByteMirror(unsigned int num)
{
    num = (num & 0xF0F0F0F0) >> 4  | (num & 0x0F0F0F0F) << 4;
    num = (num & 0xCCCCCCCC) >> 2  | (num & 0x33333333) << 2;
    num = (num & 0xAAAAAAAA) >> 1  | (num & 0x55555555) << 1;

    return num;
}

/*************************8*************************/ 
int SixAndTwoOn(unsigned char chr)
{
	return (chr & (1 << 5)) && (chr & (1 << 1));
}

/*************************9*************************/
int SixOrTwoOn(unsigned char chr)
{
	return (chr & (1 << 5)) || (chr & (1 << 1));
}

/*************************10*************************/
int SwapBits(int chr)
{
	unsigned char bit_3 = 0, bit_5 = 0;
	unsigned char xor_bits = 0, new_chr= 0;

	bit_3 = (chr >> 2) & 1; 
	bit_5 = (chr >> 4) & 1;	
	xor_bits = bit_3 ^ bit_5;
	new_chr = chr ^ (xor_bits << 2 | xor_bits << 4);

	return new_chr;
}

/***********************11***************************/
int DivisibleBySixteen(int n)
{
	return num & FFFFFFF0;
}

/************************12**************************/
void SwapVariables(int *a, int *b)
{
	*a ^= *b;
	*b ^= *a; 
	*a ^= *b;
}

/************************13**************************/
int SetBitsLoop(int n)
{
	int i = 0, on = 0;

	for(i = 0; i < 32; i++)
	{
		on += (n & (1 << i))
	}

	return on;
}

/*************************14*************************/
int SetBits(int n)
{
	int num_bits = 0;

	n = n - ((n >> 1) & 0x55555555);
	n = (n & 0x33333333) + ((n >> 2) & 0x33333333);
	n = ((n + (n >> 4)) & 0x0F0F0F0F);
	num_bits = (n*(0x01010101))>>24;

	return num_bits;
}

/*************************15*************************/
int FloatBitwise(int a, int loc)   
{
    int buf = a & 1 << loc;

    if (buf == 0) return 0;

    else return 1; 
}


