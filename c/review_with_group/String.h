#ifndef __STRING_H__  /*__STRING_H__ */
#define __STRING_H__ /*__STRING_H__ */

#include <stddef.h> /* size_t*/

/**********StrLen function*********/
/* Return a length of a string */
/* Arguments:
/* Return value: size of the string  */
/*Note: Undefined behaviour if str is NULL*/

size_t StrLen(const char* str);

/**********StrCmp function*********/
/* The StrCmp() compares two strings*/
/* character by character. If the */
/* strings are equal, the function returns 0.*/
/* Arguments: 
/* Return value: 0  if strings are equal  */
/* 0> if the first non-matching character in str1 */
/* is greater (in ASCII) than that of str2 and <0 if vice versa*/
/*Note: Undefined behaviour if str1 or str2 are NULL*/

int StrCmp (const char* str1, const char* str2);

#endif /*__STRING_H__ */
