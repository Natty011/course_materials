/***************************************
* Autor : Natty
* Reviewer : Chen
* Date : 23 / 11 / 2024
* Last update: 26 / 11 / 2024
*****************************************/
#include <stdio.h> /* printf, putchar */
#include <stdlib.h> /* malloc, realloc, free */
#include <string.h> /* strcat, strcpy, strlen */
#define N 3 
#define MAX_INT_CHAR 25

/*************** MACROS *************************/
#define MAX(a, b)  (((a) > (b)) ? (a) : (b)) 
#define MAX3(a, b, c)  (MAX((MAX((a), (b))), (c)))
#define SIZEOF_VAR(object) (char *)(&object+1) - (char *)(&object)
#define SIZEOF_TYPE(type) (char *)(((type*)0) +1) - (char *)((type*)0)

/*************** End of MACROS *************************/

/*************** typedef and structure declaration *************************/

typedef void (*print_t) (void* data); 
typedef void* (*add_t) (void* ptr, int num); 
typedef void (*clean_t) (void* ptr); 

typedef struct 
{

	void* data;
	print_t print_element;
	add_t add_element;
	clean_t clean_element;
	
} element_t;
/***************End of typedef and structure declaration ******************/

/***************************function declaration**************************/
void PrintArr( element_t* arr ,  size_t n );
void AddIntToAllElements( element_t* arr ,  size_t n, int num );
void CleanArr( element_t* arr ,  size_t n );

void PrintInt(void* ptr);
void PrintFloat(void* ptr);
void PrintString(void* ptr);

void* AddIntToInt (void* ptr , int num);
void* AddIntToFloat (void* ptr , int num);
void* AddIntToString (void* ptr , int num);

void NoClean (void* ptr);
void CleanStr (void* ptr);
void CreatArray(void);
void PrintMax(void);
void PrintMax3(void);
void PrintSizeOfVar(void);
void PrintSizeOfType(void);
/***************************function declaration**************************/

int main ()
{
    puts("=====================================================");
    puts("'CreatArray()'");
	CreatArray();
	puts("=====================================================");
	
	puts("'PrintMax()'");
	PrintMax();
    puts("=====================================================");
    
    puts("'PrintMax3()'");
	PrintMax3();
    puts("=====================================================");
    
    puts("'PrintSizeOfVar()'");
	PrintSizeOfVar();
    puts("=====================================================");
    
    puts("'PrintSizeOfType()'");
	PrintSizeOfType();
    puts("=====================================================");
    
	return 0;
}


void CreatArray(void)
{
    element_t arr[N];
	int x = 6;
	float y = 2.5;
	char* string = "hello";
	
	arr[0].data  = &x;
	arr[0].print_element = PrintInt;
    arr[0].add_element = AddIntToInt;
    arr[0].clean_element = NoClean;
    
	arr[1].data = &y;
	arr[1].print_element = PrintFloat;
	arr[1].add_element = AddIntToFloat;
	arr[1].clean_element = NoClean;
	
	arr[2].data = malloc ( strlen(string) + 1 );
	strcpy( (char*)(arr[2].data) , string );
	arr[2].print_element = PrintString;
    arr[2].add_element = AddIntToString;
    arr[2].clean_element = CleanStr;
    
	PrintArr( arr , N );
	
	AddIntToAllElements( arr , N , 10);
    
    PrintArr( arr , N );
    
    CleanArr ( arr , N );
    
    return;
}
/*** Print Array ***/
void PrintArr( element_t* arr ,  size_t n )
{
	size_t i = 0;
	
	for ( i = 0 ; i < n ; ++i)
	{
		arr[i].print_element ( arr[i].data );
		putchar(' ');
	}
	putchar('\n');	
}
/*** Add integer to  Array ***/
void AddIntToAllElements( element_t* arr ,  size_t n, int num )
{
	size_t i = 0;
	
	for ( i = 0 ; i < n ; ++i)
	{
		arr[i].data = arr[i].add_element( arr[i].data , num);
	}
}

void CleanArr( element_t* arr ,  size_t n )
{
	size_t i = 0;
	
	for ( i = 0 ; i < n ; ++i)
	{
		arr[i].clean_element( arr[i].data );
	}
}

/********** PrintInt function ********/
void PrintInt(void* ptr)
{
    printf("%d", *( (int*)ptr ) );
    return;
}

/********** PrintFloat function ********/
void PrintFloat(void* ptr)
{
    printf("%f", *( (float*)ptr ) );
    return;
}
/********** PrintString function ********/
void PrintString(void* ptr)
{
	printf("%s", (char*)ptr);
    return;
}
/********** Adds functions ********/
void* AddIntToInt (void* ptr , int num)
{
	*((int*)ptr) = *((int*)ptr) + num;
	
	return ptr;
}

void* AddIntToFloat (void* ptr , int num)
{
	*( (float*)ptr) = *( (float*)ptr) + (float)num;
	
	return ptr;
}

void* AddIntToString (void* ptr , int num)
{
   /*Make sure the array is large enough to hold the string representation */
   char temp_str[MAX_INT_CHAR] = { 0 };
   
   sprintf(temp_str, "%d", num); /* Convert integer to string */
   
   ptr = realloc ( (char*)ptr, strlen( (char*)ptr ) + strlen(temp_str) + 1 );
   strcat( (char*)ptr , temp_str); /* Concatenate to the string member */

   return ptr;	
}
/********** Clean functions ********/
void NoClean (void* ptr)
{
	(void)ptr;
	return;
}

void CleanStr (void* ptr)
{
	free ( (char*)ptr );
}
/**** MAX(a, b) MACRO ****/
void PrintMax(void)
{
    int a = 45, b = 34;
    printf("The Maximum of %d and %d is %d\n", a, b, MAX(a, b));
    return;
}
/**** MAX3 MACRO ****/
void PrintMax3(void)
{
    int a = 45, b = 34, c = 62;
    printf("The Maximum of %d and %d and %d  is %d\n", a, b, c, MAX3(a, b, c));
    return;
}
/**** SIZEOF_VAR MACRO ****/
void PrintSizeOfVar(void)
{
    double x = 0.0;
    int arr[10] = {0};
    
    printf("double var size: %ld\n", SIZEOF_VAR(x));
    printf("int arr[10] size : %ld\n", SIZEOF_VAR(arr));
    return;
}

/**** SIZEOF_TYPE MACRO ****/

void PrintSizeOfType(void)
{
    printf("double type size: %lu\n", SIZEOF_TYPE(double));
    printf("int type size: %lu\n", SIZEOF_TYPE(int));
    printf("size_t type size: %lu\n", SIZEOF_TYPE(size_t));
    printf("unsigned char type size: %lu\n", SIZEOF_TYPE(unsigned char));
    printf("short type size: %lu\n", SIZEOF_TYPE(short));
    return;
}



