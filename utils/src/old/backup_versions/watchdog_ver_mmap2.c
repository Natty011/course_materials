#define _GNU_SOURCE /* setrobust */

#include <stdio.h>
#include <pthread.h>    /*mutexattr_init, setpshared, setrobust  */
#include <sys/types.h>  /* getpid, */
#include <unistd.h>     /*getpid, fork */
#include <sys/mman.h>   /*mmap */
#include "scheduler.h"
#include "uid.h"
#include "watchdog.h"
#include "utils.h"

enum
{
    ALLOWED_MISSES = 5
};


typedef struct wd_info  //shared memory 
{

pid_t self_pid; /* current pid of watchdog (1) or client (0)*/
pid_t partner_pid; /* the other side pid */

/* mutex to protect if the other proccess collaps - robust mutex */
pthread_mutex_t mutex; 

/* condition variable waiting to heatbeat/signal */
pthread_cond_t cond_heartbeat;         

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
/*the */
int is_ready = 0;   /* */

}wd_info_ty;

/*Shared struct */
static wd_info_ty *g_info = NULL;

/*----------------
INITIAL MODE
-----------------*/
static int InitInfo(wd_info_ty *g_info);

/*----------------
NORNAL MODE TASKS
-----------------*/

int SendPing_TSK(void *param);
int CheckMisses_TSK(void *param);
int ResetMisses_TSK(void *param);
int CheckTermination_TSK(void *param);

/*----------------
FAILURE MODE TASKS
-----------------*/
int RevivePartner_TSK(void *parem);


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

int MakeMeImmortal(size_t allowed_misses, size_t ping_frequency, char** argv)
{
    scheduler_t *scheduler = NULL;
    /*assert*/
    /*Allocate shared memory of g_info to the client and watchdog*/
    g_info = mmap(NULL, sizeof(wd_info_ty), PROT_READ | PROT_WRITE,
                    MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    
    RETURN_IF_BAD(MAP_FAILED != g_info, 1, "mmap failed");
    
    RETURN_IF_BAD(0 == InitInfo(g_info), 1, "InitInfo failed");

    g_info->allowed_misses = allowed_misses;
    g_info->ping_interval = ping_frequency;

    /*fork a new watchdog proccess*/
    RETURN_IF_BAD(-1 != (g_info->partner_pid = fork()), 1, "fork failed");

    if(0 == g_info->partner_pid) 
    {
        /*child process becomes watchdog */
        g_info->is_watchdog = 1;
        execvp(argv[0], argv);  /* replace child  in main */

        perror("execvp failed");
        exit(1);
    }

    /*scheduler = SchedulerCreate();
    RETURN_IF_BAD(scheduler, 1, "SchedulerCreate failed");*/


    
}

int DoNotResuscitate(void)
{
    /*assert*/

}



static int InitInfo(wd_info_ty *g_info)
{
    pthread_mutexattr_t mutex_attr;
    pthread_condattr_t cond_attr;
    /*assert*/

    RETURN_IF_BAD(g_info, 1, "g_info is NULL");

    g_info->self_pid = getpid();
    
    g_info->is_watchdog = 0;
    g_info->misses_count = 0;
    g_info->should_terminate = 0;

    /* Initialize mutex attributes */
    RETURN_IF_BAD(0 == pthread_mutexattr_init(&mutex_attr), 1, "mutexattr_init failed");
    RETURN_IF_BAD(0 == pthread_mutexattr_setpshared(&mutex_attr, PTHREAD_PROCESS_SHARED),
        1, "mutexattr_setpshared failed");

    RETURN_IF_BAD(0 == pthread_mutexattr_setrobust(&mutex_attr, PTHREAD_MUTEX_ROBUST),
        1, "mutexattr_setrobust failed");

    /* Initialize the mutex itself */
    RETURN_IF_BAD(pthread_mutex_init(&g_info->mutex, &mutex_attr),
        1,"mutex_init failed" );

    /* Initialize condition variable attributes */
    RETURN_IF_BAD(0 == pthread_condattr_init(&cond_attr), 1, "condattr_init failed");
    RETURN_IF_BAD(0 == pthread_condattr_setpshared(&cond_attr, PTHREAD_PROCESS_SHARED),
         1, "condattr_setpshared failed");

    /* Initialize the condition variable */
    RETURN_IF_BAD(0 == pthread_cond_init(&g_info->cond_heartbeat, &cond_attr),
        1,"cond_init failed" );

    /* Clean up attributes (no longer needed) */
    RETURN_IF_BAD(0 == pthread_mutexattr_destroy(&mutex_attr),
        1,"mutexattr_destroy failed" );

    RETURN_IF_BAD(0 == pthread_condattr_destroy(&cond_attr),
        1,"pthread_condattr_destroy failed" );

    return SUCCESS;
}
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


