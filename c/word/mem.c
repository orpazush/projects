#include <stdio.h>

#include "mem.h"

/****************************************************************
*	implementation of memset, memmove & memcpy		*
*		orpaz houta					*	
*		cr by malu gerkol				*
*		31.3.2020					*
****************************************************************/

#define BIT_MASK 0xff
#define WORD_SIZE 8

void *MemSet(void *memory_to_fill, int constant, size_t bytes_to_fill)
{	
	char *cast = (char *)memory_to_fill;
	size_t adress = (size_t)memory_to_fill;
	size_t word_chunk = 0;
	size_t *cast_size_t = 0;
	
	while((adress++ % WORD_SIZE) && (bytes_to_fill--))
	{
		*cast++ = constant;
	}

	word_chunk = constant & BIT_MASK;
	word_chunk |= word_chunk << 8;
	word_chunk |= word_chunk << 16;
	word_chunk |= word_chunk << 32;

	cast_size_t = (size_t *)cast;

	while(bytes_to_fill / WORD_SIZE)
	{ 
		*cast_size_t++ = word_chunk;
		bytes_to_fill -= WORD_SIZE;
	}
	
	cast = (char *)cast_size_t;

	while(bytes_to_fill--)
	{
		*cast++ = constant;
	}

 	return memory_to_fill;
}

void *MemCpy(void *dest, const void *source, size_t bytes_to_copy)
{
	size_t adress = (size_t)dest;
	char *cast_dest = (char *)dest;
	char *cast_source = (char *)source;
	size_t *size_t_dest = 0;
	size_t *size_t_source = 0;
	
	while((adress++ % WORD_SIZE) && bytes_to_copy--)
	{
		*cast_dest++ = *cast_source++;
	} 
	
	size_t_dest = (size_t *)cast_dest;
	size_t_source = (size_t *)cast_source;

	while(bytes_to_copy / WORD_SIZE)
	{
		*size_t_dest++ = *size_t_source++;
		bytes_to_copy -= WORD_SIZE;
	}
	
	cast_dest = (char *)size_t_dest;
	cast_source = (char *)size_t_source;

	while(bytes_to_copy--)
	{
		*cast_dest++ = *cast_source++;
	}

	return dest;
}

void *MemMove(void *dest, const void *source, size_t bytes_to_copy)
{
	char *cast_dest = (char *)dest;
	char *cast_source = (char *)source;
	size_t *size_t_dest = 0;
	size_t *size_t_source = 0;
	
	if(source < dest)
	{
		cast_dest += bytes_to_copy;
		cast_source += bytes_to_copy;

		while(--bytes_to_copy % WORD_SIZE)
		{
			*cast_dest-- = *cast_source--;
		}

		size_t_dest = (size_t *)dest;
		size_t_source = (size_t *)source;
		
		while(bytes_to_copy)
		{
			size_t_dest--;
			size_t_source--;
			*size_t_dest = *size_t_source;
			bytes_to_copy -= WORD_SIZE;
		}		
	}

	else
	{
		dest = MemCpy(dest, source, bytes_to_copy);
	}

	return dest;
}

void PrintArray(int array[], int n)
{
	int i;

	for(i = 0; i < n; i++)
	{
		printf("%d,", array[i]);
	}

	printf("\n");		
}

