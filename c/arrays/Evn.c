#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char *dupLowerCase(char *);
int CountElements(char *);
void printVariables (char **, int);
void FreeArr(char *arr[], int size);

int main(int argc, char **argv, char *envp[])
{
	int i = 0;
	int size = strlen(*envp) + 1;
	char **envp_lower = NULL;
	
	/*creating a new array of pointers to the envpies*/
	envp_lower = (char**)malloc(size * sizeof(char*));
	argc = 0;
	printf("%s\n", argv[argc]);
	
	for (i = 0; i < size; i++)
	{
		envp_lower[i] = dupLowerCase(envp[i]);	
	}
	
	printVariables(envp_lower, size);
	FreeArr(envp_lower, size);
	
	/*after we freed every dup we create, we free the main arr*/
	free(envp_lower);
	envp_lower = NULL;
	
	return 0;
}

char *dupLowerCase(char *s)
{
	int len = strlen(s) + 1;
	int i = 0;

	char *dup_str = (char*) malloc(len * sizeof(char));

	for (; i < len - 1; ++i)
	{
		dup_str[i] = tolower(s[i]);	
	}
	
	dup_str[i] = '\0';

	return dup_str;
}

void FreeArr(char *arr[], int size)
{
	int i = 0;
	
	for(; i < size ; ++i)
	{	
		free(arr[i]);
		arr[i] = NULL;		
	}	

	return;
}

void printVariables(char *arr[], int size)
{
	int i = 0;
	
	for(; i < size; ++i)
	{
		printf("%s\n", arr[i]);
	}
	
	return;
}





