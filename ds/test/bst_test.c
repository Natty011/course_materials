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

#define MIN(a, b)		((a > b ) ? b : a )
#define MAX(a, b)		((a > b ) ? a : b )

extern int destroy_check;
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
static void TestBstOneNode(void);
static void TestBstTwoeNode(void);
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
   	puts(BACK_BLUE"'TestBstOneNode()'"RESET);
    TestBstOneNode();
       
 	puts(BLUE"====================================================="RESET);  	
   	puts(BACK_BLUE"'TestBstTwoeNode()'"RESET);
    TestBstTwoeNode();
    
	puts(BLUE"====================================================="RESET);

	return 0;
}


/********************  TestBstOneNode  ****************************/
static void TestBstOneNode(void)
{	
	int flag = FALSE;

	int arr[8] = {100, 70, 110, 85, 80, 75 ,65 , 85 };
	
	bst_iter_t dummy_itr1;
	bst_iter_t itr1;

	bst_t *bst1 = BstCreate(SortingFunc);	
	/*puts(RED);*/

	if( !BstIsEmpty(bst1) ) 
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
	
	itr1 = BstInsert(bst1, arr);
	/* SortingFunc(BstGetData(itr1) ,BstGetData(BstBegin(bst1))) */
	/* BstSize(bst1) != 1 || */
	/* BstIsEmpty(bst1)  */
	/* *arr != *(int*)BstGetData(BstBegin(bst1)) */
	/*printf("size = %lu\n", BstSize(bst1) );*/
	if( SortingFunc(BstGetData(itr1) ,BstGetData(BstBegin(bst1)))  
	     || BstSize(bst1) != 1 || BstIsEmpty(bst1) )
		 
	{
		puts("Failes in_1: Insert || Begin || GetData || Size || IsEmpty");
		flag =  TRUE;
	}
	
	if( itr1 != BstPrev(dummy_itr1) || dummy_itr1 != BstPrev(itr1) )
	{
		puts("Failes in_1: Prev");
		flag =  TRUE;	
	}
	
	if( dummy_itr1 != BstNext(dummy_itr1) || dummy_itr1 != BstNext(itr1) )
	{
		puts("Failes in_1: Next");
		flag =  TRUE;	
	}
	
	if( itr1 != BstFind(bst1, arr) || dummy_itr1 != BstFind(bst1, arr + 1) 
		|| dummy_itr1 != BstFind(bst1, arr + 2) )
	{
		puts("Failes in_1: Find");
		flag =  TRUE;	
	}
	
	if( TRUE != IsIterSame(itr1, itr1) || 
		FALSE != IsIterSame(itr1, dummy_itr1) )
	{
		puts("Failes in_1: IsIterSame");
		flag =  TRUE;
	} 
	
	if( SUCCESS != BstForEach(itr1, dummy_itr1, SortingFunc, arr) || 
		OPERATION_FAIL != BstForEach(itr1, dummy_itr1, SortingFunc, arr + 1) )
	{
		puts("Failes in_1: ForEach");
		flag =  TRUE;
	
	} 
	
	if( dummy_itr1 != BstRemove(itr1) || BstSize(bst1) != 0 )
	{
		puts("Failes in_1: Remove || Size");
		flag =  TRUE;	
	}
	
	itr1 = BstInsert(bst1, arr);  
	BstDestroy(bst1);
	bst1 = NULL;
	
	if( OPERATION_FAIL == destroy_check )
	{
		puts("Failes in_1: Destroy");
		flag =  TRUE;
	}
	/*printf("destroy_check = %d\n", destroy_check);*/
	/*BstFind*/
	/*itr1 = BstInsert(bst1, arr);*/

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



/********************  TestBstOneNode  ****************************/
static void TestBstTwoeNode(void)
{	
	int arr[11] = {100, 70, 110, 85, 80, 75 ,65 , 67, 130, 30, 150};
	int arr_sort[11] = {30, 65, 67, 70, 75, 80, 85 ,100 , 110, 130, 150};
	int flag = FALSE, max = arr[0], min = arr[0];
	size_t i = 0;

	bst_iter_t dummy_itr1;
	bst_iter_t itr1;
	bst_iter_t itr2;
	bst_iter_t itr3;
	bst_iter_t itr4;
	bst_iter_t itr5;
	
	bst_t *bst1 = BstCreate(SortingFunc);	
	/*puts(RED);*/

	if( !BstIsEmpty(bst1) )  
	{

		puts("Failes in_2: IsEmpty");
		flag =  TRUE;
	}
	
	if( BstSize(bst1) != 0 )  
	{
		puts("Failes in_2: Size");
		flag =  TRUE;
	}
	
	dummy_itr1 = BstBegin(bst1);
	
	if( BstEnd(bst1) != dummy_itr1 )
	{
		puts("Failes in_2: Begin || End ");
		flag =  TRUE;
	}
	/*printf("size = %lu\n", BstSize(bst1) );*/

	for(i = 0; i <= 10; ++i)
	{
		itr1 = BstInsert(bst1, arr + i);
		/*Aux_Pre_Print_Tree(bst1);*/
		min = MIN(arr[i], min);
		max = MAX(arr[i], max);
		/*printf("min = %d, max = %d \n", min, max);*/
		/*printf(" GetData = %d, \n",  *(int*)BstGetData(itr1) );*/
		/*printf("size = %lu, Iteration = %lu \n", BstSize(bst1) , i);*/
		if(	BstSize(bst1) != (i + 1) )
		{
			printf("Failes in_2: Size || Next || Insert, Iteration = %lu \n", i);
			flag =  TRUE;
		}
		
		if( SortingFunc(BstGetData(BstBegin(bst1) ) , &min ) ) 
		{
			printf("Failes in_2: Insert || Begin Iteration: %lu \n", i);
			flag =  TRUE;
		}
		
		if( SortingFunc(BstGetData(BstPrev(dummy_itr1) ) , &max ) )
		{
			printf("Failes in_2: Insert || Prev Iteration: %lu \n", i);
			flag =  TRUE;
		}
	
	}
	
	/*Aux_Pre_Print_Tree(bst1, 0);*/
	
	itr3 = BstFind(bst1, arr + 3); /* 85 */
	itr2 = BstFind(bst1, arr); /* 100 (root) */
	/*printf(" GetData_itr3 = %d, \n",  *(int*)BstGetData(itr3) );*/
	
	if(SortingFunc(BstGetData(itr3)  ,arr + 3 )) 
	{
		puts("Failes in_2: Find");
		flag =  TRUE;	
	}
	
	if( TRUE != IsIterSame(itr2 , BstNext(itr3)) )  /* itr3->data == 85 */
	{
		puts("Failes in_2: Next");
		flag =  TRUE;	
	}
	
	if( TRUE != IsIterSame(dummy_itr1 , BstNext(itr1)) ) /* itr1->data == 150 */
	{
		puts("Failes in_3: Next");
		flag =  TRUE;	
	}
	itr4 = BstNext(itr1);
	itr5 = BstBegin(bst1);
	/* || SUCCESS != BstForEach(BstPrev(itr4), itr4, SortingFunc, arr_sort + 10 - i) */
	for( i = 0; i <= 10; ++i)
	{
		
		/*printf(" GetData_itr4 = %d, \n",  *(int*)BstGetData(itr4) );*/
			/*printf(" GetData_BstNext(itr5) = %d, \n",  *(int*)BstGetData(BstNext(itr5)) );*/
		if( SUCCESS != BstForEach(itr5, BstNext(itr5), SortingFunc, arr_sort + i)
			|| SUCCESS != BstForEach(BstPrev(itr4), itr4, SortingFunc, arr_sort + 10 - i) )  
		{

			printf("Iteration = %lu \n",  i);
			puts("Failes in_3: ForEach || Next || Prev");
			flag =  TRUE;
	
		}
		itr5 = BstNext(itr5);
		/*itr2 = BstNext(itr2);*/
		itr4 = BstPrev(itr4);
	
	} 
	
	/*Aux_Pre_Print_Tree(bst1, 0);*/	
	
	BstDestroy(bst1);
	bst1 = NULL;
	
	if( OPERATION_FAIL == destroy_check )
	{
		puts("Failes in_1: Destroy || Remove ");
		flag =  TRUE;
	}
	/*printf("destroy_check = %d\n", destroy_check);*/
	/*BstFind*/
	/*itr1 = BstInsert(bst1, arr);*/

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
		
/*******************SortingFunc*********************/
static int SortingFunc(void* check_data , void* new_data)
{
	return (*(int*)check_data - *(int*)new_data);
}

	/*itr1 = BstInsert(bst1, arr);*/
	/* SortingFunc(BstGetData(itr1) ,BstGetData(BstBegin(bst1))) */
	/* BstSize(bst1) != 1 || */
	/* BstIsEmpty(bst1)  */
	/* *arr != *(int*)BstGetData(BstBegin(bst1)) */
	/*printf("size = %lu\n", BstSize(bst1) );*/
	/*
	if( SortingFunc(BstGetData(itr1) ,BstGetData(BstBegin(bst1)))  
	     || BstSize(bst1) != 1 || BstIsEmpty(bst1) )
		 
	{
		puts("Failes in_1: Insert || Begin || GetData || Size || IsEmpty");
		flag =  TRUE;
	}
	
	if( itr1 != BstPrev(dummy_itr1) || dummy_itr1 != BstPrev(itr1) )
	{
		puts("Failes in_1: Prev");
		flag =  TRUE;	
	}
	
	if( dummy_itr1 != BstNext(dummy_itr1) || dummy_itr1 != BstNext(itr1) )
	{
		puts("Failes in_1: Next");
		flag =  TRUE;	
	}
	
	if( itr1 != BstFind(bst1, arr) || dummy_itr1 != BstFind(bst1, arr + 1) 
		|| dummy_itr1 != BstFind(bst1, arr + 2) )
	{
		puts("Failes in_1: Find");
		flag =  TRUE;	
	}
	
	if( TRUE != IsIterSame(itr1, itr1) || 
		FALSE != IsIterSame(itr1, dummy_itr1) )
	{
		puts("Failes in_1: IsIterSame");
		flag =  TRUE;
	} 
	
	if( SUCCESS != BstForEach(itr1, dummy_itr1, SortingFunc, arr) || 
		OPERATION_FAIL != BstForEach(itr1, dummy_itr1, SortingFunc, arr + 1) )
	{
		puts("Failes in_1: ForEach");
		flag =  TRUE;
	
	} 
	
	if( dummy_itr1 != BstRemove(itr1) || BstSize(bst1) != 0 )
	{
		puts("Failes in_1: Remove || Size");
		flag =  TRUE;	
	}
	*/
	
	
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


/*
puts("\n" BACK_CYAN"Ratio time:"RESET"\n");
	printf("BubbleSort/QuickSort   : "BACK_GREEN" %f "RESET" \n", \
           t_bubble/t_qsort);
           
*/           
