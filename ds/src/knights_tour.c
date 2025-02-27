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
typedef struct knights_tour
{
	position_t *ret_path[8];
	int degree;
	uint8_t current_move;
	
}knights_tour_t;


/******************************************************************************/
/************************ static functions declartions ************************/
/******************************************************************************/
op_result_t InBoard( uint8_t x, uint8_t y );
op_result_t IsLegal(uint8_t x, uint8_t y, bit_arr_t board);
uint8_t Degree( uint8_t x_begin, uint8_t y_begin,
		 bit_arr_t board,  position_t *ret_path); /* , position_t *ret_path  */
static op_result_t
 RecKnightsTour(bit_arr_t board,position_t *ret_path,
		uint8_t x_begin,uint8_t y_begin,
			 uint8_t path_length, heap_pq_t* heap_pq_min);

static int
SortingFunc(void* check_data ,void* new_data, void* param);

#ifdef PRINTS
	void PrintBoard(position_t *ret_path);
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
	op_result_t res = FALSE;
	heap_pq_t *heap_pq_min = NULL;

	heap_pq_min = HeapPQueueCreate(SortingFunc);

	if(! heap_pq_min )
	{
		printf("line: %d \n" , __LINE__ );

		puts("Failes in_1: Create - Allocation");
		return FALSE;
	}
/*
	mange_tour = 
		(knights_tour_t*)calloc(KNIGHT_MOVE_NUM, sizeof(knights_tour_t) );

		if(! mange_tour )
		{
			HeapPQueueDestroy(heap_pq_min);
			heap_pq_min = NULL;	

			printf("line: %d \n" , __LINE__ );
			puts("Failes in_2: Create - Allocation");
			return FALSE;
		}
*/
	board = BitArrResetAll(board);

	res = RecKnightsTour(board, ret_path, x_begin,
		 y_begin, path_length, heap_pq_min);

	 if (res)
	 {
		printf("Solution found!\n");
		/*PrintBoard(ret_path);*/
	 }
	else
	{
		printf("No solution found!\n");
	}

	HeapPQueueDestroy(heap_pq_min);
	heap_pq_min = NULL;	

	return res;
}

static op_result_t RecKnightsTour(bit_arr_t board,position_t *ret_path,
	 uint8_t x_begin,uint8_t y_begin,
	  uint8_t path_length, heap_pq_t* heap_pq_min )
{
	uint8_t x_next = 0, y_next = 0, move_index = 0, move_index2 = 0,
	 			temp_length = path_length + 1 ;
	bit_arr_t bit_set_on = 0, bit_set_off = 0;			
	 /*mx_next = 0, my_next = 0, count = 0,  move_index2 = 0,*/
	int degree = 0;
	knights_tour_t mange_tour = { 0 };
	knights_tour_t *temp_mange_tour = NULL;
	
	op_result_t result = FALSE;
	/*temp_mange_tour = &mange_tour;*/

	printf("temp_length = %u, \n",temp_length );
	printf("{ x_begin , y_begin } = {%d, %d} \n", x_begin, y_begin );

	printf(" board_before_SetOn = %#lx \n", board);
	printf(" x_begin +( COLUMN_SIZE * y_begin ) = %d \n",
		x_begin +( COLUMN_SIZE * y_begin ) );

	printf(" (x_begin +( COLUMN_SIZE * y_begin ) mode BOARD_SIZE = %d \n",
		(x_begin +( COLUMN_SIZE * y_begin ) ) % BOARD_SIZE);

	bit_set_on = BitArrSetOn(board, 
	        ( x_begin +( COLUMN_SIZE * y_begin )) % BOARD_SIZE) ;
	board = bit_set_on;
	printf(" BitArrSetOn = %#lx \n", bit_set_on);
	printf(" BitArrSetOn_board = %#lx \n", board);

	/*
	HeapPQueueDestroy(heap_pq_degrees);
	heap_pq_degrees = NULL;
	*/

	if(2 == temp_length ) /* BOARD_SIZE == temp_length */
	{
		return TRUE;
	}

	
	for(move_index2 = 0; move_index2 < KNIGHT_MOVE_NUM; ++move_index2 )
	{
		printf("move_index2 = %u \n",move_index2 );
		/*Check all possible moves */ 
		for(move_index = 0; move_index < KNIGHT_MOVE_NUM; ++move_index)
		{
			/* Next moves */
			printf("move_index = %u \n",move_index );

			x_next = x_begin + lut_knight_moves[move_index][0];
			y_next = y_begin + lut_knight_moves[move_index][1];
			printf("{ x_next , y_next } = {%d, %d} \n", x_next, y_next );
	
			if( !IsLegal(x_next, y_next, board) )
			{
			printf("NOT_LEGAL = { x_next , y_next } = {%d, %d} \n", x_next, y_next );

				continue;
			}
			printf("LEGAL = { x_next , y_next } = {%d, %d} \n", x_next, y_next );

			/*degree = Degree(x_next, y_next, board, ret_path );*/
			degree = Degree(x_next, y_next, board, mange_tour.ret_path[move_index]);

			if( 0 != degree )
			{
				printf("degree = %d \n ", degree);

				mange_tour.degree = degree;
				mange_tour.current_move = move_index2;
				mange_tour.ret_path[move_index]; /*  = ret_path */		 

				puts("1\n");
				HeapPQueueEnqueue(heap_pq_min, &mange_tour); /* &degree*/
				puts("2\n");

				
				printf("HeapPQueueSize(heap_pq_min) = %lu \n",
						 HeapPQueueSize(heap_pq_min) );
				printf("mange_tour.ret_path = %p \n",  \
						 (void*)(mange_tour.ret_path[move_index]));

						 /*
						 printf("{ mange_tour->ret_path->x , \
							mange_tour->ret_path->y } = {%d, %d} \n", \
						   mange_tour.ret_path->x, mange_tour.ret_path->y );
						   */		 
						 
			}

			puts("3\n");

		}
		puts("4\n");

		if(! HeapPQueueIsEmpty(heap_pq_min ) )
			{
				puts("5\n");

				temp_mange_tour = (knights_tour_t*)HeapPQueueDequeue(heap_pq_min);
				/*printf("{ temp_mange_tour->ret_path->x , \
					 temp_mange_tour->ret_path->y } = {%d, %d} \n", \
					mange_tour.ret_path->x, mange_tour.ret_path->y );*/
					puts("6\n");

					/*
					ret_path->x = temp_mange_tour->ret_path->x;
					ret_path->y = temp_mange_tour->ret_path->y;
					*/
				/*BitArrSetOn(board, ( x_begin * COLUMN_SIZE + y_begin ) % BOARD_SIZE ) ;*/
				printf("board_after_loop1 = %lu \n", board);

				result = RecKnightsTour(board, ret_path + 1,
					ret_path->x, ret_path->y, path_length + 1, heap_pq_min );
					puts("7\n");

				if(TRUE == result )
				{
					return TRUE;
				}/*			 
				else if(! HeapPQueueIsEmpty(heap_pq_min ) ) 
				{
					puts("HeapPQueueDequeue");
					HeapPQueueDequeue(heap_pq_min);
				}
				*/
			}

	}	

	bit_set_off = BitArrSetOff(board, ( x_begin + ( COLUMN_SIZE * y_begin ) ) % BOARD_SIZE) ;
	board = bit_set_off;

	printf(" BitArrSetOff = %#lx \n", bit_set_off);
	printf(" BitArrSetOff_board = %#lx \n", board);
	return FALSE;

}	
	
/************************************************************/
/*************  Static Functions definition  ****************/
/************************************************************/


/************************************************************/
/*************************  InBoard**************************/
/************************************************************/
op_result_t InBoard( uint8_t x, uint8_t y )
{
	return  0 <= (x * COLUMN_SIZE + y )&&
				(x * COLUMN_SIZE + y) < BOARD_SIZE ;
}

/************************************************************/
/********************  IsLegal**********************/
/************************************************************/


op_result_t IsLegal(uint8_t x, uint8_t y, bit_arr_t board)
{
	return InBoard(x, y) &&
		 ( UN_VISITED == BitArrGetVal( board,
					 (x * COLUMN_SIZE + y )% BOARD_SIZE) );
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

	if( 0 != degree )
	{
		ret_path->x = x_begin % BOARD_SIZE;
		ret_path->y = y_begin % BOARD_SIZE;

		 /*
			printf("{ ret_path->x , \
			ret_path->y } = {%d, %d} \n", \
			ret_path->x, ret_path->y );
		*/	
			
	}
	return degree;
}

/************************************************************/
/********************  SortingFunc**********************/
/************************************************************/
/*
static int SortingFunc(void* check_data ,void* new_data, void* param)
{
	UNUSED(param);
	return (-1) * ((( (knights_tour_t*)check_data)->degree) -
							 (((knights_tour_t*)new_data)->degree) );
}
 */
/* *(int*) */

#ifdef PRINTS

void PrintBoard(position_t *ret_path)
{
	size_t index = 0 ;

	printf("return_path[] = \n" );

	while( index < BOARD_SIZE )
	{
		printf("index = %ld \n", index);
		printf("x = %d, y = %d \n", ret_path->x, ret_path->y );
		++index;
	}
}

#endif

/************************************************************/
/********** End Of Static Functions definition  *************/
/************************************************************/


	

