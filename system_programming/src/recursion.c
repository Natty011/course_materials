/***************************************
* Author : Natty
* Reviewer : David
* Date : 05 / 02 / 2025
* Last update: 06 / 02 / 2025
*****************************************/
#include <string.h> 	/*  strlen */
#include <stdio.h>

#include <assert.h> 	/* assert */
#include <stdlib.h> 	/* malloc, free */
#include "recursion.h" 

#define UNUSED( var )       ( (void)var )

/****************struct and enum declaration*********************/
/***************End of struct and enum declaration *******/
/***********Functions declaration*******/
static void AuxSortIntegers(stack_t* stack, int temp );
/**********End of functions declaration *******/
/******************static functions definition**********************/
/******************End of static functions definition**********************/

/****************StrLen*********************/
size_t StrLen(const char *s)
{
	assert(s);
	if( ! *s )
	{
		return 0;
	}
	
	return StrLen(++s) + 1;
}

/****************StrCmp*********************/
int StrCmp(const char *s1, const char *s2)
{
 	assert(s1);
 	assert(s2);
 	
 	if( !(*s1)  || (*s1 - *s2) ) /* !(*s1) */
 	{
 		return *s1 - *s2;
 	}
 	
 	return StrCmp( ++s1, ++s2 );
} 

/****************StrCpy*********************/
char *StrCpy(char *dest, const char *src)
{
	assert(dest);
    assert(src);

	*dest = *src ;

	if( !(*src ) )
	{
		*dest = '\0' ;
		return dest;
	}
	return StrCpy(++dest , ++src) - 1;
	

}
/**********************StrCat*********************/
char *StrCat(char *dest, const char *src)
{
	assert(dest);
    assert(src);
    
    if( !( *dest ) )
    {  
    	return StrCpy(dest, src);
    }
   	else
    {
   		return StrCat(++dest, src ) - 1; 
    }
}

/************************StrStr*********************/
char *StrStr(const char *haystack, const char *needle)
{
	assert(haystack);
    assert(needle);
    
    if( ! strlen( needle ) )
    {
    	return (char*)haystack ;
    }
    
    if( strlen( haystack ) >= strlen( needle ) )
    {
    	return  !strncmp( haystack, needle, strlen( needle )) ?  
    							(char*)needle : StrStr(++haystack, needle) ;
    }
    
    else
    {
    	return NULL;
    }
}

/************************Fibonacci*********************/
int Fibonacci(int element_index)
{
	
	assert( element_index > -1 );
	
	if( 2 > element_index )
	{
		return 1; 
	}
	
	return Fibonacci( element_index - 1 ) +  
				(element_index > 1 ) * Fibonacci( element_index - 2 );

}
/************************FlipList*********************/
node_t *FlipList(node_t *node)
{
	node_t *prev = NULL, *front = NULL;
	assert(node);

	if( NULL == node || NULL == node->next )
	{
		return node;
	}
	
	prev = FlipList( node->next );
	front = node->next;
	
	front->next = node;
	node->next = NULL;
	
	return prev;
}

/************************AuxSortIntegers*********************/
static void AuxSortIntegers(stack_t* stack, int temp )
{		
	int temp_aux = 0;
		
	if ( StackIsEmpty( stack ) || temp >= *(int*)StackPeek( stack ) )
	{
		StackPush( stack, &temp );
		return;
	}
		
	temp_aux = *(int*)StackPeek( stack );
	StackPop( stack );
		
	AuxSortIntegers( stack, temp_aux );
		
	StackPush( stack, &temp_aux );
	return;
		
}



/************************SortIntegers*********************/
void SortIntegers(stack_t* stack)
{
	
	int temp = 0;
	
	assert(stack);
	
	if( StackIsEmpty( stack ) )
	{
		return;
	}
	
	temp = *(int*)StackPeek( stack );
	StackPop( stack );
	
	SortIntegers( stack );
	
	AuxSortIntegers( stack, temp );
	
	
}
/*
AuxSortIntegers(stack_t* stack, int temp )
	{
		
		int temp_aux = 0;
		
		if ( StackIsEmpty( stack ) || temp => *(int*)StackPeek( stack ) )
		{
			StackPush( stack, &temp );
			return;
		}
		
		temp_aux = *(int*)StackPeek( stack );
		StackPop( stack );
		
		AuxSortIntegers( stack, temp_aux );
		
		StackPush( stack, &temp_aux );
		return;
		
	}

*/


