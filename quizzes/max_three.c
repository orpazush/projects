#include <stddef.h>
#include <stdio.h>

#define SIZE  (11)

int MaxThree(int array[], size_t size);

int main()
{
    size_t i = 0;
    int array[SIZE] = {1, 20, 3, 45, 12, 55, 0, 69, 44, 44, 44};

    i = MaxThree(array, SIZE);
    printf("%d, %d, %d\n", array[i], array[i + 1], array[i + 2]);
    return 0;
}

int MaxThree(int array[], size_t size)
{
    size_t first = 0, sum = 0, max_sum = 0, max_first = 0;

    if (size < 3)
    {
        return 0;
    }

    sum = array[first] + array[first + 1] + array[first + 2];
    max_sum = sum;

    for (first = 0; size > (first + 2); ++first)
    {
        sum += (array[first + 2] - array[first - 1]);
        if (max_sum < sum)
        {
            max_first = first;
            max_sum = sum;
        }
    }

    return (max_first);
}
