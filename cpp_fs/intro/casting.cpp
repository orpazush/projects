/* c++ intro */
#include <stdio.h>

typedef struct List List_t;
typedef struct Person Person_t;

struct List
{
    int list;
};

struct Person
{
    char age;
};

void *ll_find(List_t *ll, int key)
{
    return (NULL);
}

void foo(List_t *ll, int key, int age)
{
    void *vv = ll_find(ll, key);
    long *cc = {0};
    int *p = static_cast<int*>(cc);
    // p->age = age;
}

int main()
{
    return (0);
}
