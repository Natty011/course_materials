/***************************************
 * Author : Natty
 * Reviewer : ?
 * Date : 20 / 03 / 2025
 * Last update: 21 / 03 / 2025
 *****************************************/

#include <stdio.h>       
#include <pthread.h>    /*pthread_create, join, mutex_destoy, mutex_(un)lock*/
#include <semaphore.h>  /*sem_wait, sem_post, sem_destroy, sem_init */
#include "slist.h"      /*Create, GetData, Remove, End, Begin, Equal, IsEmpty*/
#include "utils.h"		 /* ExitIfBad, msg */
#include "tqueue.h"		 /* ExitIfBad, msg */

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


static void CheckSum(tq_t *fsk);


tq_t *TQCreate(size_t size)
{
    tq_t *p_fsq = NULL;
    int *buffer = NULL;

    p_fsq = (tq_t*)malloc(sizeof(tq_t));

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

    if( !pthread_mutex_init(&p_fsq->read_mutex, NULL) ||
        !pthread_mutex_init(&p_fsq->write_mutex, NULL) ||
        !sem_init(&p_fsq->empty_size_slots, )

    
   
}

static void CheckSum(tq_t *fsk)
{
    int empty = 0;
    int full = 0;

    ExitIfBad(0 == sem_getvalue(&fsk->empty_size_slots, &empty),
        "sem_getvalue failed\n");

    ExitIfBad(0 == sem_getvalue(&fsk->full_size_slots, &full),
        "sem_getvalue failed\n");

    assert((size_t)(empty + full) == fsk->size);

}



















