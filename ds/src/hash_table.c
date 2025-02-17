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
 	
 	table->hash_array  = (dlist_t*)malloc( capacity * sizeof(dlist_t) );
 	
 	if( NULL == table->hash_array )
 	{
 		free(table);
 		table = NULL;
 		
 		return NULL;
 	}
 	
 	for ( i = 0; i < capacity; ++i )
 	{
 	 	if ( NULL == *( (table->hash_array) + i ) = DListCreate() )
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
  
/********************  SortlistIsEmpty  ****************************/
int SortlistIsEmpty(const sort_list_t* sort_list)
{
	 assert(sort_list);	
	 return DListIsEmpty(SRLISTTODLIST(sort_list));
}

/********************  SortlistBegin  ****************************/
sort_list_iter_t SortlistBegin(const sort_list_t* sort_list)
{

	sort_list_iter_t itr = {0};
		
	assert(sort_list);
	
	itr.iter = DListBegin(SRLISTTODLIST(sort_list));
	
	# ifndef NDEBUG
		itr.list = (sort_list_t*)sort_list;
	#endif
	 
	return itr;
}

/********************  SortlistEnd  ****************************/
sort_list_iter_t SortlistEnd(const sort_list_t* sort_list)
{
	
	sort_list_iter_t itr = {0};
		
	assert(sort_list);
	
	itr.iter = DListEnd(SRLISTTODLIST(sort_list));
	
	# ifndef NDEBUG
		itr.list = (sort_list_t*)sort_list;
	#endif
	 
	return itr;

}

/********************  SortlistNext  ****************************/  
sort_list_iter_t SortlistNext(sort_list_iter_t iter)
{

	iter.iter = DListNext(iter.iter); 
	
	return iter;
}

/********************  SortlistPrev  ****************************/  
sort_list_iter_t SortlistPrev(sort_list_iter_t iter)
{
	iter.iter = DListPrev(iter.iter); 
	
	return iter;
}

/********************  SortlistIterIsEqual  ****************************/   
int SortlistIterIsEqual( sort_list_iter_t iter1 , sort_list_iter_t iter2 )
{
	
	int res = TRUE;
	
	# ifndef NDEBUG
		res = (iter1.list == iter2.list);
	#endif
	
	return res * DListIterIsEqual(iter1.iter, iter2.iter);
}

/********************  SortlistGetData  ****************************/
void* SortlistGetData(sort_list_iter_t iter)
{
	return DListGetData(iter.iter);
}


/********************  SortlistSize  ****************************/
size_t SortlistSize(const sort_list_t* sort_list)
{	
	assert(sort_list);	
		
	return DListCount(SRLISTTODLIST(sort_list));
}

/********************  SortlistDestroy  ****************************/
void SortlistDestroy( sort_list_t* sort_list )
{

	assert(sort_list);
	
	if(	 NULL == sort_list )
	{
		return;
	}
	DListDestroy(SRLISTTODLIST(sort_list));
	
	SRLISTTODLIST(sort_list) = NULL;
	free(sort_list);
	sort_list = NULL;
}


/********************  SortlistRemove  ****************************/ 
sort_list_iter_t SortlistRemove(sort_list_iter_t what )
{	
	 
	what.iter = DListRemove(what.iter); 	
			
	return what; 	
}

/******************  SortlistInsert  ***********************/

sort_list_iter_t SortlistInsert(sort_list_t* sort_list ,const void *data)
{
	
	sort_list_iter_t next_iter = {0};
	void* temp_data = NULL;
	int res_cmp = FALSE;
	
	assert(sort_list);
				
	next_iter = SortlistBegin(sort_list); 

	temp_data = SortlistGetData(next_iter);

	
	if( !SortlistIsEmpty(sort_list) )
	{
		res_cmp = sort_list->cmp_func(temp_data, (void*)data);
	}
	

	while( !SortlistIterIsEqual(next_iter,SortlistEnd(sort_list)) && 
			res_cmp <= FALSE )
	  
	{

		next_iter = SortlistNext(next_iter);
		if( NULL == SortlistNext(next_iter).iter)
		{
			break;
		}
		temp_data = SortlistGetData(next_iter);
		res_cmp = sort_list->cmp_func(temp_data, (void*)data);	
		
	}
		
	next_iter.iter = DListInsertBefore(SRLISTTODLIST(sort_list),
							 next_iter.iter , data);
							 
 	return next_iter;
 			
}

/********************  SortlistPopFront  ****************************/ 
void* SortlistPopFront( sort_list_t* sort_list )
{	
	assert(sort_list);
	
	return DListPopFront(SRLISTTODLIST(sort_list));	
}

/********************  SortlistPopBack  ****************************/ 

void* SortlistPopBack( sort_list_t* sort_list )
{
	assert(sort_list);
	
	return DListPopBack(SRLISTTODLIST(sort_list));	
 
}

/********************  SortlistForEach  **************************/ 
int SortlistForEach(sort_list_iter_t start, sort_list_iter_t end,
                     operation_func_t op_func ,void* user_param)
{
	
	assert(start.list == end.list);
	assert(op_func);
	
	return DListForEach(start.iter, end.iter, op_func, user_param);	
}                     

/********************  SortlistFindIf  **************************/ 

sort_list_iter_t SortlistFindIf( sort_list_iter_t start, sort_list_iter_t end,
                                match_func_t match_func , void* user_param )
{
		
	assert(start.list == end.list);
	
	assert(match_func);
			
	start.iter = DListFind(start.iter, end.iter, match_func, user_param);
		
	return start;
	
}

/********************  SortlistFind  ****************************/   
sort_list_iter_t SortlistFind(sort_list_t* sort_list , sort_list_iter_t start ,
                                  sort_list_iter_t end , void* user_param )
{		
	assert(start.list == end.list);
	assert(sort_list);	
	
	while(!SortlistIterIsEqual(start, end)) 
	{
	
		if(SUCCESS == sort_list->cmp_func(SortlistGetData(start), user_param))
		{
			return start;
		}
		
		start = SortlistNext(start);
	}

	return end;
	
} 
/********************  WhereToInsert  ****************************/ 
  
static sort_list_iter_t WhereToInsert( sort_list_t* list ,
						sort_list_iter_t dest_itr_where, void* new_data )
{
	sort_list_iter_t itr = dest_itr_where;
	sort_list_iter_t end = SortlistEnd( list );
	
	while ( ! SortlistIterIsEqual( itr , end ) )
	{
		if ( list->cmp_func( SortlistGetData( itr ) , new_data ) > 0 )
		{
			return itr;
		}
		
		itr = SortlistNext( itr );	
	}
	return itr;
}

/********************  SortlistMerge  ****************************/   

void SortlistMerge(sort_list_t *dest, sort_list_t *src)
{


	sort_list_iter_t dest_itr_where = SortlistBegin( dest );
	sort_list_iter_t src_itr ={0};
	sort_list_iter_t src_end = SortlistEnd(src);
	sort_list_iter_t tmp = {0};

	assert(dest);
	assert(src);
	assert(dest != src);
			
	while ( ! SortlistIsEmpty(src) )
	{
	
		src_itr = SortlistBegin(src);
		dest_itr_where = WhereToInsert( dest ,dest_itr_where , 
										SortlistGetData(src_itr) );
		do
		{		
			src_itr = SortlistNext( src_itr );
			if ( SortlistIterIsEqual( src_itr , src_end ) ) break;
			
		} while ( SortlistIterIsEqual( dest_itr_where ,
					WhereToInsert( dest ,dest_itr_where, 
									SortlistGetData(src_itr) ) ) );
		tmp = SortlistBegin(src);
		
		DListSplice(dest_itr_where.iter, tmp.iter, src_itr.iter);

	}
}




