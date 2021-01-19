/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review : Malu Gerkol									 *
 * 					Last update : 22.6.20									 *
 ****************************************************************************/
#include <pthread.h>    /* pthread_t */
#include <stdio.h>      /* printf */

#define ARRAY_SIZE (100000)

int g_array[ARRAY_SIZE];

int	pthread_attr_setdetachstate(pthread_attr_t *threads, int detachstate);

void* set_index(void* index);

int main ()
{
    size_t i = 0;
    pthread_attr_t threads[ARRAY_SIZE] = {0};
    pthread_t tid[ARRAY_SIZE] = {0};

    for(i = 0; i < ARRAY_SIZE; ++i)
    {
        pthread_attr_setdetachstate(&threads[i], PTHREAD_CREATE_DETACHED);
        while (pthread_create(&tid[i], &threads[i], set_index, (void *)i));
    }

    for (i = 0; i < ARRAY_SIZE; ++i)
    {
        printf("array[%ld] %d\n",i, g_array[i]);
    }

    return 0;
}


void* set_index(void *index)
{
    size_t i = (size_t)index;

    g_array[i] = i;

    return (NULL);
}
