#include <stdio.h>
#include <stdlib.h>


#include "heap.h"

typedef enum
{
	SUCCESS = 0,
	FAIL = 1

} result_t;

/******************************************************************************/
/******************************* True / False Enum ****************************/

typedef enum
{
	FALSE = 0,
	TRUE = 1
} bool_t;

void *GetVectorIndex(heap_t *h, size_t index);
void PrintVector(heap_t *h);

int CmpInt( void *check_data,  void *new_data, void *param);
int MatchInt(void *check_data, void *param);

void InitHeap(heap_t *heap);

result_t TestIsEmpty(void);
result_t TestSize(void);
static result_t MakeRemove(heap_t *heap, int to_remove, int *exp);
result_t TestRemove(void);
result_t TestPop(void);

static int arr[] = {6, 10, 5, 8, 9, 12, 36};
static size_t len = sizeof arr / sizeof arr[0];

int main()
{   
    printf("Test IEmpty %s\n" , TestIsEmpty() == SUCCESS ?
    "SUCCESS" : "FAIL" );
    printf("Test Size %s\n" , TestSize() == SUCCESS ?
    "SUCCESS" : "FAIL" );

    printf("Test Remove %s\n", TestRemove() == SUCCESS ? "SUCCESS" : "FAIL");
    printf("Test Pop %s\n" , TestPop() == SUCCESS ?
                                               "SUCCESS" : "FAIL" );
    return 0;
}

void InitHeap(heap_t *heap)
{
    size_t i = 0;
    if (NULL == heap)
    {
        printf("HeapCreat System fail...\n");
        return;
    }
    for (i = 0; i < len; ++i)
    {
        if (HeapPush(heap, arr + i) == FAIL)
        {
            printf("%lu\n",i);
            printf("HeapPush System fail...\n");
            return;
        }
    }
}

result_t TestIsEmpty(void)
{
    heap_t *heap = HeapCreate(NULL, CmpInt);
    size_t i = 0;

    if (HeapIsEmpty(heap) != TRUE)
    {
        HeapDestroy(heap);
        return FAIL;
    }

    InitHeap(heap);

    if (HeapIsEmpty(heap) != FALSE)
    {
        HeapDestroy(heap);
        return FAIL;
    }

    for (i = 0; i < len - 1; i++)
    {
        HeapPop(heap);
    }

    if (HeapIsEmpty(heap) != FALSE)
    {
        HeapDestroy(heap);
        return FAIL;
    }

    HeapPop(heap);

    if (HeapIsEmpty(heap) != TRUE)
    {
        HeapDestroy(heap);
        return FAIL;
    }

    HeapDestroy(heap);

    return SUCCESS;
}

result_t TestSize(void)
{
    heap_t *heap = HeapCreate(NULL, CmpInt);
    size_t i = 0;

    for (i = 0; i < len; i++)
    {
        if (HeapSize(heap) != i)
        {
            return FAIL;
        }
        HeapPush(heap, arr + i);
    }

    HeapDestroy(heap);

    return SUCCESS;
}

static result_t MakeRemove(heap_t *heap, int to_remove, int *exp)
{
    size_t i = 0;
    void *data = NULL;
    
    data = HeapRemove(heap, MatchInt, &to_remove);
    puts("after_remove and_heapifies \n");
    printf("heap size = %lu\n" , HeapSize(heap));
	PrintVector(heap);
    for (i = 0; i < len -1; i++)
    {
        if (exp[i] != *(int *)GetVectorIndex(heap, i))
        {
            printf("1\n");
            return FAIL;
        }
        if (*(int *)data != to_remove)
        {
            printf("2\n");
            return FAIL;
        }
    }
    return SUCCESS;
}

result_t TestRemove(void)
{
    heap_t *heap = NULL;
    size_t tests = 0, i = 0;
    int exp[][7] =
        {
            {12, 9, 10, 6, 8, 5},
            {36, 9, 10, 6, 8, 5},
            {36, 9, 12, 6, 8, 5},
            {36, 10, 12, 6, 8, 5},
            {36, 10, 12, 9, 8, 5},
            {36, 9, 12, 6, 8, 10}
        };

    int remove[] = {36, 12, 10, 9, 6, 5};

    tests = sizeof exp / sizeof exp[0];

    for (i = 0; i < tests; i++)
    {
        heap = HeapCreate(NULL, CmpInt);
        InitHeap(heap);
        
        if (MakeRemove(heap, remove[i], exp[i]) == FAIL)
        {
            printf("i = %lu\n" , i);
            printf("faild on remove %d\n", remove[i]);
            PrintVector(heap);
            HeapDestroy(heap);
            return FAIL;
        }
        HeapDestroy(heap);
        heap = NULL;
    }

    return SUCCESS;
}

result_t TestPop(void)
{
    heap_t *heap = HeapCreate(NULL, CmpInt);
    int exp[] = {36, 12, 10, 9, 8, 6, 5, 4};
    size_t i = 0;
    result_t res = 0;

    InitHeap(heap);

    while (HeapIsEmpty(heap) == FALSE)
    {
        if (exp[i] != *(int *)HeapPeek(heap) && i < len)
        {
            printf("peek : %3d\nexp  : %3d\n", *(int *)HeapPeek(heap), exp[i]);
            HeapDestroy(heap);
            return FAIL;
        }

        HeapPop(heap);
        ++i;
    }

    res = HeapIsEmpty(heap) ? SUCCESS : FAIL;

    HeapDestroy(heap);

    return res;
}

int CmpInt(void *check_data, void *new_data, void *param)
{
    (void)param;
    return (*(int *)check_data) - (*(int *)new_data);
}

int MatchInt(void *check_data, void *param)
{
    (void)param;
    return (*(int *)check_data) == (*(int *)param);
}