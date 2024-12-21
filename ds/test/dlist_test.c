/***************************************
* Author : Natty
* Reviewer : Eric
* Date : 21 / 12 / 2024
* Last update: 21 / 12 / 2024
*****************************************/

#include <stdio.h> 		/* printf, puts,  */
#include <string.h> 	/* strcpy, strcmp */
#include "dlist.h" 

static int match_func (void *check_data, void *user_param);
static int op_func (void *data, void *user_param);
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

	void* data = NULL;
	int res = 0;
	int i = 0;
	char* arr[4] = {"blabla", "Natty", "Hello", "itr5" };
	
	char* arr2[4] = {"Splice", "MultiFind", "Meir", "Banai" };
		
	dlist_iter_t dummy_itr1;
	dlist_iter_t itr2;
	dlist_iter_t itr3;
	dlist_iter_t itr4;
	dlist_iter_t itr5;
	dlist_iter_t itr6;	
	
	dlist_t* d1 = DListCreate();
	dlist_t* d2 = DListCreate();
	
	dummy_itr1 = DListBegin(d1);
	
	if(DListGetData(dummy_itr1) != d1 || DListNext(dummy_itr1) != NULL || 
		DListPrev(dummy_itr1) !=  DListPrev(DListEnd(d1)))
	{
		puts("Failes in TestString: End & GetData & Next & Prev");
	}
	
	if( !DListIsEmpty(d1)  || DListCount(d1) != 0)
	{
		puts("Failes in TestString: Create & IsEmpty & Count");
	}
	
	itr2 = DListInsertBefore(d1, DListBegin(d1), arr[0]);

	if( DListIsEmpty(d1)  || DListCount(d1) != 1)
	{
		puts("Failes in TestString: IsEmpty & Count & Begin & InsertBefore");
	}
	
	if( strcmp( arr[0], (char*)DListGetData(itr2) ) )
	{
		puts("Failes in TestString: Begin & GetData & InsertBefore");
	}
	
	if(DListGetData(DListPrev(dummy_itr1)) != DListGetData(itr2) ||
	   dummy_itr1 != DListNext(itr2) )
	{
		puts("Failes in TestString: GetData & Next & Prev & InsertBefore");
	}

	
	if(DListGetData(dummy_itr1) != d1 ||
	   DListGetData(DListNext(itr2)) != DListGetData(DListEnd(d1)) ||
	   DListNext(dummy_itr1) != NULL )
	{
		puts("Failes in TestString: End & GetData & Next");
	}
	
	itr3 = DListInsertBefore(d1, DListEnd(d1), arr[1]);
		
	if( DListIsEmpty(d1)  || DListCount(d1) != 2)
	{
		puts("Failes in TestString: IsEmpty & Count & End & InsertBefore");
	}
	
	
	itr5 = DListInsertBefore(d2, DListBegin(d2), arr[3]);
	/*printf(" DListBegin1(d2) = %p \n", (void*)DListBegin(d2));*/
	DListSetData(itr5, DListGetData(itr3));

	if( strcmp( (char*)DListGetData(itr3), (char*)DListGetData(itr5) ) )
	{
		puts("Failes in TestString: SetData & GetData & InsertBefore");
	}
	
	
	itr5 = itr3;

	if(1 != DListIterIsEqual(itr5, itr3))
	{
		puts("Failes in TestString: DListIterIsEqual");
	}
	
	itr4 = DListPushFront(d1, arr[2]);

	if(  itr4 != DListBegin(d1) || DListCount(d1) != 3 ||
	    strcmp((char*)DListGetData(itr4), (char*)DListGetData(DListBegin(d1))))
	{
		puts("Failes in TestString: Count & PushFront");
	}
	
	itr5 = DListFind(DListBegin(d1), DListEnd(d1),match_func,
					 DListGetData(itr2));
	
	if(1 != DListIterIsEqual(itr5, itr2))
	{
		puts("Failes in TestString: DListFind");
	}
			
	itr5 = DListBegin(d1);

	for( i = 0; i < 3 ; ++i )
	{
		
		res = DListForEach(itr5, DListNext(itr5),op_func,
					       DListGetData(itr5));
		
		if( 1 != res) 
		{
			puts("Failes in TestString: DListForEach");
		} 
		
		itr5 = DListNext(itr5);			       
	}
	
	if( DListIsEmpty(d2) || DListCount(d2) != 1)
	{
		puts("Failes in TestString: IsEmpty & Count");
	}
	
	data = DListPopFront(d2);
	
	if( !DListIsEmpty(d2) || DListCount(d2) != 0 ||
	    strcmp((char*)DListGetData(itr3), data) )
	{
		puts("Failes in TestString: IsEmpty & Count & PopFront");
	}
			
	res = DListForEach(DListBegin(d1), DListEnd(d1),op_func,"itr5");
		
	if( 0 != res) 
	{
			puts("Failes in TestString: DListForEach");
	} 
	
	itr5 = DListPushBack(d1, arr[3]);
		
	if(  itr5 != DListPrev(DListEnd(d1)) || DListCount(d1) != 4 ||
	     strcmp((char*)DListGetData(itr5), "itr5") )
	{
		puts("Failes in TestString: Count & PushBack");
	}
	
	data = DListPopBack(d1);
	
	if( DListCount(d1) != 3 || strcmp("itr5", data) )
	{
		puts("Failes in TestString: Count & PopBack");
	}

	itr5 = DListPushBack(d1, arr[3]);							
	itr5 = DListRemove(itr5);
	
	if(!DListIterIsEqual(itr5, DListEnd(d1)) || DListCount(d1) != 3 )
	{
		puts("Failes in TestString: Remove & PushBack & Count");
	}

	itr5 = DListPushFront(d1, arr2[1]);							
	itr5 = DListPushBack(d1, arr2[1]);							

	res = DListMultiFind(DListBegin(d1), DListEnd(d1),match_func,
			 			 "MultiFind", d2);

				 			 
	if( 0 != res || DListCount(d2) != 2	|| DListCount(d1) != 5 ||
	strcmp((char*)DListGetData(DListBegin(d2)), "MultiFind") ||
	strcmp((char*)DListGetData(DListNext(DListBegin(d2))), "MultiFind") )
	
	{
		puts("Failes in TestString: DListMultiFind & PushBack & PushFront");	
	}
	
	itr6 = DListPushBack(d2, arr2[0]); /* "Splice" */	
	itr5 = DListPushBack(d2, arr2[2]); /* "Meir" */	
	itr5 = DListPushBack(d2, arr2[3]); /* "Banai */
									 			 
	if(	DListCount(d2) != 5	)
	{
		puts("Failes in TestString: PushBack");		
	}
	
	itr5 = DListSplice(itr3, itr6, DListEnd(d2));
	
	if( DListCount(d2) != 2	|| DListCount(d1) != 8 ||
		!DListIterIsEqual( DListNext(itr5) ,itr3)  ||
		strcmp((char*)DListGetData(itr5), "Banai") ||
		strcmp((char*)DListGetData(DListPrev(itr5)), "Meir") ||
		strcmp((char*)DListGetData(DListPrev(DListPrev(itr5))), "Splice") ||
		strcmp((char*)DListGetData(DListPrev(DListPrev(DListPrev(itr5)))), "blabla") )		
	{
		puts("Failes in TestString: Splice");	
	}

	puts("TestString: Success");	
	DListDestroy(d1);
	DListDestroy(d2);
}
	

/*******************match_function*********************/
static int match_func(void *check_data, void *user_param )
{
	return !strcmp(check_data, user_param);
}
/*****************************************************/

/*******************op_func*********************/
static int op_func (void *data, void *user_param)
{
	return !strcmp(data, user_param);
}


