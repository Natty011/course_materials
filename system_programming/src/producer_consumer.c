/***************************************
 * Author : Natty
 * Reviewer : ?
 * Date : 19 / 03 / 2025
 * Last update: 19 / 03 / 2025
 *****************************************/

#include <stdio.h>       /*__atomic_store_n, __atomic_load_n */
#include <pthread.h>    /*pthread_create, pthread_join*/
#include "utils.h"		 /* ExitIfBad, msg */

enum 
{
    NUM_ITEMS = 5
};

volatile unsigned int g_shared_data = 0; /* shared data both of consumer and producer   */
volatile int g_is_fresh_data = 0; /*0 == not_fresh(there is no data in the buffer to consum),
                         1 == fresh*/
                         
void *Producer(void *arg);
void *Consumer(void *arg);

int main()
{
    int i = 0;
    pthread_t producer_thread, consumer_thread;

    unsigned int produce_data[NUM_ITEMS] = {0};
    unsigned int consume_data[NUM_ITEMS] = {0};

    ExitIfBad( 0 == pthread_create(&producer_thread,
        NULL, Producer, produce_data), "pthread_create failed\n");

    ExitIfBad( 0 == pthread_create(&consumer_thread,
        NULL, Consumer, consume_data), "pthread_create failed\n" );

    ExitIfBad(0 == pthread_join(producer_thread, NULL),
                "pthread_join failed\n");

    ExitIfBad(0 == pthread_join(consumer_thread, NULL),
                "pthread_join failed\n");

    for(i = 0; i < NUM_ITEMS; ++i  )  
    {
        if(produce_data[i] != consume_data[i])
        {
            printf("line: %d \n" , __LINE__ );
			puts("Failes in:  ");

            printf("Produce: %u\n", produce_data[i]);
            printf("Consume: %u\n", consume_data[i]);

        }
    }
    
    return 0;
}


void *Producer(void *arg)
{
    int i = 0;

    for(i = 0; i < NUM_ITEMS; ++i  ) /*produce 5 items*/
    {
        *((unsigned int*)arg + i ) = rand() % 1000000000;
        /*waiting to consumer*/
        while(__atomic_load_n(&g_is_fresh_data, __ATOMIC_SEQ_CST))
        {}

        /*storing new_date to consume*/
        g_shared_data = *((unsigned int*)arg + i );

        /* indicating to consumer that it can read the new data */
        __atomic_store_n(&g_is_fresh_data, 1, __ATOMIC_SEQ_CST); 

    }

    return NULL;
}


void *Consumer(void *arg)
{
    int i = 0;
    
    for(i = 0; i < NUM_ITEMS; ++i  ) /*(consume 5 items)*/
    {
        /*waiting to product*/
        while(!__atomic_load_n(&g_is_fresh_data, __ATOMIC_SEQ_CST))
        {}
       
        /*reading new_date to consume*/
        *((unsigned int*)arg + i ) = g_shared_data;

        /* indicating to producer that it can create a new data */
        __atomic_store_n(&g_is_fresh_data, 0, __ATOMIC_SEQ_CST); 

    }

    return NULL;
}



