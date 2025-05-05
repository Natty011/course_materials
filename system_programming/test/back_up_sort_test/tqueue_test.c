/***************************************
* Author : Natty
* Reviewer : ???
* Date : 23 / 03 / 2025
* Last update: 23 / 03 / 2025
*****************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "utils.h"		 /* ExitIfBad, msg */
#include "tqueue.h"


#define BLACK        "\x1b[30m"
#define RED          "\x1b[31m"
#define GREEN        "\x1b[32m"
#define YELLOW       "\x1b[33m"
#define BLUE         "\x1b[34m"
#define MAGENTA      "\x1b[35m"
#define CYAN         "\x1b[36m"
#define WHITE        "\x1b[37m"

#define RESET        "\x1b[0m"

/* BACKGROUND COLOR */
#define BACK_BLACK   "\x1b[40m"
#define BACK_RED     "\x1b[41m"
#define BACK_GREEN   "\x1b[42m"
#define BACK_YELLOW  "\x1b[43m"
#define BACK_BLUE  	 "\x1b[44m"
#define BACK_MAGENTA "\x1b[45m"
#define BACK_CYAN 	 "\x1b[46m"
#define BACK_WHITE   "\x1b[47m"


#define DEBUG		"DEBUG MODE"
#define RELEASE		"RELEASE MODE"


/***************struct and enum declaration *******/


enum 
{
    QUEUE_SIZE = 10,
	NUM_ITEMS = 3,
    NUM_PRODUCERS = 3,
    NUM_CONSUMERS = 3
};



unsigned int g_arr_producer_data[NUM_PRODUCERS][NUM_ITEMS] = {0};
unsigned int g_arr_consumer_data[NUM_CONSUMERS][NUM_ITEMS*NUM_ITEMS] = {0};
int g_stop_consumers = 0;

typedef struct
{
    tq_t *queue;
    int id;
} thread_arg_t;


/***************End of struct and enum declaration *******/



static void TestTqueue(void);
void *Producer(void *arg);
void *Consumer(void *arg);



int main ()
{
	char* mode = RELEASE;
	char* background =  BACK_MAGENTA;	
	
	#ifndef NDEBUG
		mode = DEBUG;
		background =  BACK_YELLOW;
	#endif

	puts(BLUE"====================================================="RESET);
	printf("%sTEST: %s "RESET" \n", background,  mode);
   	puts(BACK_BLUE"'TestTqueue()'"RESET);
	TestTqueue();
	
	puts(BLUE"====================================================="RESET);


	return 0;
}



/************************************************************/
/************************  TestTqueue  ************************/
/************************************************************/


static void TestTqueue(void)
{
   
	int status_result = 0;
	size_t arg = 0;
	tq_t *fsq1 = NULL;

    thread_arg_t producer_args[NUM_PRODUCERS] = {0};
    thread_arg_t consumer_args[NUM_CONSUMERS] = {0};
	pthread_t producer_thread_id[NUM_PRODUCERS] = {0};
    pthread_t consumer_thread_id[NUM_CONSUMERS] = {0};


	fsq1 = TQCreate(QUEUE_SIZE);
  
	ExitIfBad(NULL != fsq1, "TQCreate failed\n");


	for(arg = 0; arg < NUM_PRODUCERS; ++arg) 
    {

		producer_args[arg].queue = fsq1;
		producer_args[arg].id = arg;

		ExitIfBad(0 == pthread_create(&producer_thread_id[arg], NULL,
             Producer, &producer_args[arg] ), "pthread_create failed\n" );

    }
	
	for(arg = 0; arg < NUM_CONSUMERS; ++arg)
    {
        consumer_args[arg].queue = fsq1;
		consumer_args[arg].id = arg;

		ExitIfBad(0 == pthread_create(&consumer_thread_id[arg], NULL,
             Consumer, &consumer_args[arg] ), "pthread_create failed\n" );
    }
	
	for(arg = 0; arg < NUM_PRODUCERS; ++arg)
    {

		ExitIfBad(0 == pthread_join(producer_thread_id[arg], NULL),
            "pthread_join failed\n");

		
    }

	for(arg = 0; arg < NUM_CONSUMERS; ++arg)
    {
        ExitIfBad(0 == pthread_join(consumer_thread_id[arg], NULL),
            "pthread_join failed\n");
    }


	TQDestroy(fsq1);
	fsq1 = NULL;

	if( !status_result  )
	{
		puts(RESET);		
		puts(BACK_BLUE"Test: Success"RESET);

	}

	else
	{
		puts(BACK_RED"Test: Failure"RESET);	
	}


    return;
}




void *Producer(void *arg)
{
    unsigned long i = 0;
	int data = 0;
    thread_arg_t *targ = (thread_arg_t*)arg;


    for(i = 0; i < NUM_ITEMS; ++i ) 
    {
        data = g_arr_producer_data[targ->id][i] += i*(100) + targ->id;
        printf("Producer %d enqueued: %d\n", targ->id, data);

		TQEnqueue(targ->queue, data);

        
    }

    return NULL;
}


void *Consumer(void *arg)
{
    unsigned long item = 0;
    int item_copy = 0;
    thread_arg_t *targ = (thread_arg_t*)arg;

	for(item = 0; item < NUM_ITEMS; ++item ) 
    {
		item_copy = TQDequeue(targ->queue);

		g_arr_consumer_data[targ->id][item] = item_copy;

		printf("Consumer %d enqueued: %d\n", targ->id, item_copy);
    }

    return NULL;
}
