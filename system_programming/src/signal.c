/***************************************
 * Author : Natty
 * Reviewer : ???
 * Date : 05 / 10 / 2025
 * Last update: 11 / 03 / 2025
 ***************************************/

#define _POSIX_C_SOURCE 199309L

#include <stdio.h>	   /* perror  */
#include <stdlib.h>    /* exit, EXIT_SUCCESS, EXIT_FAILURE */
#include <string.h>	   /* strcmp */
#include <unistd.h>	   /* fork, execv*/
#include <sys/wait.h>  /* wait */
#include <sys/types.h> /* pid_t */

#include <signal.h>	   /* sigaction */
#define UNUSED(var) ((void)var)


volatile static int is_on_child = 0;
volatile static int is_on_parent = 0;

static char *msg[] = {"fork failed\n", "fgets failed\n", "strtok failed\n",
	"execvp failed\n", "Too many arguments\n",
 "Empty line is not allowed\n", "SIGINT terminated the proccess\n"};




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
    /*TO DO: REMOVE printf from handles*/
	if (sig == SIGUSR2)
     {
        /*printf("Parent: Received SIGUSR2 from child, sending SIGUSR1\n");*/
        is_on_parent = 1;
 	} 
    else if (sig == SIGUSR1)
    {
       /* printf("Child: Received SIGUSR1 from parent, sending SIGUSR2\n");*/
		is_on_child = 1;
    }
}


int main() 
{
    struct sigaction sa = { 0 };
	int child_cnt = 0, parent_cnt = 0;
    pid_t child_pid = -1;

    sa.sa_handler = handle_signal;

	sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);

	child_pid = fork();
	printf("Parent PID: %d, Child PID: %d\n", getpid(), child_pid);

	ExitIfBad(BAD_PID != child_pid , msg[0]);

    if (  0 ==  child_pid )
    {
		while (child_cnt++ < 3 )
		{
			printf("Child: Sending SIGUSR2 to parent\n");
			kill(getppid(), SIGUSR2);

			while( !is_on_child )
			{
				sleep(1);
			}
			
			is_on_child = 0;
		
		}
	}	

	else /* The parent */
	{
		while (parent_cnt++ < 3 )
		{
			

			while( !is_on_parent )
			{
				sleep(1);
			}

			printf("Parent: Sending SIGUSR1 to child\n");
			kill(child_pid, SIGUSR1);

			
			is_on_parent = 0;
		
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

