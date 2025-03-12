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
#include <sys/wait.h>   /* wait */
#include "utils.h"		/* ExitIfBad, msg */
#include <signal.h>	   /* sigaction */

volatile sig_atomic_t is_on_parent = 0;
 
static void handle_signal(int sig)
{
    if (SIGUSR2 == sig)
    {
        is_on_parent = 1;
    }
    
    else if( SIGTERM == sig  || SIGINT == sig )
    {
        ExitIfBad(FAIL, "Parent: terminated the proccess\n");
    }

}
 
 
int main(int argc, char *argv[]) 
{
    struct sigaction sa = { 0 };
    int parent_cnt = 0;
    pid_t child_pid = -1;
    
    sa.sa_handler = handle_signal;

    sigaction(SIGUSR2, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);
    sigaction(SIGINT, &sa, NULL);

    if (2 != argc)
    {
        ExitIfBad(FAIL, msg[8]);
    }
    
    child_pid = atoi(argv[1]);
    printf("Ping process started with PID: %d, communicating with Pong PID: %d\n", getpid(), child_pid);

    /*kill(child_pid, SIGUSR1);*/

    while ( parent_cnt++ < 3 ) 
    {
        while( !is_on_parent )
        {
            puts("i am pong_parent");
            sleep(1);
        }

        is_on_parent = 0;
        
        printf("Parent: Received SIGUSR2 from child, sending SIGUSR1\n");
        kill(child_pid, SIGUSR1);

    }

    

    return 0;
}
 