/******************************************************************************
*	Version 1.0
******************************************************************************/
#ifndef __STACK_H__     /* __STACK_H__ */
#define __STACK_H__     /* __STACK_H__ */

#include <stddef.h>     /* size_t */

typedef struct stack stack_t;

/******************************************************************************
*	Name: StackCreate
*	Description: creates a stack of given capacity.
*	Arguments: requested size of stack, requested size of element.
*	Return: pointer to allocated stack in case of success, otherwise NULL.
*   complexity: Dependant on system call complexity
*	Notes: 
******************************************************************************/
stack_t *StackCreate(size_t capacity, size_t element_size);


/******************************************************************************
*	Name:StackDestroy
*	Description: Frees all dynamically allocated memory to the stack
*	Arguments: a pointer to the stack to be freed
*	Return: nothing
*   complexity: Dependant on system call complexity
*	Notes: if "stack" is NULL no operations will be performed. 
******************************************************************************/
void StackDestroy(stack_t *stack);


/******************************************************************************
*	Name: StackPeek
*	Description: retrieves the address of first element of the array
*	Arguments: a pointer to the stack
*	Return: void* of the value at the "top" of the stack
*   complexity: O(1).
*	Notes: undefined behaviour is "stack" is NULL. 
******************************************************************************/
void *StackPeek(const stack_t *stack);


/******************************************************************************
*	Name: StackPop
*	Description: remove top element from stack.
*	Arguments: pointer ot a stack.
*	Return: nothing.
*   complexity: O(1).
*	Notes: undefined behaviour if "stack" is NULL or stack is free.
******************************************************************************/
void StackPop(stack_t *stack);


/******************************************************************************
*	Name: StackPush
*	Description: Inserting a new value at the top of the stack
*	Arguments: New value in void* format and Pointer to relevant stack
*	Return: no value is returned
*   complexity: O(1).
*	Notes: undefined behaviour if "stack" or "new_data" is NULL or stack is full.
******************************************************************************/
void StackPush(stack_t *stack, const void *new_data);


/******************************************************************************
*	Name: StackSize
*	Description: Returns the amount of elements.
*	Arguments: "stack" - Referenced stack object.
*	Return: amount of elements in the stack.
*   complexity: O(1).
*	Notes: undefined behaviour if "stack" is NULL.
******************************************************************************/
size_t StackSize(const stack_t *stack);


/******************************************************************************
*	Name: StackCapacity
*	Description: Returns the stack's capacity
*	Arguments: "stack" - Referenced stack object
*	Return: Returns the capacity of the stack
*   complexity: O(1).
*	Notes: Undefined behaviour if "stack" is NULL
******************************************************************************/
size_t StackCapacity(const stack_t *stack);


/******************************************************************************
*	Name: StackIsEmpty
*	Description: Returns if the stack empty or full
*	Arguments: "stack" - Referenced stack object
*	Return: Returns 1 if the stack is empty, 0 if not
*   complexity: O(1).
*	Notes: Undefined behaviour if "stack" is NULL
******************************************************************************/
int StackIsEmpty(const stack_t *stack);


#endif                  /* __STACK_H__ */
