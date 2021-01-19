
#include <iostream>
using namespace std;

void Foo(const double &param)
{
    cout << param << endl;
    cout << &param << endl;
}

void Bar(double &param)
{
    cout << param << endl;
    cout << &param << endl;
}
void Int(int &)
{
    ;
}

int main()
{
    int x = 10;
    char ch = 'a';
    unsigned int unint = 98989;
    Foo(x);
    Foo(ch);
    Bar(reinterpret_cast<double &>(x));
    Int(reinterpret_cast<int &>(unint));

    return 0;
}
