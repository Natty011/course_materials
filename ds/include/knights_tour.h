/******************************************************************************
*	Version 1.0
*   Last Updated:   26/02/25
*                   14:20
******************************************************************************/
#ifndef __KNIGHTS_TOUR_H__		/* __KNIGHTS_TOUR_H__      */
#define __KNIGHTS_TOUR_H__		/* __KNIGHTS_TOUR_H__      */

#include <stdint.h>             /* uint8_t                 */
#include "pqueue.h"

typedef struct position
{
    uint8_t x;
    uint8_t y;

} position_t;

/******************************************************************************
*
*       Description: Solve the Knight's Tour Problem
*       Arguments: * 'x', 'y' - Coordinates
*                  * 'ret_path' - Path the knight took
*       Return: SUCCESS (0) on succes, FAILURE (1) on solution time-out
*       Notes: The path is returned through 'ret_path' which is a 2D array
*              representation of the chess-board with every cell storing the
*              step number of the knight after landing on the tile starting
*              from step '0'.
*              The function times out after 5 minutes of run-time.
* 
*/      int KnightsTour(uint8_t x, uint8_t y, position_t *ret_path);
/*
******************************************************************************/

#endif                          /* __KNIGHTS_TOUR_H__      */

/*
#ifdef PRINTS
    void PrintBoard(uint8_t board[8][8],  position_t *ret_path);

#endif
*/