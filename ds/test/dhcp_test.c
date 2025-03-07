/***************************************
* Author : Natty
* Reviewer : Rawan
* Date : 26 / 02 / 2025
* Last update: 26 / 02 / 2025
*****************************************/

#include <stdio.h> 		/* printf, puts  */


#include <assert.h>
#include <string.h> 	/* strcpy, strcmp */
#include <stdlib.h> 	/* calloc, free */
#include <time.h> 		/* clock */
#include <stdint.h> 	/* uint8_t*/

#include "dhcp.h" 

#ifdef PRINTS

#endif

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

#define MIN(a, b)		((a > b ) ? b : a )
#define MAX(a, b)		((a > b ) ? a : b )
#define UNUSED( var )       ( (void)var )

#define WORD_SIZE		( 32 )
#define  BYTES_IN_IP    (4)

/***************struct and enum declaration *******/


typedef enum
{
	DOUBLE_FREE_FAIL = -1,
	SUCCESS = 0,
	FAIL = 1,
	REQUEST_NOT_MET = 2
	
}dhcp_result_t;

typedef enum
{
	
	FALSE = 0,
	TRUE = 1
	
}func_result_t;

typedef uint8_t ip_addrs_t[4];

/*
	#ifdef PRINTS
		Aux_Pre_Print_Tree(avl1, 0);
	#endif
*/
/***************End of struct and enum declaration *******/

/***************************function declaration**************************/
static void TestDhcp(void);
static int
	 	CompareRetIp(ip_addrs_t expected_ip, ip_addrs_t ret_ip );
/***************************End of function declaration******************/

/******************static functions definition**********************/
		
/******************End of static functions definition**********************/


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
   	puts(BACK_BLUE"'TestDhcp()'"RESET);
	TestDhcp();

	puts(BLUE"====================================================="RESET);

	return 0;
}

/************************************************************/
/********************  TestDhcp  *********************/
/************************************************************/
static void TestDhcp(void)
{	

	int result = FALSE, status_result = FALSE, idx = 0; 
	dhcp_t *dhcp1 = NULL;
	ip_addrs_t ip = {192, 168, 2, 5};
	ip_addrs_t requested_ip[10] ={ {192, 168, 2, 0}, { 0 },
		 {192, 168, 2, 254 }, {192, 168, 2, 255 } } ;
	ip_addrs_t ret_allocated_ip[10] =  { { 0 } } ;
	ip_addrs_t arr_expected[10] = { {192, 168, 2, 1} , { 192, 168, 2, 2 } ,
	{ 0 }, { 0 }, { 0 } };

	size_t bits_num_in_subnet1 = 24, count_free = 0;
	count_free = 1UL<<(WORD_SIZE - bits_num_in_subnet1) ;
	count_free -= 3;

	dhcp1 = DHCPCreate(ip, bits_num_in_subnet1);

	if( !dhcp1 )
	{
		printf("line: %d \n" , __LINE__ );
		status_result =  TRUE;
		puts("Failes in: DHCPCreate ");

		return;
	}
	/*printf("count_free = %lu\n", count_free);
	printf("DHCPCountFree(dhcp1) = %lu\n", DHCPCountFree(dhcp1));*/

	if( DHCPCountFree(dhcp1) != count_free )
	{
		printf("line: %d \n" , __LINE__ );
		status_result =  TRUE;
		puts("Failes in: DHCPCountFree ");

	}

	result = DHCPAllocateIP(dhcp1, requested_ip[0], ret_allocated_ip[0]);
	
	#ifdef PRINTS
/*
		printf("result = { %d }\n", result);
		printf("ret_allocated_ip_test = {%u, %u, %u, %u} \n", 
			ret_allocated_ip[0][0], ret_allocated_ip[0][1],
			ret_allocated_ip[0][2], ret_allocated_ip[0][3]);
*/			
	#endif

	if( REQUEST_NOT_MET != result || 
		CompareRetIp(arr_expected[0],ret_allocated_ip[0] ) ||
		DHCPCountFree(dhcp1) != --count_free  )	
	{
		printf("line: %d \n" , __LINE__ );
		status_result =  TRUE;
		puts("Failes in: AllocateIP || CountFree ");
	}

	result = DHCPAllocateIP(dhcp1, requested_ip[1], ret_allocated_ip[1]);

	if( REQUEST_NOT_MET != result || 
		CompareRetIp(arr_expected[1],ret_allocated_ip[1] ) ||
		DHCPCountFree(dhcp1) != --count_free  )	
	{
		printf("line: %d \n" , __LINE__ );
		status_result =  TRUE;
		puts("Failes in: AllocateIP || CountFree ");
	}

	result = DHCPAllocateIP(dhcp1, requested_ip[2], ret_allocated_ip[2]);

	if( FAIL != result || 
		CompareRetIp(arr_expected[2],ret_allocated_ip[2] ) ||
		DHCPCountFree(dhcp1) != count_free  )	
	{
		printf("line: %d \n" , __LINE__ );
		status_result =  TRUE;
		puts("Failes in: AllocateIP || CountFree ");
	}

	result = DHCPAllocateIP(dhcp1, requested_ip[3], ret_allocated_ip[3]);

	if( FAIL != result || 
		CompareRetIp(arr_expected[3],ret_allocated_ip[3] ) ||
		DHCPCountFree(dhcp1) != count_free   )	
	{
		printf("line: %d \n" , __LINE__ );
		status_result =  TRUE;
		puts("Failes in: AllocateIP || CountFree ");
	}

	for( idx = 0 ; idx < BYTES_IN_IP; ++idx )
	{
		if( 1 == idx) continue;

		result = DHCPFreeIP(dhcp1, requested_ip[idx]);

		if( DOUBLE_FREE_FAIL != result ||
			DHCPCountFree(dhcp1) != count_free )
		
		{
			printf("line: %d \n" , __LINE__ );
			status_result =  TRUE;
			puts("Failes in: DHCPFreeIP || CountFree ");
		}
	}

	for( idx = 0 ; idx < 2; ++idx )
	{

		result = DHCPFreeIP(dhcp1, arr_expected[idx]);

		if( SUCCESS != result ||
			DHCPCountFree(dhcp1) != ++count_free )
		
		{
			printf("line: %d \n" , __LINE__ );
			status_result =  TRUE;
			puts("Failes in: DHCPFreeIP ");
		}

	}




	DHCPDestroy(dhcp1);
	dhcp1 = NULL;

	
	if( !status_result  )
	{
		puts(RESET);		
		puts(BACK_BLUE"Test: Success"RESET);

	}

	else
	{
		puts(BACK_YELLOW"Test: Failure"RESET);	
	}


}


/************************************************************/
/****************** CompareRetIp *****************/
/************************************************************/
static int 	CompareRetIp(ip_addrs_t expected_ip, ip_addrs_t ret_ip )
{
	uint8_t i = 0;
	for(i = 0; i < BYTES_IN_IP ; ++i )
	{
		if( expected_ip[i] != ret_ip[i] )
		{
			return FAIL;
		}
	}

	return SUCCESS;
}




	
