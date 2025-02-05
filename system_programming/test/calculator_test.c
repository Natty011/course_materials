/***************************************
* Author : Natty
* Reviewer : Matan
* Date : 22 / 01 / 2025
* Last update: 02 / 02 / 2025
*****************************************/

#include <stdio.h> 		/* printf, puts, qsort  */
#include <assert.h>
#include <string.h> 	/* strcpy, strcmp */
#include "calculator.h" 
#include "stack.h" 


#define BLACK        "\x1b[30m"
#define RED          "\x1b[31m"
#define GREEN        "\x1b[32m"
#define YELLOW       "\x1b[33m"
#define BLUE         "\x1b[34m"
#define MAGENTA      "\x1b[35m"
#define CYAN         "\x1b[36m"
#define WHITE        "\x1b[37m"

#define RESET        "\x1b[0m"

/* BACKGROUND COLOR */
#define BACK_BLACK   "\x1b[40m"
#define BACK_RED     "\x1b[41m"
#define BACK_GREEN   "\x1b[42m"
#define BACK_YELLOW  "\x1b[43m"
#define BACK_BLUE  	 "\x1b[44m"
#define BACK_MAGENTA "\x1b[45m"
#define BACK_CYAN 	 "\x1b[46m"
#define BACK_WHITE   "\x1b[47m"


#define DEBUG		"DEBUG MODE"
#define RELEASE		"RELEASE MODE"

#define MIN(a, b)		((a > b ) ? b : a )
#define MAX(a, b)		((a > b ) ? a : b )

extern int destroy_check;
/***************struct and enum declaration *******/

/** possible return values **/
/*
typedef enum
{
	
	SUCCESS = 0,
	OPERATION_FAIL = 1
	
}bst_result_t;
*/

typedef enum
{
	
	FALSE = 0,
	TRUE = 1
	
}func_result_t;

/*
typedef enum
{
    SUCCESS = 0,
    MATH_ERROR = 1,
    SYNTAX_ERROR = 2,
    SYSTEM_ERROR = 3
} status_t;
*/
/*
	#ifdef PRINTS
		Aux_Pre_Print_Tree(bst1, 0);
	#endif
*/
/***************End of struct and enum declaration *******/

/***************************function declaration**************************/
static void TestBstOneNode(void);
/*
static int SortingFunc(void* check_data , void* new_data);
*/
/***************************End of function declaration******************/

/******************static functions definition**********************/
		
/*******************SortingFunc*********************/
/*
static int SortingFunc(void* check_data , void* new_data)
{
	return (*(int*)check_data - *(int*)new_data);
}
*/
/*******************Compare*********************/
/*
static int Compare(void* check_data , void* new_data)
{
	return !(SUCCESS == (*(int*)check_data - *(int*)new_data));
}
*/
/******************End of static functions definition**********************/


int main ()
{

	char* mode = RELEASE;
	char* background =  BACK_MAGENTA;	
	
	#ifndef NDEBUG
		mode = DEBUG;
		background =  BACK_YELLOW;
	#endif

	puts(BLUE"====================================================="RESET);
	printf("%sTEST: %s "RESET" \n", background,  mode);
   	puts(BACK_BLUE"'TestBstOneNode()'"RESET);
    TestBstOneNode();
    
	puts(BLUE"====================================================="RESET);

	return 0;
}

/* 
TESTS TYPES:                  				Pass/Fail     curr_state
Add ints: " 3.5+2.3";							P			NUM+OP
Add doubles: " 3.5+2.3"; 						P			NUM+OP
space first(num): " 3.5+2.3";					P			NUM
space end (num): 	"3.5+2.3 ";		    		P		    NUM
space first & end (num): "       3.5+2.3    ";	P		    NUM
space first (op): " 3.5 +2.3";					P			OP
space end (num): " 3.5+ 2.3";					P			NUM
space first & end (num): "  3.5  + 2.3  "	    P		    NUM+OP
Sub ints: "3-2";							    P 			OP
Sub ints with first negative: "-3-2";           P 			NUM+OP
Sub/Add: "-1- 3  -  2  + 3 -  5  -10   ";       P 			NUM+OP

*/
/********************  TestBstOneNode  ****************************/
static void TestBstOneNode(void)
{	
	
	int flag = FALSE;
	status_t result_status = -1;
	char* exp1 = "-1- 3  -  2  + 3 -  5  -10   ";
	double res = 0.0;
	double* result = NULL;
	
	result = &res;
	
	/*puts(RED);*/
	
	result_status = Calculate(exp1, result);
	printf(" result_status_exp1 = %d \n", result_status);
	printf(" result_exp1 = %f \n", *result);
	if( !flag ) /*!flag*/
	{
		puts(RESET);		
		puts(BACK_BLUE"Test: Success"RESET);

	}
	
	else
	{
		puts(BACK_YELLOW"Test: Failure"RESET);	
	}
	
}

/*
	if( OPERATION_FAIL == destroy_check )
	{
		puts("Failes in_1: Destroy");
		flag =  TRUE;
	}
*/


