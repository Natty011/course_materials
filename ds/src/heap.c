/***************************************
* Author : Natty
* Reviewer : 
* Date : 19 / 02 / 2025
* Last update: 19 / 02 / 2025
*****************************************/
#ifdef PRINTS
	#include <stdio.h> 
	#include <math.h> 	
#endif

#include <assert.h> 	/* assert */
#include <stdlib.h> 	/* malloc, free */

#include <stdio.h> 
#include <string.h> /* memcpy */
#include "heap.h" 
#include "vector.h" 
#include "aux_func.h"

#define MAX( a , b )		( ( (a) > (b) ) ? (a) : (b) )
#define UNUSED( var )       ( (void)var )
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
/*************************** Left child / Right child Enum ********************/

typedef enum
{
	LEFT = 0  ,
	RIGHT = 1 ,
	NUMBER_OF_CHILDRENS
	
} child_pose_t;
/******************************************************************************/


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
#ifdef PRINTS

									
#endif
/*******************End Of Static Functions declartions************************/


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
	
	heap_p->vector =  VectorCreate(capacity,  ELEMENT_SIZE ); /* cap == 3*/
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
	return VectorGetAccess( heap->vector, 1);
}
/********************  HeapPush  ****************************/
int HeapPush( heap_t* heap , const void* data )
{
	size_t parent = 0, i = 0;
	assert( heap);
	
	if ( VectorPushBack( heap->vector, data) )
	{
		return FAIL;
	}

	i = HeapSize(heap); /* must to be : size >= 1, if size == 1 is allready sorted */
	parent = i / 2;

	/* Heapify up */
	while ( parent > 0 && 
		heap->cmp_func( VectorGetAccess( heap->vector, parent),
				 VectorGetAccess( heap->vector, i), heap->param ) < 0 )
	{
		
		if ( FAIL == SwapQuick( VectorGetAccess( heap->vector, parent),
 						VectorGetAccess( heap->vector, i), ELEMENT_SIZE) )
		{
			return FAIL;	
		}

		i = parent;
		parent = i / 2;

	}

	#ifdef PRINTS
	printf(" HeapPeek(heap)  = %d", *(int*)HeapPeek(heap) );
	#endif

	return SUCCESS;
}

/*******************Static Functions definition************************/

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








