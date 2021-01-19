#include <iostream>

using namespace std;

struct X
{
    X(int a_, int b_);

    void Inc();
    void Dec();

    int m_a;
    int m_b;
};

X::X(int a_, int b_) : m_a(a_), m_b(b_)
{
    cout << "In Ctor int, int " << endl;
}

void X::Inc()
{
    cout << "this " << this << endl;
    ++m_a;
    ++m_b;
}

void X::Dec()
{
    cout << "this " << this << endl;
    --m_a;
    --m_b;
}

void Inc()
{
    cout << "In generic Inc " << endl;
}

int main(void)
{
    X x1(7, -55);
    X x2(x1);

    Inc();
    x1.Inc();
    x1.Inc();
    x2.Dec();    

    return (0);
}
