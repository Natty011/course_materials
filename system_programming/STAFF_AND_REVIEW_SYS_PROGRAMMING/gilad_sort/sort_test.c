/*auther: Gilad, tester: Sauser*/

#include <stdlib.h>/* qsort */
#include <time.h>  /* clock, clock_t */
#include <stdio.h> /* printf */
#include <limits.h> /* INT_MAX */

#include "sort.h"

#define ARR_SIZE 5000

static int PracticalTest(int* arr, size_t n);
static int Compare(const void *a, const void *b);
static void TestBubbleSort(int* result);
static void TestInsertionSort(int* result);
static void TestSelectionSort(int* result);
static void TestCountingSort(int* result);
static void TestRadixSort(int* result);
static void TestMergeSort(int* result);
static void TestQuickSort(int* result);
static void TestHeapSort(int* result);
static int TestSort(void (*fptr_void)(int*, size_t),
		int (*fptr_int)(int*, size_t), char* name, int range);
static int TestQSort(void (*fptr_quick)(void *, size_t, size_t,
               int (*)(const void *, const void *)), char* name, int range);


int main()
{
	int result = 0;
	int* ptr_result = &result;
	/*TestBubbleSort(ptr_result);
	TestInsertionSort(ptr_result);
	TestSelectionSort(ptr_result);
	TestCountingSort(ptr_result);
	TestRadixSort(ptr_result);
	TestMergeSort(ptr_result);
	TestQuickSort(ptr_result);*/
	TestHeapSort(ptr_result);

	if(result)
	{
		printf("failed in tests, amount failed: %d \n", result);
	}
	else
	{
		printf("success in tests\n");
	}
	return 0;	
}

/*makes sure the array is sorted*/
static int PracticalTest(int* arr, size_t n)
{
	size_t i = 0;
	for(i = 0; i < n - 1; i++)
	{
		if(arr[i] > arr[i+1])
		{
			return 1;
		}
	}
	return 0;
}

/*a function to compare for qsort*/
static int Compare(const void *a, const void *b) {
    int int_a = *((int*)a);
    int int_b = *((int*)b);

    if (int_a == int_b)
	{
		return 0;
	}
    else if (int_a < int_b)
	{ 
		return -1;
	}
    else
	{
		return 1;
	}
}

int compare_ints(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

static void TestBubbleSort(int* result)
{
	void (*fptr)(int*, size_t) = &BubbleSort;
	
	*result += TestSort(fptr,NULL, "BubbleSort", INT_MAX);

}

static void TestInsertionSort(int* result)
{
	void (*fptr)(int*, size_t) = &InsertionSort;
	
	*result += TestSort(fptr,NULL, "InsertionSort", INT_MAX);
}

static void TestSelectionSort(int* result)
{
	void (*fptr)(int*, size_t) = &SelectionSort;
	
	*result += TestSort(fptr,NULL, "SelectionSort", INT_MAX);
}

static void TestCountingSort(int* result)
{
	int (*fptr)(int*, size_t) = &CountingSort;
	
	*result += TestSort(NULL,fptr,"CountingSort", 100);
}

static void TestRadixSort(int* result)
{
	int (*fptr)(int*, size_t) = &RadixSort;
	
	*result += TestSort(NULL,fptr,"RadixSort", 100);
}

static void TestMergeSort(int* result)
{
	int (*fptr)(int*, size_t) = &MergeSort;
	
	*result += TestSort(NULL,fptr,"MergeSort", INT_MAX);
}

static void TestQuickSort(int* result)
{
	void (*fptr)(void *, size_t, size_t,
               int (*)(const void *, const void *)) = QuickSort;
	
	*result += TestQSort(fptr,"QuickSort", INT_MAX);
}

static void TestHeapSort(int* result)
{
	void (*fptr)(int*, size_t) = &HeapSort;
	
	*result += TestSort(fptr,NULL,"HeapSort", INT_MAX);
}


static int TestSort(void (*fptr_void)(int*, size_t), int (*fptr_int)(int*, size_t), char* name, int range)
{
	clock_t time_req;
	int arr_function [ARR_SIZE] = {0};
	int arr_quick [ARR_SIZE] = {0};
	int i = 0 , result = 0;

	for(i = 0;i < ARR_SIZE; i++)
	{
		arr_function[i] = rand() % range;
		arr_quick[i] = rand() % range;
	}
	time_req = clock();
	if(fptr_void)
	{
		fptr_void(arr_function, ARR_SIZE);
	}
	else
	{
		fptr_int(arr_function, ARR_SIZE);
	}
	time_req = clock() - time_req;
	printf("Processor time taken in %s function: %f seconds\n",
					 name,(float)time_req / CLOCKS_PER_SEC);

	result += PracticalTest(arr_function, ARR_SIZE);

	time_req = clock();
	qsort(arr_quick, ARR_SIZE, sizeof(int), Compare);
	time_req = clock() - time_req;
	printf("Processor time taken in QuickSort function: %f seconds\n",
					 (float)time_req / CLOCKS_PER_SEC);

	result += PracticalTest(arr_quick, ARR_SIZE);

	return result;
}

int CmpFunc(const void *a, const void *b) {
    int arg1 = *(const int *)a;
    int arg2 = *(const int *)b;
    return (arg1 > arg2) - (arg1 < arg2);
}


static int TestQSort(void (*fptr_quick)(void *, size_t, size_t,
               int (*)(const void *, const void *)), char* name, int range)
{
	clock_t time_req;
	int arr_function [ARR_SIZE] = {0};
	int arr_quick [ARR_SIZE] = {0};
	int i = 0 , result = 0;

	for(i = 0;i < ARR_SIZE; i++)
	{
		arr_function[i] = rand() % range;
		arr_quick[i] = rand() % range;
	}
	time_req = clock();

	fptr_quick(arr_function, ARR_SIZE, sizeof(int), Compare);

	time_req = clock() - time_req;
	printf("Processor time taken in %s function: %f seconds\n",
					 name,(float)time_req / CLOCKS_PER_SEC);

	result += PracticalTest(arr_function, ARR_SIZE);

	time_req = clock();
	qsort(arr_quick, ARR_SIZE, sizeof(int), Compare);
	time_req = clock() - time_req;
	printf("Processor time taken in QuickSort function: %f seconds\n",
					 (float)time_req / CLOCKS_PER_SEC);

	result += PracticalTest(arr_quick, ARR_SIZE);

	return result;
}


