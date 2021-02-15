/****************************************************************************
* 					written by : orpaz houta								*
* 					review : Izik Avinoam    								*
*					Last update : 2.6.20 									*
****************************************************************************/
#include <assert.h> /* assert */
#include <malloc.h> /* malloc */

#include "avl.h"

/*--------------------------structs & enums----------------------------------*/
typedef struct avl_node avl_node_t;

struct avl_node
{
    void *data;
    avl_node_t *child[2];
    size_t height;
};

struct avl
{
    cmp_func_t key;
    avl_node_t *root;
    void *param;
};

typedef enum
{
    LEFT,
    RIGHT
}side_t;

#define NO_SUCH_ORDER (-1)
#define MATCH (0)
#define SUCCESS (0)
/*----------------------------------------------------------------------------*/

/*-----------------------------static functions-------------------------------*/
static avl_node_t *_CreateNewLeaf(void *data);
static avl_node_t *_KeyInsert(avl_t *avl, avl_node_t *locate, void *data);
static void _DestroyLeaf(avl_node_t *to_destroy);
static void _AVLClear(avl_node_t *to_destroy);
static size_t _Count(avl_node_t *element);
static void *_Find(const avl_t *avl, avl_node_t *seek, const void *data);
static int _ForEachPreOrder(avl_node_t *node, callback_func_t func, void* param);
static int _ForEachInOrder(avl_node_t *node, callback_func_t func, void* param);
static int _ForEachPostOrder(avl_node_t *node, callback_func_t func, void* param);
static avl_node_t *_RemoveNode(avl_t *avl, avl_node_t *remove, const void *data);
static void *_GetPrevData(avl_node_t *prev);
static avl_node_t *_Balance(avl_node_t *unbalanced, side_t side);
static avl_node_t *_Rotate(avl_node_t *unbalanced, side_t direction);
static long _BalanceFactor(avl_node_t *parent, side_t side);
static size_t _Getheight(avl_node_t *node);
/*----------------------------------------------------------------------------*/


avl_t *AVLCreate(cmp_func_t key, void *param)
{
    avl_t *new = NULL;

    assert(key);

    new = (avl_t *)malloc(sizeof(avl_t));
    if (!new)
    {
#ifndef NDEBUG
        perror("AVLCreate: ");
#endif
        return (NULL);
    }
    new->root = NULL;
    new->key = key;
    new->param = param;

    return (new);
}

void AVLDestroy(avl_t *avl)
{
    assert(avl);

    _AVLClear(avl->root);
    avl->root = NULL;
    avl->key = NULL;
    avl->param = NULL;
    free(avl);
    avl = NULL;
}

void AVLRemove(avl_t *avl, const void *data)
{
    assert(avl);
    assert(data);

    avl->root = _RemoveNode(avl, avl->root, data);
}

int AVLInsert(avl_t *avl, void *data)
{
    avl_node_t *returned;

    assert(avl);
    assert(data);

    returned = _KeyInsert(avl, avl->root, data);
    avl->root = (!returned) ? avl->root : returned;

    return (!returned);
}

size_t AVLHeight(const avl_t *avl)
{
    assert(avl);

    return (avl->root->height);
}

size_t AVLSize(const avl_t *avl)
{
    assert(avl);

    return (_Count(avl->root));
}

int AVLIsEmpty(const avl_t *avl)
{
    return  (!avl->root);
}

void *AVLFind(const avl_t *avl, const void *data)
{
    assert(avl);
    assert(data);

    return (_Find(avl, avl->root, data));
}

int AVLForEach(avl_t *avl, callback_func_t func, void* param, order_t order)
{
    int status = 0;

    assert(avl);
    assert(func);

    switch (order)
    {
        case PREORDER :
            status = _ForEachPreOrder(avl->root, func, param);
            break;

        case INORDER :
            status = _ForEachInOrder(avl->root, func, param);
            break;

        case POSTORDER :
            status = _ForEachPostOrder(avl->root, func, param);
            break;

        default :
            status = NO_SUCH_ORDER;
    }
    return (status);
}

/*------------------definition of static functions---------------------------*/
/* creates a new leaf & initialise it's data */
static avl_node_t *_CreateNewLeaf(void *data)
{
    avl_node_t *new = (avl_node_t *)malloc(sizeof(avl_node_t));
    if (!new)
    {
#ifndef NDEBUG
        perror("_CreateNewLeaf: ");
#endif
        return (NULL);
    }
    new->height = 0;
    new->child[LEFT] = NULL;
    new->child[RIGHT] = NULL;
    new->data = data;

    return (new);
}

/* inserts a new key to it's right position in the 'avl'*/
static avl_node_t *_KeyInsert(avl_t *avl, avl_node_t *locate, void *data)
{
    int side = 0;

    if (!locate)
    {
        locate = _CreateNewLeaf(data);
        return (locate);
    }
    side = (0 < (avl->key(data, locate->data, avl->param)));
    locate->child[side] = _KeyInsert(avl, locate->child[side], data);
    if (locate->child[side])
    {
		/* incase the child's height grew after the insertion and became 
		   as the father's, it means the height of the father's has to be
		   apdate and it might need some balance to keep the avl properties */
        if (locate->height == locate->child[side]->height)
        {
            ++locate->height;
            return (_Balance(locate, side));
        }
        return (locate);
    }
    
    return (NULL);
}

/* gets an 'unbalanced' node and the 'direction' to rotate and changes the
   order of the nodes to balance the tree */
static avl_node_t *_Rotate(avl_node_t *unbalanced, side_t direction)
{
    avl_node_t *child_to_return;

    assert(unbalanced);

    child_to_return = unbalanced->child[!direction];
    unbalanced->child[!direction] = child_to_return->child[direction];
    child_to_return->child[direction] = unbalanced;

    unbalanced->height = _Getheight(unbalanced);
    child_to_return->height = _Getheight(child_to_return);

    return (child_to_return);
}

/* get a node and balances the tree incase the node is unbalanced */
static avl_node_t *_Balance(avl_node_t *unbalanced, side_t side)
{
    if (1 < _BalanceFactor(unbalanced, side))
    {
        if (0 > _BalanceFactor(unbalanced->child[side], side))
        {
            unbalanced->child[side] = _Rotate(unbalanced->child[side], side);
        }
        return (_Rotate(unbalanced, !side));
    }
    return (unbalanced);
}
/* compares between the heights of the two subtrees of a given 'root'
   and returns (+) if the subtree on the given 'side' is deeper
               (-) if the other subtree is deeper */
static long _BalanceFactor(avl_node_t *root, side_t side)
{
    long h_side = (!root->child[side]) ? -1 : (long)root->child[side]->height;
    long h_other = (!root->child[!side]) ? -1 : (long)root->child[!side]->height;

    return (h_side - h_other);
}

/* returns the height of a given 'node' */
static size_t _Getheight(avl_node_t *node)
{
    long h_left = (!node->child[LEFT]) ? -1 : (long)node->child[LEFT]->height;
    long h_right = (!node->child[RIGHT]) ? -1 : (long)node->child[RIGHT]->height;

    return ((h_left > h_right) ? (h_left + 1) : (h_right + 1));
}

/* detroys all the nodes in a given tree/sub-tree begins in 'to_destroy' */
static void _AVLClear(avl_node_t *to_destroy)
{
    if (to_destroy)
    {
        _AVLClear(to_destroy->child[LEFT]);
        _AVLClear(to_destroy->child[RIGHT]);
        _DestroyLeaf(to_destroy);
    }
}

/* erases specific node contains a given 'data' if exist and returns */
static avl_node_t *_RemoveNode(avl_t *avl, avl_node_t *remove, const void *data)
{
    int is_match = 0;
    avl_node_t *heir = NULL;
    int side = 0;

    if (!remove)
    {
        return (NULL);
    }
    is_match = avl->key(data, remove->data, avl->param);
    if (MATCH == is_match)
    {
        if (remove->child[LEFT] && remove->child[RIGHT])
        {
            void *new_data = _GetPrevData(remove->child[LEFT]);
            remove->data = new_data;
            remove->child[LEFT] = _RemoveNode(avl,remove->child[LEFT],new_data);
        }
        else
        {
            /* returns the not NULL child if exist or NULL if not exist */
            heir = remove->child[(!remove->child[LEFT])];
            _DestroyLeaf(remove);

            return (heir);
        }
    }
    side = (0 < is_match);
    remove->child[side] = _RemoveNode(avl, remove->child[side], data);
    remove->height = _Getheight(remove);

    return (_Balance(remove, side));
}

/* gets the previous data */
static void *_GetPrevData(avl_node_t *prev)
{
            if (!prev->child[RIGHT])
            {
                return prev->data;
            }
            return (_GetPrevData(prev->child[RIGHT]));
}
/* destroys a given node and frees it's allocated memory */
static void _DestroyLeaf(avl_node_t *to_destroy)
{
    to_destroy->child[RIGHT] = NULL;
    to_destroy->child[LEFT] = NULL;
    to_destroy->data = NULL;

    free(to_destroy);
    to_destroy = NULL;
}

/* returns the number of elements in a given tree/sub-tree begins in 'element'*/
static size_t _Count(avl_node_t *element)
{
    size_t count = 0;

    if (element)
    {
        count = 1;
        count += (_Count(element->child[LEFT]));
        count += (_Count(element->child[RIGHT]));
    }
    return (count);
}

/* checks whether a given 'data' is whithin a given 'avl'*/
static void *_Find(const avl_t *avl, avl_node_t *seek, const void *data)
{
    int is_match = 0;

    assert(avl);
    assert(data);

    if (!seek)
    {
        return (NULL);
    }
    is_match = avl->key(data, seek->data, avl->param);
    if (MATCH == is_match)
    {
        return (seek->data);
    }
    return (_Find(avl, seek->child[(0 < is_match)], data));
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
   the ForEach functions execute operation in a recursive way on all the
   elements in a a given tree/sub-tree begins in 'node'.
   the user get to choose which order the operation will occcure - */

/* first the node then it's left child and last it's right child */
static int _ForEachPreOrder(avl_node_t *node, callback_func_t func, void* param)
{
    int status = 0;

    if (node)
    {
        status = func(node->data, param);

        if (SUCCESS == status)
        {
            status = (_ForEachPreOrder(node->child[LEFT], func, param));
        }
        if (SUCCESS == status)
        {
            status = (_ForEachPreOrder(node->child[RIGHT], func, param));
        }
    }
    return (status);
}
/* first the node's left child then the node itself and last the node's
   right child */
static int _ForEachInOrder(avl_node_t *node, callback_func_t func, void* param)
{
    int status = 0;

    if (node)
    {
        status = (_ForEachInOrder(node->child[LEFT], func, param));
        if (SUCCESS == status)
        {
            status = func(node->data, param);
        }
        if (SUCCESS == status)
        {
            status = (_ForEachInOrder(node->child[RIGHT], func, param));
        }
    }
    return (status);
}
/* children first then the node itself */
static int _ForEachPostOrder(avl_node_t *node, callback_func_t func,void* param)
{
    int status = 0;

    if (node)
    {
        status = (_ForEachPostOrder(node->child[LEFT], func, param));
        if (SUCCESS == status)
        {
            status = (_ForEachPostOrder(node->child[RIGHT], func, param));
        }
        if (SUCCESS == status)
        {
            status = func(node->data, param);
        }
    }
    return (status);
}
/*----------------------------------------------------------------------------*/
