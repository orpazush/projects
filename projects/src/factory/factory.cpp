/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review : Gil Steinberg     						         *
 * 					Last update : 11.10.20									 *
 ****************************************************************************/
#include <iostream>
#include "factory.hpp"

using namespace ilrd;
using namespace project;
using namespace std;

class Base
{
public:
    Base();
};

Base::Base()
{
    cout << "Base ctor" << endl;
}

class A : public Base
{
public:
    A();
};

A::A()
{
    cout << "A ctor" << endl;
}

Base *CreateA()
{
    A *toRet = new (A);
    return toRet;
}

class B : public Base
{
public:
    B();
};

B::B()
{
    cout << "B ctor" << endl;
}

Base *CreateB()
{
    B *toRet = new (B);
    return toRet;
}
/*---------------------------------------------------------------------------*/
class Case
{
public:
    Case();
};

Case::Case()
{
    cout << "Case ctor" << endl;
}

class C : public Case
{
public:
    C(int m);
private:
    int m_int;
};

C::C(int m) : m_int(m)
{
    cout << "C ctor of " << m_int << endl;
}

Case *CreateC(int m)
{
    C *toRet = new C(m);
    return toRet;
}

class D : public Case
{
public:
    D(int m);
private:
    int m_int;
};

D::D(int m) : m_int(m)
{
    cout << "D ctor of " << m_int << endl;
}

Case *CreateD(int m)
{
    D *toRet = new D(m);
    return toRet;
}

int main()
{
    Factory<Base, int> factory;
    factory.Add(0, CreateA);
    factory.Add(1, CreateB);
//    factory.Add(1, CreateA); //throw
    factory.Create(0);
    factory.Create(1);
//    factory.Create(2); //throw
    Factory<Case, int, int> facwithparam;
    facwithparam.Add(2, CreateC);
    facwithparam.Add(4, CreateD);
    facwithparam.Create(2, 9);
    facwithparam.Create(4, 20);

    return 0;
}