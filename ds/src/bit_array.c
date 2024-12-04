/***************************************
* Author : Natty
* Reviewer : 
* Date : 03 / 12 / 2024
* Last update: 03 / 12 / 2024
*****************************************/

#include <stdio.h> /* puts, printf, __WORDSIZE */
#include <assert.h> /* assert */
#include "bit_array.h" /*  */
#include <stdlib.h> /* exit*/
#include <string.h> /* strlen */
#define TOTAL_BITS 64
#define BOOL_VAL 1

/***************************function declaration**************************/

static unsigned char ByteMirrorLut( unsigned char number );
static char* SizetToa2Base(size_t n, char* str, int base);
static void ReverseStr(char* str);
static int CountBitLut(unsigned int n);

/***************************End of function declaration******************/

/********************  BitArrSetAll  ****************************/
bit_arr_t BitArrSetAll(bit_arr_t bit_array)
{
	bit_array = -1;
	return bit_array;
}

/********************  BitArrResetAll  ****************************/
bit_arr_t BitArrResetAll(bit_arr_t bit_array)
{
	bit_array =0; /* can be deleted*/
	return bit_array;
}
/********************  BitArrSetOn  ****************************/
bit_arr_t BitArrSetOn(bit_arr_t bit_array, size_t index)
{
	assert( index < TOTAL_BITS );
	return bit_array | ( (size_t)1 << index );
	
}
 /********************  BitArrSetOff  ****************************/
bit_arr_t BitArrSetOff(bit_arr_t bit_array, size_t index)
{
	size_t bit = -1;
	assert( index < TOTAL_BITS );
	bit = bit ^ ( (size_t)1 << index );
	return bit_array & bit;
}

/********************  BitArrSetBit  ****************************/
bit_arr_t BitArrSetBit(bit_arr_t bit_array, size_t index, int bool_val)
{
	assert( bool_val == 0 || bool_val == 1 );
	return bool_val ? BitArrSetOn(bit_array, index) : \
	                  BitArrSetOff(bit_array, index);
}

/********************  BitArrGetVal  ****************************/
int BitArrGetVal(bit_arr_t bit_array, size_t index)
{
	size_t bit = (size_t)1 << index ;
	size_t bit2 = bit_array & bit ;

	assert( index < TOTAL_BITS );
	return bit2 ? 1 : 0;

}

/********************  BitArrFlipBit  ****************************/
bit_arr_t BitArrFlipBit(bit_arr_t bit_array, size_t index)
{
	return BitArrGetVal(bit_array, index) ? BitArrSetOff(bit_array, index): \
											BitArrSetOn(bit_array, index);
}

/********************  BitArrMirror  ****************************/
bit_arr_t BitArrMirror(bit_arr_t bit_array)
{
	
	size_t word = 0;
	unsigned char byte = 0;
	int i = 0; 
	
	/* 1st shift */
	for( i = 0; i < 7 ; ++i)
	{
		byte = ByteMirrorLut( bit_array & 0xff );
		word = word | byte;
		word = word << 8;
		bit_array = (bit_array >> 8);
	
	}
	
	byte = ByteMirrorLut((bit_array >>= 8) & 0xff );
	word = word | byte;
	
	return word;
	
}

static unsigned char ByteMirrorLut( unsigned char number )
{
    unsigned char result = 0;
    /* Shifting the nibbles to get each nibble separately */

    unsigned char REVERSE_NUMBER_TABLE[16] = 
    {
        0x0, 0x8, 0x4, 0xC, /* [0...3]*/
        0x2, 0xA, 0x6, 0xE, /* [4...7]*/
        0x1, 0x9, 0x5, 0xD, /* [8...11]*/
        0x3, 0xB, 0x7, 0xF, /* [12...15]*/
    };

   unsigned char LsbNibble = number << 4; 
   unsigned char MsbNibble = number >> 4;

    /* Sum the 2 nibbles after the reversinng*/
    result = (REVERSE_NUMBER_TABLE[LsbNibble>>4]<<4) |
              REVERSE_NUMBER_TABLE[MsbNibble];
    return result;
}

/********************  BitArrRotateLeft  ****************************/
bit_arr_t BitArrRotateLeft(bit_arr_t bit_array, size_t shifts_num)
{
	
	size_t msb_bit = 0;
    size_t i = 0;
	
	for( i = 0; i < shifts_num % TOTAL_BITS ; ++i)
	{
		msb_bit = bit_array & 0x8000000000000000;

		bit_array = bit_array << 1;

		bit_array = bit_array | (msb_bit ? 1 : 0);
	}
	
	return bit_array;
	
}

/********************  BitArrRotateRight  ****************************/
bit_arr_t BitArrRotateRight(bit_arr_t bit_array, size_t shifts_num)
{
	size_t msb_bit = 0;
    size_t i = 0;
	
	for( i = 0; i < shifts_num % TOTAL_BITS ; ++i)
	{
		msb_bit = bit_array & 0x0000000000000001;
		bit_array = bit_array >> 1;
		bit_array = bit_array | (msb_bit ? BitArrMirror(msb_bit) : 0);
	}
	
	return bit_array;
}

/********************  BitArrToString  ****************************/
char *BitArrToString(size_t bit_array, char *dest)
{
	
	assert (dest);
	return SizetToa2Base(bit_array, dest, 2);
	
}



/****************** SizetToa2Base function definition *******************/
/* 
   DESCRIPTION: Converts an integer value to a null-terminated string
                using the specified base and stores the result in the
                array given by str parameter.

   RETURN VALUE: A pointer to the resulting null-terminated string,
                  same as parameter str.
                  
    NOTE: 1) No checks for overflow or underflow are done.
            base 2 input can be converted.
*/
         

static char* SizetToa2Base(size_t n, char* str, int base)
{

	int remainder = 0;
	char* pstr = str;
	int i = 0;
	if(NULL == str )
	{
		puts("str is a null pointer");
		exit(EXIT_FAILURE);
	}
	
	while( i < TOTAL_BITS )
	{
		remainder = n % base;
		*str++ = remainder + '0';
		n = n / base;
		++i;
	}
	
	*str = '\0'; 
	ReverseStr(pstr);
	return pstr;	
}

/* An auxilary function to reverse a string*/
static void ReverseStr(char* str)
{

	char temp = 0;
	int low = 0;
	int high = strlen(str) - 1 ;

	while( low < high )
	{
		temp = str[low];
		str[low] = str[high];
		str[high] = temp;
		low++;
		high--;
	}
	
}


/********************  BitArrCountOn  ****************************/
size_t BitArrCountOn(bit_arr_t bit_array)
{
	size_t count = 0;
	count += CountBitLut( bit_array & 0xffffffff );
	count += CountBitLut( (bit_array>>32) & 0xffffffff );
	
	return count;
	
}


/* Counting by multiplying each MSB niblle with the number */
static int CountBitLut(unsigned int n)
{
    int LsbNibble = 0xF;
    int count = 0;
  
    /* Puting in each cell the number of bits in each niblle from 0x0->0xF*/
    int COUNT_BITS_TABLE[16] = 
    {
        0x0, 0x1, 0x1, 0x2, /* [0...3]*/
        0x1, 0x2, 0x2, 0x3, /* [4...7]*/
        0x1, 0x2, 0x2, 0x3, /* [8...11]*/
        0x2, 0x3, 0x3, 0x4, /* [12...15]*/
    };
    
    count += COUNT_BITS_TABLE[ (n & LsbNibble)]; /* 1 */
    count += COUNT_BITS_TABLE[ ((n>>4) & LsbNibble) ] ; /* 2 */
    count += COUNT_BITS_TABLE[ ((n>>8) & LsbNibble) ] ; /* 3 */
    count += COUNT_BITS_TABLE[ ((n>>12) & LsbNibble) ] ; /* 4 */
    count += COUNT_BITS_TABLE[ ((n>>16) & LsbNibble) ] ; /* 5 */
    count += COUNT_BITS_TABLE[ ((n>>20) & LsbNibble) ] ; /* 6 */
    count += COUNT_BITS_TABLE[ ((n>>24) & LsbNibble) ] ; /* 7 */
    count += COUNT_BITS_TABLE[ ((n>>28) & LsbNibble) ] ; /* 8 */
    
    return count;
}

/********************  BitArrCountOff  ****************************/

size_t BitArrCountOff(bit_arr_t bit_array)
{
	return ( TOTAL_BITS - BitArrCountOn(bit_array) );
}





