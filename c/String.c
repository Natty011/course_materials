/****************************************
* Autor : Natty
* Reviewr : Rawan
* Date : 04 / 11 / 2024
* Last update: 05 / 11 / 2024
*****************************************/

#include <stdio.h> /*while, for*/
#include <assert.h> /* assert */
#include <stdint.h>/*size_t*/
#include <stddef.h> /* size_t*/
#include "String.h" /*Declerations of StrLen, StrCmp */

/**********StrLen function definition*********/
size_t StrLen(const char* str)
{
    size_t i = 0;
    assert(str);
    
    while (*(str+i))
    {
       i++;
    }  
    return i;
}

/**********StrCmp function definition*********/
int StrCmp (const char* str1, const char* str2)
{
    int result = 0;	
    size_t i = 0;
    assert(str1);
    assert(str2);

    while (((*(str1 + i)) && (*(str2 + i))) && (*(str1 + i) == *(str2 + i)))
    {
       i++;
       continue;
    }
    
    result = *(str1 + i) - *(str2 + i);
    if (result < 0)
    {
    	return -1;
    }
    
    else if (result > 0)
    {
       return 1;
    }
    
    return result; /* result == 0 */
}
