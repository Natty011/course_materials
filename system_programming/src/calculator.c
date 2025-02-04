/***************************************
* Author : Natty
* Reviewer : Matan
* Date : 03 / 03 / 2025
* Last update: 03 / 02 / 2025
*****************************************/
#include <stdio.h>
#include <assert.h> 	/* assert */
#include <stdlib.h> 	/* malloc, free */
#include "stack.h" 
#include "calculator.h" 
/*
#define 	NodeToIter(x)		((bst_iter_t)x)
#define		IterToNode(x)		((bst_node_t*)x)	
*/
/****************struct and enum declaration*********************/
/*
typedef enum
{
    SUCCESS = 0,
    MATH_ERROR = 1,
    SYNTAX_ERROR = 2,
    SYSTEM_ERROR = 3
}status_t;
*/
typedef enum 
{
	INVALID_INPUT = 0, /* the rest */
	NUMBER_EVENT = 1, /* 49 - 57*/
	DIV = 2, /* 47 */
	MULT = 3, /* 42 */
	MINUS = 4, /* 45 */
	PLUSE = 5,  /* 43 */
	OPEN_BRACKET = 6, /* 40 */
	CLOSE_BRACKET = 7, /* 41 */
	SPACE = 8, /* 32 */
	NUM_OF_EVENTS
	
}event_t;

typedef struct 
{
	space_t handle_space;
	
	state_t CURR_STATE;
	state_t NEXT_STATE;

}handlers_array_t;

typedef enum 
{
	WAIT_FOR_NUMBER = 0,
	WAIT_FOR_NON_ZERO = 1,
	WAIT_FOR_OPERATOR = 2,
	ERROR = 3,
	NUM_OF_STATES

}state_t;

typedef struct 
{
	const char* str;
	double* result;
	const stack_t *num_stack;
	const stack_t *op_stack;

}calc_t;

/* typedef void* (*handler_t) (void* ptr, calc_t calc_state, void* result); */
/*
typedef status_t (*handler_num_t) (char* ptr, calc_t calc_state,  double* result);
typedef status_t (*space_t) (calc_t calc_state,  double* result);
typedef status_t (*minus_t) (calc_t calc_state,  double* result);    
typedef status_t (*pluse_t) (double num1, double num2, calc_t calc_state,  double result);
typedef status_t (*pluseMinuse_t) (char* ptr, calc_t calc_state, double* result);
typedef status_t (*operation_t) (char* ptr, calc_t calc_state, double* result);
typedef status_t (*bracket_t) (char* ptr, calc_t calc_state, double* result);    
typedef status_t (*error_t) (char* ptr, calc_t calc_state, double* result);
 
*/


status_t Space(calc_t calc_state, double* result)
{

}
/* global current and next state */
state_t current_state = WAIT_FOR_NUMBER;
state_t next_state = WAIT_FOR_NUMBER;

int arr_events[128] = { 0 };

status_t InitArrEvent(int *arr_event, calc_t calc_state )
{
	int i = 0;
	assert(arr_event);
	
	for(i = 0; i < 127; ++i)
	{

		if ( 32 == i  )
		{
			arr_event[i] = SPACE;
		}
		
		if ( 40 == i  )
		{
			arr_event[i] = OPEN_BRACKET;
		}
		
		if ( 41 == i  )
		{
			arr_event[i] = CLOSE_BRACKET;
		}
		if ( 42 == i  )
		{
			arr_event[i] = MULT;
		}
		
		if ( 43 == i  )
		{
			arr_event[i] = PLUSE;
		}
		
		if ( 45 == i  )
		{
			arr_event[i] = MINUS;
		}
		
		if ( 47 == i )
		{
			arr_event[i] = DIV;
		}
		
		if ( 48 <= i  && i <=57 )
		{
			arr_event[i] = NUMBER_EVENT;
		}
	}
	
}




/** possible return values **/


/*int destroy_check = SUCCESS; *//* extern */

/***************End of struct and enum declaration *******/

/***********Functions declaration*******/

status_t Space(calc_t calc_state, double* result);

/**********End of functions declaration *******/

/***********Static Functions definition*******/


/***********End Of Static Functions definition*******/


