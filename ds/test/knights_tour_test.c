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
#include <time.h> /* clock */
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
#define BOARD_SIZE 		8
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
	position_t ret_path[STEP_LANGTH] = { 0 };
    uint8_t x = 0, y = 0;

	uint8_t x_begin = 4, y_begin = 5;
	int result = FALSE; 
	clock_t start_time_knight = clock();
	float t_knight = 0.0;
	uint8_t not_solvable_count = 0;

	srand((unsigned int)time(NULL));
    x_begin = (uint8_t)(rand() % BOARD_SIZE);
    y_begin = (uint8_t)(rand() % BOARD_SIZE);
	
    printf("Starting Knight's Tour at (%d, %d)\n", x_begin, y_begin);
    
    start_time_knight = clock();
	
	result = KnightsTour(x_begin, y_begin, ret_path);
	 start_time_knight = clock() - start_time_knight;

	 t_knight = (float)start_time_knight / CLOCKS_PER_SEC;

	 printf("KnightsTour : "BACK_GREEN" %f "RESET" seconds  \n", t_knight);

	
    printf("Checking solvability for all positions...\n");

    for (x = 0; x < BOARD_SIZE; x++) {
        for (y = 0; y < BOARD_SIZE; y++) {
            if (KnightsTour(x, y, ret_path) != 0) {
                printf("No solution starting at (%d, %d)\n", x, y);
                not_solvable_count++;
            }
        }
    }

    if (not_solvable_count == 0) {
        printf("All positions are solvable.\n");
    } else {
        printf("%d positions are not solvable.\n", not_solvable_count);
    }
	
	

	if( !result && !not_solvable_count )
	{
		puts(RESET);		
		puts(BACK_BLUE"Test: Success"RESET);

	}

	else
	{
		puts(BACK_YELLOW"Test: Failure"RESET);	
	}

}
