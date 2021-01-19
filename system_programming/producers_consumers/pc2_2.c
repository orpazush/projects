/*****************************************************************************
* 					written by : Orpaz Houta								 *
* 					review : Izik Avinoam   								 *
* 					Last update : 29.6.20									 *
****************************************************************************/
#include <stdio.h>      /* printf */
#include <semaphore.h>  /* sem_t, sem_init, sem_wait.. */

#include <pthread.h>    /* pthread_t */

#include "queue.h"  /* QueueCreate, EnQueue */


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

/* ------------------------------------------------------------------------- */
static void *_Producer(void* param);
static void *_Consumer(void* param);
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
int g_item = 1;
queue_t *g_shared_queue = NULL;
sem_t g_is_empty_queue = {0};
pthread_mutex_t g_queue_mutex = PTHREAD_MUTEX_INITIALIZER;
/* ------------------------------------------------------------------------- */

int main ()
{
    size_t i = 0;
    pthread_t producer_id[NUM_OF_THREADS] = {0};
    pthread_t consumer_id[NUM_OF_THREADS] = {0};

    if (sem_init(&g_is_empty_queue, 0, 0))
    {
        perror("\nsem_init: ");

        return (FAILURE);
    }

    g_shared_queue = QueueCreate();
    if (!g_shared_queue)
    {
        PRINT_ERROR("\nmalloc failed in QueueCreate\n");
        sem_destroy(&g_is_empty_queue);

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

    printf ("%ld\n", QueueSize(g_shared_queue));

    QueueDestroy(g_shared_queue);
    sem_destroy(&g_is_empty_queue);

    return (SUCCESS);
}

static void *_Producer(void* param)
{
    UNUSED(param);

    pthread_mutex_lock(&g_queue_mutex);
    if (EnQueue(g_shared_queue, &g_item))
    {
        printf("\nEnQueue failed\n");
    }
    printf ("producer %ld\n", QueueSize(g_shared_queue));
    sem_post(&g_is_empty_queue);
    pthread_mutex_unlock(&g_queue_mutex);

    return (NULL);
}

static void *_Consumer(void* param)
{
    UNUSED(param);

    sem_wait(&g_is_empty_queue);
    pthread_mutex_lock(&g_queue_mutex);
    DeQueue(g_shared_queue);
    printf ("costumer %ld\n", QueueSize(g_shared_queue));
    pthread_mutex_unlock(&g_queue_mutex);

    return (NULL);
}
