/*****************************************************************************
* 					written by: Orpaz Houta									 *
* 					review: Izik Avinoam									 *
* 					Last update: 17.5.20									 *
*****************************************************************************/
#include <assert.h> /* assert */
#include <malloc.h> /* malloc */

#include "bst.h"

#define NODE(x) _IteraTorToNode(x)
#define ITER(x) _NodeToIterator(x)

typedef struct bst_node bst_node_t;

struct bst_node
{
    bst_node_t *parent;
    bst_node_t *child[2];
    void *data;
};

struct bst
{
    cmp_func_t direct;
    bst_node_t root;
    void *extention;
};

typedef enum
{
    LEFT,
    RIGHT
}child_t;


/* static funcs */
static bst_iterator_t _CreateNewLeaf(void *data);
static void _DestroyLeaf(bst_iterator_t to_destroy);
static void _TellTheParent(bst_iterator_t dead);
static void _Inherit(bst_iterator_t testator, bst_iterator_t heir);
static void _AttachLeaf(bst_iterator_t parent, bst_iterator_t new, child_t side);
static bst_iterator_t _BSTRoot(const bst_t *bst);
static bst_iterator_t _BSTChild(bst_iterator_t parent, child_t side);
static bst_iterator_t _BSTParent(bst_iterator_t child);
static void _BSTSetData(bst_iterator_t to_set, void *data);
static bst_node_t *_IteraTorToNode(bst_iterator_t to_convert);
static bst_iterator_t _NodeToIterator(bst_node_t *to_convert);


bst_t *BSTCreate(cmp_func_t direct, void *param)
{
    bst_t *new;

    assert( direct);

    new = (bst_t *)malloc(sizeof(bst_t));
	if (!new)
	{
#ifndef NDEBUG
		perror("BSTCreate: ");
#endif
		return NULL;
	}
    new->direct = direct;
    new->extention = param;

    new->root.parent = NULL;
    new->root.child[LEFT] = NULL;
    new->root.child[RIGHT] = NULL;
    new->root.data = (void *)0xDEADBEEF;

	return new;
}

void BSTDestroy(bst_t *bst)
{
    bst_iterator_t destroy = NULL;
    bst_iterator_t parent = NULL;

    assert(bst);

    destroy = BSTBegin(bst);
    while (!BSTIterIsEqual(destroy, BSTEnd(bst)))
    {
        if (!_BSTChild(destroy, RIGHT))
        {
            parent = _BSTParent(destroy);
            _TellTheParent(destroy);
            _DestroyLeaf(destroy);
            destroy = parent;
        }
        else
        {
            destroy = BSTNext(destroy);
        }
    }
    bst->root.parent = NULL;
    bst->root.child[LEFT] = NULL;
    bst->root.child[RIGHT] = NULL;
    bst->root.data = NULL;

    free(bst);
    bst = NULL;
}

size_t BSTSize(const bst_t *bst)
{
    bst_iterator_t iter = NULL;
    size_t count = 0;

    assert(bst);

    for (iter = BSTBegin(bst), count = 0;
         iter != BSTEnd(bst);
         iter = BSTNext(iter), ++count)
         ;
    return count;
}


int BSTIsEmpty(const bst_t *bst)
{
    assert(bst);

    return (!_BSTRoot(bst));
}


bst_iterator_t BSTInsert(bst_t *bst, void *data)
{
    bst_iterator_t parent = NULL;
    bst_iterator_t iterator = NULL;
    bst_iterator_t newborn = NULL;
    int direction = LEFT;

    assert(bst);
    assert(data);

    parent = BSTEnd(bst);
    iterator = _BSTRoot(bst);
                                /* because when it's right it's 'right' */
    for (; iterator; iterator = _BSTChild(parent, (0 < direction)))
    {
        parent = iterator;
        direction = bst->direct(data, BSTGetData(parent), NULL);
    }
    newborn = _CreateNewLeaf(data);
    if(!newborn)
    {
        return BSTEnd(bst);
    }
    _AttachLeaf(parent, newborn, (0 < direction));

    return newborn;
}


void BSTRemove(bst_t *bst, void *data)
{
    bst_iterator_t to_remove = NULL;

    assert(bst);
    assert(data);

    to_remove = BSTFind(bst, data);
    if (!BSTIterIsEqual(BSTEnd(bst), to_remove))
    {
        if (_BSTChild(to_remove, LEFT) && _BSTChild(to_remove, RIGHT))
        {
            _BSTSetData(to_remove, BSTGetData(BSTNext(to_remove)));
            to_remove = BSTNext(to_remove);
        }
        if (_BSTChild(to_remove, RIGHT))
        {
            _Inherit(to_remove, _BSTChild(to_remove, RIGHT));
        }
        else if (_BSTChild(to_remove, LEFT))
        {
            _Inherit(to_remove, _BSTChild(to_remove, LEFT));
        }
        else
        {
            _TellTheParent(to_remove);
            _DestroyLeaf(to_remove);
        }
    }
}


bst_iterator_t BSTBegin(const bst_t *bst)
{
    bst_iterator_t begin;

    assert(bst);

    for (begin = BSTEnd(bst);
    _BSTChild(begin, LEFT);
    begin = _BSTChild(begin, LEFT))
    ;
    return begin;
}


bst_iterator_t BSTEnd(const bst_t *bst)
{
    assert(bst);

    return (bst_iterator_t)&bst->root;
}


bst_iterator_t BSTPrev(bst_iterator_t prev)
{
    bst_iterator_t parent;

    assert(prev);

    parent = _BSTParent(prev);
    if (!_BSTChild(prev, LEFT))
    {
        if (BSTIterIsEqual(_BSTChild(parent, RIGHT), prev))
        {
            return parent;
        }
        else
        {
            for (; BSTIterIsEqual(_BSTChild(parent, LEFT), prev)
                 ; prev = parent, parent = _BSTParent(parent))
            ;
            return parent;
        }
    }
    for (prev = _BSTChild(prev, LEFT);
        _BSTChild(prev, RIGHT);
        prev = _BSTChild(prev, RIGHT))
    ;
    return prev;
}


bst_iterator_t BSTNext(bst_iterator_t next)
{
    bst_iterator_t parent = NULL;

    assert(next);

    parent = _BSTParent(next);
    if (!_BSTChild(next, RIGHT))
    {
        if (BSTIterIsEqual(_BSTChild(parent, LEFT), next))
        {
            return parent;
        }
        else
        {
            for (; BSTIterIsEqual(_BSTChild(parent, RIGHT), next)
                 ;next = parent, parent = _BSTParent(parent))
            ;
            return parent;
        }
    }
    for (next = _BSTChild(next, RIGHT);
        _BSTChild(next, LEFT) ;
        next = _BSTChild(next, LEFT))
    ;
    return next;
}


int BSTIterIsEqual(bst_iterator_t iter1, bst_iterator_t iter2)
{
    return (iter1 == iter2);
}


void *BSTGetData(bst_iterator_t iter)
{
    return (NODE(iter)->data);
}


bst_iterator_t BSTFind(const bst_t *bst, const void *data)
{
    bst_iterator_t search = NULL;
    int is_match = 0;

    assert(bst);

    for (search = _BSTRoot(bst); search;
         search = _BSTChild(search, (0 < is_match)))
    {
        is_match = bst->direct(data, BSTGetData(search), bst->extention);
        if (!is_match)
        {
            return search;
        }
    }

    return BSTEnd(bst);
}

int BSTForEach(bst_iterator_t from, bst_iterator_t to,
               callback_func_t CallBack, void *param)
{
    int status = 0;

    assert(from);
    assert(to);
    assert(CallBack);

    for (; !BSTIterIsEqual(from, to) && !status; from = BSTNext(from))
    {
        status = CallBack(BSTGetData(from), param);
    }
    return status;
}


/* creates a new leaf and initialise it's data */
static bst_iterator_t _CreateNewLeaf(void *data)
{
    bst_node_t *new = (bst_node_t *)malloc(sizeof(bst_node_t));
    if (!new)
    {
#ifndef NDEBUG
        perror("_CreateNewLeaf: ");
#endif
        return NULL;
    }
    new->parent = NULL;
    new->child[LEFT] = NULL;
    new->child[RIGHT] = NULL;
    new->data = data;

    return (ITER(new));
}

/* connect a new leaf by apdate it to point to it's parent and reverse */
static void _AttachLeaf(bst_iterator_t parent, bst_iterator_t new, child_t side)
{
    assert(parent);
    assert(new);

    NODE(parent)->child[side] = new;
    NODE(new)->parent = parent;
}

/* destroys a given node */
static void _DestroyLeaf(bst_iterator_t to_destroy)
{
    assert(to_destroy);

    NODE(to_destroy)->parent = NULL;
    NODE(to_destroy)->child[LEFT] = NULL;
    NODE(to_destroy)->child[RIGHT] = NULL;
    NODE(to_destroy)->data = NULL;

    free(to_destroy);
    to_destroy = NULL;
}

/* 'heir' replaces it's 'testator' by changing the testator parent to point
    the heir and reverse and destroy the testator */
static void _Inherit(bst_iterator_t testator, bst_iterator_t heir)
{
    bst_iterator_t grandpa;
    child_t side;

    assert(testator);
    assert(heir);

    grandpa = _BSTParent(testator);
    side = (BSTIterIsEqual(_BSTChild(grandpa, LEFT), testator)) ? LEFT : RIGHT;
    _AttachLeaf(grandpa, heir, side);
    _DestroyLeaf(testator);
}

/* update the parent its left or right is NULL */
static void _TellTheParent(bst_iterator_t dead)
{
    bst_iterator_t parent;
    child_t side = 0;

    assert(dead);

    parent = _BSTParent(dead);
    side = (BSTIterIsEqual(_BSTChild(parent, LEFT), dead)) ? LEFT : RIGHT;
    NODE(parent)->child[side] = NULL;
}

static bst_iterator_t _BSTRoot(const bst_t *bst)
{
    assert(bst);

    return (ITER(bst->root.child[LEFT]));
}

static bst_iterator_t _BSTChild(bst_iterator_t parent, child_t side)
{
    assert(parent);

    return (ITER(NODE(parent)->child[side]));
}

static bst_iterator_t _BSTParent(bst_iterator_t child)
{
    assert(child);

    return (ITER(NODE(child)->parent));
}

static void _BSTSetData(bst_iterator_t to_set, void *data)
{
    assert(to_set);

    NODE(to_set)->data = data;
}

/* converts iterator to node (for maintainance) */
static bst_node_t *_IteraTorToNode(bst_iterator_t to_convert)
{
    return (bst_node_t *)to_convert;
}
/* converts node to iterator (for maintainance) */
static bst_iterator_t _NodeToIterator(bst_node_t *to_convert)
{
    return (bst_iterator_t)to_convert;
}
