/***************************************
* Author : Natty
* Reviewer : ???
* Date : 23 / 03 / 2025
* Last update: 23 / 03 / 2025
*****************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "tqueue.h"
#include "utils.h"		 /* ExitIfBad, msg */


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

#define UNUSED( var )       ( (void)var )


/***************struct and enum declaration *******/



/***************End of struct and enum declaration *******/

/***************************function declaration**************************/
static void TestTqueue(void);

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
   	puts(BACK_BLUE"'TestTqueue()'"RESET);
	TestTqueue();
	
	puts(BLUE"====================================================="RESET);


	return 0;
}



enum 
{
    QUEUE_SIZE = 10,
	NUM_ITEMS = 3,
    NUM_PRODUCERS = 3,
    NUM_CONSUMERS = 3
};

/************************************************************/
/************************  TestTqueue  ************************/
/************************************************************/


static void TestTqueue(void)
{
   
	int status_result = FALSE;
	tq_t *fsq1 = NULL;

	fsq1 = TQCreate(QUEUE_SIZE);
  
	ExitIfBad(NULL == fsq1, "TQCreate failed\n");

	if( !status_result  )
	{
		puts(RESET);		
		puts(BACK_BLUE"Test: Success"RESET);

	}

	else
	{
		puts(BACK_RED"Test: Failure"RESET);	
	}


    return 0;
}



