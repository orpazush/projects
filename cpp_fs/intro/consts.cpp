#include <stdio.h>

const char g_ch = 'a';
const int g_int = 38;
double g_doub = 8998.999;
char g_char = 'a';

int main()
{
    const int i = 3;

   int *ip = (int *)&i;
   *ip = 5;
   int arr[i];

   printf("%d %d\n", i, *ip);
   printf("%p\n", (void *)&i);
   printf("%p\n", ip);
   return 0;
}
