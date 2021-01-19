/*****************************************************************************
* 					written by : Orpaz Houta								 *
* 					review : Izik Avinoam   								 *
* 					Last update : 29.6.20									 *
****************************************************************************/
#include <stdio.h>      /* printf()         */
#include <semaphore.h>  /* semaphore funcs  */
#include <stdatomic.h>  /* atomic_int       */

#include <pthread.h>    /* pthread funcs    */

#ifndef NDEBUG
#define ERR_MESSAGE(x) (perror(x))
#else
#endif  /* NDEBUG */

#define UNUSED(x) ((void)x)

#define NUM_OF_THREADS (100)
#define FSQ_SIZE (10)

typedef struct fsq
{
    int queue[FSQ_SIZE];
    atomic_int head;
    atomic_int rear;
}fsq_t;

/* ------------------------------------------------------------------------- */
static void _FsqPush(int element);
static int _FsqPop(void);
static void *_Producer(void *data);
static void *_Consumer(void *data);
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
static fsq_t fsq = {0};
static pthread_mutex_t fsq_lock = PTHREAD_MUTEX_INITIALIZER;
static int push_item = 10;
/* ------------------------------------------------------------------------- */

int main()
{
    pthread_t producer_id[NUM_OF_THREADS];
    pthread_t consumer_id[NUM_OF_THREADS];
    void *retval = NULL;
    size_t i = 0;

    for (i = 0; i < NUM_OF_THREADS; ++i)
    {
        pthread_create(&producer_id[i], NULL, _Producer, NULL);
        pthread_create(&consumer_id[i], NULL, _Consumer, NULL);
    }

    for (i = 0; i < NUM_OF_THREADS; ++i)
    {
        pthread_join(consumer_id[i], &retval);
        pthread_join(producer_id[i], &retval);
    }

    return (0);
}

static void *_Producer(void *useless)
{
    UNUSED(useless);

    pthread_mutex_lock(&fsq_lock);
    _FsqPush(push_item);
    pthread_mutex_unlock(&fsq_lock);

    return (NULL);
}

static void *_Consumer(void *useless)
{
    int item = 0;

    UNUSED(useless);

    pthread_mutex_lock(&fsq_lock);
    item = _FsqPop();
    pthread_mutex_unlock(&fsq_lock);

    return ((void*)(size_t)item);
}

static int _FsqPop(void)
{
    int to_return = 0;
    to_return = fsq.queue[fsq.head];

    atomic_fetch_add(&fsq.head, 1);
    fsq.head = (fsq.head % FSQ_SIZE);

    return (to_return);
}

static void _FsqPush(int element)
{
    fsq.queue[fsq.rear] = element;

    atomic_fetch_add(&fsq.rear, 1);
    fsq.rear = (fsq.rear % FSQ_SIZE);
}
