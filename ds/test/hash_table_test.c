/***************************************
* Author : Natty
* Reviewer : 
* Date : 15 / 02 / 2025
* Last update: 15 / 02 / 2025
*****************************************/

#include <stdio.h> 		/* printf, puts, qsort  */
#include <assert.h>
#include <string.h> 	/* strcpy, strcmp */

#include "hash_table.h" 

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
/*
struct person
{
  size_t key;
  int data;
}person_t;
*/

typedef enum
{
	SUCCESS = 0,
	OPERATION_FAIL = 1
	
}hash_result_t;

typedef enum
{
	
	FALSE = 0,
	TRUE = 1
	
}func_result_t;



/*
	#ifdef PRINTS
		Aux_Pre_Print_Tree(avl1, 0);
	#endif
*/
/***************End of struct and enum declaration *******/

/***************************function declaration**************************/
static void TestHash(void);
size_t HashFunction(const void* key);
/*
static int SortingFunc(const void* check_data ,const void* new_data);
*/
/***************************End of function declaration******************/

/******************static functions definition**********************/
		
/*******************SortingFunc*********************/
/*
static int SortingFunc(const void* check_data ,const void* new_data)
{
	return (*(int*)check_data - *(int*)new_data);
}
*/
/*******************Compare*********************/

static int Compare(void* check_data , void* new_data)
{
	return (SUCCESS == (*(int*)check_data - *(int*)new_data));
}

/*******************Compare2*********************/
/*
static int Compare2(void* check_data , void* new_data)
{
	return  ( *(int*)check_data >= *(int*)new_data );
}
*/
/*******************hashFunction*********************/
size_t HashFunction(const void* key)
{
  return (*(size_t*)key) / 9;
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
   	puts(BACK_BLUE"'TestHash()'"RESET);
    TestHash();
       /*
 	puts(BLUE"====================================================="RESET);  	
   	puts(BACK_BLUE"'TestAvlTwoeNode()'"RESET);
    TestAvlTwoeNode();
    */
	puts(BLUE"====================================================="RESET);

	return 0;
}


/********************  TestHash  ****************************/
static void TestHash(void)
{	
	int flag = FALSE;
	/*struct set *array;*/
	hash_table_t *table1 = NULL;

	/*size_t size = 0;*/
	size_t capacity = 10;
	int ages[10] = {1, 10, 20, 30, 30, 40 ,50 , 60, 70, 80};
	capacity = sizeof(ages)/sizeof(ages[0]);
	/*puts(RED);*/

	table1 = HashTableCreate(HashFunction, Compare, capacity);
	if ( !table1 )
	{
		puts("Failes in_1: HashTableCreate - Allocation");
	}

	if( !HashTableIsEmpty(table1) ) 
	{
		puts("Failes in_1: IsEmpty");
		flag =  TRUE;
	}

	if( 0 != HashTableSize(table1) )
	{
		
		puts("Failes in_1: Size");
		flag =  TRUE;
	
	}

	HashTableDestroy(table1);

	table1 = NULL;
	
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
	avl_t *avl1 = AVLCreate(SortingFunc);
*/
	/*puts(RED);*/
/*
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
			puts("Failes in_1: Insert Allocation failed ");
			flag =  TRUE;
		}

	}

	
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
*/
	/*AVLRemove(avl1, arr + 1  ); */
	
/*
	Aux_Pre_Print_Tree_Avl(avl1, 0);
*/	
	/*
	if( 4 != AVLHeight(avl1) )
	{
		puts("Failes in_2: Insert");
		flag =  TRUE;
	
	}
	*/
	/*printf("size = %lu \n", AVLSize(avl1));*/
	/*
	if( 11 != AVLSize(avl1) )
	{
		
		puts("Failes in_1: Size");
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
	
	if( SUCCESS != AVLForEachInOrder(avl1, Compare2, foreach , PRE_ORDER)
		|| OPERATION_FAIL != AVLForEachInOrder(avl1, Compare2, foreach + 1, PRE_ORDER) )  
	{

		puts("Failes in_1: ForEachPreOrder");
		flag =  TRUE;
	}
		
	if( SUCCESS != AVLForEachInOrder(avl1, Compare2, foreach , POST_ORDER)
		|| OPERATION_FAIL != AVLForEachInOrder(avl1, Compare2, foreach + 1, POST_ORDER) )  
	{
		puts("Failes in_2: ForEachPostOrder");
		flag =  TRUE;
	}
		
	if( SUCCESS != AVLForEachInOrder(avl1, Compare2, foreach , IN_ORDER)
		|| OPERATION_FAIL != AVLForEachInOrder(avl1, Compare2, foreach + 1, IN_ORDER) )  
	{

		puts("Failes in_3: ForEachInOrder");
		flag =  TRUE;
	}
	
	if( 11 != AVLSize(avl1) )
	{
		
		puts("Failes in_3: Size");
		flag =  TRUE;
	
	}
	
	
	AVLRemove(avl1, arr + 9); 
	

	
	if( 10 != AVLSize(avl1) )
	{
		
		puts("Failes in_4: Size");
		flag =  TRUE;
	
	}
	
	*/
	
	/*
	if( 11 != AVLSize(avl1) )
	{
		
		puts("Failes in_4: Size");
		flag =  TRUE;
	
	}
	Aux_Pre_Print_Tree_Avl(avl1, 0);
	
	AVLRemove(avl1, arr + 1); 
	
	if( 10 != AVLSize(avl1) )
	{
		
		puts("Failes in_5: Size");
		flag =  TRUE;
	
	}
	*/
	/*
	if( 11 != AVLSize(avl1) )
	{
		
		puts("Failes in_3: Size");
		flag =  TRUE;
	
	}
		
	Aux_Pre_Print_Tree_Avl(avl1, 0);
	AVLRemove(avl1, arr + 4); 
	
	if( 10 != AVLSize(avl1) )
	{
		
		puts("Failes in_4: Size");
		flag =  TRUE;
	
	}
	*/
	/*Aux_Pre_Print_Tree_Avl(avl1, 0);*/
	
	
	
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

