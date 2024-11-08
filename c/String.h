#ifndef __STRING_H__  /*__STRING_H__ */
#define __STRING_H__  /*__STRING_H__ */

#include <stddef.h> /* size_t*/

/**********StrLen function*********/
/* Return a length of a string */
/* Arguments: */
/* Return value: size of the string  */
/*Note: Undefined behaviour if str is NULL*/

size_t StrLen(const char* str);

/**********StrCmp function*********/
/* The StrCmp() compares two strings*/
/* character by character. If the */
/* strings are equal, the function returns 0.*/
/* Arguments:  */
/* Return value: 0  if strings are equal  */
/* 0> if the first non-matching character in str1 */
/* is greater (in ASCII) than that of str2 and <0 if vice versa*/

int StrCmp (const char* str1, const char* str2);

/**********StrCpy function*********/
/* Copy src string to dest string */
/* Arguments: 2-  pointers */
/* Return value: Pointer to the dest string */

char* StrCpy(char* dest, const char* src);

/**********StrnCpy function*********/
/* Copy "n" first characters from src to dest string */
/* Arguments:  */
/* Return value: Pointer to the dest string */

char* StrnCpy(char *dest, const char *src, size_t n);

/**********StrnCmp function*********/
/* Compares "n" first characters of two null-terminated arrays */
/* Arguments:  */
/* Return value: The sign of the difference between the values
                 of the first pair of characters (both interpreted as
                 unsigned char)that differ in the arrays being compared. */
/*Note: The behavior is undefined when access occurs past the end of
        either array lhs or rhs. The behavior is undefined when either lhs
        or rhs is the null pointer.*/
        
int StrnCmp( const char* lhs, const char* rhs, size_t n );

/**********StrCaseCmp function*********/
/* The StrCaseCmp() function compares s1 and s2 without sensitivity to case */
/* Arguments:  */
/* Return value: The sign of the difference between the values
                 of the first pair of characters that differ in
                 the arrays being compared. */
/*Note: The StrCaseCmp() function operates on null terminated strings.
        The string arguments to the function are expected to contain
         a null character ('\0') marking the end of the string. */
/*Note2: Both strings need to be unsigned char */         

int StrCaseCmp(const char* s1, const char* s2);

/**********StrChr function*********/
/* Finds the first occurrence of ch */
/* Arguments: str - pointer to the null-terminated byte string to be analyzed. 
               ch - character to search for*/
/* Return value: Pointer to the found character in str, or null pointer
                 if no such character is found */
/* Note: The terminating null character is considered
         to be a part of the string*/

char* StrChr(const char* str, int ch);

/***********StrDup function*********/
/* Duplication of the string src.
   The space for the new string is obtained as if the malloc was invoked. */
/* Return value: Returns a pointer to a null-terminated byte string */
/* Note: The returned pointer must be passed
         to free to avoid a memory leak.*/

char* StrDup(const char *src );

/***********StrCat function*********/
/* Appends a copy of the null-terminated byte string pointed to by src to the
   end of the null-terminated byte string pointed to by dest. The character
   src[0] replaces the null terminator at the end of dest.
   The resulting byte string is null-terminated. */
/* Return value: Returns a copy of dest */
/* Note: The behavior is undefined if the destination array is not large
         enough for the contents of both src and dest and the terminating
        null character, Or if the strings overlap, Or if either dest or src
        is not a pointer to a null-terminated byte string */
        
char* StrCat(char* dest, const char* src );

/***********StrnCat function*********/
/* Appends at most count characters from the character array pointed to by src,
  stopping if the null character is found, to the end of the null-terminated 
  byte string pointed to by dest. The character src[0] replaces the null
 terminator at the end of dest. The terminating null character is always
 appended in the end (so the maximum number of bytes the function 
 may write is count+1). */

/* Return value: Returns a copy of dest */
/* Note: The behavior is undefined if the destination array does not have
         enough space for the contents of both dest and the first count
          characters of src, plus the terminating null character.
          Or if either dest is not a pointer to a null-terminated byte
          tring or src is not a pointer to a character array. */
        
char* StrnCat(char* dest, const char* src, size_t n );

/***********StrStr function*********/
/* The strstr() function finds the first occurrence of string2 in string1.
   The function ignores the null character (\0) that ends string2 in
    the matching process.
    
  Return value: The function returns a pointer to the beginning of the first
              occurrence of string2 in string1. If string2 does not appear 
              in string1, the function returns NULL. If string2 points to
              a string with zero length, the function returns string1. */

char* StrStr(const char* s1, const char* s2 );

/***********StrSpn function*********/

/* Returns the length of the initial portion of s1 which consists only of
   characters that are part of s2. The null character (\0) that ends s2 is not
   considered in the matching process.
   
   Return Value: The return value is equal to the length of the initial
    substring of s1 that consists entirely of characters from s2. If s1
     begins with a character not in s2, the function returns 0. If all
      the characters in s1 are found in s2, the length of s1 is returned. */

size_t StrSpn(const char *s1, const char *s2);


#endif /*__STRING_H__ */
