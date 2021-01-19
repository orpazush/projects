/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review : Omer Hefetz									 *
 * 					Last update : 4.5.20									 *
 ****************************************************************************/

#include <assert.h>	/* assert */
#include "fsa.h"


/* thank's to Omerika😘️ */
#define FIRST_FREE_MANAGER ((manager_t *)(segment->first_free - MANAGER_SPACE))
#define NEXT_MANAGER ((manager_t *)(manager->next_free - MANAGER_SPACE))
#define FULL_BLOCK (MANAGER_SPACE + ((size_of_block % WORD) \
					 ? size_of_block + WORD - (size_of_block % WORD) \
					 : size_of_block))

#define MANAGER_SPACE (sizeof(manager_t))
#define FSA_SPACE (sizeof(struct fsa))
#define WORD (sizeof(size_t))

struct fsa
{
	size_t first_free;
};

typedef struct manager
{
	size_t next_free;

#ifndef NDEBUG
	size_t is_mine;
#endif

}manager_t;


fsa_t *FSAInit(void *segment, size_t capacity, size_t size_of_block)
{
	fsa_t *new = (fsa_t *)segment;
	manager_t *manager = (manager_t *)((size_t)segment + FSA_SPACE); 
	size_t next = (size_t)manager + MANAGER_SPACE;

	assert(segment);

	new->first_free = next;

	for (; ((size_t)manager + FULL_BLOCK) < ((size_t)segment + capacity);
		manager = NEXT_MANAGER)
	{
		next += FULL_BLOCK;
		manager->next_free = next;

#ifndef NDEBUG
		manager->is_mine = 0xDABBAD00;
#endif
		
	}
	manager->next_free = 0;

	return new;
}


void *FSAAlloc(fsa_t *segment)
{
	size_t *alloc_block = (size_t *)segment->first_free;
	manager_t *manager = FIRST_FREE_MANAGER;

	assert(segment);

	if (0 == segment->first_free)
	{
		return NULL;
	}
	segment->first_free = manager->next_free;
	manager->next_free = (size_t)segment;

#ifndef NDEBUG
		manager->is_mine = 0xDABBAD00;
#endif

	return alloc_block;
}


void FSAFree(void *ptr)
{
	manager_t *manager = (manager_t *)((size_t)ptr - MANAGER_SPACE);
	fsa_t *fsa = (fsa_t *)manager->next_free;

	assert(manager->is_mine == 0xDABBAD00);

	if (NULL != ptr)
	{
	manager->next_free = fsa->first_free;

#ifndef NDEBUG
		manager->is_mine = 0XBADCAFFE;
#endif

	fsa->first_free = (size_t)ptr;
	}
}


size_t FSACountFree(const fsa_t *segment)
{
	size_t count = 0;
	manager_t *manager = FIRST_FREE_MANAGER;

	assert(segment);

	if (0 == segment->first_free)
	{
		return count;
	}
	for (count = 1;	manager->next_free != 0; manager = NEXT_MANAGER, ++count)
		;

	return count;
}


size_t FSASuggestSize(size_t number_of_blocks, size_t size_of_block)
{
	return (FSA_SPACE + (number_of_blocks * FULL_BLOCK));
}

















