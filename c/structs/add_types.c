#include <stdio.h>
#include <stdarg.h> /* va_start, va_list, va_end */
#include <string.h> 	/* strlen */
#include <malloc.h>	/* malloc */

/********************************************************
*		multytype array				*
*		orpaz houta				*
*		reviewed by omer hefetz			*	
*		31.3.2020				*
********************************************************/

#define MAX_STRING 100

typedef enum type_t{ERROR, INT, FLOAT, STRING}type_t;

typedef union value_t
{
	char *type_string;
	float type_float;
	int type_int;
}value_t;

typedef struct elements_t
{
	value_t value;
	type_t data_type;
}elements_t;

elements_t *CreateArray(size_t num_of_elements, ...)
{
	size_t i = 0;
	type_t input_data_type = 0;
	char *for_string = NULL;
	va_list arguments;

	elements_t *new_arr = malloc(sizeof(elements_t)*(num_of_elements));

	va_start(arguments, num_of_elements);

	for(i = 0; i < num_of_elements; i++)
	{
		input_data_type = va_arg(arguments, type_t);
		
		switch(input_data_type)
		{
			case INT:
			new_arr[i].data_type = INT;
			new_arr[i].value.type_int = va_arg(arguments, int);
			break;

			case FLOAT:
			new_arr[i].data_type = FLOAT;
			new_arr[i].value.type_float = va_arg(arguments, double);
			break;

			case STRING:
			for_string = va_arg(arguments, char *);
			new_arr[i].data_type = STRING;
			new_arr[i].value.type_string = malloc(strlen(for_string) + 1);
			sprintf(new_arr[i].value.type_string,"%s", for_string);
			break;
			
			default:
			printf("error: type %d undifine\n", new_arr[i].data_type);
		}
	}
	
	va_end(arguments);

	return new_arr;
}

void PrintElements(elements_t new_arr[], size_t num_of_elements)
{
	size_t i = 0;
	
	for(i = 0; i < num_of_elements; i++)
	{	
		switch(new_arr[i].data_type)
		{
			case INT:
			printf("%d\n", new_arr[i].value.type_int);
			break;
			
			case FLOAT:
			printf("%f\n", new_arr[i].value.type_float);
			break;
			
			case STRING:
			printf("%s\n", new_arr[i].value.type_string);
			break;

			default:
			printf("Error: Could not identify data type.\n");  
			break;
		}
	}
}
char *AddToString(char *string, int to_add)
{
	char *new_string = NULL;
	int new_string_size = sizeof(char)*(strlen(string) + MAX_STRING);
	
	new_string = malloc(new_string_size);
	sprintf(new_string, "%s%d", string, to_add);
	free(string);
	string = new_string;

	return string;
}

void AddToElements(elements_t array_to_add[], size_t num_of_elements, int to_add)
{
	size_t i = 0;

	for(i = 0; i < num_of_elements; i++)
	{	
		switch(array_to_add[i].data_type)
		{
			case INT:
			array_to_add[i].value.type_int += to_add;
			break;
			
			case FLOAT:
			array_to_add[i].value.type_float += to_add;
			break;
			
			case STRING:
			array_to_add[i].value.type_string = 
			AddToString(array_to_add[i].value.type_string, to_add);
			break;

			default:
			printf("Error: Could not identify data type.\n");  
			break;
		}
	}
}

void CleanUp(elements_t *arr_to_clean, size_t num_of_elements)
{
	size_t i = 0;

	for (i = 0; num_of_elements> i; ++i)
	{
		if (arr_to_clean[i].data_type == 3)
		{
			free(arr_to_clean[i].value.type_string);
		}
	}
	free(arr_to_clean);
}




