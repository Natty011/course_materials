/***************************************
* Author : Natty
* Reviewer : Hadar
* Date : 04 / 12 / 2024
* Last update: 08 / 12 / 2024
*****************************************/

#include <assert.h> /* assert */
#include <stdlib.h> /* malloc, free*/
#include <string.h> /* memcpy */
#include "stack.h" /*  */


/****************struct and enum declaration declaration*********************/

struct stack
{

size_t capacity;
size_t current_size;
size_t element_size;
char* top_element;
char* array;

};

/***************End of struct and enum declaration declaration*******/


/********************  StackCreate  ****************************/
stack_t *StackCreate(size_t capacity, size_t element_size)
{
	stack_t* p_stack = NULL;
	p_stack = (stack_t*)malloc(sizeof(struct stack));
	
	if ( NULL == p_stack )
	{
		return NULL;
	}
	
	p_stack->array =(char*)malloc(capacity*element_size);
	
	if ( NULL == p_stack->array )
	{
		free(p_stack);
		p_stack = NULL;
		return NULL;
	}
	
	p_stack->element_size = element_size;
	p_stack->top_element =p_stack->array - p_stack->element_size;
	p_stack->capacity = capacity;
	p_stack->current_size = 0;
	return 	p_stack;
}	
/********************  StackDestroy  ****************************/
void StackDestroy(stack_t *stack)
{
	free(stack->array);
	stack->array = NULL;
	free(stack);
	stack = NULL;
}
/********************  StackPeek  ****************************/
void *StackPeek(const stack_t *stack)
{
	assert(stack);
	return stack->top_element;
}
/********************  StackPop  ****************************/
void StackPop(stack_t *stack)
{
	assert(stack);
	stack->top_element -= stack->element_size;
    --stack->current_size;	
}
/********************  StackPush  ****************************/
void StackPush(stack_t *stack, const void *new_data)
{
	assert(stack);
	stack->top_element += stack->element_size;
	memcpy(stack->top_element, new_data, stack->element_size);
	++stack->current_size;
}
/********************  StackSize  ****************************/
size_t StackSize(const stack_t *stack)
{
	assert(stack);
	return stack->current_size;
}
/********************  StackCapacity  ****************************/
size_t StackCapacity(const stack_t *stack)
{
	assert(stack);
	return stack->capacity;
}
/********************  StackIsEmpty  ****************************/
int StackIsEmpty(const stack_t *stack)
{
	assert(stack);
	return  0 == stack->current_size;
}







