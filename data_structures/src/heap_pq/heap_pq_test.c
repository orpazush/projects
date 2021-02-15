/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review : Gil Steinberg  						         *
 * 					Last update : 9.6.20									 *
 *---------------------------------------------------------------------------*
 * Priority Queue is more specialized data structure than Queue.             *
 * Like ordinary queue, priority queue has same method but with a major      *
 * difference. In Priority queue items are ordered by key value so that      *
 * item with the lowest value of key is at front and item with the highest   *
 * value of key is at rear or vice versa. So we're assigned priority to item *
 * based on its key value. Lower the value, higher the priority. Following   *
 * are the principal methods of a Priority Queue.                            *
 ****************************************************************************/

#include "ca_test_util.h" 	/* ©️ chanan & aviv */
#include "heap.h"	        /* heap_t */
#include "heap_pq.h"			/* heap_pq_t */

#define MAX_SHORT (0x7fff)

void TestHeapEnPQ();
void TestHeapPQClear();
void TestHeapPQErase();

int CmpInt(int *data1, int *data2, void *param);
void PrintListINT(heap_pq_t *heap_pq);
int IsIntMatch(const void *data, const void *param);

int main()
{
	TestHeapEnPQ();
	TestHeapPQErase();

    TEST_SUMMARY();

    return 0;
}

/* used on this test HeapPQCreate, HeapPQSize, HeapPQIsEmpty, HeapPQDestroy */
void TestHeapEnPQ()
{
    heap_pq_t *test_heap_pq = HeapPQCreate((cmp_func)&CmpInt);
	int array[20] = {1,555,88,9999,7,32,-58,87,-1};
	int i = 0;

    INT_TEST(0, HeapPQSize(test_heap_pq));
	INT_TEST(1, HeapPQIsEmpty(test_heap_pq));

	for (i = 0; array[i]; i++)
    {
        HeapEnPQ(test_heap_pq, &array[i]);
    }
	PrintListINT(test_heap_pq);

	for (i = 0; array[i]; i++)
    {
        HeapEnPQ(test_heap_pq, &array[i]);
    }

    INT_TEST(9, HeapPQSize(test_heap_pq));
	INT_TEST(0, HeapPQIsEmpty(test_heap_pq));

	HeapPQPeek(test_heap_pq);

	while (!HeapPQIsEmpty(test_heap_pq))
	{
		HeapDePQ(test_heap_pq);
	}

	PrintListINT(test_heap_pq);
	HeapPQDestroy(test_heap_pq);
}

void TestHeapPQErase()
{
	heap_pq_t *test_heap_pq = HeapPQCreate((cmp_func)&CmpInt);
	int array[20] = {1,555,88,9,777,32,-58,87,-1};
	int data = 1000000;
	int i = 0;
	int *pdata = &data;

    INT_TEST(0, HeapPQSize(test_heap_pq));
	INT_TEST(1, HeapPQIsEmpty(test_heap_pq));

	for (i = 0; array[i]; i++)
    {
        HeapEnPQ(test_heap_pq, &array[i]);
    }

	HeapEnPQ(test_heap_pq, &data);
    INT_TEST(1, (pdata == (int *)HeapPQPeek(test_heap_pq)));

	pdata = (int *)HeapPQErase(test_heap_pq,
									(is_match_func)&IsIntMatch, &array[3]);
    INT_TEST(1, (pdata == &array[3]));

	pdata = (int *)HeapPQErase(test_heap_pq,
									(is_match_func)&IsIntMatch, &array[4]);
    INT_TEST(1, (pdata == &array[4]));

	HeapPQClear(test_heap_pq);

    INT_TEST(0, HeapPQSize(test_heap_pq));
	INT_TEST(1, HeapPQIsEmpty(test_heap_pq));

	HeapPQDestroy(test_heap_pq);
}

void PrintListINT(heap_pq_t *heap_pq)
{
    while (!HeapPQIsEmpty(heap_pq))
    {
        printf("%d ", *(int *)HeapPQPeek(heap_pq));
        HeapDePQ(heap_pq);
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
