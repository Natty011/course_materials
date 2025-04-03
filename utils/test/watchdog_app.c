/***************************************
 * Author : Natty
 * Reviewer : David
 * Date : 01 / 04 / 2025
 * Last update: 01 / 04 / 2025
 ***************************************/

#define _POSIX_C_SOURCE 199309L /*struct sigaction*/

#include <stdio.h>      /*perror, printf, __atomic_store_n, __atomic_load_n */
#include <pthread.h>    /*pthread_t, */
#include <signal.h>     /*kill, SIGUSR1 , siaction*/
#include <stdlib.h>     /*atoi, exit*/
#include <sys/types.h>  /* pid_t */
#include <sys/wait.h>   /*waitpid*/

#include <unistd.h>     /*fork*/
#include "scheduler.h"  /*Create, */
#include "watchdog.h"
#include "utils.h" /*RETURN_IF_BAD*/

volatile int should_stop = 0;
static volatile int g_missed_SOL = 0;/*sig_atomic_int ??? instead int !!*/
static pthread_t g_wd = 0;

static int InitInfo(wd_task_info_ty *info, int argc, char** argv);
static void SendHeartBeat_Hand(int sig);

int main(int argc, char** argv)
{
    wd_task_info_ty *info = NULL;
    struct sigaction sa_app = {0};
    char *new_argv[3] = {0};
    scheduler_t *sch = NULL;
    int ret = SUCCESS;

    if(argc > 1 &&  (0 == strcmp(argv[1], "watchdog") ))
    {
        RunAsWatchdog();

        return 0;
    }

    info = (wd_task_info_ty*)malloc(sizeof(wd_task_info_ty));
    RETURN_IF_BAD(info, FAIL, "malloc failed");

    
    RETURN_IF_BAD(SUCCESS != InitInfo(info, argc, argv), FAIL, "InitInfo failed");
    info->sch = SchedulerCreate();

    if(NULL == info->sch)
    {
        free(info);
        info = NULL;
        RETURN_IF_BAD(FALSE, FAIL, "SchedulerCreate failed");

    }

    sch = info->sch;

    ret = MakeMeImmortal(info->allowed_misses, info->ping_frequency_seconds, argv);
    RETURN_IF_BAD(SUCCESS != ret, FAIL, "InitInfo failed");

    /* Set handler for SIGCHLD to cleanup Dead processes w/o become to Zombies */
    /*signal from the system that the child process is terminated*/
    signal(SIGCHLD, ChildCleanup_HAND);

   /* Setup signal handler for SIGUSR1 (first signal) */
    sa_app.sa_handler = SendHeartBeat_Hand;
    RETURN_IF_BAD(SUCCESS != sigemptyset(&sa_app.sa_mask), FAIL, "sigemptyset failed");
    RETURN_IF_BAD(SUCCESS != sigaction(SIGUSR1, &sa_app, NULL), FAIL, "sigaction failed");


    /*fork and start watchdog*/
    /*----------need to be in MMI Not here!!------------------*/
    RETURN_IF_BAD(-1 != (info->child_pid = fork()), FAIL,  "fork failed");
    if(0 == info->child_pid)
    {
        /*prepare argv for execvp*/
        new_argv[0] = argv[0];      /* ./watchdog_app */
        new_argv[1] = "watchdog"; /* flag to identify WD process*/
        new_argv[2] = NULL;

        execvp(argv[0], new_argv);
        RETURN_IF_BAD(FALSE, FAIL,  "execvp failed");

    }
    /*----------need to be in MMI Not here!!------------------*/

    
    /*
    ADD TASKS: SchedulerAdd(...);
       SendSignal_TSK
       CheckMisses_TSK
       CheckDnrFlag_TSK
    /* Add tasks to scheduler */
    

    /*
    Create SchedulerTread_TH / pthread_create(...);

    join(&g_wd) or detach(&g_wd) ?? need to check
    */    

    /*while(!g_stop_app)*/
        /*The job of the Application ...*/
    

    DoNotResuscitate();

    return 0;
}

/*prevents mass of zombies in the process table,
 while deads child sexist the parent collects them*/
  
static void ChildCleanup_HAND(int sig)
{
    (void)sig;

    pid_t pid = 0;
    int status = 0;
    /*WNOHANG non blocking/waiting, just check if there is dead process childs*/
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0)
    {
       /* printf("Child process %d cleaned up.\n", pid);*/
    }
    /*there is dead child proccess and failed to clean it up*/
    if (pid == -1 && errno != ECHILD) 
    {
        
        perror("waitpid failed in ChildCleanup_HAND");
    }

}


static void SendHeartBeat_Hand(int sig)
{
    assert(SIGUSR1 == sig);
    __atomic_store_n(&g_missed_SOL, 0, __ATOMIC_SEQ_CST);
}


static int InitInfo(wd_task_info_ty *info, int argc, char** argv)
{
    assert(NULL == info);

    RETURN_IF_BAD(argc >= 3, FAIL, "Use:./watchdog_app.out <#freq> <#misses>");


    info->ping_frequency_seconds = (size_t)atoi(argv[1]);
    info->allowed_misses = (size_t)atoi(argv[2]);
    info->argv = argv;
    info->argc = argc;
    info->sch = NULL;

    return SUCCESS;
}





























  /*assert*/
     /*check that argv consists a string name that is
      identical with the executable file name */

     /*Register signal handler for SIGINT/SIGTERM via StopApp_HAND*/

    /*allow_misses = 5*/
    /*ping_frequency = 2 sec*/

    /*if MMI(Arguments...) failed */
        /*perror msg and exit */


    /*while(!g_stop_app)*/
        /*The job of the Application ...*/

     /*DNR()*/


/*signal handler to allow gracefull terminaion */

/*StopApp_HAND(int sig)*/

    /*change g_stop_app to true*/
    /*return*/
