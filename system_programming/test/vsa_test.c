/***************************************
* Author : Natty
* Reviewer : Michael
* Date : 26 / 12 / 2024
* Last update: 26 / 12 / 2024
*****************************************/

#include <stdio.h> 		/* printf, puts,  */
#include <string.h> 	/* strcpy, strcmp */
#include <assert.h>
#include <stdlib.h>
#include "fsa.h" 

#define WORD_SIZE 		8

#define RED          "\x1b[31m"
#define GREEN        "\x1b[32m"
#define BLUE         "\x1b[34m"
#define RESET        "\x1b[0m"

#define YELLOW  "\x1b[43m"
#define MAGENTA "\x1b[45m"

#define CANDIDATE    "CANDIDATE TO INSERT: "

#define DEBUG		"DEBUG MODE"
#define RELEASE		"RELEASE MODE"

typedef enum
{
	
	FALSE = 0,
	TRUE = 1
	
}func_result_t;

/********************  CalcNumOfDiffBytes  ****************************/
static size_t CalcNumOfDiffBytes(char* addr1, char* addr2)
{

	return (addr2 - addr1);	
}

/********************  CheckAlignAddr  ****************************/
static int CheckAlignAddr(char* addr)
{

	return (size_t)addr % WORD_SIZE;	
}

/***************************function declaration**************************/
static void Test2Block(void);
static size_t CalcNumOfDiffBytes(char* addr1, char* addr2);
static int CheckAlignAddr(char* addr);
/***************************End of function declaration******************/

int main ()
{

	char* mode = RELEASE;
	char* background = MAGENTA;	
	
	#ifndef NDEBUG
		mode = DEBUG;
		background = YELLOW;
	#endif

	puts(BLUE"====================================================="RESET);
	printf("%sTEST: %s "RESET" \n", background,  mode);
    puts(GREEN"'Test2Block()'");
    Test2Block();
    
	puts(BLUE"====================================================="RESET);

     
	return 0;
}



/********************  Test2Block  ****************************/
static void Test2Block(void)
{
	
	size_t num_of_blocks = 2;
	size_t size_of_block = 7;
	size_t curr_size = 0;
	size_t suggest = 0;

	
	fsa_t* fsa1 = NULL;
	fsa_t* fsa2 = NULL;	
	char* ptr = NULL;
	void* mem_area = NULL;
	void* mem_area1 = (void*)&ptr;	
	
	char* curr_alloc_block1 = NULL;
	char* curr_alloc_block2 = NULL;
	
	puts(RED);

	suggest = FSASuggestSize(num_of_blocks, size_of_block);

	mem_area = malloc(suggest);
	
	if(! mem_area)
	{
		puts("Failes in malloc");
		return;
		
	}

	
	fsa2 = FSAInit(mem_area1 ,24 - 1, 7); 

	if( NULL != fsa2)
	{
		puts("Failes in FSAInit_1: Lower of minimum suggest");
		
	}
	/*FSAInit(mem_area, suggest, size_of_block + 1 );*/	
	/*FSAInit(mem_area, 24, 6 + 1 ) */
	fsa1 = FSAInit(mem_area, suggest, size_of_block + 1 ); 


	if( NULL == fsa1)
	{
		puts("Failes in_2: FSAInit:");
		
	}
	
	if( FSACountFree(fsa1) != 2 )
	{
		puts("Failes in_1: CountFree");
	}	

	
	curr_alloc_block1 = (char*)FSAAlloc(fsa1);
	
	curr_size = FSACountFree(fsa1);
	

	if( FSACountFree(fsa1) != 1  
		|| 0x10 != CalcNumOfDiffBytes(mem_area,curr_alloc_block1 )
		|| CheckAlignAddr(curr_alloc_block1)  )
	{
		puts("Failes in_1 : CountFree && DiffBytes && Align");
	}
	
	curr_alloc_block2 = (char*)FSAAlloc(fsa1);
	curr_size = FSACountFree(fsa1);	
	


	if( curr_size != 0 
		|| 0x20 != CalcNumOfDiffBytes(mem_area,curr_alloc_block2 )
		|| CheckAlignAddr(curr_alloc_block2)  )
	{
		puts("Failes in_2 : CountFree && DiffBytes && Align");
	}
	
	FSAFree(fsa1, curr_alloc_block1);
	
	if( FSACountFree(fsa1) != 1  )
	{
		puts("Failes in_1 : FSAFree");
	}
	
	
	curr_alloc_block1 = (char*)FSAAlloc(fsa1);
	
	curr_size = FSACountFree(fsa1);
	

	if( FSACountFree(fsa1) != 0  
		|| 0x10 != CalcNumOfDiffBytes(mem_area,curr_alloc_block1 )
		|| CheckAlignAddr(curr_alloc_block1)  )
	{
		puts("Failes in_3 : CountFree && DiffBytes && Align");
	}
	
	
	FSAFree(fsa1, curr_alloc_block2);

	
	if( FSACountFree(fsa1) != 1  )
	{
		puts("Failes in_2 : FSAFree");
	}		
				
	puts(GREEN"TestString: Success"RESET);
	
	free(mem_area);
	
	mem_area = NULL;
		
}



