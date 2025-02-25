/***************************************
* Author : Natty
* Reviewer : Natan / gilad( HeapSort )
* Date : 22 / 01 / 2025
* Last update: 25 / 02 / 2025
*****************************************/
#include <assert.h> 	/* assert */
#include <stdlib.h> 	/* malloc, calloc, free, srand/rand */
#include <string.h> 	/* memcpy */
#include "sort.h"

#include "../include/heap.h" 
#include "../include/vector.h" 
#include "aux_func.h"


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
static void	AuxMergeSort(int *arr, size_t size, int* helper_array );
static void	Merge( int* arr_left, int left, int* arr_right,
					 int right, int* helper_array);
static int SwapQuick(void* ptr1, void* ptr2, size_t element_size);

static void BuildHeap( int* arr, size_t size );
static void Heapify(int *arr, size_t size, size_t index );
/*static size_t Random( size_t count );		*/			 
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


/*************************AuxMergeSort***************************/	
static void	AuxMergeSort(int *arr, size_t size, int* helper_array )
{
	int left = size / 2, right = size - left;	
	assert( helper_array );
	assert( arr );
		
	if ( size < 2 ) 
	{
		return;
	}
	
	AuxMergeSort(arr ,left ,helper_array);
	AuxMergeSort(arr + left ,right ,helper_array );	
	Merge(arr, left, arr + left, right, helper_array );
	memcpy( arr, helper_array, sizeof(arr[0]) * size  );	
}

/*************************Merge***************************/	
static void	Merge( int* arr_left, int left, int* arr_right,
					 int right, int* helper_array)
{
	int len_left = 0, len_right = 0, len_helper = 0 ;
	
	assert( helper_array );
	assert( arr_left );
	assert( arr_right );
	
	for ( ; (len_left < left ) && (len_right < right ) ; ++len_helper )
	{
		if ( arr_left[len_left] < arr_right[len_right] )
		{
			helper_array[len_helper] = arr_left[len_left];
			++len_left;
		}
		
		else
		{
			helper_array[len_helper] = arr_right[len_right];
			++len_right;
		}
		
	}
	
	while( 	len_left < left )
	{
		helper_array[len_helper] = arr_left[len_left];
		++len_left;
		++len_helper;
	}
	
	while( 	len_right < right )
	{
		helper_array[len_helper] = arr_right[len_right];
		++len_right;
		++len_helper;
	}		
}

/***************************SwapQuick***************************/
static int SwapQuick(void* ptr1, void* ptr2, size_t element_size)
{
	char* temp = NULL;
	
	assert( ptr1 );
	assert ( ptr2 );
	
	temp = (char*)malloc( element_size );

	if ( NULL == temp )
	{
		return FAIL;
	}
	
	memcpy(temp, ptr1, element_size );
	memcpy(ptr1, ptr2, element_size );
	memcpy(ptr2, temp, element_size );
	
	free( temp );
	temp = NULL;
	
	return SUCCESS;
}
/*************************Random***************************/	
/*
static size_t Random( size_t count )
{
	size_t random_pivot = 0 ;
	random_pivot = rand() % count ;

	return random_pivot;
}
*/
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

/*************************BinarySearchIterative***************************/
int BinarySearchIterative(int *arr, size_t size, int num)
{
	int low = 0, high = 0, mid = 0;
	assert( arr );
	
	low = 0;
	high = size - 1 ;
	mid = (low +high ) / 2;
	
	while ( low <= high )
	{
		if ( num == *(arr + mid) )	
		{
			return mid;
		}
		
		else if( num < *(arr + mid) )
		{
			high = mid - 1;
		}
		
		else
		{
			low = mid + 1;
		}
		
		mid = (low +high ) / 2;
	}
	
	return -1;
}	

/*************************BinarySearchRecursive***************************/	
int* BinarySearchRecursive(int *arr, size_t size, int num)
{
	int  mid = 0;
	assert( arr );

	if ( 0 == size )
	{
		return NULL;
	}	
	mid = size / 2;
		
	if ( num == *(arr + mid) )
	{
		return arr + mid;
	}
		
	if ( num < *(arr + mid) )
	{
		return BinarySearchRecursive(arr, mid, num );
	}
	
	return BinarySearchRecursive(arr + mid  + 1, size - mid - 1, num );
}

	 
/*************************MergeSort***************************/	

int MergeSort(int *arr, size_t size)
{
	int *helper_array = NULL;
	
	helper_array = (int*)malloc( size * sizeof( arr[0] ) ); 
	assert( helper_array );
	
	if( NULL == helper_array )
	{
		return FAIL;
	}
	
	AuxMergeSort(arr ,size ,helper_array );

	free( helper_array );
	helper_array = NULL;
	
	return SUCCESS;
}	

	
/*************************QuickSort***************************/	
void QuickSort(void *arr, size_t count, size_t elem,
                       int (*cmp_func)(const void *, const void *))
{
	char *pivot = NULL, *arr_ptr = NULL;
	size_t base = 1, tail = count - 1;
	
	assert( arr );
	assert( cmp_func );
	arr_ptr = (char*)arr;
	
	if ( count < 2 )
	{
		return;
	}
	
	pivot = (char*)arr;
	
	while( base <= tail )
	{
		while( base <= tail &&  (0 <= cmp_func(arr_ptr + (elem * tail), pivot )))
		{
			--tail;
		}
		
		while( base <= tail &&  (0 < cmp_func(pivot, arr_ptr + (elem * base ))))
		{
			++base;
		}
		
		if( base < tail )
		{
			if ( FAIL == SwapQuick( arr_ptr + (elem * base ),
					 arr_ptr + (elem * tail) , elem) )
			{
				return;
			}		 
			

			--tail;
			++base;			
		}
	}
	
	if ( FAIL == SwapQuick( pivot, arr_ptr + (elem * tail) , elem) )
	{
		return;	
	}
	
	QuickSort(arr_ptr, tail, elem, cmp_func );
	QuickSort(arr_ptr + (elem * (tail + 1)) , count - tail - 1, elem, cmp_func );	
}                       

/*************************************************************/	
/*************************HeapSort***************************/	
/*************************************************************/

void HeapSort(int *arr, size_t size)
{
	size_t index = 0;
	BuildHeap(arr, size );

	for(index = size - 1; index > 0 ; --index )
	{
		swap( arr + index, arr );
		Heapify(arr, index, 0);
	}

}

/*************************************************************/	
/*************************BuildHeap***************************/	
/*************************************************************/
static void BuildHeap( int* arr, size_t size )
{
	size_t i = 0;
	for( i = size / 2 - 1 ; i >= 0; --i )
	{
		Heapify( arr, size, i );
	}



}
/*************************************************************/	
/*************************Heapify***************************/	
/*************************************************************/

static void Heapify(int *arr, size_t size, size_t index )
{
	size_t left = 0, right = 0, largest = 0;
	
	largest = index;
	left = 2 * index + 1;
	right = left + 1;

	if(left < size &&  arr[left] > arr[ largest]  )
	{
		largest = left;
	}

	if(right < size &&  arr[right] > arr[ largest]  )
	{
		largest = right;
	}

	if( largest != index )
	{
		swap( arr + largest, arr + index );
		Heapify(arr, size, largest );
	}

}

