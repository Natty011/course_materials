/***************************************
 * Author : Natty
 * Reviewer : Sauser
 * Date : 05 / 10 / 2025
 * Last update: 15 / 03 / 2025
 *****************************************/

#include <stdio.h>	 	 /* printf, fgets  */
#include <stdlib.h>	  	 /* exit, EXIT_SECCESS, EXIT_FAILURE */
#include <time.h> 		/*clock*/
#include <pthread.h>    /* */
#include "utils.h"		 /* ExitIfBad, msg */

#define UNUSED(var) ((void)var)

#define ARR_SIZE (100000)

/* the position of each thread in his jobs priority*/
int g_arr_ret_threads[ARR_SIZE] = { 0 }; 

/* hold the thread_id*/
pthread_t g_arr_thread_id[ARR_SIZE]  = { 0 }; 

void *start_routine(void *arg)
{
	g_arr_ret_threads[*(int*)arg] =  *(int*)arg;
	return NULL;
}

int main() 
{
	int i = 0;

	for( i = 0; i < ARR_SIZE ; ++i )
	{
		ExitIfBad( 0 == pthread_create(&g_arr_thread_id[i], NULL, start_routine, &i ), "pthread_create failed\n");
		pthread_join(g_arr_thread_id[i], NULL);
	}

	puts("arr_values");

	for( i = 0; i < ARR_SIZE ; ++i )
	{
		printf("g_arr_ret_threads[%d] = { %d }\n", i, g_arr_ret_threads[i]);
	}
	return 0;
}

