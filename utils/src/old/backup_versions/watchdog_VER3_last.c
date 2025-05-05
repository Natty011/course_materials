/***************************************
 * Author : Natty
 * Reviewer : David
 * Date : 01 / 04 / 2025
 * Last update: 01 / 04 / 2025
 ***************************************/

#define _POSIX_C_SOURCE 199309L /*struct sigaction*/

#include <stdio.h>      /* perror */
#include <stdlib.h>     /* exit */
#include <unistd.h>     /*getpid, fork */

#include <pthread.h>    /*  */
#include <sys/types.h>  /* getpid, */
#include <signal.h>     /*kill, SIGUSR1 , siaction*/
#include <sys/types.h>  /*pid_t*/
#include "scheduler.h"
#include "uid.h"
#include "watchdog.h"
#include "utils.h"

typedef enum mode
{
    MODE_INIT = 0,
    MODE_NORMAL =1,
    MODE_RECOVER = 2,
    MODE_STOP
}mode_t;


typedef struct wd_info  
{

pid_t self_pid; /* current pid of watchdog (1) or client (0)*/
pid_t partner_pid; /* the other side pid */

/*if i am watchdog / client ->the code of both is equal so 
need to know what the purpose of
itself(watchdog/client -->monitor each other)*/

int is_watchdog;
/*to terminate the monitoring if the proccess client / watchdog collapse*/

int should_terminate;        
/*misses count to check if the proccess is dead. above N misses it 
will do resuscitate to the proccess that collapse. (in DNR)*/
int misses_count;
size_t allowed_misses; /* N misses allow*/

/*the frequency of the signaling sending */
size_t ping_interval;


}wd_info_ty;


static wd_info_ty *g_info = NULL;
static volatile sig_atomic_t g_watchdog_is_ready = 0;
static mode_t g_mode = MODE_INIT;

static int InitInfo(wd_info_ty *g_info);

/*----------------
INITIAL MODE
-----------------*/
int WaitForReady_TSK(void *param);
int SendPing_TSK(void *param);

/*----------------
NORNAL MODE TASKS
-----------------*/

int SendPing_TSK(void *param);
int CheckMisses_TSK(void *param);
int ResetMisses_TSK(void *param);
int CheckTermination_TSK(void *param);

/*----------------
RECOVERY MODE TASKS
-----------------*/
int RevivePartner_TSK(void *parem);

static void *WatchdogThread_TH(void *arg);
static void ReadySignal_HAND(int sig);

/*--------------------
SWITCH MODE FUNCTIONS
--------------------*/

SchedSwitchToNoramalMode(mode_t mew_mode);
SchedSwitchToRecoveryMode(mode_t mew_mode);



int MakeMeImmortal(size_t allowed_misses, size_t ping_frequency, char** argv)
{
    char *new_argv[] = {argv[0], "--watchdog", NULL};
      
    /*assert*/
    /*Allocate shared memory of g_info to the client and watchdog*/
    struct sigaction sig_act = {0};
    RETURN_IF_BAD(g_info = calloc(1, sizeof(wd_info_ty)), 1, "calloc failed" );

    
    /*Init variable*/

    RETURN_IF_BAD(0 == InitInfo(g_info), 1, "InitInfo failed");

    g_info->allowed_misses = allowed_misses;
    g_info->ping_interval = ping_frequency;
    /*assign ReadySignal_HAND*/
    /*create watchdog proccess */

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
    
    RETURN_IF_BAD(-1 != (g_info->partner_pid = fork()), FAIL, "fork failed");

    if(0 == g_info->partner_pid) 
    {
        /*create watchdog proccess */
        g_info->is_watchdog = 1;
        execvp(argv[0], new_argv);  /*replace child proccess with watchdog proccess */

        perror("execvp failed");
        exit(1);
    }

    while(!g_watchdog_is_ready)
    {
        /*sigwait(&sigset, &sig);*/

        /*wait for SIGUSR1*/
    }


    return 0;
    
}

int DoNotResuscitate(void)
{
    /*assert*/

}

/*send signal to the other side */
int SendPing_TSK(void *param)
{
    /* Send SIGUSR1 to partner */
    kill(g_info->partner_pid, SIGUSR1);

    return SHOULD_REPEAT;
}

/* chack if signal/heartbeat arrived */
int CheckMisses_TSK(void *param)
{
    if(g_info->misses_count > g_info->allowed_misses )
    {
        return FAIL;
    
    }

    ++g_info->misses_count;
    return SHOULD_REPEAT;

}

/*reset the misses if signal/heatbeat arrived*/
int ResetMisses_TSK(void *param)
{
    g_info->misses_count = 0;

    return SHOULD_REPEAT;
}

/*check if need to end the proccess*/
int CheckTermination_TSK(void *param)
{
    if(g_info->should_terminate)
    {
        return STOPPED;
    }

    return SHOULD_REPEAT;

}



static int InitInfo(wd_info_ty *g_info)
{

    /*assert*/

    RETURN_IF_BAD(g_info, 1, "g_info is NULL");

    g_info->self_pid = getpid();
    
    g_info->is_watchdog = 0;
    g_info->misses_count = 0;
    g_info->should_terminate = 0;

    return SUCCESS;
}

/*if arriving to maximum allowing misses than kill the other proccess
and try to revive it */
int RevivePartner_TSK(void *parem)
{
    kill(g_info->partner_pid, SIGKILL);
    RETURN_IF_BAD(-1 != (g_info->partner_pid = fork()), 1, "fork failed");

    if( 0 == g_info->partner_pid )
    {
        /*this is the watchdog proccess*/
        g_info->is_watchdog = 1;
        /*execlp(/.../);  ???*/
    }

}


static void *WatchdogThread_TH(void *arg)
{
    /*Signal to client that watchdog is ready*/
    kill(g_info->partner_pid, SIGUSR1);

    /* TO DO: need to implement schedular tasks */
    return NULL;

}

/*client wait for watchdog */
static void ReadySignal_HAND(int sig)
{
    (void)sig;
    g_watchdog_is_ready = 1;
}














































































/*
Input: argv: strings of the commands of the current procces,
    the watchdog need to run it again in order it will succeded.

    
    info - poiner to strcuct info_ty, saving inforamion on the system:
    states, sync_object, pid,v ...

max_misses- how many times can miss respponse from the client/watchdog

interval_sec - how many secodns to charck that the client is alive

return:
Success - If the creations seccessed
Failure - If there was a failure in in the creation of thr proccess's client


*/


/*

0. If allready called brfore return succes - don't want to create
    watchdog 

// to prevent duplicate of creation 
1. Marke already_called_before = TRUE;

 Intitialization: mutex and condition variable 

2.a. 
     //handle if the thread that has the mutex is died
     // use with "pthread_mutexattr_setrobust"

    info.mutex  = PTHREAD_MUTEX_ROBUST 

    //The purpose of PTHREAD_PROCESS_SHARED is to 
        allow the mutex to be used to synchronise threads
        in different processes.
     // use with "pthread_mutexattr_setpshared"

    info.mutex  = PTHREAD_PROCESS_SHARED 

2.b.

    // use pthread_condattr_init to initialization 
    info.cond_heatbeat
    // use with "pthread_condattr_setpshared(&cond_heatbeat, PTHREAD_PROCESS_SHARED);"
    info.cond_heatbeat  = PTHREAD_PROCESS_SHARED 




3. Initilaize info struct:

   info.self_pid = getpid() // of the client
   info.is_watchdog =  0 // client == 0, watchdog ==1 
   info.shuld_terminate = 0 // still not asked to stop(DNR)
   info.misses = 0 //still do not miss signal/heartbit




Create a new proccess:
    pid = fork();

    RETURN_IF_BAD(-1 != pid, -1, "fork failed\n");

   if

*/


