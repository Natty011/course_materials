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
#include "heap_pq.h" 

#include "knights_tour.h" 
#include "bit_array.h" 
#include "heap.h" 

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
		 bit_arr_t board,  position_t *ret_path); /* , position_t *ret_path  */
static bool_t
 RecKnightsTour(bit_arr_t board,position_t *ret_path,
		uint8_t x_begin,uint8_t y_begin,
			 uint8_t path_length, heap_pq_t* heap_pq_min);

static int
SortingFunc(void* check_data ,void* new_data, void* param);

#ifdef PRINTS
	void PrintBoard(position_t *ret_path)
#endif

/******************************************************************************/
/*******************End Of Static Functions declartions************************/
/******************************************************************************/

/******************************************************************************/

/************************************************************/
/********************  KnightsTour  *************************/
/************************************************************/

int KnightsTour(uint8_t x_begin, uint8_t y_begin,
				 position_t *ret_path)
{
	bit_arr_t board = 0;
	uint8_t path_length = 0; 
	bool_t res = FALSE;
	void *dummy = NULL;
	
	heap_pq_t *heap_pq_min = NULL;

	heap_pq_min = HeapCreate(&dummy, SortingFunc);

	if(! heap_pq_min )
	{
		printf("line: %d \n" , __LINE__ );
		puts("Failes in_1: Create - Allocation");
		return FALSE;
	}

	res = RecKnightsTour(board, ret_path, x_begin,
		 y_begin, path_length, heap_pq_min);

	 if (res)
	 {
		printf("Solution found!\n");
		PrintBoard(ret_path);
	 }
	else
	{
		printf("No solution found!\n");
	}

	HeapPQueueDestroy(heap_pq_min);
	heap_pq_min = NULL;	

	return res;
}

static bool_t RecKnightsTour(bit_arr_t board,position_t *ret_path,
	 uint8_t x_begin,uint8_t y_begin,
	  uint8_t path_length, heap_pq_t* heap_pq_min )
{
	uint8_t x_next = 0, y_next = 0, move_index = 0, move_index2 = 0,
	 temp_length = path_length + 1, mx_next = 0, my_next = 0, count = 0;
	int degree = 0;
	bool_t result = FALSE;
	BitArrSetOn(board, ( x_begin * COLUMN_SIZE + y_begin ) % BOARD_SIZE ) ;

	/*
	HeapPQueueDestroy(heap_pq_degrees);
	heap_pq_degrees = NULL;
	*/

	if(BOARD_SIZE == temp_length)
	{
		return TRUE;
	}

	
		// Check all possible moves
		for(move_index = 0; move_index < KNIGHT_MOVE_NUM; ++move_index)
		{
			// Next moves
			x_next = x_begin + lut_knight_moves[move_index][0];
			y_next = y_begin + lut_knight_moves[move_index][1];
				
			if( !IsLegal(x_next, y_next, board) )
			{
				continue;
			}

			degree = Degree(x_next, y_next, board, ret_path );

			if( 0 != degree )
			{
				HeapPQueueEnqueue(heap_pq_min, &degree);
			}

			if(! HeapPQueueIsEmpty(heap_pq_min ) )
			{
				result = RecKnightsTour(board, ret_path + 1,
					ret_path->x, ret_path->y, path_length + 1, heap_pq_min );
			
				if(TRUE == result )
				{
					return TRUE;
				}			 
				else if(! HeapPQueueIsEmpty(heap_pq_min ) ) /* result == FAIL */
				{
					HeapPQueueDequeue(heap_pq_min);
				}

			}
		}

	BitArrSetOff(board, ( x_begin * COLUMN_SIZE + y_begin ) % BOARD_SIZE ) ;

	return FALSE;

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
		 ( UN_VISITED == BitArrGetVal( board,
					 (x * COLUMN_SIZE + y )% BOARD_LIMIT) );
}

/************************************************************/
/********************  IsLegal**********************/
/************************************************************/

uint8_t Degree( uint8_t x_begin, uint8_t y_begin,
			 bit_arr_t board, position_t *ret_path ) /* , position_t *ret_path*/
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

	ret_path->x = x_begin % BOARD_SIZE;
	ret_path->y = y_begin % BOARD_SIZE;
	
	return degree;
}

/************************************************************/
/********************  SortingFunc**********************/
/************************************************************/
static int SortingFunc(void* check_data ,void* new_data, void* param)
{
	UNUSED(param);
	return (-1) * (*(int*)check_data - *(int*)new_data);
}


#ifdef PRINTS

void PrintBoard(position_t *ret_path)
{
	size_t index = 0 ;

	printf("return_path[] = \n" );

	while( index <= BOARD_LIMIT )
	{
		printf("index = %ld \n", index);
		printf("x = %ld, y = %ld \n", ret_path->x, ret_path->y );
		++index;
	}
}

#endif

/************************************************************/
/********** End Of Static Functions definition  *************/
/************************************************************/


// Check all possible neighbors
		/*
		for(move_index2 = 0; move_index2 < KNIGHT_MOVE_NUM ; ++move_index2)
		{
			mx_next = x_next + lut_knight_moves[move_index2][0];
		    my_next = y_next + lut_knight_moves[move_index2][1];

			if( !IsLegal(mx_next, my_next, board) )
			{
				continue;
			}
			
        	
			degree = Degree(x_next, y_next, board );

			if( 0 != degree )
			{
				HeapPQueueEnqueue(heap_pq_min, &degree);
			}
		}
		*/	

/*
		ret_path->x = x_begin % BOARD_SIZE;
		ret_path->y = y_begin % BOARD_SIZE;

		ret_path->x = x_next % BOARD_SIZE;
		ret_path->y = y_next % BOARD_SIZE;

	*/		





	 
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




