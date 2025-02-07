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
	
	FALSE = 0,
	TRUE = 1
	
}func_result_t;


typedef enum 
{
	INVALID_INPUT = 0, /* the rest */
	NUMBER_EVENT = 1, /* 48 - 57*/
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

typedef enum 
{

	ZERO_CHAR = '0', /* 48*/
	DIV_CHAR = '/', /* 47 */
	MULT_CHAR = '*', /* 42 */
	MINUS_CHAR = '-', /* 45 */
	PLUS_CHAR = '+',  /* 43 */
	OPEN_BRACKET_CHAR = '(', /* 40 */
	CLOSE_BRACKET_CHAR = ')', /* 41 */
	SPACE_CHAR = ' ', /* 32 */
	BACK_SLASH_CHAR = '\0' /* '0/' */

}characther_t;


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
	state_t curr_state;
	status_t curr_status;
	stack_t *num_stack;
	stack_t *op_stack;

}calc_t;

typedef state_t (*handler_t)(calc_t* calc_state, double* result);

/***********Functions declaration*******/

state_t Space(calc_t* calc_state, double* result);
status_t CalcRest(calc_t *calc_state, double* result);
status_t InitArrEvent(int *arr_event);
status_t InitStacks(const char* expression, calc_t *p_calc_state);
static void InitNumHandlers(handler_t* num_arr_handlers  );
state_t PushNum(calc_t *calc_state, double* result);
state_t PushPlus(calc_t *calc_state, double* result);
state_t PushDiv(calc_t *calc_state, double* result);
state_t PushMult(calc_t *calc_state, double* result);
state_t Error(calc_t *calc_state, double* result);
static double CalcTwoNum(double num_left, double num_right, char op);
static int IsDigit( char ch );
/**********End of functions declaration *******/

/*********************Globals****************************/
/* global current and next state */

state_t current_state = WAIT_FOR_NUM;
/*state_t next_state = WAIT_FOR_OP;*/

int arr_events[128] = { 0 };

/**************End Of Globals****************************/

/**************PushNum****************************/
state_t PushNum(calc_t *calc_state, double* result)
{

	double num1 = 1.0;
	assert(calc_state);
	assert(result);

	if( ZERO_CHAR == *(calc_state->str) && IsDigit( *((calc_state->str) + 1)) )
	{
	    calc_state->curr_status = SYNTAX_ERROR;
		calc_state->curr_state = ERROR;
		*result = 0.0;
		return ERROR;	
	
	}

	num1 = strtod( calc_state->str, &calc_state->str );
	printf("PushNum_num1 = %f\n", num1);
	if( !num1 && !StackIsEmpty( calc_state->op_stack ) 
		&& DIV_CHAR == *(char*)StackPeek(calc_state->op_stack)   )
	{
	    calc_state->curr_status = MATH_ERROR;
		calc_state->curr_state = ERROR;
		*result = 0.0;
		return ERROR;	
	
	}
	
	printf("! PushNum_num1 = %d\n", !num1);
	StackPush( calc_state->num_stack, &num1 );

	return WAIT_FOR_OP;
}


/**************PushPlus****************************/
state_t PushPlus(calc_t *calc_state, double* result)
{
	
	assert(calc_state);
	assert(result);

	/*
		1.  Use StackPeek to see the current operator in the op_stack
			before pushing thr current operator.
			
		 2. if precedence of the opertaor is lower or call to CalcRest 
			to do the job, and return from the the update result */
	/*if( '+' != *(calc_state->str ) )*/
	
	calc_state->curr_status = CalcRest(calc_state, result);
	/*
	if( '\0' == *(calc_state->str ) )
	{
		return WAIT_FOR_NUM;
	}
	*/
	StackPush(calc_state->op_stack, calc_state->str );

	++(calc_state->str);
	
	return WAIT_FOR_NUM;
}

/**************PushMinus****************************/
state_t PushMinus(calc_t *calc_state, double* result)
{
	
	assert(calc_state);
	assert(result);
	/**pluse = PLUS_CHAR;*/
	/*
		1.  Use StackPeek to see the current operator in the op_stack
			before pushing thr current operator.
			
		 2. if precedence of the opertaor is lower or call to CalcRest 
			to do the job, and return from the the update result */
	/*if( '+' != *(calc_state->str ) )*/
	
	calc_state->curr_status = CalcRest(calc_state, result);
	/*
	if( '\0' == *(calc_state->str ) )
	{
		return WAIT_FOR_NUM;
	}
	*/

	/*printf("before_*calc_state->str _PushMinus = %c\n" , *calc_state->str );*/
	StackPush(calc_state->op_stack, calc_state->str );
	++(calc_state->str);

	/*printf("after_*calc_state->str _PushMinus = %c\n" , *calc_state->str );*/

	/*printf("BACK_SLASH_CHAR = %d \n", BACK_SLASH_CHAR);*/
	
	
	return WAIT_FOR_NUM;
}


/**************PushUnaryMinus****************************/
state_t PushUnaryMinus(calc_t *calc_state, double* result)
{
	
	char op = MULT_CHAR;
	double num = -1.0;
	
	assert(calc_state);
	assert(result);

	/*
		1.  Use StackPeek to see the current operator in the op_stack
			before pushing thr current operator.
			
		 2. if precedence of the opertaor is lower or equal then  call to CalcRest 
			to do the job, and return from there the updated result */
	/*if( '+' != *(calc_state->str ) )*/
	
	/*calc_state->curr_status = CalcRest(calc_state, result);*/
	/*
	if( '\0' == *(calc_state->str ) )
	{
		return WAIT_FOR_NUM;
	}
	*/

	/*printf("before_*calc_state->str _PushMinus = %c\n" , *calc_state->str );*/
	StackPush(calc_state->op_stack, &op );
	StackPush( calc_state->num_stack, &num );
	++(calc_state->str);

	/*printf("after_*calc_state->str _PushMinus = %c\n" , *calc_state->str );*/

	/*printf("BACK_SLASH_CHAR = %d \n", BACK_SLASH_CHAR);*/
	
	return WAIT_FOR_NUM;
}

/**************PushDiv****************************/
state_t PushDiv(calc_t *calc_state, double* result)
{
		
	assert(calc_state);
	assert(result);
	
	StackPush(calc_state->op_stack, calc_state->str );
	++(calc_state->str);
	
	return WAIT_FOR_NUM;
	
}

/**************PushMult****************************/
state_t PushMult(calc_t *calc_state, double* result)
{
		
	assert(calc_state);
	assert(result);
	
	StackPush(calc_state->op_stack, calc_state->str );
	++(calc_state->str);
	
	return WAIT_FOR_NUM;
	
}		
/**************Error****************************/

state_t Error(calc_t *calc_state, double* result)
{
	/* After Push the operator to the operator stack
		and increment the expression-> check what is
									 the current expression */
	UNUSED( result );								 
	if( WAIT_FOR_OP == calc_state->curr_state &&  
		BACK_SLASH_CHAR == *(calc_state->str)  )
	{
		switch ( *(char*)StackPeek(calc_state->op_stack) ) /* what operator i did pushed before  */
		{
			case CLOSE_BRACKET_CHAR:
				 calc_state->curr_status = SUCCESS;
				 return WAIT_FOR_OP;
			
			default:
				calc_state->curr_status = SYNTAX_ERROR;
				return ERROR;
		}
	}
	/* !StackIsEmpty(calc_state->num_stack) */
	 /* !StackIsEmpty(calc_state->op_stack) */ 
	
	if(	WAIT_FOR_NUM == calc_state->curr_state )
	{
		switch ( *(calc_state->str) ) /* before pushing number */
		{
			/*
			case DIV_CHAR:
				if (ZERO_CHAR == *(calc_state->str) )
				{
					calc_state->curr_status = MATH_ERROR;
					return ERROR;
				}
					 		
			case CLOSE_BRACKET_CHAR:
				 calc_state->curr_status = SYNTAX_ERROR;
				 return ERROR;
			*/	
			default:
				calc_state->curr_status = SYNTAX_ERROR;
				calc_state->curr_state = ERROR;
				*result = 0.0;
				return ERROR;
		}
	}
	 
	if(	WAIT_FOR_NUM == calc_state->curr_state )
	{
		switch ( *(char*)StackPeek(calc_state->op_stack) ) /* before pushing number */
		{
			case DIV_CHAR:
				if (ZERO_CHAR == *(calc_state->str) )
				{
					calc_state->curr_status = MATH_ERROR;
					calc_state->curr_state = ERROR;
					*result = 0.0;
					return ERROR;
				}
				break;
					 		
			case CLOSE_BRACKET_CHAR:
				 calc_state->curr_status = SYNTAX_ERROR;
				 calc_state->curr_state = ERROR;
				*result = 0.0;
				 return ERROR;
				
			default:
				calc_state->curr_status = SYNTAX_ERROR;
				calc_state->curr_state = ERROR;
				*result = 0.0;
				return ERROR;
		}
	}

	return ERROR; /* WILL NOT ARRIVE HERE */
}

/**************CalcRest****************************/
status_t CalcRest(calc_t *calc_state, double* result)
{
	
	double res = 0.0, num_right = 0.0, num_left = 0.0;
	char operator = DIV_CHAR;
	/*double sign = +1.0;*/
	
	assert(calc_state);
	assert(result);
	
	/* if the user insert only one positive number */
	*result = *(double*)StackPeek(calc_state->num_stack);
	/* (StackSize(calc_state->num_stack) > 1 ) && */
	/* !StackIsEmpty(calc_state->num_stack) &&*/
	while(  !StackIsEmpty(calc_state->op_stack) && 
			
	         OPEN_BRACKET_CHAR != *(char*)StackPeek(calc_state->op_stack) ) 
	{
	
		operator = *(char*)StackPeek(calc_state->op_stack);
		StackPop( calc_state->op_stack );
		
		num_right  = *(double*)StackPeek(calc_state->num_stack);
		StackPop(calc_state->num_stack);
		num_left = *(double*)StackPeek(calc_state->num_stack);
		StackPop(calc_state->num_stack);
		
		res = CalcTwoNum(num_left, num_right, operator );
			
		/*printf("num_right = %f \n", num_right);*/
		/*printf("num_left = %f \n", num_left);	*/
		/*printf("res  = %f \n", res);*/
		
		*result = res; 

		/*printf(" *result(if empty_op_stack) = %f \n", *result);*/

		StackPush( calc_state->num_stack , result );
		
		res = 0.0, num_right = 0.0, num_left = 0.0;	
	}
	
	return SUCCESS;
	
}
/**************CalcTwoNum****************************/
static double CalcTwoNum(double num_left, double num_right, char op)
{
	switch( op )
	{
		case PLUS_CHAR:
			return num_left + num_right;
				
		case MINUS_CHAR:
			return num_left - num_right;
						
		case MULT_CHAR:
			return num_left * num_right;
							
		case DIV_CHAR:
			return num_left / num_right;
	}
	
	return 0.0; /* should not to arrive here */
			
}
/**************IsDigit****************************/
static int IsDigit( char ch )
{
	return  ('0' <= ch) &&  (ch <= '9' ) ;
}	
		
			
	
 /* need to complete if arrive to back_slash while the 
 	current state is WAIT_FOR_OP, if the current state is WAIT_FOR_NUM
 	then jump to next_state  = ERROR */
 	
 	/* 
 		if the cuurent state is WAIT_FOR_OP and the characther is
 		 minus, then you need to AddPluse to oprtator stack( with handler function)
 		 then ( in the same handler function ) need to Add -1 to number stack
 		 and then to Add multiple operator ( * ) to operator stack and now
 		 to send the stack to func CalcRest because the precedance is violats
 		 because i enter * after + and + is lower precedance then * .
 		 After returning from CalcRest you need to pass ( the current state)
 		 to WAIT_FOR_NUM. 
 	*/




/*****************************CalcRest*************************/


/*****************************Space*************************/
state_t Space(calc_t *calc_state, double* result)
{

	UNUSED(result);
	
	assert(calc_state);
	assert( calc_state->str ); 
	/*assert(result);*/

	(void)result; /* maybe not neccessery */
	
	while( isspace( *calc_state->str ) )
	{
		++(calc_state->str);
	}
	calc_state->curr_status = SUCCESS;
	/*calc_state->curr_state = WAIT_FOR_NUM;*/
	return calc_state->curr_state; 
	
}

/*****************************InitArrEvent*************************/
status_t InitArrEvent(int *arr_event )
{
	size_t i = 0;
	assert(arr_event);
	
	arr_event[BACK_SLASH_CHAR] = BACK_SLASH; 
	arr_event[SPACE_CHAR] = SPACE;	
	arr_event[OPEN_BRACKET_CHAR] = OPEN_BRACKET;	
	arr_event[CLOSE_BRACKET_CHAR] = CLOSE_BRACKET;
	arr_event[MULT_CHAR] = MULT;
	arr_event[PLUS_CHAR] = PLUS;
	arr_event[MINUS_CHAR] = MINUS;
	arr_event[DIV_CHAR] = DIV;
		
	for( i = 48; i <=57; ++i )
	{
		arr_event[i] = NUMBER_EVENT;
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
	p_calc_state->num_stack = StackCreate( len, sizeof(double) );
	
	if( NULL == p_calc_state->num_stack )
	{
		p_calc_state->curr_status = SYSTEM_ERROR;
		return SYSTEM_ERROR;
	}
	
	p_calc_state->op_stack = StackCreate( len, sizeof(char) );	
	
	if( NULL == p_calc_state->op_stack )
	{
		StackDestroy(p_calc_state->num_stack );
		p_calc_state->num_stack = NULL;
		
		p_calc_state->curr_status = SYSTEM_ERROR;
		return SYSTEM_ERROR;
		
	}
	
	p_calc_state->curr_status = SUCCESS;
	p_calc_state->curr_state = WAIT_FOR_NUM;
	return SUCCESS;
	
}
/**********************InitNumHandlers *******************************/
static void InitNumHandlers(handler_t* num_arr_handlers  )
{
	assert(num_arr_handlers);
	
	num_arr_handlers[ INVALID_INPUT ] = Error;
	/* need to handle if zero arive and in the stack there is DIV*/
	num_arr_handlers[ NUMBER_EVENT ] = PushNum; 
	
	num_arr_handlers[ PLUS ] = Error;
	
	num_arr_handlers[ MINUS ] = PushUnaryMinus;
	
	num_arr_handlers[ DIV ] = Error;
	num_arr_handlers[ MULT ] = Error;
	/*
	num_arr_handlers[ OPEN_BRACKET ] = PushOpenBracket; ((
	*/
	num_arr_handlers[ CLOSE_BRACKET ] = Error; 
	num_arr_handlers[ SPACE ] = Space;
	
	/* check if the current op_stack is close bracket */
	num_arr_handlers[ BACK_SLASH ] = Error; 
	
}


/**********************InitNumHandlers *******************************/
static void InitOpHandlers(handler_t* op_arr_handlers  )
{
	assert(op_arr_handlers);
	
	op_arr_handlers[ INVALID_INPUT ] = Error;
	op_arr_handlers[ NUMBER_EVENT ] = Error;
	
	op_arr_handlers[ PLUS ] = PushPlus;
	op_arr_handlers[ MINUS ] = PushMinus;
	
	op_arr_handlers[ DIV ] = PushDiv;
	op_arr_handlers[ MULT ] = PushMult;
	
	op_arr_handlers[ OPEN_BRACKET ] = Error; 
	/*
	op_arr_handlers[ CLOSE_BRACKET ] = PushClosedBracket;  ))
	*/
	op_arr_handlers[ SPACE ] = Space;
	/*
	op_arr_handlers[ BACK_SLASH ] = BackSlash;  Error; ??  MAYBE NOT NECCESERY AT ALL !NOTE SHURE
	*/
	
}
	
/*int destroy_check = SUCCESS; *//* extern */

/***************End of struct and enum declaration *******/



/***********Static Functions definition*******/


/***********End Of Static Functions definition*******/

status_t Calculate(const char* expression, double* result)
{
	
	/*double num1 = 0.0, num2 = 0.0;*/
	status_t current_status = SUCCESS; 
	event_t num_event = INVALID_INPUT;
	event_t op_event = INVALID_INPUT;
	calc_t calc_state = { 0 };
	calc_t *p_calc_state = &calc_state;
	
	handler_t num_arr_handlers[ 10 ] = { NULL };
	handler_t op_arr_handlers[ 10 ] = { NULL };
	
	InitNumHandlers ( num_arr_handlers );
	InitOpHandlers ( op_arr_handlers );
	
	current_state = WAIT_FOR_NUM;

	InitArrEvent(arr_events);

	current_status = InitStacks((char*)expression, p_calc_state  );
	
	if( SYSTEM_ERROR == current_status )
	{
		return SYSTEM_ERROR;
	}
	 /* && *(p_calc_state->str) != '\0'  */
	while( (ERROR != current_state) && *(p_calc_state->str) != '\0' )
	{
		printf("before switch = %c\n" , *p_calc_state->str );
		printf("curr_state_before switch = %d\n" , current_state );
		switch ( current_state )
		{
			case WAIT_FOR_NUM:
				num_event = arr_events[ *(p_calc_state->str) ];
				
				if(num_arr_handlers[ num_event ] != NULL) /*Not to get segmentation fault */ 
        		{
            		current_state = 
            		num_arr_handlers[ num_event ](p_calc_state, result);
            		/*current_state = p_calc_state->curr_state;*/
            		p_calc_state->curr_state = current_state;
            		current_status = p_calc_state->curr_status;
       			}
       			break;
       			
			case WAIT_FOR_OP:
				 op_event = arr_events[ *(p_calc_state->str) ];
				
				if(op_arr_handlers[ op_event ] != NULL)  /*Not to get segmentation fault*/
				{
            		current_state = 
            		(op_arr_handlers[ op_event ])(p_calc_state, result);
            		 
            		p_calc_state->curr_state = current_state;
            		current_status = p_calc_state->curr_status;
            		
       			}
       			break;
       			/*			
       			else
       			{
       				current_state = ERROR;
       				p_calc_state->curr_state = current_state;
       				p_calc_state->curr_status = SYNTAX_ERROR;
       				current_status = p_calc_state->curr_status;
       				break;
       			}
       			 
				*/
       			
       		case ERROR: 
       			printf(" need to handle error, current_status = %d\n", current_status);
       			
       			current_status = SYNTAX_ERROR;
       			
       			break;			
		}
		
	}
	/* Not possible to finish with that state */
	if ( WAIT_FOR_NUM == current_state && *(p_calc_state->str) == '\0' ) 
	{
		current_status = SYNTAX_ERROR;
		current_state = ERROR;
		p_calc_state->curr_state = current_state;
		*result = 0.0;
	}
	/*if ( ERROR != current_state )*/
	printf("curr_state_after_while = %d\n" , current_state );
	/* !StackIsEmpty(p_calc_state->op_stack) && */
	if( (ERROR != current_state) ) 
	{
		current_status = CalcRest( p_calc_state, result);
	}
	
	
	
	StackDestroy(p_calc_state->num_stack );
	StackDestroy(p_calc_state->op_stack );
	
	return current_status;

}


