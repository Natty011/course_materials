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
#include <assert.h>
#include <string.h>     /*strcmp*/
#include <unistd.h>     /*fork*/
#include "scheduler.h"  /*Create, */
#include "watchdog.h"
#include "utils.h" /*RETURN_IF_BAD*/

volatile int should_stop = 0;
static volatile sig_atomic_t g_missed_SOL = 0;
static pthread_t g_wd = 0;

static int InitInfo(wd_task_info_ty *info, int argc, char** argv);
static void SendHeartBeat_Hand(int sig);
static void *SchedulerThread_TH(void *arg);
static void ChildCleanup_HAND(int sig);
int SendSignal_TSK(void *param);
int CheckMisses_TSK(void *param);
int RevivePartner_TSK(void *param);
int CheckDnrFlag_TSK(void *param);


int main(int argc, char** argv)
{
    wd_task_info_ty *info = NULL;
    struct sigaction sa_app = {0};
    struct sigaction sa_child = {0};

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


     /* Setup signal handler for SIGUSR1 (first signal) */
    sa_app.sa_handler = SendHeartBeat_Hand; /* תחסום את הסיגנלים חוץ מסיגיוסר*/
    RETURN_IF_BAD(SUCCESS != sigemptyset(&sa_app.sa_mask), FAIL, "sigemptyset failed");
    RETURN_IF_BAD(SUCCESS != sigaction(SIGUSR1, &sa_app, NULL), FAIL, "sigaction failed");

     /* Set handler for SIGCHLD to cleanup Dead processes w/o become to Zombies */
    /*signal from the system that the child process is terminated*/

    sa_child.sa_handler = ChildCleanup_HAND;
    RETURN_IF_BAD(SUCCESS !=  sigemptyset(&sa_child.sa_mask), FAIL, "sigemptyset failed");
    RETURN_IF_BAD(SUCCESS != sigaction(SIGCHLD, &sa_child, NULL), FAIL, "sigaction failed");

     
    ret = MakeMeImmortal(info->allowed_misses, info->ping_frequency_seconds, argv);
    RETURN_IF_BAD(SUCCESS != ret, FAIL, "InitInfo failed");

    
    SchedulerAdd(sch,SendSignal_TSK, info, info->ping_frequency_seconds);
    SchedulerAdd(sch, CheckMisses_TSK, info, info->ping_frequency_seconds);
    
     /* Every 10 second, high delay */
    SchedulerAdd(sch, CheckDnrFlag_TSK, info, 10); 

    RETURN_IF_BAD(SUCCESS != pthread_create(&g_wd, NULL,
         SchedulerThread_TH, info), FAIL, "pthread_create failed");
    RETURN_IF_BAD(SUCCESS !=  pthread_detach(g_wd), FAIL, "pthread_detach failed");

    while (!should_stop)
    {
        pause();
    }

    DoNotResuscitate();

    return 0;
}

/* Thread routine to run the scheduler */
static void *SchedulerThread_TH(void *arg)
{
    wd_task_info_ty *info = (wd_task_info_ty *)arg;

    SchedulerRun(info->sch);

    SchedulerDestroy(info->sch);

    return NULL;
}
  

/*prevents mass of zombies in the process table,
 while deads child sexist the parent collects them*/
  
static void ChildCleanup_HAND(int sig)
{

    pid_t pid = 0;
    int status = 0;

    (void)sig;

    /*WNOHANG non blocking/waiting, just check if there is dead process childs*/
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0)
    {
       /* printf("Child process %d cleaned up.\n", pid);*/
    }

}


static void SendHeartBeat_Hand(int sig)
{
    assert(SIGUSR1 == sig);
    __sync_fetch_and_add(&g_missed_SOL, 1); 
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


/* Task 1: send signal to ־watchdog */
int SendSignal_TSK(void *param)
{
    pid_t wd_pid = ((wd_task_info_ty *)param)->child_pid;
    
    if ( -1 == kill(wd_pid, SIGUSR1) )
    {
        /* if failed switch to Revive or Panic */
        return FAIL_FROM_RUN;
    }

    return SHOULD_REPEAT;
}

/* Task 2: increment the counter and revive if pass the allowed misses */
int CheckMisses_TSK(void *param)
{
    wd_task_info_ty *info = (wd_task_info_ty *)param;
    size_t max_misses = info->allowed_misses;

    int current = __atomic_add_fetch(&g_missed_SOL, 1, __ATOMIC_SEQ_CST);

    if (current > max_misses)
    {
        SchedulerClear(info->sch);
        /* Every 10 second, low delay */
        SchedulerAdd(info->sch, RevivePartner_TSK, info, 1);  
        return FINISHED;
    }

    return SHOULD_REPEAT;
}

/* Task 3: revive watchdog again  */
int RevivePartner_TSK(void *param)
{
    wd_task_info_ty *info = param;
    
    kill(info->child_pid, SIGKILL);
    
    info->child_pid = fork();

    if (info->child_pid == 0)
    {
        execvp(info->argv[0], info->argv);
        perror("execvp");
        exit(1);
    }

    return FINISHED;
}

/* Task 4: stop all */
int CheckDnrFlag_TSK(void *param)
{
    wd_task_info_ty *info = (wd_task_info_ty *)param;

    if (should_stop)
    {
        SchedulerStop(info->sch);
        return FINISHED;
    }

    return SHOULD_REPEAT;
}

