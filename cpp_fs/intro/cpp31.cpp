#include <iostream>
#include <exception>
#include <string>
#include <cstdlib>
#include <memory>

using namespace std;

void myunexpected () 
{
  std::cerr << "unexpected called\n";
//   exit (3);    // out without Dtors..
//   throw '4';     // throws char calling terminate 
  throw 5;     // throws int  
}

void myterminate () throw (int)
{
  std::cerr << "terminate handler called\n";
  abort();  // the default.. forces abnormal termination
}


class X
{
public:
    X() {std::cout << "X::Ctor" << this <<std::endl;}
    ~X(){std::cout << "X::Dtor" << this <<std::endl;}
};

void Fifi(int num) 
{
    X x;
    if (!(num%4))
    {
        char throwchar = 'a';
        throw throwchar;
    }
    if (!(num%3))
    {
        float throwfloat = 9.5;
        throw throwfloat;
    }
    if (!(num%2))
    {
        throw num;
    }
    // double throwfloat

    // throw 

    cerr << "Fifi() after throw" << endl;
}
void Foo(int num)

{
    X x;
    // int *ip = new int;
    std::auto_ptr<int>ptri(new int(4));
    Fifi(num);
    
    cerr << "Foo() after Fifi()" << endl;
    // delete ip;
}

void Bar(int num)
{
    X x;
    Foo(num);
    cerr << "Bar() after Foo()" << endl;
}

int main() 
{
    set_unexpected (myunexpected);
    set_terminate (myterminate);

    // try
    // {
        Bar(3);
    // }
    // catch(float)
    // {
    //     cerr << "float" << endl;
    // }
    // catch(char)
    // {
    //     cerr << "char" << endl;
    // }
    // catch(int)
    // {
    //     // terminate();
    //     cerr << "int" << endl;
    // }
    // catch(exception& r)
    // {
    //     cerr << "unknown exception: " << r.what();
    //     exit(4);
    // }

    return 0;
}