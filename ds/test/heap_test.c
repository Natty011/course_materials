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

/***************************End of function declaration******************/

/******************static functions definition**********************/
		
/*******************SortingFunc*********************/
static int SortingFunc(const void* check_data ,const void* new_data, void* param)
{
	UNUSED(param);
	return (*(int*)check_data - *(int*)new_data);
}
/*******************Compare*********************/
static int Compare(void* check_data , void* new_data)
{
	return !(SUCCESS == (*(int*)check_data - *(int*)new_data));
}
/*******************Compare2*********************/
static int Compare2(void* check_data , void* new_data)
{
	return  ( *(int*)check_data >= *(int*)new_data );
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
       /*
 	puts(BLUE"====================================================="RESET);  	
   	puts(BACK_BLUE"'TestAvlTwoeNode()'"RESET);
    TestAvlTwoeNode();
    */
	puts(BLUE"====================================================="RESET);

	return 0;
}



/********************  TestAvlOneNode  ****************************/
static void TestHeap(void)
{	
	int flag = FALSE;
	heap_t *heap1 = NULL;
	int arr[10] = {16, 10, 13, 8, 5, 9, 3, 2, 1, 4};
	int param [ 10 ] =  {16, 10, 13, 8, 5, 9, 3, 2, 1, 4};
	/*size_t i = 0;*/
		
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

	if ( FAIL == HeapPush( heap1, arr ) )
	{
		printf("line: %d \n" , __LINE__ );
		puts("Failes in_1: Push - Allocation");
		flag =  TRUE;

	}

	

	/*
	for(i = 0; i <= 10; ++i)
	{
		flag = AVLInsert(heap1, arr + i);
		
		if( flag )
		{
			puts("Failes in_1: Insert Allocation failed ");
			flag =  TRUE;
		}

	}
	*/
/*
	if( 11 != AVLSize(avl1) || 3 != AVLHeight(avl1) )
	{
		
		puts("Failes in_1: Size || Height");
		flag =  TRUE;
	
	}
	
	
	for(i = 0; i <= 10; ++i)
	{
		flag = Compare(AVLFind(avl1, arr + i), arr + i);
		
		if( flag )
		{
			printf("Failes in_1: Find, i = %lu \n", i);
			flag =  TRUE;
		}

	}
	
	*/
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
	
