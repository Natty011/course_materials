#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>  /* pid_t */
#include <sys/wait.h>   /*waitpid*/
#include <assert.h>
#include <string.h>     /*strcmp*/
#include <unistd.h>     /*fork*/
#include "watchdog.h"
#include "utils.h" /*RETURN_IF_BAD*/

/* Dummy implementation of MakeMeImmortal */
int MakeMeImmortal(size_t allowed_misses, size_t ping_frequency, char **argv)
{
    pid_t pid_wd = -1;
    (void)allowed_misses;
    (void)ping_frequency;
    (void)argv;

    printf("[MakeMeImmortal] Dummy: initializing watchdog mechanism...\n");

    RETURN_IF_BAD(-1 != (pid_wd = fork()), FAIL,  "fork failed");
    if(0 == pid_wd)
    {
        char *new_argv[3] ={NULL};
        /*prepare argv for execvp*/
        new_argv[0] = argv[0];      /* ./watchdog_app */
        new_argv[1] = "watchdog"; /* flag to identify WD process*/
        new_argv[2] = NULL;
        printf("Reached before execvp\n");

        execvp(argv[0], new_argv);
        printf("Reached after execvp\n");

        perror("execvp failed");
        exit(1);

        /*RETURN_IF_BAD(FALSE, FAIL,  "execvp failed");*/

    }
    /*----------need to be in MMI Not here!!------------------*/
 

    return 0; /* success */
}

/* Dummy implementation of DoNotResuscitate */
int DoNotResuscitate(void)
{
    printf("[DoNotResuscitate] Dummy: cleaning up and stopping watchdog...\n");
    return 0; /* success */
}

/* Already in your app.c, but place it here if you move to final location */
void RunAsWatchdog(void)
{
    printf("[RunAsWatchdog] Starting dummy watchdog logic\n");
    sleep(2);  /* simulate watchdog work */
    printf("[RunAsWatchdog] Done dummy logic, exiting\n");
}

