/***************************************
 * Author : Natty
 * Reviewer : David
 * Date : 05 / 03 / 2025
 * Last update: 15 / 03 / 2025
 ***************************************/

#define _POSIX_C_SOURCE 199309L /*struct sigaction*/

#include <stdio.h>	   /* perror , printf */
#include <stdlib.h>    /* exit */
#include <sys/types.h>  /* pid_t */
#include <signal.h>	   /* sigaction, kill */
#include <unistd.h>       /* sleep, getpid */
#include "utils.h"		/* ExitIfBad, msg */

volatile sig_atomic_t g_on_parent = 0;

static void handle_signal(int sig)
{
    if (SIGUSR2 == sig)
    {
        g_on_parent = 1;
    }
    
}
 

int main(int argc, char *argv[]) 
{
    struct sigaction sa = { 0 };
    int parent_cnt = 0;
    pid_t child_pid = -1;
    
    sa.sa_handler = handle_signal;

    sigaction(SIGUSR2, &sa, NULL);


    if (2 != argc)
    {
        ExitIfBad(FAIL, msg[8]);
    }
    
    child_pid = atoi(argv[1]);
    printf("Ping process started with PID: %d, communicating with Pong PID: %d\n", getpid(), child_pid);


    while ( parent_cnt++ < 10 ) 
    {
        printf("Parent: Received SIGUSR2 from child, sending SIGUSR1\n");
        kill(child_pid, SIGUSR1);


        while( !g_on_parent )
        {
            sleep(1);
        }

        g_on_parent = 0;
        
       
    }
    
    return 0;
}
 