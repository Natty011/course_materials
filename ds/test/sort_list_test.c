/***************************************
* Author : Natty
* Reviewer : Eric
* Date : 22 / 12 / 2024
* Last update: 22 / 12 / 2024
*****************************************/

#include <stdio.h> 		/* printf, puts,  */
#include <string.h> 	/* strcpy, strcmp */
#include "sort_list.h" 
#include "sort_list.h" 

static int match_func (void *check_data, void *user_param);
static int op_func (void *data, void *user_param);
static int sort_func(void *check_data, void *user_param );

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
		
	sort_list_iter_t dummy_itr1;
	sort_list_iter_t itr2;
	sort_list_iter_t itr3;
	sort_list_iter_t itr4;
	sort_list_iter_t itr5;
	sort_list_iter_t itr6;	
	
	sort_list_t* srl1 = SortlistCreate(sort_func);
	sort_list_t* srl2 = SortlistCreate(sort_func);

	dummy_itr1 = SortlistBegin(srl1);

/*	
	printf("srl1 = %p \n", (void*)srl1);
	printf("SortlistGetData(dummy_itr1) = %p \n", SortlistGetData(dummy_itr1));	
*/	
	if(SortlistNext(dummy_itr1).iter != NULL || 
		SortlistPrev(dummy_itr1).iter !=  SortlistPrev(SortlistEnd(srl1)).iter)
	{
		puts("Failes in TestString: Begin & End & GetData & Next & Prev");
	}

	if( !SortlistIsEmpty(srl1) || SortlistSize(srl1) != 0)
	{
		puts("Failes in TestString: Create & IsEmpty & Size");
	}

	
	itr2 = SortlistInsert(srl1, arr[0]);

	if( SortlistIsEmpty(srl1)  || SortlistSize(srl1) != 1)
	{
		puts("Failes in TestString: IsEmpty & Count & Begin & Insert");
	}
	
	
/*
	if( strcmp( arr[0], (char*)SortlistGetData(itr2) ) )
	{
		puts("Failes in TestString: Begin & GetData & InsertBefore");
	}
*/			
	puts("TestString: Success");	
	SortlistDestroy(srl1);
	SortlistDestroy(srl2);
	

}
/*	
	dummy_itr1 = sort_listBegin(d1);
	
	if(sort_listGetData(dummy_itr1) != d1 || sort_listNext(dummy_itr1) != NULL || 
		sort_listPrev(dummy_itr1) !=  sort_listPrev(sort_listEnd(d1)))
	{
		puts("Failes in TestString: End & GetData & Next & Prev");
	}
	
	if( !sort_listIsEmpty(d1)  || sort_listCount(d1) != 0)
	{
		puts("Failes in TestString: Create & IsEmpty & Count");
	}
	
	itr2 = sort_listInsertBefore(d1, sort_listBegin(d1), arr[0]);

	if( sort_listIsEmpty(d1)  || sort_listCount(d1) != 1)
	{
		puts("Failes in TestString: IsEmpty & Count & Begin & InsertBefore");
	}
	
	if( strcmp( arr[0], (char*)sort_listGetData(itr2) ) )
	{
		puts("Failes in TestString: Begin & GetData & InsertBefore");
	}
	
	if(sort_listGetData(sort_listPrev(dummy_itr1)) != sort_listGetData(itr2) ||
	   dummy_itr1 != sort_listNext(itr2) )
	{
		puts("Failes in TestString: GetData & Next & Prev & InsertBefore");
	}

	
	if(sort_listGetData(dummy_itr1) != d1 ||
	   sort_listGetData(sort_listNext(itr2)) != sort_listGetData(sort_listEnd(d1)) ||
	   sort_listNext(dummy_itr1) != NULL )
	{
		puts("Failes in TestString: End & GetData & Next");
	}
	
	itr3 = sort_listInsertBefore(d1, sort_listEnd(d1), arr[1]);
		
	if( sort_listIsEmpty(d1)  || sort_listCount(d1) != 2)
	{
		puts("Failes in TestString: IsEmpty & Count & End & InsertBefore");
	}
	
	
	itr5 = sort_listInsertBefore(d2, sort_listBegin(d2), arr[3]);

	sort_listSetData(itr5, sort_listGetData(itr3));

	if( strcmp( (char*)sort_listGetData(itr3), (char*)sort_listGetData(itr5) ) )
	{
		puts("Failes in TestString: SetData & GetData & InsertBefore");
	}
	
	
	itr5 = itr3;

	if(1 != sort_listIterIsEqual(itr5, itr3))
	{
		puts("Failes in TestString: sort_listIterIsEqual");
	}
	
	itr4 = sort_listPushFront(d1, arr[2]);

	if(  itr4 != sort_listBegin(d1) || sort_listCount(d1) != 3 ||
	    strcmp((char*)sort_listGetData(itr4), (char*)sort_listGetData(sort_listBegin(d1))))
	{
		puts("Failes in TestString: Count & PushFront");
	}
	
	itr5 = sort_listFind(sort_listBegin(d1), sort_listEnd(d1),match_func,
					 sort_listGetData(itr2));
	
	if(1 != sort_listIterIsEqual(itr5, itr2))
	{
		puts("Failes in TestString: sort_listFind");
	}
			
	itr5 = sort_listBegin(d1);

	for( i = 0; i < 3 ; ++i )
	{
		
		res = sort_listForEach(itr5, sort_listNext(itr5),op_func,
					       sort_listGetData(itr5));
		
		if( 1 != res) 
		{
			puts("Failes in TestString: sort_listForEach");
		} 
		
		itr5 = sort_listNext(itr5);			       
	}
	
	if( sort_listIsEmpty(d2) || sort_listCount(d2) != 1)
	{
		puts("Failes in TestString: IsEmpty & Count");
	}
	
	data = sort_listPopFront(d2);
	
	if( !sort_listIsEmpty(d2) || sort_listCount(d2) != 0 ||
	    strcmp((char*)sort_listGetData(itr3), data) )
	{
		puts("Failes in TestString: IsEmpty & Count & PopFront");
	}
			
	res = sort_listForEach(sort_listBegin(d1), sort_listEnd(d1),op_func,"itr5");
		
	if( 0 != res) 
	{
			puts("Failes in TestString: sort_listForEach");
	} 
	
	itr5 = sort_listPushBack(d1, arr[3]);
		
	if(  itr5 != sort_listPrev(sort_listEnd(d1)) || sort_listCount(d1) != 4 ||
	     strcmp((char*)sort_listGetData(itr5), "itr5") )
	{
		puts("Failes in TestString: Count & PushBack");
	}
	
	data = sort_listPopBack(d1);
	
	if( sort_listCount(d1) != 3 || strcmp("itr5", data) )
	{
		puts("Failes in TestString: Count & PopBack");
	}

	itr5 = sort_listPushBack(d1, arr[3]);							
	itr5 = sort_listRemove(itr5);
	
	if(!sort_listIterIsEqual(itr5, sort_listEnd(d1)) || sort_listCount(d1) != 3 )
	{
		puts("Failes in TestString: Remove & PushBack & Count");
	}

	itr5 = sort_listPushFront(d1, arr2[1]);							
	itr5 = sort_listPushBack(d1, arr2[1]);							

	res = sort_listMultiFind(sort_listBegin(d1), sort_listEnd(d1),match_func,
			 			 "MultiFind", d2);

				 			 
	if( 0 != res || sort_listCount(d2) != 2	|| sort_listCount(d1) != 5 ||
	strcmp((char*)sort_listGetData(sort_listBegin(d2)), "MultiFind") ||
	strcmp((char*)sort_listGetData(sort_listNext(sort_listBegin(d2))), "MultiFind") )
	
	{
		puts("Failes in TestString: sort_listMultiFind & PushBack & PushFront");	
	}
*/	
	/* itr6 = sort_listPushBack(d2, arr2[0]); */ /* "Splice" */	
	/*itr5 = sort_listPushBack(d2, arr2[2]); *//* "Meir" */	
	/*itr5 = sort_listPushBack(d2, arr2[3]); *//* "Banai */
/*									 			 
	if(	sort_listCount(d2) != 5	)
	{
		puts("Failes in TestString: PushBack");		
	}
	
	itr5 = sort_listSplice(itr3, itr6, sort_listEnd(d2));
	
	if( sort_listCount(d2) != 2	|| sort_listCount(d1) != 8 ||
		!sort_listIterIsEqual( sort_listNext(itr5) ,itr3)  ||
		strcmp((char*)sort_listGetData(itr5), "Banai") ||
		strcmp((char*)sort_listGetData(sort_listPrev(itr5)), "Meir") ||
		strcmp((char*)sort_listGetData(sort_listPrev(sort_listPrev(itr5))), "Splice") ||
		strcmp((char*)sort_listGetData(sort_listPrev(sort_listPrev(sort_listPrev(itr5)))), "blabla") )		
	{
		puts("Failes in TestString: Splice");	
	}

}
	
*/
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

/*******************match_function*********************/
static int sort_func(void *check_data, void *user_param )
{
	return (-1) * strcmp(check_data, user_param);
}

