/****************************************************************************
* 					written by : orpaz houta								*
* 					review : Elimelech billet  								*
*					Last update : 12.7.20 									*
****************************************************************************/
#include <stdio.h>      /* printf */
#include <malloc.h>     /* malloc */
#include <assert.h>     /* assert */
#include <pthread.h>    /* pthread_t */

#define NUM_OF_THREADS        (100)
#define NUM_OF_DICTS          (100)
#define THREAD_RANGE(size)    ((size * NUM_OF_DICTS) / NUM_OF_THREADS)

static void *SumLetters(void *param);
static size_t GetSizeOfFile(void);
static void _InitBigData(char *sg_big_data, size_t dict_size);


static size_t sg_size_of_dict = 0;
static char *sg_big_data = NULL;

int main()
{
    size_t i = 0;
    pthread_t counter_id[NUM_OF_THREADS] = {0};
    size_t total_num_of_letters = 0;
    size_t exit_val = 0;
    size_t param = 0;


    sg_size_of_dict = GetSizeOfFile();
    sg_big_data = (char *)malloc(sg_size_of_dict * sizeof(char) * NUM_OF_DICTS);
    _InitBigData(sg_big_data, sg_size_of_dict);
    printf("amount of letters in %d: %ld\n", NUM_OF_DICTS,
          (sg_size_of_dict * NUM_OF_DICTS));

    for(i = 0; i < NUM_OF_THREADS; ++i, param += THREAD_RANGE(sg_size_of_dict))
    {
        while (pthread_create(&counter_id[i], NULL, SumLetters, &param));
    }

    for (i = 0; i < NUM_OF_THREADS; ++i)
    {
        pthread_join(counter_id[i], (void *)&exit_val);
        total_num_of_letters += exit_val;
    }

    total_num_of_letters += ((NUM_OF_THREADS * THREAD_RANGE(sg_size_of_dict)) %
                              sg_size_of_dict);
    printf("total_num_of_letters = %ld\n", total_num_of_letters);
    free(sg_big_data);

    return (0);
}

static void *SumLetters(void *param)
{
    char *letter_to_count = &sg_big_data[(size_t)param];
    size_t sum_of_letters = 0;
    size_t i = 0;
    size_t j = 0;
    char temp = 0;

    for (i = 0; i < THREAD_RANGE(sg_size_of_dict); ++i)
    {
        /* useless operation to give the thread more work */
        for (j = 0; j < 1000; ++j)
        {
            if (letter_to_count[i] != 'a' && letter_to_count[i] != 'z')
            {
                temp = letter_to_count[i];
                letter_to_count[i] = j;
                sum_of_letters += j;
                letter_to_count[i] = temp;
            }
            if (letter_to_count[i] != 'a' && letter_to_count[i] != 'z')
            {
                temp = letter_to_count[i];
                letter_to_count[i] = j;
                sum_of_letters -= j;
                letter_to_count[i] = temp;
            }
        }

        ++sum_of_letters;
    }

    return ((void *)sum_of_letters);
}

static size_t GetSizeOfFile(void)
{
    size_t sg_size_of_dict = 0;
    FILE *words = NULL;

    assert(words);

    words = fopen("/usr/share/dict/american-english", "r");
    fseek(words, 0, SEEK_END);
    sg_size_of_dict = ftell(words);

    fclose(words);

    return (sg_size_of_dict);
}

static void _InitBigData(char *sg_big_data, size_t dict_size)
{
    size_t i = 0;
    FILE *words = fopen("/usr/share/dict/american-english", "r");

    assert(words);

    for (i = 0; i <= NUM_OF_DICTS; ++i)
    {
        while (dict_size != fread(sg_big_data, sizeof(char), dict_size, words));
        rewind(words);
    }

    fclose(words);
}
