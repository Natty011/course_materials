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



static char *msg[] = {"fork failed\n", "fgets failed\n", "strtok failed\n",
	"execvp failed\n", "Too many arguments\n",
 "Empty line is not allowed\n", "SIGINT terminated the proccess\n"};

pid_t child_pid = 0;

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

void handle_signal(int signal )
{
	if(SIGUSR1 == signal)
	{
		printf("Caught signal %d\n", signal);
	}

	else if (SIGUSR2 == signal)
	{
		printf("Caught signal %d\n", signal);
	}

	else 			/* SIGINT*/
	{
		ExitIfBad(SIGINT != signal, msg[6]); 
	}

}

/*exercise1 - ping pong*/
int main() 
{
	struct sigaction sa;
	sa.sa_handler = handle_signal;

	sigemptyset(&sa.sa_mask); /* reset all signal group*/

	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL); 
	sigaction(SIGINT, &sa, NULL); /* ctrl + c to terminate */
	
	child_pid = fork();

	if( 0 == child_pid)
	{
		sleep(1);
		printf("Parent pid: %d, Child pid: %d\n", getpid(), child_pid);
		kill(getppid(), SIGUSR2); /* send signal from the child to his parent*/ 
	}

	else if ( child_pid > 0 )/* the parent proccess*/
	{
		while(1)
		{
			sleep(1);
			kill(child_pid, SIGUSR1); /*send signal from parent to his child */
		}
	}

	else
	{
		ExitIfBad(FAIL, msg[0]);
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

