/***************************************
* Author : Natty
* Reviewer : Natan / gilad( HeapSort )
* Date : 22 / 01 / 2025
* Last update: 25 / 02 / 2025
*****************************************/

#include <stdio.h> 		/* printf, puts, qsort  */
#include <assert.h>
#include <stdlib.h> /* rand */
#include <time.h> /* clock */

#include "sort.h" 

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

#define MAX 		5000
#define MIN 		1

/***************struct and enum declaration *******/

typedef enum state
{
	FALSE = 0,
	TRUE = 1
}state_t;
/*
typedef struct sort_time_req
{
    clock_t time_bubble;
    clock_t time_insertion;
    clock_t time_selectionn;   
    clock_t time_qsort;
    
}sort_time_req_t;
*/

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
static void TestSort(void);
static void TestSort2(void);
static void TestSort3(void);

static void GenRandArr(int* arr, size_t len, size_t min, size_t max);
int ArrIsSorted(int* arr, size_t len);
static int TestBinarySearchIterative(void);
static int TestBinarySearchRecursive(void);
static int TestMergeSort(void);
static int TestQuickSort(void);
static int TestHeapSort(void);
/*static void PrintArr(int* arr, size_t len);*/
/***************************End of function declaration******************/

/******************static functions definition**********************/

/********************  GenRandArr  ****************************/
/* range [min, max] */
static void GenRandArr(int* arr, size_t len, size_t min, size_t max)
{
	size_t i = 0;
	
	assert(arr);
	srand(time(NULL));	
	for(i = 0 ; i < len; ++i)
	{
		arr[i] = rand() % (max - min) + min;
		
	}
	
}

/********************  ArrIsSorted  ****************************/
int ArrIsSorted(int* arr, size_t len)
{
	size_t i = 0;
	int flag = FALSE; /* sorted */
	
	assert(arr);
	
	for(i = 0; i < len - 1; i++)
	{
		/*	
		printf("arr[i] = %d , i = %lu \n", arr[i], i);
		printf("arr[i + 1] = %d , i + 1 = %lu \n", arr[i + 1], i + 1);	
		*/
		if(arr[i] > arr[i + 1] )
		{
			flag = TRUE; /* not sorted */
			/*break;*/
		}	
		
	}
	
	return flag;
	
}

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
/* For qsort*/
int Compare(const void* a, const void* b)
{
    return (*(int*)a - *(int*)b);
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
	
   	puts(BACK_BLUE"'TestSort()'"RESET);
    TestSort();
    
	puts(BLUE"====================================================="RESET);  
	  
    puts(BACK_BLUE"'TestSort2()'"RESET);
    TestSort2();
    
	puts(BLUE"====================================================="RESET);

	puts(BACK_BLUE"'TestSort3()'"RESET);
    TestSort3();
    
	puts(BLUE"====================================================="RESET);

	return 0;
}


/********************  Test2Block  ****************************/
static void TestSort2(void)
{	
	int flag = FALSE;

	puts("'TestBinarySearchIterative()'");
    flag = TestBinarySearchIterative();
    puts("====================================================="); 	
    
	puts("'TestBinarySearchRecursive()'");
    flag = TestBinarySearchRecursive();
    puts("=====================================================");
    
    puts("'TestMergeSort()'");
    flag = TestMergeSort();
    puts("====================================================="); 	 	
    
	puts("'TestQuickSort()'");
    flag = TestQuickSort();
    puts("====================================================="); 	    
    
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

/*************************************************************/	
/*************************TestSort3***************************/	
/*************************************************************/

static void TestSort3(void)
{	
	int flag = FALSE;

	puts("'TestHeapSort()'");
    flag = TestHeapSort();
    puts("====================================================="); 
	
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


/*************************************************************/	
/*************************TestHeapSort************************/	
/*************************************************************/
static int TestHeapSort(void)
{
	int arr[6] = {45 ,14 ,61 ,37, 56, 22};
	int arr1[6] = {-7 ,5 ,2 , 1, -5, 7};
	size_t size = sizeof(arr)/sizeof(arr[0])  ;
	int flag = FALSE , flag1 = FALSE;
	
	HeapSort(arr, size );
	HeapSort(arr1, size );
	
	flag = ArrIsSorted( arr, size );
	flag1 = ArrIsSorted( arr1, size );
	
	if ( !flag && !flag1 )
	{
		puts(BACK_BLUE"TestQuickSort Successed"RESET);		
	}
	
	else
	{
		puts("TestQuickSort Failed");		
	}
	
	return flag;

}



/******************  TestBinarySearchIterative  ***********************/
static int TestBinarySearchIterative(void)
{
	int arr[4] = {-5, 0, 5, 10};
	size_t size = sizeof(arr)/sizeof(arr[0])  ;
	int flag = FALSE, res = -2 ;
	
	res = BinarySearchIterative(arr, size, 5);
	
	if ( 2 != res )
	{
		puts("TestBinarySearchIterative Failed_1");
		flag = TRUE; 
	}

	res = BinarySearchIterative(arr, size, -6 );
	
	if ( -1 != res )
	{
		puts("TestBinarySearchIterative Failed_2");
		flag = TRUE; 
	}
	
	res = BinarySearchIterative(arr, size, 10 );
	
	if ( 3 != res )
	{
		puts("TestBinarySearchIterative Failed_3");
		flag = TRUE; 
	}
	
	if ( !flag )
	{
		puts(BACK_BLUE"TestBinarySearchIterative Successed"RESET);		
	}
	
	return flag;		
}

/******************  TestBinarySearchRecursive  ***********************/
static int TestBinarySearchRecursive(void)
{
	int arr[4] = {-5, 0, 5, 10};
	size_t size = sizeof(arr)/sizeof(arr[0])  ;
	int flag = FALSE, *res = NULL ;
	
	res = BinarySearchRecursive(arr, size, 5);
	
	if ( 5 != *res )
	{
		puts("TestBinarySearchRecursive Failed_1");
		flag = TRUE; 
	}
	
	res = BinarySearchRecursive(arr, size, -6 );
	
	if ( NULL != res )
	{
		puts("TestBinarySearchRecursive Failed_2");
		flag = TRUE; 
	}
	
	res = BinarySearchRecursive(arr, size, 10 );

	if ( 10 != *res )
	{
		puts("TestBinarySearchRecursive Failed_3");
		flag = TRUE; 
	}
	
	res = BinarySearchRecursive(arr, size, -5);
	
	if ( -5 != *res )
	{
		puts("TestBinarySearchRecursive Failed_4");
		flag = TRUE; 
	}	
	
	if ( !flag )
	{
		puts(BACK_BLUE"TestBinarySearchRecursive Successed"RESET);		
	}
	
	return flag;		
}			 
	
/******************  TestMergeSort  ***********************/
static int TestMergeSort(void)
{
	int arr[6] = {45 ,14 ,61 ,37, 56, 22};
	size_t size = sizeof(arr)/sizeof(arr[0])  ;
	int flag = FALSE, flag_malloc = FALSE ;
	
	flag_malloc = MergeSort(arr, size );
	
	flag = ArrIsSorted( arr, size );
	
	if ( flag_malloc )
	{
		puts("TestMergeSort Failed in Allocation ");
		flag = TRUE; 
	}
	
	if ( !flag )
	{
		puts(BACK_BLUE"TestMergeSort Successed"RESET);		
	}
	
	else
	{
		puts("TestMergeSort Failed");		
	}
	
	return flag;		
}

/******************  TestQuickSort  ***********************/
static int TestQuickSort(void)
{
	int arr[6] = {45 ,14 ,61 ,37, 56, 22};
	int arr1[6] = {-7 ,5 ,2 , 1, -5, 7};
	size_t size = sizeof(arr)/sizeof(arr[0])  ;
	int flag = FALSE ;
	
	QuickSort(arr, size, sizeof(arr[0]) , Compare );
	QuickSort(arr1, size, sizeof(arr[0]) , Compare );
	
	flag = ArrIsSorted( arr, size );
	flag = ArrIsSorted( arr1, size );
	
	if ( !flag )
	{
		puts(BACK_BLUE"TestQuickSort Successed"RESET);		
	}
	
	else
	{
		puts("TestQuickSort Failed");		
	}
	
	return flag;		
}				 
	
/********************  Test2Block  ****************************/
static void TestSort(void)
{	
	int flag = FALSE, flag_bubble = FALSE, flag_insertion = FALSE,
		flag_selection = FALSE, flag_counting = FALSE, flag_radix = FALSE,
		flag_merge = FALSE, flag_my_quick = FALSE;
	int arr[MAX] = { 0 };
	size_t len = MAX;
	
    clock_t time_req_bubble = clock();
    clock_t time_req_insertion = clock();
    clock_t time_req_selection = clock();
    clock_t time_req_qsort = clock();
	clock_t time_req_counting = clock();
	clock_t time_req_radix = clock();
	
	clock_t time_req_merge = clock();
	clock_t time_req_my_quick = clock();
			
	float t_bubble = 0.0, t_insert = 0.0, t_select = 0.0, 
		  t_count = 0.0, t_radix = 0.0, t_qsort = 0.0,
		  t_merge = 0.0, t_my_quick = 0.0;

	/* BubbleSort test	*/    
	GenRandArr(arr, len, MIN, MAX);	
	time_req_bubble = clock();
	BubbleSort(arr, len);
	time_req_bubble = clock() - time_req_bubble;
	flag_bubble  = ArrIsSorted(arr, MAX);
	
	
	/* InsertionSort test	*/    
	GenRandArr(arr, len, MIN, MAX);
	time_req_insertion = clock();
	InsertionSort(arr, len);
	time_req_insertion = clock() - time_req_insertion;
	flag_insertion  = ArrIsSorted(arr, MAX);

	/* SelectionSort test	*/    
	GenRandArr(arr, len, MIN, MAX);
	time_req_selection = clock();
	SelectionSort(arr, len);
	time_req_selection = clock() - time_req_selection;
	flag_insertion  = ArrIsSorted(arr, MAX);

	/* CountingSort test	*/    
	GenRandArr(arr, MAX, 1, 101);
	time_req_counting = clock();
	CountingSort(arr, MAX);
	time_req_counting = clock() - time_req_counting;
	flag_counting  = ArrIsSorted(arr, MAX);

	/* RedixSort test	*/    
	GenRandArr(arr, MAX, 1000000, 2000000);
	time_req_radix = clock();
	RadixSort(arr, MAX);
	time_req_radix = clock() - time_req_radix;
	flag_radix  = ArrIsSorted(arr, MAX);

	/* MergeSort test	*/    
	GenRandArr(arr, len, MIN, MAX);
	time_req_merge = clock();
	MergeSort(arr, len);
	time_req_merge = clock() - time_req_merge;
	flag_merge  = ArrIsSorted(arr, MAX);

	/* QuickSort test	*/    
	GenRandArr(arr, len, MIN, MAX);		
	time_req_my_quick = clock();
	QuickSort(arr, len, sizeof(int), Compare);
	time_req_my_quick = clock() - time_req_my_quick;
	flag_my_quick  = ArrIsSorted(arr, MAX);	
				
	if(flag_bubble || flag_insertion || flag_selection || flag_counting
		 || flag_radix || flag_merge || flag_my_quick)
	{
		puts(RED);
		
		if(flag_bubble)
		{
			puts("Failes in BubbleSort: Unsorted array of numbers");
		}
		
		if(flag_insertion)
		{
			puts("Failes in InsertionSort: Unsorted array of numbers");
		}

		if(flag_selection)
		{
			puts("Failes in SelectionSort: Unsorted array of numbers");
		}
		
		if(flag_counting)
		{
			puts("Failes in CountingSort: Unsorted array of numbers");
		}
		
		if(flag_radix)
		{
			puts("Failes in RedixSort: Unsorted array of numbers");
		}
		
		if(flag_merge)
		{
			puts("Failes in MergeSort: Unsorted array of numbers");
		}
		
		if(flag_my_quick)
		{
			puts("Failes in QuickSort: Unsorted array of numbers");
		}
					
		flag = TRUE;
	}
				
	GenRandArr(arr, len, MIN, MAX);		
	time_req_qsort = clock();
	qsort(arr, len, sizeof(int), Compare);
	time_req_qsort = clock() - time_req_qsort;

	t_bubble = (float)time_req_bubble / CLOCKS_PER_SEC;
	t_insert = (float)time_req_insertion / CLOCKS_PER_SEC;
	t_qsort = (float)time_req_qsort / CLOCKS_PER_SEC;
	t_select = (float)time_req_selection / CLOCKS_PER_SEC;	
	t_count = (float)time_req_counting / CLOCKS_PER_SEC;	
	t_radix = (float)time_req_radix / CLOCKS_PER_SEC;

	t_merge = (float)time_req_merge / CLOCKS_PER_SEC;	
	t_my_quick = (float)time_req_my_quick / CLOCKS_PER_SEC;	
		
	puts("\n" BACK_CYAN"Processor time taken for:"RESET"\n");
		
	printf("BubbleSort   : "BACK_GREEN" %f "RESET" seconds  \n", t_bubble);

	printf("SelectionSort: "BACK_GREEN" %f "RESET" seconds  \n", t_select);
           
	printf("InsertionSort: "BACK_GREEN" %f "RESET" seconds  \n", t_insert);
	
 	printf("CountingSort : "BACK_GREEN" %f "RESET" seconds  \n", t_count); 
 		
 	printf("RadixSort    : "BACK_GREEN" %f "RESET" seconds  \n", t_radix);
 	 	 	                     
	printf("QuickSort    : "BACK_GREEN" %f "RESET" seconds  \n", t_qsort);
	 	 	 	                     
	printf("My_QuickSort : "BACK_GREEN" %f "RESET" seconds  \n", t_my_quick);
	
	printf("MergeSort    : "BACK_GREEN" %f "RESET" seconds  \n", t_merge);
		
	puts("\n" BACK_CYAN"Ratio time:"RESET"\n");
	
	printf("BubbleSort/QuickSort   : "BACK_GREEN" %f "RESET" \n", \
           t_bubble/t_qsort);

	printf("SelectionSort/QuickSort: "BACK_GREEN" %f "RESET" \n", \
           t_select/t_qsort); 
                      
	printf("InsertionSort/QuickSort: "BACK_GREEN" %f "RESET" \n", \
           t_insert/t_qsort);
           
    printf("MergeSort/QuickSort    : "BACK_GREEN" %f "RESET" \n", \
           t_merge/t_qsort); 
                      
	printf("My_QuickSort/QuickSort : "BACK_GREEN" %f "RESET" \n", \
           t_my_quick/t_qsort);                        
	  	                  
	if( !flag )
	{		
		puts(BACK_BLUE"Test: Success"RESET);

	}
	
	else
	{
		puts(BACK_YELLOW"Test: Failure"RESET);	
	}

}



