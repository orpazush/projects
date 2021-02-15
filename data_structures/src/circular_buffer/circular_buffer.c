/****************************************************************************
 * 					written by : orpaz houta								*
 * 					review : yana Gorikhovski								*
 *					Last update : 14.4.20 									*
 ***************************************************************************/

#include <unistd.h>	/* ssize_t */
#include <errno.h>	/* errno */
#include <malloc.h>	/* malloc */
#include <assert.h>	/* assert */

#include "circular_buffer.h"

struct buffer
{
	size_t front;
	size_t size;
	size_t capacity;
	char array[1];
};

#define ERROR (-1)

buffer_t *BufCreate(size_t capacity)
{
	buffer_t *buffer = (buffer_t *)malloc
								(sizeof(buffer_t) + sizeof(char) * capacity);

	if (!buffer)
	{
#ifndef NDEBUG
		perror("malloc error in create buffer:");
#endif
		return NULL;
	}
	buffer->front =  0;
	buffer->size =  0;
	buffer->capacity =  capacity;

	return buffer;
}

void BufDestroy(buffer_t *buffer)
{
	free(buffer);

	buffer = NULL;
}

ssize_t BufWrite(buffer_t *buffer, const void *src, size_t count_byte)
{
	ssize_t written_bytes = 0;
	char *source = (char *)src;
	int to_write = (buffer->size + buffer->front) % buffer->capacity;

	assert(buffer);
	assert(src);

	if (buffer->size == buffer->capacity)
	{
		errno = ENOBUFS;
		return ERROR;
	}

	while (count_byte-- && !(buffer->size == buffer->capacity))
	{
		buffer->array[to_write++] = *source++;
		to_write %= buffer->capacity;
		buffer->size++;
		written_bytes++;
	}
	return written_bytes;
}

ssize_t BufRead(buffer_t *buffer, void *dest, size_t count_byte)
{
	ssize_t read_bytes = 0;
	char *destination = (char *)dest;

	assert(buffer);
	assert(dest);

	if (!buffer->size)
	{
		errno = ENODATA;
		return ERROR;
	}

	while (count_byte-- && buffer->size)
	{
		*destination++ = buffer->array[buffer->front++];
		buffer->size--;
		buffer->front %= buffer->capacity;
		read_bytes++;
	}

	return read_bytes;
}

size_t BufAvailableSpace(const buffer_t *buffer)
{
	assert(buffer);

	return (buffer->capacity - buffer->size);
}

size_t BufCapacity(const buffer_t *buffer)
{
	assert(buffer);

	return buffer->capacity;
}

int BufIsEmpty(const buffer_t *buffer)
{
	assert(buffer);

	return (!buffer->size);
}
