/***************************************
* Author : Natty
* Reviewer : Michael
* Date : 03 / 03 / 2025
* Last update: 08 / 02 / 2025
*****************************************/

#include <stdio.h> 		/* printf, puts  */
#include <assert.h>
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


/***************struct and enum declaration *******/

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

/***************End of struct and enum declaration *******/

/***************************function declaration**************************/
static void TestCalculator(void);
/***************************End of function declaration******************/

/******************static functions definition**********************/
		
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
   	puts(BACK_BLUE"'TestCalculator()'"RESET);
    TestCalculator();
    
	puts(BLUE"====================================================="RESET);

	return 0;
}

/* 
TESTS TYPES:                  				Pass/Fail     curr_state
Add ints: "3+2";							P			NUM+OP
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
2 Mimus in a row: "--1--10   "; / "-1--10   ";  P 			NUM+OP
3 Mimus in a row_1: "---1   ";   			    P 		    NUM+OP
3 Mimus in a row_2: "---1---4   ";   			P 		 NUM+OP
Insert one positive number:  "0.5  "            P			NUM
Syntax Error_1: "-1 -  ";                       P			NUM
Plus & Minus & Mult & Div: "2*3*2-2/2+2-2/2";   P        NUM+OP
Math Error_1: "2*3*2-2/2+2-2/2/0";              P         NUM+OP
Math Error_2: "1/0.0000;                        P         NUM+OP
Math Error_3: "1/    0;                         P         NUM+OP
Brackets_1 : "((-(2-(1+2)*2)-2))";              P         NUM+OP
Brackets_2 : "((-(2-(1+2)*2)-8/4))";            P         NUM+OP  
Syntax Error_2: "(2))";                         P		 NUM+OP 
Syntax Error_3: "((2)";                         P		 NUM+OP
Syntax Error_4: "((((-(2-(1+2)*2)-2))";         P         NUM+OP 

*/

/********************  TestBstOneNode  ****************************/
static void TestCalculator(void)
{	

	/*
	status_t result_status = -1;
	char* exp1 = "3+2"; */ 
	
	int flag = FALSE;
	double res = 0.0;
	double* result = NULL;
	
	result = &res;
	/*
	result_status = Calculate(exp1, result);
	printf(" result_status_exp1 = %d \n", result_status);
	printf(" result_exp1 = %f \n", *result);
	*/	
	puts(RED);
	
	if ( SUCCESS != Calculate("3+2", result) ||
		 5.0 !=  *result )
	{
		puts("Failes in Add ints: 3+2 ");
		flag = TRUE;
	
	}
		
	if ( SUCCESS != Calculate("3.5+2.3", result) ||
		 5.8 !=  *result )
	{
		puts("Failes in Add doubles: 3.5+2.3");
		flag = TRUE;
	
	}

	if ( SUCCESS != Calculate(" 3.5+2.3", result) ||
		 5.8 !=  *result )
	{
		puts("Failes in space(Num State): 3.5+2.3");
		flag = TRUE;
	
	}
	
	if ( SUCCESS != Calculate(" 3.5 + 2.3 ", result) ||
		 5.8 !=  *result )
	{
		puts("Failes in space(NUM+OP State): 3.5 + 2.3 ");
		flag = TRUE;
	
	}
	
	
	if ( SUCCESS != Calculate("3-2", result) ||
		 1.0 !=  *result )
	{
		puts("Failes in Sub ints: 3-2 ");
		flag = TRUE;
	
	}
	
	if ( SUCCESS != Calculate("-3-2", result) ||
		 -5.0 !=  *result )
	{
		puts("Failes in Sub ints(first negative): -3-2 ");
		flag = TRUE;
	
	}
	
	if ( SUCCESS != Calculate(" -1- 3  - 2 + 3 - 5 -10 ", result) ||
		 -18.0 !=  *result )
	{
		puts("Failes in Sub+Add: - 1- 3  - 2 + 3 - 5 -10 ");
		flag = TRUE;
	
	}
	
	if ( SUCCESS != Calculate("--1--10", result) ||
		 11.0 !=  *result )
	{
		puts("Failes in 2 Mimus in a row_1: --1--10");
		flag = TRUE;
	
	}
	
	if ( SUCCESS != Calculate("-1--10", result) ||
		 9.0 !=  *result )
	{
		puts("Failes in 2 Mimus in a row_2: -1--10");
		flag = TRUE;
	
	}
		
	if ( SUCCESS != Calculate("---1", result) ||
		 -1.0 !=  *result )
	{
		puts("Failes in 3 Mimus in a row_1: ---1");
		flag = TRUE;
	
	}
	
	if ( SUCCESS != Calculate("---1---4", result) ||
		 -5.0 !=  *result )
	{
		puts("Failes in 3 Mimus in a row_2:---1---4");
		flag = TRUE;
	
	}
	
	if ( SUCCESS != Calculate("0.5 ", result) ||
		 0.5 !=  *result )
	{
		puts("Failes in one positive number: 0.5");
		flag = TRUE;
	
	}

	if ( SYNTAX_ERROR != Calculate("-1 -  ", result) ||
		 0.0 !=  *result )
	{
		puts("Failes in Syntax Error_1: -1 -  ");
		flag = TRUE;
	
	}
	
	if ( SUCCESS != Calculate("2*3*2-2/2+2-2/2", result) ||
		 12.0 !=  *result )
	{
		puts("Failes in Plus & Minus & Mult & Div :2*3*2-2/2+2-2/2");
		flag = TRUE;
	
	}
	
	if ( MATH_ERROR != Calculate("2*3*2-2/2+2-2/2/0", result) ||
		 0.0 !=  *result )
	{
		puts("Failes in Math Error_1 : 2*3*2-2/2+2-2/2/0");
		flag = TRUE;
	
	}
	
	if ( MATH_ERROR != Calculate("1/0.0000", result) ||
		 0.0 !=  *result )
	{
		puts("Failes in Math Error_2 : 1/0.0000");
		flag = TRUE;
	
	}
	
	if ( MATH_ERROR != Calculate("1/     0", result) ||
		 0.0 !=  *result )
	{
		puts("Failes in Math Error_3 : 1/    0");
		flag = TRUE;
	
	}
	
	if ( SYNTAX_ERROR != Calculate("1/01", result) ||
		 0.0 !=  *result )
	{
		puts("Failes in Math Error_4 : 1/01");
		flag = TRUE;
	
	}
	
	if ( (SYNTAX_ERROR != Calculate("0.0.0", result) || 0.0 !=  *result) && 
		 (SYNTAX_ERROR != Calculate("0..5", result) || 0.0 !=  *result)  &&
		 (SYNTAX_ERROR != Calculate("05", result) || 0.0 !=  *result ) &&
		 (SYNTAX_ERROR != Calculate("1+0110", result) || 0.0 !=  *result ) )
	{
		puts("Failes in Syntax Error_2: 0.0.0 || 0..5 || 05 || 1+0110");
		flag = TRUE;
	
	}
	
	if ( (SYNTAX_ERROR != Calculate("1+2  -", result) || 0.0 !=  *result) && 
		 (SYNTAX_ERROR != Calculate("-  ", result) || 0.0 !=  *result)  &&
		 (SYNTAX_ERROR != Calculate("+1-1", result) || 0.0 !=  *result ) )
	{
		puts("Failes in Syntax Error_3: 1+2  - || - || +1-1 ");
		flag = TRUE;
	
	}
	
	if ( SUCCESS != Calculate("0.00 ", result) ||
		 0.0 !=  *result )
	{
		puts("Failes in ZERO number: 0.00");
		flag = TRUE;
	
	}
	
	if ( SUCCESS != Calculate("1/0.00000005", result) ||
		 20000000.0 !=  *result )
	{
		puts("Failes in small denominator number : 1/0.00000005");
		flag = TRUE;
	
	}
	
	if ( SUCCESS != Calculate("0.00000005/1", result) ||
		 0.00000005 !=  *result )
	{
		puts("Failes in small numerator number : 0.00000005/1");
		flag = TRUE;
	
	}
	
	if ( SUCCESS != Calculate("((-(2-(1+2)*2)-2))", result) ||
		 2.0 !=  *result )
	{
		puts("Failes in Brackets_1:   ((-(2-(1+2)*2)-2)) ");
		flag = TRUE;
	
	}
	
	if ( SUCCESS != Calculate("((-(2-(1+2)*2)-8/4))", result) ||
		 2.0 !=  *result )
	{
		puts("Failes in Brackets_2:   ((-(2-(1+2)*2)-8/4)) ");
		flag = TRUE;
	
	}
	
	
	if ( SYNTAX_ERROR != Calculate(" (2) ) ", result) ||
		 0.0 !=  *result )
	{
		puts("Failes in Syntax Error_4(Brackets unbalanced): (2) ) ");
		flag = TRUE;
	
	}
	
	if ( SYNTAX_ERROR != Calculate("((2)", result) ||
		 0.0 !=  *result )
	{
		puts("Failes in Syntax Error_5(Brackets unbalanced): ((2)");
		flag = TRUE;
	
	}
	
	if ( SYNTAX_ERROR != Calculate("(((-(2-(1+2)*2)-2))", result) ||
		 0.0 !=  *result )
	{
		puts("Failes in Syntax Error_6(Brackets unbalanced):(((-(2-(1+2)*2)-2))");
		flag = TRUE;
	
	}
	
	if ( (SYNTAX_ERROR != Calculate("1/0.5^", result) || 0.0 !=  *result) && 
		 (SYNTAX_ERROR != Calculate("10%/ 1%", result) || 0.0 !=  *result)  &&
		 (MATH_ERROR != Calculate("10/0 .5", result) || 0.0 !=  *result ) &&
		 (SYNTAX_ERROR != Calculate("-@10/1", result) || 0.0 !=  *result ) )
	{
		puts("Failes in Syntax Error_2: 1/0.5^ || 10%/ 1% || 10/0 .5 || -@10/1");
		flag = TRUE;
	
	}
	
	if ( SUCCESS != Calculate("3+2", result) ||
		 5.0 !=  *result )
	{
		puts("Failes in Add ints_global_initilized:   3+2 ");
		flag = TRUE;
	
	}
	
	if( !flag ) 
	{
		puts(RESET);		
		puts(BACK_BLUE"Test: Success"RESET);

	}
	
	else
	{
		puts(BACK_YELLOW"Test: Failure"RESET);	
	}
	
}




