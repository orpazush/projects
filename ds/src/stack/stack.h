/********************************************
*											*
*		code by - orpaz houta				*	
*		CR by -	Izik Avinoam				*
*		coding date - 02.04.2020			*
*                         					*
********************************************/

#ifndef __STACK_H__ 
#define __STACK_H__ 

typedef struct stack stack_t;


/* a handle to be used with this API 
 * (App Programming Interface) */


/*
* Function: StackCreate 
* -------------------------
* creates a new stack by allocating memory and initialise the stack's members
*
* parameter: the capacity of the stack
*
*  returns: pointer to the new stack
*/
stack_t *StackCreate(size_t capacity);


/*
* Function: StackDestroy 
* --------------------------
* destroy the given 'stack' of type stack_t by freeing his memory
*
* parameter: pointer to a 'stack' of type stack_t
*
*  returns: void
*/
void StackDestroy(stack_t *stack);


/*
* Function: StackPop 
* ----------------------
* releases the element on top of the stack if the stack doesn't empty
* NOTE - it is not possible to pop when stack is empty
*
* parameter: pointer to a 'stack' of type stack_t
*
* returns: void
*/
void StackPop(stack_t *stack);


/*
* Function: StackPush 
* -----------------------
* pushes a new element to the stack incase it doesn't reach it's capacity
* NOTE - it is not possible to push more then the capacity
*
* parameter: pointer to a 'stack' of type stack_t
* parameter pointer to element of type void to be pushed into the stack
*
* returns: void
*/
void StackPush(stack_t *stack, void *element);


/*
* Function: StackPeek 
* -----------------------
* peeks the element on top of the stack incase it doesn't empty
* NOTE - peeking when stack is empty will cause an undefined behviour
*
* parameter: pointer to a 'stack' of type stack_t
*
* returns: pointer to the stack's element 'on_top' or NULL when stack is empty
*/
void *StackPeek(const stack_t *stack);


/*
* Function: StackSize 
* -----------------------
* checks what the size of a given 'stack'
*
* parameter: pointer to a 'stack' of type stack_t
*
*  returns: the number of elements within the stack
*/
size_t StackSize(const stack_t *stack);


/*
* Function: StackIsEmpty 
* --------------------------
* checks if the stack is empty or not
*
* parameter: tpointer to a 'stack' of type stack_t
*
*  returns: is_empty, int 1 if empty, 0 if not 
*/
int StackIsEmpty(const stack_t *stack);


/*
* Function: StackCapacity 
* ---------------------------
* brings the maximum number of elements a given stack can hold
*
* parameter: pointer to a 'stack' of type stack_t
*
*  returns: the capacity of the stack
*/
size_t StackCapacity(const stack_t *stack);



#endif /* ifdef __STACK_H__ */ 
/* (╯°□°）╯︵ ┻━┻ */
