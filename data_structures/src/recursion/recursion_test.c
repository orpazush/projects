/****************************************************************************
* 					written by : orpaz houta								*
* 					review : Malu Gerkol     								*
*					Last update : 25.5.20 									*
****************************************************************************/
#include <string.h> /* strlen, strcpy, strcmp.. */

#include "recursion.h"
#include "ca_test_util.h" 	/* ©️ chanan & aviv */

#define SIZE (20)

void TestFibo();
void TestStrings();
void TestFlip();
void TestSortSrack();

int main()
{
    TestFibo();
/*    TestStrings();
    TestFlip();
    TestSortSrack();*/

    TEST_SUMMARY();

    return 0;
}

void TestFibo()
{
    INT_TEST(1, IterateFibonacci(0));
    INT_TEST(1, IterateFibonacci(1));
    INT_TEST(2, IterateFibonacci(2));
    INT_TEST(34, IterateFibonacci(8));
    INT_TEST(13, IterateFibonacci(6));

    INT_TEST(1, RecFibonacci(0));
    INT_TEST(1, RecFibonacci(1));
    INT_TEST(2, RecFibonacci(2));
    INT_TEST(34, RecFibonacci(8));
    INT_TEST(13, RecFibonacci(6));
}

void TestStrings()
{
    char *sourcetest = "orpaz";
    char desttest2[100];
    char desttest[100];
    char needle = 'n';

    INT_TEST(1, (RecStrLen(sourcetest) == strlen(sourcetest)));
    INT_TEST(1, (RecStrLen("do yoy") == strlen("do yoy")));
    INT_TEST(1, (RecStrLen("want") == strlen("want")));
    INT_TEST(1, (RecStrLen("to build a snowman") == strlen("to build a snowman")));

    INT_TEST(1, (RecStrCmp("orpaz", "orpaz") == strcmp("orpaz", "orpaz")));
    INT_TEST(1, (RecStrCmp("orpaz", "nalu") == strcmp("orpaz", "nalu")));
    INT_TEST(1, (RecStrCmp("maluka", "malu") == 'k'));
    INT_TEST(1, (RecStrCmp("yes", "no") == ('y' - 'n')));
    INT_TEST(1, (RecStrCmp("malu", "maluka") == -'k'));

    INT_TEST(0, (RecStrCmp(RecStrCpy(desttest, sourcetest), sourcetest)));
    INT_TEST(0, (RecStrCmp(RecStrCpy(desttest, "happy"), "happy")));
    INT_TEST(0, (RecStrCmp(RecStrCpy(desttest, "shavuot"), "shavuot")));

    RecStrCat(desttest, " is good!");
    INT_TEST(0, (RecStrCmp(desttest, "shavuot is good!")));
    RecStrCpy(desttest2, "there is ");
    RecStrCat(desttest2, "nothing else");
    INT_TEST(0, (RecStrCmp(desttest2, "there is nothing else")));

    INT_TEST(1, (*RecStrStr(desttest2, &needle) == 'n'));
    needle = 'e';
    INT_TEST(1, (*RecStrStr(desttest2, &needle) == needle));
    needle = 'd';
    RecStrStr(desttest2, &needle);
    INT_TEST(1, (!RecStrStr(desttest2, &needle)));
    needle = 'l';
    INT_TEST(1, (*RecStrStr(desttest2, &needle) == needle));
}

void TestFlip()
{
    int i = 0;
    Node array[SIZE];
    int data_arr[SIZE];
    Node *flip = NULL;

    for (i = 0; i < SIZE; ++i)
    {
        data_arr[i] = i;
    }

    for (i = 0; i < (SIZE - 1); ++i)
    {
        array[i].next = &array[i + 1];
        array[i].data = &data_arr[i];
    }
    array[SIZE - 1].next = NULL;
    array[SIZE - 1].data = &data_arr[SIZE - 1];

    flip = FlipNode(&array[0]);
    INT_TEST(1, (*flip->data == (SIZE - 1)));

    for (i = 0; i < SIZE; ++i)
    {
        INT_TEST(1, (*flip->data == (SIZE - (1 + i))));
        flip = flip->next;
    }
}

void TestSortSrack()
{
    int i = 0;
    stack_t *to_sort = NULL;
    int a = 1, b = 9, c = 5, d = -12, e = 50;
    int peek1 = 0;
    int peek2 = 0;

    to_sort = StackCreate(100);

    StackPush(to_sort, &a);
    StackPush(to_sort, &b);
    StackPush(to_sort, &c);
    StackPush(to_sort, &d);
    StackPush(to_sort, &e);

    RecSortStack(to_sort);
    StackPop(to_sort);

    peek1 = *(int *)StackPeek(to_sort);
    for (i = 0; !StackIsEmpty(to_sort); ++i)
    {
        peek2 = *(int *)StackPeek(to_sort);
        INT_TEST(1, (peek1 >= peek2));
        StackPop(to_sort);
        peek1 = peek2;
    }
    StackDestroy(to_sort);
}
