/***************************************
* Author : Natty
* Reviewer : Matan
* Date : 29 / 12 / 2024
* Last update: 29 / 12 / 2024
*****************************************/

#include <sys/types.h>  	/* pid_t, time_t, size_t */
#include <ifaddrs.h> 		/* getifaddrs */
#include <time.h>       	/* time_t */
#include <unistd.h>  		/* getpid */
#include <string.h> 		/* memcpy */

#include "uid.h" 

#define IP_ADDR_LEN 14

/****************struct and enum declaration*********************/

const ilrd_uid_t BADUID = {0, 0, 0, {0} };

typedef enum
{
	
	FALSE = 0,
	TRUE = 1
	
}func_result_t;

/***************End of struct and enum declaration *******/

/***************************function declaration**************************/

static int CmpIpAddr(ilrd_uid_t uid_1, ilrd_uid_t uid_2 );

/***************************End of function declaration******************/

/********************  UIDCreate  ****************************/
ilrd_uid_t UIDCreate(void)
{
	ilrd_uid_t uid;
	struct ifaddrs *ifaddr, *ifa;
		
	static size_t count = 0;
	
	uid.counter = count;
	++count;
	
	if (-1 == getifaddrs(&ifaddr)) 
	{
        return BADUID;
    }
    
    /* Walk through linked list, maintaining head pointer so we
       can free list later */
       
    for(ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next)
    {
    	
    	if( NULL == ifa->ifa_addr )
    	{
        	continue;   	
    	}
    	
    	else
    	{
    		break;
    	}
	}
	
	memcpy(uid.ip_addr, ifa->ifa_addr->sa_data, IP_ADDR_LEN);

	uid.pid = getpid();
	
	time(&(uid.time));
	
    freeifaddrs(ifaddr);
    
	ifaddr = NULL;	
	
	return uid;
}

/********************  UIDIsSame  ****************************/

int UIDIsSame(ilrd_uid_t uid_1, ilrd_uid_t uid_2)
{
	return (uid_1.pid == uid_2.pid &&
	
			uid_1.time == uid_2.time &&
			
			uid_1.counter == uid_2.counter &&
			
			CmpIpAddr(uid_1, uid_2));
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



