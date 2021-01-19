#include <stdio.h>      /* printf */

#define NUMBER (1234567890)

int main ()
{
    size_t i = 0;
    size_t sum_of_divisors = 0;

    for (i = 0; i < (NUMBER - 1); ++i)
    {
        if (!(NUMBER % (i + 1)))
        {
            sum_of_divisors += (i + 1);
        }
    }

    printf("sum of divisors of %d is %ld\n", NUMBER, sum_of_divisors);

    return 0;
}
