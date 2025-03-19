/***************************************
 * Author : Natty
 * Reviewer : Sauser
 * Date : 16 / 03 / 2025
 * Last update: 17 / 03 / 2025
 *****************************************/

#include <stdio.h> /* fgets*/
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include "utils.h"		 /* ExitIfBad, msg */

#define MAX_STRINGS (2)
#define BUFFER_SIZE (50)
#define MAX_COMMAND_SIZE (20)

#define TMP_DIR     "/tmp/"

void GetInput(char buffer[], size_t buff_len, char argv[]);


int main(int argc, char *argv[])
{
    char buffer[BUFFER_SIZE] = {0};
    char command[MAX_COMMAND_SIZE] = {0};

    if(2 != argc)
    {
        ExitIfBad(FALSE, "Wrong number of arguments\n");
    }

    GetInput(buffer, BUFFER_SIZE, argv[1]);


    return 0;
}

void GetInput(char buffer[], size_t buff_len, char argv[])
{
    snprintf(buffer, buff_len, "%s%s",TMP_DIR, argv[1] );
}
    

 /*
   1.  int GetInput( buffer, size_t buff_len, char *argv[1])

    Get from user file name string for creating semaphore
      with this string id.

    2. Create, with function, a this file name in /tmp/file_name

    3. If the file was created seccessfully, begin an infinite loop
        for getting commands from another terminal.

    4. the aplication needs to support several commands that the user
        enters after he runs another instase of the application 
        in another terminal window. 

   */


/*

1st function: return if the file created secessfully  
then get the semid, and before compare the argv[1] of the 
other process with ...
int GetInput(char buffer[], size_t buff_len, char *argv[1])
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

2nd function: return if the the key and semid created secessfully.

int CreateKeyAndSemId(char buffer[], char *key_and_id[])
{
    1. using the path in the buffer to create key and semid.
    2. by using ftok and semget
    3. enter key and semid into array ' key_and_id '
        in order not to create again key and semid

}

*/


/*

3nd function: RunSemaphore().

int RunSemaphore(char command[], char *key_and_id[])
{
    0. using while(1) to scan the command and handle it according 
        to his data. 
    1. get the command by using 'fgets' and store it in command array
    2. divide to differnt cases the result from the command.
    3. implement the result of each case by using 'semop' function
        or 'semctl' function.  

}

*/

