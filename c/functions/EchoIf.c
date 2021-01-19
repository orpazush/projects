#include<stdio.h>
#include<stdlib.h>

void IfElse(char pressed_char)
{
	if(pressed_char == 'T')
	{
		printf("pressed T\n");
	}
	else if(pressed_char == 'A')
	{
		printf("pressed A\n");
	}
	else if(pressed_char == 27)
	{
		exit(0);
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
