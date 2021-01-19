/*****************************************************************************
 * 					written by: Orpaz Houta									 *
 * 					review: Shachar Reshef									 *
 * 					Last update: 8.5.20										 *
 ****************************************************************************/
#include <unistd.h>	/* size_t */

#ifndef __VSA_H__ 
#define __VSA_H__ 

typedef struct vsa vsa_t;
	
/*****************************************************************************
 * Function: VSAInit														 *
 * --------------------------------------------------------------------------*
 * gets an area of allocated memory pointed by 'segment' of size 			 * 
 * 'segment_size' and creates an VSA to manage this area					 *
 * NOTE - not all the given memory will be available to the user after it	 *
 *																			 *
 * segment: void *, pointer to the allocated memory							 *
 * segment_size: size_t, the size of the allocated memory segment			 *
 *																			 *
 * returns: vsa_t *, pointer to the new VSA									 *
 *																			 *
 * The function in O(1) complications. 										 *
 ****************************************************************************/
vsa_t *VSAInit(void *segment, size_t segment_size);


/*****************************************************************************
 * Function: VSAAlloc														 *
 * --------------------------------------------------------------------------*
 * provides the user a 'size_of_block' bytes of memory						 *
 *																			 *
 * segment: vsa_t *, pointer to the allocated memory						 *
 * size_of_block: size_t, number of wanted bytes							 *
 *																			 *
 * returns: void *, pointer to the allocated memory or NULL in case			 *
 *					of not enugh memory										 *
 *																			 *
 * The function in O(n) complications. 										 *
 ****************************************************************************/
void *VSAAlloc(vsa_t *segment, size_t size_of_block);


/*****************************************************************************
 * Function: VSAFree														 *
 * --------------------------------------------------------------------------*
 * frees the memory space pointed to by 'ptr'								 *
 * NOTE - if the 'ptr' wasn't returned by a previous VSAAlloc()				 *
 *	      or it has already been freed, undefined behavior occurs.			 *
 *		- if the function recieves a NULL as 'ptr', nothing will happen		 *
 *																			 *
 * ptr: void *, pointer to the memory to free								 *
 *																			 *
 * returns: NONE															 *
 *																			 *
 * The function in O(1) complications. 										 *
 ****************************************************************************/
void VSAFree(void *ptr);


/*****************************************************************************
 * Function: VSALargestChunkAvailable 										 *
 * ------------------------------------------------------------------------- *
 * segment: vsa_t *, pointer to the allocated memory						 *
 *																			 *
 * returns: size_t, the biggest number of bytes available at the moment		 *
 *																			 *
 * The function in O(n) complications.										 *
 ****************************************************************************/
size_t VSALargestChunkAvailable(vsa_t *segment);

	
#endif /* ifdef __VSA_H__ */ 
