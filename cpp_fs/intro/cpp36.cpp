#include <iostream>
using namespace std;

class X
{
public:
    X(double in = 3) : m_y(in) { cout << "X Ctor: " << (size_t)this << endl; }
    virtual ~X() { cout << "X Dtor: " <<  (size_t)this << endl;}
    virtual void Print() { cout << "x print " << m_y << endl; }

    double m_y;
private:
    // double m_1;
};

class Y : public X
{
public:
    Y() : X(5), m_b(4) { cout << "Y Ctor: " <<  (size_t)this << endl;}
    ~Y() { cout << "Y Dtor: " <<  (size_t)this << endl;}
    virtual void Print() { cout << "Y print " << m_b << endl; }
private:
    int m_b;
};

void Foo(X x)
{
    x.Print();
    cout << "Foo" << x.m_y << endl;
}

int main()
{
    // X *xp = new Y[5];
    // // delete[] static_cast<Y*> (xp);
    // delete[] (xp);    
    // // Y *y1 =
    X x1;
    Y y1;
    // X *px = &y1;
    // X x1;
    // Y *py1 = static_cast<Y *>(&x1);

    // X xx = *px;

    Foo(x1);
    Foo(y1);
    
    return 0;
}
