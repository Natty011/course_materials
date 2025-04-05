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
extern pid_t g_wd_pid;

/* ------------------ Struct Definition ------------------ */
typedef struct wd_task_info
{
    size_t allowed_misses;
    size_t ping_frequency;
    char **argv;
    int argc;
    scheduler_t *sch;
    pid_t child_pid;
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

/* ------------------ Main ------------------ */
int main(int argc, char **argv)
{
    wd_task_info_ty info = {0};

    assert(argc >= 4);

    EXIT_IF_BAD(SUCCESS == InitInfo(&info, argc, argv), "InitInfo failed");
    EXIT_IF_BAD(SUCCESS == SetupSignalHandlers(), "SetupSignalHandlers failed");
    EXIT_IF_BAD(SUCCESS == SetupScheduler(&info), "SetupScheduler failed");

    EXIT_IF_BAD(SUCCESS == pthread_create(&g_wd_thread, NULL,
        (void *(*)(void *))SchedulerThread_TH, &info), "pthread_create failed");

    EXIT_IF_BAD(SUCCESS == pthread_detach(g_wd_thread), "pthread_detach failed");

    puts("WD_APP: --------------BEFORE while (!should_stop) ---------------------");
    /*  
    while (!g_should_stop)
    {
        pause();
    }
    */
    return 0;
}

/* ------------------ Initialization ------------------ */
static int InitInfo(wd_task_info_ty *info, int argc, char **argv)
{
    assert(NULL != info);

    info->ping_frequency = (size_t)atoi(argv[1]);
    info->allowed_misses = (size_t)atoi(argv[2]);
    info->argv = argv;
    info->argc = argc;
    info->sch = SchedulerCreate();
    EXIT_IF_BAD(NULL != info->sch, "SchedulerCreate failed");

    info->child_pid = g_wd_pid; /* wd_pid */

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

    uid = SchedulerAdd(info->sch, (int (*)(void *))SendSignal_TSK, info, info->ping_frequency);
    EXIT_IF_BAD(FALSE == UIDIsSame(uid, BADUID), "Add SendSignal_TSK failed");

    uid = SchedulerAdd(info->sch, (int (*)(void *))CheckMisses_TSK, info, info->ping_frequency);
    EXIT_IF_BAD(FALSE == UIDIsSame(uid, BADUID), "Add CheckMisses_TSK failed");

    uid = SchedulerAdd(info->sch, (int (*)(void *))CheckDnrFlag_TSK, info, 1);
    EXIT_IF_BAD(FALSE == UIDIsSame(uid, BADUID), "Add CheckDnrFlag_TSK failed");

    return SUCCESS;
}

/* ------------------ Tasks ------------------ */
static int SendSignal_TSK(wd_task_info_ty *info)
{
    int kill_res = kill(info->child_pid, SIGUSR1);

    if (-1 == kill_res)
    {
        if (ESRCH == errno)
        {
            execvp(info->argv[3], info->argv + 3);  /*revive the client app*/
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
        SchedulerAdd(info->sch, (int (*)(void *))SendSignal_TSK, info, 1);
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
    int ret = SchedulerRun(info->sch);
    PRINT_IF_DEBUG("WD_APP: Scheduler finished with code: %d\n", ret);
    SchedulerDestroy(info->sch);
    return NULL;
}
