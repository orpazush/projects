/****************************************************************************
 * 					written by : orpaz houta								*
 * 					review : yana Gorikhovski								*
 *					Last update : 14.4.20 									*
 ***************************************************************************/

#include <stdio.h>	/* printf */
#include <unistd.h>	/* ssize_t */

#include "circular_buffer.h"

#define FAIL (1) 		/* status */
#define SUCCESS (0)		/* status */
#define CAPACITY (15)

int SanityTest();

int main() 
{ 
	printf("****************START TESTING ***********************\n");
	SanityTest() ? printf("test failed\n") : printf("all tests succeeded!:)\n");
	printf("****************END TESTING ***********************\n");

	return 0; 
} 
 
int SanityTest()
{
	int status = SUCCESS;
	char *src = "veaz ani ehye cmo shemesh la'olam"; 
	char dest[35] = "";
	ssize_t write = 0, read = 0;
	size_t available = 0, capacity = 0;

	buffer_t *buffer = BufCreate(CAPACITY);

	if (!buffer)
	{
		status = FAIL;
		printf("bufCreate FAIL\n");
	}

	if (!BufIsEmpty(buffer))
	{
		status = FAIL;
		printf("bufferIsEmpty FAIL\n");
	}

	capacity = BufCapacity(buffer);
	if (CAPACITY != capacity)
	{
		status = FAIL;
		printf("BufCapacity FAIL\n");
	}

	write = BufWrite(buffer, src, 10);
	if (10 != write)
	{
		status = FAIL;
		printf("BufWrite FAIL\n");
	}

	available = BufAvailableSpace(buffer);
	if (available != (capacity - write))
	{
		status = FAIL;
		printf("BufAvailableSpace FAIL\n");
	}

	write = BufWrite(buffer, src, 20);
	if (available != (size_t)write)
	{
		status = FAIL;
		printf("BufWrite FAIL\n");
	}

	if (BufIsEmpty(buffer))
	{
		status = FAIL;
		printf("bufferIsEmpty FAIL\n");
	}

	read = BufRead(buffer, dest, 8);
	if (8 != read)
	{
		status = FAIL;
		printf("BufRead FAIL\n");
	}

	read = BufRead(buffer, dest, 10);
	if (7 != read)
	{
		status = FAIL;
		printf("BufRead FAIL\n");
	}

	if (!BufIsEmpty(buffer))
	{
		status = FAIL;
		printf("bufferIsEmpty FAIL\n");
	}

	BufDestroy(buffer);

	return status;
}
	




