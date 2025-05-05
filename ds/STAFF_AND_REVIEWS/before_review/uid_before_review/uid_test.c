/***************************************
* Author : Natty
* Reviewer : Matan
* Date : 29 / 12 / 2024
* Last update: 29 / 12 / 2024
*****************************************/

#include <stdio.h> 		/* printf, puts,  */

#include "uid.h" 

#define RED          "\x1b[31m"
#define GREEN        "\x1b[32m"
#define BLUE         "\x1b[34m"
#define RESET        "\x1b[0m"
#define YELLOW  "\x1b[43m"
#define MAGENTA "\x1b[45m"

#define DEBUG		"DEBUG MODE"
#define RELEASE		"RELEASE MODE"

#define IP_ADDR_LEN 14

typedef enum
{
	
	FALSE = 0,
	TRUE = 1
	
}func_result_t;


/***************************function declaration**************************/
static int CmpIpAddr(ilrd_uid_t uid_1, ilrd_uid_t uid_2 );
static void UidTest(void);
/***************************End of function declaration******************/

int main ()
{

	char* mode = RELEASE;
	char* background = MAGENTA;	
	
	#ifndef NDEBUG
		mode = DEBUG;
		background = YELLOW;
	#endif

	puts(BLUE"====================================================="RESET);
	printf("%sTEST: %s "RESET" \n", background,  mode);
    puts(GREEN"'UidTest()'");
    UidTest();
	puts(BLUE"====================================================="RESET);

     
return 0;
}

static void UidTest(void)
{
	int flag = TRUE;	
	ilrd_uid_t uid1 = BADUID;
	ilrd_uid_t uid2 = BADUID;
	ilrd_uid_t uid3 = BADUID;

	puts(RED);
		
	uid1 = UIDCreate();
	uid2 = UIDCreate();
		
	if(UIDIsSame(uid1, uid2))
	{
		puts("Failes in UidTest: Same counter");
		flag = FALSE;
	}
	
	if(!CmpIpAddr(uid1, uid2))
	{
		puts("Failes in UidTest: Different ip_addr");
		flag = FALSE;
	}
	
	if(uid1.pid != uid2.pid)
	{
		puts("Failes in UidTest: Different pid");
		flag = FALSE;
	}
	
	if(uid1.time != uid2.time)
	{
		puts("Failes in UidTest: Different time");
		flag = FALSE;		
	}
	
	if(uid1.counter == uid2.counter)
	{
		puts("Failes in UidTest: Same counter");
		flag = FALSE;	
	}

		
	if(UIDIsSame(uid1, uid3))
	{
		puts("Failes in UidTest: BADUID Process");
		flag = FALSE;	
	}

	if(flag)
	{		
		puts(GREEN"UidTest: Success"RESET);
	}	
}

/********************  CmpIpAddr  ****************************/
static int CmpIpAddr(ilrd_uid_t uid_1, ilrd_uid_t uid_2 )
{
	
	int i = 0;
		
	for( i = 0; i < IP_ADDR_LEN; ++i)
	{
		if(uid_1.ip_addr[i] != uid_2.ip_addr[i])
		{
			return FALSE;
		}
	}
	return TRUE;
}





