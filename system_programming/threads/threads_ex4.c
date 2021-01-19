/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review : Malu Gerkol									 *
 * 					Last update : 22.6.20									 *
 ****************************************************************************/
#include <stdio.h>      /* printf */
#include <pthread.h>    /* pthread_t */

#define NUMBER          (1234567890)
#define NUM_OF_THREADS  (99)
#define THREAD_RANGE    (NUMBER / NUM_OF_THREADS)

void *SumDivisors(void* param);

int main ()
{
    size_t i = 0;
    size_t param = 0;
    size_t total_sum = 0;
    size_t exit_val = 0;
    pthread_t thread_id[NUM_OF_THREADS] = {0};

    for(i = 0, param = 1; i < NUM_OF_THREADS; ++i, param += THREAD_RANGE)
    {
        while (pthread_create(&thread_id[i], NULL, SumDivisors, (void *)param));
    }

    for (i = 0; i < NUM_OF_THREADS; ++i)
    {
        pthread_join(thread_id[i], (void *)&exit_val);
        total_sum += exit_val;
    }

    printf("sum of divisors of %d is %ld\n", NUMBER, total_sum);

    return 0;
}

void *SumDivisors(void *param)
{
    size_t i = (size_t)param;
    size_t sum_of_divisors = 0;

    for ( ; i < ((size_t)param + THREAD_RANGE) && NUMBER != i; ++i)
    {
        if (!(NUMBER % i))
        {
            sum_of_divisors += i;
        }
    }

    return ((void *)sum_of_divisors);
}
