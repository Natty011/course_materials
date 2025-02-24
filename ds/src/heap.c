/***************************************
* Author : Natty
* Reviewer : Rawan
* Date : 19 / 02 / 2025
* Last update: 22 / 02 / 2025
*****************************************/
#define PRINTS
#ifdef PRINTS
	#include <stdio.h> 
#endif
#include <assert.h> 	/* assert */
#include <stdlib.h> 	/* malloc, free */

#include <string.h> /* memcpy */

#include "heap.h" 
#include "vector.h" 
#include "aux_func.h"

#define ELEMENT_SIZE		sizeof(size_t)

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
	/* param is in the index 0 in the array(vector)*/
	expand_cmp_func_t cmp_func;	
};

/******************************************************************************/
/************************ ststic functions declartions ************************/
static void SwapQuick(void** ptr1, void** ptr2);
static size_t IsExist(heap_t* heap , match_func_t match_func , void* param );
static int MatchFuncPop( void* check_data , void* user_param );
static int HeapifyDown(heap_t* heap, size_t parent, size_t size );
static int HeapifyUp(heap_t* heap, size_t parent, size_t size );

#ifdef PRINTS
void PrintArray( heap_t* heap );							
#endif
/*******************End Of Static Functions declartions************************/
/******************************************************************************/

/******************************************************************************/
/********************  HeapCreate  ****************************/
heap_t *HeapCreate(void* param, expand_cmp_func_t cmp_func)
{
	size_t capacity = 32;
	heap_t* heap_p = ( heap_t* )malloc( sizeof(heap_t) );

	if(NULL == heap_p)
	{
		return NULL;
	}
	
	heap_p->vector =  VectorCreate(capacity,  ELEMENT_SIZE ); 
	if ( NULL == heap_p->vector )
	{
		free( heap_p);
		heap_p = NULL;

		return NULL;
	}

	heap_p->cmp_func = cmp_func;

	if ( VectorPushBack( heap_p->vector, &param ) ) 
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
	return  ! ( VectorSize( heap->vector ) - 1 );
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
	
	size_t size = 0, res = 0 ;
	assert( heap);
	
	if ( VectorPushBack( heap->vector, &data) )
	{
		return FAIL;
	}
	/* must to be : size >= 1, if size == 1 is allready sorted */
	size = HeapSize(heap); 

	res = HeapifyUp(heap, size/2, size );

	return res;

}
/********************  HeapRemove  ****************************/

void* HeapRemove( heap_t* heap , match_func_t match_func , void* match_param )
{
	size_t last_element_index = 0, to_remove = 0, size = 0;
	int res = 0;
	assert(heap);

	if ( HeapIsEmpty( heap ) )
	{
		return NULL;
	}


	to_remove = IsExist( heap , match_func, match_param);


	if( FALSE == to_remove )
	{
		return NULL;
	}

	/* must to be : size >= 1, if size == 1 is allready sorted */
	last_element_index = HeapSize(heap); 

	SwapQuick( *(void**)VectorGetAccess( heap->vector, last_element_index),
		*(void**)VectorGetAccess( heap->vector, to_remove) );


	VectorPopBack( heap->vector );
	size = HeapSize(heap);


	last_element_index = to_remove;
	/*printf("parent1 = %ld \n", parent);*/

	res = HeapifyDown(heap, last_element_index, size);
	/* ( SUCCESS == HeapifyDown(heap, parent, size) ) ? param : NULL*/
	/*res = HeapifyUp(heap, size/2, size );*/
	/*printf("parent2 = %ld \n", parent);*/
	/*parent = parent / 2;*/
	res = HeapifyUp(heap, last_element_index / 2, size );

	return SUCCESS == res ? match_param : NULL ;

}

/********************  HeapPop  ****************************/
void HeapPop( heap_t* heap )
{
	void **data = NULL;

	assert(heap);

	if ( HeapIsEmpty( heap ) )
	{
		return;
	}

	data = (void**)HeapPeek(heap);

	HeapRemove(heap, MatchFuncPop, data );
}

/********************  MatchFuncPop  ****************************/
static int MatchFuncPop( void* check_data , void* user_param )
{
	assert(check_data);
	assert(user_param);

	return *(void**)check_data == *(void**)user_param;
}

/*******************Static Functions definition************************/

/********************  MatchFuncPop  ****************************/

static int HeapifyDown(heap_t* heap, size_t parent_index, size_t size )
{
	void *param = *(void**)VectorGetAccess( heap->vector, 0);
	void **largest = NULL, **parent = NULL , **right = NULL;
	size_t max_index =0;
	while ( parent_index < size   ) 
	{
		parent = (void**)VectorGetAccess( heap->vector, parent_index);

		if ( parent_index*2 > size )
		{
			return SUCCESS;
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
			SwapQuick( parent , largest );
			parent_index = max_index;
		}
		else
		{
			return  parent_index;
		}
	}

	return SUCCESS;
}

/********************  HeapifyUp  ****************************/

static int HeapifyUp(heap_t* heap, size_t parent_index, size_t size )
{
	vector_t *vector = heap->vector;
	void **parent = (void**)VectorGetAccess( vector, parent_index);
	void* param = *(void**)VectorGetAccess( vector, 0);
	void **last_element = (void**)VectorGetAccess( vector, size);
 /* parent*/
	while ( parent_index > 0 && heap->cmp_func(*parent , *last_element , param) < 0 )
	{
		
		SwapQuick( parent , last_element );

		last_element = (void**)VectorGetAccess( vector, parent_index);
		parent = (void**)VectorGetAccess( vector, size / 2);
	}

	return SUCCESS;
}

/********************  IsExist  ****************************/

static size_t IsExist(heap_t* heap , match_func_t match_func , void* param )
{
	size_t size = 1 ;

	while( size <= HeapSize( heap ) )
	{
		if ( match_func(*(void**)VectorGetAccess(heap->vector, size ) , param ) )
		{
				return size;
		}
			++size;
	}

	return FALSE; /* the param isn't in the heap */
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
        printf("%3d", **(int **)VectorGetAccess(v, i));
    }
    putchar('\n');
}

void *GetVectorIndex(heap_t *h, size_t index)
{
    return *(void **)VectorGetAccess(h->vector, index);
}
#endif

/***************************SwapQuick***************************/
static void SwapQuick(void** ptr1, void** ptr2)
{
	void* temp = NULL;
	
	assert( ptr1 );
	assert ( ptr2 );
	
	temp = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = temp;
}


/*******************End Of Static Functions definition************************/








