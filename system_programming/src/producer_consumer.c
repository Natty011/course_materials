/***************************************
 * Author : Natty
 * Reviewer : ?
 * Date : 19 / 03 / 2025
 * Last update: 19 / 03 / 2025
 *****************************************/

#include <stdio.h>       /* */
#include <pthread.h>
#include <unistd.h>
#include "utils.h"		 /* ExitIfBad, msg */

/*
int g_shared_data -> shared data both of consumer and producer  
int g_spinlock = 0 -> 0 == unlock, 1 == lock the access to g_shared_data
int g_deta_ready = 0 -> 0 == not_ready(there is no data in the buffer to consum),
                         1 == ready
*/

enum 
{
    NUM_ITEMS = 10
};

int shared_data = 0;
int is_data_fresh = 0;



int main(int argc, char *argv[])
{
    
   /*
    pthread producer_thread, consumer_thread
   */
   
    /*
        create_pthread(function producer)
        create_pthread(function consumer)
    */

    /*
        pthread_join(function producer)
        pthread_join(function consumer)

    */
    return 0;
}


void *producer(void *arg)
{
    int i = 0;

    for(i = 0; i < NUM_ITEMS; ++i  ) /*(produce 10 items)*/
    {
        while(__atomic_load)
    }

    return NULL;
}



/*
function consumer:



*/

