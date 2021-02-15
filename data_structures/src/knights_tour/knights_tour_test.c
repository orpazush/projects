/******************************************************************************
 *                      code by : Orpaz Houta                                 *
 *                      review by : Chanan Komar                              *
 *                      coding date - 17-06-2020                              *
 ******************************************************************************/

#include "ca_test_util.h" 	/* ©️ chanan & aviv */
#include "knights_tour.h"

void TestKnightsTour();

static size_t _SumArr(int arr[], size_t size);

int main()
{
    TestKnightsTour();

    TEST_SUMMARY();

    return 0;
}

void TestKnightsTour()
{
    size_t i = 0, j = 0;
    int arr[64];
    int test_path[64] = {0};
    size_t sum_arr = 0;
    size_t sum_path = 0;

    for (i = 0; i < 64; ++i)
    {
        arr[i] = i;
    }

    sum_arr = _SumArr(arr, 64);

    for (i = 0; i < 8; ++i)
    {
        for (j = 0; j < 8; ++j)
        {
            KnightsTour(i, j, test_path);
            sum_path = _SumArr(test_path, 64);
            INT_TEST(1, (sum_path == sum_arr));
        }
    }
}

static size_t _SumArr(int arr[], size_t size)
{
    size_t sum = 0;
    size_t i = 0;

    for (i = 0; i < size; ++i)
    {
        sum += arr[i];
    }

    return sum;
}
