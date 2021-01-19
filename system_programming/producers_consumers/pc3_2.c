/*****************************************************************************
* 					written by : Orpaz Houta								 *
* 					review : Izik Avinoam   								 *
* 					Last update : 29.6.20									 *
****************************************************************************/
#include <stdio.h>            /* printf */
#include <semaphore.h>        /* sem_t, sem_init, sem_wait.. */

#include <pthread.h>          /* pthread_t */

#include "circular_buffer.h"  /* BufCreate, BufRead.. */

#ifndef NDEBUG
#define PRINT_ERROR(str) fprintf(stderr, "ERROR( %s : %d ) -- %s\n",\
                                 __FILE__, __LINE__, str)
#else
#define PRINT_ERROR(str)
#endif

#define UNUSED(x)      ((void)x)
#define ERROR          (-1)
#define QUEUE_CAPACITY (50)
#define NUM_OF_THREADS (50)
#define INT_SIZE       (sizeof(int))

/* ------------------------------------------------------------------------- */
static void *_Producer(void* param);
static void *_Consumer(void* param);
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
static int item = 33333;
static buffer_t *shared_queue = NULL;
static sem_t is_full = {0};
static sem_t is_empty = {0};
static pthread_mutex_t producers_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t consumers_mutex = PTHREAD_MUTEX_INITIALIZER;
/* ------------------------------------------------------------------------- */

int main ()
{
    size_t i = 0;
    pthread_t producer_id[NUM_OF_THREADS] = {0};
    pthread_t consumer_id[NUM_OF_THREADS] = {0};

    shared_queue = BufCreate(QUEUE_CAPACITY * INT_SIZE);
    if (!shared_queue)
    {
        PRINT_ERROR("\nmalloc failed in QueueCreate\n");

        return (ERROR);
    }

    if (sem_init(&is_full, 0, QUEUE_CAPACITY))
    {
        perror("\nsem_init");
        BufDestroy(shared_queue);

        return (ERROR);
    }

    if (sem_init(&is_empty, 0, 0))
    {
        perror("\nsem_init");
        BufDestroy(shared_queue);
        sem_destroy(&is_full);

        return (ERROR);
    }

    printf("available space in queue (ints): %ld\n",
    (BufAvailableSpace(shared_queue) / INT_SIZE));

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

    printf("available space in queue (ints): %ld\n",
          (BufAvailableSpace(shared_queue) / INT_SIZE));

    BufDestroy(shared_queue);
    sem_destroy(&is_full);
    sem_destroy(&is_empty);

    return 0;
}

static void *_Producer(void* param)
{
    UNUSED(param);

    sem_wait(&is_full);
    pthread_mutex_lock(&producers_mutex);
    if (ERROR == BufWrite(shared_queue, &item, INT_SIZE))
    {
        printf("\nis_full failed\n");
    }
    printf("producer %ld item %d\n",
          (BufAvailableSpace(shared_queue) / INT_SIZE), item);
    pthread_mutex_unlock(&producers_mutex);
    sem_post(&is_empty);

    return (NULL);
}

static void *_Consumer(void* param)
{
    UNUSED(param);

    sem_wait(&is_empty);
    pthread_mutex_lock(&consumers_mutex);
    if (ERROR == BufRead(shared_queue, &item, INT_SIZE))
    {
        printf("\nis_empty failed\n");
    }
    printf("costumer %ld item %d\n",
          (BufAvailableSpace(shared_queue) / INT_SIZE), item);
    pthread_mutex_unlock(&consumers_mutex);
    sem_post(&is_full);

    return (NULL);
}
