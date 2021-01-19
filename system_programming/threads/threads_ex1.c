/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review : Malu Gerkol									 *
 * 					Last update : 22.6.20									 *
 ****************************************************************************/
#include <stdio.h>
#include <unistd.h>

#include <pthread.h>    /* pthread_t */

#define ARRAY_SIZE (100000)

int g_array[ARRAY_SIZE];

void *set_index(void *index);

int main ()
{
    size_t i = 0;
    pthread_t tid[ARRAY_SIZE] = {0};

    for(i = 0; i < ARRAY_SIZE; ++i)
    {
        pthread_create(&tid[i], NULL, set_index, (void *)i);
    }

    while (sleep(10));

    for (i = 0; i < ARRAY_SIZE; ++i)
    {
        printf("array[%ld] %d\n",i, g_array[i]);
    }

    return 0;
}


void *set_index(void *index)
{
    size_t i = (size_t)index;

    g_array[i] = i;

    return (NULL);
}
