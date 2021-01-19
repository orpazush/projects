/* c++ intro */

#include <stdio.h>

enum E {AA = 67, BB, CC = 22, DD};
enum E2 {TT, KK};
// enum E e = 2;
enum E e = DD;
// enum E2 e2 = AA;

// ++e;
unsigned long i = KK;
unsigned long j = BB;
char x = AA;

int main()
{
    bool b1;
    bool b2 = 7;
    int i = 7;
    // i = -8;
    // b2 = i;
    i = b1;

    printf("%d\n", i);

    return 0;
}
