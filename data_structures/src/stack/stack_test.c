/********************************************************
*		build my first stack							*
*		orpaz houta										*
*		reviewed by Izik Avinoam						*	
*		2.4.2020										*
********************************************************/

#include <stdio.h>

#include "stack.h"

int main()
{
	stack_t *mystack = NULL;

	int element_int = 589;
	float element_float = 84.2565;
	char *element_string = "beguf ayef mekishlonot";
	
	mystack = StackCreate(40);

	printf("isempty? when empty: %d\n", StackIsEmpty(mystack));

	printf("capacity check: %ld\n", StackCapacity(mystack));

	StackPush(mystack, element_string);
	printf("first element of type string: %s\n", (char *)StackPeek(mystack));

	StackPush(mystack, "belev shavur lehatichot");
	printf("second element of type string: %s\n", (char *)StackPeek(mystack));

	printf("stack size: %ld\n", StackSize(mystack));

	StackPush(mystack, &element_int);
	printf("third element of type int: %d\n", *(int *)StackPeek(mystack));
	
	printf("when stack is not empty: %d\n", StackIsEmpty(mystack));

	StackPush(mystack, &element_float);
	printf("forth element of type float: %f\n", *(float *)StackPeek(mystack));

	StackPop(mystack);

	printf("peeking after pop: %d\n", *(int *)StackPeek(mystack));

	printf("capacity check: %ld\n", StackCapacity(mystack));	

	StackDestroy(mystack);

	return 0;	
}

