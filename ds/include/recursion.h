/******************************************************************************
*	Version 0.5
*   5/2/25          15:18
******************************************************************************/
#ifndef __RECURSION_H__		/* __RECURSION_H__	*/
#define __RECURSION_H__		/* __RECURSION_H__	*/

#include <stddef.h>			/* size_t			*/
#include "stack.h"          /*stack_t*/

typedef struct node
{
	struct node *next;
	void* data;
} node_t;

/******************************************************************************
*
*       Description: Get a number from the Fibonacci sequence
*       Arguments: 'element_index' - Index of the number in the sequence
*       Return: The 'element_index'th number in the Fibonacci sequence
*       Notes: The first two numbers (indexes 0 and 1) should return 1
* 
*/      int Fibonacci(int element_index);
/*
******************************************************************************/

/******************************************************************************
*
*       Description: Flips a singly linked list
*       Arguments: 'node' - Head of the list
*       Return: New head of the flipped linked list
*       Notes:
* 
*/      node_t *FlipList(node_t *node);
/*
******************************************************************************/

/******************************************************************************
*
*       Description:
*       Arguments:
*       Return:
*       Notes:
* 
*/       void SortIntegers(stack_t* stack);
/*
******************************************************************************/

/******************************************************************************
*
*       Description:
*       Arguments:
*       Return:
*       Notes:
* 
*/      size_t StrLen(const char *s);
/*
******************************************************************************/

/******************************************************************************
*
*       Description:
*       Arguments:
*       Return:
*       Notes:
* 
*/      int StrCmp(const char *s1, const char *s2);
/*
******************************************************************************/

/******************************************************************************
*
*       Description:
*       Arguments:
*       Return:
*       Notes:
* 
*/      char *StrCpy(char *dest, const char *src);
/*
******************************************************************************/

/******************************************************************************
*
*       Description:
*       Arguments:
*       Return:
*       Notes:
* 
*/      char *StrCat(char *dest, const char *src);
/*
******************************************************************************/

/******************************************************************************
*
*       Description:
*       Arguments:
*       Return:
*       Notes:
* 
*/      char *StrStr(const char *haystack, const char *needle);
/*
******************************************************************************/

#endif					    /* __RECURSION_H__	*/
