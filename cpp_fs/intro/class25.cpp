#include <cstdio>

class X
{
public:    
    explicit X(int a_);
    void Foo();
    int Get() const; 
    void Set(int to_set);

    int m_a;
};

X::X(int a_): m_a(a_)
{
}

void X::Foo()
{
    printf("%d\n", m_a);
}

int X::Get() const
{
    return (m_a);
}

void X::Set(int to_set)
{
    m_a = to_set;
}

void Foo(const X& x_)
{
    printf("%d\n", x_.Get() );
}

int main()
{
    X x1(9);
    X x2(x1);
    x1 = x2;

    x1.Foo();
    printf("%d\n", x1.Get());
    Foo(x1);

    return 0;
}