/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review :     						         *
 * 					Last update : 3.9.20									 *
 ****************************************************************************/

#include <iostream>

#include "shared_ptr.hpp"

using namespace std;
using namespace ilrd;

class B
{
public:
    B(size_t size = 8) : m_size(size) {};
    std::size_t m_size;
};

class D : public B
{
public:
    D(size_t size = 3) : B(size) {};
};

class C : public D
{
public:
    C(size_t size = 100) : D(size) {};
};


int main()
{
    SharedPtr<B> shb1(new B);
    SharedPtr<B> shb2(new D);
    SharedPtr<B> shb3(new C);
    SharedPtr<D> shd1(new C);
    SharedPtr<D> shd2(shd1);
    SharedPtr<int> shbint(new int (9));

    cout << shb1->m_size << endl;
    cout << shb2->m_size << endl;
    cout << shb3->m_size << endl;
    cout << *shbint << endl;

    shb1 = shb2;
    shb2 = shb3;
    shb3 = shb3;
    shd1 = shb1;

    return 0;
}