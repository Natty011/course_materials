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

int ret_threads[ARR_SIZE] = { 0 };
pthread_t thread_id[ARR_SIZE]  = { 0 }; /* hold the thread_id*/

void *start_routine(void *arg)
{
	ret_threads[*(int*)arg] =  *(int*)arg;
	return NULL;
}


int main() 
{
	int i = 0;

	/*pthread_attr_t attr;*/

	for( i = 0; i < ARR_SIZE ; ++i )
	{
		ExitIfBad( 0 == pthread_create(&thread_id[i], NULL, start_routine, &i ), "pthread_create failed\n");
		pthread_join(thread_id[i], NULL);
	}

	puts("arr_values");
	for( i = 0; i < ARR_SIZE ; ++i )
	{
		printf("ret_threads[%d] = { %d }\n", i, ret_threads[i]);
	}
	return 0;
}

