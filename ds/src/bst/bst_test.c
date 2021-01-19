/*****************************************************************************
 * 					written by: Orpaz Houta									 *
 * 					review: Izik Avinoam									 *
 * 					Last update: 17.5.20									 *
 ****************************************************************************/
#include "bst.h"
#include "ca_test_util.h" 	/* ©️ chanan & aviv */

#define MAX_RANGE (100)
#define SIZE (50)

void TestCreateInsert();
void TestFindRemove();

int IsBigger(void *data1, void *data2, void *param);

int main()
{
    TestCreateInsert();
    TestFindRemove();

    TEST_SUMMARY();

    return 0;
}

void TestCreateInsert()
{
    bst_t *test_bst;
    bst_iterator_t test_iter = NULL;
    int test1 = 1;
    int test2 = 2;
    int test3 = 3;
    int test4 = 4;
    int test5 = 5;
    int test6 = 6;

    test_bst = BSTCreate((cmp_func_t)IsBigger, NULL);

    INT_TEST(test4, *(int *)BSTGetData(BSTInsert(test_bst, &test4)));
    INT_TEST(test3, *(int *)BSTGetData(BSTInsert(test_bst, &test3)));
    INT_TEST(test1, *(int *)BSTGetData(BSTInsert(test_bst, &test1)));
    INT_TEST(test2, *(int *)BSTGetData(BSTInsert(test_bst, &test2)));
    INT_TEST(test6, *(int *)BSTGetData(BSTInsert(test_bst, &test6)));
    INT_TEST(test5, *(int *)BSTGetData(BSTInsert(test_bst, &test5)));

    test_iter = BSTBegin(test_bst);
    INT_TEST(test1, *(int *)BSTGetData(test_iter));
    test_iter = BSTNext(test_iter);
    INT_TEST(test2, *(int *)BSTGetData(test_iter));
    test_iter = BSTNext(test_iter);
    INT_TEST(test3, *(int *)BSTGetData(test_iter));
    test_iter = BSTNext(test_iter);
    INT_TEST(test4, *(int *)BSTGetData(test_iter));
    test_iter = BSTNext(test_iter);
    INT_TEST(test5, *(int *)BSTGetData(test_iter));
    test_iter = BSTNext(test_iter);
    INT_TEST(test6, *(int *)BSTGetData(test_iter));

    test_iter = BSTPrev(test_iter);
    INT_TEST(test5, *(int *)BSTGetData(test_iter));
    test_iter = BSTPrev(test_iter);
    INT_TEST(test4, *(int *)BSTGetData(test_iter));
    test_iter = BSTPrev(test_iter);
    INT_TEST(test3, *(int *)BSTGetData(test_iter));
    test_iter = BSTPrev(test_iter);
    INT_TEST(test2, *(int *)BSTGetData(test_iter));
    test_iter = BSTPrev(test_iter);
    INT_TEST(test1, *(int *)BSTGetData(test_iter));

    INT_TEST(1, (6 == BSTSize(test_bst)));

    BSTDestroy(test_bst);
}


void TestFindRemove()
{
    bst_t *test_bst;
    size_t i = 0;
    int j = 0;
    int data = 0;
    size_t size = 0;
    int array[SIZE];
    bst_iterator_t test_iter = NULL;

    test_bst = BSTCreate((cmp_func_t)IsBigger, NULL);
    INT_TEST(1, BSTIsEmpty(test_bst));

    for (i = 0 ; i < SIZE ; i++)
    {
        array[i] = (rand() % MAX_RANGE);
    }
    for (i = 0 ; i < SIZE ; i++)
    {
        BSTInsert(test_bst, &array[i]);
    }
    INT_TEST(0, BSTIsEmpty(test_bst));

    size = BSTSize(test_bst);
    INT_TEST(1, (SIZE >= BSTSize(test_bst)));

    for (i = 0 ; i < SIZE ; i++)
    {
        test_iter = BSTFind(test_bst, &array[i]);
        INT_TEST(array[i], *(int *)BSTGetData(test_iter));
    }
    for (i = 0 ; i < SIZE ; j = (rand() % SIZE), ++i)
    {
        test_iter = BSTFind(test_bst, &array[j]);
        INT_TEST(array[j], *(int *)BSTGetData(test_iter));
    }

    test_iter = BSTBegin(test_bst);
    for (i = 0 ; i < (SIZE - 1) ; i++)
    {
        data = *(int *)BSTGetData(BSTNext(test_iter));
        INT_TEST(1, (data >= *(int *)BSTGetData(test_iter)));
        test_iter = BSTNext(test_iter);
    }

    size = BSTSize(test_bst);
    INT_TEST(1, (SIZE >= BSTSize(test_bst)));

    BSTRemove(test_bst, &array[0]);
    INT_TEST(1, (--size == BSTSize(test_bst)));
    BSTRemove(test_bst, &array[1]);
    INT_TEST(1, (--size == BSTSize(test_bst)));
    BSTRemove(test_bst, &array[2]);
    INT_TEST(1, (--size == BSTSize(test_bst)));
    BSTRemove(test_bst, &array[3]);
    INT_TEST(1, (--size == BSTSize(test_bst)));
    BSTRemove(test_bst, &array[4]);
    INT_TEST(1, (--size == BSTSize(test_bst)));

    for (i = 0; !BSTIsEmpty(test_bst); ++i)
    {
        BSTRemove(test_bst, &array[i]);
    }
    BSTDestroy(test_bst);
}

int IsBigger(void *data1, void *data2, void *param)
{
    if (data1 == param)
    {
        return 0;
    }
    return (*(int *)data1 - *(int *)data2);
}
