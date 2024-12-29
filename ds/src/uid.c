/***************************************
* Author : Natty
* Reviewer : 
* Date : 29 / 12 / 2024
* Last update: 29 / 12 / 2024
*****************************************/
#include <stdio.h>
#include <sys/types.h>  /* pid_t, time_t, size_t	*/
#include <assert.h> 	/* assert */
#include <stdlib.h> 	/* malloc, free */
#include <ifaddrs.h> 	/* getifaddrs */
#include <time.h>       /* time_t*/
#include <unistd.h>  /* getpid */
#include <sys/socket.h> /* socket */
#include <string.h> /* memcpy */
#include <arpa/inet.h> /* sockaddr_in */
#include "uid.h" 

/****************struct and enum declaration*********************/

const ilrd_uid_t BADUID = {0, 0, 0, {0} };

typedef enum
{
	
	FALSE = 0,
	TRUE = 1
	
}func_result_t;

/***************End of struct and enum declaration *******/
int main()
{

	int i = 0;
	ilrd_uid_t uid = {0};
	uid = UIDCreate();

	printf("uid.ip_addr: \n", uid.ip_addr);	
	for( i = 0; i<14; ++i)
	{
		printf("%d", uid.ip_addr[i]);
	}
	puts("");	
	puts(uid.ip_addr);
	/*printf("uid.ip_addr = %p \n", uid.ip_addr);*/
	/*printf("uid.ip_addr_string = %s \n", uid.ip_addr);*/
	printf("counter = %lu \n", uid.counter);
	printf("time = %lu \n", uid.time);
	printf("pid = %u \n", uid.pid);
			
	return 0;
}
/********************  UIDCreate  ****************************/
ilrd_uid_t UIDCreate(void)
{
	ilrd_uid_t uid;
	struct ifaddrs *ifaddr, *ifa;
	
	/*
	struct sockaddr_in *sa;
    char *addr;
	*/
	static size_t count = 0;
	static size_t flag = 0;
	
	if(1 == flag)
	{	
		++count;
		uid.counter = count;
	}
	
	else
	{
		uid.counter = count;
		flag = 1;
	}
	
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

	/*puts(ifa->ifa_addr->sa_data);*/

	/*
	sa = (struct sockaddr_in *) ifa->ifa_addr;
	addr = inet_ntoa(sa->sin_addr);
	*/
	/*memcpy(uid.ip_addr, addr, 14);*/
	
	memcpy(uid.ip_addr, ifa->ifa_addr->sa_data, 14);
/*
	puts(ifaddr->ifa_name);

	puts(uid.ip_addr);
*/
	uid.pid = getpid();
	
	/*uid.time = time(NULL);	*/
	time(&(uid.time));
	
    freeifaddrs(ifaddr);
	ifaddr = NULL;	
	
	return uid;
}

/********************  UIDIsSame  ****************************/

int UIDIsSame(ilrd_uid_t uid_1, ilrd_uid_t uid_2)
{

}





