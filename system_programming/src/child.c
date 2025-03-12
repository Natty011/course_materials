/***************************************
 * Author : Natty
 * Reviewer : ???
 * Date : 12 / 03 / 2025
 * Last update: 12 / 03 / 2025
 ***************************************/

#define _POSIX_C_SOURCE 199309L /*struct sigaction*/

#include <stdio.h>	       /* perror , printf */
#include <stdlib.h>      /* exit */
#include <unistd.h>	  /* fork*/
#include <sys/types.h>  /* pid_t */
#include "utils.h"		/* ExitIfBad, msg */
#include <signal.h>	/* sigaction */


static volatile sig_atomic_t is_on_child = 0;

static void handle_signal(int sig)
{
    if (sig == SIGUSR1)
    {
        is_on_child = 1;
    }
/*
    else if(SIGTERM == sig )
    {
        ExitIfBad(FALSE, msg[7]);
        
    }*/
}
 
 
int main() 
{
    struct sigaction sa = { 0 };
    int child_cnt = 0;

    sa.sa_handler = handle_signal;

    sigaction(SIGUSR1, &sa, NULL);
    puts("child");

    /*sigaction(SIGTERM, &sa, NULL);*/
    /*kill(getppid(), SIGUSR2);*/

    while (child_cnt++ < 3 )
    {
        printf("Child: Received SIGUSR1 from parent, sending SIGUSR2\n");
        kill(getppid(), SIGUSR2);
        printf("child_cnt = %d\n", child_cnt);

        while( !is_on_child )
        {
            sleep(1);
        }

        
        
        is_on_child = 0;
    
    }

    return 0;
}
 
 