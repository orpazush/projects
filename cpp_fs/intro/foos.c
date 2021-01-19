#include <iostream>

void Foo(void)
{
    printf("void func\n");
}

void Foo(int i)
{
    std::cout << i << '\n';
}

void Foo(char c)
{
    std::cout << c << '\n';
}

void Foo(char *cp)
{
    std::cout << *cp << '\n';
}

// int main()
// {
//     unsigned int i = 356;
//     Foo(i);
//     Foo(88);
//     Foo('o');
//
//     return 0;
// }
