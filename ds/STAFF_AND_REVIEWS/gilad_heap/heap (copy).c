#include <stdlib.h> /*malloc, free*/
#include <assert.h> /*assert*/
#include <stdio.h>

#include "heap.h"
#include "vector.h"

struct heap
{
	vector_t* vector;
	void* u_param;
	expand_cmp_func_t comp;
};

typedef enum
{
	SUCCESS = 0,
	FAIL = 1
} status_t;

/********************************aux func declarations*************************/

static void SwapVoid(void** a, void** b);

/*gets an element from the heap's vector by index*/
static void* HeapGet(heap_t*, size_t i);

static void HeapifyDown(heap_t*, size_t i);

static void HeapifyUp(heap_t*, size_t i);

/******************************************************************************/

heap_t* HeapCreate( void* param , expand_cmp_func_t cmp_func )
{
    heap_t* heap = (heap_t*)malloc(sizeof(heap_t));
    if (!heap)
    {
        return NULL;
    }
    heap->comp = cmp_func;
	heap->u_param = param;
    heap->vector = VectorCreate(16, sizeof(void*));
    if (!heap->vector)
    {
        free(heap);
        return NULL;
    }
    return heap;
}
 
void HeapDestroy(heap_t *heap)
{
	if(heap == NULL) return;
	
	VectorDestroy(heap->vector);
	
	heap->vector = NULL;
	free(heap);
	heap = NULL;
}

int HeapPush(heap_t* heap, const void* data)
{
    assert(heap);

    if (VectorPushBack(heap->vector, &data) != 0)
    {
        return FAIL;
    }

    HeapifyUp(heap, VectorSize(heap->vector) - 1);
    return SUCCESS;
}

void HeapPop(heap_t* heap)
{
    size_t size = 0;

    assert(heap);

    size = VectorSize(heap->vector);

    if (size > 0)
    {
        SwapVoid(VectorGetAccess(heap->vector, 0), VectorGetAccess(heap->vector, size - 1));
        VectorPopBack(heap->vector);
        HeapifyDown(heap, 0);
    }
}

void* HeapRemove(heap_t *heap, match_func_t match_func, void *data)
{
    size_t i = 0;
    void* r_data = NULL;
    size_t size = 0;
    
    assert(heap);
    
    size = HeapSize(heap);
    
    /*looking for the data to find*/
    for (i = 0; i < size; i++)
    {
        void* temp = *(void**)HeapGet(heap, i);
        if (1 == match_func(temp, data))
        {
            r_data = temp;
            break;
        }
    }
    
    /*send removed value to the end*/
    if (r_data != NULL)
    {
        SwapVoid(HeapGet(heap, i), HeapGet(heap, size - 1));
        VectorPopBack(heap->vector);
        
        /*if data was found, reorder heap*/
        HeapifyDown(heap, 0);
        HeapifyUp(heap, i);
    }   
    
    return r_data;
}

void *HeapPeek(const heap_t *heap)
{
    void** data = NULL;

    assert(heap);

    data = VectorGetAccess(heap->vector, 0);
    return *data;
}

size_t HeapSize(const heap_t *heap)
{
	assert(heap);
	return VectorSize(heap->vector);
}

int HeapIsEmpty(const heap_t *heap)
{
	assert(heap);
	return 0 == VectorSize(heap->vector);
}

/***********************************aux functions******************************/

static void SwapVoid(void** a, void** b)
{
	void* temp = *a;
	*a = *b;
	*b = temp;
}

static void* HeapGet(heap_t* heap, size_t i)
{
	return VectorGetAccess(heap->vector, i);
}

static void HeapifyDown(heap_t* heap, size_t index)
{
    size_t largest = index;
    size_t left_child = 2 * index + 1;
    size_t right_child = 2 * index + 2;
    size_t heap_size = HeapSize(heap);
    expand_cmp_func_t comp = heap->comp;

    if (left_child < heap_size && 
        comp(*(void**)HeapGet(heap, largest), *(void**)HeapGet(heap, left_child), heap->u_param) < 0)
    {
        largest = left_child;
    }

    if (right_child < heap_size && 
        comp(*(void**)HeapGet(heap, largest), *(void**)HeapGet(heap, right_child), heap->u_param) < 0)
    {
        largest = right_child;
    }

    if (largest != index)
    {
        SwapVoid(HeapGet(heap, index), HeapGet(heap, largest));
        HeapifyDown(heap, largest);
    }
}

static void HeapifyUp(heap_t* heap, size_t index)
{
    size_t parent = 0;

    if (index == 0)
    {
        return;
    }

    parent = (index - 1) / 2;

    if (heap->comp(*(void**)HeapGet(heap, index), 
                   *(void**)HeapGet(heap, parent), heap->u_param) > 0)
    {
        SwapVoid(HeapGet(heap, index), HeapGet(heap, parent));
        HeapifyUp(heap, parent);
    }
}


void PrintArray( heap_t* heap )
{
	size_t size = 0 ;
	int* element = NULL;
	printf("HeapArray[] = \n" );
	while( size < HeapSize( heap ) )
	{
		element = *(void**)VectorGetAccess(heap->vector, size );
		printf("index = %ld , value = %d \n", size, *element );
			++size;
	}
}












