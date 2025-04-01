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


typedef struct wd_info  
{

    scheduler_t* sch;
    char** argv;
    int argc;
    size_t allowed_misses;
    size_t ping_frequency_seconds;
    pid_t child_pid;

}wd_info_ty;


static wd_info_ty *g_info = NULL;

static volatile int g_missed_SOL;  /* counting misses*/
static pthread_t g_wd;              /*watchdog thread identifiar*/
static volatile int should_stop;      /* using in DNR*/

static int InitInfo(wd_info_ty *g_info);

static void BeginMode(g_info)
{
    /*SchedulerClear(sch)*/
    /*SchdulerAdd(sch, WaitForFirstSignal_TSK, g_info, ping_frequency_seconds)*/
    /*ReviveMode(g_info)*/
}

static void ReviveMode(g_info)
{
    /* WDProcessCreation():
            1. using fork+exec
    
    */

    /*SchdulerAdd(sch, Revive_TSK, g_info, ping_frequency_seconds)*/

        
}





int MakeMeImmortal(size_t allowed_misses, size_t ping_frequency, char** argv)
{
    
   
    
}

int DoNotResuscitate(void)
{
    /*assert*/

}


