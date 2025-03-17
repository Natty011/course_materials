/***************************************
 * Author : Natty
 * Reviewer : Sauser
 * Date : 16 / 03 / 2025
 * Last update: 16 / 03 / 2025
 *****************************************/

#include <stdio.h>	 	 /* printf, fgets  */
#include <stdlib.h>	  	 /* exit, EXIT_SECCESS, EXIT_FAILURE */
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
	g_arr_ret_threads[(int)(long)arg] =  (int)(long)arg;

	return NULL;
}


int main() 
{
	int arg = 0, result = 0;

	pthread_attr_t attr;

	ExitIfBad(0 == pthread_attr_init(&attr), "pthread_attr_init failed\n"); 

	ExitIfBad( 0 == pthread_attr_setdetachstate(&attr,
			 PTHREAD_CREATE_DETACHED), "pthread_attr_setdetachstate failed\n");

	for( arg = 0; arg < ARR_SIZE ; ++arg )
	{
		do
		{
			result = pthread_create(&g_arr_thread_id[arg],
				&attr , start_routine, (void*)(unsigned long)arg ) ;

			ExitIfBad(!result,"pthread_create failed\n" );	
			
		} while (result);
		
	}

	/* release internal resource of struct 'attr' after using
		 attr_init function */
	ExitIfBad(0 == pthread_attr_destroy(&attr), "pthread_attr_destroy failed\n" );



	return 0;
}

