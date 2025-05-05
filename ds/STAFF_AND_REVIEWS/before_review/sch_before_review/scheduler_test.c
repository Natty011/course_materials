/***************************************
* Author : Natty
* Reviewer : Chen
* Date : 01 / 01 / 2025
* Last update: 04 / 01 / 2025
*****************************************/

#include <stdio.h> 		/* printf, puts,  */
#include "scheduler.h"
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

typedef enum
{

	OPERATION_FAIL = -3,
	SYSTEM_FAIL = -2,
	STOPPED = -1,
	SUCCESS = 0,
	FAIL = 1
		
}status_t;

typedef enum
{
	FAIL_FROM_RUN = -1,	
	FINISHED = 0,
	SHOULD_REPEAT = 1 /* not finished */
	
}task_result_t;

typedef struct
{
	scheduler_t* sch;
	ilrd_uid_t uid;
	
	
	
}op_sch_t;

/***************************function declaration**************************/
/*
static int CmpIpAddr(ilrd_uid_t uid_1, ilrd_uid_t uid_2 );
*/
static int op_func1(void *user_param );
static int op_func2(void *user_param );
static void SchedulerTest(void);
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
    puts(GREEN"'SchedulerTest()'");
    puts(GREEN"TEST RUNNING - PLEASE WAIT...");    
    SchedulerTest();
	puts(BLUE"====================================================="RESET);

     
return 0;
}

static void SchedulerTest(void)
{
	
	int flag = TRUE;
			
	char* str1 = "Hello World";
	char* str2 = "GoodBye World";
	
	int status1 = -5;
	scheduler_t* sch1 = SchedulerCreate();

	ilrd_uid_t uid1 = BADUID;
	ilrd_uid_t uid2 = BADUID;
	ilrd_uid_t uid3 = BADUID;
	/*
	op_sch_t _sch1;
	 
	op_sch_t _sch2;
	
	_sch2.sch = sch1;
	_sch2.uid = uid2;
	*/
	puts(RED);
	puts(RESET);	

	if(SchedulerSize(sch1) != 0 || !SchedulerIsEmpty(sch1))
	{
		puts("Failes in : Size & IsEmpty");
		flag = FALSE;
	}
	
	uid1 = SchedulerAdd(sch1, op_func1, str1, 1);

	if(UIDIsSame(uid1, BADUID))
	{
		puts("Failes in  :Add -> BADUID Process");
		
		flag = FALSE;	
	}
	
	if( SchedulerIsEmpty(sch1)  || SchedulerSize(sch1) != 1)
	{
		puts("Failes in : IsEmpty & Size ");
		flag = FALSE;	
	}
		
	status1 = SchedulerRun(sch1);
	printf(" status1 = %d \n", status1);
	if(SchedulerSize(sch1) != 0 || !SchedulerIsEmpty(sch1))
	{
		puts("Failes in : Run & Size & IsEmpty");
		flag = FALSE;
	}
	
	
	
	uid1 = SchedulerAdd(sch1, op_func1, str1, 1);	
	uid2 = SchedulerAdd(sch1, op_func2, str2, 2);
	
	/*SchedulerStop(sch1);*/
	printf(" status1 = %d \n", status1);
	if(UIDIsSame(uid2, BADUID) )
	{
		puts("Failes in  :Add -> BADUID Process");		
		flag = FALSE;	
	}
	
	if( SchedulerIsEmpty(sch1)  || SchedulerSize(sch1) != 2)
	{
		puts("Failes in : IsEmpty & Size ");
		flag = FALSE;	
	}
	
	status1 = SchedulerRun(sch1);		
	
	if(SchedulerSize(sch1) != 0 || !SchedulerIsEmpty(sch1))
	{
		puts("Failes in : Size & IsEmpty & Add");
		flag = FALSE;
	}
		
	printf(" status1 = %d \n", status1);
	puts(RESET);	
	if(flag)
	{		
		puts(GREEN"SchedulerTest: Success"RESET);
	}
	
	
	
	puts(RESET);
	
	SchedulerDestroy(sch1);	

}

/*******************op_function*********************/

static int op_func1(void *user_param )
{
	static int count = 0;
		
	if(2 == count)
	{
		/*SchedulerStop((scheduler_t*)user_param);*/
		/*printf("user_param.to_stop = %d\n", user_param->sch);*/
		puts("enter_stop1");
		/*return FINISHED;	*/	

	}
	
	if(5 != count)
	{

		count++;
		printf("count1 = %d \n", count);
		return SHOULD_REPEAT;
	}
	 
	return FINISHED;	
}

static int op_func2(void *user_param )
{
	static int count = 0;

	if(2 == count)
	{
		puts("enter_stop2");
		/*SchedulerStop((scheduler_t*)user_param);*/


	}		
	
	if(5 != count)
	{

		count++;
		printf("count2 = %d \n", count);
		return SHOULD_REPEAT;
	}
	
	return FINISHED;	
}
	
/*
static int op_func2(void *user_param )
{
	static int count = 0;
	
	if(5 != count)
	{
		puts((char*)user_param);
		count++;
		printf("count = %d \n", count);
		
		return SHOULD_REPEAT;
	}	 

	return FINISHED;	
}

*/


/*

int flag = TRUE;	
	ilrd_uid_t uid1 = BADUID;
	ilrd_uid_t uid2 = BADUID;
	ilrd_uid_t uid3 = BADUID;
	
			
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
*/
/********************  CmpIpAddr  ****************************/
/*
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

*/



