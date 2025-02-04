/***************************************
* Author : Natty
* Reviewer : Matan
* Date : 03 / 03 / 2025
* Last update: 03 / 02 / 2025
*****************************************/
#include <stdio.h>
#include <string.h> 	/* isspace, strlen */
#include <ctype.h> 		/* isspace */ 
#include <assert.h> 	/* assert */
#include <stdlib.h> 	/* malloc, free */
#include "stack.h" 
#include "calculator.h" 

#define UNUSED( var )       ( (void)var )
#define UNUSED_1( var )			( __attribute__((unused))var )






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
	PLUS = 5,  /* 43 */
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
	WAIT_FOR_NUM = 0,
	WAIT_FOR_OP = 1,
	ERROR = 2
	/*NUM_OF_STATES*/

}state_t;

typedef struct calc
{
	char *str;
	status_t curr_status;
	stack_t *num_stack;
	stack_t *op_stack;

}calc_t;

typedef state_t (*handler_t)(calc_t* calc_state,
				 double* result, double num1, double num2);

/***********Functions declaration*******/

state_t Space(calc_t* calc_state, double* result, double num1, double num2);
status_t Calc_Rest(calc_t *calc_state, double* result, double num1, double num2);
status_t InitArrEvent(char *arr_event);
status_t InitStacks(const char* expression, calc_t *p_calc_state);
state_t PushNum(calc_t *calc_state, double* result, double num1, double num2);
state_t PushPlus(calc_t *calc_state, double* result, double num1, double num2);


/**********End of functions declaration *******/

/*********************Globals****************************/
/* global current and next state */

state_t current_state = WAIT_FOR_NUM;
state_t next_state = WAIT_FOR_OP;

int arr_events[128] = { 0 };
/*
handler_t num_arr_handlers[ 10 ] = { NULL };
handler_t op_arr_handlers[ 10 ] = { NULL };
num_arr_handlers[ NUMBER_EVENT ] = PushNum;
op_arr_handlers[ PLUS ] = PushPlus;
*/
/**************End Of Globals****************************/

state_t PushNum(calc_t *calc_state, double* result, double num1, double num2)
{
	
	char* pEnd = NULL;
	
	assert(calc_state);
	assert(result);
	UNUSED(num2);
	num1 = strtod( calc_state->str, &pEnd );
	StackPush( calc_state->num_stack, &num1 );

	calc_state->str = pEnd;
	
	return WAIT_FOR_OP;
}

state_t PushPlus(calc_t *calc_state, double* result, double num1, double num2)
{
	char* str1 = NULL;
	
	assert(calc_state);
	assert(result);
	UNUSED(num1);
	UNUSED(num2);
	str1 = calc_state->str;
	/*
		1.  Use StackPeek to see the current operator in the op_stack
			before pushing thr current operator.
			
		 2. if precedence of the opertaor is lower or call to Calc_Rest 
			to do the job, and return from the the update result */
	
	calc_state->curr_status = Calc_Rest(calc_state, result, num1, num2);
	StackPush(calc_state->op_stack, calc_state->str );
	str1 = calc_state->str;
	calc_state->str = ++str1;
	
	return WAIT_FOR_OP;
}

status_t Calc_Rest(calc_t *calc_state, double* result, double num1, double num2)
{
	
	double res = 0.0;
	double sign = +1.0;
	
	assert(calc_state);
	assert(result);
	
	num1 = 0.0;
	num2 = 0.0;
	
	while( !StackIsEmpty(calc_state->num_stack) && !StackIsEmpty(calc_state->op_stack) 
	        &&   '(' != *(char*)StackPeek(calc_state->op_stack) ) 
	{
		/*
		num1 = StackPeek(calc_state->num_stack);
		StackPop(calc_state->num_stack);
		*/
		while( '-' == *(char*)StackPeek(calc_state->op_stack) )
		{
			sign = -1.0;
			num1 += *(double*)StackPeek(calc_state->num_stack);
			
			StackPop(calc_state->num_stack);
			StackPop(calc_state->op_stack); 
		}

		num1 *= sign;
		res += num1;
		
		if( !StackIsEmpty(calc_state->num_stack) )
		{
			num2 = *(double*)StackPeek(calc_state->num_stack);
			StackPop(calc_state->num_stack);
			
			res += num2;
			
		}
	}
	
	*result = res;
	
	return SUCCESS;
	
}	
	
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


/*****************************Space*************************/
state_t Space(calc_t *calc_state, double* result, double num1, double num2)
{
	char* str1 = NULL;
	
	UNUSED(num1);
	UNUSED(num2);
	UNUSED(result);
	
	assert(calc_state);
	assert( calc_state->str ); 
	/*assert(result);*/
	str1 = calc_state->str;
	
	(void)result; /* maybe not neccessery */
	
	while( isspace( str1 ) )
	{
		++str1;
	}
	calc_state->curr_status = SUCCESS;
	calc_state->str = str1;
	return current_state;
	
}

/*****************************InitArrEvent*************************/
status_t InitArrEvent(char *arr_event )
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
			arr_event[i] = PLUS;
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
	/* *(p_calc_state->result) = 0.0; */ 
	p_calc_state->num_stack = StackCreate( len, sizeof(*expression) );
	
	if( NULL == p_calc_state->num_stack )
	{
		p_calc_state->curr_status = SYSTEM_ERROR;
		return SYSTEM_ERROR;
	}
	
	p_calc_state->op_stack = StackCreate( len, sizeof(*expression) );	
	
	if( NULL == p_calc_state->op_stack )
	{
		StackDestroy(p_calc_state->num_stack );
		p_calc_state->num_stack = NULL;
		
		p_calc_state->curr_status = SYSTEM_ERROR;
		return SYSTEM_ERROR;
		
	}
	
	p_calc_state->curr_status = SUCCESS;
	return SUCCESS;
	

	
}

/*int destroy_check = SUCCESS; *//* extern */

/***************End of struct and enum declaration *******/



/***********Static Functions definition*******/


/***********End Of Static Functions definition*******/

status_t Calculate(const char* expression, double* result)
{
	
	double num1 = 0.0, num2 = 0.0;
	status_t current_status = SUCCESS; 
	event_t num_event = INVALID_INPUT;
	event_t op_event = INVALID_INPUT;
	calc_t calc_state = { 0 };
	calc_t *p_calc_state = &calc_state;
	
	handler_t num_arr_handlers[ 10 ] = { NULL };
	handler_t op_arr_handlers[ 10 ] = { NULL };
	num_arr_handlers[ NUMBER_EVENT ] = PushNum;
	op_arr_handlers[ PLUS ] = PushPlus;

	
	current_state = WAIT_FOR_NUM;
	/*next_state = WAIT_FOR_OP;*/

	InitArrEvent((char*)expression);
	current_status = InitStacks((char*)expression, p_calc_state  );
	
	if( SYSTEM_ERROR == current_status )
	{
		return SYSTEM_ERROR;
	}
	
	while( (ERROR != current_state) && *(p_calc_state->str) )
	{
		
		switch ( current_state )
		{
			case WAIT_FOR_NUM:
				num_event = arr_events[ *(int*)(p_calc_state->str) ];
				
				if(num_arr_handlers[ num_event ] != NULL) /*Not to get segmentation dump */ 
        		{

            		current_state = 
            		(num_arr_handlers[ num_event ])(p_calc_state, result, num1, num2);
       			}
       			break;
       			
			case WAIT_FOR_OP:
				 op_event = arr_events[ *(int*)(p_calc_state->str) ];
				/* (p_calc_state, result, num1, num2)*/ 
				if(num_arr_handlers[ op_event ] != NULL)  /*Not to get segmentation fault*/
				{
            		current_state = 
            		(op_arr_handlers[ op_event ])(p_calc_state, result, num1, num2);
            		
            		current_status = p_calc_state->curr_status;
       			} 
       			 break;
       			 
       		case ERROR: 
       			printf(" need to handle error, current_status = %d\n", current_status);
       			/*current_status = MATH_ERROR;*/
       			break;	
					
		}
	
	}
	
	StackDestroy(p_calc_state->num_stack );
	StackDestroy(p_calc_state->op_stack );
	
	return current_status;

}


