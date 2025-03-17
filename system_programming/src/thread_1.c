/***************************************
 * Author : Natty
 * Reviewer : Sauser
 * Date : 16 / 03 / 2025
 * Last update: 16 / 03 / 2025
 *****************************************/

#include <stdio.h>	 	 /* printf, fgets  */
#include <stdlib.h>	  	 /* exit, EXIT_SECCESS, EXIT_FAILURE */
#include <time.h> 		/*clock*/
#include <unistd.h> 	/*sleep*/

#include <pthread.h>    /* pthread_create */
#include "utils.h"		 /* ExitIfBad, msg */

#define UNUSED(var) ((void)var)

#define ARR_SIZE (100000)

/* the position of each thread in his jobs priority*/
int g_arr_ret_threads[ARR_SIZE] = { 0 }; 

/* hold the thread_id*/
pthread_t g_arr_thread_id[ARR_SIZE]  = { 0 }; 

void *start_routine(void *arg)
{
	g_arr_ret_threads[(long)arg] =  (long)arg;

	return NULL;
}


int main() 
{
	int arg = 0;


	for( arg = 0; arg < ARR_SIZE ; ++arg )
	{
		ExitIfBad( 0 == pthread_create(&g_arr_thread_id[arg],
				 NULL, start_routine, (void*)(unsigned long)arg ), "pthread_create failed\n");

		/*pthread_join(g_arr_thread_id[arg], NULL);*/
	}

	for( arg = 0; arg < ARR_SIZE ; ++arg )
	{
		pthread_join(g_arr_thread_id[arg], NULL);
	}

	sleep(10);

	puts("start test:");

	for( arg = 0; arg < ARR_SIZE ; ++arg )
	{
		if(arg != g_arr_ret_threads[arg] )
		{
			printf("line: %d \n" , __LINE__ );
			puts("Failes in:  ");
			printf("g_arr_ret_threads[%d] = { %d }\n", arg, g_arr_ret_threads[arg]);
		}
	}
	return 0;
}

