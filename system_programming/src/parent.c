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
    if (sig == SIGUSR2)
    {
        is_on_parent = 1;
    } 

}


int main() 
{
    struct sigaction sa = { 0 };
    int parent_cnt = 0;
    pid_t child_pid = -1;
    
    sa.sa_handler = handle_signal;

    sigaction(SIGUSR2, &sa, NULL);

    child_pid = fork();
    ExitIfBad(BAD_PID != child_pid , msg[0]);

    if (0 == child_pid)
    {        
        execl("./child", "child", (char*)NULL );
        ExitIfBad(FAIL, msg[0]);
    }  

    else /*if (0 < child_pid)*/
    {

        while (parent_cnt++ < 3)
        {
            while( !is_on_parent )
            {
                sleep(1);
            }

            is_on_parent = 0;
            
            printf("Parent: Received SIGUSR2 from child, sending SIGUSR1\n");
            kill(child_pid, SIGUSR1);

        }

    }

    return 0;
}

