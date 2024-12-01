#ifndef __WS10_H__  /*__WS10_H__ */
#define __WS10_H__  /*__WS10_H__ */

#include <stddef.h> /* size_t*/


/* 
   DESCRIPTION: The Memset() function fills the first n bytes of the
                memory area pointe d to by s with the constant byte c.
   RETURN VALUE: The Memset() function returns a pointer to the 
                  memory area s. 
   NOTE: 1) The behavior is undefined if access occurs beyond
            the end of the 's' array.
         2) The behavior is undefined if 's' is a null pointer.
*/
void *Memset(void *s, int c, size_t n);

/* 
   DESCRIPTION: The  Memcpy()  function  copies  n bytes from
                memory area src to memory area dest. The memory
                 areas must not overlap. 
   RETURN VALUE: The Memcpy() function returns a pointer to dest.
   NOTE: 1) The behavior is undefined if access occurs beyond
            the end of the dest array. 
         2) If the objects overlap the behavior is undefined. 
         3)The behavior is undefined if either dest or src
           is an invalid or null pointer.
*/
void *Memcpy(void *dest, const void *src, size_t n);


/* 
   DESCRIPTION:  The  Memmove()  function  copies n bytes from
                 memory area src to memory area dest.
                 The memory areas may overlap.
   RETURN VALUE: The Memmove() function returns a pointer to dest.
   NOTE: 1) The behavior is undefined if access occurs beyond
            the end of the dest array. 
         2)The behavior is undefined if either dest or src
           is an invalid or null pointer.
*/

void *Memmove(void *dest, const void *src, size_t n);


#endif /*__WS10_H__ */


