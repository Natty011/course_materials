/*auther: Gilad, tester: Sauser*/

#include <limits.h> /* INT_MIN */
#include <stdlib.h> /* malloc, calloc, free */
#include <string.h> /* memcpy */
 
#include "sort.h"

#define INDEX(arr, i) *(arr + i)
#define BASE 10

static void Swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void BubbleSort(int* arr, size_t size)
{
	int* start = arr;
	int swap_amount = 0;
	size_t i = 0, j = 0;

	/*we sort 1 element each pass and so we need n-1 passes*/
	for(i = size - 1; i > 0; i--)
	{
		swap_amount = 0;
		arr = start;

		/*swap if needed or continue if not*/
		for (j = 0; j < i; j++)
		{
			if(*arr > *(arr + 1))
			{
				Swap(arr, (arr + 1));
				swap_amount++;
			}
			arr++;
		}
		if(0 == swap_amount)
		{
			return;
		}
	}
}

void InsertionSort(int* arr, size_t size)
{
	int* start = arr;
	size_t i = 0;

	/*this index will represent the sorted small subarray*/
	for(i = 0; i < size; i++)
	{
		arr = start;
		arr += i;

		/*if we are not in the first element,
			 swap elements until the right position*/
		while(arr != start && *arr < *(arr - 1))
		{
			Swap(arr, (arr - 1));
			arr--;
		}
	}
}

void SelectionSort(int* arr, size_t size)
{
	int* start = arr;
	int* end_of_sub = NULL;
	int* biggest = NULL;
	int max = INT_MIN;
	size_t i = 0, j = 0;

	/*every time we sort 1 element to the right position in the end
		index i will represent the index to swap the max*/
	for(i = size - 1; i > 0; i--)
	{
		arr = start;
		end_of_sub = start + i;
		max = INT_MIN;
		biggest = end_of_sub;

		/*we find the max and put it in the right position at the i index*/
		for (j = 0; j <= i; j++)
		{
			if(*arr > max)
			{
				max = *arr;
				biggest = arr;
			}
			arr++;
		}

		Swap(biggest, end_of_sub);
	}
}

/*find the maximum and the minimum for the counting sort*/
static void MaxMin(int *arr, int *ptr_max, int *ptr_min, size_t size) {
    size_t i = 0;
    for(i = 0; i < size; i++) {
        if(INDEX(arr, i) > *ptr_max) {
            *ptr_max = INDEX(arr, i);
        }
        if(INDEX(arr, i) < *ptr_min) {
            *ptr_min = INDEX(arr, i);
        }
    }
}

static void Max(int *arr, int *ptr_max, size_t size) {
    size_t i = 0;
    for(i = 0; i < size; i++) {
        if(INDEX(arr, i) > *ptr_max) {
            *ptr_max = INDEX(arr, i);
        }
    }
}

int CountingSort(int *arr, size_t size)
{
	int max = INT_MIN, min = INT_MAX;
	size_t i = 0;
	int* count_arr = NULL;
	int* final_arr = NULL;

	MaxMin(arr, &max, &min, size);

	count_arr = (int*)calloc((size_t)(max - min + 1),sizeof(int));
	if(!count_arr)
	{
		return 1;
	}
	final_arr = (int*)malloc(sizeof(int)*(size));
	if(!final_arr)
	{
		free(count_arr);
		return 1;
	}
	
	/*setting up the count array*/
	for(i = 0; i < size; i++)
	{
		count_arr[INDEX(arr, i) - min]++;
	}

	/*adding up to find real locations*/
	for(i = 1; i < (size_t)(max - min + 1); i++)
	{
		INDEX(count_arr, i) += INDEX(count_arr, i - 1);
	}

	/*setting up the final array and updating count*/
	for(i = size; i > 0; i--)
	{
		final_arr[count_arr[INDEX(arr, i - 1) - min] - 1] = INDEX(arr, i - 1);
		count_arr[INDEX(arr, i - 1) - min]--;
	}

	/*copy the final array to the original*/
	for(i = 0; i < size; i++)
	{
		INDEX(arr, i) = INDEX(final_arr, i);
	}

	free(count_arr);
	free(final_arr);

	count_arr = NULL;
	final_arr = NULL;

	return 0;	
}

static int CountingSortForDigit(int *arr, int size, int digit) {
    int *count_arr, *output;
	int i = 0;
    int base = BASE;
    
    count_arr = (int*)calloc(base, sizeof(int));
	if(!count_arr)
	{
		return 1;
	}
    output = (int*)malloc(size * sizeof(int));
	if(!output)
	{
		free(count_arr);
		count_arr = NULL;
		return 1;
	}
    
	/*add them to count array based on the digit in the right place*/
    for (i = 0; i < size; i++) 
	{
        count_arr[(INDEX(arr, i) / digit) % base]++;
    }
    
	/*adding up to find real locations*/
    for (i = 1; i < base; i++) 
	{
        INDEX(count_arr, i) += INDEX(count_arr, i - 1);
    }
   
	/*setting up the final array and updating count*/ 
    for (i = size - 1; i >= 0; i--) 
	{
        output[count_arr[(INDEX(arr, i) / digit) % base] - 1] = INDEX(arr, i);
        count_arr[(INDEX(arr, i) / digit) % base]--;
    }
    
	/*copy the final array to the original*/
    for (i = 0; i < size; i++) 
	{
        INDEX(arr, i) = output[i];
    }
    
    free(count_arr);
    free(output);

	count_arr = NULL;
	output = NULL;
	return 0;
}

int RadixSort(int *arr, size_t size) {
    int max = *arr;
	int digit = 0;
    
	/*find the max*/
	Max(arr, &max, size);
   
	/*send the right digit as a pow of BASE*/ 
    for (digit = 1; max / digit > 0; digit *= BASE) 
	{
        if(CountingSortForDigit(arr, size, digit))
		{
			return 1;
		}
    }
	return 0;
}

int BinarySearchIterative(int *arr, size_t size, int num)
{
	size_t low = 0, high = size, mid = 0;
	while(high > low)
	{
		mid = (low + high) / 2;
		if(arr[mid] == num)
		{
			return mid;
		}
		else if(arr[mid] < num)
		{
			low = mid + 1;
		}
		else
		{
			high = mid - 1;
		}
	}
	return -1;
}

int* BinarySearchRecursive(int *arr, size_t size, int num)
{
	size_t mid = 0;

	if(size == 0)
	{
		return NULL;
	}
	
	mid = size / 2;

	if(arr[mid] == num)
	{
		return &arr[mid];
	}

	if(arr[mid] < num)
	{
		return BinarySearchRecursive(arr + mid, size - mid, num);
	}
	else
	{
		return BinarySearchRecursive(arr, mid - 1, num);
	}
	return NULL;
}

static int merge(int arr[], int left, int mid, int right)
{
	int i = 0, j = 0, n = 0;
	int right_size = right - mid , left_size = mid - left + 1;

	int* left_arr = (int*)malloc(sizeof(int) * left_size);
	int* right_arr = (int*)malloc(sizeof(int) * right_size);
	if(!left_arr || !right_arr)
	{
		return 1;
	}

	for (i = 0; i < left_size; i++)
	{
        left_arr[i] = arr[left + i];
	}
    for (j = 0; j < right_size; j++)
	{
        right_arr[j] = arr[mid + 1 + j];
	}
	
	i = 0;
	j = 0;
	n = left;

	while(i < left_size && j < right_size)
	{
		if (left_arr[i] <= right_arr[j]) {
            arr[n] = left_arr[i];
            i++;
        }
        else {
            arr[n] = right_arr[j];
            j++;
        }
        n++;
	}

	while (i < left_size) {
        arr[n] = left_arr[i];
        i++;
        n++;
    }

    while (j < right_size) {
        arr[n] = right_arr[j];
        j++;
        n++;
    }

	free(left_arr);
	free(right_arr);

	return 0;

}

int MergeSort(int *arr, size_t size)
{
	if(size > 1)
	{
		size_t mid = size / 2;

		MergeSort(arr, mid);
		MergeSort(arr + mid, size - mid);

		if(merge(arr, 0, mid - 1, size - 1))
		{
			return 1;
		}
	}
	return 0;
}


/*memory swap with malloc because of possible diffrent sizes*/
void swap(void *a, void *b, size_t size) {
    void *temp = malloc(size);
    memcpy(temp, a, size);
    memcpy(a, b, size);
    memcpy(b, temp, size);
    free(temp);
}

void QuickSort(void *arr, size_t count, size_t element_size,
               int (*cmp_func)(const void *, const void *)) 
{
	char *array = NULL;
	void *pivot = NULL;
	size_t i, j;

	/*when size is 1 we dont need to continue*/
    if (count < 2) return;

    array = arr;

	/*because the function swap changes in memory we dont want the pivot to 
	change and interfere so we dynamically allocate him*/
    pivot = malloc(element_size);
    memcpy(pivot, array + (count / 2) * element_size, element_size);
    
    for (i = 0, j = count - 1;; i++, j--) 
	{
		/*2 loops to go until we find a match*/
        while (cmp_func(array + i * element_size, pivot) < 0) i++;
        while (cmp_func(array + j * element_size, pivot) > 0) j--;

        if (i >= j) break;

		/*swap the match*/
        swap(array + i * element_size, array + j * element_size, element_size);
    }
	
	free(pivot);

	/*recursivly do depending on when the i ended*/
    QuickSort(array, i, element_size, cmp_func);
    QuickSort(array + i * element_size, count - i, element_size, cmp_func);
}

static void heapify(int* arr, size_t size, int index)
{
	int head = index;
	int left = 2 * index + 1;
	int right = 2 * index + 2;

	if(left < (int)size && arr[left] > arr[head])
	{
		head = left;
	}
	if(right < (int)size && arr[right] > arr[head])
	{
		head = right;
	}

	if(head != index)
	{
		swap(arr + index ,arr + head, sizeof(int));
		heapify(arr, size, head);
	}
}

void HeapSort(int* arr, size_t size)
{
	int i = 0;
	assert( arr );
	for(i = size / 2 - 1; i >= 0; i--)
	{
		heapify(arr ,size ,i);
	}

	for(i = size - 1; i >= 0; i--)
	{
		swap(arr ,arr + i, sizeof(int));
		heapify(arr ,i ,0);
	}
}




















