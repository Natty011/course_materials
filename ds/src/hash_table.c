/***************************************
* Author : Natty
* Reviewer : 
* Date : 17 / 02 / 2025
* Last update: 17 / 02 / 2025
*****************************************/

#include <assert.h> 	/* assert */
#include <stdlib.h> 	/* malloc, free */
#include "hash_table.h" 
#include "dlist.h" 


#define NULL_ITER                     {0}

/****************struct and enum declaration*********************/

struct hash_table
{
	size_t capacity;	/* size of the array -> result_hash_func % capacity will bring the index */
	size_t size; /* size of the total node ( sum of each dlist */
	dlist_t **hash_array; /* dlist_t* hash_array[ size ] */
	cmp_func_t cmp_func;
	hash_func_t hash_func;


};

typedef enum
{
	
	SUCCESS = 0,
	OPERATION_FAIL = 1
	
}dlist_result_t;

typedef enum
{
	
	FALSE = 0,
	TRUE = 1
	
}func_result_t;

/***************End of struct and enum declaration *******/

/********************  HashTableCreate  ****************************/
hash_table_t *HashTableCreate(hash_func_t hash_func, cmp_func_t cmp_func, 
								size_t capacity )
{	
 	size_t i = 0;
 	hash_table_t *table = NULL;
 	
	assert(hash_func);
  	assert(cmp_func);
  	
  	table = (hash_table_t*)malloc(sizeof( hash_table_t ) );
  		 	
 	if(  NULL == table )
 	{
 		return NULL;
 	}
 	
 	table->hash_array  = (dlist_t**)malloc( capacity * sizeof(dlist_t*) );
 	
 	if( NULL == table->hash_array )
 	{
 		free(table);
 		table = NULL;
 		
 		return NULL;
 	}
 	
 	
 	for ( i = 0; i < capacity; ++i )
 	{
 	 	if ( NULL == ( *( (table->hash_array) + i ) = DListCreate() ) )
 	 	{
 	 		while ( i > 0 )
 	 		{
 	 			free( *( (table->hash_array) + i - 1 ) );
 	 			*( (table->hash_array) + i - 1 ) = NULL;
 	 			--i;
 	 		}
 	 		
 	 		free( table->hash_array );
 	 		table->hash_array = NULL;
 	 		
 	 		free(table);
 			table = NULL;
 		
 			return NULL;
 	 	} 
 	}
 	
 	table->capacity = capacity;
 	table->size = 0;
	table->cmp_func = cmp_func;
	table->hash_func = hash_func;
	
	return table;
 	
}
  


