/******************************************************************************
*Author: hadar
*Reviewer:  
*Date: 
*Version 1
******************************************************************************/
#include <stdio.h>            /*NULL, printf */
#include "slist_exercises.h" 
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void TastFlip();

void TastHasLoop();

void TastFindIntersection();
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int main(void)
{
	
	TastFlip();
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	
	TastHasLoop();
	
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	TastFindIntersection();
	return 0;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void TastFlip()
{
	int a = 0;
	int b = 5;
	int c = 10;
	int d = 15;
	node_t node1;
	node_t node2;
	node_t node3;
	node_t node4;
	node_t* head = &node1;
	
	node1.data = &a;
	node1.next = &node2;
	
	node2.data = &b;
	node2.next = &node3;
	
	node3.data = &c;
	node3.next = &node4;
	
	node4.data = &d;
	node4.next = NULL;
	
	printf("before Flip\n");
	printf("data head:%d \n", *(int*)(head->data));
	printf("data head one next:%d \n",*(int*)(head->next->data));
	printf("data head two next:%d \n",*(int*)(head->next->next->data));
	printf("data head three next:%d \n",*(int*)(head->next->next->next->data));
	
	head = Flip(head);
	
	printf("\nafter Flip\n");
	printf("data head:%d \n", *(int*)(head->data));
	printf("data head one next:%d \n",*(int*)(head->next->data));
	printf("data head two next:%d \n",*(int*)(head->next->next->data));
	printf("data head three next:%d \n",*(int*)(head->next->next->next->data));
	
	if (NULL != head->next)  /*  0 == HasLoop(head) */
	{
		printf("\ntest1 HasLoop success\n");
	}
	else
	{
		printf("\ntest1 HasLoop failed\n");
	}
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


void TastHasLoop()
{
	int a = 0;
	int b = 5;
	int c = 10;
	int d = 15;
	int e = 20;
	int f = 25;
	int g = 30;
	int h = 35;
	node_t node1;
	node_t node2;
	node_t node3;
	node_t node4;
	node_t node5;
	node_t node6;
	node_t node7;
	node_t node8;
	node_t* head = &node1;
	
	node1.data = &a;
	node1.next = &node2;
	
	node2.data = &b;
	node2.next = &node3;
	
	node3.data = &c;
	node3.next = &node4;
	
	node4.data = &d;
	node4.next = &node5;
	
	node5.data = &e;
	node5.next = &node6;
	
	node6.data = &f;
	node6.next = &node7;
	
	node7.data = &g;
	node7.next = &node8;
	
	node8.data = &h;
	node8.next = &node6;
	
	if (1 == HasLoop(head))
	{
		printf("test2 HasLoop success\n");
	}
	else
	{
		printf("test2 HasLoop failed\n");
	}
	
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void TastFindIntersection()
{
	int a = 0;
	int b = 5;
	int c = 10;
	int d = 15;
	int e = 20;
	int f = 25;
	int g = 30;
	int h = 35;
	node_t node1;
	node_t node2;
	node_t node3;
	node_t node4;
	node_t node5;
	node_t node6;
	node_t node7;
	node_t node8;
	node_t* head_1 = &node1;
	node_t* head_2 = &node5;
	
	node1.data = &a;
	node1.next = &node2;
	
	node2.data = &b;
	node2.next = &node3;
	
	node3.data = &c;
	node3.next = &node4;
	
	node4.data = &d;
	node4.next = NULL; /*end list1*/
	
	
	node5.data = &e;
	node5.next = &node6;
	
	node6.data = &f;
	node6.next = &node7;
	
	node7.data = &g;
	node7.next = &node8;
	
	node8.data = &h;
	node8.next = &node2; /*connected to node2*/
	
	if (head_1->next == FindIntersection(head_1, head_2))
	{
		printf("test1 FindIntersection success\n");
	}
	else
	{
		printf("test1 FindIntersection failed\n");
	}
	
	/*test2*/
	node1.data = &a;
	node1.next = &node2;
	
	node2.data = &b;
	node2.next = &node3;
	
	node3.data = &c;
	node3.next = &node4;
	
	node4.data = &d;
	node4.next = NULL; /*end list1*/
	
	
	node5.data = &e;
	node5.next = &node6;
	
	node6.data = &f;
	node6.next = &node7;
	
	node7.data = &g;
	node7.next = &node8;
	
	node8.data = &h;
	node8.next = NULL; /*end list1*/
	
	if (NULL == FindIntersection(head_1, head_2))
	{
		printf("test2 FindIntersection success\n");
	}
	else
	{
		printf("test2 FindIntersection failed\n");
	}
}


