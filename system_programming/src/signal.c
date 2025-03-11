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


static int is_on_child = 0;
static int is_on_parent = 0;

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

void handle_signal(int signal )
{
	is_on_child = 1;
	is_on_parent = 1;

	if (signal == SIGUSR1)
		printf("Received SIGUSR1\n");
	else if (signal == SIGUSR2)
		printf("Received SIGUSR2\n");


	if(SIGUSR1 == signal)
	{
		printf("Caught signal %d\n", signal);
		/*fflush(stdout);*/
		/*ExitIfBad(SIGINT != signal, msg[6]); */


	}

	else if (SIGUSR2 == signal)
	{
		printf("Caught signal %d\n", signal);
		/*fflush(stdout);*/

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
	pid_t child_pid = fork();

	sa.sa_handler = handle_signal;

	/*sigemptyset(&sa.sa_mask);*/ /* reset all signal group*/

	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL); 
	sigaction(SIGINT, &sa, NULL); /* ctrl + c to terminate */
	

	if( 0 == child_pid)
	{
		while(1)
		{
			sleep(3);
			printf("Im am the child:\nParent pid: %d, Child pid: %d\n", getppid(), child_pid);
			fflush(stdout);
			is_on_child = 0;

			kill(getppid(), SIGUSR2); /* send signal from the child to his parent*/ 
		}
		
	}

	else if ( child_pid > 0 )/* the parent proccess*/
	{
		while(1  ) /* && !is_on */
		{
			/*wait(NULL);*/
			sleep(3);
			printf("Im am the perent:\nParent pid: %d, Child pid: %d\n", getpid(), child_pid);
			fflush(stdout);
			is_on_parent = 0;
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

