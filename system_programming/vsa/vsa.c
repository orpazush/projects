/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review : Shachar Reshef									 *
 * 					Last update : 8.5.20									 *
 ****************************************************************************/

#include <assert.h>	/* assert */

#include "vsa.h"	

/* thank's to Omerika */
#define PADDING ((size_of_block % WORD) ? WORD - (size_of_block % WORD) : 0)
#define BLOCK_ALIGNED ((ssize_t)(size_of_block + PADDING))
#define NEXT_HEADER(x) ((header_t *)((size_t)x + HEADER_SPACE + x->size))

#define HEADER_SPACE (sizeof(header_t))
#define VSA_SPACE (sizeof(struct vsa))
#define WORD (sizeof(size_t))

struct vsa
{
	size_t end;
};

typedef struct header
{
	ssize_t size;

#ifndef NDEBUG
	size_t is_mine;
#endif

}header_t;


static header_t *NextFreeMD(vsa_t *segment, header_t *is_free); 
static void Defreg(vsa_t *segment, header_t *header);

vsa_t *VSAInit(void *segment, size_t segment_size)
{
	vsa_t *new = (vsa_t *)segment; 
	header_t *header = (header_t *)((size_t)segment + VSA_SPACE);

	assert(segment);
	
	new->end = (size_t)segment + segment_size;
	header->size = segment_size - VSA_SPACE - HEADER_SPACE;

#ifndef NDEBUG
	header->is_mine = 0xDABBAD00;
#endif

	return new;
}


void *VSAAlloc(vsa_t *segment, size_t size_of_block)
{
	header_t *header = (header_t *)((size_t)segment + VSA_SPACE);
	header_t *next_h = NULL;

	assert(segment);
	
	for (; (size_t)header < segment->end; 
		header = (header_t *)((size_t)header + HEADER_SPACE + BLOCK_ALIGNED))
	{		
		header = NextFreeMD(segment, header);
		if (NULL == header)	
		{
			return NULL;
		}
		Defreg(segment, header);
		next_h = (header_t *)((size_t)header + HEADER_SPACE + BLOCK_ALIGNED);
		
		if (header->size == BLOCK_ALIGNED 
		   || (header->size - HEADER_SPACE) == (size_t)BLOCK_ALIGNED)
		{
#ifndef NDEBUG
			header->is_mine = 0xDABBAD00;
#endif
			header->size *= -1;
			return (++header);			
		}
		else if (header->size > BLOCK_ALIGNED)
		{
			next_h->size = header->size - HEADER_SPACE - BLOCK_ALIGNED;
			header->size = -BLOCK_ALIGNED;
			
#ifndef NDEBUG
			header->is_mine = 0xDABBAD00;
#endif
			return (++header);
		}
	}

	return NULL;
}


void VSAFree(void *ptr)
{
	header_t *header = (header_t *)((size_t)ptr - HEADER_SPACE);

	assert(header->is_mine == 0xDABBAD00);

	if (NULL != ptr)
	{
	header->size *= -1;
#ifndef NDEBUG
			header->is_mine = 0xBAADF00D;
#endif
	}	
}


size_t VSALargestChunkAvailable(vsa_t *segment)
{
	ssize_t largest = 0;
	header_t *header = (header_t *)((size_t)segment + VSA_SPACE);

	assert(segment);

	for (; (size_t)header < segment->end; header = NEXT_HEADER(header))
	{
		header = NextFreeMD(segment, header);
		if (NULL == header)	
		{
			return largest;
		}
		Defreg(segment, header);
		largest = (largest < header->size) ? header->size : largest;
	}
	return largest;
}

/* this function should recieve only free 'header' (after 'NextFreeMD'..) */
static void Defreg(vsa_t *segment, header_t *to_defreg)
{
	header_t *header = NULL;

	assert(segment);
	assert(header);

	for (header = NEXT_HEADER(to_defreg); ((size_t)header < segment->end) 
		&& (0 < header->size); header = NEXT_HEADER(to_defreg)) 
	{
		to_defreg->size += (header->size + HEADER_SPACE);	
	}
}


static header_t *NextFreeMD(vsa_t *segment, header_t *is_free)
{
	for (; (size_t)is_free < segment->end;
		is_free = (header_t *)((size_t)is_free + HEADER_SPACE -is_free->size))
	{
		if (0 <= is_free->size)
		{	
			return is_free;
		}
	}
	return NULL;
}














