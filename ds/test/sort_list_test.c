/***************************************
* Author : Natty
* Reviewer : Matan
* Date : 22 / 12 / 2024
* Last update: 24 / 12 / 2024
*****************************************/

#include <stdio.h> 		/* printf, puts,  */
#include <string.h> 	/* strcpy, strcmp */
#include <assert.h>
#include "sort_list.h" 

#define ANSI_COLOR_RED          "\x1b[31m"
#define ANSI_COLOR_GREEN        "\x1b[32m"
#define ANSI_COLOR_BLUE         "\x1b[34m"
#define ANSI_RESET_ALL          "\x1b[0m"

static int match_func (void *check_data, void *user_param);
static int op_func (void *data, void *user_param);
static int sort_func(void *check_data, void *user_param );

/***************************function declaration**************************/
static void TestString(void);
/***************************End of function declaration******************/

int main ()
{

	puts(ANSI_COLOR_BLUE"====================================================="ANSI_RESET_ALL);
    puts(ANSI_COLOR_GREEN"'TestString()'"ANSI_RESET_ALL);
    TestString();
	puts(ANSI_COLOR_BLUE"====================================================="ANSI_RESET_ALL);
     
return 0;
}

static void TestString(void)
{

	void* data = NULL;
	int res = 0;
	int i = 0;
	char* arr[4] = {"blabla", "Natty", "hello", "itr5" };
	
	char* arr2[5] = {"Splice", "sortlistMerge", "Meir", "cBanai", "sot" };
		
	sort_list_iter_t dummy_itr1;
	sort_list_iter_t itr1;
	sort_list_iter_t itr2;
	sort_list_iter_t itr3;
	sort_list_iter_t itr33;
	sort_list_iter_t itr333;

	sort_list_iter_t itr5;

		
	sort_list_iter_t next_iter;
	
	sort_list_t* srl1 = SortlistCreate(sort_func);
	sort_list_t* srl2 = SortlistCreate(sort_func);

	sort_list_t* srl3 = SortlistCreate(sort_func); /* Empty dest */
	sort_list_t* srl4 = SortlistCreate(sort_func); /* Not Empty src */
	
	dummy_itr1 = SortlistBegin(srl1);


	if(SortlistNext(dummy_itr1).iter != NULL || 
		SortlistPrev(dummy_itr1).iter !=  SortlistPrev(SortlistEnd(srl1)).iter)
	{
		puts(ANSI_COLOR_RED"Failes in TestString: Begin & End & GetData & Next & Prev"ANSI_RESET_ALL);
	}

	if( !SortlistIsEmpty(srl1) || SortlistSize(srl1) != 0)
	{
		puts(ANSI_COLOR_RED"Failes in TestString: Create & IsEmpty & Size"ANSI_RESET_ALL);
	}

	
	itr2 = SortlistInsert(srl1, arr[0]);

	assert((dummy_itr1.list == itr2.list ) && puts(ANSI_COLOR_GREEN"NDEBUG SAME LIST TEST - OK"ANSI_RESET_ALL));
	
	if( SortlistIsEmpty(srl1)  || SortlistSize(srl1) != 1)
	{
		puts(ANSI_COLOR_RED"Failes in TestString: IsEmpty & Size & Begin & Insert"ANSI_RESET_ALL);
	}
	
	

	if( strcmp( arr[0], (char*)SortlistGetData(itr2) ) )
	{
		puts(ANSI_COLOR_RED"Failes in TestString: Begin & GetData & Insert"ANSI_RESET_ALL);
	}


	itr3 = SortlistInsert(srl1, arr[1]);
		
	if( SortlistIsEmpty(srl1)  || SortlistSize(srl1) != 2 ||
		itr2.iter !=  SortlistPrev(SortlistEnd(srl1)).iter)
	{
		puts(ANSI_COLOR_RED"Failes in TestString: IsEmpty & Size & End & Insert & Prev"ANSI_RESET_ALL);
	}
	
 	
	next_iter = SortlistBegin(srl1);
	data = SortlistGetData(next_iter);

	if(strcmp(arr[1], (char*)SortlistGetData(itr3)) ||
		 
	0 < sort_func( (char*)data, (char*)SortlistGetData(SortlistNext(next_iter)) ))
	{
		puts(ANSI_COLOR_RED"Failes in TestString: sort_func & GetData & Next & Prev & Insert"ANSI_RESET_ALL);
	}


	itr33 = SortlistInsert(srl1, arr[2]);
	
	if( SortlistSize(srl1) != 3 ||
		itr33.iter !=  SortlistPrev(SortlistEnd(srl1)).iter	)
	{
		puts(ANSI_COLOR_RED"Failes in TestString: Size & End & Insert & sort_func"ANSI_RESET_ALL);
	}
	
	itr333 = SortlistInsert(srl1, arr[2]);
	
	if( SortlistSize(srl1) != 4 ||
		itr333.iter !=  SortlistPrev(SortlistEnd(srl1)).iter	)
	{
		puts(ANSI_COLOR_RED"Failes in TestString: Size & End & Insert & sort_func"ANSI_RESET_ALL);
	}
	
	itr5 = itr3;

	if(1 != SortlistIterIsEqual(itr5, itr3))
	{
		puts(ANSI_COLOR_RED"Failes in TestString: SortlistIterIsEqual"ANSI_RESET_ALL);
	}
	
	data = SortlistPopBack(srl1);
	
	if( SortlistSize(srl1) != 3 || strcmp("hello", data) )
	{
		puts(ANSI_COLOR_RED"Failes in TestString: Size & PopBack"ANSI_RESET_ALL);
	}	
	
	data = SortlistPopFront(srl1);
	
	if( SortlistSize(srl1) != 2 || strcmp("Natty", data) )
	{
		puts(ANSI_COLOR_RED"Failes in TestString: Size & PopFront"ANSI_RESET_ALL);
	}
	
		
	itr3 = SortlistInsert(srl1, arr[1]);
		
	if(  SortlistSize(srl1) != 3 ||
		itr33.iter !=  SortlistPrev(SortlistEnd(srl1)).iter ||
		itr2.iter !=  SortlistPrev(itr33).iter    )
	{
		puts(ANSI_COLOR_RED"Failes in TestString: Size & End & Insert & Prev"ANSI_RESET_ALL);
	}
	
	itr5 = SortlistFind(srl1, SortlistBegin(srl1),
						SortlistEnd(srl1),	SortlistGetData(itr2));
	
	if(1 != SortlistIterIsEqual(itr5, itr2))
	{
		puts(ANSI_COLOR_RED"Failes in TestString: SortlistFind"ANSI_RESET_ALL);
	}

	itr5 = SortlistBegin(srl1);

	for( i = 0; i < 3 ; ++i )
	{
		
		res = SortlistForEach(itr5, SortlistNext(itr5),op_func,
					       SortlistGetData(itr5));
		
		if( 1 != res) 
		{
			puts(ANSI_COLOR_RED"Failes in TestString: SortlistForEach"ANSI_RESET_ALL);
		} 
		
		itr5 = SortlistNext(itr5);			       
	}
	
	res = SortlistForEach(SortlistBegin(srl1), SortlistEnd(srl1),
						 op_func,"natty");
		
	if( 0 != res) 
	{
			puts(ANSI_COLOR_RED"Failes in TestString: SortlistForEach"ANSI_RESET_ALL);
	}
	
	itr5 = SortlistInsert(srl1, arr[3]);							
	itr5 = SortlistRemove(itr5);

	if(!SortlistIterIsEqual(itr5, SortlistEnd(srl1)) || SortlistSize(srl1) != 3 )
	{
		puts(ANSI_COLOR_RED"Failes in TestString: Remove & PushBack & Count"ANSI_RESET_ALL);
	}	
	
	
	itr5 = SortlistFindIf(SortlistBegin(srl1), SortlistEnd(srl1),
	 					match_func, SortlistGetData(itr2));
	
	if(1 != SortlistIterIsEqual(itr5, itr2) ||
	   0 != sort_func( SortlistGetData(itr2), SortlistGetData(itr5) ) )
	{
		puts(ANSI_COLOR_RED"Failes in TestString: SortlistFindIf"ANSI_RESET_ALL);
	}
	
	itr5 = SortlistInsert(srl1, arr2[1]); /* "sortlistMerge" */						
	itr5 = SortlistInsert(srl1, arr2[1]); /* "sortlistMerge" */						

	itr5 = SortlistInsert(srl2, "dortlistMerge");						
	itr5 = SortlistInsert(srl2, "dortlistMerge");

 			 
	if( SortlistSize(srl2) != 2	|| SortlistSize(srl1) != 5 ||
		strcmp((char*)SortlistGetData(SortlistBegin(srl2)), "dortlistMerge")
	  )
	
	{
		puts(ANSI_COLOR_RED"Failes in TestString_1: SortlistInsert"ANSI_RESET_ALL);	
	}
	
		SortlistInsert(srl2, arr2[0]); /* "Splice" */	
		itr5 = SortlistInsert(srl2, arr2[2]); /* "Meir" */	


	if(	SortlistSize(srl2) != 4	)
	{
		puts(ANSI_COLOR_RED"Failes in TestString_2: SortlistInsert"ANSI_RESET_ALL);		
	}
	
	SortlistMerge(srl1, srl2);
		
	if( SortlistSize(srl2) != 0	|| SortlistSize(srl1) != 9 ||
		strcmp(SortlistGetData(SortlistNext(itr2)), "dortlistMerge") ||
		strcmp(SortlistGetData(SortlistPrev(itr33)), "dortlistMerge") ||
		strcmp(SortlistGetData(SortlistNext(itr3)), "Splice") ||
		strcmp(SortlistGetData(SortlistPrev(itr3)), "Meir")  
	  )									 

	{
		puts(ANSI_COLOR_RED"Failes in TestString_1: SortlistMerge"ANSI_RESET_ALL);	
	}

	itr5 = SortlistInsert(srl2, arr2[3]); /* "cBanai */
	itr5 = SortlistInsert(srl2, arr2[4]); /* "sot" */
	
	if(	SortlistSize(srl2) != 2	)
	{
		puts(ANSI_COLOR_RED"Failes in TestString_3: SortlistInsert"ANSI_RESET_ALL);		
	}
	
	SortlistMerge(srl1, srl2);
		
	if( SortlistSize(srl2) != 0	|| SortlistSize(srl1) != 11 ||
		strcmp(SortlistGetData(SortlistNext(itr2)), "cBanai") ||
		strcmp(SortlistGetData(SortlistPrev(SortlistEnd(srl1))), "sot")
	  )
			
	{
		puts(ANSI_COLOR_RED"Failes in TestString_2: SortlistMerge"ANSI_RESET_ALL);	
	}
	
	
	itr2 = SortlistInsert(srl4, arr2[0]); /* "Splice" */	
	itr1 = SortlistInsert(srl4, arr2[2]); /* "Meir" */
	itr3 = SortlistInsert(srl4, arr2[3]); /* "cBanai */
	SortlistInsert(srl4, arr2[4]); /* "sot" */

	if(	SortlistSize(srl4) != 4	)
	{
		puts(ANSI_COLOR_RED"Failes in TestString_4: SortlistInsert"ANSI_RESET_ALL);		
	}	
	
	itr5 = itr1;
	SortlistMerge(srl3, srl4);
	
	if( SortlistSize(srl4) != 0	|| SortlistSize(srl3) != 4 )
	{
		puts(ANSI_COLOR_RED"Failes in TestString_4: SortlistInsert"ANSI_RESET_ALL);		
	}

	itr5 = SortlistFind(srl3, SortlistBegin(srl3),
						SortlistEnd(srl3),	SortlistGetData(itr5));
	
	if( 
		strcmp(SortlistGetData(itr5), "Meir") ||
		strcmp(SortlistGetData(SortlistNext(itr5)), "Splice") ||
		strcmp(SortlistGetData(SortlistNext(SortlistNext(itr5))), "cBanai") ||
		strcmp(SortlistGetData(SortlistPrev(SortlistEnd(srl1))), "sot") 					
	  )
			
	  {
		  puts(ANSI_COLOR_RED"Failes in TestString_2: SortlistMerge"ANSI_RESET_ALL );	
	  }
		
				
	puts(ANSI_COLOR_GREEN"TestString: Success"ANSI_RESET_ALL);
		
	SortlistDestroy(srl1);
	SortlistDestroy(srl2);
	
	SortlistDestroy(srl3);
	SortlistDestroy(srl4);

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

/*******************match_function*********************/
static int sort_func(void *check_data, void *user_param )
{
	int res = strcmp(check_data, user_param);
		
	return res;
}


