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

#define ARR_SIZE (30000) /*62778*/
#define RANGE_SIZE (100) 

/* the position of each thread in his jobs priority*/
int g_arr_ret_threads[ARR_SIZE] = { 0 }; 
unsigned int g_number = 10;

/* hold the thread_id*/
pthread_t g_arr_thread_id[ARR_SIZE]  = { 0 }; 

unsigned int g_sum_of_divisors_local[ARR_SIZE] = { 0 } ;


void *SumOfDivisors(void *arg)
{
	int start = ((int)(long)arg ) * RANGE_SIZE + 1 ;
	int end = ( (int)(long)arg + 1) * RANGE_SIZE ;

	g_arr_ret_threads[(int)(long)arg] =  (int)(long)arg;

	for( ; start <= end ; ++start ) /* (g_number/ARR_SIZE)*( (int)arg  */
	{
		if( 0 == g_number % start)
		{
			g_sum_of_divisors_local[(int)(long)arg] += start;
		}
	}

	return NULL;
}


int main() 
{
	int arg = 0, result = 0;
	int sum_of_divisors = 0 ;

	pthread_attr_t attr;

	ExitIfBad(0 == pthread_attr_init(&attr), "pthread_attr_init failed\n"); 

	for( arg = 0; arg < ARR_SIZE ; ++arg )
	{
		do
		{
			result = pthread_create(&g_arr_thread_id[arg],
				&attr , SumOfDivisors, (void*)(unsigned long)arg ) ;

			ExitIfBad(!result,"pthread_create failed\n" );	
			
		} while (result);
		
	}

	for( arg = 0; arg < ARR_SIZE ; ++arg )
	{
		ExitIfBad(0 == pthread_join(g_arr_thread_id[arg], NULL),"pthread_join failed\n" );

			sum_of_divisors += g_sum_of_divisors_local[arg];
	}

	printf("sum_of_divisors = { %d }\n", sum_of_divisors);

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

