/***************************************
* Author : Natty
* Reviewer : Idan
* Date : 09 / 12 / 2024
* Last update: 10 / 12 / 2024
*****************************************/

#include <stdio.h> /* printf, puts,  */
#include <string.h> /* strcpy, strcmp */
#include "vector.h" /*  */
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
static int CmpStruct(struct_test_t v1, struct_test_t s2);
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
	vector_t* v1 = VectorCreate(cap, sizeof(arr[0]));
	
	if(VectorCapacity(v1) != (cap) || VectorSize(v1))
	{
		puts("Failes in TestChars: Create & Capacity");
	}
	
	for(i = 0; i < cap ; ++i)
	{
		
		VectorPushBack(v1, arr + i);
		if(arr[i] != *(char*)VectorGetAccess(v1, i))
		{
			puts("Failes in TestChars: PushBack & GetAccess ");
		}
		
		if(VectorSize(v1) != (i + 1))
		{
			puts("Failes in TestChars: Size ");
		}
		
	}
	for(i = 0; i < cap ; ++i)
	{
		
		VectorPushBack(v1, arr + i);
		if(arr[i] != *(char*)VectorGetAccess(v1, cap + i))
		{
			puts("Failes in TestChars: PushBack & GetAccess ");
		}
		
		if(VectorSize(v1) != ( cap + i + 1   ) )
		{
			puts("Failes in TestChars: Size ");

		}
		
	}
	
	for(i = 0; i < cap; ++i)
	{
		if(arr[cap-i-1] != *(char*)VectorGetAccess(v1, VectorSize(v1) -1 ))
		{
			puts("Failes in TestChars: GetAccess & PopBack & Size ");
		}
		VectorPopBack(v1);
	}
	
	if( VectorSize(v1) != cap)
	{
		puts("Failes in TestChars: Size");
	}
	
	VectorReserve(v1, 3*cap);
	
	if(VectorCapacity(v1) != (3*cap) || VectorSize(v1) != cap)
	{
		puts("Failes in TestChars: Reserve");
	}
	
	VectorShrink(v1);
	
	if(VectorCapacity(v1) != cap || VectorSize(v1) != cap)
	{
		puts("Failes in TestChars: Shrink");
	}
	

	VectorDestroy(v1);
	puts("TestChars: Success");			
}

static void TestDouble(void)
{
	double arr[3] = {-0.5, 82.75, 2.0};
	size_t cap = sizeof(arr)/sizeof(arr[0]) , i = 0 ;
	vector_t* v1 = VectorCreate(cap, sizeof(arr[0]));
	
	if(VectorCapacity(v1) != cap || VectorSize(v1))
	{
		puts("Failes in TestDouble: Create & Capacity");
	}
	
	for(i = 0; i < cap ; ++i)
	{
		VectorPushBack(v1, arr + i);
		if(arr[i] != *(double*)VectorGetAccess(v1, i) ) 
		{
			puts("Failes in TestDouble: PushBack & GetAccess");
		}
		
		if(VectorSize(v1) != (i + 1))
		{
			puts("Failes in TestDouble: Size");
		}
		
	}
	
	for(i = 0; i < cap ; ++i)
	{
		
		VectorPushBack(v1, arr + i);
		
		if(arr[i] != *(double*)VectorGetAccess(v1, i + cap))
		{
			puts("Failes in TestDouble: PushBack & GetAccess ");
		}

		if(VectorSize(v1) != ( cap + i + 1   ) )
		{
			puts("Failes in TestDouble: Size ");

		}
	}
	
	for(i = 0; i < cap; ++i)
	{
		if(arr[cap-i-1] != *(double*)VectorGetAccess(v1, VectorSize(v1) - 1 ))
		{
			puts("Failes in TestDouble: GetAccess & PopBack & Size ");

		}
		
		VectorPopBack(v1);
	}
	
	if( VectorSize(v1) != cap)
	{
		puts("Failes in TestDouble: Size");
	}
	
	VectorReserve(v1, 4*cap);
	
	if(VectorCapacity(v1) != (4*cap) || VectorSize(v1) != cap)
	{
		puts("Failes in TestDouble: Reserve");
	}
	
	VectorShrink(v1);
	
	if(VectorCapacity(v1) != cap || VectorSize(v1) != cap)
	{
		puts("Failes in TestDouble: Shrink");
	}
	
	VectorDestroy(v1);
	puts("TestDouble: Success");
}

static void TestStruct(void)
{
	struct_test_t arr[3];
	size_t cap = sizeof(arr)/sizeof(arr[0]) , i = 0 ;
	vector_t* v1 = VectorCreate(cap, sizeof(arr[0]));
	
	InitStruct(arr+0, "Natty", 95, 95.25);
	InitStruct(arr+1, "Hello", 94, 95.5);
	InitStruct(arr+2, "World", 93, 95.75);	
	
	
	if(VectorCapacity(v1) != cap ||  VectorSize(v1))
	{
		puts("Failes in TestStruct: Create & Capacity");
	}
	
	for(i = 0; i < cap; ++i)
	{
		
		VectorPushBack(v1, arr + i);
		if(CmpStruct(arr[i] , *(struct_test_t*)VectorGetAccess(v1, i)))
		{
			puts("Failes in TestStruct: PushBack & GetAccess ");
		}
		
		if( VectorSize(v1) != (i + 1) )
		{
			puts("Failes in TestStruct: Size ");
		}
		
	}
	
	for(i = 0; i < cap; ++i)
	{
		VectorPushBack(v1, arr + i);
		
		if(CmpStruct( arr[i], *(struct_test_t*)VectorGetAccess(v1, i + cap) ) )
		{
			puts("Failes in TestStruct: PushBack & GetAccess ");
		}
		
		if( VectorSize(v1) != ( cap + i + 1) || VectorCapacity(v1) != 2*cap)
		{
			puts("Failes in TestStruct: Size");
		}
	}
	
	for(i = 0; i < cap; ++i)
	{
		if(CmpStruct(arr[cap-i-1], *(struct_test_t*)VectorGetAccess(v1, \
			VectorSize(v1) - 1 )))
		{
			puts("Failes in TestStruct: GetAccess & PopBack & Size ");

		}
		
		VectorPopBack(v1);
	}
	
	if( VectorSize(v1) != cap || VectorCapacity(v1) != 2*cap)
	{
		puts("Failes in TestStruct: Size");
	}
	
	VectorReserve(v1, 4*cap);
	
	if(VectorCapacity(v1) != (4*cap) || VectorSize(v1) != cap)
	{
		puts("Failes in TestStruct: Reserve");
	}
	
	VectorShrink(v1);
	
	if(VectorCapacity(v1) != (cap) || VectorSize(v1) != cap)
	{
		puts("Failes in TestStruct: Shrink");
	}
	
	VectorDestroy(v1);
	puts("TestStruct: Success");			
}

static void InitStruct(struct_test_t* s, char* str, int score1, float score2)
{
	strcpy(s->name, str);
	s->score1 = score1;
	s->score2 = score2;
}

static int CmpStruct(struct_test_t v1, struct_test_t s2)
{
	return strcmp(v1.name, s2.name) && !(v1.score1 == s2.score1) \
	                                  && !(v1.score2 == s2.score2);
}




