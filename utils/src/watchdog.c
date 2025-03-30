#include <stdio.h>
#include "watchdog.h"


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

int MakeMeImmortal(void *argv, info_ty *info, int max_misses, int interval_sec)
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

    */
}

void DoNotResuscitate(void *argv, info_ty *info)
{

}
