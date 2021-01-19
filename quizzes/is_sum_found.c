#include <stdio.h>
#include <stddef.h>

#define SUM_FOUND     (1)
#define SUM_NOT_FOUND (0)

int IsSumFound(int arr[], size_t size, int sum, size_t *idx1, size_t *idx2);

int main()
{
    size_t idx1 = 0, idx2 = 0;
    int sum = 21;
    int array[] = {1, 3, 5, 9, 14, 15, 16, 20, 24, 30, 31, 32, 33, 40, 45, 50};
    size_t size = (sizeof(array) / sizeof(int));

    if (IsSumFound(array, size, sum, &idx1, &idx2))
    {
        printf("%d + %d = %d\n", array[idx1], array[idx2], sum);
    }

    return (0);
}

int IsSumFound(int arr[], size_t size, int sum, size_t *idx1, size_t *idx2)
{
    size_t left = 0, right = (size -1);

    while (left < right)
    {
        if (sum == (arr[left] + arr[right]))
        {
            *idx1 = left;
            *idx2 = right;
            return (SUM_FOUND);
        }

        else if (sum < (arr[left] + arr[right]))
        {
            --right;
        }

        else
        {
            ++left;
        }
    }

    return (SUM_NOT_FOUND);
}
