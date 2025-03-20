/***************************************
 * Author : Natty
 * Reviewer : ?
 * Date : 20 / 03 / 2025
 * Last update: 20 / 03 / 2025
 *****************************************/

#include <stdio.h>       /* rand */
#include <pthread.h>    /*pthread_create, pthread_join*/
#include "../../git/ds/include/slist.h"
#include "utils.h"		 /* ExitIfBad, msg */

enum 
{
    NUM_ITEMS = 3,
    NUM_PRODUCERS = 3,
    NUM_CONSUMERS = 3
};
volatile unsigned int g_arr_producer_data[NUM_PRODUCERS][NUM_ITEMS] = {0};
volatile unsigned int g_arr_consumer_data[NUM_CONSUMERS][NUM_ITEMS*NUM_ITEMS] = {0};

slist_t *g_shared_slist = NULL;

pthread_mutex_t g_mutex_lock = PTHREAD_MUTEX_INITIALIZER; 
pthread_cond_t g_cond_empty = PTHREAD_COND_INITIALIZER ;
                        
void *Producer(void *arg);
void *Consumer(void *arg);

int main()
{
    int arg = 0;

    pthread_t producer_thread_id[NUM_PRODUCERS] = {0};
    pthread_t consumer_thread_id[NUM_CONSUMERS] = {0};

    g_shared_slist = SlistCreate();

    ExitIfBad(NULL != g_shared_slist, "SlistCreate failed\n");

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
        ExitIfBad(0 == pthread_join(consumer_thread_id[arg], NULL),
            "pthread_join failed\n");
    }
    
    ExitIfBad(0 == pthread_mutex_desroy(&g_mutex_lock),
        "pthread_mutex_desroy failed\n");

    ExitIfBad(0 == pthread_cond_desroy(&g_cond_empty),
        "pthread_mutex_desroy failed\n");         

    SlistDestroy(g_shared_slist);         
    g_shared_slist = NULL;
    
    return 0;
}


void *Producer(void *arg)
{
    unsigned int i = 0;
    

    for(i = 0; i < NUM_ITEMS; ++i  ) /*produce 3 items*/
    {
        g_arr_producer_data[(long)arg][i] =  rand() % 1000000000;

        /*lock the critical code -> shared slist */
        ExitIfBad(0 == pthread_mutex_lock(&g_mutex_lock),
                 "pthread_mutex_lock failed\n");
        
        ExitIfBad(SlistEnd(g_shared_slist) != SlistInsertBefore(g_shared_slist,
            SlistEnd(g_shared_slist), &g_arr_producer_data[(long)arg][i] ), 
                 "SlistInsertBefore failed\n");


        ExitIfBad(0 == pthread_mutex_signal(&g_cond_empty),
                 "pthread_mutex_signal failed\n" );   

   
        ExitIfBad(0 == pthread_mutex_unlock(&g_mutex_lock),
        "pthread_mutex_unlock failed\n");


    }

    return NULL;
}


void *Consumer(void *arg)
{
    unsigned int item = 0;
    unsigned int temp_data = 0;

    while(1)
    {
        ExitIfBad(0 == pthread_mutex_lock(&g_mutex_lock),
                "pthread_mutex_lock failed\n");

        while(SlistIsEmpty(g_shared_slist))
        {
            ExitIfBad(0 == pthread_cond_wait(&g_cond_empty, &g_mutex_lock),
                "pthread_cond_wait failed\n");
        }

        temp_data = (g_arr_consumer_data[(long)arg][item++] = 
                *(unsigned int*)SlistGetData(SlistBegin(g_shared_slist) ) );

        /* exit if SlistBegin is dummies */
        ExitIfBad(NULL != temp_data || 
                g_shared_slist != temp_data, "SlistGetData failed\n");

        SlistRemove(SlistBegin(g_shared_slist) );
        
        ExitIfBad(0 == pthread_mutex_unlock(&g_mutex_lock),
        "pthread_mutex_unlock failed\n");

    }

    return NULL;
}



