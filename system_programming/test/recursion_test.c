/***************************************
* Author : Natty
* Reviewer : Matan
* Date : 22 / 01 / 2025
* Last update: 02 / 02 / 2025
*****************************************/

#include <stdio.h> 		/* printf, puts, qsort  */
#include <assert.h>
#include <string.h> 	/* strcpy, strcmp */
#include "recursion.h" 
#include "stack.h" 


#define BLACK        "\x1b[30m"
#define RED          "\x1b[31m"
#define GREEN        "\x1b[32m"
#define YELLOW       "\x1b[33m"
#define BLUE         "\x1b[34m"
#define MAGENTA      "\x1b[35m"
#define CYAN         "\x1b[36m"
#define WHITE        "\x1b[37m"

#define RESET        "\x1b[0m"

/* BACKGROUND COLOR */
#define BACK_BLACK   "\x1b[40m"
#define BACK_RED     "\x1b[41m"
#define BACK_GREEN   "\x1b[42m"
#define BACK_YELLOW  "\x1b[43m"
#define BACK_BLUE  	 "\x1b[44m"
#define BACK_MAGENTA "\x1b[45m"
#define BACK_CYAN 	 "\x1b[46m"
#define BACK_WHITE   "\x1b[47m"


#define DEBUG		"DEBUG MODE"
#define RELEASE		"RELEASE MODE"

#define MIN(a, b)		((a > b ) ? b : a )
#define MAX(a, b)		((a > b ) ? a : b )

/*extern int destroy_check;*/
/***************struct and enum declaration *******/


/*
typedef enum
{
	
	SUCCESS = 0,
	OPERATION_FAIL = 1
	
}bst_result_t;
*/

typedef enum
{
	
	FALSE = 0,
	TRUE = 1
	
}result_t;

/***************End of struct and enum declaration *******/

/***************************function declaration**************************/
static void TestRecursion(void);
static int TestStrLen(void);
static int TestStrCmp(void);

/***************************End of function declaration******************/

/******************static functions definition**********************/

/******************End of static functions definition**********************/


int main ()
{

	char* mode = RELEASE;
	char* background =  BACK_MAGENTA;	
	
	#ifndef NDEBUG
		mode = DEBUG;
		background =  BACK_YELLOW;
	#endif

	puts(BLUE"====================================================="RESET);
	printf("%sTEST: %s "RESET" \n", background,  mode);
   	puts(BACK_BLUE"'TestRecursion()'"RESET);
    TestRecursion();
    
	puts(BLUE"====================================================="RESET);

	return 0;
}

/********************  TestRecursion  ****************************/
static void TestRecursion(void)
{	
	
	int flag = FALSE;

	/*puts(RED);*/
	
	puts("=====================================================");
    puts("'TestStrLen()'");
    flag = TestStrLen();
    puts("=====================================================");
	
	puts("'TestStrCmp()'");
    flag = TestStrCmp();
    puts("=====================================================");
    
    
	if( !flag ) 
	{
		puts(RESET);		
		puts(BACK_BLUE"Test: Success"RESET);

	}
	
	else
	{
		puts(BACK_YELLOW"Test: Failure"RESET);	
	}
	
}

/**********TestStrLen function *********/
/* Checks StrLen function by strlen() */
/*from the string library*/
/* Arguments: void */
/* Return value: void. massages according to the correctness */

static int TestStrLen(void)
{
    int result = 0;	
    const char* str1 = "ab\n";
    const char str2[] = "cd";
    const char str3 [] = {'e', 'f',' ', '\0', 'd'};
    const char str4 [] = "";
    char str5 [] = "3%$#@!^&*(dn\t\0";
    
    result = (strlen(str1) == StrLen(str1)) && (strlen(str2) == StrLen(str2)) 
            && (strlen(str3) == StrLen(str3)) && (strlen(str4) == StrLen(str4))
              && (strlen(str5) == StrLen(str5));
    			
    
    if (result)
    {
       puts("'StrLen()' Function works great");
    }  
    
    else
    {
       puts("'StrLen()' Function failed");
    }
    return !result;
}

/**********TestStrCmp function *********/
/* Checks StrCmp function by strcmp() */
/*from the string library*/
/* Arguments: void */
/* Return value: void. massages according to the correctness */

static int TestStrCmp (void)
{
    int flag = FALSE;
    
    const char* str1 = "ab\n";
    const char str11 []= "ab\n";
    const char str2[] = "cd5";
    char str22[] = {'c','d' ,'\0','0'};
    char str3 [] = "3%$#@!^&*(dn\t\0";
    char str33 [] = "3%$#@!^&*(dn\t+\0";
    
    if (strcmp(str1, str11) != StrCmp(str1, str11))
    {
       puts("'StrCmp()' Function failed at an identicals' strings comparison");
       flag = TRUE;
    }
    
    if ((strcmp(str2, str22) <= 0)  && (StrCmp(str2, str22) <= 0))
    {
       puts("'StrCmp()' Function failed in case str1 > str2");
       flag = TRUE;
    }
    
    
    if ((strcmp(str3, str33) >= 0) && (StrCmp(str3, str33) >= 0))
    {
        puts("'StrCmp()' Function failed in case str1 < str2");
        flag = TRUE;
    }
    
    if( !flag )
    {
        puts("'StrCmp()' Function works great");
    }
    
   return flag;
}


