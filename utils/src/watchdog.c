/***************************************
 * Author : Natty
 * Reviewer : 
 * Date : 01 / 04 / 2025
 * Last update: 05 / 04 / 2025
 ***************************************/

#include <stdio.h> 
#include <stdlib.h>     /*  */
#include <unistd.h>
#include <sys/types.h>  /* pid_t */
#include <sys/wait.h>   /*waitpid*/
#include <assert.h>
#include <string.h>     /*strcmp*/
#include <unistd.h>     /*fork*/
#include "watchdog.h"
#include "utils.h" /*RETURN_IF_BAD*/


pid_t g_wd_pid; /*extern*/ 

 /*prepare argv for execvp*/
       /* new_argv[0] = argv[0]; */     /* ./watchdog_app */
        /*new_argv[1] = "watchdog";*/ /* flag to identify WD process*/
        /*new_argv[2] = client_pid_str;*/ /* client's PID */
       /* new_argv[3] = NULL;*/
/* argv[0] = ./watchdog_app.out, argv[1] = "watchdog", argv[2] = <client_pid>, argv[3] = NULL */

 /* Dummy implementation of MakeMeImmortal */      
int MakeMeImmortal(size_t allowed_misses, size_t ping_frequency, char **argv)
{
    pid_t pid_wd = -1;
    pid_t pid_wd_app = getpid();
    printf("WD.c: Current PID (pid_wd_app)in MMI before fork : %d\n", pid_wd_app);

    (void)allowed_misses;
    (void)ping_frequency;
    (void)argv;

    printf("WD.c:[MakeMeImmortal] Dummy: initializing watchdog mechanism...\n");
    printf("WD.c: Current PID in MMI before fork : %d\n", getpid());

    RETURN_IF_BAD(-1 != (pid_wd = fork()), FAIL,  "fork failed");

    if(0 == pid_wd)
    {

        printf("WD.c: Reached before execvp\n");
        printf("WD.c: Current PID in MMI before execvp : %d\n", getpid());

        execvp(argv[0], argv);
        printf("WD.c: Reached after execvp\n");

        perror("WD.c: execvp failed");
        exit(1);

        /*RETURN_IF_BAD(FALSE, FAIL,  "execvp failed");*/
    }
    /*----------need to be in MMI Not here!!------------------*/

    g_wd_pid = pid_wd;
    printf("WD.c: [WD] My PID(g_wd_pid) after fork in MMI: %d, Client PID: %d\n", g_wd_pid, getpid());
    

    return 0; /* success */
}

/* Dummy implementation of DoNotResuscitate */
int DoNotResuscitate(void)
{
    printf("WD.c: [DoNotResuscitate] Dummy: cleaning up and stopping watchdog...\n");

    return 0; /* success */
}

/* Already in your app.c, but place it here if you move to final location */
void RunAsWatchdog(pid_t client_pid)
{
    
    printf("WD.c: [RunAsWatchdog] Got client PID : %d\n", client_pid);
    
}

