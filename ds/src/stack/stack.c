/********************************************************
*		build my first stack							*
*		orpaz houta										*
*		reviewed by Izik Avinoam						*
*		2.4.2020										*
********************************************************/

#include <stdio.h>
#include <malloc.h> /* malloc */
#include <assert.h> /* assert */

#include "stack.h"

#define EMPTY (-1)

struct stack
{
	void **container;
	int on_top;
	size_t capacity;
};

stack_t *StackCreate(size_t capacity)
{
	stack_t *new_stack = (stack_t *)malloc(sizeof(stack_t));
	new_stack->container = (void *)malloc(sizeof(void *) * capacity);
	if (NULL == new_stack || NULL == new_stack->container)
	{
#ifndef NDEBUG
		perror("malloc error on StackCreate new_stack:");
#endif
		return NULL;
	}
	new_stack->on_top = EMPTY;
	new_stack->capacity = capacity;

	return new_stack;
}

void StackDestroy(stack_t *stack)
{

	free(stack->container);
	stack->container = NULL;

	free(stack);
	stack = NULL;
}

void StackPush(stack_t *stack, void *element)
{
	assert(NULL != stack);

	if (StackCapacity(stack) >= StackSize(stack))
	{
		stack->on_top++;
		stack->container[stack->on_top] = element;
	}
}

void *StackPeek(const stack_t *stack)
{
	assert(NULL != stack);

	if(StackIsEmpty(stack))
	{
		return NULL;
	}

	return stack->container[stack->on_top];
}

void StackPop(stack_t *stack)
{
	assert(NULL != stack);

	if(!StackIsEmpty(stack))
	{
		stack->container[stack->on_top] = NULL;
		stack->on_top--;
	}
}

size_t StackSize(const stack_t *stack)
{
	assert(NULL != stack);
	return (stack->on_top + 1);
}

int StackIsEmpty(const stack_t *stack)
{
	assert(NULL != stack);
	return (stack->on_top == EMPTY);
}

size_t StackCapacity(const stack_t *stack)
{
	assert(NULL != stack);
	return stack->capacity;
}
