/****************************************
* Autor : Natty
* Reviewr : Michael
* Date : 04 / 11 / 2024
* Last update: 04 / 11 / 2024
*****************************************/
#ifndef STRING_H
#define STRING_H
/**********StrLen function*********/
/* Return a length of a string */
/* Arguments: 1 const char* str */
/* Return value: size of the string  */

size_t StrLen(const char* str);

/**********StrCmp function*********/
/* The StrCmp() compares two strings
/* character by character. If the */
/*strings are equal, the function returns 0.*/
/* Arguments: The function takes two parameters: str1, str2 */
/* Return value: 0  if strings are equal  */
/* 0> if the first non-matching character in str1 */
/* is greater (in ASCII) than that of str2 and <0 if vice versa*/

int StrCmp (const char* str1, const char* str2);

#endif
