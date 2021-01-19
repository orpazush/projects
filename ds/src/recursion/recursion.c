/****************************************************************************
* 					written by : orpaz houta								*
* 					review : Malu Gerkol     								*
*					Last update : 25.5.20 									*
****************************************************************************/
#include <assert.h> /* assert */

#include "recursion.h"

static void SortInsert(stack_t *to_sort, int *value);

int IterateFibonacci(int element_index)
{
    int i = 0;
    int one = 0;
    int two = 1;
    int three = 1;

    assert(0 <= element_index);

    for (i = 0; i < element_index; ++i)
    {
        three = one + two;
        one = two;
        two = three;
    }
    return three;
}

int RecFibonacci(int i)
{
    assert(0 <= i);

    return (2 > i) ? 1 : (RecFibonacci(i - 1) + RecFibonacci(i - 2));
}

Node *FlipNode(Node *node)
{
    Node *next = NULL;
    Node *new_head = NULL;

    assert(node);

    if (!node->next)
    {
        return node;
    }

    next = node->next;
    node->next = NULL;
    new_head = FlipNode(next);
    next->next = node;

    return new_head;
}

void RecSortStack(stack_t *to_sort)
{
    int *curr_element = NULL;

    assert(to_sort);

    if (!StackIsEmpty(to_sort))
    {
        curr_element = StackPeek(to_sort);
        StackPop(to_sort);
        RecSortStack(to_sort);
        SortInsert(to_sort, curr_element);
    }
}

/* strings */
size_t RecStrLen(const char *string)
{
    assert(string);

    return ((!*string) ? 0 : (1 + RecStrLen(++string)));
}

int RecStrCmp(const char *string1, const char *string2)
{
    assert(string1);
    assert(string2);

    return (('\0' != *string1 && *string1 == *string2)
            ? RecStrCmp(++string1, ++string2)
            : (*string1 - *string2));
}

char *RecStrCpy(char *dest, const char *source)
{
    assert(dest);
    assert(source);

    *dest = *source;

    return ((!*source) ? dest : (RecStrCpy(++dest, ++source) - 1));
}

char *RecStrCat(char *dest, const char *source)
{
    assert(dest);
    assert(source);

    RecStrCpy((dest + RecStrLen(dest)), source);

    return dest;
}

char *RecStrStr(const char *haystack, const char *needle)
{
    assert(haystack);
    assert(needle);

    if (!*haystack)
    {
        return NULL;
    }
    
    return (*haystack == *needle)
            ? (char *)haystack
            : RecStrStr(++haystack, needle);
}

static void SortInsert(stack_t *to_sort, int *value)
{
    int *peek = NULL;

    assert(to_sort);

    peek = (int *)StackPeek(to_sort);

    if (StackIsEmpty(to_sort) || *value > *peek)
    {
        StackPush(to_sort, value);
    }
    else
    {
        StackPop(to_sort);
        SortInsert(to_sort, value);
        StackPush(to_sort, peek);
    }
}
