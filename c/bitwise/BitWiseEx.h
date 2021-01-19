#include"BitWiseEx.c"

/**********************************************************************
	
			tricks with bits
	orpaz houta
	25/3/2020
	reviewd by Tali Raphael

**********************************************************************/

/* #1 return x*2^y */
long PowTwo(unsigned int x, unsigned int y); 		   

/* #2 recieve unsigned int and return 0 if it is power of two */
int IsPowLoop(unsigned int n);      

/* #3 the same as #2 without loop */
int IsPowTwo(unsigned int n);		     

/* #4 recieve an integer and return the namber in addition of 1 */
int AddOne(int n);	

/* #5 recieve an array of ints and prints the elements with 3 set bits */
void SetOfThree(int arr[], int arr_size);

/* #6 recieve an unsigned integer and return the value after reverse its bits */
unsigned int ByteMirrorLoop(unsigned int num); 		    

/* #7 same as #6 without loop */
unsigned int ByteMirror(unsigned int num);     

/* #8 recieve an unsigned char and return 0, if bits 6 & 2 are on */
int SixAndTwoOn(unsigned char chr);	      

/* #9 recieve an unsigned char and return 0, if bits 6 or 2 is on */
int SixOrTwoOn(unsigned char chr);		 

/* #10 recieve an int and return the value after swap its bits 3 & 5 */
int SwapBits(int chr);				       

/* #11 recieve a number and return the closest number divisible in 16 */
int DivisibleBySixteen(int n); 

/* #12 swaps between two variables */
void SwapVariables(int *a, int *b);	                

/* #13 recieve an int and returns the number of its set bits */
int SetBitsLoop(int n);			 

/* #14 recieve an int and returns the number of set bits without loop */
int SetBits(int n);

/* #15 recieve float number and print its bits */	   
int FloatBitwise(int a, int loc);	   

