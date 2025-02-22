/***************************************
* Author : Natty
* Reviewer : Rawan
* Date : 19 / 02 / 2025
* Last update: 22 / 02 / 2025
*****************************************/
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
	void *param;
	expand_cmp_func_t cmp_func;	
};

/******************************************************************************/
/************************ ststic functions declartions ************************/
static int SwapQuick(void* ptr1, void* ptr2, size_t element_size);
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
	size_t capacity = 16;
	size_t* dummy_start = NULL;
	size_t dummy = 0;
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
	heap_p->param = param;

	dummy_start = &dummy;
	/* to start from index 1 */
	if ( VectorPushBack( heap_p->vector, dummy_start ) ) 
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
	assert(heap);
	/*changed because of PQueueDequeue, need to check if thare is an affect
	after the change. if not, remove this commant */
	/*return  VectorGetAccess( heap->vector, 1);*/
	return  (! HeapIsEmpty(heap) ) ? VectorGetAccess( heap->vector, 1) : NULL; 
}
/********************  HeapPush  ****************************/
int HeapPush( heap_t* heap , const void* data )
{
	
	size_t size = 0, res = 0 ;
	assert( heap);
	
	if ( VectorPushBack( heap->vector, data) )
	{
		return FAIL;
	}
	/* must to be : size >= 1, if size == 1 is allready sorted */
	size = HeapSize(heap); 

	#ifdef PRINTS
			printf("afterpush_before_heapify_up \n");
			PrintArray( heap );
	#endif
	res = HeapifyUp(heap, size/2, size );

	#ifdef PRINTS
			printf("afterpush_after_heapify_up \n");
			PrintArray( heap );
	#endif
	return res;
	/*return HeapifyUp(heap, size/2, size );*/

}
/********************  HeapRemove  ****************************/

void* HeapRemove( heap_t* heap , match_func_t match_func , void* param )
{
	size_t parent = 0, to_remove = 0, size = 0;

	assert(heap);

	if ( HeapIsEmpty( heap ) )
	{
		return NULL;
	}

	to_remove = IsExist( heap , match_func, param);

	if( FALSE == to_remove )
	{
		return NULL;
	}

	/* must to be : size >= 1, if size == 1 is allready sorted */
	parent = HeapSize(heap); 

	if( FAIL == SwapQuick( VectorGetAccess( heap->vector, parent),
 						VectorGetAccess( heap->vector, to_remove), ELEMENT_SIZE) )
	{
			return NULL;	
	}

	VectorPopBack( heap->vector );
	size = HeapSize(heap);
	parent = to_remove;

	return ( SUCCESS == HeapifyDown(heap, parent, size) ) ? param : NULL;
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

	data = HeapPeek(heap);

	HeapRemove(heap, MatchFuncPop, data );
}

/********************  MatchFuncPop  ****************************/
static int MatchFuncPop( void* check_data , void* user_param )
{
	assert(check_data);
	assert(user_param);

	return ! ( (size_t*)check_data - (size_t*)user_param );
}

/*******************Static Functions definition************************/

/********************  MatchFuncPop  ****************************/

static int HeapifyDown(heap_t* heap, size_t parent, size_t size )
{
	size_t left = 0, right = 0, largest = 0;
	int swapped_occured = FALSE;
	
	while ( parent < size   ) 
	{
		largest = parent;
		swapped_occured = FALSE;
		left = 2 * parent;
		right = left + 1;

		if( left <= size && heap->cmp_func( VectorGetAccess( heap->vector, parent),
							VectorGetAccess( heap->vector, left), heap->param ) < 0 )
		{
			largest = left;
		}

		if( right <= size && heap->cmp_func( VectorGetAccess( heap->vector, largest),
							VectorGetAccess( heap->vector, right), heap->param ) < 0 )
		{
			largest = right;
		}		

		if( largest != parent )
		{
			if( FAIL == SwapQuick( VectorGetAccess( heap->vector, parent),
							VectorGetAccess( heap->vector, largest), ELEMENT_SIZE) )
			{
				return FAIL;	
			}

			parent = largest;
			swapped_occured = TRUE;
		}

		if(!swapped_occured)
		{
			break;
		}
	}

	return SUCCESS;
}

/********************  HeapifyUp  ****************************/

static int HeapifyUp(heap_t* heap, size_t parent, size_t size )
{
	while ( parent > 0 && 
		heap->cmp_func( VectorGetAccess( heap->vector, parent),
				VectorGetAccess( heap->vector, size), heap->param ) < 0 )
	{
		
		if ( FAIL == SwapQuick( VectorGetAccess( heap->vector, parent),
						VectorGetAccess( heap->vector, size), ELEMENT_SIZE) )
		{
			return FAIL;	
		}

		size = parent;
		parent = size / 2;
	}

	return SUCCESS;
}

/********************  IsExist  ****************************/

static size_t IsExist(heap_t* heap , match_func_t match_func , void* param )
{
	size_t size = 1 ;

	while( size <= HeapSize( heap ) )
	{
		if ( match_func(VectorGetAccess(heap->vector, size ) , param ) )
		{
			#ifdef PRINTS
				printf("size_isExist = %lu \n", size);
				PrintArray( heap );
			#endif
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
	printf("HeapArray[] = \n" );
	while( size <= HeapSize( heap ) )
	{
		printf("index = %ld , value = %c \n", size, 
			 *(char*)VectorGetAccess(heap->vector, size ) );

			++size;
	}
}
#endif

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


/*******************End Of Static Functions definition************************/








