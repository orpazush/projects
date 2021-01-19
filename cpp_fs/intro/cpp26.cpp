#include <iostream>
using namespace std;

class X;

int operator+(const X& x1_, const X& x2_);
// ostream& operator<<(ostream& os_, const X& x_);

class X
{
public:
    void operator=(int new_m_a);//assigmnment
    bool operator==(const X& o_) const { return m_a == o_.m_a; }
    friend int operator+(const X& x1_, const X& x2_);
   //java style inline  not allowed in our coding standard
private:
    friend ostream& operator<<(ostream& os_, const X& x_);
    int m_a;
};

int main()
{
    X x1;
    X x2;
    x1 = 5;
    x2 = 10;

    cout << " x1+x2:" << x1 + x2 <<
           " x1==x2:" << (x1 == x2) <<
           " x1:" << x1 <<
           " x2:" << x2 << endl;
    
    return 0;
}

void X::operator=(int new_m_a)
{
    m_a = new_m_a;
}

ostream& operator<<(ostream& os_, const X& x_) 
{
    return os_ << x_.m_a;
}

int operator+(const X& x1_, const X& x2_)
{ 
    return x1_.m_a + x2_.m_a;
}
