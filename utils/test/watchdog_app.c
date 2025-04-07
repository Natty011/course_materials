/***************************************
 * Author : Natty
 * Reviewer :
 * Date : 01 / 04 / 2025
 * Last update: 06 / 04 / 2025
 ***************************************/

#define _POSIX_C_SOURCE 199309L /* struct sigaction */

#include <stdio.h>      /* perror, sprintf, printf */
#include <stdlib.h>     /* atoi, exit, abort */
#include <unistd.h>     /* fork, execvp, getpid */
#include <sys/types.h>  /* pid_t */
#include <sys/wait.h>   /* waitpid */
#include <pthread.h>    /* pthread_create, pthread_detach */
#include <signal.h>     /* sigaction, SIGUSR1 */
#include <string.h>     /* strcmp */
#include <assert.h>

#include "scheduler.h"
#include "watchdog.h"
#include "utils.h"

/* ------------------ Global Variables ------------------ */
volatile int g_should_stop = 0;
static volatile sig_atomic_t g_missed_SOL = 0;
static pthread_t g_wd_thread = 0;
/*extern pid_t g_wd_pid;*/


/* ------------------ Struct Definition ------------------ */
typedef struct wd_task_info
{
    size_t allowed_misses;
    size_t ping_frequency;
    char **argv;
    int argc;
    scheduler_t *sch;
    pid_t partner_pid;
} wd_task_info_ty;

/* ------------------ Forward Declarations ------------------ */
static int InitInfo(wd_task_info_ty *info, int argc, char **argv);
static int SetupSignalHandlers(void);
static int SetupScheduler(wd_task_info_ty *info);
static void *SchedulerThread_TH(wd_task_info_ty *info);
static void HeartbeatHandler_HAND(int sig);
static void CleanupDeadChildren_HAND(int sig);

static int SendSignal_TSK(wd_task_info_ty *info);
static int CheckMisses_TSK(wd_task_info_ty *info);
static int CheckDnrFlag_TSK(wd_task_info_ty *info);

static int ResetSignalMask(void);

/* ------------------ Main ------------------ */
int main(int argc, char **argv)
{
    wd_task_info_ty info = {0};
    int i = 0;
    assert(argc >= 3);
    PRINT_IF_DEBUG("[wd_app](main) value of getpid =%d ", getpid());

    EXIT_IF_BAD(SUCCESS == InitInfo(&info, argc, argv), "InitInfo failed");
    EXIT_IF_BAD(SUCCESS == SetupSignalHandlers(), "SetupSignalHandlers failed");
    EXIT_IF_BAD(SUCCESS == SetupScheduler(&info), "SetupScheduler failed");

    EXIT_IF_BAD(SUCCESS == pthread_create(&g_wd_thread, NULL,
        (th_func_ptr)SchedulerThread_TH, &info), "pthread_create failed");

    EXIT_IF_BAD(SUCCESS == pthread_detach(g_wd_thread), "pthread_detach failed");

    for (i = 0; argv[i] != NULL; ++i)
    {
        printf("[wd_app](main) argv[%d] = %s\n", i, argv[i]);
    }

    puts("[wd_app]: --------------BEFORE while (!should_stop) ---------------------");
     
    while (!g_should_stop)
    {
        puts("[wd_app]: --------------IN while (!should_stop) ---------------------");
        pause();
    }
    

    puts("[wd_app]: --------------After while (!should_stop) ---------------------");

    return 0;
}

/* ------------------ Initialization ------------------ */
static int InitInfo(wd_task_info_ty *info, int argc, char **argv)
{
    char **argv_copy = NULL;
    char *pid_str = NULL;
    pid_t child_pid = getpid();
    int i = 0;

    assert(NULL != info);
    assert(argc >= 4);

    /* Allocate and build argv_copy for partner revival */
    argv_copy = (char **)malloc(6 * sizeof(char *));
    pid_str = (char *)malloc(20);

    if(!argv_copy || !pid_str)
    {
        free(argv_copy);
        free(pid_str);

        RETURN_IF_BAD(argv_copy, FAIL, "[wd_app] malloc for argv_copy failed");
        RETURN_IF_BAD(pid_str, FAIL, "[wd_app] malloc for pid_str failed");
    }

    argv_copy[0] = argv[3];          /* ./wd_test.out */
    argv_copy[1] = argv[1];          /* 20 */
    argv_copy[2] = argv[2];          /* 3 */
    argv_copy[3] = argv[0];          /* ./watchdog_app.out */
    sprintf(pid_str, "%d", child_pid);
    argv_copy[4] = pid_str;          /* my pid */
    argv_copy[5] = NULL;

    info->argv = argv_copy;
    info->argc = 5;
    info->ping_frequency = (size_t)atoi(argv[1]);
    info->allowed_misses = (size_t)atoi(argv[2]);
    info->partner_pid = (argc >= 5) ? atoi(argv[4]) : 0 ;   

    /*EXIT_IF_BAD(argc >= 5, "Not enough arguments – expected argv[4] to be client PID");*/
    
    info->sch = SchedulerCreate();
    EXIT_IF_BAD(NULL != info->sch, "SchedulerCreate failed");

    for (i = 0; i < info->argc; ++i)
    {
        printf("[wd_app](InitInfo) info->argv[%d] = %s\n", i, info->argv[i]);
    }

    PRINT_IF_DEBUG("[wd_app](InitInfo) value of info->partner_pid =%d ", info->partner_pid);
    PRINT_IF_DEBUG("[wd_app](InitInfo) value of argc =%d ", argc);


    return SUCCESS;
}

static int SetupSignalHandlers(void)
{
    struct sigaction sa_usr1 = {0};
    struct sigaction sa_chld = {0};

    sa_usr1.sa_handler = HeartbeatHandler_HAND;
    EXIT_IF_BAD(SUCCESS == sigemptyset(&sa_usr1.sa_mask), "sigemptyset failed");
    EXIT_IF_BAD(SUCCESS == sigaction(SIGUSR1, &sa_usr1, NULL), "sigaction failed");

    sa_chld.sa_handler = CleanupDeadChildren_HAND;
    EXIT_IF_BAD(SUCCESS == sigemptyset(&sa_chld.sa_mask), "sigemptyset failed");
    EXIT_IF_BAD(SUCCESS == sigaction(SIGCHLD, &sa_chld, NULL), "sigaction failed");

    return SUCCESS;
}

static int SetupScheduler(wd_task_info_ty *info)
{
    ilrd_uid_t uid = {0};

    uid = SchedulerAdd(info->sch, (task_func_ptr)SendSignal_TSK, info, info->ping_frequency);
    EXIT_IF_BAD(FALSE == UIDIsSame(uid, BADUID), "Add SendSignal_TSK failed");

    uid = SchedulerAdd(info->sch, (task_func_ptr)CheckMisses_TSK, info, info->ping_frequency);
    EXIT_IF_BAD(FALSE == UIDIsSame(uid, BADUID), "Add CheckMisses_TSK failed");

    uid = SchedulerAdd(info->sch, (task_func_ptr)CheckDnrFlag_TSK, info, 1);
    EXIT_IF_BAD(FALSE == UIDIsSame(uid, BADUID), "Add CheckDnrFlag_TSK failed");

    return SUCCESS;
}

/* ------------------ Tasks ------------------ */
static int SendSignal_TSK(wd_task_info_ty *info)
{
    int kill_res = -1;
    printf("[wd_app](SendSignal_TSK(info->argv[0]): %s\n", info->argv[0]);

    printf("[wd_app](SendSignal_TSK(info->argv[3]): %s\n", info->argv[3]);

    if (0 == info->partner_pid)   /*revive for the first time*/
    {
        
        printf("[wd_app](SendSignal_TSK) no child yet, reviving:info->argv[3]: %s, line =%d \n", info->argv[3], __LINE__);
        printf("[wd_app](SendSignal_TSK(0 == info->child_pid):info->argv[3]: %s\n", info->argv[3]);

        RETURN_IF_BAD(SUCCESS == ResetSignalMask(), FAIL, "ResetSignalMask failed");

        execvp(info->argv[0], info->argv ); /*  revive client for first time */
        perror("execvp failed");
        exit(1);
    }


    kill_res = kill(info->partner_pid, SIGUSR1);
    PRINT_IF_DEBUG("[wd_app](SendSignal_TSK) value of kill_res =%d ", kill_res);

    if (-1 == kill_res)
    {
        printf("[wd_app](SendSignal_TSK(-1 == kill_res)info->argv[0]: %s\n", info->argv[0]);
        printf("[wd_app](SendSignal_TSK(-1 == kill_res)info->argv[3]: %s\n", info->argv[3]);

        if (ESRCH == errno)
        {
            printf("[wd_app](SendSignal_TSK)(ESRCH == errno) about to execinfo->argv[3]: %s\n", info->argv[3]);
            
            RETURN_IF_BAD(SUCCESS == ResetSignalMask(), FAIL, "ResetSignalMask failed");

            execvp(info->argv[0], info->argv  ); /*revive the client app*/

            perror("execvp failed");
            exit(1);
        }
        else
        {
            ABORT_IF_BAD(FALSE,"abort executed -> check core file");
        }
    }

    return SHOULD_REPEAT;
}

static int CheckMisses_TSK(wd_task_info_ty *info)
{
    int count = 0;

    if ((size_t)g_missed_SOL > info->allowed_misses)
    {
        SchedulerClear(info->sch);
        SchedulerAdd(info->sch, (task_func_ptr)SendSignal_TSK, info, 1);
        return FINISHED;
    }

    count = __atomic_add_fetch(&g_missed_SOL, 1, __ATOMIC_SEQ_CST);
    
    PRINT_IF_DEBUG("[wd_app] value of g_missed_SOL =%d ", count);
    return SHOULD_REPEAT;
}

static int CheckDnrFlag_TSK(wd_task_info_ty *info)
{

    if (g_should_stop)
    {
        SchedulerStop(info->sch);
        return FINISHED;
    }

    return SHOULD_REPEAT;
}

/* ------------------ Handlers ------------------ */
static void HeartbeatHandler_HAND(int sig)
{
    assert(SIGUSR1 == sig);
    __sync_lock_test_and_set(&g_missed_SOL, 0); /*reset the misses counter*/
    printf("[wd_app]: [HeartbeatHandler_HAND] got SIGUSR1 at %s:%d\n", __FILE__, __LINE__);

}

static void CleanupDeadChildren_HAND(int sig)
{
    int status = 0;
    (void)sig;
    while (waitpid(-1, &status, WNOHANG) > 0);
}

/* ------------------ Thread ------------------ */
static void *SchedulerThread_TH(wd_task_info_ty *info)
{
    
    int ret = -5;
    sigset_t set;

    printf("[wd_app][wd_thread] argv[3] = %s\n", info->argv[3]);

    RETURN_IF_BAD(SUCCESS == sigemptyset(&set), NULL, "sigemptyset failed");
    RETURN_IF_BAD(SUCCESS == sigaddset(&set, SIGUSR1), NULL, "sigaddset failed");
    RETURN_IF_BAD(SUCCESS == sigprocmask(SIG_UNBLOCK, &set, NULL), NULL, "sigprocmask failed");

    ret = SchedulerRun(info->sch);
    PRINT_IF_DEBUG("[wd_app]: Scheduler finished with code: %d\n", ret);
    SchedulerDestroy(info->sch);
    return NULL;
}


static int ResetSignalMask(void)
{
    sigset_t set;

    RETURN_IF_BAD(SUCCESS == sigemptyset(&set), FAIL, "sigemptyset failed");
    RETURN_IF_BAD(SUCCESS == sigprocmask(SIG_SETMASK, &set, NULL), FAIL, "sigprocmask failed");
    
    return 0;
}

