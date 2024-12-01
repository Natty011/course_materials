/***************************************
* Author : Natty
* Reviewer : Idan
* Date : 28 / 11 / 2024
* Last update: 30 / 11 / 2024
*****************************************/

#include <stdio.h> /* puts, __WORDSIZE */
#include <stdlib.h> /* size_t, exit, EXIT_FAILURE */

static const int bytes_per_word = __WORDSIZE / 8;

/********************Memmove Function definition ****************************/

void *Memmove(void *dest, const void *src, size_t n)
{
	size_t *ptr_src_word = NULL;
	unsigned char *ptr_src_byte = (unsigned char*)(src) + n - 1 ;
	
	size_t *ptr_dest_word = NULL;
    unsigned char *ptr_dest_byte = (unsigned char*)(dest) + n - 1 ;
    
	size_t remainder = 0;

	if(NULL == src)
	{
		if( NULL == dest)
		{
			puts("src is a null pointer");
			puts("dest is a null pointer");
			exit(EXIT_FAILURE);
		}
		puts("src is a null pointer");
	    exit(EXIT_FAILURE);
	}
	
	if( n <= 0 )
	{
		return dest;
	}
		
	/*Copies byte by byte until the address is aligns to word boundery */
	/*The 1st condition: Check if src is aligns <-> there is remainder? */
	while(((((size_t)ptr_src_byte)&(bytes_per_word -1)) && n) ||
	      ((((size_t)ptr_dest_byte)&(bytes_per_word -1)) && n))
	{
		*ptr_dest_byte = *ptr_src_byte;
		 --ptr_dest_byte;
		 --ptr_src_byte;
		 --n;
	}
	
	/*Now the addresses of src and dest point to theirs word boundery->align */
	/* Want to jump backward with 8 byte chanks so for the convenience
	   i "walk" forward '1'  bytes' addresses of each ptr_byte */
	ptr_src_word = (size_t*)(++ptr_src_byte);
	ptr_dest_word = (size_t*)(++ptr_dest_byte);
	
	/* Save the remainder(bytes number) of 'n' modulo bytes_per_word */
	remainder = n & (bytes_per_word - 1); 
	
	/*Get the number of the word-size chunks that enter in 'n' w/o renainder*/
	n = n >> 3; 

	/* Copies word-size chunks */ 
    /* Point to 1 word-size address backward before copying */
	while( n )
	{
		--ptr_dest_word;
		--ptr_src_word;
		*ptr_dest_word = *ptr_src_word;
		 --n;
	}

	/* Copies byte by byte with the remainder */ 
    ptr_src_byte = (unsigned char*)ptr_src_word;
	ptr_dest_byte = (unsigned char*)ptr_dest_word;
	
	while(remainder)
    {
    	
    	--ptr_dest_byte;
		--ptr_src_byte;
    	*ptr_dest_byte = *ptr_src_byte;
		--remainder;
    }
    
    return dest;

}

/********************Memcpy Function definition ****************************/

void *Memcpy(void *dest, const void *src, size_t n)
{
	size_t *ptr_src_word = NULL;
	unsigned char *ptr_src_byte = (unsigned char*)src;
	
	size_t *ptr_dest_word = NULL;
    unsigned char *ptr_dest_byte = (unsigned char*)dest;
    
	size_t remainder = 0;

	if(NULL == src)
	{
		if( NULL == dest)
		{
			puts("src is a null pointer");
			puts("dest is a null pointer");
			exit(EXIT_FAILURE);
		}
		puts("src is a null pointer");
	    exit(EXIT_FAILURE);
	}
	
	if( n <= 0 )
	{
		return dest;
	}

    /*Copies byte by byte until the address is aligns to word boundery */
	/*The 1st condition: Check if src is aligns <-> there is remainder? */
	while(((((size_t)ptr_src_byte)&(bytes_per_word -1)) && n) ||
	      ((((size_t)ptr_dest_byte)&(bytes_per_word -1)) && n))
	{
		*ptr_dest_byte = *ptr_src_byte;
		 ++ptr_dest_byte;
		 ++ptr_src_byte;
		 --n;
	}
	
	/*Now the addresses of src and dest point to theirs word boundery->align */
	ptr_src_word = (size_t*)ptr_src_byte;
	ptr_dest_word = (size_t*)ptr_dest_byte;
	
	/* Save the remainder(bytes number) of 'n' modulo bytes_per_word */
	remainder = n & (bytes_per_word - 1); 
	
	/*Get the number of the word-size chunks that enter in 'n' w/o renainder*/
	n = n >> 3; 
	
	/* Copies word-size chunks */ 
	while( n )
	{
		*ptr_dest_word = *ptr_src_word;
		 ++ptr_dest_word;
		 ++ptr_src_word;
		 --n;
	}
	
    /* Copies byte by byte with the remainder */ 
    ptr_src_byte = (unsigned char*)ptr_src_word;
	ptr_dest_byte = (unsigned char*)ptr_dest_word;
	
	while(remainder)
    {
    	*ptr_dest_byte = *ptr_src_byte;
		++ptr_dest_byte;
		++ptr_src_byte;
    	--remainder;
    }
    
    return dest;
}

/********************Memset Function definition ****************************/

void *Memset(void *s, int c, size_t n)
{
	
	size_t *ptr_word = NULL;
	unsigned char *ptr_byte = (unsigned char*)s;
	
	size_t c_word = c & 0xff;
	unsigned char c_byte = c & 0xff;
	
	size_t remainder = 0;
    int i = 3;
	if(NULL == s)
	{
		puts("s is a null pointer");
		exit(EXIT_FAILURE);
	}
	
	if( n <= 0 )
	{
		return s;
	}
	
	/* Duplication of 'c' input to appear in each byte of a word size
	   in order to handle a copy of word-size chunks, when the address
	   that s points to it divides by word size without remainder; 
	   i.e: The address is aligns to a word boundary */
	for(i = 3; i < 6 ; ++i)
	{
		c_word = c_word | (c_word<<(1<<i)); 
	}   
	 
	/*Copies byte by byte until the address is aligns to word boundery */
	/*The 1st condition: Check if ptr_byte is aligns <-> there is remainder? */
	while((((size_t)ptr_byte)&(bytes_per_word -1)) && n)
	{
		*ptr_byte = c_byte;
		 ++ptr_byte;
		 --n;
	}
	/* Now the address that (size_t)ptr_byte points to it is aligns */
	ptr_word = (size_t*)ptr_byte;
	
	/* Save the remainder(bytes number) of 'n' modulo bytes_per_word */
	remainder = n & (bytes_per_word - 1); 
	
	/*Get the number of the word-size chunks that enter in n w/o renainder*/
	n = n >> 3; 
	
	/* Copies word-size chunks */ 
	while( n )
	{
		*ptr_word = c_word;
		++ptr_word;
		--n;
	}
    /* Copies byte by byte with the remainder */ 
    ptr_byte = (unsigned char*)ptr_word;
    
    while(remainder)
    {
    	*ptr_byte = c_byte;
    	++ptr_byte;
    	--remainder;
    }
	
	return s;
}



