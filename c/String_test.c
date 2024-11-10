/****************************************
* Autor : Natty
* Reviewer : 
* Date : 04 / 11 / 2024
* Last update: 08 / 11 / 2024
*****************************************/
#define _POSIX_C_SOURCE 200809L /* strdup */

#include <stdio.h> /* while, for*/
#include <assert.h> /* assert */
#include <stddef.h> /* size_t*/
#include <string.h> /* strlen, strcmp, strcpy, strncpy, strncmp, strchr */
                   /* strdup, strcat, strncat, strstr, strspn */
#include <stdlib.h> /* exit*/
#include <strings.h> /* strcasecmp */

#include "String.h" /* StrLen, StrCmp, StrCpy */

#define SIZE_BUFFER 100

/**********************function declaration***********************/

static void TestStrLen(void);
static void TestStrCmp(void);
static void TestStrCpy(void);
static void TestStrnCpy(void);
static void TestStrnCmp(void);
static void TestStrCaseCmp(void);
static void TestStrChr(void);
static void TestStrDup(void);
static void TestStrCat(void);
static void TestStrnCat(void);
static void TestStrStr(void);
static void TestStrSpn(void);

/**********************End of function declaration**************/

int main(void)
{   
    puts("=====================================================");
    puts("'TestStrLen()'");
    TestStrLen();
    puts("=====================================================");
    
    puts("'TestStrCmp()'");
    TestStrCmp();
    puts("=====================================================");
    
    puts("'TestStrCpy()'");
    TestStrCpy();
    puts("=====================================================");
    
    puts("'TestStrnCpy()'");
    TestStrnCpy();
    puts("=====================================================");
    
    puts("'TestStrnCmp()'");
    TestStrnCmp();
    puts("=====================================================");  
    
    puts("'TestStrCaseCmp()'");
    TestStrCaseCmp();
    puts("=====================================================");
    
    puts("'TestStrChr()'");
    TestStrChr();
    puts("=====================================================");
    
    puts("'TestStrDup()'");
    TestStrDup();
    puts("=====================================================");
    
    puts("'TestStrCat()'");
    TestStrCat();
    puts("=====================================================");
    
    puts("'TestStrnCat()'");
    TestStrnCat();
    puts("=====================================================");
    
    puts("'TestStrStr()'");
    TestStrStr();
    puts("=====================================================");
    
    puts("'TestStrSpn()'");
    TestStrSpn();
    puts("=====================================================");
      
    return 0;
}

/**********TestStrLen function *********/
/* Checks StrLen function by strlen() */
/*from the string library*/
/* Arguments: void */
/* Return value: void. massages according to the correctness */

static void TestStrLen(void)
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
    return;
}

/**********TestStrCmp function *********/
/* Checks StrCmp function by strcmp() */
/*from the string library*/
/* Arguments: void */
/* Return value: void. massages according to the correctness */

static void TestStrCmp (void)
{
    const char* str1 = "ab\n";
    const char str11 []= "ab\n";
    const char str2[] = "cd5";
    char str22[] = {'c','d' ,'\0','0'};
    char str3 [] = "3%$#@!^&*(dn\t\0";
    char str33 [] = "3%$#@!^&*(dn\t+\0";
    
    
    if (strcmp(str1, str11) != StrCmp(str1, str11))
    {
       puts("'StrCmp()' Function failed at an identicals' strings comparison");
    }
    
    else if ((strcmp(str2, str22) <= 0)  && (StrCmp(str2, str22) <= 0))
    {
       puts("'StrCmp()' Function failed in case str1 > str2");
    }
    
    else if ((strcmp(str3, str33) >= 0) && (StrCmp(str3, str33) >= 0))
    {
        puts("'StrCmp()' Function failed in case str1 < str2");
    }
    
    else
    {
        puts("'StrCmp()' Function works great");
    }
    
   return;
}

/**********TestStrCpy function *********/
/* Checks StrCpy function by strcpy() */
/*from the string library*/
/* Arguments: void */
/* Return value: void. massages according to the correctness */

static void TestStrCpy(void)
{	
    int i = 0;
    const char* src= "#%$#@!^&*(dn";
    char dest[13] = "323t4d";
    char dest1[13] = "gf43";
    
    char* DestCpy= StrCpy(dest, src);
    char* destcpy= strcpy(dest1, src);

	for (i = 0; *(dest + i) != '\0'; i++)
	{
	    if( *(DestCpy +i ) != *(destcpy + i))
	        {
	            puts("'StrCpy()' Function failed");
	        }
	}

    puts("'StrCpy()' Function works great");
    return;
}

/**********TestStrCpy function *********/
/* Checks StrnCpy function by strncpy() */
/*from the string library*/
/* Arguments: void */
/* Return value: void. massages according to the correctness */

static void TestStrnCpy(void)
{	
    size_t i = 0;
    const char* src = "hi";
    char dest[7] = "abcdef"; 
    char dest1[7] = "abcdef"; 
    char* DestCpy = StrnCpy(dest, src, 4);
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wstringop-truncation"
    char* destcpy = strncpy(dest1, src, 4);
    #pragma GCC diagnostic pop
 
    for ( ; i < sizeof(dest) ; i++)
	{

            if( *(DestCpy +i ) != *(destcpy + i))
	        {
	            puts("'StrnCpy()' Function failed");
	        }
	}

    puts("'StrnCpy()' Function works great");
    
    return;
}

/**********TestStrnCmp function *********/
/* Checks StrnCmp function by strncmp() */
/*from the string library*/
/* Arguments: void */
/* Return value: void. massages according to the correctness */

static void TestStrnCmp(void)
{
    const char* str1 = "ab";
    const char str11 []= "ab";
    const char str2[] = "cd5";
    char str22[] = "cc5";
    char str3 [] = "3%$#@!^";
    char str33 [] = "3%$#@!^A";
    

    
    if (strncmp(str1, str11, 3) != StrnCmp(str1, str11, 3))
    {
       puts("'StrnCmp()' Function failed at an identicals' strings comparison");
    }
    
    else if (StrnCmp(str2, str22, 2) <= 0)
    {
       puts("'StrnCmp()' Function failed in case str1 > str2");
    }
    
    else if (StrnCmp(str3, str33, 8) >= 0)
    {
        puts("'StrnCmp()' Function failed in case str1 < str2");
    }
    
    else
    {
        puts("'StrnCmp()' Function works great");
    }

   return;
}

/**********TestStrCaseCmp function *********/
/* Checks StrCaseCmp function by strcasecmp() */
/*from the strings library*/
/* Arguments: void */
/* Return value: void. massages according to the correctness */

static void TestStrCaseCmp(void)
{
    const char* str1 = "AB";
    const char str11 []= "ab";
    const char str2[] = "cD5";
    char str22[] = "cc5";
    char str3 [] = "3%$#@!^a";
    char str33 [] = "3%$#@!^B";
    

    if (strcasecmp(str1, str11) != StrCaseCmp(str1, str11))
    {
       puts("'StrCaseCmp()' Function failed at an identicals' strings comparison");
    }
    
    else if (StrCaseCmp(str2, str22) <= 0)
    {
       puts("'StrCaseCmp()' Function failed in case str1 > str2");
    }
    
    else if (StrCaseCmp(str3, str33) >= 0)
    {
        puts("'StrCaseCmp()' Function failed in case str1 < str2");   
    }
    
    else
    {
        puts("'StrCaseCmp()' Function works great");
    }
       
   return;
}

/**********TestStrChr function *********/
/* Checks StrChr function by strchr() */
/*from the strings library*/
/* Arguments: void */
/* Return value: void. massages according to the correctness */

static void TestStrChr(void)
{
    const char *str = "Try not. Do, or do not. There is no tpryp.";
    char target = 'p';
    char* result1 = StrChr(str, target);
    char* result2 = strchr(str, target);
    
    if (strcmp(result1, result2))
    {
       puts("'StrChr()' Function failed at middles' strings comparison");
    }
    
    else if (strcmp(StrChr(str, '\0') , strchr(str, '\0')))
    {
       puts("'StrChr()' Function failed in the terminating null character");
    }
    
    else if ((NULL != StrChr(str, 'F')) || (NULL != strchr(str, 'F')))
    {
       puts("'StrChr()' Function failed at character without occurrence");
    }
    
    else
    {
        puts("'StrChr()' Function works great");
    }
    
    return;
}

/**********TestStrDup function *********/
/* Checks StrDup function by strdup() */
/*from the strings library and macro _POSIX_C_SOURCE 200809L*/
/* Arguments: void */
/* Return value: void. massages according to the correctness */

static void TestStrDup(void)
{
    const char* str = "_POSIX_C_SOURCE 200809L";
    char* result1 = StrDup(str);
    char* result2 = strdup(str);
    
    if (NULL == result1)
    {
    puts("StrDup cannot reserve storage");
    }
    
    if (NULL == result2)
    {
    puts("strdup cannot reserve storage");
    }
    
    if (strcmp(result1, result2))
    {
       puts("'StrDup()' Function failed at the Duplication of 'src' string");
    }
    
    else
    {
        puts("'StrDup()' Function works great");
    }
    
    free(result1);
    free(result2);
    
    return;
}

/**********TestStrCat function *********/
/* Checks StrCat function by strcat() */
/*from the strings library*/
/* Arguments: void */
/* Return value: void. massages according to the correctness */

static void TestStrCat(void)
{
    char buffer1[SIZE_BUFFER] = "computer";  /* SIZE_BUFFER == 100 */
    char buffer2[SIZE_BUFFER] = "computer";  /* SIZE_BUFFER == 100 */
     
    char* result1 = StrCat( buffer1, " program" );
    char* result2 = strcat( buffer2, " program" );
    
    char* result3 = StrCat( buffer1, " haha45" );
    char* result4 = strcat( buffer2, " haha45" );
    
    char str[50] = "World!";  
    char* result5 = StrCat( buffer1, str );
    char* result6 = strcat( buffer2, str );
    
    if (strcmp(result1, result2))
    {
       puts("'StrCat()' Function failed at the concatenation of 'src' string");
    }
    
    else if (strcmp(result3, result4))
    {
       puts("'StrCat()' Function failed at the concatenation of 'src' string");
    }
    
    else if (strcmp(result5, result6))
    {
       puts("'StrCat()' Function failed at the concatenation of 'src' string");
    }
    
    else
    {
        puts("'StrCat()' Function works great");
    }
    
    return;
}

static void TestStrnCat(void)
{
    char buffer1[SIZE_BUFFER] = "computer";  /* SIZE_BUFFER == 100 */
    char buffer2[SIZE_BUFFER] = "computer";  /* SIZE_BUFFER == 100 */
    
    #pragma GCC diagnostic push
    /* disable warning of strncat in diffrent length input */
    #pragma GCC diagnostic ignored "-Wstringop-truncation" 
    /* disable warning of strncat for most characther of src length input */
    #pragma GCC diagnostic ignored "-Wstringop-overflow="  
    
    char* result1 = StrnCat( buffer1, " program", strlen(" program"));
    char* result2 = strncat( buffer2, " program", strlen(" program"));
    
    char* result3 = StrnCat( buffer1, " haha45", 7 );
    char* result4 = strncat( buffer2, " haha45", 7 );
    
    char str[50] = "World!";  
    char* result5 = StrnCat( buffer1, str, 3);
    char* result6 = strncat( buffer2, str, 3);
    
    #pragma GCC diagnostic pop
    
    if (strcmp(result1, result2))
    {
       puts("'StrCat()' Function failed at the concatenation of 'src' string");
    }
    
    else if (strcmp(result3, result4))
    {
       puts("'StrnCat()' Function failed at the concatenation of 'src' string");
    }
    
    else if (strcmp(result5, result6))
    {
       puts("'StrnCat()' Function failed at the concatenation of 'src' string");
    }
    
    else
    {
        puts("'StrnCat()' Function works great");
    }
    
    return;
}

/**********TestStrStr function *********/

static void TestStrStr(void)
{
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
    }
    
    else if (strcmp(result3, result4))
    {
       puts("'StrStr()' Function failed  when s2 is a zero length sub-string");
    }
    
    else if ((NULL != result5) || (NULL != result6))
    {
       puts("'StrStr()' Function failed wheb s2 isn't a sub-string of s1");
    }
    
    else
    {
        puts("'StrStr()' Function works great");
    }
  
  return;
}

/**********TestStrSpn function *********/

static void TestStrSpn(void)
{

   char s1[] = "9299h"; 
   char s11[] = "929@901fA"; 
   char s111[] = "!929@901fA"; 

   char s2[] = "12@34f567A890";
   
   if ( StrSpn (s1,s2) != strspn (s1,s2) )
    {
       puts("'StrSpn()' failed in counting an initial portion of s1");
    }
    
    else if (StrSpn (s11,s2) != strspn (s11,s2))
    {
       puts("'StrSpn()' failed in counting the entire characthers of s1");
    }
    
    else if (StrSpn (s111,s2) != strspn (s111,s2))
    {
       puts("'StrSpn()' failed in counting non exist an initial portion of s1");
    }
    
    else
    {
        puts("'StrSpn()' Function works great");
    }

   return;
}

