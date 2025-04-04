/***************************************
 * Author : Natty
 * Reviewer : 
 * Date : 01 / 04 / 2025
 * Last update: 01 / 04 / 2025
 ***************************************/

#define _POSIX_C_SOURCE 199309L /*struct sigaction*/

#include <stdio.h>      /*perror, sprintf, printf, __atomic_store_n, __atomic_load_n */
#include <pthread.h>    /*pthread_t, */
#include <signal.h>     /*kill, SIGUSR1 , siaction*/
#include <stdlib.h>     /*atoi, exit, abort, getenv*/
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
static void *SchedulerThread_TH(wd_task_info_ty *info);
static void ChildCleanup_HAND(int sig);
int SendSignal_TSK(wd_task_info_ty *info);
int CheckMisses_TSK(wd_task_info_ty *info);
int RevivePartner_TSK(wd_task_info_ty *info);
int CheckDnrFlag_TSK(wd_task_info_ty *info);

/* Forward declaration to avoid implicit declaration warning */
void RunAsWatchdog(pid_t client_pid);
static int InitNewArgv(char **new_argv, char client_pid_str[], pid_t pid_self, char **argv );
static pid_t GetWatchdogPIDFromEnv(void);


int main(int argc, char** argv)
{
    wd_task_info_ty *info = NULL;
    struct sigaction sa_app = {0};
    struct sigaction sa_child = {0};
    ilrd_uid_t ret_uid = BADUID;
    scheduler_t *sch = NULL;

    
    char client_pid_str[20] = {0};

    /* argv[0] = ./watchdog_app.out, argv[1] = "watchdog", argv[2] = <client_pid>, argv[3] = NULL */
    char *new_argv[4] = {0}; 
    pid_t pid_self = getpid();

    int ret = SUCCESS;

    printf("[Client] Starting main()\n");
    printf("[Client] My PID: %d\n", pid_self);

    InitNewArgv(new_argv, client_pid_str,pid_self, argv);
    
    printf("Current parent PID in main_start : %d\n", getppid());
    printf("Current  PID in main_start : %d\n", getpid());

    if(argc > 1 &&  (0 == strcmp(argv[1], "watchdog") ))
    {
        pid_t client_pid = (pid_t)atoi(argv[2]);
        printf("[WD] My PID: %d, Client PID: %d\n", pid_self, client_pid);


        RunAsWatchdog(client_pid); /*client_pid*/

        return 0;
    }

    info = (wd_task_info_ty*)malloc(sizeof(wd_task_info_ty));
    RETURN_IF_BAD(info, FAIL, "malloc failed");

    
    RETURN_IF_BAD(TRUE == InitInfo(info, argc, argv), FAIL, "InitInfo failed");
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
    RETURN_IF_BAD(SUCCESS == sigemptyset(&sa_app.sa_mask), FAIL, "sigemptyset sa_app failed");
    RETURN_IF_BAD(SUCCESS == sigaction(SIGUSR1, &sa_app, NULL), FAIL, "sigaction failed");

     /* Set handler for SIGCHLD to cleanup Dead processes w/o become to Zombies */
    /*signal from the system that the child process is terminated*/

    sa_child.sa_handler = ChildCleanup_HAND;
    RETURN_IF_BAD(SUCCESS ==  sigemptyset(&sa_child.sa_mask), FAIL, "sigemptyset sa_child failed");
    RETURN_IF_BAD(SUCCESS == sigaction(SIGCHLD, &sa_child, NULL), FAIL, "sigaction failed");

    ret = MakeMeImmortal(info->allowed_misses, info->ping_frequency_seconds, new_argv);
    RETURN_IF_BAD(SUCCESS == ret, FAIL, "MakeMeImmortal failed");


    info->child_pid = GetWatchdogPIDFromEnv();


    ret_uid =  SchedulerAdd(sch,(int (*)(void *))SendSignal_TSK, info, info->ping_frequency_seconds);
    RETURN_IF_BAD( SUCCESS == UIDIsSame(ret_uid, BADUID), FAIL, "SchedulerAdd SendSignal_TSK failed");

    ret_uid = SchedulerAdd(sch, (int (*)(void *))CheckMisses_TSK, info, info->ping_frequency_seconds);

    RETURN_IF_BAD( SUCCESS == UIDIsSame(ret_uid, BADUID), FAIL, "SchedulerAdd CheckMisses_TSK failed");
     /* Every 10 second, low delay */
    ret_uid = SchedulerAdd(sch, (int (*)(void *))CheckDnrFlag_TSK, info, 1);

    RETURN_IF_BAD( SUCCESS == UIDIsSame(ret_uid, BADUID), FAIL, "SchedulerAdd CheckDnrFlag_TSK failed");

    RETURN_IF_BAD(SUCCESS == pthread_create(&g_wd, NULL,
        (void *(*)(void *))SchedulerThread_TH, info), FAIL, "pthread_create failed");

     puts("lalalalalalal");  
    RETURN_IF_BAD(SUCCESS ==  pthread_detach(g_wd), FAIL, "pthread_detach failed");
    puts("babababababa");  

    while (!should_stop)
    {
        pause();
    }

    DoNotResuscitate();

    return 0;
}
static int InitNewArgv(char **new_argv, char client_pid_str[], pid_t pid_self,  char **argv )
{
    /* Prepare new argv for execvp to create watchdog */
    sprintf(client_pid_str, "%d", pid_self);

    puts(client_pid_str);

    new_argv[0] = argv[0];        /* ./watchdog_app.out */
    new_argv[1] = "watchdog";     /* identifier for WD process*/
    new_argv[2] = client_pid_str; /* client's PID */
    new_argv[3] = NULL;

    return SUCCESS;
}



/* Thread routine to run the scheduler */
static void *SchedulerThread_TH(wd_task_info_ty *info)
{
    int ret = -5;

    ret = SchedulerRun(info->sch);
    printf("ret SchedulerRun: %d\n", ret);

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
    assert(NULL != info);

    RETURN_IF_BAD(argc >= 3, FAIL, "Use:./watchdog_app.out <#freq_ping> <#allow_misses>");

    info->ping_frequency_seconds = (size_t)atoi(argv[1]);
    info->allowed_misses = (size_t)atoi(argv[2]);
    info->argv = argv;
    info->argc = argc;
    info->sch = NULL;
    /*info->child_pid = getppid();
    printf("Current PID(getppid()) of info->child_pid in InitInfo : %d\n", info->child_pid);
    printf("Current PID( getpid()) of info->child_pid in InitInfo : %d\n", getpid());*/

    return TRUE;
}


/* Task 1: send signal to ־watchdog */
int SendSignal_TSK(wd_task_info_ty *info)
{    
    int ret = 0;
    if ( -1 == (ret = kill(info->child_pid, SIGUSR1) ) )
    {
        printf("Current PID( getppid()) in SendSignal_TSK : %d\n", getppid());
        /*if the partner procces does not exist*/
        if(ESRCH == errno)
        {
            /*revive new wd */
            execvp(info->argv[0], info->argv);
            perror("execvp");
            exit(1);

        }

        else
        {
            perror("abort executed -> check core file");
            abort();
        }

        /* if failed switch to Revive or Panic */
        return FINISHED;
    }

    return SHOULD_REPEAT;
}

/* Task 2: increment the counter and revive if pass the allowed misses */
int CheckMisses_TSK(wd_task_info_ty *info)
{
    size_t max_misses = info->allowed_misses;

    int current = __atomic_add_fetch(&g_missed_SOL, 1, __ATOMIC_SEQ_CST);

    if (current > (int)max_misses)
    {
        SchedulerClear(info->sch);
        /* Every 10 second, low delay */
        SchedulerAdd(info->sch, (int (*)(void *))RevivePartner_TSK, info, 1);  
        return FINISHED;
    }

    return SHOULD_REPEAT;
}

/* Task 3: revive watchdog again  */
int RevivePartner_TSK(wd_task_info_ty *info)
{
    printf("Reached before kill in RevivePartner_TSK\n");
    
    printf("Current PID: %d\n", getpid());
    printf("Child PID (to kill): %d\n", info->child_pid);

    /*RETURN_IF_BAD(SUCCESS ==  kill(info->child_pid, SIGKILL), FAIL, "kill in RevivePartner_TSK failed");*/
    printf("Reached after kill in RevivePartner_TSK\n");
 
    /*info->child_pid = GetWatchdogPIDFromEnv fork();
    printf("Reached after fork in RevivePartner_TSK\n");*/

   
        execvp(info->argv[0], info->argv);
        perror("execvp");
        exit(1);
    

    return FINISHED;
}

/* Task 4: stop all */
int CheckDnrFlag_TSK(wd_task_info_ty *info)
{

    if (should_stop)
    {
        SchedulerStop(info->sch);
        return FINISHED;
    }

    return SHOULD_REPEAT;
}

/* Returns WD PID from environment or -1 on failure */
static pid_t GetWatchdogPIDFromEnv(void)
{
    char *wd_pid_str = getenv("WD_PID");

    if (NULL == wd_pid_str)
    {
        perror("WD_PID not found");
        return -1;
    }
    printf("Got WD PID from env: %d\n",(pid_t)atoi(wd_pid_str));

    return (pid_t)atoi(wd_pid_str);
}
