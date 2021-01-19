//
// Created by orpaz on 15/12/2020.
//
#include <string>       //string
#include <vector>       //vector
#include <iostream>     //cout

using namespace std;


void Permute(vector<string> *results, string str, size_t left, size_t right)
{
    if (left == right)
    {
        results->push_back(str);
    }
    else
    {
        for (size_t i = left; i <= right; i++)
        {
            swap(str[left], str[i]);
            Permute(results, str, left+1, right);
            swap(str[left], str[i]);
        }
    }
}

vector<string> *StringPermutations(string str)
{
    vector<string> *result = new vector<string>();

    Permute(result, str, 0, str.size()-1);

    return result;
}

int main()
{
    vector<string> *test = StringPermutations("orpaz");

    for (vector<string>::iterator i = test->begin(); i != test->end(); ++i)
    {
        cout << i.base()->begin().base() << endl;
    }

    cout << test->size() << endl;

    return 0;
}
