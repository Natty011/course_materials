/***************************************
* Author : Natty
* Reviewer : Hadar
* Date : 05 / 08 / 2024
* Last update: 08 / 12 / 2024
*****************************************/

#include <stdio.h> /* printf, puts,  */
#include <string.h> /* strcpy, strcmp */
#include "stack.h" /*  */
/****************struct and enum declaration declaration*********************/
typedef struct
{
	char name[10];
	int score1;
	float score2;
	  
}struct_test_t;

/***************End of struct and enum declaration declaration*******/
/***************************function declaration**************************/
static void TestChars(void);
static void TestDouble(void);
static void TestStruct(void);
static void InitStruct(struct_test_t* s, char* str, int score1, float score2);
static int CmpStruct(struct_test_t s1, struct_test_t s2);
/***************************End of function declaration******************/

int main ()
{

	puts("=====================================================");
    puts("'TestChars()'");
    TestChars();
    puts("=====================================================");
  
    puts("'TestDouble()'");
    TestDouble();
    puts("=====================================================");
  
	puts("'TestStruct()'");
    TestStruct();
    puts("=====================================================");
   
return 0;
}

static void TestChars(void)
{
	char arr[3] = {'a', '\t', '2'};
	size_t cap = sizeof(arr)/sizeof(arr[0]) , i = 0 ;
	stack_t* s1 = StackCreate(cap, sizeof(arr[0]));
	
	if(StackCapacity(s1) != cap || !StackIsEmpty(s1) || StackSize(s1))
	{
		puts("Failes in TestChars: Create & Capacity");
	}
	
	for(i = 0; i < cap; ++i)
	{
		
		StackPush(s1, arr + i);
		if(arr[i] != *(char*)StackPeek(s1))
		{
			puts("Failes in TestChars: Push & Peek ");
		}
		
		if(StackIsEmpty(s1) || StackSize(s1) != (i + 1))
		{
			puts("Failes in TestChars: IsEmpty & Size ");
		}
		
	}
	
	for(i = 0; i < cap; ++i)
	{
		if(arr[cap-i-1] != *(char*)StackPeek(s1) )
		{
			puts("Failes in TestChars: Peek & Pop ");
		}
		StackPop(s1);
	}
	
	if( !StackIsEmpty(s1) || StackSize(s1))
	{
		puts("Failes in TestChars: IsEmpty & Size");
	}
	
	StackDestroy(s1);
	puts("TestChars: Success");			
}

static void TestDouble(void)
{
	double arr[3] = {-0.5, 82.75, 0.0};
	size_t cap = sizeof(arr)/sizeof(arr[0]) , i = 0 ;
	stack_t* s1 = StackCreate(cap, sizeof(arr[0]));
	
	if(StackCapacity(s1) != cap || !StackIsEmpty(s1) || StackSize(s1))
	{
		puts("Failes in TestDouble: Create & Capacity");
	}
	
	for(i = 0; i < cap; ++i)
	{
		
		StackPush(s1, arr + i);
		if(arr[i] != *(double*)StackPeek(s1))
		{
			puts("Failes in TestDouble: Push & Peek ");
		}
		
		if(StackIsEmpty(s1) || StackSize(s1) != (i + 1))
		{
			puts("Failes in TestDouble: IsEmpty & Size ");
		}
		
	}
	
	for(i = 0; i < cap; ++i)
	{
		if(arr[cap-i-1] != *(double*)StackPeek(s1) )
		{
			puts("Failes in TestDouble: Peek & Pop ");
		}
		StackPop(s1);
	}
	
	if( !StackIsEmpty(s1) || StackSize(s1))
	{
		puts("Failes in TestDouble: IsEmpty & Size");
	}
	
	StackDestroy(s1);
	puts("TestDouble: Success");			
}

static void TestStruct(void)
{
	struct_test_t arr[3];
	size_t cap = sizeof(arr)/sizeof(arr[0]) , i = 0 ;
	stack_t* s1 = StackCreate(cap, sizeof(arr[0]));
	
	InitStruct(arr+0, "Natty", 95, 95.25);
	InitStruct(arr+1, "Hello", 94, 95.5);
	InitStruct(arr+2, "World", 93, 95.75);	
	
	
	if(StackCapacity(s1) != cap || !StackIsEmpty(s1) || StackSize(s1))
	{
		puts("Failes in TestStruct: Create & Capacity");
	}
	
	for(i = 0; i < cap; ++i)
	{
		
		StackPush(s1, arr + i);
		if(CmpStruct(arr[i] , *(struct_test_t*)StackPeek(s1)))
		{
			puts("Failes in TestStruct: Push & Peek ");
		}
		
		if(StackIsEmpty(s1) || StackSize(s1) != (i + 1))
		{
			puts("Failes in TestStruct: IsEmpty & Size ");
		}
		
	}
	
	for(i = 0; i < cap; ++i)
	{
		if(CmpStruct( arr[cap-i-1], *(struct_test_t*)StackPeek(s1) ) )
		{
			puts("Failes in TestStruct: Peek & Pop ");
		}
		StackPop(s1);
	}
	
	if( !StackIsEmpty(s1) || StackSize(s1))
	{
		puts("Failes in TestStruct: IsEmpty & Size");
	}
	
	StackDestroy(s1);
	puts("TestStruct: Success");			
}

static void InitStruct(struct_test_t* s, char* str, int score1, float score2)
{
	strcpy(s->name, str);
	s->score1 = score1;
	s->score2 = score2;
}

static int CmpStruct(struct_test_t s1, struct_test_t s2)
{
	return strcmp(s1.name, s2.name) && !(s1.score1 == s2.score1) \
	                                  && !(s1.score2 == s2.score2);
}




