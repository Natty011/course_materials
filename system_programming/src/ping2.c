/***************************************
 * Author : Natty
 * Reviewer : Idan
 * Date : 12 / 03 / 2025
 * Last update: 12 / 03 / 2025
 ***************************************/

#define _POSIX_C_SOURCE 199309L /*struct sigaction*/

#include <stdio.h>	       /* perror , printf */
#include <stdlib.h>      /* exit */
#include <unistd.h>	    /* fork*/
#include <sys/types.h>  /* pid_t */
#include "utils.h"		/* ExitIfBad, msg */
#include <signal.h>	    /* sigaction */


volatile sig_atomic_t is_on_child = 0;

static void handle_signal(int sig)
{
    if (sig == SIGUSR1)
    {
        is_on_child = 1;
    }
}


int main(int argc, char *argv[]) 
{
    struct sigaction sa = { 0 };
    int child_cnt = 0;
    pid_t parent_pid = -1;


    if (2 != argc)
    {
        ExitIfBad(FAIL, msg[8]);
    }

    sa.sa_handler = handle_signal;

    sigaction(SIGUSR1, &sa, NULL);

    parent_pid = atoi(argv[1]);

    printf("Pong process started with PID: %d, communicating with Ping PID: %d\n", getpid(), parent_pid);
    while (child_cnt++ < 3 ) 
    {
        printf("Child: Received SIGUSR1 from parent, sending SIGUSR2\n");


        while( !is_on_child )
        {
           puts("i am ping_child");
            sleep(1);
        }
        

        kill(parent_pid, SIGUSR2);
        is_on_child = 0;
    }

    return 0;
}

  