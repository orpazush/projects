//
// Created by orpaz on 06/01/2021.
//

//*Time complexity:O(n),  space complexityO(1)


#include <cstring>
#include <iostream>

static char *reverseWords(char str[])
{
    static const char MAX_LETTERS_IN_WORD = 50;

    char bufferLeft[MAX_LETTERS_IN_WORD];
    char bufferRight[MAX_LETTERS_IN_WORD];

    char *leftBufPtr = bufferLeft;
    char *rightBufPtr = bufferRight;

    char *leftP = str;
    char *rightP = str + strlen(str) - 1;

    char *lefty = leftP;
    char *righty = rightP;

    for (; leftP < rightP; ++lefty, --righty)
    {
        if (*righty == ' ')
        {
            while (rightBufPtr > bufferRight)
            {
                *leftP = *rightBufPtr;
                ++leftP;
                --rightBufPtr;
            }
        }

        if (*lefty == ' ')
        {
            while (leftBufPtr > bufferLeft)
            {
                *rightP = *leftBufPtr;
                --rightP;
                --leftBufPtr;
            }
        }

        ++leftBufPtr;
        *leftBufPtr = *lefty;

        ++rightBufPtr;
        *rightBufPtr = *righty;
    }

    return str;
}


int main()
{
    char test1[] = "there is nothing to do with you now";
    reverseWords(test1);

    std::cout << test1 << std::endl;

    return 0;
}