#include <iostream>
using namespace std;

struct X
{
    // explicit X();//initial
    explicit X(int a_, int b_ = 8);//ccreate Ctor

    ~X();//destroy

    X(const X& other_);//copy
    // X& operator=(const X& other_);//assigmnment

    long m_a;
    const int m_b;
};

struct Y
{
    explicit Y();//initial
    Y& operator=(const Y& other_);//assigmnment
    X m_x;
    int m_i;
};


Y::Y(): m_x(9, 5), m_i(10)
{
//    m_a = 3;
    // m_b = 4;
    cout << "this:" << this << " Y default Ctor.m_a: " << endl;
}

Y& Y::operator=(const Y& other_)
{
    m_x.m_a = other_.m_x.m_a;
    //m_b = other_.m_b;
    cout << "this:" << this << " Y assigmnment operator. m_a: " << m_x.m_a
         << " does not change m_b: " << m_b << endl;

    return *this;
}

//
// X::X(): m_a(5), m_b(10)
// {
//     m_a = 3;
//     // m_b = 4;
//     cout << "this:" << this << " X default Ctor.m_a: " << m_a << " m_b: " << m_b << endl;
// }

X::X(int a_, int b_): m_a(a_), m_b(b_)
{
    cout << "this:" << this << "X int int Ctor. m_a: " << m_a << " m_b: " << m_b << endl;
}

X::X(const X& other_): m_a(other_.m_a), m_b(other_.m_b)
{
    cout << "this:" << this << "X copy Ctor. m_a: " << m_a << " m_b: " << m_b << endl;
}
//
// X& X::operator=(const X& other_)
// {
//     m_a = other_.m_a;
//     //m_b = other_.m_b;
//     cout << "this:" << this << " X assigmnment operator. m_a: " << m_a << " does not change m_b: " << m_b << endl;
//
//     return *this;
// }

X::~X()
{
    cout << "this:" << this << " X Dtor. m_a: " << m_a << " m_b: " << m_b << endl;
}

int main(void)
{
    // X x1;
    // x1.m_a = 10;
    // X x2(7);
    // X *px = new X[3];
    // X x3(9, 10);
    // X x4(x1);
    // // X x4(x1);
    // delete[] px;
    // cout << sizeof(x3) << endl;
    //
    // x1 = x3;
    //
    // px = 0;

    Y y1;
    y1.m_x.m_a = 250;
    // y1.m_x.m_b = 750;
    Y y2(y1);
    Y y3;

    y3 = y1;

    return (0);
}
