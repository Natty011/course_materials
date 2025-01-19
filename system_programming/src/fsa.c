/***************************************
* Author : Natty
* Reviewer : Chen 
* Date : 13 / 01 / 2025
* Last update: 15 / 01 / 2025
*****************************************/
 	
#include <assert.h> 	/* assert */
#include <stdlib.h> 	/* malloc, free */

#include "fsa.h"

#define 	HEADER_SIZE 		AlignSizeBlock(sizeof(block_header_t))
#define 	FSA_SIZE 			AlignSizeBlock(sizeof(fsa_t))
#define 	WORD_SIZE 			sizeof(size_t)

struct fsa
{
	char* mem_pool_first;
};

typedef struct block_header
{
	char* next_free;
	
}block_header_t;



/***************End of struct and enum declaration *******/

/***************************function declaration**************************/
static size_t AlignSizeBlock(size_t size_of_block );
/***************************End of function declaration******************/

/***************************AlignSizeBlock************************/
static size_t AlignSizeBlock(size_t size_of_block )
{
	
	if(size_of_block % WORD_SIZE)
	{
		size_of_block += (WORD_SIZE - size_of_block % WORD_SIZE);
	}
	
	return size_of_block;
}

/********************  FSASuggestSize  ****************************/
size_t FSASuggestSize(size_t num_of_blocks, size_t size_of_block)
{
	
	size_t align_size_of_block = 0;
	
	if ( !(size_of_block && num_of_blocks) )
	{
		return 0;
	}
	
	align_size_of_block =  AlignSizeBlock(size_of_block); 
							
	return ((align_size_of_block + HEADER_SIZE) * num_of_blocks) + HEADER_SIZE;
}
/********************  FSAInit  ****************************/

fsa_t* FSAInit(void* mem_area, size_t mem_size, size_t size_of_block)
{
	
	size_t i = 0;
	
	fsa_t* manager_pool_ptr = NULL;
	block_header_t* curr_header_ptr = NULL;
	
	size_t num_of_valid_blocks = 0;
		

	
	size_t mem_size_wo_meta_data = mem_size - FSA_SIZE; 
	size_t align_size_of_block = AlignSizeBlock(size_of_block);	
	size_t align_size_block_with_header = align_size_of_block + HEADER_SIZE;
		
	assert(mem_area);
	

	if ( ! size_of_block )
	{
		return NULL;
	}
	/* Chack if there is enough space for one block */
	if( align_size_block_with_header > mem_size_wo_meta_data ) 
	{
		return NULL;
	}

	manager_pool_ptr = (fsa_t*)mem_area;
			
	num_of_valid_blocks =(mem_size_wo_meta_data) / align_size_block_with_header;
		

	((fsa_t*)mem_area)->mem_pool_first = (char*)mem_area + FSA_SIZE + HEADER_SIZE ;
	
	curr_header_ptr = (block_header_t*)((char*)mem_area + HEADER_SIZE);


	for( i = 1 ; i < num_of_valid_blocks; ++i)
	{
	
		curr_header_ptr->next_free =  (char*)curr_header_ptr +
		align_size_block_with_header + HEADER_SIZE;
		
		curr_header_ptr = (block_header_t*)((char*)curr_header_ptr +
								 align_size_block_with_header);
		
	}
	
	curr_header_ptr->next_free = NULL;
	
	return 	manager_pool_ptr;
}

/********************  FSAFree  ****************************/
void FSAFree(fsa_t* fsa, void* block)
{

	
	char* curr_header_ptr = NULL; 

	assert(fsa);
	if(NULL == block )
	{
		return;
	}

	curr_header_ptr = (char*)block - HEADER_SIZE;
	 
	((block_header_t*)curr_header_ptr)->next_free = fsa->mem_pool_first; 

	fsa->mem_pool_first = (char*)block; 
	
}

/********************  FSAAlloc  ****************************/

void* FSAAlloc(fsa_t* fsa)
{
	
	char* addr_block_to_return = NULL;
		
	char* curr_header_ptr = NULL; 
		
	assert(fsa);
		
	if( !FSACountFree(fsa))
	{
		return NULL;
	}
	
	curr_header_ptr = fsa->mem_pool_first; 

	addr_block_to_return = 	curr_header_ptr;
	
	curr_header_ptr = curr_header_ptr - HEADER_SIZE;
	
	fsa->mem_pool_first = ((block_header_t*)curr_header_ptr)->next_free;
	
	return (void*)addr_block_to_return;

	
}

/********************  FSACountFree  ****************************/
size_t FSACountFree(const fsa_t* fsa)
{

	char* curr_header_ptr = NULL;
	
	size_t num_of_free_block = 0;

	assert(fsa);


	curr_header_ptr = fsa->mem_pool_first; 
		
	while(NULL != curr_header_ptr ) 
	{
		++num_of_free_block;
		
		curr_header_ptr = ((block_header_t*)(curr_header_ptr
											 - HEADER_SIZE ))->next_free;		
	}
	
	return num_of_free_block;
	
}





