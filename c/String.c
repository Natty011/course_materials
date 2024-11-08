/****************************************
* Autor : Natty
* Reviewer : 
* Date : 04 / 11 / 2024
* Last update: 08 / 11 / 2024
*****************************************/

#include <stdio.h> /* while, for*/
#include <assert.h> /* assert */
#include <stddef.h> /* size_t*/
#include <string.h> /* strlen, strcmp, strncmp */
#include <stdlib.h> /* exit*/
#include <ctype.h> /* tolower */


#include "String.h" /* StrLen, StrCmp, StrCpy, StrnCpy, StrnCmp, StrCaseCmp */
                   /* StrChr, StrDup, StrCat, StrnCat, StrStr */
                   

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
    size_t i = 0;
    assert(str1);
    assert(str2);

    while (((*(str1 + i)) && (*(str2 + i))) && (*(str1 + i) == *(str2 + i)))
    {
       i++;
    }
    
    return *(str1 + i) - *(str2 + i);
}

/**********StrCpy function definition*********/

char* StrCpy(char* dest, const char* src)
{	
    int i = 0;
    char *p = dest;
    assert(dest);
    assert(src);

    for (i = 0; *(src + i) != '\0'; i++)
	{
	    *(p +i ) = *(src + i);    
	}
   *(p +i ) = '\0';
   
    return dest;
}


/**********StrnCpy function definition*********/

char *StrnCpy(char *dest, const char *src, size_t n)
{
 
    char* p = dest;
    size_t i = 0;

    assert(dest);
    assert(src);

    while ( i < n && *(src + i))
    {
       *(p +i) = *(src + i);
       i++;
    }
    /*To  add '\0' if necessary*/
    /*Do not overwrite data after arriving to dest array null char control*/
    while ( i != n && *(p + i) ) 
    {
       *(p +i) = '\0';
       i++;
    }
    
    return dest;
}
/**********StrnCmp function definition*********/

int StrnCmp( const char* lhs, const char* rhs, size_t n )
{
    size_t i = 0;
    assert(lhs);
    assert(rhs);
    while ( ( i < n ) && ((*lhs) && (*rhs)) && (*(lhs) == *(rhs)))
    {
       ++lhs;
       ++rhs;
       ++i;
    }
    
    return *(lhs) - *(rhs);
}

/**********StrCaseCmp function definition*********/

int StrCaseCmp(const char* s1, const char* s2)
{
     assert(s1);
     assert(s2);
    while (((*s1) && (*s2)) && (tolower(*s1) == tolower(*s2)))
    {
       ++s1;
       ++s2;
    }
    
    return tolower(*s1) - tolower(*s2);
}
/**********StrChr function definition*********/

char* StrChr(const char* str, int ch)
{
   const char* result = str;	
   unsigned char target = (unsigned char)ch;
   size_t len_str= strlen(result) + 1;
   size_t i = 0;
   
   assert(str);
   
   while (i <= len_str )
   { 
       if(*(result +i) == target)
        {
           return (char *)result +i;         
        }
        else 
        {
           ++i;
        } 
   }
   
   return NULL; /*The ch wasn't found */
}
/**********StrDup function definition*********/

char* StrDup(const char *src )
{
   size_t src_len = strlen(src);
   char* result = (char*)malloc(src_len + 1);
   if( NULL == result)
   {
      return NULL;
   }
   
   if( NULL == src)
   {
      return NULL;
   }
   
  strcpy(result, src);
  
  return result;
}
/**********StrCat function definition*********/

char* StrCat(char* dest, const char* src)
{
   size_t i = 0;
   size_t dest_len = strlen(dest);
   size_t src_len = strlen(src);
     
   assert(dest);
   assert(src);
   
   while ( i < src_len )
   {
      *(dest + dest_len +i) = *(src + i); 
      ++i;
   }
     
   *(dest + dest_len + i) = '\0';
   
   return dest;    
}

/**********StrnCat function definition*********/

char* StrnCat(char* dest, const char* src, size_t n )
{
   size_t i = 0;
   size_t dest_len = strlen(dest);
   size_t src_len = strlen(src);

   assert(dest);
   assert(src);
   
   if(n > src_len + 1)
   {
       puts("The input length to concatenate exceeds src string");
       exit(EXIT_FAILURE);
   }
   
   while ( i < n )
   {
      *(dest + dest_len +i) = *(src + i);
      ++i; 
   }
   
   *(dest + dest_len + i) = '\0';
   
   return dest;  
}

/**********StrStr function definition*********/

char* StrStr(const char* s1, const char* s2 )
{
   size_t i = 0;
   size_t s2_len = strlen(s2);
   int result = -1;
  
   assert(s1);
   assert(s2);
  
   if ( s2_len == 0 )
   {
       return (char*)s1;
   }
  
   while(*(s1 +i ))
   {
       if( strlen(s1+i) < (s2_len) ) /* s2 isn't a sub-string of s1 */
       {
           return NULL;
       }
      
       result = strncmp( s1+i, s2, s2_len);
      
       if( result == 0 ) /* s2 is a sub-string of s1 */
       {
           return (char*)s1+i;
       }
      
       ++i;
   }
  
   return NULL;
  
}

/**********StrSpn function definition*********/

size_t StrSpn(const char *s1, const char *s2)
{
    size_t sum = 0;
    int hist [129] = {0}; /* 128 Asci characthers */
    int i = 0;
    
    assert(s1);
    assert(s2);
    
    for ( ; i < 129 ; ++i ) /* Initialization of the hist*/
    {
        hist[i] = 0;
    } 
    
    while ( *s2 )
    {
        hist[(int)(*s2)] = 1; /* Occurrence of a characther in s2 */
        ++s2;
    } 
    
    while ( *s1 )
    {
        if ( hist[(int)(*s1)] == 1 ) 
        {
            ++sum;
            ++s1;
        }
        else
        {
            return sum;
        }
    }
    
    return sum; 
}

