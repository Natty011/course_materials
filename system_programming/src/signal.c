/***************************************
 * Author : Natty
 * Reviewer : ???
 * Date : 05 / 10 / 2025
 * Last update: 11 / 03 / 2025
 *****************************************/

#ifdef PRINTS
#endif
#define _GNU_SOURCE
#include <signal.h>	   /* sigaction */
#include <stdio.h>	   /* perror  */
#include <stdlib.h>	   /* exit, EXIT_SECCESS, EXIT_FAILURE */
#include <string.h>	   /* strcmp */
#include <unistd.h>	   /* fork, execv*/
#include <sys/wait.h>  /* wait */
#include <sys/types.h> /* pid_t */

pid_t child_pid; 
int counter = 3;

/*
static int is_on_child = 0;
static int is_on_parent = 0;
*/
static char *msg[] = {"fork failed\n", "fgets failed\n", "strtok failed\n",
	"execvp failed\n", "Too many arguments\n",
 "Empty line is not allowed\n", "SIGINT terminated the proccess\n"};


#define UNUSED(var) ((void)var)

#define BUFFER_SIZE (501)
#define MAX_STRINGS (20)

void ExitIfBad(int is_good, const char *msg);

enum
{
	BAD_PID = -1,
	SUCCESS = 0,
	FAIL = 1
};

enum
{
	FALSE = 0,
	TRUE = 1
};


void handle_signal(int sig)
 {
    if (sig == SIGUSR2)
     {
        printf("Parent: Received SIGUSR2 from child, sending SIGUSR1\n");
        kill(child_pid, SIGUSR1);
    } 
    else if (sig == SIGUSR1)
    {
        printf("Child: Received SIGUSR1 from parent, sending SIGUSR2\n");
        kill(getppid(), SIGUSR2);
    }
}

void child_process()
 {
    struct sigaction sa;
    sa.sa_handler = handle_signal;

    sigaction(SIGUSR1, &sa, NULL);

    if( 0!= counter)
    {
        --counter;

        if( 0 == counter)
    {
        exit(0);
    }
    while (1 && 0!= counter)
    {
        sleep(1);

    
		--counter;
		if( 0== counter)
		{
			exit(0);
		}
			--counter;
			printf("Child: Sending SIGUSR2 to parent\n");
			if( 0!= counter)
			{    
				--counter;

				kill(getppid(), SIGUSR2);
			}
	}
	}
 }


int main() 
{
    struct sigaction sa;
    sa.sa_handler = handle_signal;

    sigaction(SIGUSR2, &sa, NULL);

    child_pid = fork();

    if (child_pid == -1 )
    {
		ExitIfBad(FAIL, msg[0]);

    }
    if( 0!= counter)
    {
        --counter;

    if (child_pid == 0)
     {
        child_process();
    } 
    else 
    {
        printf("Parent PID: %d, Child PID: %d\n", getpid(), child_pid);

        sleep(1); 
        printf("Parent: Sending SIGUSR1 to child\n");
        if( 0!= counter)
        {
            --counter;

            kill(child_pid, SIGUSR1);
        }
        while (1 ) 
        {
            sleep(1);
        }
       
    }   

    }

    return 0;
}


void ExitIfBad(int is_good, const char *msg)
{
	if (FALSE == is_good) 
	{
		perror(msg);
		exit(EXIT_FAILURE);
	}
}

