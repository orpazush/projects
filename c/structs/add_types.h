#ifndef __ADD_TYPES_H__
#define __ADD_TYPES_H__

/********************************************************
*		multytype array				*
*		orpaz houta				*
*		reviewed by omer hefetz			*	
*		29.3.2020				*
********************************************************/

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

/* function to crate an array of elements from different data types
according to inserted values */

elements_t *CreateArray(size_t num_of_elements, ...);


/* function that recieves an array of elements from different types and prints them */

void PrintElements(elements_t new_arr[], size_t num_of_elements);


/* function that recieves an array of elements from different types and add
every element a requested number 'to_add' (in case of type string concatation) */

void AddToElements(elements_t array_to_add[], size_t num_of_elements, int to_add);


/* sub function to 'AddToElements' to concat number to string */

char *AddToString(char *string, int to_add);


/* clean up aloocated memory */

void CleanUp(elements_t *arr_to_clean, size_t num_of_elements);


#endif
