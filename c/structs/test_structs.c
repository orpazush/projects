#include <stdio.h>

#include "add_types.h" 

/********************************************************
*		multytype array				*
*		orpaz houta				*
*		reviewed by omer hefetz			*	
*		29.3.2020				*
********************************************************/
#define ARRAY_SIZE 6

int main()
{
	elements_t *new_arr = NULL;	

	new_arr = CreateArray(ARRAY_SIZE, 1, 85, 3, "ribono shel olam", 2, 3,
			     "im nedaber gluyot", 2, 100.22, 3.558565, 1, 97777777); 

	PrintElements(new_arr, ARRAY_SIZE);

	AddToElements(new_arr, ARRAY_SIZE, 5);

	PrintElements(new_arr, ARRAY_SIZE);

	CleanUp(new_arr, ARRAY_SIZE);

	return 0;
}



