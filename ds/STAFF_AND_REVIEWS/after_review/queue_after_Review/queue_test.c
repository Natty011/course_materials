/***************************************
* Author : Natty
* Reviewer : Chen
* Date : 15 / 12 / 2024
* Last update: 15 / 12 / 2024
*****************************************/

#include <stdio.h> 		/* printf, puts,  */
#include <string.h> 	/* strcpy, strcmp */
#include "queue.h"
#include "slist.h" 



/***************************function declaration**************************/
static void TestString(void);
/***************************End of function declaration******************/

int main ()
{

	puts("=====================================================");
    puts("'TestString()'");
    TestString();
    puts("=====================================================");
     
return 0;
}

static void TestString(void)
{

	size_t i = 0;
	int res = 0;
	char* arr[4] = {"blabla", "Natty", "Hello", "World" };
	
	queue_t* Q1 = QCreate();
	queue_t* Q2 = QCreate();
	

	if(QSize(Q1) != 0 || !QIsEmpty(Q1) )
	{
		puts("Failes in TestString: QPeek & QSize & QIsEmpty");
	}
	
	if(QSize(Q2) != 0 || !QIsEmpty(Q2) )
	{
		puts("Failes in TestString: QPeek & QSize & QIsEmpty");
	}
	
	res = QEnqueue(Q1, arr[0]);
	
	if( QIsEmpty(Q1)  || QSize(Q1) != 1 || res ||
		strcmp((char*)QPeek(Q1), (char*)arr[0]))
	{
		puts("Failes in TestString: QIsEmpty & QSize & QPeek & QEnqueue");
	}
	
	QDequeue(Q1);
	
	if( !QIsEmpty(Q1)  || QSize(Q1) != 0)
	{
		puts("Failes in TestString: IsEmpty & QSize & QDequeue");
	}
	
	res = QEnqueue(Q2, arr[0]);
	
	if( QIsEmpty(Q2)  || QSize(Q2) != 1 || res ||
		strcmp((char*)QPeek(Q2), (char*)arr[0]))
	{
		puts("Failes in TestString: QIsEmpty & QSize & QPeek & QEnqueue");
	}
	
	for(i = 1; i <= 3; ++i)
	{
        res = QEnqueue(Q1, arr[i]);
        
        if( QIsEmpty(Q1)  || QSize(Q1) != i || res ||
		strcmp((char*)QPeek(Q1), (char*)arr[1]) )

		{
			puts("Failes in TestString: QIsEmpty & QSize & QPeek & QEnqueue");
		}
	}
	
	Q1 = QAppend(Q1, Q2);
	
	if( QIsEmpty(Q1) || !QIsEmpty(Q2) || QSize(Q1) != 4 || QSize(Q2) != 0 )

		{								
			puts("Failes in TestString: QAppend");
		}
		
	for(i = 0; i <= 3; ++i)
	{
		if( QSize(Q1) != 4-i || strcmp((char*)QPeek(Q1), (char*)arr[(i+1)%4]))

		{
			puts("Failes in TestString: QAppend & QDequeue");
		}
		
		QDequeue(Q1); 
	}
	
	if( !QIsEmpty(Q1) || QSize(Q1) != 0 )
	
	{
		puts("Failes in TestString: QDequeue & QSize & QIsEmpty");	
	}
	
	QDestroy(Q1);
	QDestroy(Q2);
}
	



