/***************************************
* Author : Natty
* Reviewer : Michael
* Date : 03 / 03 / 2025
* Last update: 08 / 02 / 2025
*****************************************/
#include <string.h> 	/* strlen */
#include <ctype.h> 		/* isspace */ 
#include <assert.h> 	/* assert */
#include <stdlib.h> 	/* malloc, free, strtod */

#include "stack.h" 
#include "calculator.h" 

#define UNUSED( var )       ( (void)var )
#define ASCI_LEN			256
/****************struct and enum declaration*********************/

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
	BACK_SLASH = 9, /* '\0' */
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
	BACK_SLASH_CHAR = '\0' /* 0 */

}character_t;

typedef enum 
{
	WAIT_FOR_NUM = 0,
	WAIT_FOR_OP = 1,
	ERROR = 2

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

/***************End of struct and enum declaration *******/

/***********Functions declaration*******/

static void InitNumHandlers(handler_t* num_arr_handlers  );
static void InitOpHandlers(handler_t* op_arr_handlers  );
static void HandlePrecedence( calc_t *calc_state );
static void	DestroyStacks( calc_t *p_calc_state );
static int IsDigit( char ch );
static double CalcTwoNums(double num_left, double num_right, char op);


static status_t IntermediateResult(calc_t *calc_state, double* result);
static status_t InitArrEvent(int *arr_event);
static status_t InitStacks(const char* expression, calc_t *p_calc_state);
static status_t CheckNumOfBrackets( calc_t *calc_state, double* result);
static status_t CheckResInBracket( calc_t *calc_state, double* result);
static status_t CheckNextZero( calc_t *calc_state, double* result);
static status_t IsZeroAfterDiv( calc_t *calc_state, double* result, double num);
static status_t	InitArrays(handler_t* num_arr_handlers, handler_t* op_arr_handlers
				,int* arr_events, calc_t *p_calc_state, const char* expression );

static state_t Space(calc_t* calc_state, double* result);
static state_t PushNum(calc_t *calc_state, double* result);
static state_t PushPlus(calc_t *calc_state, double* result);
static state_t PushMinus(calc_t *calc_state, double* result);
static state_t PushUnaryMinus(calc_t *calc_state, double* result);
static state_t PushDiv(calc_t *calc_state, double* result);
static state_t PushMult(calc_t *calc_state, double* result);
static state_t PushOpenBracket(calc_t *calc_state, double* result);
static state_t ClosedBracket(calc_t *calc_state, double* result);
static state_t Error(calc_t *calc_state, double* result);

/**********End of functions declaration *******/

/*********************Globals****************************/

static state_t current_state = WAIT_FOR_NUM;
static int num_of_brackets = 0;
int arr_events[ASCI_LEN] = { 0 };

handler_t num_arr_handlers[ NUM_OF_EVENTS ] = { NULL };
handler_t op_arr_handlers[ NUM_OF_EVENTS ] = { NULL };
static status_t current_status = SUCCESS; 
static event_t num_event = INVALID_INPUT;
static event_t op_event = INVALID_INPUT;

/**************End Of Globals****************************/

/**************Calculate****************************/

status_t Calculate(const char* expression, double* result)
{
	calc_t calc_state = { 0 };
	calc_t *p_calc_state = &calc_state;

	assert(expression);
	assert(result);

	current_status = InitArrays(num_arr_handlers, op_arr_handlers, arr_events,
	 							p_calc_state, expression);
	 											
	current_state = WAIT_FOR_NUM;

	if( SYSTEM_ERROR == current_status )
	{
		return SYSTEM_ERROR;
	}
	while( (ERROR != current_state) &&
			( BACK_SLASH_CHAR !=  *(p_calc_state->str) ) )
	{
		switch ( current_state )
		{
			case WAIT_FOR_NUM:
				num_event = arr_events[ (size_t)*(p_calc_state->str) ];
				
				/*Not to get segmentation fault */ 
				if(NULL != num_arr_handlers[ num_event ] ) 
        		{
            		current_state = 
            			num_arr_handlers[ num_event ](p_calc_state, result);
            		p_calc_state->curr_state = current_state;
            		current_status = p_calc_state->curr_status;
       			}
       			
       			break;
       			
			case WAIT_FOR_OP:
				 op_event = arr_events[ (size_t)(*(p_calc_state->str)) ];
				
				if(NULL != op_arr_handlers[ op_event ] )  
				{
            		current_state = 
            			op_arr_handlers[ op_event ](p_calc_state, result);
            		p_calc_state->curr_state = current_state;
            		current_status = p_calc_state->curr_status;	
       			}
       			
       			break;
       			
       		default:
       			break;	
		}
	}

	/* Not possible to finish with that state */
	if ( WAIT_FOR_NUM == current_state && 
		BACK_SLASH_CHAR == *(p_calc_state->str)) 
	{
		current_status = SYNTAX_ERROR;
		current_state = ERROR;
		p_calc_state->curr_state = current_state;
		*result = 0.0;
	}
	
	if( (ERROR != current_state) ) 
	{
		current_status = IntermediateResult( p_calc_state, result);
	}
	
	/* CHECK IF #BRACKETS ARE BALANCES*/
	if ( 0 !=  num_of_brackets ) 
	{
		current_status = SYNTAX_ERROR;
		current_state = ERROR;
		p_calc_state->curr_state = current_state;
		*result = 0.0;
		
		/* Must be initilized again because it is a global */
		num_of_brackets = 0; 
	}

	DestroyStacks( p_calc_state );

	return current_status;
}



/***********Static Functions definition*******/

/**************CalcTwoNums****************************/
static double CalcTwoNums(double num_left, double num_right, char op)
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
	op_arr_handlers[ CLOSE_BRACKET ] = ClosedBracket; 
	op_arr_handlers[ SPACE ] = Space;

}
		
/**********************InitNumHandlers *******************************/
static void InitNumHandlers(handler_t* num_arr_handlers  )
{
	assert(num_arr_handlers);
	
	num_arr_handlers[ INVALID_INPUT ] = Error;
	num_arr_handlers[ NUMBER_EVENT ] = PushNum; 
	num_arr_handlers[ PLUS ] = Error;
	num_arr_handlers[ MINUS ] = PushUnaryMinus;
	num_arr_handlers[ DIV ] = Error;
	num_arr_handlers[ MULT ] = Error;
	num_arr_handlers[ OPEN_BRACKET ] = PushOpenBracket; 
	num_arr_handlers[ CLOSE_BRACKET ] = Error; 
	num_arr_handlers[ SPACE ] = Space;
		
}
/**********************HandlePrecedence *******************************/
static void HandlePrecedence( calc_t *calc_state )
{
	char op = MULT_CHAR;
	double num =*(double*)StackPeek(calc_state->num_stack);
		
	assert(calc_state); 
		
	if( !StackIsEmpty( calc_state->op_stack ) 
		&& DIV_CHAR == *(char*)StackPeek(calc_state->op_stack)   )
	{
		num = 1.0 / num;
		StackPop( calc_state->op_stack );
		StackPush(calc_state->op_stack, &op );
		StackPop( calc_state->num_stack );
		StackPush(calc_state->num_stack, &num );
	}
		
}

/**********************DestroyStacks *******************************/
static void	DestroyStacks( calc_t *p_calc_state )
{
	StackDestroy(p_calc_state->num_stack );
	p_calc_state->num_stack = NULL;
	StackDestroy(p_calc_state->op_stack );
	p_calc_state->op_stack = NULL;

}

/***********Status Functions definition*******/


/**********************CheckNumOfBrackets *******************************/
static status_t CheckNumOfBrackets( calc_t *calc_state, double* result)
{
	if ( 1 > num_of_brackets  )
	{
		calc_state->curr_status = SYNTAX_ERROR;
		calc_state->curr_state = ERROR;
		*result = 0.0;
		
		return SYNTAX_ERROR;
	}
	
	return SUCCESS;
}

/**********************CheckResInBracket *******************************/
static status_t CheckResInBracket( calc_t *calc_state, double* result)
{
	 /* CHECK IF THE RESULT INDISE THE BRACKET IS ZERO*/
	if( !(*result) && !StackIsEmpty( calc_state->op_stack ) 
		&& DIV_CHAR == *(char*)StackPeek(calc_state->op_stack)   )
	{
	    calc_state->curr_status = MATH_ERROR;
		calc_state->curr_state = ERROR;
		*result = 0.0;
		
		return MATH_ERROR;	
	}
	
	return SUCCESS;	
}
/**********************CheckNextZero *******************************/
static status_t CheckNextZero( calc_t *calc_state, double* result)
{
	 /* CHECK THE NEXT CHAR AFTER ZERO  */
	 
	if( ZERO_CHAR == *(calc_state->str) && IsDigit( *((calc_state->str) + 1)) )
	{
	    calc_state->curr_status = SYNTAX_ERROR;
		calc_state->curr_state = ERROR;
		*result = 0.0;
		return SYNTAX_ERROR;	
	}
	
	return SUCCESS;
}	
/**********************IsZeroAfterDiv *******************************/
static status_t IsZeroAfterDiv( calc_t *calc_state, double* result, double num)
{
	 /* Not to divide by zero */ 
	 if( !num && !StackIsEmpty( calc_state->op_stack ) 
		&& DIV_CHAR == *(char*)StackPeek(calc_state->op_stack)   )
	{
	    calc_state->curr_status = MATH_ERROR;
		calc_state->curr_state = ERROR;
		*result = 0.0;
		return MATH_ERROR;	
	
	}
	return SUCCESS;
}

/**********************InitArrays *******************************/
static status_t	InitArrays(handler_t* num_arr_handlers, handler_t* op_arr_handlers
				,int* arr_events, calc_t *p_calc_state, const char* expression )
{
	assert(num_arr_handlers);
	assert(op_arr_handlers);
	assert(arr_events);
	assert(p_calc_state);
	assert(expression);
	
	InitNumHandlers ( num_arr_handlers );
	InitOpHandlers ( op_arr_handlers );
	InitArrEvent(arr_events);
	
	return InitStacks((char*)expression, p_calc_state  );
	
}
	


/*****************************InitArrEvent*************************/
static status_t InitArrEvent(int *arr_event )
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
		
	for( i = '0'; i <='9'; ++i )
	{
		arr_event[i] = NUMBER_EVENT;
	}

	return SUCCESS;
}
/**********************InitStacks *******************************/
static status_t InitStacks(const char* expression, calc_t *p_calc_state)
{
	size_t len = 0;

	assert(p_calc_state);
	assert(expression);
	
	len = strlen(expression);
	p_calc_state->str = (char*)expression;

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

/**************IntermediateResult****************************/
static status_t IntermediateResult(calc_t *calc_state, double* result)
{
	
	double res = 0.0, num_right = 0.0, num_left = 0.0;
	char operator = DIV_CHAR;
	
	assert(calc_state);
	assert(result);
	
	/* if the user insert only one positive number */
	if ( ! StackIsEmpty(calc_state->num_stack) )
	{
		*result = *(double*)StackPeek(calc_state->num_stack);
	}	

	while(  !StackIsEmpty(calc_state->op_stack) && 
			
	         OPEN_BRACKET_CHAR != *(char*)StackPeek(calc_state->op_stack) ) 
	{
	
		operator = *(char*)StackPeek(calc_state->op_stack);
		StackPop( calc_state->op_stack );
		
		num_right  = *(double*)StackPeek(calc_state->num_stack);
		StackPop(calc_state->num_stack);
		num_left = *(double*)StackPeek(calc_state->num_stack);
		StackPop(calc_state->num_stack);
		
		res = CalcTwoNums(num_left, num_right, operator );
		
		*result = res; 
		
		StackPush( calc_state->num_stack , result );
		
		res = 0.0, num_right = 0.0, num_left = 0.0;	
	}
	return SUCCESS;
	
}

/***********End Of Status Functions definition*******/

/***********State Functions definition*******/
	
/*****************************Space*************************/
static state_t Space(calc_t *calc_state, double* result)
{
	UNUSED(result);
	
	assert(calc_state);
	assert( calc_state->str ); 
	assert(result);

	(void)result; /* maybe not neccessery */
	
	while( isspace( *calc_state->str ) )
	{
		++(calc_state->str);
	}
	calc_state->curr_status = SUCCESS;

	return calc_state->curr_state; 
	
}

/**************PushNum****************************/
static state_t PushNum(calc_t *calc_state, double* result)
{

	static status_t status = SYNTAX_ERROR;
	double num = 1.0;
	
	assert(calc_state);
	assert(result);

	status = CheckNextZero( calc_state, result );
	
	if ( SYNTAX_ERROR == status )
	{
		return ERROR;
	}

	num = strtod( calc_state->str, &calc_state->str );

	status = IsZeroAfterDiv( calc_state, result, num );
	
	if ( MATH_ERROR == status )
	{
		return ERROR;
	}
				
	StackPush( calc_state->num_stack, &num );

	return WAIT_FOR_OP;
}


/**************PushPlus****************************/
static state_t PushPlus(calc_t *calc_state, double* result)
{
	
	assert(calc_state);
	assert(result);
	
	calc_state->curr_status = IntermediateResult(calc_state, result);

	StackPush(calc_state->op_stack, calc_state->str );

	++(calc_state->str);
	
	return WAIT_FOR_NUM;
}

/**************PushMinus****************************/
static state_t PushMinus(calc_t *calc_state, double* result)
{
	
	assert(calc_state);
	assert(result);
	
	calc_state->curr_status = IntermediateResult(calc_state, result);

	StackPush(calc_state->op_stack, calc_state->str );
	++(calc_state->str);
	
	return WAIT_FOR_NUM;
}


/**************PushUnaryMinus****************************/
static state_t PushUnaryMinus(calc_t *calc_state, double* result)
{
	
	char op = MULT_CHAR;
	double num = -1.0;
	
	assert(calc_state);
	assert(result);
	UNUSED(result);
	
	StackPush(calc_state->op_stack, &op );
	StackPush( calc_state->num_stack, &num );
	++(calc_state->str);
	
	return WAIT_FOR_NUM;
}


/**************PushOpenBracket****************************/
static state_t PushOpenBracket(calc_t *calc_state, double* result)
{
	
	assert(calc_state);
	assert(result);
	UNUSED(result);
	
	StackPush(calc_state->op_stack ,calc_state->str );
	++(calc_state->str);
	
	++num_of_brackets;
	
	return WAIT_FOR_NUM;
	
}

/**************ClosedBracket****************************/
static state_t ClosedBracket(calc_t *calc_state, double* result)
{
	
	static status_t status = SYNTAX_ERROR;
	assert(calc_state);
	assert(result);

	status = CheckNumOfBrackets(calc_state , result);
	
	if ( SYNTAX_ERROR == status )
	{
		return ERROR;
	}
	
	calc_state->curr_status = IntermediateResult(calc_state, result);
	
	++(calc_state->str);
	--num_of_brackets;
	
	StackPop( calc_state->op_stack );

	status = CheckResInBracket(calc_state , result);
	
	if ( MATH_ERROR == status )
	{
		return ERROR;
	}
	
	return WAIT_FOR_OP;
}

/**************PushDiv****************************/
static state_t PushDiv(calc_t *calc_state, double* result)
{
	
	assert(calc_state);
	assert(result);
	UNUSED(result);
	
	HandlePrecedence( calc_state );
	
	StackPush(calc_state->op_stack, calc_state->str );
	++(calc_state->str);
	
	return WAIT_FOR_NUM;
	
}

/**************PushMult****************************/
static state_t PushMult(calc_t *calc_state, double* result)
{
	assert(calc_state);
	assert(result);
	UNUSED(result);
	
	HandlePrecedence( calc_state );
	StackPush(calc_state->op_stack, calc_state->str );
	++(calc_state->str);
	
	return WAIT_FOR_NUM;
	
}		
/**************Error****************************/
static state_t Error(calc_t *calc_state, double* result)
{
	assert(calc_state);
	assert(result);
	UNUSED( result );
									 
	calc_state->curr_status = SYNTAX_ERROR;
	calc_state->curr_state = ERROR;
	*result = 0.0;
	
	return ERROR;
}

/***********End Of State Functions definition*******/

/***********End Of Static Functions definition*******/



