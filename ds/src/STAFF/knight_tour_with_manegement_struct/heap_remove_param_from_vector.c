/***************************************
* Author : Natty
* Reviewer : Rawan
* Date : 19 / 02 / 2025
* Last update: 25 / 02 / 2025
*****************************************/
/*#define PRINTS*/
#ifdef PRINTS
	#include <stdio.h> /* printf */
#endif
#include <assert.h> 	/* assert */
#include <stdlib.h> 	/* malloc, free */

#include "heap.h" 
#include "vector.h" 
#include "aux_func.h"

#define ELEMENT_SIZE		sizeof(size_t)
#define CAPACITY 			16

/***************************** Success / Fail Enum ****************************/

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

/******************************************************************************/
/***************************** Management struct ******************************/
struct heap
{
	vector_t *vector;
	void *param;
	/* param is in the index 0 in the array(vector)*/
	expand_cmp_func_t cmp_func;	
};

/******************************************************************************/
/************************ ststic functions declartions ************************/
static void Swap(void** ptr1, void** ptr2);
static size_t IsExist(heap_t* heap , match_func_t match_func , void* param );
static int MatchFuncPop( void* check_data , void* user_param );
static void HeapifyDown(heap_t* heap, size_t parent );
static void HeapifyUp(heap_t* heap, size_t index );

#ifdef PRINTS
void PrintArray( heap_t* heap );							
#endif
/*******************End Of Static Functions declartions************************/
/******************************************************************************/

/******************************************************************************/
/********************  HeapCreate  ****************************/
heap_t *HeapCreate(void* param, expand_cmp_func_t cmp_func)
{
	heap_t* heap_p = ( heap_t* )malloc( sizeof(heap_t) );
	vector_t *vector = NULL;
	void **dummy_ptr = NULL;
	void *dummy = NULL;
	dummy_ptr = &dummy;
	if(NULL == heap_p)
	{
		return NULL;
	}

	vector = VectorCreate(CAPACITY,  ELEMENT_SIZE ); 

	if ( NULL == vector )
	{
		free( heap_p);
		heap_p = NULL;

		return NULL;
	}

	heap_p->cmp_func = cmp_func;
	heap_p->vector = vector;
	heap_p->param = param;

	if ( VectorPushBack( heap_p->vector, dummy_ptr ) ) 
	{
		HeapDestroy( heap_p );
		heap_p->vector = NULL;
		heap_p = NULL;

		return NULL;
	}

	return heap_p;
}

/********************  HeapDestroy  ****************************/
void HeapDestroy(heap_t *heap)
{
	if( NULL != heap)
	{
		VectorDestroy(heap->vector);
		heap->vector = NULL;

		free( heap );
		heap = NULL;
	}
}

/********************  HeapIsEmpty  ****************************/
int HeapIsEmpty(const heap_t *heap)
{
	assert( heap );
	return  VectorSize( heap->vector ) == 1;
}
/********************  HeapSize  ****************************/
size_t HeapSize(const heap_t *heap)
{
	assert( heap );
	return VectorSize( heap->vector) - 1; 
}

/********************  HeapPeek  ****************************/
void* HeapPeek( const heap_t* heap )
{
	void* data = NULL;
	assert(heap);

	if ( ! HeapIsEmpty(heap)  )
	{
		data = *(void**)VectorGetAccess( heap->vector, 1);
	}

	return  data; 
}
/********************  HeapPush  ****************************/
int HeapPush( heap_t* heap , const void* data )
{
	
	size_t size = 0;
	assert( heap);
	
	if ( VectorPushBack( heap->vector, &data) )
	{
		return FAIL;
	}
	/* must to be : size >= 1, if size == 1 is allready sorted */
	size = HeapSize(heap); 
	if ( 1 < size )
	{
		HeapifyUp(heap, size );
	}
	return SUCCESS;

}
/********************  HeapRemove  ****************************/

void* HeapRemove( heap_t* heap , match_func_t match_func , void* match_param )
{
	size_t last_element_index = 0, to_remove = 0;
	void **to_remove_ptr = NULL, **last_element_ptr = NULL;

	assert(heap);

	if ( HeapIsEmpty( heap ) )
	{
		return NULL;
	}


	to_remove = IsExist( heap , match_func, match_param);

	if( 0 == to_remove )
	{
		return NULL;
	}

	last_element_index = HeapSize(heap); 

	to_remove_ptr = VectorGetAccess( heap->vector, to_remove);
	last_element_ptr = VectorGetAccess( heap->vector, last_element_index);

	Swap( last_element_ptr, to_remove_ptr);
	VectorPopBack( heap->vector );
	
	if( (1 <  HeapSize(heap) ) && ( last_element_index != to_remove ))
	{
		HeapifyDown(heap, to_remove);
		HeapifyUp(heap, to_remove );
	
	}
	
	return match_param ;
}

/********************  HeapPop  ****************************/
void HeapPop( heap_t* heap )
{
	void *data = NULL;

	assert(heap);

	if ( HeapIsEmpty( heap ) )
	{
		return;
	}

	data = (void*)HeapPeek(heap);

	HeapRemove(heap, MatchFuncPop, data );
}

/********************  MatchFuncPop  ****************************/
static int MatchFuncPop( void* check_data , void* user_param )
{
	assert(check_data);
	assert(user_param);
	return check_data == user_param;
}

/*******************Static Functions definition************************/

/********************  MatchFuncPop  ****************************/

static void HeapifyDown(heap_t* heap, size_t parent_index )
{
	void* param = *(void**)heap->param;
	void **largest = NULL, **parent = NULL , **right = NULL;
	size_t max_index = 0, size = HeapSize(heap);

	while ( parent_index < size   ) 
	{
		parent = (void**)VectorGetAccess( heap->vector, parent_index);

		if ( parent_index*2 > size )
		{
			return ;
		}
	
		largest = (void**)VectorGetAccess( heap->vector, 2 * parent_index);
		max_index = parent_index*2;
		
		if (parent_index*2 + 1 <= size)
		{
			right = (void**)VectorGetAccess(heap->vector, 2 * parent_index + 1);
			if ( heap->cmp_func(*largest ,*right ,param) < 0  )
			{
				largest = right;
				++max_index;
			}
		}

		if ( heap->cmp_func(*parent , *largest , param) < 0 )
		{
			Swap( parent , largest );
			parent_index = max_index;
		}
		else
		{
			break;
		}
	}
}

/********************  HeapifyUp  ****************************/

static void HeapifyUp(heap_t* heap, size_t index )
{
	
	vector_t *vector = heap->vector;
	void **element_to_heapify_up = (void**)VectorGetAccess( vector, index);
	size_t parent_index = index/2;
	void **parent = (void**)VectorGetAccess( vector, parent_index);
	void* param = *(void**)heap->param;

	while ( parent_index > 0 && heap->cmp_func(*parent ,
				 *element_to_heapify_up , param) < 0 )
	{
		Swap( parent , element_to_heapify_up );

		index = parent_index ;
		parent_index /= 2; 

		parent = (void**)VectorGetAccess( vector, parent_index);
		element_to_heapify_up = (void**)VectorGetAccess( vector, index);
	}
}

/********************  IsExist  ****************************/

static size_t IsExist(heap_t* heap , match_func_t match_func , void* param )
{
	size_t index = 1 ;
	while( index <= HeapSize( heap ) )
	{
		if ( match_func(*(void**)VectorGetAccess(heap->vector, index ) , param ) )
		{
				return index;
		}
			++index;
	}

	return FALSE; /* the param isn't in the heap */
}

/***************************Swap***************************/
static void Swap(void** ptr1, void** ptr2)
{
	void* temp = NULL;
	
	assert( ptr1 );
	assert ( ptr2 );
	
	temp = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = temp;
}


#ifdef PRINTS
void PrintArray( heap_t* heap )
{
	size_t size = 1 ;
	int* element = NULL;
	printf("HeapArray[] = \n" );
	while( size <= HeapSize( heap ) )
	{
		element = *(void**)VectorGetAccess(heap->vector, size );
		printf("index = %ld , value = %d \n", size, *element );
			++size;
	}
}
void PrintVector(heap_t *h)
{
    vector_t *v = h->vector;
    size_t len = VectorSize(v), i = 0;

    for (i = 0; i < len; ++i)
    {
        printf("%3d", **(int **)VectorGetAccess(v, i+1));
    }
    putchar('\n');
}

void *GetVectorIndex(heap_t *h, size_t index)
{
    return *(void **)VectorGetAccess(h->vector, index);
}
#endif



/*******************End Of Static Functions definition************************/








