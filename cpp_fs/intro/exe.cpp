#include <iostream>
using namespace std;

void Foo (void)
{
    bool b;
    cout << b << endl;
    long l = b;
    cout << l << endl;
    int i = b;
    cout << i << endl;

    b = 888;
}

int main()
{
    Foo();
    Foo();

    return (0);
}
