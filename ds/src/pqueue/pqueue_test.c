/****************************************************************************
 * 						written by: Orpaz Houta								*
 * 						review: Alex Sevostyanov							*
 * 						Last update: 26.4.20 								*
 ***************************************************************************/

#include "ca_test_util.h" 	/* ©️ chanan & aviv */
#include "sorted_list.h"	/* sorted_list_t */
#include "pqueue.h"			/* pqueue_t */

#define MAX_SHORT (0x7fff)

void TestEnPQueue();
void TestPQueueClear();
void TestPQueueErase();

int CmpInt(int *data1, int *data2, void *param);
void PrintListINT(pqueue_t *pqueue);
int IsIntMatch(const void *data, const void *param);

int main()
{
	TestEnPQueue();
	TestPQueueErase();

    TEST_SUMMARY();

    return 0;
}

/* used on this test PQueueCreate, PQueueSize, PQueueIsEmpty, PQueueDestroy */
void TestEnPQueue()
{
    pqueue_t *test_pqueue = PQueueCreate((cmp_func)&CmpInt);
	int array[20] = {1,555,88,9999,7,32,-58,87,-1};
	int i = 0;

    INT_TEST(0, PQueueSize(test_pqueue));
	INT_TEST(1, PQueueIsEmpty(test_pqueue));

	for (i = 0; array[i]; i++)
    {
        EnPQueue(test_pqueue, &array[i]);
    }
	PrintListINT(test_pqueue);

	for (i = 0; array[i]; i++)
    {
        EnPQueue(test_pqueue, &array[i]);
    }

    INT_TEST(9, PQueueSize(test_pqueue));
	INT_TEST(0, PQueueIsEmpty(test_pqueue));

	PQueuePeek(test_pqueue);

	while (!PQueueIsEmpty(test_pqueue))
	{
		DePQueue(test_pqueue);
	}

	PrintListINT(test_pqueue);
	PQueueDestroy(test_pqueue);
}

void TestPQueueErase()
{
	pqueue_t *test_pqueue = PQueueCreate((cmp_func)&CmpInt);
	int array[20] = {1,555,88,9,777,32,-58,87,-1};
	int data = 1000000;
	int i = 0;
	int *pdata = &data;

    INT_TEST(0, PQueueSize(test_pqueue));
	INT_TEST(1, PQueueIsEmpty(test_pqueue));

	for (i = 0; array[i]; i++)
    {
        EnPQueue(test_pqueue, &array[i]);
    }

	EnPQueue(test_pqueue, &data);
    INT_TEST(1, (pdata == (int *)PQueuePeek(test_pqueue)));

	pdata = (int *)PQueueErase(test_pqueue,
									(is_match_func)&IsIntMatch, &array[3]);
    INT_TEST(1, (pdata == &array[3]));

	pdata = (int *)PQueueErase(test_pqueue,
									(is_match_func)&IsIntMatch, &array[4]);
    INT_TEST(1, (pdata == &array[4]));

	PQueueClear(test_pqueue);

    INT_TEST(0, PQueueSize(test_pqueue));
	INT_TEST(1, PQueueIsEmpty(test_pqueue));

	PQueueDestroy(test_pqueue);
}

void PrintListINT(pqueue_t *pqueue)
{
    while (!PQueueIsEmpty(pqueue))
    {
        printf("%d ", *(int *)PQueuePeek(pqueue));
        DePQueue(pqueue);
    }
    printf("\n");
}

int CmpInt(int *data1, int *data2, void *param)
{
	if (param)
	{
		return (*data1 - *data2);		
	}
	return (*data1 - *data2);
}

int IsIntMatch(const void *data, const void *param)
{
	return (*(int *)data == *(int *)param);
}
