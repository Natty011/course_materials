/******************************************************************************
*	Version 1.0
******************************************************************************/
#ifndef __SLIST_EXCERCISES_H__       /* __SLIST__EXCERCISES_H__ */
#define __SLIST__EXCERCISES_H__      /* __SLIST_EXCERCISES_H__ */

#include <stddef.h>             /* size_t */

typedef struct node
{
	
	void* data;
	struct node *next;
	
}node_t;

/* Reverses the order of a given slist. */
node_t *Flip(node_t *head);

/* Tell whether a given slist has loop. */
int HasLoop(const node_t *head);

/* Returns a pointer to a first node mutual to both slists, if any. */
node_t *FindIntersection(node_t *head_1, node_t *head_2); 


#endif                          /* __SLIST__EXCERCISES_H__ */
