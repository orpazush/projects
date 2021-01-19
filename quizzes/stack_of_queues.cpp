//
// Created by orpaz on 15/12/2020.
//

#include <iostream>
#include <queue>

using namespace std;

template <typename T>
class Stack
{
public:
//    explicit Stack(); //default
//    ~Stack(); //default

    void Push(T newElement);
    T Pop();

private:
    queue<T> m_queue1;
    queue<T> m_queue2;
};

template<typename T>
void Stack<T>::Push(T newElement)
{
    if (!m_queue2.empty())
    {
        m_queue2.push(newElement);
    }
    else
    {
        m_queue1.push(newElement);
    }
}

template<typename T>
T Stack<T>::Pop()
{
    T toRet = {0};
    if (m_queue1.empty())
    {
        while (1 != m_queue2.size())
        {
            m_queue1.push(m_queue2.front());
            m_queue2.pop();
        }
        toRet = m_queue2.front();
        m_queue2.pop();
    }

    else
    {
        while (1 != m_queue1.size())
        {
            m_queue2.push(m_queue1.front());
            m_queue1.pop();
        }
        toRet = m_queue1.front();
        m_queue1.pop();
    }

    return (toRet);
}

int main()
{
    Stack<int> test;
    size_t tests = 0;

    test.Push(1);
    test.Push(2);
    test.Push(3);

    tests += (3 == test.Pop());
    tests += (2 == test.Pop());

    test.Push(4);
    test.Push(5);
    test.Push(6);

    tests += (6 == test.Pop());
    tests += (5 == test.Pop());

    if (tests == 4)
    {
        cout << "Success!\n";
    } else
    {
        cout << "Fail\n";
    }

    return 0;
}
