#include<stdio.h>

int Josephus(int soldiers[], int n)
{
	int sword = 0, step = 0;
	int dead = 0, alive = 0;
	int last_dead = 0, flag = 0;


	/*number of kill circles*/
	for(step = 2; step < n*2; step *=2)
	{
		sword = 0;
		/*the first soldier alive*/
		while(soldiers[sword] == 0)
		{
			++sword;
		}
		if (flag == 0)
		{
			sword += (step/2);
		}
		
		/*circle kill*/
		while(sword < n)
		{
			soldiers[sword] = dead;
			sword += step;	
		}
		/*to check if the last man in the circle is alive or dead*/
		last_dead = sword - step;
		flag = ((n - last_dead) > step/2) ? 1 : 0;		
	} 	

	for(alive = 0; soldiers[alive] == 0; ++alive);

	return soldiers[alive];	
}

int main()
{
	int soldiers[100];
	int i = 0;
	for(i = 0; i < 100; ++i)
	{
		soldiers[i] = (i + 1);
	}
	printf("the last soldier alive is %d\n", Josephus(soldiers, 100));

	return 0;
}
