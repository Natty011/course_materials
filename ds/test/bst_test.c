/***************************************
* Author : Natty
* Reviewer : Matan
* Date : 22 / 01 / 2025
* Last update: 01 / 02 / 2025
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
		Aux_Pre_Print_Tree(bst1, 0);
	#endif
*/
/***************End of struct and enum declaration *******/

/***************************function declaration**************************/
static void TestBstOneNode(void);
static void TestBstTwoeNode(void);
static int SortingFunc(void* check_data , void* new_data);

/***************************End of function declaration******************/

/******************static functions definition**********************/
		
/*******************SortingFunc*********************/
static int SortingFunc(void* check_data , void* new_data)
{
	return (*(int*)check_data - *(int*)new_data);
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
	puts(RED);

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
	int to_insert[10] = { 76 }; 
	
	int* data = NULL;
	
	int flag = FALSE, max = arr[0], min = arr[0];
	size_t i = 0;

	bst_iter_t dummy_itr1;
	bst_iter_t itr1;
	bst_iter_t itr2;
	bst_iter_t itr3;
	bst_iter_t itr4;
	bst_iter_t itr5;
	bst_iter_t itr6;
	bst_iter_t itr7;
	
	bst_t *bst1 = BstCreate(SortingFunc);	
	puts(RED);

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

	for(i = 0; i <= 10; ++i)
	{
		itr1 = BstInsert(bst1, arr + i);
		min = MIN(arr[i], min);
		max = MAX(arr[i], max);
		
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
	
	itr4 = BstNext(itr1); /* itr4->data == end->data*/
	itr5 = BstBegin(bst1); /* itr5->data == 30*/
	for( i = 0; i <= 10; ++i)
	{	
		if( SUCCESS != BstForEach(itr5, BstNext(itr5), SortingFunc, arr_sort + i)
			|| SUCCESS != BstForEach(BstPrev(itr4), itr4, SortingFunc, arr_sort + 10 - i) )  
		{

			printf("Iteration = %lu \n",  i);
			puts("Failes in_3: ForEach || Next || Prev");
			flag =  TRUE;
	
		}
		itr5 = BstNext(itr5);
		itr4 = BstPrev(itr4);
	
	} 
	/*Aux_Pre_Print_Tree(bst1, 0);*/
	itr5 = BstPrev(itr5); /* the Prev result: itr5->data == 150 */
	itr6 = BstFind(bst1, arr_sort + 9); /*itr6->data == 130  */
	itr6 = BstRemove(itr6); /* the node (itr6) has one child */
	itr7 = BstFind(bst1, arr_sort + 8); /*itr7->data == 110  */
	
	if( !IsIterSame(itr6, itr5) || BstSize(bst1) != 10 || 
		!IsIterSame(itr6, BstNext(itr7)) || !IsIterSame(BstPrev(itr6), itr7) )
	{
		puts("Failes in_3 - One child case: Remove ");
		flag =  TRUE;
	}
		
	/*Aux_Pre_Print_Tree(bst1, 0);*/
	itr1 = BstInsert(bst1, to_insert); /* itr1->data == 76*/
	if ( BstSize(bst1) != 11)
	{
		puts("Failes in_3: Insert");
		flag =  TRUE;
	}
	
	itr3 = BstFind(bst1, arr_sort + 3); /*itr3->data == 70 */
	itr4 = BstNext(itr3); /*itr4->data == 75 */
	
	data = BstGetData(itr4); /* 75 */
	
	itr5 = BstNext(itr4); /*itr5->data == 76 */
	itr6 = BstNext(itr5); /*itr6->data == 80 */
	
	/*Aux_Pre_Print_Tree(bst1, 0);*/
		
	itr3 = BstRemove(itr3); /* the node (itr3) has two childs */
	/*After remove: itr3->data == 75 */

	if( SortingFunc(BstGetData(itr3), data) ||
		!IsIterSame(BstNext(itr3), itr5) || BstSize(bst1) != 10 )
	{
		puts("Failes in_4 - Two childs case: Remove ");
		flag =  TRUE;
	}
	
	data = BstGetData(BstNext(itr3)); /* 76 */
	itr3 = BstRemove(itr3); /* itr3->data == 75, the node has two childs */

	if( SortingFunc(BstGetData(itr3), data) ||
		!IsIterSame(BstNext(itr3), itr6) || BstSize(bst1) != 9 )
	{
		puts("Failes in_5 - Two childs case: Remove ");
		flag =  TRUE;
	}
	
	itr2 = BstFind(bst1, arr); /* itr2->data == 100 ,  (root) */
	data = BstGetData(BstNext(itr2)); /* 110 */
	itr3 = BstNext(BstNext(itr2)); /* itr2->data == 150 */
	itr2 = BstRemove(itr2); /* the node has two childs */
	
	if( SortingFunc(BstGetData(itr2), data) ||
		!IsIterSame(BstNext(itr2), itr3) || BstSize(bst1) != 8 )
	{
		puts("Failes in_5 - Two childs case: Remove ");
		flag =  TRUE;
	}
	
	itr2 = BstFind(bst1, arr_sort + 2); /* itr2->data == 67 ,   */
	itr2 = BstRemove(itr2); /* the node has two childs */
	if( SortingFunc(BstGetData(itr2), to_insert) || BstSize(bst1) != 7 )
	{
		puts("Failes in_6 - Two childs case: Remove ");
		flag =  TRUE;
	}
	
	itr2 = BstFind(bst1, to_insert); /* itr2->data == 76 ,   */
	itr2 = BstRemove(itr2); /* the node has two childs */
	if( SortingFunc(BstGetData(itr2), arr_sort + 5) || BstSize(bst1) != 6 )
	{
		puts("Failes in_7 - Two childs case: Remove ");
		flag =  TRUE;
	}

	itr1 = BstInsert(bst1, to_insert);
	BstDestroy(bst1);
	bst1 = NULL;
	
	if( OPERATION_FAIL == destroy_check )
	{
		puts("Failes in_2: Destroy || Remove ");
		flag =  TRUE;
	}

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


