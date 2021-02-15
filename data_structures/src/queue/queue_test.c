/****************************************************************************
 *                   written by :orpaz houta								*
 *                   review : Gil Mazliah (Gilio):)							*
 *                   Last update : 13.4.20									*
 ***************************************************************************/

#include <stdio.h> /* printf */

#include "queue.h"

#define FAIL (1) 		/* status */
#define SUCCESS (0)		/* status */

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
	int arr[10] = {0,1,2,3,4,5,6,7,8,9}; 

	int i = 0;
	size_t size1 = 0, size2 = 0, size3 = 0;

 	int status = SUCCESS;

	queue_t *queue1 = QueueCreate();
	queue_t *queue2 = QueueCreate();

	if(!queue1 || !queue2)
	{
		status = FAIL;
		printf("QueueCreate FAIL\n");
	}

	if(!QueueIsEmpty(queue1))
	{
		status = FAIL;
		printf("QueueIsEmpty FAIL\n");
	}

	if(EnQueue(queue1, &arr[0]))
	{
		status = FAIL;
		printf("EnQueue FAIL\n");
	}

	if(QueueIsEmpty(queue1))
	{
		status = FAIL;
		printf("QueueIsEmpty FAIL\n");
	}

	if(arr[0] != *(int *)QueuePeek(queue1))
	{
		status = FAIL;
		printf("QueuePeek FAIL\n");
	}	
	 
	for (i = 1; i < 10; i++)
	{
		EnQueue(queue1, &arr[i]);
	}

	size1 = QueueSize(queue1);
	if(10 != size1)
	{
		status = FAIL;
		printf("QueueSize FAIL\n");
	}

	DeQueue(queue1);
	size2 = QueueSize(queue1);
	if(size1 == size2)
	{
		status = FAIL;
		printf("DeQueue FAIL\n");
	}
	
	for (i = 9; i >= 0; i--)
	{
		EnQueue(queue2, &arr[i]);
	}

	size1 = QueueSize(queue1);
	size2 = QueueSize(queue2);
	QueueAppend(queue1, queue2);
	size3 = QueueSize(queue1);
	
	if(size3 != size1 + size2)
	{
		status = FAIL;
		printf("QueueAppend FAIL\n");
	}

	QueueDestroy(queue1);

	return status;
}


