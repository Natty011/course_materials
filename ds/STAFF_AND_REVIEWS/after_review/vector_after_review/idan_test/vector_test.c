#include <stdio.h>  /* printf */
#include <string.h> /* strcmp */
#include <assert.h> /* assert */

#include "vector.h"
#include "vector_test_data.h" /* arrays for Tester function*/

#define PEEKCHAR( s ) *(char*)StackPeek( s )
#define PEEKINT( s ) *(int*)StackPeek( s )
#define PEEKDOUBLE( s ) *(double*)StackPeek( s )

typedef enum
{

	SUCCESS = 0 ,
	A_FAILURE = 1,
	B_FAILURE = 2,
	C_FAILURE = 3,
	D_FAILURE = 4,
	E_FAILURE = 5 ,
	NUMOFFAILURES

} status_t; 

typedef void ( *print_t )( void* element );
typedef int ( *cmp_t )( void* , void* );

status_t Tester(char* arr ,size_t len ,size_t bytes ,print_t print ,cmp_t compare);
void PrintStatus( status_t  , char* test_name );

int CmpAsChar( void* element , void* c_ptr);
int CmpAsInt( void* element , void* c_ptr);
int CmpAsDouble( void* element , void* c_ptr);
int CmpAsStructs( void* element , void* c_ptr);

void PrintVector( vector_t* v , print_t print  );
void PrintAsChar( void* element);
void PrintAsInt( void* element );
void PrintAsDouble( void* element);
void PrintAsStructs( void* element );

int main ()
{

	PrintStatus(
		Tester( chars , lenC , sizeof(char) , PrintAsChar , CmpAsChar )
		, "Chars"
	);
	
	PrintStatus(
		Tester( (char*)ints , lenI , sizeof(int) , PrintAsInt , CmpAsInt )
		, "Ints"
	);
	
	PrintStatus(
		Tester((char*)doubles ,lenD ,sizeof(double) ,PrintAsDouble ,CmpAsDouble)
		, "Doubles"
	);
	
	PrintStatus(
	  Tester((void*)structs, lenS ,sizeof(test_t), PrintAsStructs, CmpAsStructs)
		, "Structs"
	);
	
	return 0;
}

void PrintStatus( status_t status  , char* test_name )
{
	static char* messages[NUMOFFAILURES] =
	{
		"**** %s test end with SUCCESS ****\n" , 
		"%s test FAILED :( A FAILURE ):\n" ,
		"%s test FAILED :( B FAILURE ):\n" ,
		"%s test FAILED :( C FAILURE ):\n" ,
		"%s test FAILED :( D FAILURE ):\n" ,
		"%s test FAILED :( E FAILURE ):\n" 
	};
	
	printf( messages[status] , test_name );
	
} 	

status_t Tester(char* arr, size_t len, size_t bytes, print_t print, cmp_t compare)
{
	size_t i = 0;
	vector_t* v1 = VectorCreate( len ,  bytes );

	if ( VectorCapacity( v1 ) != len || VectorSize( v1 ) )
	{
		PrintVector( v1 , print );
		return A_FAILURE;
	}
	
	for ( i = 0 ; i < len ; ++i )
	{
		VectorPushBack( v1 , arr + i*bytes );
	}

	if ( VectorSize( v1 ) != len )
	{
		PrintVector( v1 , print );
		return B_FAILURE;
	} 
		
	VectorPushBack( v1 , arr );
	VectorPushBack( v1 , arr + 1*bytes );
	
	if (VectorCapacity(v1) != len*2 || VectorSize( v1 ) != len + 2 )
	{
			PrintVector( v1 , print );
			return E_FAILURE;
	}
	
	VectorPopBack( v1 );
	VectorPopBack( v1 );
	
	for ( i = 0 ; i < len ; ++i)
	{
		if ( ! compare( VectorGetAccess( v1 , i ) , arr + i*bytes ) )
		{
			PrintVector( v1 , print );
			return C_FAILURE;
		} 
		VectorPopBack( v1 );
	}
	
	
	if (VectorCapacity(v1) != len*2 || VectorSize( v1 ) != 0 )
	{
		PrintVector( v1 , print );
		return D_FAILURE;
	}
	
	VectorDestroy( v1 );
	
	return SUCCESS;
}

int CmpAsChar( void* element , void* c_ptr)
{
	return *(char*)element == *(char*)c_ptr;
}

int CmpAsInt( void* element , void* i_ptr)
{
	return *(int*)element == *(int*)i_ptr;
}

int CmpAsDouble( void* element , void* d_ptr)
{
	return *(double*)element == *(double*)d_ptr;
}

int  CmpAsStructs( void* element , void* s_ptr)
{
	test_t *t1 = (test_t*)element , *t2 = (test_t*)s_ptr;

	return ( (! strcmp(t1->name , t2->name)) &&	
			 t1->age == t2->age &&
			 t1->avg == t2->avg 
		   );
}

void PrintVector( vector_t* v , print_t print  )
{
	size_t i = 0 , size = VectorSize( v );
	printf("cap = %ld\n" , VectorCapacity( v ) );
	printf("size = %ld\n" , size );
	
	if ( ! size )
	{
		printf("\nstack is empty\n");
	}
	else
	{
		for ( i = 0 ; i < size ; ++i )
		printf("arr[%ld] = " , i );
		print( VectorGetAccess(v , i) );
		putchar('\n');
	} 
	
}

void PrintAsChar( void* element )
{
	printf("%c" , *(char*)element );
}

void PrintAsInt( void* element )
{
	printf("%d" , *(int*)element );
}

void PrintAsDouble( void* element )
{
	printf("%f\n" , *(double*)element );
}

void PrintAsStructs( void* element )
{
	test_t* t = (test_t*)element; 
	putchar('\n');
	printf("name: %s\n" , t->name);
	printf("age: %d\n" , t->age);
	printf("avg: %f\n\n" , t->avg);
}




























