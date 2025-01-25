/***************************************
* Author : Natty
* Reviewer : David  
* Date : 22 / 01 / 2025
* Last update: 23 / 01 / 2025
*****************************************/
#include <assert.h> 	/* assert */
#include <stdlib.h> 	/* malloc, calloc, free */

#include "sort.h"

#define MIN(a, b)		((a > b ) ? b : a )
#define MAX(a, b)		((a > b ) ? a : b )
/***************struct and enum declaration *******/

typedef enum state
{
	FALSE = 0,
	TRUE = 1
}state_t;

typedef enum status
{
	SUCCESS = 0,
	FAIL = 1
}status_t;

/*
typedef struct min_max
{
	int min;
	int max;
}min_max_t;
*/
/***************End of struct and enum declaration *******/

/***************************function declaration***************************/
static void swap(int* ptr1, int* ptr2);
static void FindMinMax(	int* arr, size_t size, int* min, int* max);
static int CountingSortAux(int *arr, size_t size, int exp_digit);
/***************************End of function declaration******************/

/******************static functions definition**********************/

/***************************swap***************************/
static void swap(int* ptr1, int* ptr2)
{
	int temp = 0;
	
	assert(ptr1);
	assert(ptr2);
	
	temp = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = temp;
}
/*************************FindMinMax***************************/
static void FindMinMax(	int* arr, size_t size, int* min, int* max)
{
	size_t i = 0;
	
	assert(arr);
	
	for( i = 0; i < size ; ++i)
	{
		*min = MIN(arr[i], *min);
		*max = MAX(arr[i], *max);	
	}
}

/*************************CountingSortAux***************************/
static int CountingSortAux(int *arr, size_t size, int exp_digit)
{
	int i = 0, hist_size = 10, *arr_sorted = NULL, len  = (int)size ;
	int hist[10] = { 0 };
		
	assert(arr);

	/* fill the hist*/
	for(i = 0; i < len; ++i)
	{
		hist[( arr[i] / exp_digit) % 10 ]++; 
	}
	
	/* acumulatiom of each data cell with the previouses data
	include the current cell */	
	for(i = 1; i < hist_size; ++i)
	{
		hist[i] += hist[i-1]; 
	}
	
	/* check if the acumulations correct*/
	assert( size == (size_t)hist[hist_size - 1]);
	
	arr_sorted = (int*)malloc( size * sizeof(int) );
	
	if( !arr_sorted )
	{		
		return FAIL;
	}
	/* do the sorting */	
	for(i = len - 1 ; i >= 0; --i)
	{
		--hist[ (arr[i] / exp_digit) % 10 ];
		arr_sorted[ hist[ (arr[i] / exp_digit) % 10 ] ] = arr[i];
	}
	/* copy to original array after the sorting */		
	for(i = 0; i < len ; ++i)
	{
		arr[i] = arr_sorted[i];
	}
	
	free(arr_sorted);
	arr_sorted = NULL; 
	
	return SUCCESS; /* 0 */

}

/******************End of static functions definition**********************/

/***************************BubbleSort***************************/
void BubbleSort(int* arr, size_t size)
{
	int swapped_occured = FALSE;
	size_t i = 0, j = 0;

	assert(arr);
		
	for(i = 0; i < size; ++i)
	{
		for( j = 0; j < size - i -1 ; ++j)
		{
			if( arr[j] > arr[j + 1])
			{
				swap(arr + j, arr + j + 1);
				
				swapped_occured = TRUE;
			}				
		}
	
		if(!swapped_occured)
		{
			break;
		}
	}
	
	return;
}

/***************************InsertionSort***************************/

void InsertionSort(int *arr, size_t size)
{
	int key = 0, i = 0, j = 0;
		
	assert(arr);

	for(i = 1; (size_t)i < size; ++i)
	{
		key = arr[i];
		j = i - 1;
		
		while( (j >= 0) && (arr[j] > key) ) 
		{
			arr[j + 1] = arr[j];
			j = j - 1;	
		}
		
		arr[j + 1] = key;	
	}
	
	return;
}

/***************************SelectionSort***************************/
void SelectionSort(int *arr, size_t size)
{
	int i = 0, j = 0, min_index = 0;
	
	assert(arr);
	
	for(i = 0; (size_t)i < size - 1; ++i)
	{
		min_index = i;
		
		for(j = i + 1; (size_t)j < size; ++j)
		{
			if(arr[j] < arr[min_index] )
			{
				min_index = j;
			}
		
		}
	
		swap( arr + min_index, arr + i);				
	}

}
/***************************CountingSort***************************/

int CountingSort(int *arr, size_t size)
{
	int i = 0, hist_size = 0, min = arr[0], max = arr[0],
				 *hist = NULL, *arr_sorted = NULL;
	int len  = (int)size ;
	assert(arr);

	FindMinMax(arr, size, &min, &max);
	
	hist_size = max - min + 1;
	hist = (int*)calloc( hist_size, sizeof(int) );
	
	if( !hist )
	{
		return FAIL; /* 1 */		
	}
	
	/* fill the hist*/
	for(i = 0; i < len; ++i)
	{
		hist[arr[i] - min]++; 
	}
	
	/* acumulatiom of each data cell with the previouses data
	include the current cell */	
	for(i = 1; i < hist_size; ++i)
	{
		hist[i] += hist[i-1]; 
	}
	
	/* check if the acumulations correct*/
	assert( size == (size_t)hist[hist_size - 1]);
	
	arr_sorted = (int*)malloc( size * sizeof(int) );
	
	if( !arr_sorted )
	{
		
		free(hist);
		hist = NULL;
				
		return FAIL;
	}
	/* do the sorting */	
	for(i = len - 1 ; i >= 0; --i)
	{
		--hist[ arr[i] - min ];
		arr_sorted[ hist[ arr[i] - min ] ] = arr[i];
	}
	/* copy to original array after the sorting */		
	for(i = 0; i < len ; ++i)
	{
		arr[i] = arr_sorted[i];
	}
	
	free(hist);
	free(arr_sorted);
	hist = NULL;
	arr_sorted = NULL; 
	
	return SUCCESS; /* 0 */
}

/***************************RadixSort***************************/
int RadixSort(int *arr, size_t size)
{
	int max = arr[0], exp_digit = 1; /* exp_digit == 10^digit_to_sort*/
    int min __attribute__((unused))= arr[0];

	assert(arr);
	FindMinMax(arr, size, &min, &max);
	
	for(exp_digit = 1; max/exp_digit > 0; exp_digit *= 10)
	{

		if (CountingSortAux(arr, size, exp_digit) )
		{
			return FAIL;
		}
		
	}
	
	return SUCCESS;
}

