#include<iostream>
using namespace std;

struct X 
{ 
   explicit X(int); 
    ~X(); 
    void Foo(); 
    void Bar() const; 

    int m_a; 
    int *m_p; 
}; 

X::X(int a_): m_a( a_ ), m_p(new int(a_)) {} 

X::~X() {delete m_p; m_p=0; } 

void X::Foo() { ++m_a; --(*m_p); } 

void X::Bar() const 
{ 
    cout << m_a << endl; 
    cout << *m_p << endl; 
    cout << m_p << endl;    
    //m_a = 0; //---1---
    //m_p = 0; //---2---
    //*m_p = 0; //---3---
    //Foo(); //---5---
} 

void Fifi(const X& x_) 
{ 
    //x_.Foo(); //---4---
    x_.Bar(); 
} 

int main() 
{ 
    X x1(1); 

    x1.Foo(); 
    Fifi(x1); 

    return (0); 
}