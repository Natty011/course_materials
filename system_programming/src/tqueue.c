/***************************************
 * Author : Natty
 * Reviewer : ?
 * Date : 20 / 03 / 2025
 * Last update: 21 / 03 / 2025
 *****************************************/

#include <stdio.h>
#include <assert.h>     /* assert*/
#include <stdlib.h> 	/* calloc, free */
#include <pthread.h>    /*pthread_create, join, mutex_destoy, mutex_(un)lock*/
#include <semaphore.h>  /*sem_wait, sem_post, sem_destroy, sem_init */
#include "tqueue.h"		 /* */
#include "utils.h"	 	 /* ExitIfBad, msg */

enum 
{
    NUM_ITEMS = 3,
    NUM_PRODUCERS = 3,
    NUM_CONSUMERS = 3
};


struct fsq
{
   int *buffer;
   size_t size;                 /* size of the qeueue*/
   size_t read_index;             
   size_t write_index;

   pthread_mutex_t read_mutex;  /* locking comsumers*/
   pthread_mutex_t write_mutex; /* locking producers*/

   sem_t empty_size_slots;
   sem_t full_size_slots;
};

/* static functions decleration */
static void CheckSum(tq_t *fsq);


tq_t *TQCreate(size_t size)
{
    tq_t *p_fsq = NULL;

    p_fsq = (tq_t*)calloc(1, sizeof(tq_t));

    if(!p_fsq)
    {
        p_fsq = NULL;
        return NULL;
    }

    p_fsq->buffer = (int*)calloc(size, sizeof(int));

    if(!p_fsq->buffer)
    {
        free(p_fsq);
        p_fsq = NULL;

        return NULL;
    }

    p_fsq->size = size;
    p_fsq->read_index = 0;
    p_fsq->write_index = 0;

    if( pthread_mutex_init(&p_fsq->read_mutex, NULL) ||
        pthread_mutex_init(&p_fsq->write_mutex, NULL) ||
        sem_init(&p_fsq->empty_size_slots, 0, (unsigned int)size) ||
        sem_init(&p_fsq->full_size_slots, 0, 0) )

    {
       
        free(p_fsq->buffer);
        p_fsq->buffer = NULL;

        free(p_fsq);
        p_fsq = NULL;

        return NULL;
    }
    
    return  p_fsq;
}

static void CheckSum(tq_t *fsq)
{
    int empty = 0;
    int full = 0;

    ExitIfBad(0 == sem_getvalue(&fsq->empty_size_slots, &empty),
        "sem_getvalue failed\n");

    ExitIfBad(0 == sem_getvalue(&fsq->full_size_slots, &full),
        "sem_getvalue failed\n");

    assert((size_t)(empty + full) == fsq->size);

}

void TQEnqueue(tq_t *fsq, int num)
{
    ExitIfBad(0 == sem_wait(&fsq->empty_size_slots),
        "sem_wait failed\n");

    ExitIfBad(0 == pthread_mutex_lock(&fsq->write_mutex),
        "pthread_mutex_lock failed\n");

    fsq->buffer[fsq->write_index] = num;
    fsq->write_index = (fsq->write_index + 1) % fsq->size;


    ExitIfBad(0 == pthread_mutex_unlock(&fsq->write_mutex),
    "pthread_mutex_unlock failed\n");

    ExitIfBad(0 == sem_post(&fsq->full_size_slots), "sem_post failed\n");

    CheckSum(fsq);

}

int TQDequeue(tq_t *fsq)
{
    int read_value = 0;

    ExitIfBad(0 == sem_wait(&fsq->full_size_slots),
        "sem_wait failed\n");

    ExitIfBad(0 == pthread_mutex_lock(&fsq->read_mutex),
        "pthread_mutex_lock failed\n");
    
    read_value = fsq->buffer[fsq->read_index];
    fsq->read_index = (fsq->read_index + 1) % fsq->size;

    
    ExitIfBad(0 == pthread_mutex_unlock(&fsq->read_mutex),
        "pthread_mutex_unlock failed\n");
     

    ExitIfBad(0 == sem_post(&fsq->empty_size_slots), "sem_post failed\n");    

    CheckSum(fsq);

    return read_value;
        
}

void TQDestroy(tq_t *fsq)
{
    ExitIfBad(0 == pthread_mutex_destroy(&fsq->write_mutex),
    "pthread_mutex_destroy failed\n");

    ExitIfBad(0 == pthread_mutex_destroy(&fsq->read_mutex),
        "pthread_mutex_destroy failed\n");

    ExitIfBad(0 == sem_destroy(&fsq->empty_size_slots),
        "sem_destroy failed\n");

    ExitIfBad(0 == sem_destroy(&fsq->full_size_slots),
        "sem_destroy failed\n");

    /*DEBUG ONLY */
    /*
        assert(! (fsq->size = 0) );
        fsq->read_index = 0
        fsq->write_index = 0;
    */
    free(fsq->buffer);
    fsq->buffer = NULL;

    free(fsq);
    fsq = NULL;

}



















