/***************************************
 * Author : Natty
 * Reviewer : 
 * Date : 01 / 04 / 2025
 * Last update: 01 / 04 / 2025
 ***************************************/

#include <stdio.h> 
#include <stdlib.h>     /* putenv */
#include <unistd.h>
#include <sys/types.h>  /* pid_t */
#include <sys/wait.h>   /*waitpid*/
#include <assert.h>
#include <string.h>     /*strcmp*/
#include <unistd.h>     /*fork*/
#include "watchdog.h"
#include "utils.h" /*RETURN_IF_BAD*/


/*extern int putenv(char *wd_pid_str);*/
/*static char wd_pid_str[64] = {0};*/
pid_t g_wd_pid; /*extern*/ 
/* Dummy implementation of MakeMeImmortal */
int MakeMeImmortal(size_t allowed_misses, size_t ping_frequency, char **argv)
{
    pid_t pid_wd = -1;
    pid_t pid_wd_app = getpid();
    printf("Current PID (pid_wd_app)in MMI before fork : %d\n", pid_wd_app);

    (void)allowed_misses;
    (void)ping_frequency;
    (void)argv;

    printf("[MakeMeImmortal] Dummy: initializing watchdog mechanism...\n");
    printf("Current PID in MMI before fork : %d\n", getpid());

    RETURN_IF_BAD(-1 != (pid_wd = fork()), FAIL,  "fork failed");

    if(0 == pid_wd)
    {
        /*sprintf(wd_pid_str, "WD_PID=%d", getpid());
        puts(wd_pid_str);

        if (0 != putenv(wd_pid_str))
        {
            perror("putenv failed");
            return 1;
        }*/

        /*prepare argv for execvp*/
       /* new_argv[0] = argv[0]; */     /* ./watchdog_app */
        /*new_argv[1] = "watchdog";*/ /* flag to identify WD process*/
        /*new_argv[2] = client_pid_str;*/ /* client's PID */
       /* new_argv[3] = NULL;*/

        printf("Reached before execvp\n");
        printf("Current PID in MMI before execvp : %d\n", getpid());

        execvp(argv[0], argv);
        printf("Reached after execvp\n");

        perror("execvp failed");
        exit(1);

        /*RETURN_IF_BAD(FALSE, FAIL,  "execvp failed");*/

    }
    /*----------need to be in MMI Not here!!------------------*/

    g_wd_pid = pid_wd;
    printf("[WD] My PID afterfork in MMI - g_wd_pid: %d, Client PID: %d\n", g_wd_pid, getpid());

    printf("Current PID in MMI after if(0 == pid_wd) : %d\n", getpid());
    

    return 0; /* success */
}

/* Dummy implementation of DoNotResuscitate */
int DoNotResuscitate(void)
{
    printf("[DoNotResuscitate] Dummy: cleaning up and stopping watchdog...\n");

    return 0; /* success */
}

/* Already in your app.c, but place it here if you move to final location */
void RunAsWatchdog(pid_t client_pid)
{
    
    printf("[RunAsWatchdog] Got client PID : %d\n", client_pid);
    
}

