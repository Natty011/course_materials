/*******************************************************************************
 *
 *	Aouther:	Idan Hadad
 *	Review:     Ofek Lougassi
 *	Date:       22/02/25
 *	worksheet:  DS::Heap
 *
 *******************************************************************************/
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "typedefs.h"
#include "vector.h"
#include "heap.h"

#define INIT_VECTOR_CAPACITY 16

#define IS_INDEX_LAST(i, len) ((i) == ((len) - 1))
#define IS_INDEX_LEAF(i, len) ((((i) * 2) + 1) >= (len))

/******************************************************************************/
/***************************** Management struct ******************************/

struct heap
{
    vector_t *arr;
    expand_cmp_func_t cmp_func;
    void *param;
};


typedef enum
{
	SUCCESS = 0,
	FAIL = 1
} status_t;

typedef enum
{
 FALSE = 0,
 TRUE = 1   

} bool_t;

/******************************************************************************/
/************************ ststic functions declartions ************************/
static long HeapifyUp(heap_t *heap, size_t index);

static long HeapifyDown(heap_t *heap, long index);

static long
FindIndexToRemove(heap_t *heap, match_func_t func, void *param, void **data);

static long HandleLeaf(heap_t *heap, long index);

static void RemoveIndex(heap_t* heap ,long index);

static void **GetMaxChild(heap_t *heap, long index, long *max_index);

static void SwapVoidPtr(size_t *x, size_t *y);

/********************************** HeapCreate  *******************************/

heap_t *HeapCreate(void *param, expand_cmp_func_t cmp_func)
{
    heap_t *heap = (heap_t *)malloc(sizeof(heap_t));

    if (NULL == heap)
    {
        return NULL;
    }

    heap->arr = VectorCreate(INIT_VECTOR_CAPACITY, sizeof(size_t));

    if (NULL == heap->arr)
    {
        free(heap);
        heap = NULL;

        return NULL;
    }

    heap->cmp_func = cmp_func;
    heap->param = param;

    return heap;
}

/******************************************************************************/
/********************************* HeapDestroy  *******************************/

void HeapDestroy(heap_t *heap)
{
    VectorDestroy(heap->arr);
    heap->arr = NULL;
    heap->cmp_func = NULL;
    heap->param = NULL;

    free(heap);
    heap = NULL;
}

int HeapPush(heap_t *heap, const void *new_data)
{
    long index = 0;
    vector_t *vector = NULL;

    assert(heap);
    vector = heap->arr;
    assert(vector);

    if (VectorPushBack(vector, &new_data) == FAIL)
    {
        return FAIL;
    }

    index = VectorSize(vector) - 1;
    
    while (index != -1)
    {
        index = HeapifyUp(heap, index);
    }

    return SUCCESS;
}

void HeapPop(heap_t *heap)
{
    assert(heap);
    assert(heap->arr);

    RemoveIndex(heap , 0);
}

void *HeapRemove(heap_t *heap, match_func_t match_func, void *param)
{
    long index = -1;
    void *data = NULL;

    assert(heap);
    assert(heap->arr);

    index = FindIndexToRemove(heap, match_func, param, &data);

    RemoveIndex( heap, index);

    return data;
}

void *HeapPeek(const heap_t *heap)
{
    assert(heap);
    assert(heap->arr);

    return *(void **)VectorGetAccess(heap->arr, 0);
}

size_t HeapSize(const heap_t *heap)
{
    assert(heap);
    assert(heap->arr);

    return VectorSize(heap->arr);
}

int HeapIsEmpty(const heap_t *heap)
{
    assert(heap);
    assert(heap->arr);

    return VectorSize(heap->arr) == 0;
}

void* HeapGetParam(const heap_t *heap)
{
	assert(heap);
	
	return heap->param;
}

/************************ ststic functions definitions ************************/

static long HeapifyUp(heap_t *heap, size_t index)
{
    vector_t *vector = heap->arr;
    long parent_index = -1;
    void **child = NULL, **parent = NULL;

    if (index != 0)
    {
        parent_index = ((index - 1) / 2);
        child = (void **)VectorGetAccess(vector, index);
        parent = (void **)VectorGetAccess(vector, parent_index);

        if (heap->cmp_func(*child, *parent, heap->param) > 0)
        {
            SwapVoidPtr((size_t *)parent, (size_t *)child);
        }
    }

    return parent_index;
}

static long HeapifyDown(heap_t *heap, long index)
{
    void **parent = NULL, **max_child = NULL;
    long parent_index = -1, max_child_index = 0;

    max_child = GetMaxChild(heap, index, &max_child_index);

    if (max_child)
    {
        parent = (void **)VectorGetAccess(heap->arr, index);

        if (heap->cmp_func(*parent, *max_child, heap->param) < 0)
        {
            parent_index = max_child_index;
            SwapVoidPtr((size_t *)parent, (size_t *)max_child);
        }
    }

    return parent_index;
}

static long
FindIndexToRemove(heap_t *heap, match_func_t func, void *param, void **data)
{
    vector_t *vector = heap->arr;
    long i = 0, len = VectorSize(vector);
    void **cheked_data_ptr = NULL;

    for (i = 0; i < len; i++)
    {
        cheked_data_ptr = (void **)VectorGetAccess(vector, i);
        if (func(*cheked_data_ptr, param) == TRUE)
        {
            *data = *cheked_data_ptr;
            return IS_INDEX_LEAF(i, len) ? HandleLeaf(heap, i) : i;
        }
    }
    return -1;
}

static long HandleLeaf(heap_t *heap, long index)
{
    vector_t *vector = heap->arr;
    void **data_to_remove = NULL, **end = NULL, **parent = NULL;
    long len = VectorSize(vector), index_to_return = index, parent_index = 0;

    if (IS_INDEX_LAST(index, len))
    {
        VectorPopBack(vector);
        return -1;
    }

    data_to_remove = (void **)VectorGetAccess(vector, index);

    end = (void **)VectorGetAccess(vector, len - 1);

    parent_index = ((index - 1) / 2);
    parent = (void **)VectorGetAccess(vector, parent_index);

    if (heap->cmp_func(*end, *parent, heap->param) > 0)
    {
        SwapVoidPtr((size_t *)data_to_remove, (size_t *)parent);
        index_to_return = parent_index;
    }

    return index_to_return;
}

static void RemoveIndex(heap_t* heap ,long index)
{
    vector_t* vector = heap->arr;
    void **data_to_remove =  NULL , **end = NULL;
    
    if ( -1 == index )
    {
        return;
    }
    
    data_to_remove = (void**)VectorGetAccess(vector, index);
    end = (void**)VectorGetAccess(vector, VectorSize(vector) - 1);

    SwapVoidPtr((size_t *)data_to_remove, (size_t *)end);
    VectorPopBack(vector);
    
    while (-1 != index)
    {
        index = HeapifyDown(heap, index);
    }
}

static void **GetMaxChild(heap_t *heap, long index, long *max_index)
{
    void **left = NULL, **right = NULL;
    long left_index = 2 * index + 1, right_index = 2 * index + 2;
    vector_t *vector = heap->arr;
    long len = VectorSize(vector);

    left =
        left_index < len ? (void**)VectorGetAccess(vector, left_index) : NULL;

    right =
        right_index < len ? (void**)VectorGetAccess(vector, right_index) : NULL;

    if (left && right)
    {
        if (heap->cmp_func(*left, *right, heap->param) > 0)
        {
            *max_index = left_index;
            return left;
        }
    }
    else if (left)
    {
        *max_index = left_index;
        return left;
    }

    *max_index = right_index;
    return right;
}

static void SwapVoidPtr(size_t *x, size_t *y)
{
    size_t tmp = *x;
    *x = *y;
    *y = tmp;
}


#ifdef PRINTS
void PrintVector(heap_t *h)
{
    vector_t *v = h->arr;
    size_t len = VectorSize(v), i = 0;

    for (i = 0; i < len; ++i)
    {
        printf("%3d", **(int **)VectorGetAccess(v, i));
    }
    putchar('\n');
}

void *GetVectorIndex(heap_t *h, size_t index)
{
    return *(void **)VectorGetAccess(h->arr, index);
}

#endif /* PRINTS */
