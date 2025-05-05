/***************************************
* Author : Natty
* Reviewer : Michael
* Date : 15 / 12 / 2024
* Last update: 16 / 12 / 2024
*****************************************/


#include <assert.h> 	/* assert */
#include <stdlib.h> 	/* malloc, free, realloc*/
#include "slist_exercises.h"

#define MAX(a, b)  (((a) > (b)) ? (a) : (b)) 


/******************* HasLoop *********************/

/* The fast pointer is faster then slow pointer(x2), So if there is a loop
   the fast pointer eventually will reach/meet the slow pointer, 
   otherwise there there is not loop  */ 

int HasLoop(const node_t *head)
{
	const node_t* fast = head;
	const node_t* slow = head;
	
	while(NULL != fast && NULL != fast->next)
	{
		fast = fast->next->next;
		slow = slow->next;
		
		if( fast == slow )
		{
			return 1;
		}
	}	
	
	return 0;
	
}


/******************* Flip *********************/
/* Flip the next of each node to point to the previous node */
node_t *Flip(node_t *head)
{

	node_t* NextNode = NULL;
	node_t* PrevNode = NULL;
	
	while(head)
	{
		
		NextNode = head->next;
		head->next = PrevNode;
		PrevNode = head;
		head = NextNode;
	}
	
	return PrevNode;
}

/******************* FindIntersection *********************/
node_t *FindIntersection(node_t *head_1, node_t *head_2)
{
	node_t* head1 = head_1;
	node_t* head2 = head_2;
	int len1 = 0;
	int len2 = 0;
	
	size_t move1 = 0;
	size_t move2 = 0;
	
	assert(head_1->next);
	assert(head_2->next);
	
	while(NULL != head1->next)
	{
		len1 += 1;
		head1 = head1->next;	
	}
	
	while(NULL != head2->next)
	{
		len2 += 1;
		head2 = head2->next; 	
	}
	/* If tails of both lists are different then return NULL */


	if( head1 != head2)
	{
		return NULL;
	}
	
	move1 = MAX(0 , len1 - len2);
	move2 = MAX(0 , len2 - len1);

	/* Head pointer of the longer list is moved to next till
	 length of both lists become equal*/ 

	while( move1 > 0)
	{
		head_1 = head_1->next;
		--move1;	
	}
	
	while( move2 > 0)
	{
		head_2 = head_2->next;
		--move2;	
	}
	
	while( head_1 != head_2 )
	{
		head_1 = head_1->next;
		head_2 = head_2->next;
	}
	
	return head_1;
	
}





 
