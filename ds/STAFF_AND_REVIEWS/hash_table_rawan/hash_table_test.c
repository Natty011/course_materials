/*******************************************************************************
*
*	Auther:		rawan Nabwany
*	Reviewer:	
*	Date:		17/02/25
*	worksheet:  C:: Hash Table
*
*******************************************************************************/
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "dlist.h"
#include "hash_table.h"

#define CAPACITY 10
#define DICT_LINES_NUM 104350
#define MAX_CHARS_IN_STR 25
#define LETTERS 26

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
    cmp_func_t cmp_func;
};


/*****************************************************************************/
int TestCreate( void );
int TestInsert( void );
int TestRemove( void );
int TestFind( void );
int TestForEach( void );



/*****************************************************************************/

static int CompareFunc( void* check_data , void* user_param )
{
	return ( *(int*)check_data == *(int*)user_param ) ; 

}

static int CompareStr( void* check_data , void* user_param )
{
	return 0 == strcmp((char*)check_data , (char*)user_param); 

}

static size_t HashFunc( const void *data )
{
    return *(int*)data % CAPACITY;
}

static int AddTen( void* check_data , void* user_param  )
{
	*(int*)check_data += *(int*)user_param;
	
	return SUCCESS ;

}

static int PrintForEach( void *check_data , void *user_param )
{	
	(void)user_param;
	 printf("%d\t" , *(int*)check_data );
	 
	 return SUCCESS;
}

static size_t HashFuncWord( const void *str )
{
    int upper = 0 ;

    char c = *(char*)str ;

     upper = toupper( c ) ;

    return upper - 'A' ;
}

int main( int argc, char* argv[] )
{
    size_t i = 0 ;
    int res = SUCCESS;
    char *buffer[DICT_LINES_NUM] = { NULL };
    FILE *words_file = NULL;
    char *user_str = NULL ;
    hash_table_t *hash_table = NULL; 
    
    
    if ( 2 > argc )
    {
        return FAIL;
    }

    hash_table = HashTableCreate( HashFuncWord ,CompareStr , LETTERS );


    if( !hash_table)
    {
        return FAIL;
    }
    
    words_file = fopen("/usr/share/dict/words" , "r");

    if ( NULL == words_file ) 
    {
        HashTableDestroy( hash_table );
        perror("Error opening file");
        return 1;
    }



    for ( i = 0 ; i < DICT_LINES_NUM ; ++i  )
    {
        buffer[i] = (char*)calloc( 1 ,  sizeof( char ) * MAX_CHARS_IN_STR);

        if ( NULL == buffer[i] )
        {
            break;
        }
    }
    
    if( i < DICT_LINES_NUM  && NULL ==  buffer[i] )
    {
        while( i-- )
        {
            free(buffer[i]);
            buffer[i] = NULL;
        }
    }


    for ( i = 0 ; i < DICT_LINES_NUM ; ++i )
    {
        fgets( buffer[i] , MAX_CHARS_IN_STR , words_file );
        
        if(buffer[i])
        {
            buffer[i][strcspn(buffer[i] , "\n")] = '\0';

            if( HashTableInsert( hash_table , buffer[i] ) )
            {
                fclose( words_file );
                HashTableDestroy( hash_table );
                
                return FAIL;
            }
        }
       

    }

    user_str = argv[1];

    if (NULL ==  HashTableFind( hash_table , user_str ) )
    {
        return FAIL;
    }
    else
    {
       printf("\n\n");
        printf(" word was found\n ");
    }


    for ( i = 0 ; i < DICT_LINES_NUM ; ++i  )
    {
        free(buffer[i]);
        buffer[i] = NULL;
    }


    res += TestCreate();
    res += TestInsert();
    res += TestRemove();
    res += TestFind();
    res += TestForEach();

    
    if ( res )
	{
		printf("At Least One Function Failed\n");
	
	}
	
	else
	{
		printf("All Functions Succeeded\n");
	
	}

    

    fclose( words_file );
    HashTableDestroy( hash_table );

    return 0;
}


int TestCreate()
{
    hash_table_t *hash_table = HashTableCreate( HashFunc ,CompareFunc , CAPACITY );


    if( !hash_table)
    {
        return FAIL;
    }

    HashTableDestroy( hash_table );

    return SUCCESS;

}

int TestInsert()
{
    size_t i = 0;

    int data[] = { 12 , 15 , 9 , 30 , 21  };  
    size_t len = sizeof( data ) / sizeof( data[0] );
    hash_table_t *hash_table = HashTableCreate( HashFunc ,CompareFunc , CAPACITY );


    if( !hash_table)
    {
        return FAIL;
    }


    for ( i = 0 ; i < len ; ++i )
    {
        HashTableInsert( hash_table , &data[i] ); 
    }

    if( len != HashTableSize( hash_table ) )
    {
        return FAIL;
    }

    if( HashTableIsEmpty( hash_table ) )
    {
        return FAIL;
    }

    HashTableDestroy( hash_table );


    return SUCCESS;
}



int TestRemove()
{
    size_t i = 0;

    int data[] = { 1  , 4 , 9 , 13  , 55 , 35 , 26 , 100  };  
    size_t len = sizeof( data ) / sizeof( data[0] );
    hash_table_t *hash_table = HashTableCreate( HashFunc ,CompareFunc , CAPACITY );


    if( !hash_table)
    {
        return FAIL;
    }

    for ( i = 0 ; i < len ; ++i )
    {
        HashTableInsert( hash_table , &data[i] ); 
    }

    if( len != HashTableSize( hash_table ) )
    {
        return FAIL;
    }

    for ( i = 0 ; i < len ; ++i )
    {
        HashTableRemove( hash_table , &data[i] ); 
    }

    HashTableDestroy( hash_table );
    
    return SUCCESS;

}


int TestFind()
{
    size_t i = 0;

    int find1 = 5 , find2 = 8 , find3 = 1103 , find4 = 26 , find5 = 10;
    int res = 0 ;

    int data[] = { 5  , 3 , 8 , 13  , 45 , 25 , 26 , 1103  };  
    size_t len = sizeof( data ) / sizeof( data[0] );
    hash_table_t *hash_table = HashTableCreate( HashFunc ,CompareFunc , CAPACITY );


    if( !hash_table)
    {
        return FAIL;
    }

    for ( i = 0 ; i < len ; ++i )
    {
        HashTableInsert( hash_table , &data[i] ); 
    }

    res = *(int*)HashTableFind(hash_table , &find1);

    if(data[0] != res)
    {
        return FAIL;
    }

    res = *(int*)HashTableFind(hash_table , &find2);

    if(data[2] != res)
    {
        return FAIL;
    }

    res = *(int*)HashTableFind(hash_table , &find3);

    if(data[7] != res)
    {
        return FAIL;
    }

    res = *(int*)HashTableFind(hash_table , &find4);

    if(data[6] != res)
    {
        return FAIL;
    }

    if(NULL != HashTableFind(hash_table , &find5))
    {
        HashTableDestroy( hash_table );
        return FAIL;
    }

    HashTableDestroy( hash_table );

    return SUCCESS;

}




int TestForEach()
{
    size_t i = 0;
    int ten = 10 ; 

    int data[] = { 600   , 245 , 144 , 220  , 321 , 122 , 37 , 84  };  
    size_t len = sizeof( data ) / sizeof( data[0] );
    hash_table_t *hash_table = HashTableCreate( HashFunc ,CompareFunc , CAPACITY );


    if( !hash_table)
    {
        return FAIL;
    }

    for ( i = 0 ; i < len ; ++i )
    {
        HashTableInsert( hash_table , &data[i] ); 
    }

    HashTableForEach( hash_table , PrintForEach , NULL );

    HashTableForEach( hash_table , AddTen , &ten  );
    
    printf("\n\n\n\n\n\n");
    HashTableForEach( hash_table , PrintForEach , NULL );

    HashTableDestroy( hash_table );

    return SUCCESS;

}
