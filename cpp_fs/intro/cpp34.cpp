#include <iostream>     // cerr
#include <exception>    // bad_alloc
#include <typeinfo>     // bad_cast

using namespace std;

int Foo(int) throw(bad_alloc)
{
    cerr << "Foo() befor throw" << endl;
    
    throw bad_alloc();
    cerr << "Foo() after throw" << endl;
}

void Bar() throw(bad_cast)
{
    cerr << "Bar() befor throw" << endl;
    
    throw bad_cast();
    cerr << "Bar() after throw" << endl;
}

class X
{
private:
    int m_a;
public:
    X() : m_a(4) {cout << "Ctor X" << endl;};
    ~X();
};

X::~X()
{
    cerr << "Dtor X" << endl;
    try
    {
        cerr << Foo(m_a) << endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << "inside Dtor" << e.what() << '\n';
    }
}

void Fishi()
{
    X x1;
    Bar();
}

int main()
{
    try
    {
        Fishi();
    }
    catch(const exception& b_c)
    {
        std::cerr << b_c.what() << '\n';
    }

    return 0;
}