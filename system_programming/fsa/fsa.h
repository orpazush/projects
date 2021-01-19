/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review : Omer Hefetz									 *
 * 					Last update : 4.5.20									 *
 * ------------------------------------------------------------------------- *
 *					header file to prog fsa									 *
 ****************************************************************************/

#include <stddef.h> /* size_t */

#ifndef __FSA_H__ 
#define __FSA_H__ 

typedef struct fsa fsa_t;

	
/*****************************************************************************
 * Function : FSAInit														 * 
 * ------------------------------------------------------------------------- *
 * gets an area of allocated memory pointed by 'segment' and initiates the	 * 
 * FSA to manage this area as fixed size chuncks of memory of 'size_of_block'*
 * bytes.																	 *
 * NOTE - it is the user's responsability to give enough memory to the FSA,	 *
 *		  use 'FSASuggestSize' to get the optimal 'capacity' to your needs.	 *
 * 		- not all the given memory will be available to the user after it.	 *
 *																			 *
 * segment : void *, pointer to the allocated memory.						 *
 * capacity : size_t, the size of the allocated memory.						 *
 * size_of_block : size_t, the chosen size of fixed blocks.					 *
 *																			 *
 * returns : fsa_t *, pointer to the new FSA.								 *
 *																			 *
 * The function in O(n) complications. 										 *
 *****************************************************************************/
fsa_t *FSAInit(void *segment, size_t capacity, size_t size_of_block);


/*****************************************************************************
 * Function : FSAAlloc 														 *
 * ------------------------------------------------------------------------- *
 * allocates a block of (fixed size) memory to the user use. 				 *
 *																			 *
 * segment : fsa_t *, pointer to the FSA memory area.						 *
 *																			 *
 * returns : void *, pointer to the allocated block or NULL in case of lack. *
 * 			 of memory.														 *
 *																			 *
 * The function in O(1) complications.										 *
 *****************************************************************************/
void *FSAAlloc(fsa_t *segment);


/*****************************************************************************
 * Function : FSAFree 														 *
 * ------------------------------------------------------------------------- *
 * free block of memory pointed by 'ptr' and add it to the free memory in	 * 
 * the FSA.																	 *
 * NOTE - if the 'ptr' wasn't returned by a previous FSAAlloc()				 *
 *	      or it has already been freed, undefined behavior occurs.			 *
 *		- if the function recieves a NULL as 'ptr', nothing will happen.	 *
 *																			 *
 * ptr : void *, pointer to the block to free. 								 *
 *																			 *
 * returns : NONE. 															 *
 *																			 *
 * The function in O(1) complications. 										 *
 ****************************************************************************/
void FSAFree(void *ptr);


/*****************************************************************************
 * Function : FSACountFree 													 *
 * ------------------------------------------------------------------------- *
 * segment : fsa_t *, pointer to the FSA.									 *
 *																			 *
 * returns : size_t, the number of free blocks in the given 'segment'.		 *
 *																			 *
 * The function in O(n) complications.										 *
 *****************************************************************************/
size_t FSACountFree(const fsa_t *segment);


/*****************************************************************************
 * Function : FSASuggestSize 												 *
 * ------------------------------------------------------------------------- *
 * calculate the optimal size needed for the FSA to manage the wanted		 *
 * 'number_of_blocks' of the wanted 'size_of_block'.						 *
 *																			 *
 * size_of_block : size_t, the wanted size of blocks.	 					 *
 * number_of_blocks : size_t, the wanted number of fixed blocks. 			 *
 *																			 *
 * returns : size_t, the optimal size needed to alloc for the FSA.			 *
 *																			 *
 * The function in O(1) complications. 										 *
 *****************************************************************************/
size_t FSASuggestSize(size_t number_of_blocks, size_t size_of_block);

	
#endif /* ifdef __FSA_H__ */ 
