//
// Created by orpaz on 30/11/2020.
//
#include <iostream>
#include <climits>

using namespace std;

bool IsPermutation(string str1, string str2)
{
    char ascii[CHAR_MAX] = {0};

    if(str1.size() != str2.size())
    {
        return (false);
    }

    for (char *i = str1.begin().base(); i != str1.end().base(); ++i)
    {
        ++ascii[*i];
    }

    for (char *i = str2.begin().base(); i != str2.end().base(); ++i)
    {
        if (ascii[*i] == 0)
        {
            return (false);
        }
        else
        {
            --ascii[*i];
        }
    }

    return (true);
}

int main()
{
    string str1("orpaz");
    string str2("zapor");
    string str3("paor");
    string str4("aposk");

    size_t tests = 0;
    tests += (true == IsPermutation(str1, str2));
    tests += (false == IsPermutation(str1, str3));
    tests += (false == IsPermutation(str1, str4));

    if (tests == 3)
    {
        cout << "success!\n";
    }

    else
    {
        cout << "failure!\n";

    }

    return 0;
}