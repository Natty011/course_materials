/***************************************
 * Author : Natty
 * Reviewer : Sauser
 * Date : 16 / 03 / 2025
 * Last update: 17 / 03 / 2025
 *****************************************/

#include <stdio.h>	 	 /* printf, fgets  */
#include <pthread.h>    /* pthread_create */
#include "utils.h"		 /* ExitIfBad, msg */
#include <omp.h>		/**/
#define UNUSED(var) ((void)var)


/* the position of each thread in his jobs priority*/
unsigned int g_number = 10;

/* hold the thread_id*/



size_t SumOfDivisors(void)
{

	unsigned int start = 1;
	unsigned int end = g_number;
	size_t sum_of_divisors = 0;

	#pragma omp parallel for

		for( start = 1 ; start <= end ; ++start ) 
		{
			if( 0 == g_number % start)
			{
			sum_of_divisors += start;
			}
		}
		
	return sum_of_divisors;
}

int main() 
{
	size_t sum_of_divisors = 0 ;

	sum_of_divisors = SumOfDivisors();
	printf("sum_of_divisors = { %ld }\n", sum_of_divisors);

	return 0;
}

