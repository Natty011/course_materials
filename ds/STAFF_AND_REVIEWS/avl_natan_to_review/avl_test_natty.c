/***************************************
* Author : Natty
* Reviewer : 
* Date : 15 / 02 / 2025
* Last update: 15 / 02 / 2025
*****************************************/

#include <stdio.h> 		/* printf, puts, qsort  */
#include <assert.h>
#include <string.h> 	/* strcpy, strcmp */
#include <math.h> 	

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
static int SortingFunc(void* check_data ,void* new_data);

/***************************End of function declaration******************/

/******************static functions definition**********************/
		
/*******************SortingFunc*********************/
static int SortingFunc(void* check_data ,void* new_data)
{
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
/*110*/
	int arr[11] = {100, 70, 110, 85, 80, 75 ,
				65 , 67, 130, 30, 150};
	/*int arr2[11] = {100, 70, 80, 85, 80, 75 ,65 , 67, 130, 30, 150};*/
	size_t i = 0;
	int foreach[2] = {151, 150};
		
	avl_t *avl1 = AVLCreate(SortingFunc);

	/*puts(RED);*/

	if( !AVLIsEmpty(avl1) ) 
	{
		printf("line: %d \n" , __LINE__ );	 
		puts("Failes in_1: IsEmpty");
		flag =  TRUE;
	}
	
	for(i = 0; i <= 10; ++i)
	{
		flag = AVLInsert(avl1, arr + i);
		
		if( flag )
		{
			printf("line: %d \n" , __LINE__ );	 
			puts("Failes in_1: Insert Allocation failed ");
			flag =  TRUE;
		}

	}

	#ifdef PRINTS	
		puts("************AvlInsert***********");
		PrintTree(avl1);
	#endif
	
	if( 11 != AVLSize(avl1) || 3 != AVLHeight(avl1) )
	{
		printf("line: %d \n" , __LINE__ );	 		
		puts("Failes in_1: Size || Height");
		flag =  TRUE;
	
	}
	
	
	for(i = 0; i <= 10; ++i)
	{
		flag = Compare(AVLFind(avl1, arr + i), arr + i);
		
		if( flag )
		{
			printf("line: %d \n" , __LINE__ );	 
			printf("Failes in_1: Find, i = %lu \n", i);
			flag =  TRUE;
		}

	}
	
	if( SUCCESS != AVLForEach(avl1, Compare2, foreach , PRE_ORDER)
		|| OPERATION_FAIL != AVLForEach(avl1, Compare2, foreach + 1, PRE_ORDER) )  
	{
		printf("line: %d \n" , __LINE__ );	 
		puts("Failes in_1: ForEachPreOrder");
		flag =  TRUE;
	}
		
	if( SUCCESS != AVLForEach(avl1, Compare2, foreach , POST_ORDER)
		|| OPERATION_FAIL != AVLForEach(avl1, Compare2, foreach + 1, POST_ORDER) )  
	{
		printf("line: %d \n" , __LINE__ );	 
		puts("Failes in_2: ForEachPostOrder");
		flag =  TRUE;
	}
		
	if( SUCCESS != AVLForEach(avl1, Compare2, foreach , IN_ORDER)
		|| OPERATION_FAIL != AVLForEach(avl1, Compare2, foreach + 1, IN_ORDER) )  
	{
		printf("line: %d \n" , __LINE__ );	 
		puts("Failes in_3: ForEachInOrder");
		flag =  TRUE;
	}
	
	
	/*30 */

	AVLRemove(avl1, arr + 9); 
	
	if( 10 != AVLSize(avl1) || 3 != AVLHeight(avl1))
	{
		printf("line: %d \n" , __LINE__ );	 		
		puts("Failes in_4: Size || Height || Remove"  );
		flag =  TRUE;
	
	}
	#ifdef PRINTS	
		puts("************Remove 30***********");
		PrintTree(avl1);
	#endif

		/*70 */

	AVLRemove(avl1, arr + 1); 
	
	if( 9 != AVLSize(avl1) || 3 != AVLHeight(avl1))
	{
		printf("line: %d \n" , __LINE__ );	 		
		puts("Failes in_5: Size || Height || Remove");
		flag =  TRUE;
	
	}
	
	#ifdef PRINTS	
		puts("************Remove 70***********");
		PrintTree(avl1);
	#endif

	/*80 */
	AVLRemove(avl1, arr + 4); 
	
	if( 8 != AVLSize(avl1) || 3 != AVLHeight(avl1))
	{
		printf("line: %d \n" , __LINE__ );	 		
		puts("Failes in_6: Size || Height || Remove");
		flag =  TRUE;
	
	}
	
	#ifdef PRINTS	
		puts("************Remove 80***********");
		PrintTree(avl1);
	#endif

	/*100 */
	AVLRemove(avl1, arr + 0  );

	if( 7 != AVLSize(avl1) || 2 != AVLHeight(avl1))
	{
		printf("line: %d \n" , __LINE__ );	 		
		puts("Failes in_7: Size || Height || Remove");
		flag =  TRUE;
	
	}
	
	#ifdef PRINTS	
		puts("************Remove 100***********");
		PrintTree(avl1);
	#endif
	/*110 */

	AVLRemove(avl1, arr + 2  );
	
	if( 6 != AVLSize(avl1) || 2 != AVLHeight(avl1))
	{
		printf("line: %d \n" , __LINE__ );	 		
		puts("Failes in_8: Size || Height || Remove");
		flag =  TRUE;
	
	}
	#ifdef PRINTS	
		puts("************Remove 110***********");
		PrintTree(avl1);
	#endif

	/*85 */
	AVLRemove(avl1, arr + 3  );

	if( 5 != AVLSize(avl1) || 2 != AVLHeight(avl1))
	{
		printf("line: %d \n" , __LINE__ );	 		
		puts("Failes in_9: Size || Height || Remove");
		flag =  TRUE;
	
	}
	
	#ifdef PRINTS	
		puts("************Remove 85***********");
		PrintTree(avl1);
	#endif
	/*do not exist  */
	AVLRemove(avl1, arr + 4  );

	if( 5 != AVLSize(avl1) || 2 != AVLHeight(avl1))
	{
		printf("line: %d \n" , __LINE__ );	 		
		puts("Failes in_10: Size || Height || Remove");
		flag =  TRUE;
	
	}
	#ifdef PRINTS	
		puts("************Remove 80 - do not exist  ***********");
		PrintTree(avl1);
	#endif
	/*150 */
	AVLRemove(avl1, arr + 10  );
	if( 4 != AVLSize(avl1) || 2 != AVLHeight(avl1))
	{
		printf("line: %d \n" , __LINE__ );	 		
		puts("Failes in_11: Size || Height || Remove");
		flag =  TRUE;
	
	}
	
	#ifdef PRINTS	
		puts("************Remove 150***********");
		PrintTree(avl1);
	#endif

   /*65 */
  AVLRemove(avl1, arr + 6  );
  if( 3 != AVLSize(avl1) || 1 != AVLHeight(avl1))
  {
		printf("line: %d \n" , __LINE__ );	 	
		puts("Failes in_12: Size || Height || Remove");
		flag =  TRUE;

  }
  
  #ifdef PRINTS	
		puts("************Remove 65***********");
		PrintTree(avl1);
  #endif

   /*75 */
   AVLRemove(avl1, arr + 5  );
   if( 2 != AVLSize(avl1) || 1 != AVLHeight(avl1))
   {
		printf("line: %d \n" , __LINE__ );	 
		puts("Failes in_13: Size || Height || Remove ");
	 	flag =  TRUE;
 
   }

	#ifdef PRINTS	
		puts("************Remove 75***********");
		PrintTree(avl1);
  	#endif
	
	AVLDestroy(avl1);
	avl1 = NULL;
	
	
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
	
