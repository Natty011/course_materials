
/***************************************
 * Author : Natty
 * Reviewer :
 * Date : 01 / 04 / 2025
 * Last update: 06 / 04 / 2025
 ***************************************/

#define _POSIX_C_SOURCE 200809L /* sigaction, kill, fork, execvp */

#include <stdio.h>      /* printf, perror */
#include <stdlib.h>     /* exit, malloc */
#include <unistd.h>     /* fork, execvp, getpid, getppid */
#include <pthread.h>    /* pthread_create, pthread_detach */
#include <assert.h>
#include <signal.h>     /* sigaction, kill */
#include <errno.h>
#include <string.h>     /* strcmp */
#include <sys/types.h>
#include <sys/wait.h>

#include "scheduler.h"
#include "watchdog.h"
#include "utils.h"

/*pid_t g_wd_pid = 0*/; /*extern*/ 
/* ---------------------- Struct Definition ---------------------- */

typedef struct wd_internal_info
{
    scheduler_t *sched;
    size_t ping_frequency;
    size_t allowed_misses;
    pid_t partner_pid;
    char **argv;
    int argc;
} wd_internal_info_ty;


/* Enum for operational modes */
typedef enum mode
{
    BEGINE_MODE = 0,
    REVIVE_MODE = 1,
    ROUTINE_MODE = 2,
    DESTROY_MODE = 3
} wd_mode_t;

/* ---------------------- Global ---------------------- */

static volatile sig_atomic_t g_should_stop = 0;
static volatile sig_atomic_t g_missed = 0;

/* ---------------------- Forward Declarations ---------------------- */

static void HeartbeatHandler_HAND(int sig);
static void SigchldHandler_HAND(int sig);
static void *SchedulerThread_TH(wd_internal_info_ty *info);
static void BeginMode(wd_internal_info_ty *info);
static void ReviveMode(wd_internal_info_ty *info);
static void RoutineMode(wd_internal_info_ty *info);
static void DestroyMode(wd_internal_info_ty *info);
static void SchedulerSwitchMode(wd_internal_info_ty *info, int mode);

static int WaitForFirstSignal_TSK(wd_internal_info_ty *info);
static int RevivePartner_TSK(wd_internal_info_ty *info);
static int IsPartnerAlive_TSK(wd_internal_info_ty *info);
static int SendSignal_TSK(wd_internal_info_ty *info);
static int CheckMisses_TSK(wd_internal_info_ty *info);
static int CheckDnrFlag_TSK(wd_internal_info_ty *info);
/*static char **CopyArgvWithPid(char **argv, int argc, pid_t pid);*/

/* ---------------------- Implementation ---------------------- */

int MakeMeImmortal(size_t allowed_misses, size_t ping_frequency, int argc, char **argv)
{
    pid_t child_pid = -1;
    wd_internal_info_ty *info = NULL;
    struct sigaction sa = {0};
    pthread_t tid = 0;
    int i = 0;
    char **argv_copy = NULL;
    char *pid_str = NULL;

    assert(argc >= 4);

    for(i = 0; argv[i] != NULL; ++i)
    {
        fprintf(stderr, "[wd](MMI) argv[%d] = %s\n", i, argv[i]);
    }
    puts("[WD LIB] inside MakeMeImmortal()");

    child_pid = getpid();  /*pid_of the client app: wd_test.out*/
    
    printf("[WD(MMI)] got SIGUSR1 at %s:%d\n", __FILE__, __LINE__);
    PRINT_IF_DEBUG("[WD(MMI)] value of child_pid =%d ", child_pid);

    /* signal handlers */
    sa.sa_handler = HeartbeatHandler_HAND;
    RETURN_IF_BAD(SUCCESS == sigemptyset(&sa.sa_mask) , FAIL, "sigemptyset failed");
    RETURN_IF_BAD(SUCCESS == sigaction(SIGUSR1, &sa, NULL), FAIL, "sigaction failed");

    sa.sa_handler = SigchldHandler_HAND;
    RETURN_IF_BAD(SUCCESS == sigemptyset(&sa.sa_mask), FAIL, "sigemptyset failed");
    RETURN_IF_BAD(SUCCESS == sigaction(SIGCHLD, &sa, NULL), FAIL, "sigaction failed");

    info = (wd_internal_info_ty *)malloc(sizeof(wd_internal_info_ty));
    RETURN_IF_BAD(info, FAIL, "malloc failed");

    info->sched = SchedulerCreate();
    RETURN_IF_BAD(info->sched, FAIL, "SchedulerCreate failed");

    info->allowed_misses = allowed_misses;
    info->ping_frequency = ping_frequency;
    info->partner_pid = child_pid;
    
    /* Copy argv and append watchdog_app PID to the end */
    argv_copy = (char **)malloc((argc + 2) * sizeof(char *));
    pid_str = (char *)malloc(20); /* store the watchdog_app PID as string */

    RETURN_IF_BAD(argv_copy, FAIL, "malloc for argv_copy failed");
    RETURN_IF_BAD(pid_str, FAIL, "malloc for pid_str failed");

    for (i = 0; i < argc; ++i)
    {
        argv_copy[i] = argv[i];
    }

    sprintf(pid_str, "%d", child_pid);
    argv_copy[argc] = pid_str;
    argv_copy[argc + 1] = NULL;

    info->argv = argv_copy;
    info->argc = argc + 1;
    PRINT_IF_DEBUG("[WD(MMI)] value of pid_str =%s", pid_str);

    SchedulerSwitchMode(info, BEGINE_MODE); /* BEGIN mode */


    RETURN_IF_BAD(SUCCESS == pthread_create(&tid, NULL, (void *(*)(void *))SchedulerThread_TH, info),
                FAIL, "pthread_create failed");
    RETURN_IF_BAD(SUCCESS == pthread_detach(tid), FAIL, "pthread_detach failed");


    return SUCCESS;
}

int DoNotResuscitate(void)
{
    g_should_stop = 1;
    return SUCCESS;
}

/* ---------------------- Scheduler Thread ---------------------- */

static void *SchedulerThread_TH(wd_internal_info_ty *info)
{
    /*copy info to local struct and then release info struct by free
        such as line 132... but way to do so? the constrain...
        dont know how much bytes need to copy... need to solve it....*/

    /*TO DO: COPY     free(info) to local struct and free info  */  
    SchedulerRun(info->sched);
    SchedulerDestroy(info->sched);
    return NULL;
}

/* ---------------------- Modes ---------------------- */

static void BeginMode(wd_internal_info_ty *info)
{
    SchedulerClear(info->sched);
    SchedulerAdd(info->sched, (int (*)(void *))WaitForFirstSignal_TSK, info, info->ping_frequency);
}

static void ReviveMode(wd_internal_info_ty *info)
{
    SchedulerClear(info->sched);
    SchedulerAdd(info->sched, (int (*)(void *))RevivePartner_TSK, info, 1);
}

static void RoutineMode(wd_internal_info_ty *info)
{
    SchedulerClear(info->sched);
    SchedulerAdd(info->sched, (int (*)(void *))IsPartnerAlive_TSK, info, info->ping_frequency);
    SchedulerAdd(info->sched, (int (*)(void *))SendSignal_TSK, info, info->ping_frequency);
    SchedulerAdd(info->sched, (int (*)(void *))CheckMisses_TSK, info, info->ping_frequency);
    SchedulerAdd(info->sched, (int (*)(void *))CheckDnrFlag_TSK, info, 1);
}

static void DestroyMode(wd_internal_info_ty *info)
{
    kill(info->partner_pid, SIGKILL);

    SchedulerStop(info->sched);

    free(info->argv[info->argc - 1]); /* malloc of pid_str of wd */
    free(info->argv);                 /**/
    free(info);
}



static void SchedulerSwitchMode(wd_internal_info_ty *info, int mode)
{
    switch (mode)
    {
        case 0:
            BeginMode(info);
            break;
        case 1:
            ReviveMode(info);
            break;
        case 2:
            RoutineMode(info);
            break;
        case 3:
            DestroyMode(info);
            break;
    }
}

/* ---------------------- Tasks ---------------------- */

static int WaitForFirstSignal_TSK(wd_internal_info_ty *info)
{
    PRINT_IF_DEBUG("[wd(WaitForFirstSignal_TSK)] value of (int)info->allowed_misses =%d ", (int)info->allowed_misses);

    if(g_missed < (int)info->allowed_misses) 
    {
        PRINT_IF_DEBUG("[wd(WaitForFirstSignal_TSK)] value of g_missed =%d ", g_missed);
        SchedulerSwitchMode(info, ROUTINE_MODE);
        return FINISHED;
    }
    
    return SHOULD_REPEAT;
}

static int RevivePartner_TSK(wd_internal_info_ty *info)
{
    pid_t child_pid = fork();
    fprintf(stderr, "[WD](RevivePartner_TSK) child_pid after fork: %d\n", child_pid);

    RETURN_IF_BAD(child_pid >= 0, FINISHED, "fork failed");

    if (0 == child_pid)
    {
        printf("[WD LIB](RevivePartner_TSK) fork result(child_pid): %d (my pid: %d)\n", child_pid, getpid());

        fprintf(stderr, "[WD](RevivePartner_TSK) about to exec: info->argv[0]: %s\n", info->argv[0]);

        execvp(info->argv[0], info->argv);  /*revive watchdog_app.out*/
        perror("execvp failed");
        exit(1);
    }

    info->partner_pid = child_pid;  /* watchdog  pid */
    PRINT_IF_DEBUG("[wd(RevivePartner_TSK)] value of info->partner_pid =%d ", info->partner_pid);

    SchedulerSwitchMode(info, ROUTINE_MODE); /* Go back to routine */

    return FINISHED;
}

static int IsPartnerAlive_TSK(wd_internal_info_ty *info)
{
    
    int kill_ret = kill(info->partner_pid, 0);
    PRINT_IF_DEBUG("[wd(IsPartnerAlive_TSK)] value of info->partner_pid =%d ", info->partner_pid);

    PRINT_IF_DEBUG("[wd(IsPartnerAlive_TSK)] value of kill_ret =%d ", kill_ret);

    if ( -1 == kill_ret )
    { 
        if(errno == ESRCH)
        {
            SchedulerSwitchMode(info, REVIVE_MODE); /* revive */
            return FINISHED;
        }

        else
        {
            ABORT_IF_BAD(FALSE,"abort executed -> check core file");
        }
    }   
    return SHOULD_REPEAT;
}

static int SendSignal_TSK(wd_internal_info_ty *info)
{
    int kill_res = kill(info->partner_pid, SIGUSR1);
    PRINT_IF_DEBUG("[wd(SendSignal_TSK)] value of kill_res =%d ", kill_res);

    if (-1 == kill_res)
    {
        if (ESRCH == errno)
        {
            SchedulerSwitchMode(info, REVIVE_MODE);
            return FINISHED;
        }
        else
        {
            ABORT_IF_BAD(FALSE,"abort executed -> check core file");
        }
    }

    return SHOULD_REPEAT;
}

static int CheckMisses_TSK(wd_internal_info_ty *info)
{
    int current = 0;

    if (g_missed > (int)info->allowed_misses)
    {
        /*TO DO: SEND SIKKILL BEFORE REVIVE*/
        int ret = kill(info->partner_pid, SIGKILL);

        if (-1 == ret)
        {
            if (ESRCH == errno)
            {
                SchedulerSwitchMode(info, REVIVE_MODE);
                return FINISHED;
            }
        }
    }    
    current = __sync_add_and_fetch(&g_missed, 1);
    PRINT_IF_DEBUG("[wd] value of g_missed =%d ", current);


    return SHOULD_REPEAT;
}

static int CheckDnrFlag_TSK(wd_internal_info_ty *info)
{
    if (g_should_stop)
    {
        SchedulerSwitchMode(info, DESTROY_MODE);
        return FINISHED;
    }

    return SHOULD_REPEAT;
}

/* ---------------------- Signal Handlers ---------------------- */

static void HeartbeatHandler_HAND(int sig)
{
    assert(SIGUSR1 == sig);
    PRINT_IF_DEBUG("[wd(HeartbeatHandler_HAND)] value of g_missed =%d ", g_missed);

    __sync_lock_test_and_set(&g_missed, 0); /*reset the misses counter*/
    printf("WD: [HeartbeatHandler_HAND] got SIGUSR1 at %s:%d\n", __FILE__, __LINE__);

}

static void SigchldHandler_HAND(int sig)
{
    (void)sig;
    while (waitpid(-1, NULL, WNOHANG) > 0) {}
}
