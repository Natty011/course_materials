/***************************************
* Author : Natty
* Reviewer : Michael
* Date : 16 / 12 / 2024
* Last update: 16 / 12 / 2024
*****************************************/

#include <stdio.h> 		/*  puts,  */
#include "slist_exercises.h"



/***************************function declaration**************************/
static void TestHasLoop(void);
static void TestFlip(void);
static void TestFindIntersection(void);
/***************************End of function declaration******************/

int main ()
{

	puts("=====================================================");
    puts("'TestHasLoop()'");
    TestHasLoop();
    puts("=====================================================");
    
    puts("'TestFlip()'");
    TestFlip();
    puts("=====================================================");
  
  	puts("'TestFindIntersection()'");
    TestFindIntersection();
    puts("=====================================================");
  
     
return 0;
}

static void TestHasLoop(void)
{

	int arr[6] = {0, 1, 2, 3, 4, 5};

	node_t n1, n2, n3, n4, n5;  
	node_t* head = &n1;
	
	n1.data = &arr[1];
	n1.next = &n2;
	n2.data = &arr[2];
	n2.next = &n3;
	n3.data = &arr[3];
	n3.next = &n4;
	n4.data = &arr[5];
	n4.next = &n5;
	n5.data = &arr[6];
	n5.next = &n2;
	
	if(!HasLoop(head))
	{

		puts(" HasLoop Failed");			

	}
	
	n5.next = NULL;
	
	if(!HasLoop(head))
	{
		puts(" Head Has Loop");			
	}

	puts(" HasLoop Successed");		
}

static void TestFlip(void)
{

	int arr[6] = {0, 1, 2, 3, 4, 5};
	int i = 0 ;
	node_t n0, n1, n2, n3, n4, n5;  
	node_t* head = &n0;
	node_t* new_head = NULL;
	
	n0.data = &arr[0];
	n0.next = &n1;
	n1.data = &arr[1];
	n1.next = &n2;
	n2.data = &arr[2];
	n2.next = &n3;
	n3.data = &arr[3];
	n3.next = &n4;
	n4.data = &arr[4];
	n4.next = &n5;
	n5.data = &arr[5];
	n5.next = NULL;

	new_head = Flip(head);
	
	if(&n5 != new_head)
	{
		puts("TestFlip Failed");			
	}
	
	for(i = 5; i>=0 ; --i)
	{
		if(*(int*)(new_head->data) != i)
		{
			printf("TestFlip Failed in %d \n ", i);	
		}
		
		new_head = new_head -> next;
	}
	
	puts(" TestFlip Successed");		
}
	
static void TestFindIntersection(void)
{

	int arr[6] = {0, 1, 2, 3, 4, 5};

	node_t n0, n1, n2, n3, n4, n5;  
	node_t* head1 = &n1;
	node_t* head2 = &n3;
	node_t* new_head = NULL;
	
	n0.data = &arr[0];
	n0.next = NULL;
		
	n1.data = &arr[1];
	n1.next = &n2;
	n2.data = &arr[2];
	n2.next = &n3;
	n3.data = &arr[4];
	n3.next = &n4;
	n4.data = &arr[5];
	n4.next = &n5;
	n5.data = &arr[6];
	n5.next = NULL;

	new_head = FindIntersection(head1, head2);
	
	if(&n3 != new_head)
	{
		puts("FindIntersection Failed: with intersect case");			
	}
	
	head2 = &n0;
	new_head = FindIntersection(head1, head2);
	
	if(NULL != new_head)
	{
		puts("FindIntersection Failed: without intersect case");			
	}

	puts(" FindIntersection Successed");		
}	
	
	
	



