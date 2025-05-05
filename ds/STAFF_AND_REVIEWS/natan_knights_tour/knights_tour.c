/******************************************************************************
*
*	Aouther:	Natan Yunger
*	Review:		
*	Date:		26/02/25
*
******************************************************************************/

#include <assert.h>		/* assert */
#include <string.h>		/* memset */
#include <stdio.h>
#include "knights_tour.h"
#include "bit_array.h"
#include "pqueue.h"

#define NUM_OF_MOVES				8
#define BOARD_LENGTH				8
#define BOARD_SIZE					64

#define IS_ON_BOARD(x, y)			(((x) >= 0) && ((x) < BOARD_LENGTH) &&\
											 ((y) >= 0) && ((y) < BOARD_LENGTH))
#define COORDS_TO_IDX(x, y)			((x) + BOARD_LENGTH * (y))
#define IDX_TO_X_COORD(p)			((p) % BOARD_LENGTH)
#define IDX_TO_Y_COORD(p)			((p) / BOARD_LENGTH)

enum
{
	X = 0,
	Y = 1
};

enum
{
	SUCCESS = 0,
	FAIL = 1
};

static char which_moves[NUM_OF_MOVES][2] = {{-2, -1}, {-1, -2}, {1, -2},
											 {2, -1}, {2, 1}, {1, 2}, {-1, 2},
									 								 {-2, 1}};
static char how_meny_moves[BOARD_SIZE] = {0};

static int RecMoveKnight(bit_arr_t board, position_t* ret_path,
											 pqueue_t* next_moves_pq, size_t index);
static void InitLut(char how_meny_moves[BOARD_SIZE]);

static int HasLessMoves(void* check_data, void* new_data);

void PrintBoard(uint8_t board[NUM_OF_MOVES][NUM_OF_MOVES],  position_t *ret_path);


int KnightsTour(uint8_t x, uint8_t y, position_t* ret_path)
{
	int res = SUCCESS, i = 0;
	size_t index = COORDS_TO_IDX(x, y);
	bit_arr_t board = BitArrResetAll(0);

	pqueue_t* next_moves_pq = PQueueCreate(HasLessMoves);
	if (!next_moves_pq)
	{
		return FAIL;
	}
	
	assert(ret_path);
	
	InitLut(how_meny_moves);
	
	res = RecMoveKnight(board, ret_path, next_moves_pq, index);

	PQueueDestroy(next_moves_pq);
	next_moves_pq = NULL;
	
	return res;
}

static void InitLut(char how_meny_moves[BOARD_SIZE])
{
	int i = 0, j = 0;
	
	memset(how_meny_moves, 0, BOARD_SIZE);
	
	for (i = 0; i < BOARD_SIZE; ++i)
	{
		for (j = 0; j < NUM_OF_MOVES; ++j)
		{
			how_meny_moves[i] +=
			 IS_ON_BOARD(IDX_TO_X_COORD(i) + which_moves[j][X],
			 							 IDX_TO_Y_COORD(i) + which_moves[j][Y]);
		}
	}
}

static int RecMoveKnight(bit_arr_t board, position_t* ret_path,
										 pqueue_t* next_moves_pq, size_t index)
{
	size_t i = 0;
	size_t neighbors[NUM_OF_MOVES] = {0};
	size_t size = 0;
	
	int res = FAIL;
	/* please call once to IDX_TO_X_COORD & IDX_TO_Y_COORD, and assign
		the results from x & y to ret_path */
	char x = IDX_TO_X_COORD(index);
	char y = IDX_TO_Y_COORD(index);
	
	ret_path->x = IDX_TO_X_COORD(index);
	ret_path->y = IDX_TO_Y_COORD(index);
	
	board = BitArrSetOn(board, index);
	
	/* stop condition: if all spots on board have been reached - return success. */
	if (!BitArrCountOff(board))
	{
		return SUCCESS;
	}
	
	PQueueClear(next_moves_pq);
	
	for (i = 0; i < NUM_OF_MOVES; ++i)
	{
		/* valid movess that have not yet been visited, are inserted to a
			priority queue, which sortes them by least next moves availible.  */
		if (IS_ON_BOARD(x + which_moves[i][X], y + which_moves[i][Y]))
		{
			neighbors[size] =
					 COORDS_TO_IDX(x + which_moves[i][X], y + which_moves[i][Y]);
			
			if (BitArrGetVal(board, neighbors[size]))
			{
				continue;
			}
			
			--how_meny_moves[neighbors[size]];
			
			if (PQueueEnqueue(next_moves_pq, neighbors + size))
			{
				return FAIL;
			}
			
			++size;
		}
	}
	
	while (size)
	{
		res = RecMoveKnight(board, ret_path + 1, next_moves_pq,
										 *(size_t*)PQueuePeek(next_moves_pq)); 
		/* if function succeeded, return success to caller frame. */
		if (!res)
		{
			return SUCCESS;
		}
		
		/* otherwise, refill the queue, and go to next "branch". */
		for (i = 0; i < size; ++i)
		{
			if (PQueueEnqueue(next_moves_pq, neighbors + i))
			{
				return FAIL;
			}
		}
		
		PQueueDequeue(next_moves_pq);
		--size;
	}
	
	/* if size is 0, the function either reached the end of the board, and 
		returns success, or reached a deadend, returns fail, and backtracks. */
	board = BitArrSetOff(board, index);
	return res;
}

/* compare function used in pqueue: */
static int HasLessMoves(void* check_data, void* new_data)
{
	return (int)(how_meny_moves[*(size_t*)check_data] -
											 how_meny_moves[*(size_t*)new_data]);
}



	



























