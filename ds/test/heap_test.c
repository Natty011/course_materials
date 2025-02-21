/***************************************
* Author : Natty
* Reviewer : 
* Date : 19 / 02 / 2025
* Last update: 19 / 02 / 2025
*****************************************/

#include <stdio.h> 		/* printf, puts, qsort  */
#include <assert.h>
#include <string.h> 	/* strcpy, strcmp */

#include "heap.h" 
#include "vector.h" 

#ifdef PRINTS
	#include "vector.h" 
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

#define MIN(a, b)		((a > b ) ? b : a )
#define MAX(a, b)		((a > b ) ? a : b )
#define UNUSED( var )       ( (void)var )
/***************struct and enum declaration *******/


typedef enum
{
	
	SUCCESS = 0,
	FAIL = 1
	
}avl_result_t;

typedef enum
{
	
	FALSE = 0,
	TRUE = 1
	
}func_result_t;

typedef enum
{
	
	LEFT = 0,
	RIGHT = 1
	
}child_pose_t;

typedef enum
{
	
	NO_CHILDS = 0,
	ONE_CHILD = 1,
	TWO_CHILDS = 2
	
}nume_of_childs_t;

/*
	#ifdef PRINTS
		Aux_Pre_Print_Tree(avl1, 0);
	#endif
*/
/***************End of struct and enum declaration *******/

/***************************function declaration**************************/
static void TestHeap(void);
/*
static void TestAvlTwoeNode(void);
*/
static int SortingFunc(const void* check_data ,const void* new_data, void* param);
static int match_func(void* check_data , void* new_data);
/***************************End of function declaration******************/

/******************static functions definition**********************/
		
/*******************SortingFunc*********************/
static int SortingFunc(const void* check_data ,const void* new_data, void* param)
{
	UNUSED(param);
	return (*(int*)check_data - *(int*)new_data);
}
/*******************Compare*********************/
/*
static int Compare(void* check_data , void* new_data)
{
	return !(SUCCESS == (*(int*)check_data - *(int*)new_data));
}
*/
/*******************Compare2*********************/
/*
static int Compare2(void* check_data , void* new_data)
{
	return  ( *(int*)check_data >= *(int*)new_data );
}
*/
/*******************match_func*********************/

static int match_func(void* check_data , void* new_data)
{
	return (SUCCESS == (*(int*)check_data - *(int*)new_data));
}

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
   	puts(BACK_BLUE"'TestHeap()'"RESET);
    TestHeap();

	puts(BLUE"====================================================="RESET);

	return 0;
}



/********************  TestAvlOneNode  ****************************/
static void TestHeap(void)
{	
	int flag = FALSE;
	heap_t *heap1 = NULL;
	int arr[12] = {16, 10, 13, 8, 5, 9, 3, 2, 1, 4, 12 , 17};
	/*int arr[11] = {16, 10, 13, 8, 5, 9, 3, 2, 1, 4, 12};*/
	void *data = NULL;
	int param [ 1 ] =  {16};

	int param2 [ 1 ] =  {20};
	size_t size = sizeof( arr ) / sizeof( arr[0] ) ; 
	size_t i = 0;
		
	heap1 = HeapCreate(param , SortingFunc);

	/*puts(RED);*/

	if(! heap1 )
	{
		printf("line: %d \n" , __LINE__ );
		puts("Failes in_1: Create - Allocation");
		flag =  TRUE;
	}

	if( !HeapIsEmpty(heap1)||  0 != HeapSize(heap1) ) 
	{
		printf("line: %d \n" , __LINE__ );
		puts("Failes in_1: IsEmpty || Size ");
		flag =  TRUE;
	}

	if ( FAIL == HeapPush( heap1, arr ))
	{
		printf("line: %d \n" , __LINE__ );
		puts("Failes in_1: Push - Allocation");
		flag =  TRUE;

	}

	if ( HeapIsEmpty(heap1) ||  1 != HeapSize(heap1) || 
	 			arr[0] != *(int*)HeapPeek(heap1) )
	{
		printf("line: %d \n" , __LINE__ );
		puts("Failes in_2: Push || Peek");

		#ifdef PRINTS
			printf(" HeapPeek(heap1)  = %d", *(int*)HeapPeek(heap1) );
		#endif
		flag =  TRUE;
	}


	/*PrintArray(heap1);	*/
	/* pop 16 , one member */
	HeapPop(heap1);
	/*PrintArray(heap1);	*/

	if( !HeapIsEmpty(heap1)||  0 != HeapSize(heap1) ) 
	{
		printf("line: %d \n" , __LINE__ );
		puts("Failes in_1: Pop ");
		flag =  TRUE;
	}

	if ( FAIL == HeapPush( heap1, arr ))
	{
		printf("line: %d \n" , __LINE__ );
		puts("Failes in_2: Push - Allocation");
		flag =  TRUE;

	}

	if ( HeapIsEmpty(heap1) ||  1 != HeapSize(heap1) || 
	 			arr[0] != *(int*)HeapPeek(heap1) )
	{
		printf("line: %d \n" , __LINE__ );
		puts("Failes in_3: Push || Peek");

		#ifdef PRINTS
			printf(" HeapPeek(heap1)  = %d", *(int*)HeapPeek(heap1) );
		#endif
		flag =  TRUE;
	}
	/* remove 16 , one member */
	PrintArray(heap1);	

	data = HeapRemove(heap1, match_func, arr  );

	if( data )
	{
		if ( arr[0] != *(int*)data || 0 != HeapSize(heap1) )
		{
			printf("line: %d \n" , __LINE__ );
			puts("Failes in_2: Remove || Size");
		}

		#ifdef PRINTS
			/*printf(" data  = %d \n", *(int*)data );*/
		#endif
	}
	
	for(i = 0; i < size  ; ++i) /* size */
	{
		if ( FAIL == HeapPush( heap1, arr + i ))
		{
			printf("line: %d , Iteration = %ld \n" , __LINE__ , i );
			puts("Failes in_1: Push - Allocation");
			flag =  TRUE;

		}
		
		if ( HeapIsEmpty(heap1) || ( i + 1 ) != HeapSize(heap1) )
		{
			printf("line: %d , Iteration = %ld \n" , __LINE__ , i );
			puts("Failes in_2: Push ");

			#ifdef PRINTS
				printf(" HeapPeek(heap1)  = %d", *(int*)HeapPeek(heap1) );
			#endif
			flag =  TRUE;

		}

		/* heapify to root 16 -> 17*/
		if ( i == size - 1)
		{
			if( arr[ i ] != *(int*)HeapPeek(heap1) )
			{
				printf("line: %d , Iteration = %ld \n" , __LINE__ , i );
				puts("Failes in_3: Push ");
				flag =  TRUE;
			}

		}
		
	}
	PrintArray(heap1);	
	#ifdef PRINTS
		printf(" HeapPeek(heap1)  = %d \n", *(int*)HeapPeek(heap1) );
	#endif

	/* pop 17  */
	puts("pop 17");

	/*HeapPop(heap1);*/
/*
	if( HeapIsEmpty(heap1) || 11 != HeapSize(heap1) ||
		arr[0] != *(int*)HeapPeek(heap1) ) 
	{
		printf("line: %d \n" , __LINE__ );
		puts("Failes in_3: Pop ");
		flag =  TRUE;
	}
*/
	/* remove 9 */
	/*puts("remove_9");*/
	data = HeapRemove(heap1, match_func, arr + 5 );
	
	if(  arr[5] != *(int*)data || 10 != HeapSize(heap1) ||
		arr[0] != *(int*)HeapPeek(heap1)  )
	{
			printf("line: %d \n" , __LINE__ );
			puts("Failes in_4: Remove ");
		
		/*printf(" data  = %d \n", *(int*)data ); */
	}
	
	/* remove 16  */
	/*puts("remove_16");*/

	data = HeapRemove(heap1, match_func, arr  );

	if(  arr[0] != *(int*)data || 9 != HeapSize(heap1) ||
			arr[2] != *(int*)HeapPeek(heap1)  )
	{

			printf("line: %d \n" , __LINE__ );
			puts("Failes in_5: Remove ");
	
		/*printf(" data  = %d \n", *(int*)data ); */
	}

	/* remove 12 */
	/*puts("remove_12");*/

	data = HeapRemove(heap1, match_func, arr + 10  );

	if(  arr[10] != *(int*)data || 8 != HeapSize(heap1) ||
			arr[2] != *(int*)HeapPeek(heap1)  )
	{

			printf("line: %d \n" , __LINE__ );
			puts("Failes in_6: Remove ");
	
		/*printf(" data  = %d \n", *(int*)data ); */
	}
	
	/*PrintArray(heap1);*/

	/*puts("remove_20_doesnt_exist");*/

	data = HeapRemove(heap1, match_func, param2  );

	if(  NULL != data || 8 != HeapSize(heap1) ||
			arr[2] != *(int*)HeapPeek(heap1)  )
	{

			printf("line: %d \n" , __LINE__ );
			puts("Failes in_7: Remove ");
	
		/*printf(" data  = %d \n", *(int*)data ); */
	}

	/*PrintArray(heap1);*/

	/* pop 13  */
	/*puts("pop 13");*/

	/*HeapPop(heap1);*/

	if( 7 != HeapSize(heap1) || arr[1] != *(int*)HeapPeek(heap1) ) 
	{
		printf("line: %d \n" , __LINE__ );
		puts("Failes in_5: Pop ");
		flag =  TRUE;
	}

	/*PrintArray(heap1);*/

	/* pop 10  */
	/*puts("pop 10");*/

	/*HeapPop(heap1);*/

	if( 6 != HeapSize(heap1) || arr[3] != *(int*)HeapPeek(heap1) ) 
	{
		printf("line: %d \n" , __LINE__ );
		puts("Failes in_6: Pop ");
		flag =  TRUE;
	}

	/*PrintArray(heap1);*/

	/* pop 8  */
	/*puts("pop 8");*/

	/*HeapPop(heap1);*/

	if( 5 != HeapSize(heap1) || arr[4] != *(int*)HeapPeek(heap1) ) 
	{
		printf("line: %d \n" , __LINE__ );
		puts("Failes in_7: Pop ");
		flag =  TRUE;
	}

	/*PrintArray(heap1);*/
	/* pop 5  */
	/*puts("pop 5");*/

	/*HeapPop(heap1);*/

	if( 4 != HeapSize(heap1) || arr[9] != *(int*)HeapPeek(heap1) ) 
	{
		printf("line: %d \n" , __LINE__ );
		puts("Failes in_7: Pop ");
		flag =  TRUE;
	}

	/*PrintArray(heap1);*/

	/* pop 4  */
	/*puts("pop 4");*/

	/*HeapPop(heap1);*/

	if( 3 != HeapSize(heap1) || arr[6] != *(int*)HeapPeek(heap1) ) 
	{
		printf("line: %d \n" , __LINE__ );
		puts("Failes in_8: Pop ");
		flag =  TRUE;
	}

	/*PrintArray(heap1);*/

	/* pop 3  */
	/*puts("pop 3");*/

	/*HeapPop(heap1);*/

	if( 2 != HeapSize(heap1) || arr[7] != *(int*)HeapPeek(heap1) ) 
	{
		printf("line: %d \n" , __LINE__ );
		puts("Failes in_9: Pop ");
		flag =  TRUE;
	}

	/*PrintArray(heap1);*/

	/* pop 2  */
	/*puts("pop 2");*/

	/*HeapPop(heap1);*/

	if( 1 != HeapSize(heap1) || arr[8] != *(int*)HeapPeek(heap1) ) 
	{
		printf("line: %d \n" , __LINE__ );
		puts("Failes in_10: Pop ");
		flag =  TRUE;
	}

	HeapDestroy(heap1);
	heap1 = NULL;
	
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
	
