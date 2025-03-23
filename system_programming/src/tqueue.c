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
   int fsq_buffer;
   size_t size;                 /* size of the qeueue*/
   size_t read_index;             
   size_t write_index;

   pthread_mutex_t read_mutex;  /* locking comsumers*/
   pthread_mutex_t write_mutex; /* locking producers*/

   sem_t empty_size_places;
   sem_t full_size_places;
};


static void CheckSum(tq_t *fsk);


int main()
{


    return 0;
}

static void CheckSum(tq_t *fsk)
{
    int empty = 0;
    int full = 0;

    ExitIfBad(0 == sem_getvalue(&fsk->empty_size_places, &empty),
        "sem_getvalue failed\n");

    ExitIfBad(0 == sem_getvalue(&fsk->full_size_places, &full),
        "sem_getvalue failed\n");

    assert((size_t)(empty + full) == fsk->size);

}



















