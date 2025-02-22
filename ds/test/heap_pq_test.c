/***************************************
* Author : Natty
* Reviewer : Michael
* Date : 26 / 12 / 2024
* Last update: 26 / 12 / 2024
*****************************************/

#include <stdio.h> 		/* printf, puts,  */
#include <string.h> 	/* strcpy, strcmp */
#include <assert.h>
#include "pqueue.h" 

#define RED          "\x1b[31m"
#define GREEN        "\x1b[32m"
#define BLUE         "\x1b[34m"
#define RESET        "\x1b[0m"

#define YELLOW  "\x1b[43m"
#define MAGENTA "\x1b[45m"

#define CANDIDATE    "CANDIDATE TO INSERT: "

#define DEBUG		"DEBUG MODE"
#define RELEASE		"RELEASE MODE"

typedef enum
{
	
	FALSE = 0,
	TRUE = 1
	
}func_result_t;

static int match_func (void *check_data, void *user_param);
static int priority_func(void *check_data, void *user_param );

/***************************function declaration**************************/
static void TestString(void);
/***************************End of function declaration******************/

int main ()
{

	char* mode = RELEASE;
	char* background = MAGENTA;	
	
	#ifndef NDEBUG
		mode = DEBUG;
		background = YELLOW;
	#endif

	puts(BLUE"====================================================="RESET);
	printf("%sTEST: %s "RESET" \n", background,  mode);
    puts(GREEN"'TestString()'");
    TestString();
	puts(BLUE"====================================================="RESET);

     
return 0;
}

static void TestString(void)
{
	
	size_t i = 0;
	int res = 0;
	char* arr[5] = {"a", "b", "e", "i", "c" };
	
	pqueue_t* pqueue1 = PQueueCreate(priority_func);
	
	puts(RED);
	
	if(PQueueSize(pqueue1) != 0 || !PQueueIsEmpty(pqueue1))
	{
		puts("Failes in TestString: Size & IsEmpty");
	}
		
	res = PQueueEnqueue(pqueue1, arr[0]);
	
	if( PQueueIsEmpty(pqueue1)  || PQueueSize(pqueue1) != 1 || res ||
		match_func((char*)PQueuePeek(pqueue1), (char*)arr[0]) != TRUE)
	{
		puts("Failes in TestString: IsEmpty & Size & Peek & Enqueue");
	}

	PQueueDequeue(pqueue1);
	
	if( !PQueueIsEmpty(pqueue1)  || PQueueSize(pqueue1) != 0)
	{
		puts("Failes in TestString: IsEmpty & Size & Dequeue");
	}
	
	for(i = 0; i <= 4; ++i)
	{

        res = PQueueEnqueue(pqueue1, arr[i]);
	
        if((i != 4) && (PQueueIsEmpty(pqueue1)  ||
        	 PQueueSize(pqueue1) != (i+1) || res ||
			match_func((char*)PQueuePeek(pqueue1), (char*)arr[i]) != TRUE ) )
		{
			puts("Failes in TestString_1: IsEmpty & Size & Peek & Enqueue");
		}
		
		if( (i == 4) && (PQueueIsEmpty(pqueue1)  ||
			 PQueueSize(pqueue1) != (i+1) || res ||
			match_func((char*)PQueuePeek(pqueue1), (char*)arr[i-1]) != TRUE ) )
		{
			puts("Failes in TestString_2: IsEmpty & Size & Peek & Enqueue");
		}
		
	}
	
	PQueueErase(pqueue1, match_func, PQueuePeek(pqueue1) );
	
	if( PQueueIsEmpty(pqueue1)  ||
		PQueueSize(pqueue1) != 4  ||
		match_func((char*)PQueuePeek(pqueue1), arr[2]) != TRUE )
	{
		puts("Failes in TestString_1: PQueueErase & Size & Peek");
	}

	PQueueErase(pqueue1, match_func, PQueuePeek(pqueue1) );
	
	if( PQueueIsEmpty(pqueue1)  ||
		PQueueSize(pqueue1) != 3 ||
		match_func((char*)PQueuePeek(pqueue1), arr[4]) != TRUE )
	{
		puts("Failes in TestString_2: PQueueErase & Size & Peek");
	}
	
	PQueueErase(pqueue1, match_func, PQueuePeek(pqueue1) );
		
	if( PQueueIsEmpty(pqueue1)  ||
		PQueueSize(pqueue1) != 2 ||
		match_func((char*)PQueuePeek(pqueue1), arr[1]) != TRUE )
	{
		puts("Failes in TestString_3: PQueueErase & Size & Peek");
	}
	
	PQueueClear(pqueue1);
	
	if(PQueueSize(pqueue1) != 0 || !PQueueIsEmpty(pqueue1))
	{
		puts("Failes in TestString: PQueueClear");
	}
			
	puts(GREEN"TestString: Success"RESET);
	
	PQueueDestroy(pqueue1);	
}	

/*******************match_function*********************/

static int match_func(void *check_data, void *user_param )
{
	return !strcmp(check_data, user_param);
}

/*******************priority_func*********************/

static int priority_func(void *check_data, void *user_param )
{
	int res = strcmp(check_data, user_param);
		
	return (-1) * res;
}

