/***************************************
 * Author : Natty
 * Reviewer : 
 * Date : 26 / 03 / 2025
 * Last update: 30 / 03 / 2025
 *****************************************/

#ifndef WATCHDOG_H      /* WATCHDOG_H */
#define WATCHDOG_H      /* WATCHDOG_H */

/*client and watchdog save this instace struct to collet info/status on each other 
during their communication */
typedef struct info
{
    
/*
   pid_t self_pid /* watchdog / client
   pid_t parter /* the other one

    // mutex to protect if the other proccess collaps
    pthread_mutex_t mutex; 
    
     // condition variable waiting to heatbeat/signal 
    pthread_cond_t cond_heatbeat;         

    //if ia am watchdog / client becuse the code of both is equal so 
    need to know what the purpose of itself ( watchdog/client -->monitor wach other )

    int is_watchdog;  
    
     // to terminate the monitoring if the proccess client * watchdog collapse
    int should_terminate;        


   //misses count to check if the proccess is dead. above N misses it 
   will do resuscitate to the proccess that collapse.
   int misses_cnt 




*/
} info_ty;

int i = 0;

int MakeMeImmortal(void *args, info_ty *info, int max_misses, int interval_sec);
void DoNotResuscitate(void *args, info_ty *info);

#endif /* WATCHDOG_H */

