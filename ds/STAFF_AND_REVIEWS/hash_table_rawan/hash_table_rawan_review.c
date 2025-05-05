/*******************************************************************************
*
*	Auther:		rawan Nabwany
*	Reviewer:	
*	Date:		17/02/25
*	worksheet:  C::Hash Table
*
*******************************************************************************/
#include <stddef.h>     /*  size_t      */
#include <stdlib.h>     /*  malloc free */
#include <assert.h>     /*  assert      */
#include <stdio.h>

#include "dlist.h"
#include "hash_table.h"

#define EMPTY_ITER NULL

/*****************************************************************************/
/********************         ENUMS AND STRUCTS                ***************/
/*****************************************************************************/

enum
{
    SUCCESS = 0 , 
    FAIL = 1
};

struct hash_table
{
    dlist_t **arr;
    size_t ht_size;
    hash_func_t hash_func;
/* sould be: match_func_t instead  cmp_func_t  */    
    match_func_t cmp_func; /* fixed by natty */
};



/*****************************************************************************/
/********************         CREATE FUNCTION                *****************/
/*****************************************************************************/
/*   sould be: match_func_t instead  cmp_func_t -> fixed by natty */
/* nice */

hash_table_t *HashTableCreate(hash_func_t hash_func, match_func_t cmp_func
                                , size_t size)
{
    
    size_t i = 0 ;
    dlist_t **dlist_arr = NULL;
    hash_table_t *hash_table = (hash_table_t *)malloc( sizeof( hash_table_t ) );

    if( !hash_table )
    {
        return NULL;
    }

    dlist_arr = ( dlist_t** )malloc( sizeof ( dlist_t* ) * size );

    if( !dlist_arr )
    {
        free( hash_table );
        hash_table = NULL;

        return NULL;
    }

    for( i = 0 ; i < size ; ++i )
    {
        if( NULL == ( dlist_arr[i] = DListCreate() ) )
        {
            break;
        }
    }
	
	/* if the allocation failed -> return NULL after the Destroyes'*/
    if( i < size  && NULL ==  dlist_arr[i] )
    {
        while( i-- )
        {
            DListDestroy ( dlist_arr[i] );
            dlist_arr[i] = NULL;
        }

    }

    hash_table->arr = dlist_arr ; 

    hash_table->ht_size = size;

    hash_table->hash_func = hash_func;

    hash_table->cmp_func = cmp_func;

    return hash_table;
}


/*****************************************************************************/
/********************         DESTROY FUNCTION                ****************/
/*****************************************************************************/
/* good */
void HashTableDestroy(hash_table_t *table)
{
    size_t i = 0 ;
    size_t size = table->ht_size;

	/* Please: Add NULL to avoid dangling pointers -> 
		 	 	*( (table->hash_array) + i ) = NULL;  */ 
    if( table )
    {
        for ( i = 0 ; i < size ; ++i )
        {
            DListDestroy( *( ( table->arr ) + i ) );
        }
    }

    free(table->arr);
    table->arr = NULL;

    free( table );
    table = NULL;
}

/*****************************************************************************/
/********************         INSERT FUNCTION                *****************/
/*****************************************************************************/
/* well done */
int HashTableInsert(hash_table_t *table, void *value)
{
    size_t idx = 0 ;
    dlist_t *dlist = NULL;
    dlist_iter_t res = EMPTY_ITER; 

    assert(table);
    
    idx =  table->hash_func( value );
    idx %= table->ht_size;

    dlist = *((table->arr) + idx); 
    
    res =  DListPushBack( dlist , value );
    
    if ( DListIterIsEqual( res , DListEnd( ( dlist )  ) ) )
    {
        return FAIL;
    }

   return SUCCESS;
}

/*****************************************************************************/
/********************         REMOVE FUNCTION                *****************/
/*****************************************************************************/
/* very good ! */
void HashTableRemove(hash_table_t *table, void *value)
{
    size_t idx = 0 ;
    dlist_t *dlist = NULL;
    dlist_iter_t res = EMPTY_ITER;


    assert(table);

    idx =  table->hash_func( value ); 
    idx %= table->ht_size;

    dlist = *((table->arr) + idx); 

    res =  DListFind( DListBegin( dlist ) , DListEnd( dlist ) 
                            , table->cmp_func ,value );

    if ( !DListIterIsEqual( res , DListEnd( ( dlist )  ) ) )
    {
        DListRemove( res );
    }
}


/*****************************************************************************/
/********************         SIZE FUNCTION                *******************/
/*****************************************************************************/
/* excellent */
size_t HashTableSize(const hash_table_t *table)
{
    size_t i = 0 ;
    size_t size = 0 ; 
    int counter = 0 ;
    dlist_t **dlist = NULL ; 

    assert( table );

    size = table->ht_size;
    dlist = table->arr;

    for ( i = 0 ; i < size ; ++i )
    {
        counter += DListCount( *(dlist + i ));
    }

    return counter;

}


/*****************************************************************************/
/********************         IS EMPTY FUNCTION                ***************/
/*****************************************************************************/

/* great */
int HashTableIsEmpty(const hash_table_t *table)
{
    assert( table) ;

    return 0 == HashTableSize(table) ; 
}


/*****************************************************************************/
/********************         FIND FUNCTION                *******************/
/*****************************************************************************/
/* wonderful  */
void *HashTableFind(const hash_table_t *table, void *equivalent_value)
{
    size_t idx = 0 ;
    dlist_t *dlist = NULL;
    dlist_iter_t res = EMPTY_ITER;

    assert( table );

    idx =  table->hash_func( equivalent_value );
    idx %= table->ht_size;

    dlist = *((table->arr) + idx);

   res =  DListFind( DListBegin( dlist ) , DListEnd( dlist ) 
                            , table->cmp_func ,equivalent_value );
    
    if ( DListIterIsEqual( res , DListEnd( ( dlist )  ) ) )
    {
        return NULL;
    }

    return DListGetData( res ); /* like :-) !! */
}

/*****************************************************************************/
/********************         FOR EACH FUNCTION                ***************/
/*****************************************************************************/
/* great */ 
int HashTableForEach(hash_table_t *table, operation_func_t op_func, 
    void *user_param)
{
    size_t i = 0 ;
    size_t size = 0 ;
    dlist_t **dlist = NULL ;
    int res = 0 ;  
    
    assert( table );

    size =  table->ht_size;
    dlist = table->arr;

    for( i = 0 ; i < size ; ++i )
    {
        res = DListForEach( DListBegin ( *(dlist + i )) , DListEnd( *(dlist + i ) ) 
            , op_func , user_param  ) ;
        
        if ( res )
        {
           return SUCCESS; /* fix by natty */
            /*return FAIL;*/
        }
    }
    
	return FAIL; /* fix by natty */
   /* return SUCCESS;*/

}
