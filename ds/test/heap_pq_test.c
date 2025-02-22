/***************************************
* Author : Natty
* Reviewer : Michael
* Date : 26 / 12 / 2024
* Last update: 26 / 12 / 2024
*****************************************/

#include <stdio.h> 		/* printf, puts,  */
#include <string.h> 	/* strcpy, strcmp */
#include <assert.h>
#include "heap_pq.h" 
#include "heap.h" 

#define RED          "\x1b[31m"
#define GREEN        "\x1b[32m"
#define BLUE         "\x1b[34m"
#define RESET        "\x1b[0m"

#define YELLOW  "\x1b[43m"
#define MAGENTA "\x1b[45m"

#define CANDIDATE    "CANDIDATE TO INSERT: "

#define DEBUG		"DEBUG MODE"
#define RELEASE		"RELEASE MODE"
#define UNUSED( var )       ( (void)var )

typedef enum
{
	
	FALSE = 0,
	TRUE = 1
	
}func_result_t;

static int match_func (void *check_data, void *user_param);
static int
 priority_func(const void *check_data,const void *new_data, void* user_param);

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
	
	heap_pq_t* pqueue1 = HeapPQueueCreate(priority_func);
	
	puts(RED);
	
	if(HeapPQueueSize(pqueue1) != 0 || !HeapPQueueIsEmpty(pqueue1))
	{
		puts("Failes in TestString: Size & IsEmpty");
	}
		
	res = HeapPQueueEnqueue(pqueue1, arr[0]);
	
	if( HeapPQueueIsEmpty(pqueue1)  || HeapPQueueSize(pqueue1) != 1 || res ||
		match_func((char*)HeapPQueuePeek(pqueue1), (char*)arr[0]) != TRUE)
	{
		puts("Failes in TestString: IsEmpty & Size & Peek & Enqueue");
	}

	HeapPQueueDequeue(pqueue1);
	
	if( !HeapPQueueIsEmpty(pqueue1)  || HeapPQueueSize(pqueue1) != 0)
	{
		puts("Failes in TestString: IsEmpty & Size & Dequeue");
	}
	
	for(i = 0; i <= 4; ++i)
	{

        res = HeapPQueueEnqueue(pqueue1, arr[i]);
	
        if((i != 4) && (HeapPQueueIsEmpty(pqueue1)  ||
		HeapPQueueSize(pqueue1) != (i+1) || res ||
			match_func((char*)HeapPQueuePeek(pqueue1), (char*)arr[i]) != TRUE ) )
		{
			puts("Failes in TestString_1: IsEmpty & Size & Peek & Enqueue");
		}
		
		if( (i == 4) && (HeapPQueueIsEmpty(pqueue1)  ||
			HeapPQueueSize(pqueue1) != (i+1) || res ||
			match_func((char*)HeapPQueuePeek(pqueue1), (char*)arr[i-1]) != TRUE ) )
		{
			puts("Failes in TestString_2: IsEmpty & Size & Peek & Enqueue");
		}
		
	}
	
	HeapPQueueErase(pqueue1, match_func, HeapPQueuePeek(pqueue1) );
	
	if( HeapPQueueIsEmpty(pqueue1)  ||
		HeapPQueueSize(pqueue1) != 4  ||
		match_func((char*)HeapPQueuePeek(pqueue1), arr[2]) != TRUE )
	{
		puts("Failes in TestString_1: PQueueErase & Size & Peek");
	}

	HeapPQueueErase(pqueue1, match_func, HeapPQueuePeek(pqueue1) );
	
	if( HeapPQueueIsEmpty(pqueue1)  ||
		HeapPQueueSize(pqueue1) != 3 ||
		match_func((char*)HeapPQueuePeek(pqueue1), arr[4]) != TRUE )
	{
		puts("Failes in TestString_2: PQueueErase & Size & Peek");
	}
	
	HeapPQueueErase(pqueue1, match_func, HeapPQueuePeek(pqueue1) );
		
	if( HeapPQueueIsEmpty(pqueue1)  ||
		HeapPQueueSize(pqueue1) != 2 ||
		match_func((char*)HeapPQueuePeek(pqueue1), arr[1]) != TRUE )
	{
		puts("Failes in TestString_3: PQueueErase & Size & Peek");
	}

	HeapPQueueClear(pqueue1);
	
	if(HeapPQueueSize(pqueue1) != 0 || !HeapPQueueIsEmpty(pqueue1))
	{
		puts("Failes in TestString: PQueueClear");
	}
			
	puts(GREEN"TestString: Success"RESET);
	
	HeapPQueueDestroy(pqueue1);	
}	

/*******************match_function*********************/

static int match_func(void *check_data, void *user_param )
{
	return !strcmp(check_data, user_param);
}

/*******************priority_func*********************/

static int priority_func(const void *check_data,const void *new_data, void* user_param)
{
	int res = 0;
	UNUSED(user_param);
	res = strcmp((void*)check_data, (void*)new_data);
		
	return (-1) * res;
}

