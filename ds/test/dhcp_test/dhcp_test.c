/***************************************
* Author : Natty
* Reviewer : ???
* Date : 05 / 03 / 2025
* Last update: 08 / 03 / 2025
*****************************************/

#include <stdio.h> 		/* printf, puts  */


#include <assert.h>
#include <string.h> 	/* strcpy, strcmp */
#include <stdlib.h> 	/* calloc, free */
#include <time.h> 		/* clock */
#include <stdint.h> 	/* uint8_t*/

#include "dhcp.h" 

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

/***************End of struct and enum declaration *******/

/***************************function declaration**************************/
static void TestDhcp(void);
static void TestDhcp2(void);
static void TestDHCPAllAddresses(void);
static int
	 	CompareRetIp(ip_addrs_t expected_ip, ip_addrs_t ret_ip );

static int AllocateNextIP(dhcp_t *dhcp, ip_addrs_t allocated_ip);
static void PrintIP(const char *msg, const ip_addrs_t ip);
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
/*
	puts(BLUE"====================================================="RESET);
	printf("%sTEST: %s "RESET" \n", background,  mode);
   	puts(BACK_BLUE"'TestDhcp()'"RESET);
	TestDhcp();
	*/
/*
	puts(BLUE"====================================================="RESET);
	printf("%sTEST: %s "RESET" \n", background,  mode);
   	puts(BACK_BLUE"'TestDhcp2()'"RESET);
	TestDhcp2();
*/
	puts(BLUE"====================================================="RESET);

	puts(BLUE"====================================================="RESET);
	printf("%sTEST: %s "RESET" \n", background,  mode);
   	puts(BACK_BLUE"'TestDHCPAllAddresses()'"RESET);
	TestDHCPAllAddresses();

	puts(BLUE"====================================================="RESET);


	return 0;
}

/************************************************************/
/************************  TestDhcp  ************************/
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

	/*
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

*/
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
/***********************  TestDhcp2  ************************/
/************************************************************/

static void TestDhcp2(void)
{	

	int result = FALSE, status_result = FALSE, idx = 0; 
	dhcp_t *dhcp1 = NULL;
	ip_addrs_t ip = {192, 168, 2, 5};

	ip_addrs_t requested_ip[10] ={ {192, 168, 0, 0}, { 0 },
		 {192, 168, 63, 254 }, {192, 168, 63, 255 } , 
		 {192, 168, 0, 255 }, {192, 168, 0, 255 } } ;
	ip_addrs_t ret_allocated_ip[10] =  { { 0 } } ;
	ip_addrs_t arr_expected[10] = { {192, 168, 0, 1} , { 192, 168, 0, 2 } ,
	{ 0 }, { 0 },  {192, 168, 0, 255 }, {192, 168, 1, 0 } };

	size_t bits_num_in_subnet1 = 18, count_free = 0;

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
	/*
	printf("count_free = %lu\n", count_free);
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

	
	result = DHCPAllocateIP(dhcp1, requested_ip[4], ret_allocated_ip[4]);
	
	#ifdef PRINTS

		/*printf("ret_allocated_ip_test = {%u, %u, %u, %u} \n", 
				ret_allocated_ip[4][0], ret_allocated_ip[4][1],
				ret_allocated_ip[4][2], ret_allocated_ip[4][3]);*/
	#endif

	if( SUCCESS != result || 
		CompareRetIp(arr_expected[4],ret_allocated_ip[4] ) ||
		DHCPCountFree(dhcp1) != --count_free   )	
	{
		printf("line: %d \n" , __LINE__ );
		status_result =  TRUE;
		puts("Failes in: AllocateIP || CountFree ");
	}

	result = DHCPAllocateIP(dhcp1, requested_ip[5], ret_allocated_ip[5]);
	
	#ifdef PRINTS

		/*
		printf("ret_allocated_ip_test = {%u, %u, %u, %u} \n", 
				ret_allocated_ip[5][0], ret_allocated_ip[5][1],
				ret_allocated_ip[5][2], ret_allocated_ip[5][3]);
		*/
	#endif

	if( REQUEST_NOT_MET != result || 
		CompareRetIp(arr_expected[5],ret_allocated_ip[5] ) ||
		DHCPCountFree(dhcp1) != --count_free   )	
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
		puts(BACK_RED"Test: Failure"RESET);	
	}

}



/************************************************************/
/***********************  TestDhcp3  ************************/
/************************************************************/

static void TestDHCPAllAddresses(void)
{	

	
	dhcp_t *dhcp;
	ip_addrs_t subnet = {192, 168, 1, 0};  /* לדוגמה: 192.168.1.0  */
/* host_bits = 10 => bits_num_in_subnet = 32 - 10 = 22 */
	ip_addrs_t *allocated_ips = NULL;
	size_t subnet_bits = 22;
	size_t free_before = 0, free_after = 0;
	size_t allocated_count = 0, expected_free = 0, i = 0;

	printf("\n===== התחלת בדיקת הקצאה ושחרור לכל הכתובות (HOST_BITS = 10) =====\n");

	dhcp = DHCPCreate(subnet, subnet_bits);
	if (!dhcp)
	{
		printf("שגיאה: DHCPCreate נכשל\n");
		return;
	}
	printf("DHCP נוצר בהצלחה.\n");
	
		/*   נבדוק את מספר הכתובות הפנויות בתחילה  */
	free_before = DHCPCountFree(dhcp);
	printf("מספר כתובות פנוי בתחילה: %lu\n", free_before);
	
	/* נבצע הקצאה לכל הכתובות הזמינות*/
	allocated_count = 0;
	expected_free = free_before;

	allocated_ips = (ip_addrs_t*)malloc(free_before * sizeof(ip_addrs_t));
	if (!allocated_ips)
	{
		printf("שגיאה: כשל בזיכרון עבור מערך ההקצאות.\n");
		DHCPDestroy(dhcp);
		return;
	}
	
	while (AllocateNextIP(dhcp, allocated_ips[allocated_count]))
	{
		size_t current_free = DHCPCountFree(dhcp);
		allocated_count++;
		expected_free--; 
		if (current_free != expected_free)
		 {
			printf("שגיאה: מספר הכתובות הפנויות אינו תואם אחרי הקצאה %zu. צפוי: %zu, קיים: %zu\n",
					allocated_count, expected_free, current_free);
		}
		/* במידה ורוצים להדפיס עבור כל הקצאה, אפשר להפעיל את השורה הבאה:*/
		printf("הקצאה %zu: ", allocated_count), PrintIP("", allocated_ips[allocated_count-1]);
	}
	
	printf("סך כל כתובות שהוקצו: %zu\n", allocated_count);
	printf("מספר כתובות פנוי בסיום ההקצאות: %zu\n", DHCPCountFree(dhcp));
	
	/* כעת, נבצע שחרור של כל הכתובות שהוקצו, ובכל פעם נבדוק את מספר הכתובות הפנויות*/
	for ( i = 0; i < allocated_count; i++) 
	{
		int res = DHCPFreeIP(dhcp, allocated_ips[i]);
		if (res != SUCCESS)
		{
			printf("שגיאה: שחרור כתובת מסוימת נכשל, כתובת: %u.%u.%u.%u\n",
					allocated_ips[i][0], allocated_ips[i][1],
					allocated_ips[i][2], allocated_ips[i][3]);
		}

		else
		{
			free_after = DHCPCountFree(dhcp);
			expected_free++;
			if (free_after != expected_free)
			{
				printf("שגיאה: מספר כתובות פנוי אינו עולה כמצופה לאחר שחרור %zu. צפוי: %zu, קיים: %zu\n",
						i+1, expected_free, free_after);
			}
		}
	}
	
	printf("מספר כתובות פנוי לאחר שחרור כל ההקצאות: %zu\n", DHCPCountFree(dhcp));
	
	free(allocated_ips);
	DHCPDestroy(dhcp);
	printf("DHCP שוחרר מהזיכרון.\n");
	printf("===== סיום בדיקת הקצאה ושחרור לכל הכתובות =====\n");
}




/************************************************************/
/*********************** CompareRetIp ***********************/
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



/************************************************************/
/*********************** AllocateNextIP *********************/
/************************************************************/
	
static int AllocateNextIP(dhcp_t *dhcp, ip_addrs_t allocated_ip)
 {
    int res = DHCPAllocateIP(dhcp, NULL, allocated_ip);
    return  (res == SUCCESS || res == REQUEST_NOT_MET);
}

/************************************************************/
/*********************** PrintIP ****************************/
/************************************************************/

/* פונקציה להדפסת כתובת IP */
static void PrintIP(const char *msg, const ip_addrs_t ip)
{
    printf("%s %u.%u.%u.%u\n", msg, ip[0], ip[1], ip[2], ip[3]);
}