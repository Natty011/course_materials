/***************************************
* Author : Natty
* Reviewer : Matan  
* Date : 22 / 01 / 2025
* Last update: 22 / 01 / 2025
*****************************************/

#include <assert.h> 	/* assert */
#include <stdlib.h> 	/* malloc, free */

#include "sort.h"


/***************struct and enum declaration *******/

typedef enum
{
	FALSE = 0,
	TRUE = 1
}bool;

/***************End of struct and enum declaration *******/

/***************************function declaration***************************/
void swap(int* ptr1, int* ptr2);
/***************************End of function declaration******************/

/******************static functions definition**********************/
void swap(int* ptr1, int* ptr2)
{
	int temp = 0;
	
	assert(ptr1);
	assert(ptr2);
	
	temp = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = temp;
}

/******************End of static functions definition**********************/

/***************************BubbleSort***************************/
void BubbleSort(int* arr, size_t size)
{

	bool swapped_occured = FALSE;
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
	/*int temp = 0;*/
	
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

