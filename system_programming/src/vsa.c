/***************************************
* Author : Natty
* Reviewer : David 
* Date : 15 / 01 / 2025
* Last update: 19 / 01 / 2025
*****************************************/

#include <assert.h> 	/* assert */
#include <stdlib.h> 	/* malloc, free */

#include "vsa.h"

#define 	VSA_SIZE 			AlignSizeBlock(sizeof(vsa_t))
#define 	VSA_DSIZE 			(2 * VSA_SIZE)
#define		WORD_SIZE 			sizeof(size_t)
struct vsa
{
	long entry_offset;
};

typedef enum
{
	ALLOC_BLOCK = -1,
	END_MEMORY = 0,
	FREE_BLOCK = 1
	
}block_state_t;

/***************End of struct and enum declaration *******/

/***************************function declaration***************************/
static size_t AlignSizeBlock(size_t size_of_block );
static long GetOffsetValue(char*  header_entry);
static long GetOffsetValue(char*  header_entry);
static void SetOffsetValue(char*  header_entry,long value );
static long GetAbsValue(char*  header_entry);
static int CheckHeaderState(char*  header_entry);
static char* NextEntryHeaderAddr(char*  header_entry,long value);
static char* NextFirstFreeEntryHeaderAddr(char*  header_entry);
static int CanAllocCurrBlock(size_t  block_size, size_t mem_size );
static size_t GetDiffAllocCurrBlock(size_t  block_size, size_t mem_size );
static size_t GetNextBlockSizeToAlloc(size_t  block_size, size_t mem_size );
static size_t TotalFreeSpaceWithHeaders(size_t curr_size, size_t num_of_blocks);
static void* StartOfBlockAddr(char*  header_entry);
static void* StartOfHeaderBlockAddr(char*  header_entry);
/***************************End of function declaration******************/

/******************static functions definition**********************/


/***************************AlignSizeBlock************************/
static size_t AlignSizeBlock(size_t size_of_block )
{
	
	if(size_of_block % WORD_SIZE)
	{
		size_of_block += (WORD_SIZE - size_of_block % WORD_SIZE);
	}
	
	return size_of_block;
}
/***************************GetOffsetValue************************/

static long GetOffsetValue(char*  header_entry)
{
	assert(header_entry);
	return 	((vsa_t*)header_entry)->entry_offset;
}

/***************************SetOffsetValue************************/
static void SetOffsetValue(char*  header_entry,long value )
{
	assert(header_entry);	
	((vsa_t*)header_entry)->entry_offset = value;

}
/***************************GetAbsValue************************/
static long GetAbsValue(char*  header_entry)
{
	assert(header_entry);
	return GetOffsetValue(header_entry) > 0 ? GetOffsetValue(header_entry) :
											-GetOffsetValue(header_entry);
}

/***************************CheckHeaderState************************/
static int CheckHeaderState(char*  header_entry)
{
	assert(header_entry);
	return  END_MEMORY == GetOffsetValue(header_entry) ? END_MEMORY :
							2 * (GetOffsetValue(header_entry) > 0) - 1 ;		

}

/***************************NextEntryHeaderAddr************************/
static char* NextEntryHeaderAddr(char*  header_entry,long value)
{
	assert(header_entry);
	
	return header_entry +  VSA_SIZE + value ; 

}

/********************NextFirstFreeEntryHeaderAddr**********************/
static char* NextFirstFreeEntryHeaderAddr(char*  header_entry)
{

	assert(header_entry);
	
	while( END_MEMORY != CheckHeaderState(header_entry)  )
	{	
		if (ALLOC_BLOCK == CheckHeaderState(header_entry) )
		{
			header_entry = NextEntryHeaderAddr(header_entry,
											 GetAbsValue(header_entry));
											 
			continue;									  
		}
		
		else if(FREE_BLOCK == CheckHeaderState(header_entry) )
		{
			return header_entry ;
		}

	}
	  /* return NULL if Memory is full */
	return NULL; 

}

/********************StartOfBlockAddr**********************/

static void* StartOfBlockAddr(char*  header_entry)
{
	assert(header_entry);

	return CheckHeaderState(header_entry) ? (void*)(header_entry + VSA_SIZE)
											 : NULL; 
}

/********************StartOfHeaderBlockAddr**********************/

static void* StartOfHeaderBlockAddr(char*  header_entry)
{
	assert(header_entry);

	return CheckHeaderState(header_entry- VSA_SIZE) ?
	 						(void*)(header_entry - VSA_SIZE) : NULL; 
}

/********************CanAllocCurrBlock**********************/
static int CanAllocCurrBlock(size_t  block_size, size_t mem_size )
{	
	return 	block_size >= mem_size ;	
}

/********************GetDiffAllocCurrBlock**********************/
static size_t GetDiffAllocCurrBlock(size_t  block_size, size_t mem_size )
{
	/* 0 is the minimal aligns block of the difference */
	return 	block_size - mem_size ;
}

/********************TotalFreeSpaceWithHeaders**********************/
static size_t TotalFreeSpaceWithHeaders(size_t curr_size, size_t num_of_blocks)
{
	return curr_size + (VSA_SIZE * (num_of_blocks - 1) );
}

static size_t GetNextBlockSizeToAlloc(size_t  block_size, size_t mem_size )
{
	size_t get_diff = 0;
	
	get_diff = (GetDiffAllocCurrBlock(block_size, mem_size) > VSA_SIZE );
	
	return get_diff * (GetDiffAllocCurrBlock(block_size, mem_size) - VSA_SIZE);
}


/********************  VSAInit  ****************************/
vsa_t *VSAInit(void *mem_area, size_t mem_size)
{

	size_t num_of_valid_blocks = 0;
		
	vsa_t* first_init_block = NULL;
	vsa_t* tail_block = NULL;
		
	assert(mem_area);
		
	/* Chack if there is enough space for one block */
	if( (VSA_SIZE * 3) > mem_size ) 
	{
		return NULL;
	}

	num_of_valid_blocks = (mem_size - 2 * VSA_SIZE) / VSA_SIZE;
		
	first_init_block = (vsa_t*)mem_area;
	
	first_init_block->entry_offset = +(num_of_valid_blocks * VSA_SIZE);
	
	tail_block = (vsa_t*)((char*)mem_area +
				 (VSA_SIZE * (num_of_valid_blocks + 1))); 
	
	/* fixed dummy end indicator */
	tail_block->entry_offset = 0;
	
	return (vsa_t*)mem_area;

}

/********************  VSAFree  ****************************/
void VSAFree(void *chunk_to_free)
{
	
	long entry_offset = 0;
	int entry_offset_state = 0;
	char* header_of_chunck = NULL;
	
	assert(chunk_to_free);
	
	if (NULL == chunk_to_free )
	{
		return;
	}
	
	header_of_chunck = StartOfHeaderBlockAddr((char*)chunk_to_free);
	
	entry_offset_state = CheckHeaderState(header_of_chunck);
							
	entry_offset = GetOffsetValue((char*)header_of_chunck);
	
	if( END_MEMORY == entry_offset_state || FREE_BLOCK == entry_offset_state )
	{
		return; 
	}
	
	else if ( ALLOC_BLOCK == entry_offset_state )
	{
		SetOffsetValue( (char*)header_of_chunck, -entry_offset);	
		
	}
	
	return;
	
}
/********************  VSAAlloc  ****************************/

void *VSAAlloc(vsa_t *vsa, size_t chunk_size_in_bytes)
{
	
	size_t align_chuck_size = 0;
	
	size_t local_max_size = 0, local_max_free_block = 0;
	size_t curr_block_size = 0;
	size_t next_block_size_to_alloc = 0;
	size_t local_total_free_space = 0;
	
	char* local_max_first_free_entry = NULL;
	char* curr_entry_header = NULL;
		
	assert(vsa);
		
	align_chuck_size = AlignSizeBlock(chunk_size_in_bytes);

	local_max_first_free_entry = NextFirstFreeEntryHeaderAddr((char*)vsa);
	
	if( NULL == local_max_first_free_entry || 0 == chunk_size_in_bytes )
	{
		return NULL;  /* if memory is full or input is 0 */
	}	
	
	curr_entry_header = local_max_first_free_entry;

	while( NULL != local_max_first_free_entry ) /* END_MEMORY CHECKING*/
	{
	
		if ( FREE_BLOCK == CheckHeaderState(curr_entry_header) )
		{

			curr_block_size = GetOffsetValue(curr_entry_header);
				
			if( CanAllocCurrBlock( curr_block_size, align_chuck_size ))
			{
				next_block_size_to_alloc = 
					GetNextBlockSizeToAlloc(curr_block_size, align_chuck_size);
				
				if( next_block_size_to_alloc > 0 )
				{
					/* cteate new header */
					SetOffsetValue(NextEntryHeaderAddr(curr_entry_header,
							align_chuck_size) ,(long)next_block_size_to_alloc);	
					
					/* now the block is occupied */
					SetOffsetValue(curr_entry_header,
									 -(long)align_chuck_size );
									 				
								 
				}
				
				/* allocate more then require-> can't create new free header*/
				else 
				{
					SetOffsetValue(curr_entry_header,
									 -(long)curr_block_size );
					
				}
					
				return StartOfBlockAddr(curr_entry_header);
			
			}
			
			/* add the current free block to the consecutive previous blocks*/ 
			else 
			{
				
				local_max_size += curr_block_size;
				local_max_free_block += 1;
			
				local_total_free_space = TotalFreeSpaceWithHeaders(local_max_size,
														 local_max_free_block);
				 /* First Fit -> unified on demend*/											 
				if(CanAllocCurrBlock(local_total_free_space, align_chuck_size ))
				{
				
					next_block_size_to_alloc = 
						GetNextBlockSizeToAlloc(local_total_free_space,
										 align_chuck_size);
										 
					if( next_block_size_to_alloc > 0 )
					{
						/* cteate new header */
						SetOffsetValue(NextEntryHeaderAddr(local_max_first_free_entry,
								align_chuck_size) ,(long)next_block_size_to_alloc);	
					
						/* now the block is occupied */
						SetOffsetValue(local_max_first_free_entry,
									 -(long)align_chuck_size );
									 												 
					}
					
				/* allocate more then require-> can't create new free header*/
					else 
					{
						SetOffsetValue(local_max_first_free_entry,
									 -(long)local_total_free_space );									 
					}
					
					return StartOfBlockAddr(local_max_first_free_entry);																
				}
			
				curr_entry_header = NextEntryHeaderAddr(curr_entry_header,
							GetOffsetValue(curr_entry_header));	
			}
			
		}
		
		else /* ALLOC_BLOCK or END_MEMORY */
		{
			if( ALLOC_BLOCK == CheckHeaderState(curr_entry_header)  )				
			{		
				local_max_first_free_entry =
						NextFirstFreeEntryHeaderAddr(curr_entry_header);
							 
				curr_entry_header = local_max_first_free_entry;
			
				/* resets for the next chunck checking */
				curr_block_size = 0;
				local_max_free_block = 0;	
				local_max_size = 0;
				local_total_free_space = 0;
				next_block_size_to_alloc = 0;

			}
			
			else if( END_MEMORY == CheckHeaderState(curr_entry_header) )
			{
				break;
			}						
		}
		
	}
	
	return NULL; /* There is no sufficent memory space for allocation */
}

			
/*************  VSALargestChunkAvailable  ************************/

size_t VSALargestChunkAvailable(vsa_t *vsa)
{
	size_t global_max_size = 0;
	size_t local_max_size = 0 , local_max_free_block = 0;
	size_t local_total_free_space = 0;
	
	char* curr_entry_header = NULL;
	char* local_max_first_free_entry = NULL;
	
	assert(vsa);
	
	local_max_first_free_entry = NextFirstFreeEntryHeaderAddr((char*)vsa);
	curr_entry_header = local_max_first_free_entry;
	
	global_max_size = 0;
		
	while( NULL != local_max_first_free_entry ) /* END_MEMORY CHECKING*/
	{
		
		if ( FREE_BLOCK == CheckHeaderState(curr_entry_header) )
		{
	
		local_max_size += GetOffsetValue(curr_entry_header);
		local_max_free_block += 1;
			
		curr_entry_header = NextEntryHeaderAddr(curr_entry_header,
							GetOffsetValue(curr_entry_header));																
		}
							
		else if( ALLOC_BLOCK == CheckHeaderState(curr_entry_header)
				|| END_MEMORY == CheckHeaderState(curr_entry_header)  )	
		{	
			
			local_total_free_space = TotalFreeSpaceWithHeaders(local_max_size,
														 local_max_free_block);
														 
		/* unified the largests consecutive free blocks */			
			SetOffsetValue(local_max_first_free_entry,
								 (long)local_total_free_space);			
					
			/* local_max_free_block >0 if there is at list 1 block free */
			if( local_max_free_block &&
					 (local_total_free_space >= global_max_size) )
			{				
				global_max_size = local_total_free_space;
			}
			
			if ( END_MEMORY == CheckHeaderState(curr_entry_header) )
			{
				break;
			}

			SetOffsetValue(local_max_first_free_entry,
								 (long)local_total_free_space);
						
			local_max_first_free_entry =
							 NextFirstFreeEntryHeaderAddr(curr_entry_header);
							 
			curr_entry_header = local_max_first_free_entry;
			
			local_max_free_block = 0;	
			local_max_size = 0;
		}
		
	}
	
	return 	global_max_size ;	
}





