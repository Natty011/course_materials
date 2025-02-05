/***************************************
* Author : Natty
* Reviewer : Matan
* Date : 03 / 03 / 2025
* Last update: 03 / 02 / 2025
*****************************************/
#include <stdio.h>
#include <string.h> 	/* isspace, strlen */

#include <assert.h> 	/* assert */
#include <stdlib.h> 	/* malloc, free */
#include "recursion.h" 

#define UNUSED( var )       ( (void)var )
#define UNUSED_1( var )			( __attribute__((unused))var )

/****************struct and enum declaration*********************/
/***************End of struct and enum declaration *******/
/***********Functions declaration*******/

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
 	
 	if( !(*s1) && *s1 == *s2 )
 	{
 		StrCmp( ++s1, ++s2 ); 
 	}

	return *s1 - *s2;
} 







