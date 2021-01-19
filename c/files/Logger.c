#include<stdio.h>/*printf, scanf..*/
#include<stdlib.h>/*exit*/
#include<string.h>/*strcmp, strlen*/

int WriteToFile(char* request, char* file_name);
int ExitProgram(char *file_name);
int RemoveFile(char *file_name);
int CountLines(char *filename);

/*only for appearence i thoght it would help me more then it really has*/
typedef int (*FunctionC)(const char *string1, const char *string2);
typedef int (*FunctionO)(char *string1);

enum State {WORKING = 0, FAILED = 1};

typedef struct 
{
	char *name;
	FunctionC comparison;
	FunctionO operation;
} HANDLER;

int main(int argc, char *argv[])
{
	char *Filename = NULL;
	char request[20];
	int array_size = 0;
	int check = 0, errors = 0, i = 0;
	HANDLER Handlers[] = {
				{"-exit", strcmp, ExitProgram},
				{"-remove", strcmp, RemoveFile},
				{"-count", strcmp, CountLines}
				};

	if(argc < 2)
	{
		printf("ERROR! file has not been entered");
	}
	Filename = argv[1];

	array_size = sizeof(Handlers)/sizeof(Handlers[0]);
	
	while(1)
	{
		printf("enter your request here please:\n");
		gets(request);

		WriteToFile(request, Filename);

		for(i = 0; i < array_size; ++i)
		{
			check = Handlers[i].comparison(request, Handlers[i].name);
			if(check == 0)
			{
				errors = Handlers[i].operation(Filename);
				if(errors != 0)
				{
					printf("ERROR! last request failed");
				}
			}
		}
	}

	return 0;
}

int ExitProgram(char *file_name)
{
	printf("the operation program on file %s is about to exit\n", file_name);
	exit(0);
	
	return WORKING;
}

int RemoveFile(char *file_name)
{
	return remove(file_name);
}

int CountLines(char *filename)
{
	FILE *filePointer; 
	int count = 0; 
	char chr = '\0';  

	filePointer = fopen(filename, "r"); 

	if (filePointer == NULL) 
	{ 
		return FAILED; 
	} 
	
	for (chr = getc(filePointer); chr != EOF; chr = getc(filePointer))
	{ 
		if (chr == '\n')
		{ 
			count = count + 1;
		} 
	}

	fclose(filePointer); 

	printf("file %s has %d lines\n",filename, count); 
  
	return WORKING; 
}

int WriteToFile(char* request, char* file_name)
{
	FILE *file_pointer;
	file_pointer = fopen(file_name, "a+");
	
	if(file_pointer == NULL)
	{
		return FAILED;                
	}

	/*write to the begining of the file*/
	if (request[0] == '<')
	{
		FILE* tmp_pointer;
		char c = 0;
		char* tmp_name = "tmp.txt";

		tmp_pointer = fopen(tmp_name, "a+");
		
		if (tmp_pointer == NULL)
		{
			return FAILED;
		}
		
		/*first add the request to a new temporary file*/
		fprintf(tmp_pointer, "%s\n", ++request); 
	
		/*add contents of the file to the temporary*/
		while (c != EOF)
		{
			c = fgetc(file_pointer);
			fputc(c, tmp_pointer);
		}
		
		fclose(tmp_pointer);
		fclose(file_pointer);
		
		remove(file_name);
		rename(tmp_name, file_name);
	}
	/*write to the end of the file*/
	else
	{
		fprintf(file_pointer, "%s\n", request);
		fclose(file_pointer);
	}
	return WORKING;
}

