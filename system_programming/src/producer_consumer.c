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
    NUM_ITEMS = 5
};

volatile unsigned int shared_data = 0; /* shared data both of consumer and producer   */
volatile int is_data_fresh = 0; /*0 == not_fresh(there is no data in the buffer to consum),
                         1 == fresh*/



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

    for(i = 0; i < NUM_ITEMS; ++i  ) /*(produce 5 items)*/
    {
        unsigned int new_data = rand() % 100000;
       
        /*storing new_date to consume*/
        __atomic_store_n(&shared_data, new_data, __ATOMIC_SEQ_CST);

        /* indicating to consumer that it can read the new data */
        __atomic_store_n(&is_data_fresh, 1, __ATOMIC_SEQ_CST); 

        /*waiting to consumer*/
        while(__atomic_load_n(&is_data_fresh, __ATOMIC_SEQ_CST))
        {}
    }

    return NULL;
}



/*
function consumer:



*/

