/********************************************************
*			build my first vector						*
*			orpaz houta									*
*			reviewed by Gil Steinberg					*	
*			6.4.2020									*
********************************************************/

#include <stdio.h>

#include "vector.h"

int main()
{
	vector_t *new_vector;

	int element_int = 6;
	float element_float = 184.2565;
	char *element_string = "chodashim veday";
	
	new_vector = VectorCreate(2);

	printf("capacity of new vector: %ld\n", VectorCapacity(new_vector));

	VectorSetElementAddress(new_vector, 1, "tagid li ad matay?");
	
	printf("get element after setting: ");
	printf("%s\n",(char *)VectorGetElementAddress(new_vector, 1));
	
	VectorPushBack(new_vector, &element_int);
	printf("push int: %d\n",*(int *)VectorGetElementAddress(new_vector, 0));

	VectorPushBack(new_vector, element_string);
	printf("push string: %s\n",(char *)VectorGetElementAddress(new_vector, 1));
	
	printf("size of vector: %ld\n", VectorSize(new_vector));

	printf("did push went well? %d\n",VectorPushBack(new_vector, &element_float));
	
	printf("push float: %f\n",*(float *)VectorGetElementAddress(new_vector, 2));
	
	printf("capacity after growth *1.5: %ld\n", VectorCapacity(new_vector));

	printf("size befor popback: %ld\n", VectorSize(new_vector));
	VectorPopBack(new_vector);
	printf("size after popback: %ld\n", VectorSize(new_vector));

	VectorReserve(new_vector, 8);
	printf("capacity after reserve to 8: %ld\n", VectorCapacity(new_vector));
	
	printf("did shrink went well? %d\n", VectorShrinkToFit(new_vector));
	printf("capacity after shrink: %ld\n", VectorCapacity(new_vector));

	printf("get last element %d\n",*(int *)VectorGetElementAddress(new_vector, 0));
	
	VectorDestroy(new_vector);

	return 0;
}


