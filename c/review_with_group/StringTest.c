/****************************************
* Autor : Natty
* Reviewr : Rawan
* Date : 04 / 11 / 2024
* Last update: 05 / 11 / 2024
*****************************************/

#include <stdio.h> /*while, for*/
#include <assert.h> /* assert */
#include <stddef.h> /* size_t*/
#include "String.h" /*StrLen, StrCmp */
#include <string.h> /*strlen, strcmp */

/***************************function declaration**************************/
void TestStrLen();
void TestStrCmp ();

int main()
{   

    puts("'TestStrLen()'");
    TestStrLen();
    
    puts("'TestStrCmp()'");
    TestStrCmp();
    
    return 0;
}

/**********TestStrLen function *********/
/* Checks StrLen function by strlen() */
/*from the string library*/
/* Arguments: void */
/* Return value: void. massages according to the correctness */

void TestStrLen()
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

void TestStrCmp ()
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

