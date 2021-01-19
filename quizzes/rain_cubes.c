#include <stddef.h>
#include <stdio.h>

size_t RainCubes(size_t array[], size_t size);

int main()
{
    size_t result = 0;
    size_t array[] = {0, 2, 1, 3, 4, 0, 1, 2, 1, 4, 3, 1, 0, 0, 2, 0, 1};
    size_t size = 17;

    result = RainCubes(array, size);

    printf("%ld\n", result);

    return 0;
}


size_t RainCubes(size_t array[], size_t size)
{
    size_t i = 0, max_cubes = 0, field_size = 0;
    size_t sum_of_cubes = 0, total_sum = 0;
    size_t end_backround = 0;

    for (i = 0; i < size; ++i)
    {
        if (max_cubes > array[i])
        {
            ++field_size;
            sum_of_cubes += array[i];
        }

        else
        {
            total_sum += ((field_size * max_cubes) - sum_of_cubes);
            max_cubes = array[i];
            field_size = 0;
            sum_of_cubes = 0;
        }
    }

    end_backround = (i - field_size);
    max_cubes = 0;
    field_size = 0;
    sum_of_cubes = 0;

    for (i -= 1; i >= end_backround; --i)
    {
        if (max_cubes > array[i])
        {
            ++field_size;
            sum_of_cubes += array[i];
        }

        else
        {
            total_sum += ((field_size * max_cubes) - sum_of_cubes);
            max_cubes = array[i];
            field_size = 0;
            sum_of_cubes = 0;
        }
    }

    return (total_sum);
}
