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

#include "pqueue.h"

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
	bit_arr_t visited = 0;
	uint8_t path_length = 0; 
	int i = 0, j = 0;
	op_result_t res = FALSE;
	pqueue_t *pq = PQueueCreate(SortingFunc);
    uint8_t board[COLUMN_SIZE][COLUMN_SIZE] = { 0 };


	visited = BitArrResetAll(visited);
	res = RecKnightsTour( x_begin, y_begin, path_length, visited, ret_path, pq);

	 if (res)
	 {
		printf("Solution found!\n");
		
		for (i = 0; i < BOARD_SIZE ; i++)
		{
         /** 
	printf("{ ret_path[i].x , ret_path[i].y } \
		 = {%d, %d} \n", ret_path[i].x = x_begin, ret_path[i].y );
	*/
			board[ret_path[i].x][ret_path[i].y] = i;
        }
        
        for (i = 0; i < COLUMN_SIZE; i++) 
		{
            for (j = 0; j < COLUMN_SIZE; j++) 
			{
                printf("%2d ", board[i][j]);
            }
            printf("\n");
        }

		/*PrintBoard(ret_path);*/
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
	size_t size = 0, i =0 ;
	int temp_degree = 0;
	/*position_t next_move = { 0 };*/
	position_degree_t next_move_temp = { 0 }; 
	op_result_t result = FALSE;
	position_degree_t next_move[8] = { 0 };


	ret_path[path_length].x = x_begin;
    ret_path[path_length].y = y_begin;
	
	printf("{ ret_path[path_length].x , ret_path[path_length].y } \
		 = {%d, %d} \n", ret_path[path_length].x = x_begin, ret_path[path_length].y );
	
	visited = BitArrSetOn(visited, ( x_begin * COLUMN_SIZE )  +  y_begin ) ;
	PQueueClear(pq);
	if( BOARD_LIMIT == path_length ) /*BOARD_LIMIT */
	{
		return TRUE;
	}

		for(move_index = 0; move_index < KNIGHT_MOVE_NUM; ++move_index)
		{

			x_next = x_begin + lut_knight_moves[move_index][0];
			y_next = y_begin + lut_knight_moves[move_index][1];
			/*printf("{ x_next , y_next } = {%d, %}d \n", x_next, y_next );*/

			if( !IsLegalMove(x_next, y_next, visited) )
			{
				continue;
			}

			if( 62 == path_length)
			{
				next_move[move_index].neibour.x =  x_next;
			next_move[move_index].neibour.y =  y_next;
			next_move[move_index].degree = Degree(x_next, y_next, visited );
				result = RecKnightsTour( x_next,
					y_next, path_length + 1,
						 visited, ret_path, pq);
				
				if(TRUE == result )
				{
					return TRUE;
				 }		 
			}

			printf("{ x_next , y_next } = {%d, %d} \n", x_next, y_next );

			
			temp_degree = Degree(x_next, y_next, visited );
			printf("PQueueSize11111(pq) {%ld} \n", PQueueSize(pq) );
			printf("move_index = %u \n",move_index);
			if( 0 != temp_degree )
			{
			printf("{ x_next11 , y_next11 } = {%d, %d} \n", x_next, y_next );
			next_move[move_index].degree = Degree(x_next, y_next, visited );
			next_move[move_index].neibour.x =  x_next;
			next_move[move_index].neibour.y =  y_next;
			next_move[move_index].move_index = move_index;	
			next_move_temp = *(position_degree_t*)PQueuePeek(pq);
			printf("{  next_move_temp.degree111 } = {%d} \n", next_move_temp.degree );
			printf("{  next_move_temp.neibour.x111 } = {%d} \n", next_move_temp.neibour.x );
			printf("{  next_move_temp.neibour.y111 } = {%d} \n", next_move_temp.neibour.y );

				printf("degree = %d \n ", next_move[move_index].degree);
			
				PQueueEnqueue(pq, next_move + move_index);
				/*printf("PQueueSize11(pq) {%ld} \n", PQueueSize(pq) );*/

				++size;
				printf("next_move[move_index].move_index = %u \n",
					next_move[move_index].move_index);
			}
			/*
		next_move_temp = *(position_degree_t*)PQueuePeek(pq);
		printf("{  next_move_temp.degree } = {%d} \n", next_move_temp.degree );
		printf("{  next_move_temp.neibour.x } = {%d} \n", next_move_temp.neibour.x );
		printf("{  next_move_temp.neibour.y } = {%d} \n", next_move_temp.neibour.y );
		*/		
		}
		
		printf("size) {%ld} \n", size );
		while ( size ) /* !PQueueIsEmpty(pq) */
			{
				position_degree_t *next_move_p = NULL;
				/*next_move_p = (position_degree_t *)PQueueDequeue(pq);*/
				

				next_move_p = (position_degree_t *)PQueuePeek(pq);
				min = next_move_p->move_index;
				/*printf("PQueueSize(pq) {%ld} \n", PQueueSize(pq) );*/
				/*
				if( !IsLegalMove(next_move_p->neibour.x, next_move_p->neibour.y, visited) )
				{
					PQueueDequeue(pq);
					--size;
					continue;
				}
					*/
				/*if( size == 0) break;*/
				/*
				next_move_temp = *(position_degree_t*)PQueuePeek(pq);
			printf("{  next_move_temp.degree111 } = {%d} \n", next_move_temp.degree );
			printf("{  next_move_temp.neibour.x111 } = {%d} \n", next_move_temp.neibour.x );
			printf("{  next_move_temp.neibour.y111 } = {%d} \n", next_move_temp.neibour.y );
			*/
				result = RecKnightsTour( next_move_p->neibour.x,
					 next_move_p->neibour.y, path_length + 1,
					 	 visited, ret_path, pq);
/*
				if( !IsLegalMove(x_next, y_next, visited) )
				{
						continue;
				}	
						*/	 
				if(TRUE == result )
				{
					return TRUE;
				}
				visited = BitArrSetOff(visited, ( next_move_p->neibour.x * COLUMN_SIZE )
							  +   next_move_p->neibour.y) ;
				--size;
				PQueueClear(pq);

				/*PQueueDequeue(pq);*/
				if(size > 0 )
				{
					for(move_index = 0; move_index < 8; ++move_index)
					{
						if( ( min != move_index)  && 0 != next_move[move_index].degree )
						{
							PQueueEnqueue(pq, next_move + move_index);
						}
					}
				}	
				/*next_move_p = (position_degree_t *)PQueueDequeue(pq);*/
				/*
				if( !IsLegalMove(next_move_p->neibour.x, next_move_p->neibour.y, visited) )
				{
						continue;
				}	
*/
				/*PQueueClear(pq);*/

				
			
			

			 
				
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
	return  (0 <= x  &&  x < COLUMN_SIZE ) &&
			(0 <= y  &&  y < COLUMN_SIZE ) ;
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
	/*
	printf("(position_degree_t*)check_data)->degree) = {%d} \n", \
		((position_degree_t*)check_data)->degree );
	printf("(position_degree_t*)new_data)->degree) = {%d} \n", \
		((position_degree_t*)new_data)->degree );
*/
	return  ((( (position_degree_t*)check_data)->degree) -
							 (((position_degree_t*)new_data)->degree) );
	
	
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

#endif

/************************************************************/
/********** End Of Static Functions definition  *************/
/************************************************************/


	

