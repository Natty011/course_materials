/***************************************
 * Author : Natty
 * Reviewer : ?
 * Date : 19 / 03 / 2025
 * Last update: 19 / 03 / 2025
 *****************************************/

#include <stdio.h>       /*__atomic_store_n, __atomic_load_n */
#include <pthread.h>
#include <unistd.h>
#include "utils.h"		 /* ExitIfBad, msg */

enum 
{
    NUM_ITEMS = 5
};

volatile unsigned int g_shared_data = 0; /* shared data both of consumer and producer   */
volatile int g_is_data_fresh = 0; /*0 == not_fresh(there is no data in the buffer to consum),
                         1 == fresh*/
                         
void *producer(void *arg);
void *consumer(void *arg);

int main()
{
    pthread_t producer_thread, consumer_thread;
   
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    pthread_join( producer_thread, NULL);
    pthread_join( consumer_thread, NULL);

    
    return 0;
}


void *producer(void *arg)
{
    int i = 0;
    UNUSED(arg);

    for(i = 0; i < NUM_ITEMS; ++i  ) /*(produce 5 items)*/
    {
        unsigned int new_data = rand() % 100000;
       
        /*storing new_date to consume*/
        __atomic_store_n(&g_shared_data, new_data, __ATOMIC_SEQ_CST);

        printf("Produce: %u\n",new_data);

        /* indicating to consumer that it can read the new data */
        __atomic_store_n(&g_is_data_fresh, 1, __ATOMIC_SEQ_CST); 


        /*waiting to consumer*/
        while(__atomic_load_n(&g_is_data_fresh, __ATOMIC_SEQ_CST))
        {}
    }

    return NULL;
}


void *consumer(void *arg)
{
    int i = 0;
    UNUSED(arg);
    
    for(i = 0; i < NUM_ITEMS; ++i  ) /*(consume 5 items)*/
    {
        unsigned int consume_data = 0;
        /*waiting to product*/
        while(!__atomic_load_n(&g_is_data_fresh, __ATOMIC_SEQ_CST))
        {}
       
        /*reading new_date to consume*/
        consume_data = __atomic_load_n(&g_shared_data, __ATOMIC_SEQ_CST);

        /* indicating to producer that it can create a new data */
        __atomic_store_n(&g_is_data_fresh, 0, __ATOMIC_SEQ_CST); 

        printf("Consume: %u\n", consume_data);


    }

    return NULL;
}



