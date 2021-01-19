/****************************************************************************
* 					written by : orpaz houta								*
* 					review : Gil Mazliah (Gilio:)    						*
*					Last update : 2.6.20 									*
****************************************************************************/
#include <assert.h>     /* assert */
#include <malloc.h>     /* malloc */

#include "hash_table.h"


/*---------------------------------Structs-----------------------------------*/
struct hash_table
{
    dllist_t **table;
    size_t num_of_keys;
    hash_func_t hash_code;
    cmp_func_t cmp;
    void *param;			/* to use in cmp */
};

typedef struct is_match_param
{
	cmp_func_t cmp;
	const void *data;
	void *param;
}is_match_param_t;
/*---------------------------------------------------------------------------*/

/*--------------------------------Macros-------------------------------------*/
#define HASH_SUCCESS (0)
#define HASH_FAILURE (1)
#define HASH_EMPTY (1)
#define HASH_NOT_EMPTY (0)

#ifndef NDEBUG
#define PRINT_ERROR(str) fprintf(stderr, "ERROR( %s : %d ) -- %s\n",\
								 __FILE__, __LINE__ , str)
#else
#define PRINT_ERROR(str)
#endif
/*---------------------------------------------------------------------------*/

/*-------------------------Static Functions----------------------------------*/
static int IsMatchHashT(const void *data1, const void *param);
static iterator_t _FindIter(hash_t *table, dllist_t *bucket, const void *key);
/*---------------------------------------------------------------------------*/

/*-----------------------------Definitions-----------------------------------*/
hash_t *HashCreate(size_t num_of_keys, hash_func_t hash_code,
                   cmp_func_t compare, void *param)
{
    hash_t *new = NULL;

    assert(hash_code);
    assert(compare);

    new = (hash_t *)malloc(sizeof(hash_t));
    if (!new)
    {
        PRINT_ERROR("malloc error in HashCreate\n");

        return (NULL);
    }

    new->table = (dllist_t **)calloc(sizeof(dllist_t *), num_of_keys);

    new->num_of_keys = num_of_keys;
    new->hash_code = hash_code;
    new->cmp = compare;
    new->param = param;

    return (new);
}

void HashDestroy(hash_t *hash_table)
{
    size_t i = 0;

    assert(hash_table);

    for (i = 0; i < hash_table->num_of_keys; ++i)
    {
        if (hash_table->table[i])
        {
            DLListDestroy(hash_table->table[i]);
        }
    }

    free(hash_table->table);
    hash_table->table = NULL;

    hash_table->hash_code = NULL;
    hash_table->cmp = NULL;
    hash_table->param = NULL;

    free(hash_table);
    hash_table = NULL;
}

int HashInsert(hash_t *hash_table, void *key)
{
    size_t bucket = 0;

    assert(hash_table);

    bucket = hash_table->hash_code(key);
    if (!hash_table->table[bucket])
    {
        hash_table->table[bucket] = DLListCreate();
        if (!hash_table->table[bucket])
        {
            PRINT_ERROR("malloc error in DLListCreate");
            return (HASH_FAILURE);
        }
    }

    return (DLListIsSameIterator(DLListPushFront(hash_table->table[bucket],key),
                                 DLListEnd(hash_table->table[bucket])));
}

void HashRemove(hash_t *hash_table, const void *key)
{
    size_t index = 0;
	dllist_t *bucket = NULL;
    iterator_t find = {0};

    assert(hash_table);
    assert(key);

    index = hash_table->hash_code(key);
	bucket = hash_table->table[index];

    if (!hash_table->table[index])
    {
        return; /* EMPTY */
    }

	find = _FindIter(hash_table, bucket, key);

    if (!DLListIsSameIterator(DLListEnd(bucket), find))
    {
        DLListRemove(find);
        find = NULL;
    }
}

void *HashFind(hash_t *hash_table, const void *key)
{
    size_t index = 0;
	dllist_t *bucket = NULL;
    iterator_t find = {0};

    assert(hash_table);
    assert(key);

    index = hash_table->hash_code(key);
	bucket = hash_table->table[index];
    if (!hash_table->table[index])
    {
        return (NULL);
    }

	find = _FindIter(hash_table, bucket, key);

    if (DLListIsSameIterator(DLListEnd(bucket), find))
    {
        return (NULL);
    }

    DLListRemove(find);

    find = DLListPushFront(bucket, (void *)key);

	return (DLListIsSameIterator(DLListEnd(bucket), find)
            ? NULL
            : (DLListGetData(find)));
}

size_t HashSize(const hash_t *hash_table)
{
    size_t i = 0;
    size_t count = 0;

    assert(hash_table);

    for (i = 0; i < hash_table->num_of_keys; ++i)
    {
        if (hash_table->table[i])
        {
            count += DLListSize(hash_table->table[i]);
        }
    }

    return (count);
}

int HashIsEmpty(const hash_t *hash_table)
{
    size_t i = 0;

    assert(hash_table);

    for (i = 0; i < hash_table->num_of_keys; ++i)
    {
        if (hash_table->table[i] && !DLListIsEmpty(hash_table->table[i]))
        {
            return (HASH_NOT_EMPTY);
        }
    }

    return (HASH_EMPTY);
}

int HashForEach(hash_t *hash_table, acion_func_t hash_code, void *param)
{
    size_t i = 0;
    int status = HASH_SUCCESS;

    assert(hash_table);

    for (i = 0; i < hash_table->num_of_keys && HASH_SUCCESS == status; ++i)
    {
        if (hash_table->table[i])
        {

            status =  (DLListForEach(DLListBegin(hash_table->table[i]),
                                    DLListEnd(hash_table->table[i]), hash_code,
                                    param));
        }
    }

    return (status);
}

/*----------------------Static Function Definitons---------------------------*/
static int IsMatchHashT(const void *data1, const void *param)
{
	is_match_param_t *full_param = (is_match_param_t *)param;

	return (!(full_param->cmp(data1, full_param->data, full_param->param)));
}

static iterator_t _FindIter(hash_t *table, dllist_t *bucket, const void *key)
{
    is_match_param_t struct_param = {0};

    assert(table);
    assert(key);

    struct_param.cmp = table->cmp;
    struct_param.data = key;
    struct_param.param = table->param;

    return (DLListFind(DLListBegin(bucket), DLListEnd(bucket), IsMatchHashT,
                       &struct_param));
}
/*---------------------------------------------------------------------------*/
