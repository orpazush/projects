#include <iostream>
#include <iostream>
#include <exception>
#include <string>
#include <cstdlib>
#include <memory>

using namespace std;

struct BadDog: public runtime_error
{
    BadDog(const string& s_ = "This is a bad dog"): runtime_error(s_) 
    {
        cout << "Ctor Bad Dog" << endl;
    }
};

void Fifi()
{
    if (1 == 1)
    {
        throw BadDog("bad pup");
    }
    cerr << "Fifi() after throw" << endl;
}

void Foo()
{
    std::auto_ptr <int> ip(new int);
    Bar(ip);
    Fishi();
    Fifi(ip);
    Dodo();

    delete ip;
}

void Bar()
{
    Foo();
    cerr << "Bar() after Foo()" << endl;
}
