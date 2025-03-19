/***************************************
 * Author : Natty
 * Reviewer : ?
 * Date : 18 / 03 / 2025
 * Last update: 19 / 03 / 2025
 *****************************************/

#include <stdio.h>       /* fgets, sprintf, fopen, sscanf, remove, fclose*/
#include <sys/ipc.h>     /* key_t, ftok*/
#include <sys/sem.h>     /*semctl, semop, semget */
#include <string.h>      /*strstr, strcspn*/
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
void RunSemaphore(int semid, char *sem_file_path);

int main(int argc, char *argv[])
{
    char sem_file_path[BUFFER_SIZE] = {0};
    int semid = -1;

    if(2 != argc)
    {
        ExitIfBad(FALSE, "Wrong number of arguments\n");
    }

    GetInput(sem_file_path, argv[1]);

    semid = CreateKeyAndSemId(sem_file_path);

    RunSemaphore(semid, sem_file_path);

    return 0;
}


void RunSemaphore(int semid, char *sem_file_path)
{
    struct sembuf op;
    char command[MAX_COMMAND_SIZE] = {0};
    char undo_flag[MAX_COMMAND_SIZE] = {0};
    int number = 0;
    int sem_value = 0;

    while(1)
    {
        printf("> ");
        fgets(command, MAX_COMMAND_SIZE, stdin);
        command[strcspn(command, "\n")] = '\0';

        /* Decreasing number */
        if(sscanf(command, "D %d %s", &number, undo_flag )>= 1)
        {
            op.sem_num = 0;
            op.sem_op = -number; 
            op.sem_flg = (NULL != strstr(undo_flag, "undo") ) ? SEM_UNDO : 0;
            
            ExitIfBad( -1 != semop(semid, &op, 1),"semop failed\n" );
            printf("Semaphore decreased by %d (UNDO: %s)\n",
                     number, (op.sem_flg ? "ON" : "OFF"));

        }

        /* Increasing number */
        else if(sscanf(command, "I %d %s", &number, undo_flag )>= 1)
        {
            op.sem_num = 0;
            op.sem_op = number; 
            op.sem_flg = (NULL != strstr(undo_flag, "undo") ) ? SEM_UNDO : 0;
            
            ExitIfBad( -1 != semop(semid, &op, 1),"semop failed\n" );

            printf("Semaphore increased by %d (UNDO: %s)\n",
                     number, (op.sem_flg ? "ON" : "OFF"));

        }

        /* view number */
        else if('V' == command[0])
        {
           /* sem_value = semctl( semid, 0, GETVAL);*/
            ExitIfBad( -1 != (sem_value = semctl( semid, 0, GETVAL)), "semctl failed\n");

            printf("Semaphore value: %d\n", sem_value);
        }
        /* exit and removing the semophore*/

        else if('X' == command[0])
        {
            /*semctl(semid, 0, IPC_RMID);*/
            ExitIfBad( -1 != (semctl(semid, 0, IPC_RMID)), "semctl failed\n");

            printf("Semaphore removed and exiting.\n");

            /*remove(sem_file_path);*/ /* optionally */
            break;
        }

        else
        {
            ExitIfBad(FALSE,"Invalid command\n");
        }
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
    semid = semget(key, 1, 0666); /* 1 is nsems*/

    if(-1 != semid)
    {
        return semid; /* the semaphore allready exist */
    }

    /* creat semid */
    semid = semget(key, 1, IPC_CREAT | 0666);
    ExitIfBad( -1 != semid, "semget failed\n");

    InitSemaphore(semid);

    return semid;
}

void InitSemaphore(int semid)
{
    union semun arg;
    arg.val = 1; /*initial value - the critical code is available for the
                first process that calling the program */ 
    /* semnum = 0 is the index of the semaphore in the group set */
    ExitIfBad( -1 != semctl(semid, 0, SETVAL, arg), "semctl failed\n");

}


void GetInput(char buffer[], char *argv)
{
    sprintf(buffer, "%s%s",TMP_DIR, argv );
}


