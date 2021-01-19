#include <iostream>
#include <typeinfo>     //bad_cast
#include <memory>       //shared_ptr
using namespace std;

struct X
{
    X() {cerr << "X ctor" << endl; throw bad_cast();}
    X(int) { cerr << "X Ctor int" << endl;}
    ~X() { cerr << "X Dtor" << endl;}
};


struct Y
{
    Y() { cerr << "Y Ctor" << endl;}
    ~Y() { cerr << "Y Dtor" << endl;}
};

class L
{
public:
    L() : m_x(2) { cerr << "L Ctor" << endl;}
    ~L() { cerr << "L Dtor" << endl;}
private:
    Y m_y;
    X m_x;
};

class M
{
public:
    M() { cerr << "M Ctor" << endl;}
    ~M() { cerr << "M Dtor" << endl;}
private:
    Y m_y;
    X m_x;
};

class N
{
public:
    N() { cerr << "N Ctor" << endl;}
    ~N() { cerr << "N Dtor" << endl;}
private:
    Y m_y;
    X m_x;
};

class J
{
public:
    J() : m_y(new Y), m_x(new X) { cerr << "J Ctor" << endl;}
    ~J() { cerr << "J Dtor" << endl; }
private:
    // shared_ptr<Y> m_y; //only from c++11
    // shared_ptr<X> m_x;
    auto_ptr<Y> m_y;
    auto_ptr<X> m_x;    
};

class K
{
public:
    K() 
    { 
        cerr << "K Ctor" << endl;
        m_y = (new Y); m_x = (new X);
    }
    ~K() 
    { 
        cerr << "K Dtor" << endl; 
        delete m_x;
        delete m_y;
    }
private:
    // shared_ptr<Y> m_y;
    // shared_ptr<X> m_x;
    Y *m_y;
    X *m_x;
    // std::auto_ptr<Y> m_y;
    // auto_ptr<X> m_x;    
};

int main()
{
    try
    {
        M var1;
    }
    catch(const std::exception& e)
    {
        std::cerr << "exception cout.what:"<< e.what() << '\n';
    }

    return 0;    
}