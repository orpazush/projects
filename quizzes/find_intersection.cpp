//
// Created by orpaz on 29/11/2020.
//

#include <list> //list
#include <iterator>

using namespace std;

template <typename T>
typename list<T>::const_iterator GetIntersection(const list<T>& list1, const list<T>& list2)
{
    size_t len_list1 = list1.size();
    size_t len_list2 = list2.size();

    list<T>::iterator i(list1.begin());
    list<T>::const_iterator;
    j(list2.begin());

    while (len_list1 > len_list2)
    {
        ++i;
        --len_list1;
    }

    while (len_list2 > len_list1)
    {
        ++j;
        --len_list2;
    }

    for ( ;i != list1.end(); ++i, ++j)
    {
        if (i == j)
        {
            return i;
        }
    }
}

int main()
{
    list<int> list1 = {1, 3, 5, 6, 9};
    list<int> list2 = {2, 4, 8, 8, 100, 1, 6};
//
//    list2.end()._M_node->_M_next = list1.begin()._M_node;
//
//    list<int>::iterator res = GetIntersection(list1, list2);


}