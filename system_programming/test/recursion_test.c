/***************************************
* Author : Natty
* Reviewer : David
* Date : 05 / 02 / 2025
* Last update: 06 / 02 / 2025
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

#define SIZE_BUFFER 100

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
static int TestStrCpy(void);
static int TestStrCat(void);
static int TestStrStr(void);
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
    
    puts("'TestStrCpy()'");
    flag = TestStrCpy();
    puts("=====================================================");
    
    puts("'TestStrCat()'");
    flag = TestStrCat();
    puts("=====================================================");
    
    puts("'TestStrStr()'");
    flag = TestStrStr();
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

/**********TestStrCpy function *********/
/* Checks StrCpy function by strcpy() */
/*from the string library*/
/* Arguments: void */
/* Return value: void. massages according to the correctness */

static int TestStrCpy(void)
{	
    int i = 0;
    int flag = FALSE;
    const char* src= "#%$#@!^&*(dn";
    /*const char* src= "ab";*/
    char dest[13] = "323t4d";
    char dest1[13] = "gf43";
    
    char* DestCpy= StrCpy(dest, src);
    char* destcpy= strcpy(dest1, src);

	for (i = 0; *(dest + i) != '\0'; i++)
	{
	    if( *(DestCpy +i ) != *(destcpy + i))
	        {
	            puts("'StrCpy()' Function failed");
	            flag = TRUE;
	        }
	}

    puts("'StrCpy()' Function works great");
    return flag ;
}

/**********TestStrCat function *********/
/* Checks StrCat function by strcat() */
/*from the strings library*/
/* Arguments: void */
/* Return value: void. massages according to the correctness */

static int TestStrCat(void)
{
    
    int flag = FALSE;
    
    char buffer1[SIZE_BUFFER] = "computer";  /* SIZE_BUFFER == 100 */
    char buffer2[SIZE_BUFFER] = "computer";  /* SIZE_BUFFER == 100 */
     
    char* result1 = StrCat( buffer1, " program" );
    char* result2 = strcat( buffer2, " program" );
    
    char* result3 = StrCat( buffer1, "haha45" );
    char* result4 = strcat( buffer2, "haha45" );
    
    char str[50] = "World!";  
    char* result5 = StrCat( buffer1, str );
    char* result6 = strcat( buffer2, str );
    
    if (strcmp(result1, result2))
    {
       puts("TEST1: 'StrCat()' Function failed at the concatenation of 'src' string");
	   flag = TRUE;       
    }
    
    if (strcmp(result3, result4))
    {
       puts("TEST2: 'StrCat()' Function failed at the concatenation of 'src' string");
       flag = TRUE;
    }
    
    if (strcmp(result5, result6))
    {
       puts("TEST3: 'StrCat()' Function failed at the concatenation of 'src' string");
	   flag = TRUE;       
    }
    
    else
    {
        puts("'StrCat()' Function works great");
    }
    
    return flag;
}

/**********TestStrStr function *********/

static int TestStrStr(void)
{
    
   int flag = FALSE;
   char *s1 = "needle in a haystack";
   char *s2 = "haystack";
   char *result1 = StrStr(s1,s2);
   char *result2 = strstr(s1,s2);
   
   char *result3 = StrStr(s1,""); /* s2 is zero length */
   char *result4 = strstr(s1,"");
   
   char *result5 = StrStr(s1,"f"); /* s2 isn't a sub-string */
   char *result6 = strstr(s1,"f");
   
   
   if (strcmp(result1, result2) )
    {
       puts("'StrStr()' Function failed to found an exists sub-string");
       flag = TRUE;       
    }
    
    if (strcmp(result3, result4))
    {
       puts("'StrStr()' Function failed  when s2 is a zero length sub-string");
	   flag = TRUE;           
    }
    
    if ((NULL != result5) || (NULL != result6))
    {
       puts("'StrStr()' Function failed wheb s2 isn't a sub-string of s1");
	   flag = TRUE;       
    }
    
    else
    {
        puts("'StrStr()' Function works great");
    }
  
  return flag;
}




