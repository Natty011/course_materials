/***************************************
 * Author : Natty
 * Reviewer : ?
 * Date : 20 / 03 / 2025
 * Last update: 20 / 03 / 2025
 *****************************************/

#include <stdio.h>       /* rand */
#include <pthread.h>    /*pthread_create, pthread_join*/
#include <semaphore.h> /* */
#include "slist.h"
#include "utils.h"		 /* ExitIfBad, msg */

enum 
{
    NUM_ITEMS = 3,
    NUM_PRODUCERS = 3,
    NUM_CONSUMERS = 3
};

unsigned int g_arr_producer_data[NUM_PRODUCERS][NUM_ITEMS] = {0};
unsigned int g_arr_consumer_data[NUM_CONSUMERS][NUM_ITEMS*NUM_ITEMS] = {0};

int g_stop_consumers = 0;
slist_t *g_shared_slist = NULL;

pthread_mutex_t g_mutex_lock = PTHREAD_MUTEX_INITIALIZER; 
sem_t g_sem_item_available = {0};   

void *Producer(void *arg);
void *Consumer(void *arg);

int main()
{
    size_t arg = 0;

    pthread_t producer_thread_id[NUM_PRODUCERS] = {0};
    pthread_t consumer_thread_id[NUM_CONSUMERS] = {0};

    ExitIfBad(0 == sem_init(&g_sem_item_available, 0, 0), "sem_init failed\n");

    g_shared_slist = SlistCreate();

    ExitIfBad(NULL != g_shared_slist, "SlistCreate failed\n");

    for(arg = 0; arg < NUM_PRODUCERS; ++arg)
    {

        ExitIfBad(0 == pthread_create(&producer_thread_id[arg], NULL,
             Producer, (void*)(size_t)arg ), "pthread_create failed\n" );

    }

    for(arg = 0; arg < NUM_CONSUMERS; ++arg)
    {
        ExitIfBad(0 == pthread_create(&consumer_thread_id[arg], NULL,
             Consumer, (void*)(unsigned long)arg ), "pthread_create failed\n" );
    }

    for(arg = 0; arg < NUM_PRODUCERS; ++arg)
    {
        ExitIfBad(0 == pthread_join(producer_thread_id[arg], NULL),
            "pthread_join failed\n");
    }

    /*Wake up all threads after consumed the entire data*/
    pthread_mutex_lock(&g_mutex_lock);
    g_stop_consumers = 1;

    ExitIfBad(0 == pthread_mutex_unlock(&g_mutex_lock),
        "pthread_mutex_unlock failed\n" );

    for(arg = 0; arg < NUM_CONSUMERS; ++arg)
    {
        ExitIfBad(0 == sem_post(&g_sem_item_available),
            "sem_post failed\n");

    }

    for(arg = 0; arg < NUM_CONSUMERS; ++arg)
    {
        ExitIfBad(0 == pthread_join(consumer_thread_id[arg], NULL),
            "pthread_join failed\n");

    }
    
    ExitIfBad(0 == pthread_mutex_destroy(&g_mutex_lock),
        "pthread_mutex_destroy failed\n");

    ExitIfBad(0 == sem_destroy(&g_sem_item_available), "sem_destroy failed\n");
        
    SlistDestroy(g_shared_slist);         
    g_shared_slist = NULL;
    
    return 0;
}


void *Producer(void *arg)
{
    unsigned long i = 0;

    for(i = 0; i < NUM_ITEMS; ++i ) /*produce 3 items*/
    {
        g_arr_producer_data[(long)arg][i] += i + (long)arg + (10)*(long)arg;

        /*lock the critical code -> shared slist */
        ExitIfBad(0 == pthread_mutex_lock(&g_mutex_lock),
                "pthread_mutex_lock failed\n");

        ExitIfBad(! IsItrEqual(SlistEnd(g_shared_slist),
         SlistInsertBefore(g_shared_slist, SlistEnd(g_shared_slist),
          &g_arr_producer_data[(long)arg][i] ) ), "SlistInsertBefore failed\n");

        printf("g_arr_producer_data[%lu][%lu] = { %u}\n",
            (long)arg, i, g_arr_producer_data[(long)arg][i] );

        /* wake all the consumers */
        ExitIfBad(0 == sem_post(&g_sem_item_available),
            "sem_post failed\n" );

        ExitIfBad(0 == pthread_mutex_unlock(&g_mutex_lock),
            "pthread_mutex_unlock failed\n");

    }

    return NULL;
}


void *Consumer(void *arg)
{
    unsigned long item = 0;
    unsigned long item_copy = 0;

    while(1)
    {

        ExitIfBad(0 == sem_wait(&g_sem_item_available), "sem_wait failed\n");
 
        ExitIfBad(0 == pthread_mutex_lock(&g_mutex_lock),
            "pthread_mutex_lock failed\n");

        if(g_stop_consumers && SlistIsEmpty(g_shared_slist) ) 
        {
            puts("blbla11");
            printf("Exit: %lu\n", (long)arg );
            ExitIfBad(0 == pthread_mutex_unlock(&g_mutex_lock), 
                "pthread_mutex_unlock failed\n");
            puts("blbla");
            break;
        }

        item_copy = 
            *(unsigned int*)SlistGetData(SlistBegin(g_shared_slist) );

            printf("g_arr_consumer_data[%lu][%lu] = { %lu}\n",
                (long)arg, item, item_copy );
                
        SlistRemove(SlistBegin(g_shared_slist) );
        
        ExitIfBad(0 == pthread_mutex_unlock(&g_mutex_lock),
        "pthread_mutex_unlock failed\n");

        g_arr_consumer_data[(long)arg][item] = item_copy;
        /*printf("g_arr_consumer_data[%lu][%lu] = { %u}\n",
            (long)arg, item, g_arr_consumer_data[(long)arg][item] );*/
        item++;    
    }

    return NULL;
}



