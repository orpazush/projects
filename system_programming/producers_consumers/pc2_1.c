/*****************************************************************************
* 					written by : Orpaz Houta								 *
* 					review : Izik Avinoam   								 *
* 					Last update : 29.6.20									 *
****************************************************************************/
#include <stdio.h>      /* printf */

#include <pthread.h>    /* pthread_t */

#include "queue.h"      /* QueueCreate, EnQueue.. */


#ifndef NDEBUG
#define PRINT_ERROR(str) fprintf(stderr, "ERROR( %s : %d ) -- %s\n",\
                                 __FILE__, __LINE__, str)
#else
#define PRINT_ERROR(str)
#endif
#define UNUSED(x)      ((void)x)
#define FAILURE        (1)
#define SUCCESS        (0)
#define NUM_OF_THREADS (10)

static void *_Producer(void* param);
static void *_Consumer(void* param);

static int item = 1;
static queue_t *shared_queue = NULL;

pthread_mutex_t queue_mutex = PTHREAD_MUTEX_INITIALIZER;

int main ()
{
    size_t i = 0;
    pthread_t producer_id[NUM_OF_THREADS] = {0};
    pthread_t consumer_id[NUM_OF_THREADS] = {0};

    shared_queue = QueueCreate();
    if (!shared_queue)
    {
        PRINT_ERROR("\nmalloc failed in QueueCreate\n");
        return (FAILURE);
    }

    for (i = 0; i < NUM_OF_THREADS; ++i)
    {
        while (pthread_create(&producer_id[i], NULL, _Producer, NULL));
        while (pthread_create(&consumer_id[i], NULL, _Consumer, NULL));
        pthread_detach(producer_id[i]);
    }

    for (i = 0; i < NUM_OF_THREADS; ++i)
    {
        pthread_join(consumer_id[i], NULL);
    }

    printf ("%ld\n", QueueSize(shared_queue));

    QueueDestroy(shared_queue);

    return 0;
}

static void *_Producer(void* param)
{
    UNUSED(param);

    pthread_mutex_lock(&queue_mutex);
    if (EnQueue(shared_queue, &item))
    {
        printf("\nEnQueue failed\n");
    }
    printf ("producer %ld\n", QueueSize(shared_queue));
    pthread_mutex_unlock(&queue_mutex);
    return (NULL);
}

static void *_Consumer(void* param)
{
    UNUSED(param);

    while (QueueIsEmpty(shared_queue))
           ;
    pthread_mutex_lock(&queue_mutex);
    DeQueue(shared_queue);
    printf ("costumer %ld\n", QueueSize(shared_queue));
    pthread_mutex_unlock(&queue_mutex);

    return (NULL);
}
