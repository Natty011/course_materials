/***************************************
 * Author : Natty
 * Reviewer : ???
 * Date : 05 / 03 / 2025
 * Last update: 12 / 03 / 2025
 ***************************************/

#define _POSIX_C_SOURCE 199309L /*struct sigaction*/

#include <stdio.h>	   /* perror , printf */
#include <stdlib.h>    /* exit */
#include <unistd.h>	   /* fork*/
#include <sys/types.h>  /* pid_t */
#include "utils.h"		/* ExitIfBad, msg */
#include <signal.h>	   /* sigaction */


static volatile sig_atomic_t is_on_child = 0;
static volatile sig_atomic_t is_on_parent = 0;

static void handle_signal(int sig)
 {
	if (sig == SIGUSR2)
    {
        is_on_parent = 1;
 	} 
    else if (sig == SIGUSR1)
    {
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

	ExitIfBad(BAD_PID != child_pid , msg[0]);

    if (  0 ==  child_pid )
    {
		while (child_cnt++ < 3 )
		{
       		printf("Child: Received SIGUSR1 from parent, sending SIGUSR2\n");
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

			printf("Parent: Received SIGUSR2 from child, sending SIGUSR1\n");
			kill(child_pid, SIGUSR1);

			is_on_parent = 0;
		
		}

	}

    return 0;
}

