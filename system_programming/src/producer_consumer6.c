/***************************************
 * Author : Natty
 * Reviewer : ?
 * Date : 20 / 03 / 2025
 * Last update: 21 / 03 / 2025
 *****************************************/

#include <stdio.h>       
#include <pthread.h>    /*pthread_create, join, cond_wait, cond_signal,
                        cond_broadcast, mutex_(un)lock, mutex_destroy,
                        cond_destroy */

#include "utils.h"		 /* ExitIfBad, msg */

enum 
{
    NUM_ITEMS = 3,
    NUM_PRODUCERS = 5
};


volatile int g_shared_version = -1;
volatile int g_shared_data = 0;

pthread_mutex_t g_mutex_lock = PTHREAD_MUTEX_INITIALIZER; 
pthread_cond_t g_cond_version = PTHREAD_COND_INITIALIZER ;
                        
void *Producer(void *arg);
void *Consumer(void *arg);
void Produce(int *product);
void Consume(size_t arg, int data, int version);

TO DO: To contiue the implemation of this exersize !
int main()
{
    size_t arg = 0;

    pthread_t producer_thread_id = {0};
    pthread_t consumer_thread_id[NUM_CONSUMERS] = {0};


    

    ExitIfBad(0 == pthread_create(&producer_thread_id, NULL,
        Producer, (void*)(size_t)arg ), "pthread_create failed\n" );


    for(arg = 0; arg < NUM_CONSUMERS; ++arg)
    {
        ExitIfBad(0 == pthread_create(&consumer_thread_id[arg], NULL,
            Consumer, (void*)(unsigned long)arg ), "pthread_create failed\n" );
    }

    
        ExitIfBad(0 == pthread_join(producer_thread_id[arg], NULL),
            "pthread_join failed\n");
    

    
    for(arg = 0; arg < NUM_CONSUMERS; ++arg)
    {
        ExitIfBad(0 == pthread_join(consumer_thread_id[arg], NULL),
            "pthread_join failed\n");

    }
    
    
    ExitIfBad(0 == pthread_mutex_destroy(&g_mutex_lock),
        "pthread_mutex_destroy failed\n");

    ExitIfBad(0 == pthread_cond_destroy(&g_cond_version),
        "pthread_cond_destroy failed\n");         
    
    return 0;
}


void *Producer(void *arg)
{
    unsigned long i = 0;

    for(i = 0; i < NUM_ITEMS; ++i ) /*produce 3 items*/
    {
        /* TO DO: create Produce function while the 
        i don't have the mutex, insert to produce the  g_arr_producer_data
        and return the result in order to insert to the slist.*/

        /*Produce();*/

        g_arr_producer_data[(long)arg][i] += i + (long)arg + (10)*(long)arg;
        /*lock the critical code -> shared slist */
        ExitIfBad(0 == pthread_mutex_lock(&g_mutex_lock),
                "pthread_mutex_lock failed\n");

        ExitIfBad(! IsItrEqual(SlistEnd(g_shared_slist),
        SlistInsertBefore(g_shared_slist, SlistEnd(g_shared_slist),
        &g_arr_producer_data[(long)arg][i] ) ), "SlistInsertBefore failed\n");

        /*cond_signal must be inside the critical section
        while using conditional variable */
        ExitIfBad(0 == pthread_cond_signal(&g_cond_empty),
                "pthread_cond_signal failed\n" );   

    
        ExitIfBad(0 == pthread_mutex_unlock(&g_mutex_lock),
        "pthread_mutex_unlock failed\n");

    }

    return NULL;
}

void *Consumer(void *arg)
{
    unsigned long item = 0;
    
    /* TO DO:
        1. do just limited iterations such as while( i < 20 ) and the 
        you dont need the g_stop_consumers and the if condition after
        the internal while.
        2. Create Consume() function that the consumer us after 
            it releasing the mutex, this is the purpose of multithreading!! 
    */
    while(1)
    {

        ExitIfBad(0 == pthread_mutex_lock(&g_mutex_lock),
            "pthread_mutex_lock failed\n");

        while(SlistIsEmpty(g_shared_slist) && !g_stop_consumers)
        {
            ExitIfBad(0 == pthread_cond_wait(&g_cond_empty, &g_mutex_lock),
                "pthread_cond_wait failed\n");
        }

        if(g_stop_consumers && SlistIsEmpty(g_shared_slist) )
        {
            ExitIfBad(0 == pthread_mutex_unlock(&g_mutex_lock), 
                "pthread_mutex_unlock failed\n");

            break;
        }

        g_arr_consumer_data[(long)arg][item++] = 
                *(unsigned int*)SlistGetData(SlistBegin(g_shared_slist) );

        SlistRemove(SlistBegin(g_shared_slist) );
        
        ExitIfBad(0 == pthread_mutex_unlock(&g_mutex_lock),
        "pthread_mutex_unlock failed\n");

        /*Consume();*/

    }

    return NULL;
}



