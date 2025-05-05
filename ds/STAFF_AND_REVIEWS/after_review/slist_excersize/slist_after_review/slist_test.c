/***************************************
* Author : Natty
* Reviewer : Natan
* Date : 10 / 12 / 2024
* Last update: 14 / 12 / 2024
*****************************************/

#include <stdio.h> 		/* printf, puts,  */
#include <string.h> 	/* strcpy, strcmp */
#include "slist.h" 

static int match_function (void *check_data, void *user_param);
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

	int res = 0;
	int i = 0;
	char* arr[4] = {"blabla", "Natty", "Hello", "itr5" };
	slist_iter_t itr1;
	slist_iter_t itr2;
	slist_iter_t itr3;
	slist_iter_t itr4;
	slist_iter_t itr5;
	slist_t* s1 = SlistCreate();
	slist_t* s2 = SlistCreate();
	
	itr1 = SlistBegin(s1);
	
	if(SlistGetData(itr1) != s1 || SlistNext(itr1) != NULL )
	{
		puts("Failes in TestString: End & GetData & Next");
	}
	
	
	if( !SlistIsEmpty(s1)  || SlistCount(s1) != 0)
	{
		puts("Failes in TestString: Create & IsEmpty & Count");
	}
	
	itr2 = SlistInsertBefore(s1, SlistBegin(s1), arr[0]);

	if( SlistIsEmpty(s1)  || SlistCount(s1) != 1)
	{
		puts("Failes in TestString: IsEmpty & Count & Begin & InsertBefore");
	}
	
	if( strcmp( arr[0], (char*)SlistGetData(itr2) ) )
	{
		puts("Failes in TestString: Begin & GetData & InsertBefore");
	}
	
	if(SlistGetData(itr1) != SlistGetData(itr2) ||
	   SlistNext(itr1) != SlistNext(itr2) )
	{
		puts("Failes in TestString: GetData & Next & InsertBefore");
	}
	
	if(SlistGetData(SlistNext(itr1)) != s1 ||
	   SlistGetData(SlistNext(itr1)) != SlistGetData(SlistEnd(s1)) ||
	   SlistNext(SlistNext(itr1)) != NULL )
	{
		puts("Failes in TestString: End & GetData & Next");
	}
	
	itr3 = SlistInsertBefore(s1, SlistEnd(s1), arr[1]);

	if( SlistIsEmpty(s1)  || SlistCount(s1) != 2)
	{
		puts("Failes in TestString: IsEmpty & Count & End & InsertBefore");
	}
	
	itr5 = SlistInsertBefore(s2, SlistBegin(s2), arr[3]);
	SlistSetData(itr5, SlistGetData(itr3));

	if( strcmp( (char*)SlistGetData(itr3), (char*)SlistGetData(itr5) ) )
	{
		puts("Failes in TestString: SetData & GetData & InsertBefore");
	}
	
	itr5 = itr3;

	if(1 != IsItrEqual(itr5, itr3))
	{
		puts("Failes in TestString: IsItrEqual");
	}
	
	itr4 = SlistInsertBefore(s1, itr2, arr[2]);
	
	if( SlistCount(s1) != 3)
	{
		puts("Failes in TestString: Count & InsertBefore");
	}
	itr5 = SlistBegin(s1);
	
	if(1 != IsItrEqual(itr5, itr4))
	{
		puts("Failes in TestString: SlistInsertBefore & IsItrEqual");
	}
	
	itr5 = SlistFind(SlistBegin(s1), SlistEnd(s1),match_function,
					 SlistGetData(itr2));
	
	if(1 != IsItrEqual(itr5, itr2))
	{
		puts("Failes in TestString: SlistFind");
	}
	
	itr5 = SlistBegin(s1);

	for( i = 0; i < 3 ; ++i )
	{
		
		res = SlistForEach(itr5, SlistNext(itr5),op_func,
					       SlistGetData(itr5));
		
		if( 0 != res) 
		{
			puts("Failes in TestString: SlistForEach");
		} 
		
		itr5 = SlistNext(itr5);			       
	}
	
	itr5 = SlistRemove(itr2);
	
	if(!IsItrEqual(itr5, itr4) || SlistCount(s1) != 2 ||
	   !IsItrEqual(SlistNext(itr5), itr3) ||
	   !IsItrEqual(SlistNext(itr3), SlistEnd(s1)))
	{
		puts("Failes in TestString: Remove & Count");
	}
	
	SlistDestroy(s1);
	SlistDestroy(s2);
}
	

/*******************match_function*********************/
static int match_function(void *check_data, void *user_param )
{
	return !strcmp(check_data, user_param);
}
/*****************************************************/

/*******************op_func*********************/
static int op_func (void *data, void *user_param)
{
	return strcmp(data, user_param);
}


