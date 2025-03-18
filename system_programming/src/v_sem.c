/***************************************
 * Author : Natty
 * Reviewer : Sauser
 * Date : 16 / 03 / 2025
 * Last update: 17 / 03 / 2025
 *****************************************/

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include "utils.h"		 /* ExitIfBad, msg */

#define MAX_STRINGS (20)
#define BUFFER_SIZE (501)
#define TMP_STR     "/tmp/"

int main(int argc, char *argv[])
{
   /*
   1.  GetInput( buffer, size_t buff_len, char *argv[1])
    Get from user file name string for creating semaphore
      with this string id.
    2. Create, with function, a this file name in /tmp/file_name
    3. If the file was created seccessfully, begin an infinite loop
        for getting commands from another terminal.

    4. the aplication needs to support several commands that the user
        enters after he runs another instase of the application 
        in another terminal window. 

   */
    return 0;
}


/*

1st function:
void GetInput(char buffer[], size_t buff_len, char *argv[1])
{
    1. unite the file name string  with the string "/tmp/".
    2. create a file_name with path "/tmp/file_name"
        by using 'fopen', if the file not created.
        2.1 check if fopen secessed. (ExitIfBad)

    3. close the file using fclose.
        3.1. check if fopen secessed. (ExitIfBad)
}

*/


/*

2nd function:
void GetInput(char buffer[], size_t buff_len, char *argv[1])
{
    1. unite the file name string  with the string "/tmp/".
    2. create a file_name with path "/tmp/file_name"
        by using 'fopen', if the file not created.
        2.1 check if fopen secessed. (ExitIfBad)

    3. close the file using fclose.
        3.1. check if fopen secessed. (ExitIfBad)
}

*/
