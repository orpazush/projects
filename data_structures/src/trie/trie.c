/******************************************************************************
 *                      code by : Orpaz Houta                                 *
 *                      review by : Alex Sevostyanov                          *
 *                      coding date - 11-06-2020                              *
 ******************************************************************************/
#include <malloc.h> /* malloc */
#include <assert.h> /* assert */
#include <stdio.h>  /* assert */
#include <math.h>   /* pow */

#include "trie.h"

/*---------------------------------Structs-----------------------------------*/
typedef struct trie_node
{
    struct trie_node *sub_trie[2];
    char is_full;
}trie_node_t;

struct trie
{
    trie_node_t root;
    size_t height;
};
/*---------------------------------------------------------------------------*/

/*--------------------------------Macros-------------------------------------*/
#ifndef NDEBUG
#define PRINT_ERROR(str) fprintf(stderr, "ERROR( %s : %d ) -- %s\n",\
							     __FILE__, __LINE__ , str)
#else
#define PRINT_ERROR(str)
#endif

#define MASK_BIT (1)

enum is_full
{
    NOT_FULL,
    FULL
};

enum find
{
    NOT_FOUND_IN_TRIE,
    FOUND_IN_TRIE
};

enum state
{
    TRIE_SUCCESS,
    TRIE_FAILED,
    NOT_IN_TRIE,    /* used in TrieRemove */
    REMOVE_STATE    /* used in TrieRemove */
};
/*---------------------------------------------------------------------------*/

/*---------------------------Static Functions--------------------------------*/
static trie_node_t *_CreateNode();
static void _ClearTrie(trie_node_t *to_destroy);
static int _InsertPath(trie_node_t *node, size_t path, size_t index);
static int _RemovePath(trie_node_t *node, const size_t path, size_t index);
static size_t _Count(const trie_node_t *node, size_t height);
static char _UpdateIsFull(trie_node_t *node);
static int _FindRequest(const trie_node_t *node, size_t index, size_t request);
static int _GetNext(const trie_node_t *node, const size_t request, size_t index,
                    size_t *result);
static int _FindMin(trie_node_t *node, size_t index, size_t *result);
static void UpdateResult(size_t *result, size_t index, size_t bit);
/*---------------------------------------------------------------------------*/

/*---------------------------Main Definitions--------------------------------*/
trie_t *TrieCreate(size_t height)
{
    trie_t *new = (trie_t *)malloc(sizeof(trie_t));
    if (!new)
    {
        PRINT_ERROR("malloc error in TrieCreate\n");

        return (NULL);
    }

    new->root.sub_trie[0] = NULL;
    new->root.sub_trie[1] = NULL;
    new->root.is_full = NOT_FULL;

    new->height = height;

    return (new);
}

void TrieDestroy(trie_t *trie)
{
    if (trie)
    {
        _ClearTrie(trie->root.sub_trie[0]);
        _ClearTrie(trie->root.sub_trie[1]);

        free(trie);
        trie = NULL;
    }
}

int TrieInsert(trie_t *trie, size_t path)
{
    assert(trie);

    return (_InsertPath(&trie->root, path, (trie->height)));
}

int TrieRemove(trie_t *trie, const size_t path)
{
    assert(trie);

    return (NOT_IN_TRIE == _RemovePath(&trie->root, path, trie->height));
}

size_t TrieSize(const trie_t *trie)
{
    assert(trie);

    return (_Count(&trie->root, trie->height));

}

int IsInTrie(const trie_t *trie, const size_t request)
{
    assert(trie);

    return (_FindRequest(&trie->root, trie->height, request));
}

size_t TrieGetNext(const trie_t *trie, const size_t request)
{
    size_t result = 0;

    _GetNext(&trie->root, request, trie->height, &result);

    return (result);
}

int TrieIsEmpty(const trie_t *trie)
{
    assert(trie);

    return (!trie->root.sub_trie[0] && !trie->root.sub_trie[1]);
}
/*---------------------------------------------------------------------------*/

/*-------------------------------Static Definitions--------------------------*/
/* creates & initiates a new node */
static trie_node_t *_CreateNode()
{
    trie_node_t *new = (trie_node_t *)malloc(sizeof(trie_node_t));
    if (!new)
    {
        PRINT_ERROR("malloc error in TrieCreate\n");

        return (NULL);
    }

    new->sub_trie[0] = NULL;
    new->sub_trie[1] = NULL;
    new->is_full = NOT_FULL;

    return (new);
}

/* destroys all the nodes in the trie 'to_destroy' */
static void _ClearTrie(trie_node_t *to_destroy)
{
    if (to_destroy)
    {
        _ClearTrie(to_destroy->sub_trie[0]);
        _ClearTrie(to_destroy->sub_trie[1]);

        to_destroy->sub_trie[0] = NULL;
        to_destroy->sub_trie[1] = NULL;

        free(to_destroy);
        to_destroy = NULL;
    }
}

/* inserts a new 'path' (meaning element) to the trie */
static int _InsertPath(trie_node_t *node, size_t path, size_t index)
{
    int status = 0;
    int bit = 0;

    if (node->is_full || !index)
    {
        node->is_full = FULL;
        return (TRIE_SUCCESS);
    }

    bit = ((path >> (index - 1)) & MASK_BIT);
    if (!node->sub_trie[bit])
    {
        node->sub_trie[bit] = _CreateNode();
        if (!node->sub_trie[bit])
        {
            return (TRIE_FAILED);
        }
    }
    status = _InsertPath(node->sub_trie[bit], path, (index - 1));
    /* if the other sub_trie exist the node is full */
    node->is_full = _UpdateIsFull(node);

    return (status);
}

/* deletes a given 'path' (meaning element) from the trie */
static int _RemovePath(trie_node_t *node, const size_t path, size_t index)
{
    int status = 0;
    int bit = 0;

    if (!node)
    {
        return (NOT_IN_TRIE);
    }

    else if (0 == index)
    {
        node->is_full = NOT_FULL;
        return (REMOVE_STATE);
    }

    bit = ((path >> (index - 1)) & MASK_BIT);
    status = _RemovePath(node->sub_trie[bit], path, (index - 1));

    if (REMOVE_STATE == status)
    {
        free(node->sub_trie[bit]);
        node->sub_trie[bit] = NULL;
        node->is_full = _UpdateIsFull(node);

        return ((node->sub_trie[!bit]) ? TRIE_SUCCESS : REMOVE_STATE);
    }

    node->is_full = _UpdateIsFull(node);

    return (status);
}

/* counts the elements the trie holds */
static size_t _Count(const trie_node_t *node, size_t height)
{
    size_t count = 0;

    if (!node)
    {
        return 0;
    }

    if (node->is_full)
    {
        return (pow(2,height));
    }

    count += _Count(node->sub_trie[0], (height - 1));
    count += _Count(node->sub_trie[1], (height - 1));

    return (count);
}

/* updates the is_full member after relevant changes (insert & remove) */
static char _UpdateIsFull(trie_node_t *node)
{
    return (node->sub_trie[0] && node->sub_trie[1]
            && node->sub_trie[0]->is_full && node->sub_trie[1]->is_full);
}

/* checks whether a given 'request' is in the trie */
static int _FindRequest(const trie_node_t *node, size_t index, size_t request)
{
    int bit = 0 ;

    if (!node)
    {
        return (NOT_FOUND_IN_TRIE);
    }

    if (!index)
    {
        return (FOUND_IN_TRIE);
    }

    bit = ((request >> (index - 1)) & MASK_BIT);

    return (_FindRequest(node->sub_trie[bit], (index - 1), request));
}

/* gets the first non exist in trie element which is bigger then 'request'
   and update results accordingly.
   NOTE - this function used only when knowing that the request is in the 'trie'.
   sending a request which is not in the 'trie' will cause undefined behaviour */
static int _GetNext(const trie_node_t *node, const size_t request, size_t index,
                    size_t *result)
{
        int bit = ((request >> (index - 1)) & MASK_BIT);
        int status = 0;

        /* follow the request path until reach the point where the node is full
           then it will go back recursievly to the node befor and treat it there */
        if (node->is_full)
        {
            return (FULL);
        }

        status = _GetNext(node->sub_trie[bit], request, (index - 1), result);

        /* case the node after this node according to the request returned as full */
        if (status && ((!node->sub_trie[!bit])
                    || (!node->sub_trie[!bit]->is_full)))
        {
            bit = !bit;
            status = _FindMin(node->sub_trie[bit], (index - 1), result);
        }

        if (!status)
        {
            UpdateResult(result, (index - 1) , bit);
        }

        return (status);
    }

/* search for the first non exist element in a trie after a certain point 'index'
   and update result accordingly */
static int _FindMin(trie_node_t *node, size_t index, size_t *result)
{
    int status = 0;
    int bit = 0;

    /* if reached a non exist node the result will be left (0) from this
       point all the way down */
    if (!node)
    {
        UpdateResult(result, index, 0);
        return (TRIE_SUCCESS);
    }

    /* if the function can go to the left (0) it will go there first */
    bit = (!node->sub_trie[0] || !node->sub_trie[0]->is_full) ? 0 : 1;

    status = _FindMin(node->sub_trie[bit], (index - 1), result);

    UpdateResult(result, (index - 1), bit);

    return (status);
}

/* sets the result with the relevant bit */
static void UpdateResult(size_t *result, size_t index, size_t bit)
{
    *result |= (bit << index);
}
/*---------------------------------------------------------------------------*/
