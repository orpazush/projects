#include <stdio.h>

int flip(int n)
{
  int res=0, tmp;
  while (n!=0)
  {
    tmp = n%10;
    res = res*10 + tmp;
    n = n/10;
  }
  return res;
}
int main()
{
  int num;
  scanf("%d", &num);
  printf("%d\n", flip(num));
  return 0;
}
