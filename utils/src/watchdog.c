#include <stdio.h>
#include <pthread.h> /* */
#include "scheduler.h"
#include "uid.h"
#include "watchdog.h"
#include "utils.h"


typedef struct wd_info  //shared memory 
{

pid_t self_pid; /* current pid of watchdog or client */
pid_t parter; /* the other side pid */

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
size_t allowed_misses; /* N misses allowes*/

/*the frequency of the signaling sending */
size_t ping_interval;


}wd_info_ty;

/*Shared struct */
static wd_info_ty *g_info = NULL;


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
       info.shuld_terminate = 0 // still not asked so stop(DNR)
       info.misses = 0 //still do not miss signal/heartbit




    Create a new proccess:
        pid = fork();

        RETURN_IF_BAD(-1 != pid, -1, "fork failed\n");

       if

    */


    
}

int DoNotResuscitate(void)
{

}