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

#define ARR_SIZE (30000) /*62778*/
#define RANGE_SIZE (100) 

/* the position of each thread in his jobs priority*/
unsigned int g_number = 10;
size_t g_flag_routine = FALSE;

/* hold the thread_id*/

unsigned int g_sum_of_divisors_local[ARR_SIZE] = { 0 } ;


void *SumOfDivisors(void *arg)
{
	unsigned int start = ((long)arg ) * RANGE_SIZE + 1 ;
	unsigned int end = ( (long)arg + 1) * RANGE_SIZE ;

	if(start <= g_number)
	{
		g_flag_routine = TRUE;

		for( ; start <= end ; ++start ) 
		{
			if( 0 == g_number % start)
			{
				g_sum_of_divisors_local[(int)(long)arg] += start;
			}
		}
	}	

	return (void*)g_flag_routine;
}

int main() 
{
	int arg = 0, result = 0;
	int sum_of_divisors = 0 ;

	for( arg = 0; arg <=  g_sum_of_divisors_local[ arg ] ; ++arg )
	{
		do
		{
			result = *(int*)SumOfDivisors((void*)(unsigned long)arg);

		} while (result);

		if(!g_flag_routine) /* not to creat un necessary threads*/
		{
			break;
		}
		
	}

	for( arg = 0; arg <=  g_sum_of_divisors_local[ arg ] ; ++arg )
	{
		sum_of_divisors += g_sum_of_divisors_local[arg];
	}

	printf("sum_of_divisors = { %d }\n", sum_of_divisors);

	return 0;
}

