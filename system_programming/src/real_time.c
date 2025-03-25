/***************************************
 * Author : Natty
 * Reviewer : ?
 * Date : 25 / 03 / 2025
 * Last update: 25 / 03 / 2025
 *****************************************/

#include <stdio.h>       
/*compile with gcc*/
#define IS_LITTLE_ENDIAN   ( *((char*)(&((int){1}))) == (1) )

int main()
{
   printf("Is Little Endian ? %s\n", IS_LITTLE_ENDIAN ? "Yes": "No");
    
    return 0;
}




