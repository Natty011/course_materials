/***************************************
* Author : Natty
* Reviewer : ???
* Date : 05 / 03 / 2025
* Last update: 09 / 03 / 2025
*****************************************/

#include <stdio.h> 		/* printf, puts  */


#include <assert.h>
#include <string.h> 	/* strcpy, strcmp */
#include <stdlib.h> 	/* calloc, free */
#include <time.h> 		/* clock */
#include <stdint.h> 	/* uint8_t*/

#include "simple_shell.h" 

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
#define UNUSED( var )       ( (void)var )


#define BUFFER_SIZE			( 501 )
#define MAX_WORDS			( 20 )

/***************struct and enum declaration *******/


typedef enum
{
	DOUBLE_FREE_FAIL = -1,
	SUCCESS = 0,
	FAIL = 1,
	REQUEST_NOT_MET = 2
	
}dhcp_result_t;

typedef enum
{
	
	FALSE = 0,
	TRUE = 1
	
}func_result_t;


/***************End of struct and enum declaration *******/

/***************************function declaration**************************/
static void TestDhcp(void);

#ifdef PRINTS

#endif
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
   	puts(BACK_BLUE"'TestDhcp()'"RESET);
	TestDhcp();
	

	puts(BLUE"====================================================="RESET);
	printf("%sTEST: %s "RESET" \n", background,  mode);
   	puts(BACK_BLUE"'TestDhcp2()'"RESET);
	TestDhcp2();

	puts(BLUE"====================================================="RESET);
	printf("%sTEST: %s "RESET" \n", background,  mode);
   	puts(BACK_BLUE"'TestDHCPAllAddresses()'"RESET);
	TestDHCPAllAddresses();

	puts(BLUE"====================================================="RESET);


	return 0;
}

/************************************************************/
/************************  TestDhcp  ************************/
/************************************************************/
static void TestDhcp(void)
{	

	int status_result = FALSE; 
	
	if( !status_result  )
	{
		puts(RESET);		
		puts(BACK_BLUE"Test: Success"RESET);

	}

	else
	{
		puts(BACK_RED"Test: Failure"RESET);	
	}

}

