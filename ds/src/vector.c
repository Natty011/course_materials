/***************************************
* Author : Natty
* Reviewer : Idan
* Date : 09 / 12 / 2024
* Last update: 10 / 12 / 2024
*****************************************/

#include <assert.h> /* assert */
#include <stdlib.h> /* malloc, free, realloc*/
#include <string.h> /* memcpy */
#include "vector.h" /*  */

#define GrowFactor 2
/****************struct and enum declaration declaration*********************/

struct vector
{

	size_t capacity;
	size_t current_size;
	size_t element_size;
	char* array;

};

/** possible return values */
typedef enum
{

	VECTOR_SUCCESS,
	VECTOR_OPERATION_FAIL

}VectorResult;

/***************End of struct and enum declaration declaration*******/


/********************  vectorCreate  ****************************/
vector_t *VectorCreate(size_t capacity, size_t element_size)
{
	vector_t* p_vector = NULL;
	p_vector = (vector_t*)malloc(sizeof(struct vector));
	
	if ( NULL == p_vector )
	{
		return NULL;
	}
	
	p_vector->array =(char*)malloc(capacity*element_size);
	
	if ( NULL == p_vector->array )
	{
		free(p_vector);
		p_vector = NULL;
		return NULL;
	}
	
	p_vector->element_size = element_size;
	p_vector->capacity = capacity;
	p_vector->current_size = 0;
	return 	p_vector;
}	
/********************  VectorDestroy  ****************************/
void VectorDestroy(vector_t *vector)
{
	if( NULL != vector)
	{
		free(vector->array);
		vector->array = NULL;
		free(vector);
		vector = NULL;
	}
}
/********************  VectorPushBack  ****************************/
int VectorPushBack(vector_t *vector, const void *new_data)
{

	size_t vec_cap = vector->capacity;
	size_t vec_elem_size = vector->element_size;
	size_t vec_curr_size = vector->current_size;
	size_t new_size = vec_cap * vec_elem_size * GrowFactor;
	
	assert(vector);
	
	if( vec_curr_size == vec_cap )
	{
		
		if( VectorReserve( vector , vec_cap * GrowFactor ) == 1 )
		{
			return VECTOR_OPERATION_FAIL;
		}			
	}

	memcpy( vector->array + vec_curr_size * vec_elem_size,
			new_data, vec_elem_size
		  );
	++vector->current_size;
	
	return VECTOR_SUCCESS;
}

/********************  VectorPop  ****************************/
void VectorPopBack(vector_t *vector)
{
	assert(vector);
    --vector->current_size;	
}
/********************  VectorGetAccess  ****************************/
void *VectorGetAccess(const vector_t *vector, size_t index)
{
	assert(vector);
	return vector->array + index * vector->element_size;
}

/********************  VectorReserve  ****************************/
int VectorReserve(vector_t *vector, size_t new_capacity)
{
	char* temp_array = NULL;
	size_t new_size = new_capacity * vector->element_size;
	
	assert(vector);
	
	temp_array = (char*)realloc(vector->array, new_size);
	
	if( NULL == temp_array )
	{
		return VECTOR_OPERATION_FAIL;
	}
				
	vector->array = temp_array;
	vector->capacity = new_capacity;
	
	return VECTOR_SUCCESS;	
}

/********************  VectorShrink  ****************************/
int VectorShrink(vector_t *vector)
{
	return VectorReserve(vector, vector->current_size );
}

/********************  VectorSize  ****************************/
size_t VectorSize(const vector_t *vector)
{
	assert(vector);
	return vector->current_size;
}
/********************  VectorCapacity  ****************************/
size_t VectorCapacity(const vector_t *vector)
{
	assert(vector);
	return vector->capacity;
}








