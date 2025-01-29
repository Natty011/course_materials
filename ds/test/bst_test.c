/***************************************
* Author : Natty
* Reviewer : David
* Date : 22 / 01 / 2025
* Last update: 23 / 01 / 2025
*****************************************/

#include <stdio.h> 		/* printf, puts, qsort  */
#include <assert.h>
#include <string.h> 	/* strcpy, strcmp */

#include "bst.h" 

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

/** possible return values **/
typedef enum
{
	
	SUCCESS = 0,
	OPERATION_FAIL = 1
	
}bst_result_t;

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
	PrintArr(arr, 10);
	#endif
	
	# ifndef NDEBUG
	PrintArr(arr, 10);
	#endif
*/
/***************End of struct and enum declaration *******/

/***************************function declaration**************************/
static void TestBst(void);
/*
static int match_func (void *check_data, void *user_param);
static int priority_func(void *check_data, void *user_param );
static int Compare(const void* a, const void* b);
*/
static int SortingFunc(void* check_data , void* new_data);
/*static void PrintArr(int* arr, size_t len);*/
/***************************End of function declaration******************/

/******************static functions definition**********************/

/********************  PrintArr  ****************************/
/* # ifndef NDEBUG */
/*
	#ifdef PRINTS
static void PrintArr(int* arr, size_t len)
{	
	size_t i = 0;
		
	for(i = 0; i < len; ++i)
	{
		printf("arr[%lu] = %d ", i, arr[i]);
		puts("");
	}
	
}
	
#endif
*/
/********************  Compare  ****************************/



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
   	puts(BACK_BLUE"'TestBst()'"RESET);
    TestBst();
    
	puts(BLUE"====================================================="RESET);

	return 0;
}



/********************  Test2Block  ****************************/
static void TestBst(void)
{	
	int flag = FALSE, res = 0;
	size_t i = 0;
	char* arr[5] = {"a", "b", "e", "i", "c" };
	
	bst_iter_t dummy_itr1;
	bst_iter_t itr1;
	bst_iter_t itr2;
	bst_iter_t itr3;
	
	bst_t *bst1 = BstCreate(SortingFunc);	
	/*puts(RED);*/
	/* || !BstIsEmpty(bst1) */
	if( !BstIsEmpty(bst1) )  /* (BstSize(bst1) != 0 )*/
	{

		puts("Failes in_1: IsEmpty");
		flag =  TRUE;
	}
	
	if( BstSize(bst1) != 0 )  
	{
		puts("Failes in_1: Size");
		flag =  TRUE;
	}
	
	dummy_itr1 = BstBegin(bst1);
	
	if( BstEnd(bst1) != dummy_itr1 )
	{
		puts("Failes in_1: Begin || End ");
		flag =  TRUE;
	}
	/*
	res = BstInsert(pqueue1, arr[0]);
	*/	          
	if( !flag )
	{
		puts(RESET);		
		puts(BACK_BLUE"Test: Success"RESET);

	}
	
	else
	{
		puts(BACK_YELLOW"Test: Failure"RESET);	
	}
	
	BstDestroy(bst1);
	bst1 = NULL;

}

/*******************match_function*********************/
/*
static int match_func(void *check_data, void *user_param )
{
	return !strcmp(check_data, user_param);
}
*/
/*******************priority_func*********************/
/*
static int priority_func(void *check_data, void *user_param )
{
	int res = strcmp(check_data, user_param);
		
	return (-1) * res;
}
*/
/*******************Compare*********************/
/*
static int Compare(const void* a, const void* b)
{
    return (*(int*)a - *(int*)b);
}
*/
/*******************SortingFunc*********************/
static int SortingFunc(void* check_data , void* new_data)
{
	return (*(int*)check_data - *(int*)new_data);
}


/*
puts("\n" BACK_CYAN"Ratio time:"RESET"\n");
	printf("BubbleSort/QuickSort   : "BACK_GREEN" %f "RESET" \n", \
           t_bubble/t_qsort);
           
*/           
