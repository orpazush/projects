//
// Created by orpaz on 09/12/2020.
//

#include <iostream>
#include <stack>
#include <cstdlib>

using namespace std;

template <typename T>
static void Reverse(stack<T> *toReverse, T toPush)
{
    if (toReverse->empty())
    {
        toReverse->push(toPush);
    }

    else
    {
        T toSave = toReverse->top();
        toReverse->pop();
        Reverse(toReverse, toPush);
        toReverse->push(toSave);
    }
}

template <typename T>
void ReverseStack(stack<T> *toReverse)
{
    if (toReverse->empty())
    {
        return;
    }

    T toPush = toReverse->top();
    toReverse->pop();
    ReverseStack(toReverse);

    Reverse(toReverse, toPush);
}

template <typename T>
static void PutInPlace(stack<T> *toSort, T toPush)
{
    if (toSort->empty() || toPush < toSort->top())
    {
        toSort->push(toPush);
    }

    else
    {
        T toSave = toSort->top();
        toSort->pop();
        PutInPlace(toSort, toPush);
        toSort->push(toSave);
    }
}

template <typename T>
void SortStack(stack<T> *toSort)
{
    if (toSort->empty())
    {
        return;
    }

    T toPush = toSort->top();
    toSort->pop();

    SortStack(toSort);
    PutInPlace(toSort, toPush);
}


int main()
{
    stack<int>testStack;

    for (int i = 0; i < 10; ++i)
    {
        testStack.push(rand() % 10);
    }

    SortStack(&testStack);
    ReverseStack(&testStack);

    for (int i = 0; i < 10; ++i)
    {
        cout << testStack.top() << endl;
        testStack.pop();
    }

    return 0;
}
