/****************************************************************************
* 					written by : orpaz houta								*
* 					review : Malu Gerkol     								*
*					Last update : 25.5.20 									*
****************************************************************************/
#ifndef __RECURSION_H__
#define __RECURSION_H__

#include <stddef.h> /* size_t */

#include "stack.h"  /* RecSortStack */

typedef struct node
{
    struct node *next;
    int *data;
}Node;

/* returns the fibonacci value in a given 'element_index' using iteration */
int IterateFibonacci(int element_index);

/* returns the fibonacci value in a given 'element_index' using recursion */
int RecFibonacci(int i);

/* gets some node and travers all the nodes after it to point the one befor them */
Node *FlipNode(Node *node);

/* sorts a given stack 'to_sort' */
void RecSortStack(stack_t *to_sort);

/* strings */
size_t RecStrLen(const char *string);
int RecStrCmp(const char *string1, const char *string2);
char *RecStrCpy(char *destination, const char *source);
char *RecStrCat(char *dest, const char *source);
char *RecStrStr(const char *haystack, const char *needle);

#endif /* ifdef __RECURSION_H__ */
