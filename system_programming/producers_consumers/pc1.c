/*****************************************************************************
* 					written by : Orpaz Houta								 *
* 					review : Izik Avinoam   								 *
* 					Last update : 29.6.20									 *
****************************************************************************/
#include <stdio.h>        /* printf */
#include <unistd.h>       /* sleep */
#include <stdatomic.h>    /* atomic_int */

#include <pthread.h>      /* pthread_t */


#define UNUSED(x)  ((void)x)
#define SIZE_ARRAY (10)
#define STOP       (0)
#define RUN        (1)


static void *_Producer(void *param);
static void *_Consumer(void *param);

static atomic_int stat_write = RUN;
static atomic_int stat_read = STOP;
static int arr[SIZE_ARRAY] = {0};


int main ()
{
    pthread_t producer_id = 0;
    pthread_t consumer_id = 0;

    while (pthread_create(&producer_id, NULL, _Producer, NULL));
    while (pthread_create(&consumer_id, NULL, _Consumer, NULL));

    pthread_detach(producer_id);
    pthread_join(consumer_id, NULL);

    return (0);
}

static void *_Producer(void* param)
{
    size_t i = 0;

    UNUSED(param);

    while (1)
    {
        while (STOP == stat_write)
              ;

        for (i = 0; i < SIZE_ARRAY; ++i)
        {
            arr[i] += 1;
        }

        stat_write = STOP;
        stat_read = RUN;
    }

    return (NULL);
}

static void *_Consumer(void *param)
{
    size_t i = 0;
    size_t sum = 0;

    UNUSED(param);

    while (1)
    {
        while (STOP == stat_read)
              ;
        sum = 0;

        for (i = 0; i < SIZE_ARRAY; ++i)
        {
            sum += arr[i];
        }
        sleep(1);
        printf("%ld\n", sum);
        stat_read = STOP;
        stat_write = RUN;
    }

    return (NULL);
}
