/*******************************************************************************
*
*	Auther:		Rawan Nabwany
*	Reviewer:	
*	Date:		09/04/25
*	worksheet:  C:: shuffle sort
*
******************************************************************************/
#define _GNU_SOURCE  
#include <stdio.h>      /* open     */
#include <stdlib.h>     /* rand calloc free qsort*/
#include <string.h>     /* strcmp   */
#include <sys/mman.h>   /* mmap     */
#include <sys/stat.h>   /* fstat    */
#include <fcntl.h>      /* O_RDONLY */
#include <pthread.h>    /* pthread_create */
#include <time.h>

#include "utils.h"

typedef void *(*routine_func_ptr_ty)(void*);

enum 
{
    CACHE_LINE_SIZE = 64,
    NUM_OF_THREADS = 8,
    NUM_OF_DUPS = 10, 
    NUM_OF_WORDS = 104334,
    RANGE = NUM_OF_WORDS * NUM_OF_DUPS /  NUM_OF_THREADS ,
    REMAINDER =  NUM_OF_WORDS * NUM_OF_DUPS %  NUM_OF_THREADS
};

typedef struct th_arg_ty
{
    unsigned char *from;
    unsigned char *to;
}th_arg_ty;



/* declarations */
static void *ThRoutine_TH( unsigned char **arg_ );
static void *LastThRoutine_TH( unsigned char **words );
static int RandomCmpFunc(const void *, const void *);
static int StrCmpFunc(const void *, const void *);
static void MergeFunc( unsigned char **words ,size_t words_from , size_t words_to , 
    unsigned char **merged_words , size_t merged_words_from 
    , size_t merged_words_to );
static void Tokenizer(unsigned char *buffer, unsigned char **tokens, size_t tokens_siz);





int main( )
{
    int fd;
    struct stat st ;
    size_t size;
    size_t i ;
    pthread_t threads[ NUM_OF_THREADS ];
    unsigned char *map_addr =  NULL ;
    unsigned char **words = NULL;
    unsigned char **merged_words = NULL;
    pthread_t *thread_ptr = NULL;
    size_t num_of_joined_threads = 0 ;
    int joined[NUM_OF_THREADS] = {0};
    clock_t start = 0 , end = 0 ;
    double time_taken = 0 ;


    /* open file and get the file discreptor */
    fd = open(  "/usr/share/dict/words" , O_RDONLY );
    RETURN_IF_BAD( ( -1 != fd ) , -1 , " Error opening file " ); 

    /* get the size of the file using fstat */
    RETURN_IF_BAD( (0 == fstat( fd , &st ) ) , -1 , "fstat failed");
    size = st.st_size;

    /* map the file */
    map_addr =  ( unsigned char * )mmap( NULL , size , PROT_READ | PROT_WRITE 
                                        , MAP_PRIVATE , fd , 0  );
    
    RETURN_IF_BAD( ( MAP_FAILED != map_addr ) , -1 , " mmap failed" );



    /* allocate memory for the words array - amount of words * 10  */
    words = ( unsigned char ** )calloc( 10 * NUM_OF_WORDS , sizeof( unsigned char *) );
    RETURN_IF_BAD( ( NULL != words ) , -1 , " Allocation failed ");


    /* allocate memory for merged words array - amount of words * 10  */
    merged_words = ( unsigned char ** )calloc( 10 * NUM_OF_WORDS , sizeof( unsigned char *) );
    RETURN_IF_BAD( ( NULL != merged_words ) , -1 , " Allocation failed ");

    /* tokenize the buffer  & zero the new line (\n) characters ( strtok )- 
    pointers to the start of each word in the words array */
    Tokenizer( map_addr, words, NUM_OF_WORDS );

    /* duplictae every pointer in words array ( ten times overall)*/
    for( i = 1 ; i < NUM_OF_DUPS ; ++i )
    {
        memcpy( words + NUM_OF_WORDS * i , words 
            , NUM_OF_WORDS * sizeof( unsigned char *) );
    }


    /* shuffle : qsort the duplicated words array with a random compare function */
    qsort( words , 10 * NUM_OF_WORDS , sizeof( unsigned char *) , RandomCmpFunc );

    thread_ptr = threads;
    /* create N threads */
    for( i = 0 ; i < NUM_OF_THREADS - 1 ; ++i , ++thread_ptr )
    {
        RETURN_IF_BAD( ( 0 == pthread_create(thread_ptr , NULL 
            , (routine_func_ptr_ty)ThRoutine_TH , words + RANGE * i) )
            , -1 , "pthread create failed" );
    }

    RETURN_IF_BAD( ( 0 == pthread_create(thread_ptr , NULL 
        , (routine_func_ptr_ty)LastThRoutine_TH , words + RANGE * i) )
        , -1 , "pthread create failed" );

    /* tryjoin threads */
    while( NUM_OF_THREADS != num_of_joined_threads )
    { 
        int res = 0;
        int end_range = 0;
        thread_ptr = threads;

        for( i = 0 ; i < NUM_OF_THREADS ; ++i  , ++thread_ptr )
        {
            if (!joined[i])
            {
                res = pthread_tryjoin_np( *thread_ptr  , NULL);

                if( 0 == res )
                {
                    size_t start =  i ? ( (i -1)  * RANGE ) : 0 ;

                    ++num_of_joined_threads;
                    joined[i] = 1;

                    if( i == NUM_OF_THREADS - 1 )
                    {
                        start = clock();
                        MergeFunc( words , (i - 1) * RANGE , i * RANGE + REMAINDER ,
                        merged_words , (num_of_joined_threads - 1 ) * RANGE  
                        , num_of_joined_threads * RANGE );
                        end = clock();
                        time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

                        end_range += REMAINDER ;
                    }
                    else
                    {
                        start = clock();
                        MergeFunc( words , start , i * RANGE + REMAINDER ,
                        merged_words , (num_of_joined_threads - 1 ) * RANGE  
                        , num_of_joined_threads * RANGE + end_range );
                        end = clock();
                        time_taken += ((double)(end - start)) / CLOCKS_PER_SEC;

                    }
                }
            }
        }

    }

    /* merge the arrays */
    printf("\nTime taken to merge: %f seconds\n", time_taken);

    /* free allocated memory */
    free( words );
    words = NULL;

    free( merged_words );
    merged_words = NULL;


    return 0;
}

static void *ThRoutine_TH( unsigned char **words )
{
    /* qsort the words of the relevant part in words array with strcmp func*/
    qsort( words , RANGE , sizeof( unsigned char *) , StrCmpFunc );

    return NULL;
}

static void *LastThRoutine_TH( unsigned char **words )
{
    /* qsort the words of the relevant part in words array with strcmp func*/
    qsort( words , RANGE + REMAINDER , sizeof( unsigned char *) , StrCmpFunc );

    return NULL;
}

static int RandomCmpFunc(const void *x, const void *y)
{
    ( void )x;
    ( void )y;
    return rand() % 3 - 1; 
}

static int StrCmpFunc(const void *x, const void *y)
{
    /*return strcmp()*/
    return strcmp( ( char *)x, (char *)y);
}

static void MergeFunc( unsigned char **words ,size_t words_from , size_t words_to , 
                         unsigned char **merged_words , size_t merged_words_from 
                         , size_t merged_words_to )
{
    /**/
    unsigned char **start_of_words = words + words_from ;
    unsigned char **end_of_words = words + words_to -1 ;
    unsigned char **start_of_merge = merged_words + merged_words_from ;
    unsigned char **end_of_merge = merged_words + merged_words_to -1 ;
    unsigned char **new_end = merged_words + merged_words_to + (words_to - words_from) - 1; ;

    while( end_of_words >= start_of_words && end_of_merge >= start_of_merge )
    {
        if( strcmp( (char *)end_of_words , (char *)end_of_merge ) > 0 )
        {
            *new_end = *end_of_words;
            --end_of_words;
        }
        else
        {
            *new_end = *end_of_merge;
            --end_of_merge;
        }
        --new_end;
    }

    while( end_of_words >= start_of_words )
    {
        *new_end = *end_of_words;
        --end_of_words;
        --new_end;
    }

    while( end_of_merge >= start_of_merge )
    {
        *new_end = *end_of_merge;
        --end_of_merge;
        --new_end;
    }

}


static void Tokenizer(unsigned char *buffer, unsigned char **tokens, size_t tokens_siz)
{
    size_t position = 0 ;
    unsigned char *token = NULL; 

    token = (unsigned char *)strtok( (char*)buffer, "\n" );


	ExitIfBad( NULL != token , "Strtok failed\n" );


    while (token != NULL) 
    {

        tokens[position] = token;
        position++;

        token = (unsigned char *)strtok(NULL, "\n" );

        ExitIfBad( position <= tokens_siz , "position drifted");

       
    }
}