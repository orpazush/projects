#include <iostream>
using namespace std;

class X
{
public:
    X(double d_) :m_a(d_) {}
    virtual ~X() {}
    void operator=(const X& otheer) {cout << "x = " << m_a << endl;}
    virtual void Print() {cout << "x print " << m_a << endl;}

    double m_a;
private:
};

class Y: public X
{
public:
    Y(double d_, int i_): X(d_), m_b(i_) {}
    int m_b;
    void Print() {cout << "y print " << m_b << endl;}
    void operator=(const Y& otheer) { cout << "y = " << m_a << endl; }

private:
};

int main()
{
    Y y1(0.0, 0), y2(14.2, 5);
    Y y3(0.0, 0), y4(14.2, 5);

    X &x1 = y1;
    X &x2 = y2;

    X *px1 = &y1;
    X *px2 = &y2;

    *px1 = *px2;
    x1 = y2;
    y3 = y4;

    x1.Print();
    y1.Print();

    cout << y1.m_a << endl;
    cout << y3.m_a << endl;
    cout << y1.m_b << endl;
    cout << y3.m_b << endl;

    return 0;

}
