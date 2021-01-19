/*****************************************************************************
* 					written by : Orpaz Houta								 *
* 					review : Izik Avinoam   								 *
* 					Last update : 29.6.20									 *
****************************************************************************/
#include <stdio.h>      /* printf()     */
#include <pthread.h>    /* threads      */
#include <semaphore.h>  /* sem_init()   */

/* ------------------------------------------------------------------------- */
#define NUM_OF_READERS (10)
#define FAILURE        (1)
#define UNUSED(x)      ((void)x) /* For unused parameters */
/* ------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------- */
void *_Writer(void *useless);
void *_Reader(void *useless);
/* ------------------------------------------------------------------------- */

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
sem_t is_read = {0};
int message = 0;
int sum = 0;
size_t counter = 10;

int main()
{
    pthread_t writer_id = 0;
    pthread_t reader_id[NUM_OF_READERS] = {0};
    size_t i = 0;

    if (0 != sem_init(&is_read, 0, 0))
    {
        perror("\nsem_init");
        return FAILURE;
    }

    while (pthread_create(&writer_id, NULL, _Writer, NULL));

    for (i = 0; NUM_OF_READERS > i; ++i)
    {
        while (pthread_create(&reader_id[i], NULL, _Reader, NULL));
    }

    pthread_join(writer_id, NULL);

    for (i = 0; NUM_OF_READERS > i; ++i)
    {
        pthread_join(reader_id[i], NULL);
    }

    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);

    return (0);
}

/* ------------------------------------------------------------------------- */
void *_Writer(void *useless)
{
    UNUSED(useless);

    while (counter)
    {
        sem_wait(&is_read);
        pthread_mutex_lock(&lock);
        ++message;
        pthread_cond_broadcast(&cond);
        pthread_mutex_unlock(&lock);
    }

    return (NULL);
}

void *_Reader(void *useless)
{
    UNUSED(useless);

    while (counter)
    {
        pthread_mutex_lock(&lock);
        ++sum;

        if (sum == NUM_OF_READERS)
        {
            printf("sum of readers:%d\n", sum);
            sum = 0;
            --counter;
            sem_post(&is_read);
        }

        pthread_cond_wait(&cond, &lock);
        printf("The message is:%d\n", message);
        pthread_mutex_unlock(&lock);
    }

    return (NULL);
}
