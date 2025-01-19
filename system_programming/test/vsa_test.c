/***************************************
* Author : Natty
* Reviewer : David 
* Date : 19 / 01 / 2025
* Last update: 19 / 01 / 2025
*****************************************/

#include <stdio.h> 		/* printf, puts,  */
#include <assert.h>
#include <stdlib.h>
#include "vsa.h" 

#define WORD_SIZE 				sizeof(size_t)

#define RED          "\x1b[31m"
#define GREEN        "\x1b[32m"
#define BLUE         "\x1b[34m"
#define RESET        "\x1b[0m"

#define YELLOW  "\x1b[43m"
#define MAGENTA "\x1b[45m"


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

/***************************function declaration**************************/
static void Test100BlockSize(void);
static size_t CalcNumOfDiffBytes(char* addr1, char* addr2);

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
   	puts(GREEN"'Test100BlockSize()'");
    Test100BlockSize();
    
	puts(BLUE"====================================================="RESET);

     
	return 0;
}



/********************  Test2Block  ****************************/
static void Test100BlockSize(void)
{
	
	size_t size_of_mem_area = 100;
	size_t curr_size = 0;
	
	int flag = 0;
	
	vsa_t* vsa1 = NULL;
	vsa_t* vsa2 = NULL;
		
	char* ptr = NULL;
	void* mem_area = NULL;
	void* mem_area1 = (void*)&ptr;	
	
	char* curr_alloc_block1 = NULL;
	char* curr_alloc_block2 = NULL;
	char* curr_alloc_block3 = NULL;
	
	puts(RED);

	mem_area = malloc(size_of_mem_area);
	
	if(! mem_area)
	{
		puts("Failes in malloc");
		flag = 1;
		return;
		
	}
	
	vsa2 = VSAInit(mem_area1 ,24 - 1); 

	if( NULL != vsa2)
	{
		puts("Failes in vsaInit_1: Lower of minimum suggest");
		flag = 1;
	}

	vsa1 = VSAInit(mem_area ,size_of_mem_area);

	if( NULL == vsa1)
	{
		puts("Failes in_2: vsaInit:");
		flag = 1;		
	}
	
	curr_size = VSALargestChunkAvailable(vsa1);
	
	/*printf(" curr_size = %lu\n", curr_size);*/
	
	if( 80 != curr_size  )
	{
		puts("Failes in_1: VSALargestChunkAvailable");
		flag = 1;	
	}
	
	curr_alloc_block1 = (char*)VSAAlloc(vsa1, 32);

	/*diff_addrs = CalcNumOfDiffBytes(mem_area, curr_alloc_block1);*/
	/*printf("diff_addrs = %d\n", diff_addrs);*/
	
	if( 0x8 != CalcNumOfDiffBytes(mem_area, curr_alloc_block1) )
	{
		puts("Failes in_1: VSAAlloc");
		flag = 1;	
	}
	
	curr_size = VSALargestChunkAvailable(vsa1);
		
	if( 40 != curr_size  )
	{
		puts("Failes in_2: LargestChunkAvailable || VSAAlloc");
		flag = 1;	
	}
	
	curr_alloc_block2 = (char*)VSAAlloc(vsa1, 8);
	
	if( 0x30 != CalcNumOfDiffBytes(mem_area, curr_alloc_block2) )
	{
		puts("Failes in_3: VSAAlloc");
		flag = 1;	
	}
	
	curr_size = VSALargestChunkAvailable(vsa1);
		
	if( 24 != curr_size  )
	{
		puts("Failes in_3: LargestChunkAvailable || VSAAlloc");
		flag = 1;	
	}
	
	
	curr_alloc_block3 = (char*)VSAAlloc(vsa1, 32);
	
	if ( NULL != curr_alloc_block3 )
	{
		puts("Failes in_4: VSAAlloc");	
		flag = 1;	
	}
	
	curr_alloc_block3 = (char*)VSAAlloc(vsa1, 18); /* allocate 24 */
	
	if( 0x40 != CalcNumOfDiffBytes(mem_area, curr_alloc_block3) )
	{
		puts("Failes in_5: VSAAlloc");
		flag = 1;	
	}
	
	curr_size = VSALargestChunkAvailable(vsa1);
		
	if( 0 != curr_size  )
	{
		puts("Failes in_4: LargestChunkAvailable || VSAAlloc");
		flag = 1;	
	}
	
	VSAFree(curr_alloc_block2);
	
	curr_size = VSALargestChunkAvailable(vsa1);

	/*printf(" curr_size = %lu\n", curr_size);*/
		
	if( 8 != curr_size  )
	{
		puts("Failes in_5: LargestChunkAvailable || VSAFree");
		flag = 1;
	}
	
	VSAFree(curr_alloc_block3);
	
	/* should do unified and to alloc 40 bytes*/
	
	curr_alloc_block3 = (char*)VSAAlloc(vsa1, 31); 
	
	if( 0x30 != CalcNumOfDiffBytes(mem_area, curr_alloc_block3) )
	{
		puts("Failes in_6: VSAAlloc");
		flag = 1;
	}
	
	curr_size = VSALargestChunkAvailable(vsa1);
		
	if( 0 != curr_size  )
	{
		puts("Failes in_6: LargestChunkAvailable || VSAAlloc");
		flag = 1;	
	}
	
	VSAFree(curr_alloc_block1);
	
	curr_size = VSALargestChunkAvailable(vsa1);

	/*printf(" curr_size = %lu\n", curr_size);*/
		
	if( 32 != curr_size  )
	{
		puts("Failes in_7: LargestChunkAvailable || VSAFree");
		flag = 1;	
	}
	
	curr_alloc_block1 = (char*)VSAAlloc(vsa1, 15);  /* should alloc 16*/
	
	if( 0x08 != CalcNumOfDiffBytes(mem_area, curr_alloc_block1) )
	{
		puts("Failes in_7: VSAAlloc");
		flag = 1;	
	}
	
	curr_size = VSALargestChunkAvailable(vsa1);
	
	/*printf(" curr_size = %lu\n", curr_size);	*/
		
	if( 8 != curr_size  )
	{
		puts("Failes in_8: LargestChunkAvailable || VSAAlloc");
		flag = 1;	
	}
	
	curr_alloc_block2 = (char*)VSAAlloc(vsa1, 1); 
	
	if( 0x20 != CalcNumOfDiffBytes(mem_area, curr_alloc_block2) )
	{
		puts("Failes in_8: VSAAlloc");
		flag = 1;
	}
	
	curr_size = VSALargestChunkAvailable(vsa1);
	
	/*printf(" curr_size = %lu\n", curr_size);	*/
		
	if( 0 != curr_size  )
	{
		puts("Failes in_9: LargestChunkAvailable || VSAAlloc");
		flag = 1;
	}
	
	if( !flag )
	{		
		puts(GREEN"Test: Success"RESET);
	}
	
	else
	{
		puts(YELLOW"Test: Failure"RESET);	
	}
	free(mem_area);
	
	mem_area = NULL;
		
}



