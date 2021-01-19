/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review :      						         *
 * 					Last update : 21.10.20									 *
 ****************************************************************************/

#include <string>
#include <iostream>
#include "dispatcher.hpp"

using namespace ilrd;
using namespace project;
using namespace std;

class ListenerA : public Dispatcher<int>::Listener
{
public:
    explicit ListenerA(Dispatcher<int> &dispatcher);
    void AcceptMessage(const int &msg);

private:
    int m_int;
};

void ListenerA::AcceptMessage(const int &msg)
{
    ++m_int;
    cout << "ListenerA" << msg << endl;
}

ListenerA::ListenerA(Dispatcher<int> &dispatcher) : Listener(dispatcher)
{
//    empty
}

class ListenerB : public Dispatcher<int>::Listener
{
public:
    explicit ListenerB(Dispatcher<int> &dispatcher);
    void AcceptMessage(const int &msg);

private:
    int m_int;
};

void ListenerB::AcceptMessage(const int &msg)
{
    ++m_int;
    cout << "ListenerB" << msg << endl;
}

ListenerB::ListenerB(Dispatcher<int> &dispatcher) : Listener(dispatcher)
{}


int main()
{
    Dispatcher<int> disp;

    ListenerA la(disp);
    ListenerB lb(disp);
    Dispatcher<int>::Listener *pla = new ListenerA(disp);
    Dispatcher<int>::Listener *plb = new ListenerB(disp);

    for (int i = 0; i < 10; ++i)
    {
        if (!(i%2))
        {
            disp.NotifyAll(i);
        }
    }

    delete pla;
    la.~ListenerA();

    for (int i = 0; i < 10; ++i)
    {
        if (!(i%2))
        {
            disp.NotifyAll(i);
        }
    }

    return 0;
}
