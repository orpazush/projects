//
// Created by orpaz on 01/12/2020.
//

#include <iostream>
#include <cstring>

using namespace std;

bool IsRotation(const char *str1, const char *str2)
{
    size_t len1 = strlen(str1);

    if (len1 != strlen(str2))
    {
        return false;
    }

    for (size_t i = 0; i < len1; ++i)
    {
        if (*str1 == str2[i])
        {
            std::size_t rightRot = 0;
            for (std::size_t j = i;
            str1[rightRot] == str2[j % len1] && rightRot < len1;
            ++j, ++rightRot)
            {
            }

            if (rightRot == len1)
            {
                return true;
            }
        }
    }

    return false;
}
bool ShortIsRotation(const char *str1, const char *str2)
{
    string string1(str1);
    string1 += str1;

    return (string::npos != string1.find(str2));
}


int main()
{
    char *str1 = "ororpaz";
    char *yes = "azororp";
    char *no = "orpazro";

    std::size_t tests = 0;
    tests += (true == IsRotation(str1, yes));
    tests += (false == IsRotation(str1, no));

    tests += (true == ShortIsRotation(str1, yes));
    tests += (false == ShortIsRotation(str1, no));

    ((tests == 4) ? cout << "success!\n" : cout << "failure!\n");

    return 0;
}
