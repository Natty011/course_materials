#include <stdint.h>
#include <string.h>
#include <assert.h>
#include "bit_array.h"

#define TOTALBITS 64
#define BITSINBYTE 8
#define BITSINNIBBLE 4


typedef bit_arr_t ( *set_bit_func_t )( bit_arr_t , size_t );

bit_arr_t BitArrSetAll(bit_arr_t bit_array)
{	
	(void)bit_array;
	
	return (size_t)( (int64_t)(-1) );
}

bit_arr_t BitArrResetAll(bit_arr_t bit_array)
{
	(void)bit_array;
	return (bit_arr_t)0;
}

bit_arr_t BitArrSetOn(bit_arr_t bit_array, size_t index)
{
	assert( index  <= TOTALBITS );
	return bit_array | ((size_t)1 << index);
}

bit_arr_t BitArrSetOff(bit_arr_t bit_array, size_t index)
{
	assert( index  <= TOTALBITS );
	return  bit_array & ~( (size_t)1 << index ) ;
}

bit_arr_t BitArrSetBit(bit_arr_t bit_array, size_t index, int bool_val)
{
	static set_bit_func_t arr[2] = { BitArrSetOff ,  BitArrSetOn };
	assert( bool_val == 0 || bool_val == 1 );
	
	return arr[bool_val]( bit_array , index );
}

int BitArrGetVal(bit_arr_t bit_array, size_t index)
{
	assert( index  <= TOTALBITS );
	return ( ( bit_array >> index ) & 1 );
}

bit_arr_t BitArrFlipBit(bit_arr_t bit_array, size_t index)
{
	assert( index  <= TOTALBITS );
	return bit_array ^ ( (size_t)1 << index );
}



static uint8_t ByteMirror ( uint8_t byte )
{

	static uint8_t NibleMirrorLUT[] = 
	{
		0x0 , 0x8 , 0x4 , 0xc , 0x2 , 0xa , 0x6 , 0xe ,
		0x1 , 0x9 , 0x5 , 0xd , 0x3 , 0xb , 0x7 , 0xf
	};

	return NibleMirrorLUT[byte >> 4] | ( (NibleMirrorLUT[byte & 0xf]) << 4 );
}

bit_arr_t BitArrMirror(bit_arr_t bit_array)
{
	size_t i = 0;
	uint8_t* itr = (uint8_t*)&bit_array;
	size_t res = 0;
	
	for ( i = 0 ; i < BITSINBYTE - 1 ; ++i )
	{
		res |= (size_t)ByteMirror( *itr++ );
		res <<= BITSINBYTE;
	}
	
	return res | (size_t)ByteMirror(*itr);
}

bit_arr_t BitArrRotateLeft(bit_arr_t bit_array, size_t shifts_num)
{
	size_t n = shifts_num & (TOTALBITS - 1 ) ;
	return ( bit_array << n ) | ( bit_array >> (TOTALBITS - n) );     
}

bit_arr_t BitArrRotateRight(bit_arr_t bit_array, size_t shifts_num)
{
	size_t n = shifts_num & (TOTALBITS - 1 ) ;
	return ( bit_array >> n ) | ( bit_array << (TOTALBITS - n) );     
}

char* BitArrToString(size_t bit_array, char *dest)
{
	static char* NibleStringLUT[] = 
	{
		 "0000" , "0001" , "0010" , "0011" , "0100" , "0101" , "0110" , "0111"
		 ,"1000" , "1001" , "1010" , "1011" , "1100" , "1101" , "1110" , "1111"
	};
	char* start = dest;	
	size_t i = 0  , n = TOTALBITS / BITSINNIBBLE;
	assert( dest );
	bit_array = BitArrMirror( bit_array );
	for ( i = 0 ; i < n ; ++i )
	{
		strncpy( dest , NibleStringLUT[bit_array & 0xf] , BITSINNIBBLE);
		dest += BITSINNIBBLE;
		bit_array >>= BITSINNIBBLE;
	}
	*dest = '\0';
	
	return start;
}

size_t BitArrCountOn(bit_arr_t bit_array)
{
	size_t counter = 0;

	while ( bit_array )
	{
		++counter;
		
		bit_array &= ( bit_array - 1 );
	}
	
	return counter;
}

size_t BitArrCountOff(bit_arr_t bit_array)
{
	return TOTALBITS - BitArrCountOn( bit_array );
}
















