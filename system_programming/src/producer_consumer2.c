/***************************************
 * Author : Natty
 * Reviewer : ?
 * Date : 20 / 03 / 2025
 * Last update: 20 / 03 / 2025
 *****************************************/

#include <stdio.h>       /*  */
#include <pthread.h>    /*pthread_create, pthread_join*/
#include "../../git/ds/include/slist.h"
#include "utils.h"		 /* ExitIfBad, msg */

enum 
{
    NUM_ITEMS = 5,
    NUM_PRODUCERS = 3,
    NUM_CONSUMERS = 3
};
unsigned int g_arr_producer_num[NUM_PRODUCERS] = {0};
unsigned int g_arr_consumer_num[NUM_CONSUMERS] = {0};

slist_t *g_shared_slist = NULL;
pthread_mutex_t g_mutex_lock = {0};

                        
void *Producer(void *arg);
void *Consumer(void *arg);

int main()
{
    int arg = 0;

    pthread_t producer_thread_id[NUM_PRODUCERS] = {0};
    pthread_t consumer_thread_id[NUM_CONSUMERS] = {0};

    g_shared_slist = SlistCreate();

    ExitIfBad(NULL != g_shared_slist, "SlistCreate failed\n");

    ExitIfBad(0 == pthread_mutex_init(&g_mutex_lock, NULL),
        "pthread_mutex_init failed\n" );

    for(arg = 0; arg < NUM_PRODUCERS; ++arg)
    {

        ExitIfBad(0 == pthread_create(&producer_thread_id[arg], NULL,
             Producer, (void*)(unsigned long)arg ), "pthread_create failed\n" );

    }

    for(arg = 0; arg < NUM_CONSUMERS; ++arg)
    {

        ExitIfBad(0 == pthread_create(&consumer_thread_id[arg], NULL,
             Consumer, (void*)(unsigned long)arg ), "pthread_create failed\n" );

    }

    for(arg = 0; arg < NUM_PRODUCERS; ++arg)
    {
        ExitIfBad(0 == pthread_join(consumer_thread_id[arg], NULL)
                    , "pthread_join failed\n");
    }
    
    ExitIfBad(0 == pthread_mutex_desroy(&g_mutex_lock),
             "pthread_mutex_desroy failed\n");

    SlistDestroy(g_shared_slist);         
    g_shared_slist = NULL;
    
    return 0;
}


void *Producer(void *arg)
{
    int i = 0;
    unsigned int new_data = 0;
    g_arr_producer_num[(long)arg] =  (long)arg;

    for(i = 0; i < NUM_ITEMS; ++i  ) /*produce 5 items*/
    {
        new_data = rand() % 1000000000;

        /*lock the critical code -> shared slist */
        ExitIfBad(0 == pthread_mutex_lock(&g_mutex_lock),
                 "pthread_mutex_lock failed\n");
        
        ExitIfBad(SlistEnd(g_shared_slist) != SlistInsertBefore(g_shared_slist,
            SlistEnd(g_shared_slist), &new_data ), "SlistInsertBefore failed\n");

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
    g_arr_consumer_num[(long)arg] =  (long)arg;

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



