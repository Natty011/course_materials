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
#include <stdio.h>	   /* printf, fgets  */
#include <stdlib.h>	   /* exit, EXIT_SECCESS, EXIT_FAILURE */
#include <string.h>	   /* strcmp */
#include <unistd.h>	   /* fork, execv*/
#include <sys/wait.h>  /* wait */
#include <sys/types.h> /* pid_t */



static char *msg[] = {"fork failed\n", "fgets failed\n", "strtok failed\n",
	"execvp failed\n", "Too many arguments\n",
 "Empty line is not allowed\n"};

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

int handle_signal(int signal )
{
	kill(child_pid, signal);
}

/*exercise1 - ping pong*/
int main() 
{
	struct sigaction sa;
	sa.sa_handler = handle_signal;

	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL); 

	child_pid = fork();
	
	if( 0 == child_pid)
	{
		

	}

	return 0;
}






void ExitIfBad(int is_good, const char *msg)
{
	if (FALSE == is_good) 
	{
		printf("%s", msg);
		exit(EXIT_FAILURE);
	}
}

