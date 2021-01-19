#include <stdio.h>

void SevenBoom(int from, int to)
{
	int temp = from;
	int flag = 0;
	while (from <= to)
	{
		flag = 0;
		if (from%7 == 0)
		{
			printf("BOOM\n");
			++from;
		}
		temp = from;
		while (temp > 0)
		{
			if (temp%10 == 7)
			{
				flag = 1;
				printf("BOOM\n");
				break;
			}
			temp /= 10;
		}
		if (flag == 0)
		printf("%d\n", from);
		++from;
	}
}

int main()
{
	int from = 70, to = 85;
	SevenBoom(from, to);
	return 0;
}

