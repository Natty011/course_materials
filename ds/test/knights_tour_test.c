/***************************************
* Author : Natty
* Reviewer : Rawan
* Date : 26 / 02 / 2025
* Last update: 26 / 02 / 2025
*****************************************/

#include <stdio.h> 		/* printf, puts, qsort  */
#include <assert.h>
#include <string.h> 	/* strcpy, strcmp */
#include <stdlib.h> 	/* calloc, free */

#include "knights_tour.h" 
#include "bit_array.h" 

#ifdef PRINTS

#endif

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
#define STEP_LANGTH 	64

#define MIN(a, b)		((a > b ) ? b : a )
#define MAX(a, b)		((a > b ) ? a : b )
#define UNUSED( var )       ( (void)var )
/***************struct and enum declaration *******/


typedef enum
{
	
	SUCCESS = 0,
	FAIL = 1
	
}knights_result_t;

typedef enum
{
	
	FALSE = 0,
	TRUE = 1
	
}func_result_t;


/*
	#ifdef PRINTS
		Aux_Pre_Print_Tree(avl1, 0);
	#endif
*/
/***************End of struct and enum declaration *******/

/***************************function declaration**************************/
static void TestKnightsTour(void);

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
   	puts(BACK_BLUE"'TestKnightsTour()'"RESET);
	TestKnightsTour();

	puts(BLUE"====================================================="RESET);

	return 0;
}

/************************************************************/
/********************  TestKnightsTour  *********************/
/************************************************************/
static void TestKnightsTour(void)
{	
	int flag = FALSE;
	position_t *ret_path = NULL;
	uint8_t x_begin = 0, y_begin = 0;
	ret_path = (position_t*)calloc(STEP_LANGTH, sizeof(position_t) );

	if (NULL == ret_path )
	 {
		printf("line: %d \n" , __LINE__ );	
		printf("Memory allocation failed!\n");
		flag =  TRUE;
		return;
	 }
	
	 /*KnightsTour(x_begin, y_begin, ret_path);*/
	
	

	free( ret_path );
	ret_path = NULL;
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

/*
		printf("line: %d \n" , __LINE__ );
		puts("Failes in_1: IsEmpty || Size ");
		flag =  TRUE;
	
	*/