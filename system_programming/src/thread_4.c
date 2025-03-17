/***************************************
 * Author : Natty
 * Reviewer : Sauser
 * Date : 16 / 03 / 2025
 * Last update: 17 / 03 / 2025
 *****************************************/

#include <stdio.h>	 	 /* printf, fgets  */
#include <pthread.h>    /* pthread_create */
#include "utils.h"		 /* ExitIfBad, msg */

#define UNUSED(var) ((void)var)

#define ARR_SIZE (10) /*62778*/
#define RANGE_SIZE (100) 

/* the position of each thread in his jobs priority*/
int g_arr_ret_threads[ARR_SIZE] = { 0 }; 
unsigned int g_number = 10;
size_t g_flag_routine = FALSE;

/* hold the thread_id*/
pthread_t g_arr_thread_id[ARR_SIZE]  = { 0 }; 
unsigned int g_sum_of_divisors_local[ARR_SIZE] = { 0 } ;


void *SumOfDivisors(void *arg)
{
	unsigned int start = ((long)arg ) * RANGE_SIZE + 1 ;
	unsigned int end = ( (long)arg + 1) * RANGE_SIZE ;
	
	g_arr_ret_threads[(long)arg] =  (long)arg;

	if(start <= g_number)
	{
		g_flag_routine = TRUE;
		for( ; start <= end ; ++start ) 
		{
			if( 0 == g_number % start)
			{
				g_sum_of_divisors_local[(long)arg] += start;
			}
		}

	}
	
	return (void*)g_flag_routine;
}

int main() 
{
	int arg = 0, result = 0;
	int sum_of_divisors = 0 ;
	
	pthread_attr_t attr;

	ExitIfBad(0 == pthread_attr_init(&attr), "pthread_attr_init failed\n"); 

	for( arg = 0; arg <=  g_arr_ret_threads[ arg ] ; ++arg )
	{
		do
		{
			result = pthread_create(&g_arr_thread_id[arg ],
				&attr , SumOfDivisors, (void*)(unsigned long)arg ) ;

			ExitIfBad(!result,"pthread_create failed\n" );	
			
		} while (result);

		if(!g_flag_routine) /* not to creat un necessary threads*/
		{
			break;
		}

		
	}

	for( arg = 0; arg <=  g_arr_ret_threads[ arg ] ; ++arg )
	{
		ExitIfBad(0 == pthread_join(g_arr_thread_id[arg], NULL),"pthread_join failed\n" );

			sum_of_divisors += g_sum_of_divisors_local[arg];
	}

	printf("sum_of_divisors = { %d }\n", sum_of_divisors);

	for( arg = 0; arg <=  g_arr_ret_threads[ arg ] ; ++arg ) /*ARR_SIZE && arg !=*/
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

