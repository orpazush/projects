#include <iostream>
#include <malloc.h>
class C
{
public:

    virtual void Print1() const;
    virtual void Print2() const;
    virtual void Print3() const;
};

class B
{
public:
    char *pc;
    char c;
    char m_m;
    B(int a_):c('c'), m_m('b'), m_a(a_) {std::cout << "B::Ctor"<<std::endl;}
    virtual ~B(){std::cout << "B::Dtor"<<std::endl;}

    virtual void Print1() const;
    virtual void Print2() const;
    virtual void Print3() const;

private:
    int m_a;
};

void B::Print1() const
{
  std::cout << "B::Print1 B::mm -"<< m_m <<std::endl;  
}

void B::Print2() const
{
  std::cout << "B::Print2" <<std::endl;  
}

void B::Print3() const
{
  std::cout << "B::Print3" <<std::endl;  
}

class X:public B
{
public:
    X(): B (8), m_m('x') {std::cout << "X::Ctor"<<std::endl;}
    ~X(){std::cout << "X::Dtor"<<std::endl;}

    virtual void Print1()const
    {
        std::cout << "X::Print1 X::mm -"<< m_m <<std::endl;
        B::Print1();
        std::cout << "X::Print1 end" <<std::endl;
    }
    void Print2()const { std::cout << "X::Print2" <<std::endl;}
    char m_m;

private:
    int m_b;
    char *x;
    long l;

};

int main()
{
    B *b1 = new B(5);
    B *b2 = new X;
    // X xxx;
    // C cc;

    // std::cout<<std::endl << sizeof(*b1) << std::endl;
    // std::cout<<std::endl << sizeof(*b2) << std::endl;
    // std::cout<<std::endl << sizeof(xxx) << std::endl;
    // std::cout<<std::endl << sizeof(cc) << std::endl;

    std::cout<<std::endl <<"main b1:" << std::endl;
    b1->Print1();
    b1->Print2();
    b1->Print3();

    std::cout<<std::endl <<"main b2:" << std::endl;
    b2->Print1();
    b2->Print2();
    b2->Print3();
   
    X * xx =static_cast<X*>(b2);

    std::cout << std::endl << "main xx:" << std::endl;
    xx->Print2();
    b2->Print2();

// test for mutual public members
    // X mm;
    // std::cout << std::endl << mm.c << std::endl;
    // std::cout << std::endl << mm.m_m << std::endl;
    // std::cout << std::endl << mm.B::m_m << std::endl;

    delete (b1);
    delete (b2);
    
    return 0;    

}
