#include <stdio.h>
#include <stddef.h>

int MaxSubArray(int arr[], size_t size, size_t *begin, size_t *end);

int main()
{
    size_t begin = 0, end = 0;
    int array[] = {-2, 1, -3, 4, -1, 2, 3, -5, 4, 12, -10, 10, 9, -3};
    int result = 0;
    size_t size = sizeof(array) / sizeof(int);

    result = MaxSubArray(array, size, &begin, &end);

    for ( ; begin <= end; ++begin)
    {
        printf("%d ", array[begin]);
    }
    printf("\n sum = %d\n", result);

    return 0;
}

int MaxSubArray(int arr[], size_t size, size_t *begin, size_t *end)
{
    size_t i = 0, curr_begin = 0;
    int sum = 0, max_sum = 0;

    for (i = 0; i < size; ++i)
    {
        sum += arr[i];
        if (sum > max_sum)
        {
            *begin = curr_begin;
            *end = i;
            max_sum = sum;
        }

        if (0 > sum)
        {
            curr_begin = i;
            sum = 0;
        }
    }

    return (max_sum);
}
