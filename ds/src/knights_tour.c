/***************************************
* Author : Natty
* Reviewer : Matan
* Date : 26 / 02 / 2025
* Last update: 02 / 03 / 2025
*****************************************/
/*#define PRINTS*/
#ifdef PRINTS
	#include <stdio.h> /* printf */
#endif

#include <assert.h> 	/* assert */
#include <stdlib.h> 	/* malloc, free */

#include "pqueue.h"

#include "knights_tour.h" 
#include "bit_array.h" 

#define UNUSED( var )       ( (void)var )

#define KNIGHT_MOVE_NUM		8
#define BOARD_LIMIT 		63
#define COLUMN_SIZE        	8
#define BOARD_SIZE 			 64 
#define UN_VISITED          0

/************************************************************/
/********************  lut_knight_moves**********************/
/************************************************************/

static int lut_knight_moves[8][2] = 
{
	{-2, -1}, {-2, 1}, {2, -1}, {2, 1},
    {-1, -2}, {-1, 2}, {1, -2}, {1, 2}
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
} op_result_t;

/******************************************************************************/
/***************************** Management struct ******************************/
typedef struct position_degree
{
	position_t neibour;
	int degree; /* degree*/
	uint8_t move_index;
}position_degree_t;

/******************************************************************************/
/************************ static functions declartions ************************/
/******************************************************************************/
op_result_t IsInBoard( uint8_t x, uint8_t y );
op_result_t IsLegalMove(uint8_t x, uint8_t y, bit_arr_t board);
uint8_t Degree( uint8_t x_begin, uint8_t y_begin, bit_arr_t board ) ;

static op_result_t
 RecKnightsTour(uint8_t x_begin, uint8_t y_begin,
	uint8_t path_length, bit_arr_t visited, position_t *ret_path, pqueue_t *pq);

static int SortingFunc(void* check_data ,void* new_data);
/*void
 PrintBoard(uint8_t board[COLUMN_SIZE][COLUMN_SIZE],  position_t *ret_path);*/


#ifdef PRINTS
	void PrintBoard(uint8_t board[COLUMN_SIZE][COLUMN_SIZE],  position_t *ret_path);
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
	bit_arr_t visited = 0;
	uint8_t path_length = 0; 
	op_result_t res = FALSE;
	pqueue_t *pq = PQueueCreate(SortingFunc);
    uint8_t board[COLUMN_SIZE][COLUMN_SIZE] = { 0 };

	visited = BitArrResetAll(visited);
	res = RecKnightsTour( x_begin, y_begin, path_length, visited, ret_path, pq);

	 if (res)
	 {
		/*printf("Solution found!\n");*/
		/*PrintBoard(board, ret_path);*/
		
	 }

	else
	{
		printf("No solution found!\n");
	}
	PQueueDestroy(pq);
	pq = NULL;
	return !res;
}

static op_result_t
 	RecKnightsTour(uint8_t x_begin, uint8_t y_begin,
	uint8_t path_length, bit_arr_t visited, position_t *ret_path, pqueue_t *pq)
{
	uint8_t move_index = 0, x_next = 0, y_next = 0, min = 0;
	size_t size = 0 ;
	int temp_degree = 0;

	op_result_t result = FALSE;
	position_degree_t next_move[8] = { 0 };

	ret_path[path_length].x = x_begin;
    ret_path[path_length].y = y_begin;
	
	visited = BitArrSetOn(visited, ( x_begin * COLUMN_SIZE )  +  y_begin ) ;

	PQueueClear(pq);

	if( BOARD_LIMIT == path_length ) 
	{
		return TRUE;
	}

		for(move_index = 0; move_index < KNIGHT_MOVE_NUM; ++move_index)
		{
			x_next = x_begin + lut_knight_moves[move_index][0];
			y_next = y_begin + lut_knight_moves[move_index][1];

			if( !IsLegalMove(x_next, y_next, visited) )
			{
				continue;
			}
			/* if there is a move from step 62 so this is the last
				point that valid, with 0 degree */
			if( BOARD_LIMIT - 1 == path_length)
			{
				next_move[move_index].neibour.x =  x_next;
				next_move[move_index].neibour.y =  y_next;
				next_move[move_index].degree = Degree(x_next, y_next, visited );
				result = RecKnightsTour( x_next, y_next, path_length + 1,
										 visited, ret_path, pq);
				
				if(TRUE == result )
				{
					return TRUE;
				}		 
			}

			temp_degree = Degree(x_next, y_next, visited );

			if( 0 != temp_degree )
			{
				
				next_move[move_index].degree = Degree(x_next, y_next, visited );
				next_move[move_index].neibour.x =  x_next;
				next_move[move_index].neibour.y =  y_next;
				next_move[move_index].move_index = move_index;	

				PQueueEnqueue(pq, next_move + move_index);

				++size;
			}
		}
		
		while ( size ) 
		{
			position_degree_t *next_move_p = NULL;
			
			next_move_p = (position_degree_t *)PQueuePeek(pq);
			min = next_move_p->move_index;
			
			result = RecKnightsTour( next_move_p->neibour.x, 
									next_move_p->neibour.y, path_length + 1,
								    visited, ret_path, pq);
	
			if(TRUE == result )
			{
				return TRUE;
			}

			visited = BitArrSetOff(visited,( next_move_p->neibour.x * COLUMN_SIZE )
									+ next_move_p->neibour.y) ;
			--size;
			PQueueClear(pq);

			next_move[min].degree = 0; /* not valid point/dead-end, so mark 
										 the degree as zero  */

			if(size > 0 )
			{
				for(move_index = 0; move_index < 8; ++move_index)
				{
					if( ( min != move_index) && 0 != next_move[move_index].degree )
					{
						PQueueEnqueue(pq, next_move + move_index);
					}
				}
			}	
			
		}
		
	visited = BitArrSetOff(visited, ( x_begin * COLUMN_SIZE )  +  y_begin) ;

	return FALSE;

}	
	
/************************************************************/
/*************  Static Functions definition  ****************/
/************************************************************/


/************************************************************/
/*************************  IsInBoard **************************/
/************************************************************/
op_result_t IsInBoard( uint8_t x, uint8_t y )
{
	return  (x < COLUMN_SIZE ) &&
			(y < COLUMN_SIZE ) ;
}

/************************************************************/
/********************  IsLegal**********************/
/************************************************************/

op_result_t IsLegalMove(uint8_t x, uint8_t y, bit_arr_t board)
{
	return IsInBoard(x, y) &&
		(! BitArrGetVal( board, (x * COLUMN_SIZE + y ) ) ) ;
}

/************************************************************/
/********************  IsLegal**********************/
/************************************************************/

uint8_t Degree( uint8_t x_begin, uint8_t y_begin, bit_arr_t board ) 
{
	uint8_t degree = 0, move_index = 0;
	uint8_t next_x = 0, next_y = 0;

	for(move_index = 0; move_index < KNIGHT_MOVE_NUM; ++move_index)
	{
		next_x = x_begin + lut_knight_moves[move_index][0];
		next_y = y_begin + lut_knight_moves[move_index][1];
 
		if( IsLegalMove(next_x, next_y, board) ) 
		{
			++degree ;
		} 
	}

	return degree;
}

/************************************************************/
/********************  SortingFunc**********************/
/************************************************************/
static int SortingFunc(void* check_data ,void* new_data)
{
	

	return  ((( (position_degree_t*)check_data)->degree) -
							 (((position_degree_t*)new_data)->degree) );
}

#ifdef PRINTS

void PrintBoard(uint8_t board[COLUMN_SIZE][COLUMN_SIZE],  position_t *ret_path)
	{
		int i = 0, j = 0;
		size_t sum = 0; /* total sum 2016*/

		for (i = 0; i < BOARD_SIZE ; i++)
		{
         
			board[ret_path[i].x][ret_path[i].y] = i;
        }
        
        for (i = 0; i < COLUMN_SIZE; i++) 
		{
            for (j = 0; j < COLUMN_SIZE; j++) 
			{
                printf("%2d ", board[i][j]);
				sum += board[i][j];

            }
            printf("\n");
        }

		if(2016 != sum)
		{
			puts("Failure");
		}
		/*printf("sum = %lu \n", sum);*/



	}


#endif

/************************************************************/
/********** End Of Static Functions definition  *************/
/************************************************************/


	

