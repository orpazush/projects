//
// Created by orpaz on 28/12/2020.
//

#include <iostream>

using namespace std;

class Base
{
public:
    Base(int i): m_i(i), m_iptr(&m_i) {}
    virtual void foo() { cout << "Base Foo "<< *(m_iptr) << endl; }
    virtual void bar() { cout << m_i << endl; }

protected:
    virtual ~Base() =0;

private:
    int m_i;
    int *m_iptr;
};


inline Base::~Base() {}

class Derived : public Base
{
public:
    Derived(int i, char c) : m_c(c), Base(i), m_c2(c) {}
    void bar() {foo(); Base::foo(); }

private:
    void foo() { cout << "Derived Foo " << m_c << endl; }
    char m_c, m_c2;
};

int main()
{
    Derived d1(5, 'x');
    Derived d2(3, 'w');

    Base *b1 = &d1;
    b1->foo();
    b1->bar();

    Base *b2 = &d2;
    *b2 = *b1;
    b2->foo();
    d2.bar();

    return 0;
}