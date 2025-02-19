/***************************************
* Author : Natty
* Reviewer : 
* Date : 15 / 02 / 2025
* Last update: 15 / 02 / 2025
*****************************************/

#include <stdio.h> /* printf, fputs, puts, sprinf, fgets, feof, rewind */
#include <assert.h>
#include <string.h> 	/* strcpy, strcmp */
#include <ctype.h> 		/* tolower  */
#include "hash_table.h" 
#include <stdlib.h> /* free, malloc */

#define BLACK        "\x1b[30m"
#define RED          "\x1b[31m"
#define GREEN        "\x1b[32m"
#define YELLOW       "\x1b[33m"
#define BLUE         "\x1b[34m"
#define MAGENTA      "\x1b[35m"
#define CYAN         "\x1b[36m"
#define WHITE        "\x1b[37m"

#define RESET        "\x1b[0m"

/* BACKGROUND COLOR */
#define BACK_BLACK   "\x1b[40m"
#define BACK_RED     "\x1b[41m"
#define BACK_GREEN   "\x1b[42m"
#define BACK_YELLOW  "\x1b[43m"
#define BACK_BLUE  	 "\x1b[44m"
#define BACK_MAGENTA "\x1b[45m"
#define BACK_CYAN 	 "\x1b[46m"
#define BACK_WHITE   "\x1b[47m"


#define DEBUG		"DEBUG MODE"
#define RELEASE		"RELEASE MODE"

#define MIN(a, b)		((a > b ) ? b : a )
#define MAX(a, b)		((a > b ) ? a : b )
#define DICTIONARY_SIZE      105000
#define MAX_WORD_SIZE     		 40
#define WORD_NUM     		 26

/***************struct and enum declaration *******/
/*
struct person
{
  size_t key;
  int data;
}person_t;
*/

typedef enum
{
	SUCCESS = 0,
	OPERATION_FAIL = 1
	
}hash_result_t;

typedef enum
{
	
	FALSE = 0,
	TRUE = 1
	
}func_result_t;



/*
	#ifdef PRINTS
		Aux_Pre_Print_Tree(avl1, 0);
	#endif
*/
/***************End of struct and enum declaration *******/

/***************************function declaration**************************/
static void TestHash(void);
static void TestHashDictionary(void);
/*static char* RemoveNewLineAddNull( char* str );*/
size_t HashFunction(const void* key);
/*
static int SortingFunc(const void* check_data ,const void* new_data);
*/
/***************************End of function declaration******************/

/******************static functions definition**********************/
		
/*******************SortingFunc*********************/
/*
static int SortingFunc(const void* check_data ,const void* new_data)
{
	return (*(int*)check_data - *(int*)new_data);
}
*/
/*******************Compare*********************/

static int Compare(void* check_data , void* new_data)
{
	if( NULL != check_data && NULL != new_data)
	{
		return (SUCCESS == (*(int*)check_data - *(int*)new_data));
	}	

	return -1;
}

/*******************Compare2*********************/
/*
static int Compare2(void* check_data , void* new_data)
{
	return  ( *(int*)check_data >= *(int*)new_data );
}
*/
/*******************hashFunction*********************/
size_t HashFunction(const void* key)
{
  return (*(int*)key) / 10;
}

/*******************match_function*********************/
static int match_func(void *check_data, void *user_param )
{
	return !strcmp((char*)check_data, (char*)user_param);
}

/*******************HashFunction2*********************/
size_t HashFunction2(const void* key)
{
  return (	tolower( *(char*)key ) - 'a' );
}

/* Must not to copy back the new line characther '\n', 
   and should replace it with a null termination characther '\0' */
   /*
static char* RemoveNewLineAddNull( char* str )
{
	size_t i = 0;
	while( *(str + i) != '\n' ) 
	{
		*(str + i) = tolower( *(str + i) );
		++i;
	}
	*(str + i) = '\0';
	return str;
}
	*/
/******************End of static functions definition**********************/


int main ()
{
	char* mode = RELEASE;
	char* background =  BACK_MAGENTA;	
	
	#ifndef NDEBUG
		mode = DEBUG;
		background =  BACK_YELLOW;
	#endif

	puts(BLUE"====================================================="RESET);
	printf("%sTEST: %s "RESET" \n", background,  mode);
  	puts(BACK_BLUE"'TestHash()'"RESET); 
    TestHash();
 
	puts(BLUE"====================================================="RESET);

	puts(BLUE"====================================================="RESET);
	printf("%sTEST: %s "RESET" \n", background,  mode);
   	puts(BACK_BLUE"'TestHashDictionary()'"RESET);
	TestHashDictionary();
	puts(BLUE"====================================================="RESET);

	return 0;
}
/********************  TestHashDictionary  ****************************/

static void TestHashDictionary(void)
{	
	int flag = FALSE, res = -1;
	hash_table_t *dictionary = NULL;
	FILE* file = NULL;
	size_t i = 0;
	char* word_arr[11] = { "a", "AC", "ASCII", "mod", "coerce", 
							"got", "half", "impact", "react", "toward", "zygotess"};
	char *tmp_word[DICTIONARY_SIZE ] = { NULL };

	dictionary = HashTableCreate(HashFunction2, match_func, WORD_NUM);

    
	if ( !dictionary )
	{
		puts("Failes in_1: HashTableCreate - Allocation");
	}

	file = fopen("/usr/share/dict/words", "r");

    if(  NULL == file)
    {
       printf("Failed to open the file\n");
	   flag =  TRUE ;
    }
    
	i = 0;

	for( i = 0; i < DICTIONARY_SIZE; ++i)
	{
		tmp_word[i] = (char*)calloc(1,  MAX_WORD_SIZE );

		if( NULL == tmp_word[i] )
		{
			puts("Failes in_2: Dictionary - Allocation");
			printf("line: %d, Iteration = %lu \n" , __LINE__, i );

			while ( i > 0 )
			{
				free( tmp_word[i - 1] );
				tmp_word[i - 1] = NULL;
				--i;
			}

			break;
		}
	}

	i = 0;

	for( i = 0; i < DICTIONARY_SIZE; ++i)
	{
		fgets(tmp_word[i], MAX_WORD_SIZE, file); 

		if(tmp_word[i])
        {
			tmp_word[i][strcspn(tmp_word[i] , "\n")] = '\0';

			if (HashTableInsert( dictionary, tmp_word[i]) )
			{
				puts("Failes in_4: Dictionary - HashTableInsert");
				printf("line: %d, Iteration = %lu \n" , __LINE__, i );
				fclose(file);

			}
		}	

	}
		
	for( i = 0; i < 10 ; ++i )
	{
		res = HashTableForEach(dictionary ,match_func,
			HashTableFind( dictionary, (char*)word_arr[i] ) );
		   /*puts((char*)HashTableFind( dictionary, word_arr[i] ) );*/

		if( SUCCESS != res) 
		{
			
			printf("line: %d, Iteration = %lu \n" , __LINE__, i );
			puts("Failes in_insert : HashTableFind_dictionary");
		} 
		
	}

	res = HashTableForEach(dictionary ,match_func, (char*)word_arr[10] );
		
	if( OPERATION_FAIL != res) 
	{
			
		printf("line: %d \n" , __LINE__ );
		puts("Failes in : HashTableForEach");
	}
	
	if (feof(file)) 
    {
        puts("End of file is reached successfully");
    }
    
    if( 0 != fclose(file)  )
    {
       printf("Failed to close the file\n");
	   flag =  TRUE ;
    }
    

	for( i = 0; i < DICTIONARY_SIZE; ++i)
	{
		free( tmp_word[i] );
		tmp_word[i] = NULL;
	}

	HashTableDestroy(dictionary);

	dictionary = NULL;

	if( !flag )
	{
		puts(RESET);		
		puts(BACK_BLUE"Test_dictionary: Success"RESET);

	}
	
	else
	{
		puts(BACK_YELLOW"Test_dictionary: Failure"RESET);	
	}
}	

/********************  TestHash  ****************************/
static void TestHash(void)
{	
	int flag = FALSE, res = -1;
	/*struct set *array;*/
	hash_table_t *table1 = NULL;

	size_t i = 0;
	size_t capacity = 10;
	int ages[10] = {1, 10, 20, 30, 40 ,50 , 60, 70, 80, 90};
	int ages2[10] = {100, 110, 120, 130, 140 ,150 , 160, 170, 180, 190};

	capacity = sizeof(ages)/sizeof(ages[0]);
	/*puts(RED);*/
	table1 = HashTableCreate(HashFunction, Compare, capacity);
	if ( !table1 )
	{
		puts("Failes in_1: HashTableCreate - Allocation");
	}

	if( !HashTableIsEmpty(table1) ) 
	{
		puts("Failes in_1: IsEmpty");
		flag =  TRUE;
	}

	if( 0 != HashTableSize(table1) )
	{
		
		puts("Failes in_1: Size");
		flag =  TRUE;
	
	}

	for(i = 0; i < 10; ++i)
	{
		flag = HashTableInsert(table1, ages + i);
		
		if( flag )
		{
			printf("Iteration = %lu \n", i); 
			puts("Failes in_1: Insert Allocation failed ");
			flag =  TRUE;
		}
		
		if( (i + 1) != HashTableSize(table1) )
		{
		
			puts("Failes in_2: Size");
			flag =  TRUE;
	
		}
	}

	for(i = 0; i < 10; ++i)
	{
		HashTableRemove(table1, ages + i);
		
		if( flag )
		{
			printf("Iteration = %lu \n", i); 
			puts("Failes in_1: Remove failed ");
			flag =  TRUE;
		}
		
		if( (10 - i - 1) != HashTableSize(table1) )
		{
		
			puts("Failes in_3: Size");
			flag =  TRUE;
	
		}
	}

	/*res = HashTableInsert(table1, ages);*/
	/*printf("res = %d \n ", res);*/

	if(  ! HashTableIsEmpty(table1) ) 
	{
		puts("Failes in_3: IsEmpty");
		flag =  TRUE;
	}



	for(i = 0; i < 10; ++i)
	{
		flag = HashTableInsert(table1, ages + i);
		
		if( flag )
		{
			printf("Iteration = %lu \n", i); 
			puts("Failes in_2: Insert Allocation failed ");
			flag =  TRUE;
		}
		
		if( (i + 1) != HashTableSize(table1) )
		{
		
			puts("Failes in_4: Size");
			flag =  TRUE;
	
		}
	}

	for( i = 0; i < 10 ; ++i )
	{
		
		res = HashTableForEach(table1 ,Compare, ages + i);
		
		if( SUCCESS != res) 
		{
			
			printf("line: %d, Iteration = %lu \n" , __LINE__, i );
			puts("Failes in : HashTableForEach");
		} 
		
	}
	

	for( i = 0; i < 10 ; ++i )
	{
		res = HashTableForEach(table1 ,Compare, HashTableFind( table1, ages + i));
		
		if( SUCCESS != res) 
		{
			
			printf("line: %d, Iteration = %lu \n" , __LINE__, i );
			puts("Failes in : HashTableFind");
		} 
		
	}

	res = HashTableForEach(table1 ,Compare, ages2 );
		
	if( OPERATION_FAIL != res) 
	{
			
		printf("line: %d \n" , __LINE__ );
		puts("Failes in : HashTableForEach");
	}
	
	res = HashTableForEach(table1 ,Compare, HashTableFind( table1, ages2 ) );
		
	if( OPERATION_FAIL != res) 
	{
			
		printf("line: %d \n" , __LINE__ );
		puts("Failes in : HashTableFind");
	} 

	

	HashTableDestroy(table1);

	table1 = NULL;

	if( !flag )
	{
		puts(RESET);		
		puts(BACK_BLUE"Test: Success"RESET);

	}
	
	else
	{
		puts(BACK_YELLOW"Test: Failure"RESET);	
	}
}	
	