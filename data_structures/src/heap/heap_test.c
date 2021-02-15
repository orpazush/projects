/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review : Gil Steinberg  						         *
 * 					Last update : 9.6.20									 *
 ****************************************************************************/
 #include "heap.h"
 #include "ca_test_util.h" 	/* ©️ chanan & aviv */

 #define SIZE (150)
 #define MAX_RANGE (1000)

 void TestCreatDestroy();
 void TestPushPop();
 void TestRemove();

 int IsBigger(const void *data1, const void *data2);
 int IsMatch(const void *data, const void *param);

 int main()
 {
     TestCreatDestroy();
     TestPushPop();
     TestRemove();

     TEST_SUMMARY();

     return 0;
 }

 void TestCreatDestroy()
 {
     heap_t *test_heap = NULL;
     int test1 = 1;
     int test2 = 2;
     int test3 = 3;

     test_heap = HeapCreate(IsBigger);

     INT_TEST(1, HeapIsEmpty(test_heap));

     INT_TEST(0, HeapPush(test_heap, &test1));
     INT_TEST(test1, *(int *)HeapPeek(test_heap));
     INT_TEST(0, HeapPush(test_heap, &test3));
     INT_TEST(test3, *(int *)HeapPeek(test_heap));
     INT_TEST(0, HeapPush(test_heap, &test2));
     INT_TEST(test3, *(int *)HeapPeek(test_heap));

     INT_TEST(0, HeapIsEmpty(test_heap));
     INT_TEST(3, HeapSize(test_heap));

     HeapDestroy(test_heap);
 }

 void TestPushPop()
 {
     heap_t *test_Heap;
     size_t i = 0;
     int array[SIZE];
     int peek = 0;
     size_t size_test = SIZE / 2;

     test_Heap = HeapCreate(IsBigger);
     INT_TEST(1, HeapIsEmpty(test_Heap));

     for (i = 0 ; i < SIZE ; i++)
     {
         array[i] = (rand() % MAX_RANGE);
     }
     for (i = 0 ; i < SIZE ; i++)
     {
         INT_TEST(1, (i == HeapSize(test_Heap)));
         HeapPush(test_Heap, &array[i]);
     }
     INT_TEST(0, HeapIsEmpty(test_Heap));
     INT_TEST(1, (SIZE == HeapSize(test_Heap)));

     for (i = 0 ; i < size_test; i++)
     {
         peek = *(int *)HeapPeek(test_Heap);
         HeapPop(test_Heap);
         INT_TEST(1, (peek >= *(int *)HeapPeek(test_Heap)));
     }

     HeapPop(test_Heap);

     for (i = (size_test - 1) ; i < SIZE ; i++)
     {
         HeapPush(test_Heap, &array[i]);
     }
     INT_TEST(1, (SIZE == HeapSize(test_Heap)));

/*     for (i = (SIZE - 1) ; 0 >= i; i++) */
     for (i = 0; i < (SIZE - 1); i++)
     {
         peek = *(int *)HeapPeek(test_Heap);
         HeapPop(test_Heap);
         INT_TEST(1, (peek >= *(int *)HeapPeek(test_Heap)));
     }

     HeapDestroy(test_Heap);
 }
 void TestRemove()
 {
     heap_t *test_Heap;
     size_t i = 0;
     int array[SIZE];
     int *removed = NULL;
     size_t test_size = SIZE;
     int peek = 0;

     test_Heap = HeapCreate(IsBigger);
     INT_TEST(1, HeapIsEmpty(test_Heap));

     for (i = 0 ; i < SIZE ; i++)
     {
         array[i] = (rand() % MAX_RANGE);
     }

     for (i = 0 ; i < SIZE ; i++)
     {
         INT_TEST(1, (i == HeapSize(test_Heap)));
         HeapPush(test_Heap, &array[i]);
     }

     for (i = 0; !HeapIsEmpty(test_Heap); ++i)
     {
         peek = *(int *)HeapPeek(test_Heap);
         removed = (int *)HeapRemove(test_Heap, IsMatch, &array[i]);
         INT_TEST(array[i], *removed);
         if (HeapSize(test_Heap) > 0)
         {
             INT_TEST(1, (peek >= *(int *)HeapPeek(test_Heap)));
         }
         INT_TEST(1, (--test_size == HeapSize(test_Heap)));
     }

     HeapDestroy(test_Heap);
 }

 int IsBigger(const void *data1, const void *data2)
 {
     return (*(int *)data1 - *(int *)data2);
 }

 int IsMatch(const void *data, const void *param)
 {
     return (*(int *)data == *(int *)param);
 }
