/***************************************
* Author : Natty
* Reviewer : 
* Date : 15 / 02 / 2025
* Last update: 15 / 02 / 2025
*****************************************/

#include <stdio.h> 		/* printf, puts, qsort  */
#include <assert.h>
#include <string.h> 	/* strcpy, strcmp */

#include "avl.h" 

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

extern int destroy_check_avl;

/***************struct and enum declaration *******/

/** possible return values **/
typedef enum
{
	
	SUCCESS = 0,
	OPERATION_FAIL = 1
	
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
static void TestAvlOneNode(void);
/*
static void TestAvlTwoeNode(void);
*/
static int SortingFunc(const void* check_data ,const void* new_data);

/***************************End of function declaration******************/

/******************static functions definition**********************/
		
/*******************SortingFunc*********************/
static int SortingFunc(const void* check_data ,const void* new_data)
{
	return (*(int*)check_data - *(int*)new_data);
}
/*******************Compare*********************/
static int Compare(void* check_data , void* new_data)
{
	return !(SUCCESS == (*(int*)check_data - *(int*)new_data));
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
   	puts(BACK_BLUE"'TestAvlOneNode()'"RESET);
    TestAvlOneNode();
       /*
 	puts(BLUE"====================================================="RESET);  	
   	puts(BACK_BLUE"'TestAvlTwoeNode()'"RESET);
    TestAvlTwoeNode();
    */
	puts(BLUE"====================================================="RESET);

	return 0;
}


/********************  TestAvlOneNode  ****************************/
static void TestAvlOneNode(void)
{	
	int flag = FALSE;

	int arr[11] = {100, 70, 110, 85, 80, 75 ,65 , 67, 130, 30, 150};
	size_t i = 0;
		
	avl_t *avl1 = AVLCreate(SortingFunc);

	/*puts(RED);*/

	if( !AVLIsEmpty(avl1) ) 
	{
		puts("Failes in_1: IsEmpty");
		flag =  TRUE;
	}
	
	for(i = 0; i <= 10; ++i)
	{
		flag = AVLInsert(avl1, arr + i);
		
		if( flag )
		{
			puts("Failes in_1: Insert");
			flag =  TRUE;
		}

	}
	Aux_Pre_Print_Tree_Avl(avl1, 0);
	/*Aux_Pre_Print_Tree_Avl(avl1, 0);*/
	
	/*flag = AVLInsert(avl1, arr);*/
		/*Aux_Pre_Print_Tree_Avl(avl1, 0);*/
	/*AvlPrintData( AvlGetData );	*/
	/*
	if( SortingFunc(avlGetData(itr1) ,avlGetData(avlBegin(avl1)))  
	     || avlSize(avl1) != 1 || avlIsEmpty(avl1) )
		 
	{
		puts("Failes in_1: Insert || Begin || GetData || Size || IsEmpty");
		flag =  TRUE;
	}
	*/
	/*flag = AVLInsert(avl1, arr + 1);*/

	AVLDestroy(avl1);
	avl1 = NULL;
	
	if( OPERATION_FAIL == destroy_check_avl )
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
	
	/*
	if( avlSize(avl1) != 0 )  
	{
		puts("Failes in_1: Size");
		flag =  TRUE;
	}
	*/
	/*
	dummy_itr1 = avlBegin(avl1);
	*/
	/*
	if( avlEnd(avl1) != dummy_itr1 )
	{
		puts("Failes in_1: Begin || End ");
		flag =  TRUE;
	}
	
	itr1 = avlInsert(avl1, arr);
	if( SortingFunc(avlGetData(itr1) ,avlGetData(avlBegin(avl1)))  
	     || avlSize(avl1) != 1 || avlIsEmpty(avl1) )
		 
	{
		puts("Failes in_1: Insert || Begin || GetData || Size || IsEmpty");
		flag =  TRUE;
	}
	
	if( itr1 != avlPrev(dummy_itr1) || dummy_itr1 != avlPrev(itr1) )
	{
		puts("Failes in_1: Prev");
		flag =  TRUE;	
	}
	
	if( dummy_itr1 != avlNext(dummy_itr1) || dummy_itr1 != avlNext(itr1) )
	{
		puts("Failes in_1: Next");
		flag =  TRUE;	
	}
	
	if( itr1 != avlFind(avl1, arr) || dummy_itr1 != avlFind(avl1, arr + 1) 
		|| dummy_itr1 != avlFind(avl1, arr + 2) )
	{
		puts("Failes in_1: Find");
		flag =  TRUE;	
	}
	
	if( TRUE != avlIsIterSame(itr1, itr1) || 
		FALSE != avlIsIterSame(itr1, dummy_itr1) )
	{
		puts("Failes in_1: avlIsIterSame");
		flag =  TRUE;
	} 
	
	if( SUCCESS != avlForEach(itr1, dummy_itr1, Compare, arr) || 
		OPERATION_FAIL != avlForEach(itr1, dummy_itr1, Compare, arr + 1) )
	{
		puts("Failes in_1: ForEach");
		flag =  TRUE;
	
	} 
	
	if( dummy_itr1 != avlRemove(itr1) || avlSize(avl1) != 0 )
	{
		puts("Failes in_1: Remove || Size");
		flag =  TRUE;	
	}
	
	itr1 = avlInsert(avl1, arr);
	*/  
	
/********************  TestavlOneNode  ****************************/
/*
static void TestavlTwoeNode(void)
{	
	int arr[11] = {100, 70, 110, 85, 80, 75 ,65 , 67, 130, 30, 150};
	int arr_sort[11] = {30, 65, 67, 70, 75, 80, 85 ,100 , 110, 130, 150};
	int to_insert[10] = { 76 }; 
	
	int* data = NULL;
	
	int flag = FALSE, max = arr[0], min = arr[0];
	size_t i = 0;

	avl_iter_t dummy_itr1;
	avl_iter_t itr1;
	avl_iter_t itr2;
	avl_iter_t itr3;
	avl_iter_t itr4;
	avl_iter_t itr5;
	avl_iter_t itr6;
	avl_iter_t itr7;
	
	avl_t *avl1 = avlCreate(SortingFunc);	
	puts(RED);

	if( !avlIsEmpty(avl1) )  
	{

		puts("Failes in_2: IsEmpty");
		flag =  TRUE;
	}
	
	if( avlSize(avl1) != 0 )  
	{
		puts("Failes in_2: Size");
		flag =  TRUE;
	}
	
	dummy_itr1 = avlBegin(avl1);
	
	if( avlEnd(avl1) != dummy_itr1 )
	{
		puts("Failes in_2: Begin || End ");
		flag =  TRUE;
	}

	for(i = 0; i <= 10; ++i)
	{
		itr1 = avlInsert(avl1, arr + i);
		min = MIN(arr[i], min);
		max = MAX(arr[i], max);
		
		if(	avlSize(avl1) != (i + 1) )
		{
			printf("Failes in_2: Size || Next || Insert, Iteration = %lu \n", i);
			flag =  TRUE;
		}
		
		if( SortingFunc(avlGetData(avlBegin(avl1) ) , &min ) ) 
		{
			printf("Failes in_2: Insert || Begin Iteration: %lu \n", i);
			flag =  TRUE;
		}
		
		if( SortingFunc(avlGetData(avlPrev(dummy_itr1) ) , &max ) )
		{
			printf("Failes in_2: Insert || Prev Iteration: %lu \n", i);
			flag =  TRUE;
		}
	}
	
	*/
	/*Aux_Pre_Print_Tree(avl1, 0);*/
	
	/*itr3 = avlFind(avl1, arr + 3);*/ /* 85 */
/*	itr2 = avlFind(avl1, arr); *//* 100 (root) */
/*
	if(SortingFunc(avlGetData(itr3)  ,arr + 3 )) 
	{
		puts("Failes in_2: Find");
		flag =  TRUE;	
	}
	*/
	/*
	if( TRUE != avlIsIterSame(itr2 , avlNext(itr3)) )   itr3->data == 85 
	{
		puts("Failes in_2: Next");
		flag =  TRUE;	
	}
	*/
	/*
	if( TRUE != avlIsIterSame(dummy_itr1 , avlNext(itr1)) )  itr1->data == 150 
	{
		puts("Failes in_3: Next");
		flag =  TRUE;	
	}
	
	*/
	
/*	itr4 = avlNext(itr1);*/ /* itr4->data == end->data*/
	/*itr5 = avlBegin(avl1);*/ /* itr5->data == 30*/
	/*
	for( i = 0; i <= 10; ++i)
	{	
		if( SUCCESS != avlForEach(itr5, avlNext(itr5), Compare, arr_sort + i)
			|| SUCCESS != avlForEach(avlPrev(itr4), itr4, Compare, arr_sort + 10 - i) )  
		{

			printf("Iteration = %lu \n",  i);
			puts("Failes in_3: ForEach || Next || Prev");
			flag =  TRUE;
	
		}
		itr5 = avlNext(itr5);
		itr4 = avlPrev(itr4);
	
	} 
	*/
	/*Aux_Pre_Print_Tree(avl1, 0);*/
	/*itr5 = avlPrev(itr5);*/ /* the Prev result: itr5->data == 150 */
	/*itr6 = avlFind(avl1, arr_sort + 9);*/ /*itr6->data == 130  */
	/*itr6 = avlRemove(itr6);*/ /* the node (itr6) has one child */
	/*itr7 = avlFind(avl1, arr_sort + 8); *//*itr7->data == 110  */
	/*
	if( !avlIsIterSame(itr6, itr5) || avlSize(avl1) != 10 || 
		!avlIsIterSame(itr6, avlNext(itr7)) || !avlIsIterSame(avlPrev(itr6), itr7) )
	{
		puts("Failes in_3 - One child case: Remove ");
		flag =  TRUE;
	}
	*/	
	/*Aux_Pre_Print_Tree(avl1, 0);*/
	/*itr1 = avlInsert(avl1, to_insert);*/ /* itr1->data == 76*/
	/*
	if ( avlSize(avl1) != 11)
	{
		puts("Failes in_3: Insert");
		flag =  TRUE;
	}
	*/
	/*itr3 = avlFind(avl1, arr_sort + 3); *//*itr3->data == 70 */
	/*itr4 = avlNext(itr3);*/ /*itr4->data == 75 */
	
	/*data = avlGetData(itr4); *//* 75 */
	
	/*itr5 = avlNext(itr4); *//*itr5->data == 76 */
	/*itr6 = avlNext(itr5); *//*itr6->data == 80 */
	
	/*Aux_Pre_Print_Tree(avl1, 0);*/
		
	/*itr3 = avlRemove(itr3); *//* the node (itr3) has two childs */
	/*After remove: itr3->data == 75 */
/*
	if( SortingFunc(avlGetData(itr3), data) ||
		!avlIsIterSame(avlNext(itr3), itr5) || avlSize(avl1) != 10 )
	{
		puts("Failes in_4 - Two childs case: Remove ");
		flag =  TRUE;
	}
*/	
	/*data = avlGetData(avlNext(itr3)); *//* 76 */
	/*itr3 = avlRemove(itr3); *//* itr3->data == 75, the node has two childs */
/*
	if( SortingFunc(avlGetData(itr3), data) ||
		!avlIsIterSame(avlNext(itr3), itr6) || avlSize(avl1) != 9 )
	{
		puts("Failes in_5 - Two childs case: Remove ");
		flag =  TRUE;
	}
*/	
	/*itr2 = avlFind(avl1, arr); *//* itr2->data == 100 ,  (root) */
	/*data = avlGetData(avlNext(itr2));*//* 110 */
	/*itr3 = avlNext(avlNext(itr2)); *//* itr2->data == 150 */
	/*itr2 = avlRemove(itr2);*//* the node has two childs */
	/*
	if( SortingFunc(avlGetData(itr2), data) ||
		!avlIsIterSame(avlNext(itr2), itr3) || avlSize(avl1) != 8 )
	{
		puts("Failes in_5 - Two childs case: Remove ");
		flag =  TRUE;
	}
	*/
	/*itr2 = avlFind(avl1, arr_sort + 2); *//* itr2->data == 67 ,   */
	/*itr2 = avlRemove(itr2);*/ /* the node has two childs */
	/*
	if( SortingFunc(avlGetData(itr2), to_insert) || avlSize(avl1) != 7 )
	{
		puts("Failes in_6 - Two childs case: Remove ");
		flag =  TRUE;
	}
	*/
	/*itr2 = avlFind(avl1, to_insert);*/ /* itr2->data == 76 ,   */
	/*itr2 = avlRemove(itr2);*//* the node has two childs */
	/*
	if( SortingFunc(avlGetData(itr2), arr_sort + 5) || avlSize(avl1) != 6 )
	{
		puts("Failes in_7 - Two childs case: Remove ");
		flag =  TRUE;
	}

	itr1 = avlInsert(avl1, to_insert);
	avlDestroy(avl1);
	avl1 = NULL;
	
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
*/

