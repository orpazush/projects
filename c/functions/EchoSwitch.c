#include<stdio.h>
#include<stdlib.h>

void Switch(char pressed_char)
{
	switch (pressed_char)
	{
		case 'T' : printf("pressed T\n");
			break;
		case 'A' : printf("pressed A\n");
			break;
		case 27 : exit(0);
	}
}

int main()
{
	char x = 0;
	system("stty -icanon -echo");
	scanf("%c", &x);
	system("stty icanon echo"); 
	Switch(x);

	return 0;
}
