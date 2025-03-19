/***************************************
 * Author : Natty
 * Reviewer : ?
 * Date : 18 / 03 / 2025
 * Last update: 19 / 03 / 2025
 *****************************************/

 #include <stdio.h>     /* fgets, sprintf, fopen*/
#include <stdlib.h>
#include <sys/ipc.h>    /* key_t, ftok*/
#include <sys/sem.h>    /*semctl, */
#include <string.h>     /*strstr, strcspn*/
#include <sys/types.h>
#include <unistd.h>
#include "utils.h"		 /* ExitIfBad, msg */

#define MAX_STRINGS (2)
#define BUFFER_SIZE (50)
#define MAX_COMMAND_SIZE (20)

#define TMP_DIR     "/tmp/"


union semun
{
    int val; /* Value for SETVAL */
    struct semid_ds *buf; /* Buffer for IPC_STAT, IPC_SET */
    unsigned short *array; /* Array for GETALL, SETALL */
}arg;

void GetInput(char buffer[],  char *argv);
void InitSemaphore(int semid);
int CreateKeyAndSemId(char sem_file_path[]);


int main(int argc, char *argv[])
{
    char sem_file_path[BUFFER_SIZE] = {0};

    if(2 != argc)
    {
        ExitIfBad(FALSE, "Wrong number of arguments\n");
    }

    GetInput(sem_file_path, argv[1]);

    /*puts(buffer);*/

    return 0;
}


void RunSemaphore(int semid)
{
    struct sembuf op;
    char command[MAX_COMMAND_SIZE] = {0};
    char undo_flag[MAX_COMMAND_SIZE] = {0};
    int num = 0;

    while(1)
    {
        fgets(command, MAX_COMMAND_SIZE, stdin);
        command[strcspn(command, '\n')] = '\0';
    }



}


int CreateKeyAndSemId(char sem_file_path[])
{
    key_t key = -1;
    FILE *file = NULL;
    int semid = -1;

    file = fopen(sem_file_path, "a");
    ExitIfBad( NULL != file, "File creation failed\n");
    ExitIfBad( 0 == fclose(file), "File closing failed\n");

    key = ftok(sem_file_path, 'A');
    ExitIfBad( -1 != key, "ftok failed\n");

    /* 0666 flag permisions for write/read to all users/processes*/
    semid = semget(key, 1, 0666); 

    if(-1 != semid)
    {
        return semid; /* the semaphore allready exist */
    }

    /* creat semid */
    semid = semget(key, 1, IPC_CREAT | 0666);
    ExitIfBad( -1 != semid, "semget failed\n");

    return semid;
}

void InitSemaphore(int semid)
{
    union semun arg;
    arg.val = 1; /*initial value - the critical code is available*/ 
    ExitIfBad( -1 != semctl(semid, 0, SETVAL, arg), "semctl failed\n");

}


void GetInput(char buffer[], char *argv)
{
    sprintf(buffer, "%s%s",TMP_DIR, argv );
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

