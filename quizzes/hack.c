/*
x=1

Enter func1
Enter func2
Exit func2
Exit main
*/

#include <stdio.h>

void func2(void *arg)
{
    long f2;
    printf("Enter func2\n");
    /* Area2 */
/*    f2 = (long)(arg - 1);
    *(long *)f2 =*/
    printf("Exit func2\n");
}

void func1()
{
    long f1;
    printf("Enter func1\n");
    func2(&f1);
    printf("Exit func1\n");
}

int main()
{
    const long x=1;
    long y=5;
    /* Area1 */

/*  answer.1
    long *xp = (long *)&x;
    *xp = 666;
*/
/* answer.2 */
    long *py = &y;
    ++py;
    *py = 666;

    printf("x=%lu\n",x);

    func1();
    printf("Exit main\n");

    return 0;

}
