/******************************************************************************
*	Version 1.0
******************************************************************************/
#ifndef __BIT_ARR_H__
#define __BIT_ARR_H__

#include <stddef.h>  /* size_t */

typedef size_t bit_arr_t;

/*
Indexes start from 0 onwards to 63 from left to right.
Index 0 is  the closest bit to the address of the bit array.
*/

/******************************************************************************
*	Name: BitArrSetAll
*	Description: Takes the Bitarray, and returns its value with all bits sets.
*	Arguments: The BitArray.
*	Return: The maximum value for the bitarray’s type.
*	Notes: N\A.
******************************************************************************/
bit_arr_t BitArrSetAll(bit_arr_t bit_array);


/******************************************************************************
*	Name: BitArrResetAll
*	Description: Reset all bits in an array to zero 
*	Arguments: bit_array
*	Return: Zeroed array
*	Notes: N\A.
******************************************************************************/
bit_arr_t BitArrResetAll(bit_arr_t bit_array);


/******************************************************************************
*	Name: BitArrSetOn
*	Description: Set bit in <index> position
*	Arguments: bit_array, index
*	Return: The updated bit_array.
* 	Notes : Undefined behaviour if "index" is out of range ( >=64 or <0 )
******************************************************************************/
bit_arr_t BitArrSetOn(bit_arr_t bit_array, size_t index);


/******************************************************************************
*	Name: BitArrSetOff
*	Description: Sets a bit at a specific index to ‘0’
*	Arguments: “index” - The index of the bit
*	Return: Returns “bit_array” with the bit at “index” set to zero
* 	Notes : Undefined behaviour if "index" is out of range ( >=64 or <0 )
******************************************************************************/
bit_arr_t BitArrSetOff(bit_arr_t bit_array, size_t index);


/******************************************************************************
*	Name: BitArrSetBit
*	Description: Sets bit at given index to given value.
*	Arguments: Bit_array, “index” - The index of the bit, “bool_val” - New value
*	Return: bit array.
* 	Notes : Undefined behaviour if "index" is out of range ( >=64 or <0 )
*	 Undefined behavior if “bool_val” is out of range ( >1 or <0)
******************************************************************************/
bit_arr_t BitArrSetBit(bit_arr_t bit_array, size_t index, int bool_val);


/******************************************************************************
*	Name: BitArrGetVal
*	Description: returns the bit value in the index position
*	Arguments: Bit Array, index.
*	Return: an int that represent the value in the bit
* 	Notes : Undefined behaviour if "index" is out of range ( >=64 or <0 )
******************************************************************************/
int BitArrGetVal(bit_arr_t bit_array, size_t index);


/******************************************************************************
*	Name: BitArrFlipBit.
*	Description: Function that toggles (flips) the bit at a specified index
*	in a given bitarray. If the bit at the given index is 0 , it changes it 
*	to 1 , and if the bit is 1 , it changes it to 0. 
*	Arguments: Bit array , index.
*	Return:Bit array .
* 	Notes : Undefined behaviour if "index" is out of range ( >=64 or <0 )
******************************************************************************/
bit_arr_t BitArrFlipBit(bit_arr_t bit_array, size_t index);


/******************************************************************************
*	Name: BitArrMirror
*	Description: The function reverses a bit array.
*	Arguments: bit_array.
*	Return: reverse bit_array.
* 	Notes: N\A.
******************************************************************************/
bit_arr_t BitArrMirror(bit_arr_t bit_array);


/******************************************************************************
*	Name: BitArrRotateLeft
*	Description: Move the MSH  to be LSB ‘shifts_num’ times
*	Arguments: An array of 64 bits, and the number of the rotations
                  that need to do.
*	Return: The result of the rotate’s operation
* 	Notes: The LSB is in the rightmost side, and MSB vise versa 
*******************************************************************************/
bit_arr_t BitArrRotateLeft(bit_arr_t bit_array, size_t shifts_num);


/*******************************************************************************
*	Name: BitArrRotateRight
*	Description: Move the LSB  to be MSB ‘shifts_num’ times
*	Arguments: An array of 64 bits, and the number of the rotations
                  that need to do.
*	Return: The result of the rotate’s operation
* 	Notes: The LSB is in the rightmost side, and MSB vise versa 
*******************************************************************************/
bit_arr_t BitArrRotateRight(bit_arr_t bit_array, size_t shifts_num);


/*******************************************************************************
*	Name: BitArrToString
*	Description: Converts the array into a string
*	Arguments: “dest” - Destination for the converted array
*	Return: Returns pointer to “dest”
* 	Notes: Dest must be at least 65 bytes length, else undefined behaviour
*******************************************************************************/
char* BitArrToString(size_t bit_array, char *dest);

/*******************************************************************************
*	Name:BitArrCountOn
*	Description: Counts the number of set bits in the array
*	Arguments: bit_array
*	Return:number of set bits (size_t)
* 	Notes: N\A.
*******************************************************************************/
size_t BitArrCountOn(bit_arr_t bit_array);


/******************************************************************************
*	Name:BitArrCountOff
*	Description: Counts the number of zeroed bits in the array
*	Arguments: bit_array
*	Return: number of zeroed bits (size_t)
* 	Notes: N\A.
******************************************************************************/
size_t BitArrCountOff(bit_arr_t bit_array);


#endif	/*  __BIT_ARR_H__ */

