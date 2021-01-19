//
// Created by orpaz on 22/12/2020.
//
#include <iostream>

int foo()
{
    int i = 5;
    i += i * 2;
    int *p = &i;
    *p += 20;

    return i;
}

class Base
{
public:
    Base();
    /*explicit */Base(const Base& other);
};

Base::Base()
{

}

Base::Base(const Base &other)
{
    std::cout << "cc\n";
}

void Foo(Base base)
{
    std::cout << "foo\n";
}

int main()
{
    std::cout << foo() << std::endl;
//    int &d = 200;
    int v = 100;
    int &r = v;
//    int &c = 200;
    Base base;
    Foo(base);
    Foo(Base(base));

    return 0;
}
