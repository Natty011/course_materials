/***************************************
* Author : Natty
* Reviewer : 
* Date : 26 / 02 / 2025
* Last update: 26 / 02 / 2025
*****************************************/
/*#define PRINTS*/
#ifdef PRINTS
	#include <stdio.h> /* printf */
#endif
#include <assert.h> 	/* assert */
#include <stdlib.h> 	/* malloc, free */

#include "knights_tour.h" 
#include "bit_array.h" 

#define KNIGHT_MOVE_NUM		8
#define BOARD_LIMIT 		63
#define COLUMN_SIZE        	8
#define BOARD_SIZE 			BOARD_LIMIT + 1	
#define UN_VISITED          0

/************************************************************/
/********************  lut_knight_moves**********************/
/************************************************************/

static int lut_knight_moves[8][2] = 
{
	{-2, -1}, {-2, +1}, {+2, -1}, {+2, +1},
    {-1, -2}, {-1, +2}, {+1, -2}, {+1, +2}
};

/******************************************************************************/
/***************************** Success / Fail Enum ****************************/
/******************************************************************************/

typedef enum
{
	SUCCESS = 0,
	FAIL = 1

} result_t;

/******************************************************************************/
/******************************* True / False Enum ****************************/
/******************************************************************************/

typedef enum
{
	FALSE = 0,
	TRUE = 1
} bool_t;

/******************************************************************************/
/***************************** Management struct ******************************/


/******************************************************************************/
/************************ static functions declartions ************************/
/******************************************************************************/
bool_t InBoard( uint8_t x, uint8_t y );
bool_t IsLegal(uint8_t x, uint8_t y, bit_arr_t board);
uint8_t Degree( uint8_t x_begin, uint8_t y_begin,
		 bit_arr_t board); /* , position_t *ret_path  */
static bool_t
 RecKnightsTour(bit_arr_t board,position_t *ret_path,
		uint8_t x_begin,uint8_t y_begin, uint8_t path_length);
#ifdef PRINTS
	/*void PrintArray( heap_t* heap );	*/						
#endif

/******************************************************************************/
/*******************End Of Static Functions declartions************************/
/******************************************************************************/

/******************************************************************************/

/************************************************************/
/********************  KnightsTour  *************************/
/************************************************************/

int KnightsTour(uint8_t x_begin, uint8_t y_begin, position_t *ret_path)
{
	bit_arr_t board = 0;
	uint8_t path_length = 0; 
	bool_t res = FALSE;

	res = RecKnightsTour(board, ret_path, x_begin, y_begin, path_length);

	return res;
}

static bool_t RecKnightsTour(bit_arr_t board,position_t *ret_path,
	 uint8_t x_begin,uint8_t y_begin, uint8_t path_length)
{
	uint8_t x_next = 0, y_next = 0, move_index = 0, temp_length = path_length + 1;
	int degree = 9;
	ret_path->x = x_begin % BOARD_SIZE;
	ret_path->y = y_begin % BOARD_SIZE;

	BitArrSetOn(board, ( x_begin * COLUMN_SIZE + y_begin ) % BOARD_SIZE ) ;

	if(BOARD_SIZE == temp_length)
	{
		return TRUE;
	}

	for(move_index = 0; move_index < KNIGHT_MOVE_NUM; ++move_index)
	{
		/*for(count = )*/
			
		if( !IsLegal(x_next, y_next, board) )
		{
			continue;

		}

		x_next = x_begin + lut_knight_moves[move_index][0];
		y_next = y_begin + lut_knight_moves[move_index][1];

		degree = Degree(x_next, y_next, board );




	}
}	 

/************************************************************/
/*************  Static Functions definition  ****************/
/************************************************************/


/************************************************************/
/*************************  InBoard**************************/
/************************************************************/
bool_t InBoard( uint8_t x, uint8_t y )
{
	return  0 <= x * COLUMN_SIZE + y &&
				x * COLUMN_SIZE + y <= BOARD_LIMIT ;
}

/************************************************************/
/********************  IsLegal**********************/
/************************************************************/


bool_t IsLegal(uint8_t x, uint8_t y, bit_arr_t board)
{
	return InBoard(x, y) &&
		 ( UN_VISITED == BitArrGetVal( board, (x * COLUMN_SIZE + y )% BOARD_LIMIT) );
}

/************************************************************/
/********************  IsLegal**********************/
/************************************************************/

uint8_t Degree( uint8_t x_begin, uint8_t y_begin,
			 bit_arr_t board ) /* , position_t *ret_path*/
{
	uint8_t degree = 0, move_index = 0;
	uint8_t next_x = 0, next_y = 0;

	for(move_index = 0; move_index < KNIGHT_MOVE_NUM; ++move_index)
	{
		next_x = x_begin + lut_knight_moves[move_index][0];
		next_y = y_begin + lut_knight_moves[move_index][1];
 
		if( IsLegal(next_x, next_y, board) ) 
		{
			++degree ;

		} 
	}
	
	return degree;
}
#ifdef PRINTS
/*
void PrintArray( heap_t* heap )
{
	size_t size = 1 ;
	int* element = NULL;
	printf("HeapArray[] = \n" );
	while( size <= HeapSize( heap ) )
	{
		element = *(void**)VectorGetAccess(heap->vector, size );
		printf("index = %ld , value = %d \n", size, *element );
			++size;
	}
}
void PrintVector(heap_t *h)
{
    vector_t *v = h->vector;
    size_t len = VectorSize(v), i = 0;

    for (i = 0; i < len; ++i)
    {
        printf("%3d", **(int **)VectorGetAccess(v, i+1));
    }
    putchar('\n');
}

void *GetVectorIndex(heap_t *h, size_t index)
{
    return *(void **)VectorGetAccess(h->vector, index);
}
*/
#endif

/************************************************************/
/********** End Of Static Functions definition  *************/
/************************************************************/









