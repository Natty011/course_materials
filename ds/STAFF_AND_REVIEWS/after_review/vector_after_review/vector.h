/******************************************************************************
*	Version 1.0
******************************************************************************/
#ifndef __VECTOR_H__     /* __VECTOR_H__ */
#define __VECTOR_H__     /* __VECTOR_H__ */

#include <stddef.h>      /* size_t */

typedef struct vector vector_t;

/******************************************************************************
*	Name: VectorCreate
*	Description: Creates a Vector Struct.
*	Arguments: The number of initial elemets the vector is to store, and 
* the size of each element.
*	Return: pointer to vector, NULL on failure
*   Complexity: complexity of malloc.
*	Notes: Allocation may fail
*          Undefined behaviour if 'capacity' is 0
******************************************************************************/
vector_t *VectorCreate(size_t capacity, size_t element_size);

/******************************************************************************
*	Name: VectorCreate
*	Description: Frees all dynamically allocated memory to the vector
*	Arguments: A pointer to the vector to be freed
*	Return: Nothing
*   Complexity: Dependant on system call complexity
*	Notes: If 'vector' is NULL, no operations will be performed
******************************************************************************/
void VectorDestroy(vector_t *vector);

/******************************************************************************
*	Name: VectorPushBack
*	Description: pushing a new data to the end of vector data structure
*	Arguments: pointer to vector struct, new added element
*	Return: Returns status - 0 on success , otherwise 1
*   Complexity: O(n), n=size of element(new_data)
*	Notes: If the vector is full, the vector will grow and reallocate
******************************************************************************/
int VectorPushBack(vector_t *vector, const void *new_data);

/******************************************************************************
*	Name: VectorPopBack
*	Description: Removes the furthest element from the vector
*	Arguments: Pointer to a 'vector_t' struct
*	Return: N\A
*   Complexity: O(1)
*	Notes: Does not resize the vector, user must shrink the -
*          vector when necessary
******************************************************************************/
void VectorPopBack(vector_t *vector);

/******************************************************************************
*	Name: VectorGetAccess
*	Description: get access to the member of 'vector' at index 'index'.
*	Arguments: pointer to a vector, and an index (size_t).
*	Return: pointer to member of 'vector' at index 'index'.
*   Complexity: O(1).
*	Notes: Undefined behaviour if 'vector' is NULL or 'index' is out of range
*          Returned pointer may be dangling after class function calls
******************************************************************************/
void *VectorGetAccess(const vector_t *vector, size_t index);

/******************************************************************************
*	Name: 			VectorReserve
*	Description:	Enlarge the vector to a desired amount of elements
*	Arguments:		Pointer to a vector and desired capacity (number of elements)
*	Return: 		Returns status - 0 on success , otherwise 1
*   Complexity:		Dependant on system call complexity
*	Notes: Undefined behaviour if 'vector' is NULL or when new_capacity = 0
*          Does not support the user when 'new_capcity' is equal to capacity
******************************************************************************/
int VectorReserve(vector_t *vector, size_t new_capacity);

/******************************************************************************
*	Name:           VectorShrink
*	Description:    Function that updates the vector capacity to be equal 
*                   to the vector size
*	Arguments:      Pointer to a vector. 
*	Return:         Returns status - 0 on success , otherwise 1
*   Complexity:     Dependant on system call complexity
*	Notes:          Undefined behaviour if 'vector' is NULL
******************************************************************************/
int VectorShrink(vector_t *vector);

/******************************************************************************
*	Name: VectorCapacity
*	Description: Returns the vector's capacity
*	Arguments: "vector" - Referenced stack object
*	Return: Returns the capacity of the vector
*   Complexity: O(1).
*	Notes: Undefined behaviour if 'vector' is NULL
******************************************************************************/
size_t VectorCapacity(const vector_t *vector);

/******************************************************************************
*	Name: VectorSize
*	Description: returns the given vector's size (occupied space)
*	Arguments: "vector" - refrence to a vector object
*	Return: size of the vector
*   Complexity: O(1)
*	Notes: Undefined behaviour if 'vector' is NULL
******************************************************************************/
size_t VectorSize(const vector_t *vector);

#endif                  /* __VECTOR_H__ */
