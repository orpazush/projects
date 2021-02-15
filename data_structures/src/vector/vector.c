/********************************************************
*			orpaz houta									*
*			reviewed by Gil Steinberg					*
*			6.4.2020									*
********************************************************/

#include <stdio.h>	/* size_t */
#include <malloc.h> /* malloc, realloc */

#include "vector.h"


#define EMPTY (0)

enum status{SUCCESS, FAILURE};

struct vector
{
	size_t size;
	size_t capacity;
	void **array;
};

vector_t *VectorCreate(size_t capacity)
{
	vector_t *new_vector = (vector_t *)malloc(sizeof(vector_t));

	if (NULL == new_vector)
	{
#ifndef NDEBUG
		perror("VectorCreate malloc error");
#endif
		return NULL;
	}

	new_vector->array = (void **)malloc(sizeof(void *) * capacity);

	if (NULL == new_vector->array)
	{
#ifdef NDEBUG
		perror("VectorCreate->array malloc error");
#endif
		return NULL;
	}
	new_vector->size = EMPTY;
	new_vector->capacity = capacity;

	return new_vector;
}

void VectorDestroy(vector_t *vector)
{
	free(vector->array);
	vector->array = NULL;

	free(vector);
	vector = NULL;
}

void *VectorGetElementAddress(const vector_t *vector, size_t index)
{
	return vector->array[index];
}

void VectorSetElementAddress(vector_t *vector, size_t index, void *element)
{
	vector->array[index] = element;
}

int VectorReserve(vector_t *vector, size_t new_capacity)
{
	void **backup = NULL;

	backup = vector->array;

	vector->array = (void **)realloc
						(vector->array,(sizeof(void *) * new_capacity));
	if (NULL == vector->array)
	{
#ifndef NDEBUG
		perror("VectorReserve: realloc error\n");
#endif
		vector->array = backup;
		return FAILURE;
	}
	vector->capacity = new_capacity;
	backup = NULL;

	return SUCCESS;
}

int VectorShrinkToFit(vector_t *vector)
{
	void **backup = vector->array;

	backup = (void **)realloc(vector->array, sizeof(void *) * vector->size);
	if (NULL == backup)
	{
		free(backup);
		return FAILURE;
	}
	vector->capacity = vector->size;
	vector->array = backup;
	backup = NULL;

	return SUCCESS;
}

int VectorPushBack(vector_t *vector, void *element)
{
	void **backup = vector->array;

	if (vector->size == vector->capacity)
	{
		vector->capacity *= 1.5;

		vector->array = (void **)realloc
						(vector->array, sizeof(void *) * (vector->capacity + 1));
	}

	if (NULL == vector->array)
	{
		vector->array = backup;
		return FAILURE;
	}
	vector->array[vector->size] = element;
	vector->size++;
	backup = NULL;

	return SUCCESS;
}

void VectorPopBack(vector_t *vector)
{
	if (EMPTY != vector->size)
	{
		vector->array[--(vector->size)] = NULL;
	}
}

size_t VectorSize(const vector_t *vector)
{
	return vector->size;
}

size_t VectorCapacity(const vector_t *vector)
{
	return vector->capacity;
}
