/***************************************
* Author : Natty
* Reviewer : 
* Date : 17 / 02 / 2025
* Last update: 17 / 02 / 2025
*****************************************/

#include <assert.h> 	/* assert */
#include <stdlib.h> 	/* malloc, free */
#include <string.h> 	/* memcmp */
#include "hash_table.h" 
#include "dlist.h" 
#include "aux_func.h"           /* match_func_t          */

#define NULL_ITER                     {0}

/****************struct and enum declaration*********************/

struct hash_table
{
	size_t capacity;	/* size of the array -> result_hash_func % capacity will bring the index */
	size_t size; /* size of the total node ( sum of each dlist */
	dlist_t **hash_array; /* dlist_t* hash_array[ size ] */
	match_func_t match_func;
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

/***************************function declaration**************************/
/*static int match_func(void *check_data, void *user_param);*/

/***************************End of function declaration******************/

/********************  HashTableCreate  ****************************/
hash_table_t *HashTableCreate(hash_func_t hash_func, match_func_t match_func, 
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
 	 			DListDestroy( *( (table->hash_array) + i - 1 ) );
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
	table->cmp_func = match_func;
	table->hash_func = hash_func;
	
	return table;
 	
}
/********************  HashTableDestroy  ****************************/  
void HashTableDestroy(hash_table_t *table)
{
	size_t i = 0;
	if( NULL == table )
	{
		return;
	}

	for( i = 0; i < table->capacity ; ++i )
	{
		DListDestroy( *( (table->hash_array) + i  ) );
 	 	*( (table->hash_array) + i ) = NULL;
	}
	
	free( table->hash_array );
 	table->hash_array = NULL;
 	 		
 	free(table);
 	table = NULL;

}
	/*return !(SUCCESS == (*(int*)check_data - *(int*)new_data));*/
/*	
static int match_func(void* check_data , void* data_to_remove)
{
	return memcmp( check_data, data_to_remove);

}
*/
/********************  HashTableRemove  ****************************/ 
/* need to update the size after the removing */

void HashTableRemove(hash_table_t *table, void *value)
{
	size_t index = 0;
	dlist_t* dlst_indx = NULL;
	dlist_iter_t start = NULL_ITER;
	
	assert(table);
	
	/*return the index of the correct dlist*/
	index = table->hash_func( value, table->capacity );
 	
	dlst_indx = *(table->hash_array) + index;
	
	if( DListIsEmpty(dlst_indx) )
	{
		return;
	}
	
	start = DListBegin(dlst_indx);
	start = DListFind(start, DListEnd(dlst_idnx),match_func, value);
	
	if( ! DListIterIsEqual( start, DListEnd(dlst_indx) ) )
	{
		DListRemove(start);
	}		 
}

/********************  HashTableSize  ****************************/ 

size_t HashTableSize(const hash_table_t *table)
{
	assert(table);
	return table->size;
}

/********************  HashTableIsEmpty  ****************************/ 
int HashTableIsEmpty(const hash_table_t *table)
{
	assert(table);
	return !HashTableSize(table);
}

/********************  HashTableFind  ****************************/ 

void *HashTableFind(const hash_table_t *table, void *equivalent_value)
{
	assert(table);
	
	
	
}

/********************  HashTableForEach  ****************************/ 
/*
int HashTableForEach(hash_table_t *table, op_func_t op_func, 
                             void *user_param)
{


}                             

*/

