/***************************************
 * Author : Natty
 * Reviewer : Sauser
 * Date : 05 / 10 / 2025
 * Last update: 15 / 03 / 2025
 *****************************************/

#include <stdio.h>	 	 /* printf, fgets  */
#include <stdlib.h>	  	 /* exit, EXIT_SECCESS, EXIT_FAILURE */

#include <pthread.h>    /* */
#include "utils.h"		 /* ExitIfBad, msg */

#define UNUSED(var) ((void)var)

#define ARR_SIZE (100000)
/*thread_t arr_threads[ARR_SIZE] = { 0 };*/
pthread_t thread_id[ARR_SIZE]  = { 0 };

/*
typedef struct thread
{
	pthread_t thread_id;
	int arr_idx;

}thread_t;
*/


void *start_routine(void *idx)
{
	
}


int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg);

int main() 
{
	int i = 0;

	for( i = 0; i < ARR_SIZE ; ++i )
	{
		pthread_create()
	}

	return 0;
}

