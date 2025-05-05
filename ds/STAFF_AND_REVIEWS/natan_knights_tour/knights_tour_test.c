/******************************************************************************
*
*	Aouther:	Natan Yunger
*	Review:		
*	Date:		
*
******************************************************************************/

#include <stdio.h>		/* printf */
#include <stdlib.h>		/* malloc, free */

#include "knights_tour.h"

#define RED_BKG		"\033[0;31m\033[7m"
#define GRN_BKG		"\033[0;92m\033[7m"
#define PRPL		"\033[0;95m"
#define ITLC		"\033[3m"
#define NRML		"\033[0m"

#define BOARD_LENGTH				8
#define BOARD_SIZE					64

#define COORDS_TO_IDX(x, y)			((x) + BOARD_LENGTH * (y))

int TestKnightsTour(void);
#ifndef NDEBUG
	void PrintKnightsTour(void);
#endif

static int HasDuplicates(position_t* tour);
void PrintBoard(uint8_t board[BOARD_LENGTH][BOARD_LENGTH],  position_t *ret_path);
int main()
{
	int failure = 0;
	
	char* mode = NRML;
	#ifndef NDEBUG
		mode = PRPL;
	#endif
	
	printf("%s", mode);
	
	failure += (TestKnightsTour() &&
							 printf("KnightsTour "RED_BKG"failed!\n%s", mode));
	#ifndef NDEBUG
		PrintKnightsTour();
	#endif
	
	if (!failure)
	{
		printf("KnightsTour "GRN_BKG"succeeded!\n");
	}
	printf(NRML);
	



	return 0;
}

int TestKnightsTour(void)
{
	int res = 0;
	size_t x = 0, y = 0;
	
	position_t tour[BOARD_SIZE] = {0};
	uint8_t board_11[BOARD_LENGTH][BOARD_LENGTH] = { 0 };

	for	(x = 0; x < 4; ++x)
	{
		for (y = x; y < 4; ++y)
		{
			res += KnightsTour(x, y, tour);
			res += HasDuplicates(tour);
		}
	}
	

	

	PrintBoard(board_11, tour );
	return res;
}

#ifndef NDEBUG
	void PrintKnightsTour(void)
	{
		size_t i = 0;
		int x = 0, y = 0;
		size_t counter = 0;
		position_t tour[64] = {0};
		
		size_t board[BOARD_SIZE] = {0};
		
		printf("Enter x coordinate:\t");
		scanf("%d", &x);
		
		printf("Enter y coordinate:\t");
		scanf("%d", &y);
		
		KnightsTour(x, y, tour);
		
		for (i = 0; i < BOARD_SIZE; ++i)
		{
			board[COORDS_TO_IDX(tour[i].x, tour[i].y)] = i;
		}
		
		printf("\nPath starting at (%d, %d):\n\n", x, y); 
		
		for (i = 0; i < 64; ++i)
		{
			printf("%lu%s",
					 board[i], (7 == (counter % BOARD_LENGTH)) ? "\n\n" : "\t");
			++counter;
		}
	}
#endif

static int HasDuplicates(position_t* tour)
{
	size_t i = 0;
	size_t res = 0;
	
	for (i = 0; i < BOARD_SIZE; ++i)
	{
		res += COORDS_TO_IDX(tour[i].x, tour[i].y);
		res -= i;
	}
	return res;
}



void PrintBoard(uint8_t board[BOARD_LENGTH][BOARD_LENGTH],  position_t *ret_path)
	{
		int i = 0, j = 0;
		size_t sum = 0; /*total sum 2016*/
		uint8_t x = 0, y = 0;
		uint8_t not_solvable_count = 0;

		for (i = 0; i < BOARD_SIZE ; i++)
		{
         
			board[ret_path[i].x][ret_path[i].y] = i;
			/*
			printf(" ret_path[i].x, ret_path[i].y = { %u,%u } \n"
				,ret_path[i].x, ret_path[i].y );
				*/

        }
        
        for (i = 0; i < BOARD_LENGTH; i++) 
		{
            for (j = 0; j < BOARD_LENGTH; j++) 
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
		printf("sum = %lu \n", sum);



		printf("Checking solvability for all positions...\n");

    for (x = 0; x < BOARD_LENGTH; x++) {
        for (y = 0; y < BOARD_LENGTH; y++) {
            if (KnightsTour(x, y, ret_path) != 0) {
                printf("No solution starting at (%d, %d)\n", x, y);
                not_solvable_count++;
            }

			/*PrintBoard(board_11, ret_path);*/
        }
    }

    if (not_solvable_count == 0) {
        printf("All positions are solvable.\n");
    } else {
        printf("%d positions are not solvable.\n", not_solvable_count);
    }
	

	}





















