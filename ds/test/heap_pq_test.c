/***************************************
* Author : Natty
* Reviewer : Rawan
* Date : 22 / 02 / 2025
* Last update: 22 / 02 / 2025
*****************************************/

#include <stdio.h> 		/* printf, puts,  */
#include <string.h> 	/* strcpy, strcmp */
#include <assert.h>
#include "heap_pq.h" 
#include "heap.h" 

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

#define CANDIDATE    "CANDIDATE TO INSERT: "

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
	char* background = BACK_MAGENTA;	
	
	#ifndef NDEBUG
		mode = DEBUG;
		background = BACK_YELLOW;
	#endif

	puts(BLUE"====================================================="RESET);
	printf("%sTEST: %s "RESET" \n", background,  mode);
	puts(BACK_GREEN"'HeapPqTest()'"RESET);
	puts(BACK_BLUE"'TestString()'"RESET);
    TestString();
	puts(BLUE"====================================================="RESET);

     
return 0;
}

static void TestString(void)
{
	
	size_t i = 0;
	int res = 0;
	char* arr[5] = {"a", "b", "e", "i", "c" };
	int flag = FALSE;

	heap_pq_t* pqueue1 = HeapPQueueCreate(priority_func);
	
	/*puts(RED);*/
	
	if(HeapPQueueSize(pqueue1) != 0 || !HeapPQueueIsEmpty(pqueue1))
	{
		printf("line: %d \n" , __LINE__ );
		puts("Failes in TestString: Size & IsEmpty");
		flag =  TRUE;

	}
		
	res = HeapPQueueEnqueue(pqueue1, arr[0]);
	
	if( HeapPQueueIsEmpty(pqueue1)  || HeapPQueueSize(pqueue1) != 1 || res ||
		match_func((char*)HeapPQueuePeek(pqueue1), (char*)arr[0]) != TRUE)
	{
		printf("line: %d \n" , __LINE__ );
		puts("Failes in TestString: IsEmpty & Size & Peek & Enqueue");
		flag =  TRUE;

	}

	HeapPQueueDequeue(pqueue1);
	
	if( !HeapPQueueIsEmpty(pqueue1)  || HeapPQueueSize(pqueue1) != 0)
	{
		printf("line: %d \n" , __LINE__ );
		puts("Failes in TestString: IsEmpty & Size & Dequeue");
		flag =  TRUE;
	
	}
	
	for(i = 0; i <= 4; ++i)
	{
        res = HeapPQueueEnqueue(pqueue1, arr[i]);
	
        if((i != 4) && (HeapPQueueIsEmpty(pqueue1)  ||
		HeapPQueueSize(pqueue1) != (i+1) || res ||
			match_func((char*)HeapPQueuePeek(pqueue1), (char*)arr[i]) != TRUE ) )
		{
			printf("line: %d \n" , __LINE__ );
			flag =  TRUE;
			puts("Failes in TestString_1: IsEmpty & Size & Peek & Enqueue");
		}
		
		if( (i == 4) && (HeapPQueueIsEmpty(pqueue1)  ||
			HeapPQueueSize(pqueue1) != (i+1) || res ||
			match_func((char*)HeapPQueuePeek(pqueue1), (char*)arr[i-1]) != TRUE ) )
		{
			printf("line: %d \n" , __LINE__ );
			flag =  TRUE;
			puts("Failes in TestString_2: IsEmpty & Size & Peek & Enqueue");
		}
		
	}
	
	HeapPQueueErase(pqueue1, match_func, HeapPQueuePeek(pqueue1) );
	
	if( HeapPQueueIsEmpty(pqueue1)  ||
		HeapPQueueSize(pqueue1) != 4  ||
		match_func((char*)HeapPQueuePeek(pqueue1), arr[2]) != TRUE )
	{
		printf("line: %d \n" , __LINE__ );
		flag =  TRUE;
		puts("Failes in TestString_1: HeapPQueueErase & Size & Peek");
	}

	HeapPQueueErase(pqueue1, match_func, HeapPQueuePeek(pqueue1) );
	
	if( HeapPQueueIsEmpty(pqueue1)  ||
		HeapPQueueSize(pqueue1) != 3 ||
		match_func((char*)HeapPQueuePeek(pqueue1), arr[4]) != TRUE )
	{
		printf("line: %d \n" , __LINE__ );
		flag =  TRUE;
		puts("Failes in TestString_2: HeapPQueueErase & Size & Peek");
	}
	
	HeapPQueueErase(pqueue1, match_func, HeapPQueuePeek(pqueue1) );
		
	if( HeapPQueueIsEmpty(pqueue1)  ||
		HeapPQueueSize(pqueue1) != 2 ||
		match_func((char*)HeapPQueuePeek(pqueue1), arr[1]) != TRUE )
	{
		printf("line: %d \n" , __LINE__ );
		flag =  TRUE;
		puts("Failes in TestString_3: HeapPQueueErase & Size & Peek");
	}

	HeapPQueueClear(pqueue1);
	
	if(HeapPQueueSize(pqueue1) != 0 || !HeapPQueueIsEmpty(pqueue1))
	{
		printf("line: %d \n" , __LINE__ );
		flag =  TRUE;
		puts("Failes in TestString: HeapPQueueClear");
	}

	for(i = 0; i <= 4; ++i)
	{
        res = HeapPQueueEnqueue(pqueue1, arr[i]);
	
        if((i != 4) && (HeapPQueueIsEmpty(pqueue1)  ||
		HeapPQueueSize(pqueue1) != (i+1) || res ||
			match_func((char*)HeapPQueuePeek(pqueue1), (char*)arr[i]) != TRUE ) )
		{
			printf("line: %d \n" , __LINE__ );
			flag =  TRUE;
			puts("Failes in TestString_1: IsEmpty & Size & Peek & Enqueue");
		}
		
		if( (i == 4) && (HeapPQueueIsEmpty(pqueue1)  ||
			HeapPQueueSize(pqueue1) != (i+1) || res ||
			match_func((char*)HeapPQueuePeek(pqueue1), (char*)arr[i-1]) != TRUE ) )
		{
			printf("line: %d \n" , __LINE__ );
			flag =  TRUE;
			puts("Failes in TestString_2: IsEmpty & Size & Peek & Enqueue");
		}
		
	}

	HeapPQueueClear(pqueue1);
	
	if(HeapPQueueSize(pqueue1) != 0 || !HeapPQueueIsEmpty(pqueue1))
	{
		printf("line: %d \n" , __LINE__ );
		flag =  TRUE;
		puts("Failes in TestString: HeapPQueueClear");
	}

	for(i = 0; i <= 4; ++i)
	{
        res = HeapPQueueEnqueue(pqueue1, arr[i]);
	
        if((i != 4) && (HeapPQueueIsEmpty(pqueue1)  ||
		HeapPQueueSize(pqueue1) != (i+1) || res ||
			match_func((char*)HeapPQueuePeek(pqueue1), (char*)arr[i]) != TRUE ) )
		{
			printf("line: %d \n" , __LINE__ );
			flag =  TRUE;
			puts("Failes in TestString_1: IsEmpty & Size & Peek & Enqueue");
		}
		
		if( (i == 4) && (HeapPQueueIsEmpty(pqueue1)  ||
			HeapPQueueSize(pqueue1) != (i+1) || res ||
			match_func((char*)HeapPQueuePeek(pqueue1), (char*)arr[i-1]) != TRUE ) )
		{
			printf("line: %d \n" , __LINE__ );
			flag =  TRUE;
			puts("Failes in TestString_2: IsEmpty & Size & Peek & Enqueue");
		}
		
	}

	
	
	HeapPQueueDestroy(pqueue1);	
	pqueue1 = NULL;

	if( !flag )
	{
		puts(RESET);		
		puts(BACK_BLUE"Test: Success"RESET);

	}
	
	else
	{
		puts(BACK_YELLOW"Test: Failure"RESET);	
	}

	/*puts(GREEN"TestString: Success"RESET);*/
	
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
		
	return res;
}

