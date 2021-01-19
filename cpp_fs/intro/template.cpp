#include <iostream>
#include <typeinfo>

#include "template.hpp"


template <typename T>

T Max(T t1, T t2)
{
    return (t1%t2) ? t1 : t2;
}

// void foo(T t)
// {
//     std::cout << t << " generic foo for" << typeid(t).name() << std::endl;
// }
//
// template <>
// void foo<int>(int t)
// {
//     std::cout << t << " specialized foo (for int param)\n";
// }
//
// void foo(int t)
// {
//     std::cout << t << " specialized foo (for int param)\n";
// }
// using namespace temple;
enum A {OO, P, S};

int main()
{
    // foo(4.2);
    // foo(5);
    // foo<int>(5);
    // int arr[12];
    //
    std::cout << Max<int>(3, 5) << std::endl;
    std::cout << Max<int>(8, 22) << std::endl;
    std::cout << Max<double>(7.22, 19.999) << std::endl;
    // std::cout << Max<int *>(arr, arr + 8) << std::endl;
    // std::cout << Max('a', 'b') << std::endl;
    // std::cout << Max("ima", "aba") << std::endl;
    // std::cout << Max(89898989, -777) << std::endl;
    // std::cout << Max(3.999, -2.77) << std::endl;
    // std::cout << Max(OO, S) << std::endl;

    return 0;
}
