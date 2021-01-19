/****************************************************************************
* 					written by : orpaz houta								*
* 					review : Gil Mazliah (Gilio:)    						*
*					Last update : 2.6.20 									*
****************************************************************************/
#include <assert.h>     /* assert */
#include <string.h>     /* strlen */
#include <stdarg.h>     /* va_start, va_list, va_end */

#include "hash_table.h"
#include "ca_test_util.h" 	/* ©️ chanan & aviv */

#define NUMBER_OF_WORDS (102305)
#define LOAD_FACTOR (0.75)
#define DICT_NUM_OF_KEYS (size_t)((double)(NUMBER_OF_WORDS / LOAD_FACTOR))

void SanityTest();
void SpellCheckerTest();

static int IsBigger(const void *data1, const void *data2, void *param);
static size_t HashInt(const void *key);
static int PrintMe(int *to_print, int *param);
static int PrintWord(char *to_print, char *param);
static size_t HashLoad(const void *key);
static int IsInDictionary(hash_t *dictionary, const char *word);
static void SpellChecker(hash_t *dictionary);

int main()
{
    SanityTest();
    SpellCheckerTest();

    TEST_SUMMARY();

    return 0;
}

void SanityTest()
{
    int key1 = 1;
    int key2 = 2;
    int key3 = 3;
    int key4 = 4;
    int key5 = 5;
    int key6 = 6;
    int param = 0;
    hash_t *test_ht = HashCreate(5, HashInt, IsBigger, &param);

    INT_TEST(1, HashIsEmpty(test_ht));

    INT_TEST(0, HashInsert(test_ht, &key1));
    INT_TEST(0, HashInsert(test_ht, &key2));
    INT_TEST(0, HashInsert(test_ht, &key3));
    INT_TEST(0, HashInsert(test_ht, &key4));
    INT_TEST(0, HashInsert(test_ht, &key5));
    INT_TEST(0, HashInsert(test_ht, &key6));

    INT_TEST(0, HashIsEmpty(test_ht));
    INT_TEST(6, HashSize(test_ht));

    INT_TEST(0, HashForEach(test_ht, (acion_func_t)PrintMe, &key6));
    printf("\n");

    INT_TEST(key1, *(int *)HashFind(test_ht, &key1));
    INT_TEST(key2, *(int *)HashFind(test_ht, &key2));
    INT_TEST(key5, *(int *)HashFind(test_ht, &key5));
    INT_TEST(key6, *(int *)HashFind(test_ht, &key6));

    HashRemove(test_ht, &key1);
    INT_TEST(5, HashSize(test_ht));
    HashRemove(test_ht, &key6);
    INT_TEST(4, HashSize(test_ht));
    HashRemove(test_ht, &key3);
    INT_TEST(3, HashSize(test_ht));
    HashRemove(test_ht, &key4);
    INT_TEST(2, HashSize(test_ht));

    HashDestroy(test_ht);
}

void SpellCheckerTest()
{
    int param = 0;
    hash_t *test_load = HashCreate(DICT_NUM_OF_KEYS, HashLoad, IsBigger, &param);
    FILE *words = NULL;
    char *dictionary = (char *)malloc(1000000);
    char *to_free = dictionary;

    INT_TEST(1, HashIsEmpty(test_load));

    words = fopen("/usr/share/dict/american-english", "r");

    assert(words);

    while (EOF != fscanf(words, "%s", dictionary))
    {
        INT_TEST(0, HashInsert(test_load, dictionary));
        dictionary = dictionary + (strlen(dictionary) + 1);
    }

    INT_TEST(0, HashForEach(test_load, (acion_func_t)PrintWord, &param));
    printf("\n");

    INT_TEST((NUMBER_OF_WORDS), HashSize(test_load));

    SpellChecker(test_load);

    HashDestroy(test_load);

    free(to_free);

    fclose(words);
    dictionary = NULL;
}

static size_t HashInt(const void *key)
{
    size_t index = (size_t)*(int *)key;
    index %= 5;

    return index;
}

static int IsBigger(const void *data1, const void *data2, void *param)
{
    assert(param != (void *)0xDEADBEEF);

    return (*(int *)data1 - *(int *)data2);
}

static int PrintMe(int *to_print, int *param)
{
    printf("%d, ", *to_print);
    if (*to_print == *param)
    {
        printf("arrived param\n");
    }
    return 0;
}

static int PrintWord(char *to_print, char *param)
{
    printf("%s\n", to_print);
    if (*to_print == *param)
    {
        printf("arrived param\n");
    }
    return 0;
}

static size_t HashLoad(const void *key)
{
    char *word = (char *)key;
    int sum_ascii = 0;
    size_t index = 0;
    int i = 0;

    assert(key);

    sum_ascii = (isupper(word[0])) ? (word[0] + ('a' - 'A')) : word[0];

    for (i = 1; '\0' != word[i]; ++i)
    {
        sum_ascii += (1 << i * word[i]);
    }

    index = sum_ascii % DICT_NUM_OF_KEYS;

    return index;
}


static int IsInDictionary(hash_t *dictionary, const char *word)
{
    char *find_resault = NULL;

    assert(dictionary);
    assert(word);

    find_resault = (char*)(HashFind(dictionary, word));

    return (!(!find_resault));
}

static void SpellChecker(hash_t *dictionary)
{
    char input[25] = {'\0'};
    int result = 0;

    while (*input != '0')
    {
        printf("\nPlease enter a word or '0' to exit \n\n");
        scanf("%s", input);
        result = IsInDictionary(dictionary, input);
        if (result)
        {
            printf("%s is well spelled\n", input);
        }
        else if (*input != '0')
        {
            printf("%s is misspelled\n", input);
        }
    }
}
