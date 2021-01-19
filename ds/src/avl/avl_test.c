/****************************************************************************
* 					written by : orpaz houta								*
* 					review : Izik Avinoam    								*
*					Last update : 2.6.20 									*
****************************************************************************/
#include <math.h>           /* log(n) */
#include <limits.h>         /* SHRT_MAX */
#include "avl.h"
#include "ca_test_util.h" 	/* ©️ chanan & aviv */


#define MAX_RANGE (1000000)
#define SIZE (500)

void TestCreateInsert();
void TestFindRemove();
void TestForeach();
void TestBalanceHight();

int IsBigger(void *data1, void *data2, void *param);
static int Multy(int *number, float *multy);
/*static int PrintMe(int *to_print, int *param);*/

int main()
{
    TestCreateInsert();
    TestFindRemove();
    TestForeach();
    TestBalanceHight();

    TEST_SUMMARY();

    return 0;
}

void TestCreateInsert()
{
    avl_t *test_avl;
    int test1 = 1;
    int test2 = 2;
    int test3 = 3;
    int test4 = 4;
    int test5 = 5;
    int test6 = 6;
    int test7 = 7;
    int test8 = 8;

    test_avl = AVLCreate((cmp_func_t)IsBigger, NULL);

    INT_TEST(1, AVLIsEmpty(test_avl));

    INT_TEST(0, AVLInsert(test_avl, &test1));
    INT_TEST(0, AVLInsert(test_avl, &test2));
    INT_TEST(0, AVLInsert(test_avl, &test3));
    INT_TEST(0, AVLInsert(test_avl, &test4));
    INT_TEST(0, AVLInsert(test_avl, &test5));
    INT_TEST(0, AVLInsert(test_avl, &test6));
    INT_TEST(0, AVLInsert(test_avl, &test7));
    INT_TEST(0, AVLInsert(test_avl, &test8));

    INT_TEST(0, AVLIsEmpty(test_avl));
    INT_TEST(8, AVLSize(test_avl));
    INT_TEST(3, AVLHeight(test_avl));

    AVLDestroy(test_avl);
}

void TestFindRemove()
{
    avl_t *test_AVL;
    size_t i = 0;
    int j = 0;
    int array[SIZE];
    size_t test_size = 0;

    test_AVL = AVLCreate((cmp_func_t)IsBigger, NULL);
    INT_TEST(1, AVLIsEmpty(test_AVL));

    for (i = 0 ; i < SIZE ; i++)
    {
        array[i] = (rand() % MAX_RANGE);
    }

    for (i = 0 ; i < SIZE ; i++)
    {
        INT_TEST(1, (i == AVLSize(test_AVL)));
        AVLInsert(test_AVL, &array[i]);
    }
    INT_TEST(0, AVLIsEmpty(test_AVL));
    INT_TEST(1, (SIZE == AVLSize(test_AVL)));

    for (i = 0 ; i < SIZE ; i++)
    {
        INT_TEST(array[i], *(int *)AVLFind(test_AVL, &array[i]));
    }
    for (i = 0 ; i < SIZE ; j = (rand() % SIZE), ++i)
    {
        INT_TEST(array[j], *(int *)AVLFind(test_AVL, &array[j]));
    }

    INT_TEST(1, (SIZE == AVLSize(test_AVL)));
    test_size = AVLSize(test_AVL);
    for (i = 0; !AVLIsEmpty(test_AVL); ++i)
    {
        AVLRemove(test_AVL, &array[i]);
        INT_TEST(1, (--test_size == AVLSize(test_AVL)));
    }

    AVLDestroy(test_AVL);
}

void TestForeach()
{
    avl_t *test_AVL = NULL;
    size_t i = 0;
    int array[SIZE];
    int copy_array[SIZE];
    float multy = 2;
    float back_multy = 0;

    test_AVL = AVLCreate((cmp_func_t)IsBigger, NULL);
    INT_TEST(1, AVLIsEmpty(test_AVL));

    for (i = 0 ; i < SIZE ; i++)
    {
        array[i] = (rand() % MAX_RANGE);
        copy_array[i] = array[i];
    }
    for (i = 0 ; i < SIZE ; i++)
    {
        AVLInsert(test_AVL, &array[i]);
    }
    INT_TEST(0, AVLIsEmpty(test_AVL));
    INT_TEST(1, (SIZE == AVLSize(test_AVL)));

    AVLForEach(test_AVL, (callback_func_t)Multy, &multy, PREORDER);
    for (i = 0 ; i < SIZE ; i++)
    {
        INT_TEST((copy_array[i] * multy), *(int *)AVLFind(test_AVL, &array[i]));
    }
    back_multy = 1/multy;

    AVLForEach(test_AVL, (callback_func_t)Multy, &back_multy, PREORDER);
    for (i = 0 ; i < SIZE ; i++)
    {
        INT_TEST((copy_array[i]), *(int *)AVLFind(test_AVL, &array[i]));
    }

/*    multy = MAX_RANGE;
    AVLForEach(test_AVL, (callback_func_t)PrintMe, &multy, INORDER);
    for (i = 0 ; i < SIZE ; i++)
    {
        INT_TEST((copy_array[i]), *(int *)AVLFind(test_AVL, &array[i]));
    }
    printf("\n");*/

    multy = 3;
    AVLForEach(test_AVL, (callback_func_t)Multy, &multy, POSTORDER);
    for (i = 0 ; i < SIZE ; i++)
    {
        INT_TEST((copy_array[i] * multy), *(int *)AVLFind(test_AVL, &array[i]));
    }
    back_multy = 1/multy;

    AVLForEach(test_AVL, (callback_func_t)Multy, &back_multy, POSTORDER);
    for (i = 0 ; i < SIZE ; i++)
    {
        INT_TEST((copy_array[i]), *(int *)AVLFind(test_AVL, &array[i]));
    }
    INT_TEST(-1, AVLForEach(test_AVL,
                            (callback_func_t)Multy, &back_multy, 100));
    INT_TEST(-1, AVLForEach(test_AVL,
                            (callback_func_t)Multy, &back_multy, -4));

    AVLDestroy(test_AVL);
}

void TestBalanceHight()
{
    avl_t *test_avl;
    size_t i = 0;
    int array[SIZE];
    size_t test_hight = 0;

    test_avl = AVLCreate((cmp_func_t)IsBigger, NULL);
    INT_TEST(1, AVLIsEmpty(test_avl));

    for (i = 0 ; i < SIZE ; ++i)
    {
        array[i] = (rand() % MAX_RANGE);
    }
    printf("\n");

    for (i = 0 ; i < SIZE ; ++i)
    {
        AVLInsert(test_avl, &array[i]);
        test_hight = ((size_t)(1.44 * (log((double)AVLSize(test_avl)) + 2) - 0.3));
        INT_TEST(1, (test_hight >= AVLHeight(test_avl)));
    }
    INT_TEST(0, AVLIsEmpty(test_avl));
    INT_TEST(1, (SIZE == AVLSize(test_avl)));

    for (i = 0 ; AVLIsEmpty(test_avl) ; ++i)
    {
        AVLRemove(test_avl, &array[i]);
        test_hight = ((size_t)(1.44 * (log((double)AVLSize(test_avl)) + 2) - 0.3));
        INT_TEST(1, (test_hight >= AVLHeight(test_avl)));
    }

    AVLDestroy(test_avl);
}

int IsBigger(void *data1, void *data2, void *param)
{
    if (data1 == param)
    {
        return 0;
    }
    return (*(int *)data1 - *(int *)data2);
}

static int Multy(int *number, float *multy)
{
	if (SHRT_MAX < (*multy))
	{
		return 1;
	}
	*number *= *multy;

	return 0;
}
/*
static int PrintMe(int *to_print, int *param)
{
    printf("%d, ", *to_print);
    if (*to_print == *param)
    {
        printf("arrived param");
    }
    return 0;
}
*/
