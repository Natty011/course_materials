/***************************************
* Author : Natty
* Reviewer : Matan
* Date : 03 / 03 / 2025
* Last update: 03 / 02 / 2025
*****************************************/
#include <stdio.h>
#include <string.h> 	/* isspace, strlen */
#include <assert.h> 	/* assert */
#include <stdlib.h> 	/* malloc, free */
#include "stack.h" 
#include "calculator.h" 

#define UNUSED( var )       ( (void)var )
#define UNUSED_1( var )			( __attribute__((unused))var )



/***********Functions declaration*******/

state_t Space(calc_t* calc_state, double* result, double num1, double num2);
state_t Calc_Rest(calc_t *calc_state, double* result, double num1, double num2);
status_t InitArrEvent(int *arr_event);
status_t InitStacks(const char* expression, calc_t *p_calc_state);
state_t PushNum(calc_t *calc_state, double* result, double num1, double num2);
state_t PushPluse(calc_t *calc_state, double* result, double num1, double num2);


/**********End of functions declaration *******/


/****************struct and enum declaration*********************/

/*********************Globals****************************/
/* global current and next state */
typedef state_t (*handler_t) (calc_t* calc_state, double* result, double num1, double num2);
state_t current_state = WAIT_FOR_NUMBER;
state_t next_state = WAIT_FOR_OP;

int arr_events[128] = { 0 };
handler_t num_arr_handlers[ 10 ] = { NULL };
handler_t op_arr_handlers[ 10 ] = { NULL };
num_arr_handlers[ NUMBER_EVENT ] = PushNum;
op_arr_handlers[ PLUSE ] = PushPluse;
/**************End Of Globals****************************/

typedef enum
{
    SUCCESS = 0,
    MATH_ERROR = 1,
    SYNTAX_ERROR = 2,
    SYSTEM_ERROR = 3
}status_t;

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
	BACK_SLASH = 9, /* '0/' */
	NUM_OF_EVENTS
	
}event_t;
/*
typedef struct 
{
	space_t space;
	
	state_t NEXT_STATE;

}handlers_array_t;
*/
typedef enum 
{
	WAIT_FOR_NUMBER = 0,
	WAIT_FOR_OPERATOR = 1,
	ERROR = 2,
	NUM_OF_STATES

}state_t;

typedef struct 
{
	char *str;
	double* result;
	stack_t *num_stack;
	stack_t *op_stack;

}calc_t;


state_t PushNum(calc_t *calc_state, double* result, double num1, double num2)
{
	
}






/* typedef void* (*handler_t) (calc_t* calc_state, void* result); */
/*
typedef state_t (*handler_num_t) (char* ptr, calc_t calc_state,  double* result);
typedef state_t (*space_t) (calc_t* calc_state, double* result, double num1, double num2);
typedef state_t (*calc_rest_t) (calc_t* calc_state,  double* result);
typedef state_t (*minus_t) (calc_t calc_state,  double* result);    
typedef state_t (*pluse_t) (double num1, double num2, calc_t calc_state,  double result);
typedef state_t (*pluseMinuse_t) (char* ptr, calc_t calc_state, double* result);
typedef state_t (*operation_t) (char* ptr, calc_t calc_state, double* result);
typedef state_t (*bracket_t) (char* ptr, calc_t calc_state, double* result);    
typedef state_t (*error_t) (char* ptr, calc_t calc_state, double* result);

*/

/*****************************Calc_Rest*************************/
state_t Calc_Rest(calc_t *calc_state, double* result, double num1, double num2)
{
 /* need to complete if arrive to back_slash while the 
 	current state is WAIT_FOR_OP, if the current state is WAIT_FOR_NUM
 	then jump to next_state  = ERROR */
 	
 	/* 
 		if the cuurent state is WAIT_FOR_OP and the characther is
 		 minus, then you need to AddPluse to oprtator stack( with handler function)
 		 then ( in the same handler function ) need to Add -1 to number stack
 		 and then to Add multiple operator ( * ) to operator stack and now
 		 to send the stack to func Calc_Rest because the precedance is violats
 		 because i enter * after + and + is lower precedance then * .
 		 After returning from calc_rest you need to pass ( the current state)
 		 to WAIT_FOR_NUM. 
 	*/


}


/*****************************Space*************************/
state_t Space(calc_t *calc_state, double* result, double num1, double num2)
{
	char* str1 = NULL;
	calc_state->str;
	
	UNUSED(num1);
	UNUSED_1(num2);
	UNUSED_1(result);
	
	assert(calc_state);
	assert( calc_state->str ); 
	/*assert(result);*/
	str1 = calc_state->str;
	
	(void)result; /* maybe not neccessery */
	
	while( isspace( str1 ) );
	{
		++str1;
	}
	
	calc_state->str = str1;
	return current_state;
	
}

/*****************************InitArrEvent*************************/
status_t InitArrEvent(int *arr_event )
{
	size_t i = 0;
	assert(arr_event);
	
	for(i = 0; i < 127; ++i)
	{

		if ( 0 == i )
		{
			arr_event[i] = BACK_SLASH;
		}
		
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
	
	return SUCCESS;
	
}
/**********************InitStacks *******************************/
status_t InitStacks(const char* expression, calc_t *p_calc_state)
{
	size_t len = 0;

	assert(p_calc_state);
	assert(expression);
	
	len = strlen(expression);
	p_calc_state->str = (char*)expression;
	*(p_calc_state->result) = 0.0;
	p_calc_state->num_stack = StackCreate( len, sizeof(*expression) );
	
	if( NULL == p_calc_state->num_stack );
	{
		return SYSTEM_ERROR;
	}
	
	p_calc_state->op_stack = StackCreate( len, sizeof(*expression) );	
	
	if( NULL == p_calc_state->op_stack );
	{
		free( p_calc_state->num_stack);
		p_calc_state->num_stack = NULL;
		
		return SYSTEM_ERROR;
	}
	
	return SUCCESS;
	
}

/*int destroy_check = SUCCESS; *//* extern */

/***************End of struct and enum declaration *******/



/***********Static Functions definition*******/


/***********End Of Static Functions definition*******/

status_t Calculate(const char* expression, double* result)
{
	
	current_state = WAIT_FOR_NUM;
	/*next_state = WAIT_FOR_OP;*/
	/*
	handlers_array_t num_array = { 0 };
	handlers_array_t op_array = { 0 };
	*/
	status_t init_res = SUCCESS;
	
	event_t num_event = INVALID_INPUT;
	event_t op_event = INVALID_INPUT;
	
	calc_t calc_state = { 0 };
	
	calc_t *p_calc_state = &calc_state;
	
	InitArrEvent(expression);
	init_res = InitStacks( p_calc_state );
	
	if( SYSTEM_ERROR == init_res )
	{
		return SYSTEM_ERROR;
	}
	
	while( (ERROR != current_state) && (*expression) )
	{
		
		switch ( current_state )
		{
			case WAIT_FOR_NUM:
				num_event = arr_events[ *expression ];
				 
			
				
				
				
		}
	
	}

}


