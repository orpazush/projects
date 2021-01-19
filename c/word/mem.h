#ifndef __MEM_H__
#define __MEM_H__

/****************************************************************
*	implementation of memset, memmove & memcpy		*
*		orpaz houta					*	
*		cr by malu gerkol				*
*		31.3.2020					*
****************************************************************/

/* implementation of memset - a function that fills  the  first 
   'bytes_to_fill' of the memory area pointed to by 'memory_to_fill' with
    the 'constant' and  returns a pointer to the 'memory_to_fill'.
*/
void *MemSet(void *memory_to_fill, int constant, size_t bytes_to_fill);


/* implementation of memcpy - a function that copy  the  first 
   'bytes_to_copy' from 'source' to 'dest' and  returns a pointer to dest.
    note - MemCpy doesn't deal with cases of over laps.
*/
void *MemCpy(void *dest, const void *source, size_t bytes_to_copy);


/*  implementation of MemMove - doing the same as MemCpy but also
    deals with cases of over laps. 
*/
void *MemMove(void *dest, const void *source, size_t bytes_to_copy);


/* prints arrays */
void PrintArray(int array[], int n);

#endif /*MEM_H*/
