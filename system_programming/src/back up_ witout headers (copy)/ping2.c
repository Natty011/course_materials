/***************************************
 * Author : Natty
 * Reviewer : David
 * Date : 12 / 03 / 2025
 * Last update: 15 / 03 / 2025
 ***************************************/

#define _POSIX_C_SOURCE 199309L /*struct sigaction*/

#include <stdio.h>	     /* perror , printf */
#include <sys/types.h>   /* pid_t */
#include <signal.h>	     /* sigaction, kill */
#include <unistd.h>       /* sleep, getpid */
#include "utils.h"		 /* ExitIfBad, msg */

volatile sig_atomic_t g_on_child = 0;
volatile pid_t g_procces_parent_pid = 0;

static void handle_signal(int sig, siginfo_t *info, void *ucontext)
{  
    (void)ucontext;
    g_procces_parent_pid = info->si_pid;
   
    if (sig == SIGUSR1)
    {
        g_on_child = 1;
    }
}


int main()  
{
    struct sigaction sa = { 0 };
    int child_cnt = 0;
 
    sa.sa_sigaction = handle_signal;
    sa.sa_flags = SA_SIGINFO;

    sigaction(SIGUSR1, &sa, NULL);
    
    printf("Pong process started with PID: %d\n", getpid());

    while (child_cnt++ < 10 ) 
    {
        printf("Child: Received SIGUSR1 from parent, sending SIGUSR2\n");


        while( !g_on_child )
        {
            sleep(1);
        }
        
        kill(g_procces_parent_pid, SIGUSR2);
        g_on_child = 0;
    }

    return 0;
}

  