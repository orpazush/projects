#include <stdio.h>

int HasSumTen(const char *string)
{
    char digit_history[11] = {0};
    int digit = 0;

    while (*string)
    {
        digit = *string - '0';

        if (digit_history[10 - digit])
        {
            return 1;
        }

        ++digit_history[digit];
        ++string;
    }

    return 0;
}

int main()
{
    printf("%d\n", HasSumTen("13568482222"));
    printf("%d\n", HasSumTen("1111222277754444"));

    return (0);
}
