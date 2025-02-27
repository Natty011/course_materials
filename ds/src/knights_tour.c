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

typedef struct position_degree
{
	int degree_pos;

	uint8_t move_next;

}position_degree_t;

/******************************************************************************/
/***************************** Management struct ******************************/


/******************************************************************************/
/************************ static functions declartions ************************/
/******************************************************************************/
op_result_t InBoard( uint8_t x, uint8_t y );
op_result_t IsLegal(uint8_t x, uint8_t y, bit_arr_t board);
uint8_t Degree( uint8_t x_begin, uint8_t y_begin,
				 bit_arr_t board); 
static op_result_t
 RecKnightsTour(bit_arr_t board,position_t *ret_path,
				uint8_t x_begin,uint8_t y_begin,
			 		uint8_t path_length, heap_pq_t* heap_pq_min,
					 position_degree_t *adjacent_ret_path, int board_mat[8][8]);

static int
SortingFunc(void* check_data ,void* new_data, void* param);

#ifdef PRINTS
	void PrintBoard(position_t *ret_path);
	void PrintBoardMat( int board_mat[8][8]);
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
	position_degree_t *adjacent_ret_path = NULL;

	heap_pq_t *heap_pq_min = NULL;
	position_t *ret_path_handler = ret_path;

	int board_mat[8][8] = { 0 };

	heap_pq_min = HeapPQueueCreate(SortingFunc);
	
	if(! heap_pq_min )
	{
		printf("line: %d \n" , __LINE__ );
		puts("Failes in_1: Create - Allocation");
		return FALSE;
	}

	adjacent_ret_path = 
		(position_degree_t*)calloc(KNIGHT_MOVE_NUM, sizeof(position_degree_t) );

	if (NULL == adjacent_ret_path )
	 {
		HeapPQueueDestroy(heap_pq_min);
		heap_pq_min = NULL;	

		printf("line: %d \n" , __LINE__ );	
		printf("Memory allocation failed!\n");
		return FALSE;
		
	 }


	board = BitArrResetAll(board);
	/*
	ret_path->x = x_begin;
	ret_path->y = x_begin;
	*/
	printf("{ x_begin , x_begin } = {%d, %d} \n", x_begin, x_begin );

	res = RecKnightsTour(board, ret_path_handler, x_begin,
		 y_begin, path_length, heap_pq_min, adjacent_ret_path,
		 	 board_mat );

	 if (res)
	 {
		printf("Solution found!\n");
		PrintBoardMat(board_mat);
	 }
	else
	{
		printf("No solution found!\n");
	}

	HeapPQueueDestroy(heap_pq_min);
	heap_pq_min = NULL;	

	free( adjacent_ret_path );
	adjacent_ret_path = NULL;

	return res;
}

/************************************************************/
/********************  RecKnightsTour  *************************/
/************************************************************/

static op_result_t RecKnightsTour(bit_arr_t board, position_t *ret_path_handler,
			 uint8_t x_begin,uint8_t y_begin, uint8_t path_length,
		 	 heap_pq_t* heap_pq_min, position_degree_t *adjacent_ret_path,
			  int board_mat[8][8] )
{
	uint8_t x_next = 0, y_next = 0, move_index = 0, move_index2 = 0,
	 			temp_length = path_length + 1 ;
	bit_arr_t bit_set_on = 0, bit_set_off = 0;			
	 /*mx_next = 0, my_next = 0, count = 0,  move_index2 = 0,*/
	int degree = 0; /* , min = 9 */
	op_result_t result = FALSE;
	position_degree_t *neighbor = NULL;	
	board_mat[x_begin][y_begin] = temp_length;
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
	
	ret_path_handler->x = x_begin;
	ret_path_handler->y = y_begin;
	/*
	printf("{ ret_path_handler->x , ret_path_handler->y } = {%d, %d} \n", \
		ret_path_handler->x, ret_path_handler->y );
	*/					 
	if(2 == temp_length ) /* BOARD_SIZE == temp_length */
	{
		
		return TRUE;
	}

	
	for(move_index2 = 0; move_index2 < KNIGHT_MOVE_NUM; ++move_index2 )
	{
		/*HeapPQueueClear(heap_pq_min);*/
		printf("move_index2 = %u \n",move_index2 );
		/*Check all possible moves */ 
		for(move_index = 0; move_index < KNIGHT_MOVE_NUM; ++move_index)
		{
			/* Next moves */
			printf("move_index = %u \n",move_index );

			x_next = x_begin + lut_knight_moves[move_index][0];
			y_next = y_begin + lut_knight_moves[move_index][1];
	
			if( !IsLegal(x_next, y_next, board) )
			{
			printf("NOT_LEGAL = { x_next , y_next } = {%d, %d} \n", x_next, y_next );

				continue;
			}
			printf("LEGAL = { x_next , y_next } = {%d, %d} \n", x_next, y_next );

			degree = Degree(x_next, y_next, board );

			if( 0 != degree )
			{
				
				(adjacent_ret_path + move_index)->degree_pos = degree;
				(adjacent_ret_path + move_index)->move_next = move_index;
				
				printf("degree = %d \n ", degree);
				HeapPQueueEnqueue(heap_pq_min, adjacent_ret_path + move_index);

				printf("HeapPQueueSize(heap_pq_min) = %lu \n",
					HeapPQueueSize(heap_pq_min) );
		  		printf("(adjacent_ret_path + move_index)->degree_pos = %d \n",  \
					(adjacent_ret_path + move_index)->degree_pos);

				printf("(adjacent_ret_path + move_index)->move_next  = %d \n",  \
					(adjacent_ret_path + move_index)->move_next);


				/*	
					printf("{ temp_mange_tour->ret_path->x , \
					 temp_mange_tour->ret_path->y } = {%d, %d} \n", \
					mange_tour.ret_path->x, mange_tour.ret_path->y );
				*/
					
					/*
					printf("{ mange_tour->ret_path->x , \
					   mange_tour->ret_path->y } = {%d, %d} \n", \
					  mange_tour.ret_path->x, mange_tour.ret_path->y );
					  */		
			}
		}

			while(! HeapPQueueIsEmpty(heap_pq_min ) )
			{
				
			 neighbor = HeapPQueueDequeue(heap_pq_min);

			 x_next = x_begin + lut_knight_moves[neighbor->move_next][0];
			 y_next = y_begin + lut_knight_moves[neighbor->move_next][1];
			 			 
			 printf("{ x_next , y_next } = {%d, %d} \n", x_next, y_next );

				

				/*BitArrSetOn(board, ( x_begin * COLUMN_SIZE + y_begin ) % BOARD_SIZE ) ;*/
				printf("board_after_loop1 = %lx \n", board);

				result = RecKnightsTour(board, ret_path_handler + 2,
					x_next, y_next, path_length + 1,
							 heap_pq_min, adjacent_ret_path, board_mat );
					
				if(TRUE == result )
				{
		
					return TRUE;
				}
				/*
				board = BitArrSetOff(board, ( x_next + ( COLUMN_SIZE * y_next ) ) % BOARD_SIZE) ;
				*/
				/*
				else if(! HeapPQueueIsEmpty(heap_pq_min ) )
				{
					puts("HeapPQueueDequeue");
					HeapPQueueDequeue(heap_pq_min);
				}
				*/

			}
	}	
/*
	bit_set_off = BitArrSetOff(board, ( x_begin + ( COLUMN_SIZE * y_begin ) ) % BOARD_SIZE) ;
	board = bit_set_off;
*/
	printf(" BitArrSetOff = %#lx \n", bit_set_off);
	printf(" BitArrSetOff_board = %#lx \n", board);

	board_mat[x_begin][y_begin] = 0;

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
			 bit_arr_t board) /* , position_t *ret_path*/
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

/************************************************************/
/********************  SortingFunc**********************/
/************************************************************/
static int SortingFunc(void* check_data ,void* new_data, void* param)
{
	UNUSED(param);
	return (-1) * ((( (position_degree_t*)check_data)->degree_pos) -
							 (((position_degree_t*)new_data)->degree_pos) );
}


						
/* return (-1) * (*(int*)check_data - *(int*)new_data); */							 

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

void PrintBoardMat( int board_mat[8][8])
{
	size_t i = 0 ;
	size_t j = 0;

	for(i = 0; i < KNIGHT_MOVE_NUM ; ++i)
	{
		for(j = 0; j < KNIGHT_MOVE_NUM; ++j)
		{
			printf("%d ", board_mat[i][j]);
		}

		printf("\n");

	}
}

#endif

/************************************************************/
/********** End Of Static Functions definition  *************/
/************************************************************/


	

