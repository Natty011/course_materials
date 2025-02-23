/***************************************
* Author : Natty
* Reviewer : Chen
* Date : 01 / 01 / 2025
* Last update: 04 / 01 / 2025
*****************************************/

#include <stdio.h> 		/* printf, puts,  */
#include "heap_scheduler.h"
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
	ilrd_uid_t uid1;
	
}op_sch_t;

/***************************function declaration**************************/
/*
static int CmpIpAddr(ilrd_uid_t uid_1, ilrd_uid_t uid_2 );
*/
static int op_func1(void *user_param );
static int op_func2(void *user_param );
static int op_func3(void *user_param );/*stop */
static int op_func4(void *user_param );/* remove*/
static int op_func5(void *user_param );/*clear */
static void HeapSchedulerTest(void);
/***************************End of function declaration******************/
	int flag = TRUE;
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
    puts("'HeapSchedulerTest()'");
    puts("TEST RUNNING - PLEASE WAIT...");    
    HeapSchedulerTest();
	puts(BLUE"====================================================="RESET);

     
return 0;
}

static void HeapSchedulerTest(void)
{
	
	/*int flag = TRUE;*/
/*			
	char* str1 = "Hello World";
	char* str2 = "GoodBye World";
*/	
	int status1 = -5;
	scheduler_t* sch1 = HeapSchedulerCreate();

	ilrd_uid_t uid1 = BADUID;
	ilrd_uid_t uid2 = BADUID;
	ilrd_uid_t uid3 = BADUID;
	ilrd_uid_t uid4 = BADUID;
	ilrd_uid_t uid5 = BADUID;
	

	/* 
	op_sch_t sch22;
	op_sch_t sch33;

	sch11.sch = sch1;
	sch11.uid = uid1;
			
	sch22.sch = sch1;
	sch22.uid = uid2;

	sch33.sch = sch1;
	sch33.uid = uid3;
*/	
	op_sch_t sch11;	
	op_sch_t sch44 ;

	
			
	/*puts(RED);*/
	/*puts(RESET);	*/

	if(HeapSchedulerSize(sch1) != 0 || !HeapSchedulerIsEmpty(sch1))
	{
		puts("Failes in : Size & IsEmpty");
		flag = FALSE;
	}
	
	uid1 = HeapSchedulerAdd(sch1, op_func1, &sch1, 1);

	if(UIDIsSame(uid1, BADUID))
	{
		puts("Failes in  :Add -> BADUID Process");
		
		flag = FALSE;	
	}
	
	if( HeapSchedulerIsEmpty(sch1)  || HeapSchedulerSize(sch1) != 1)
	{
		puts("Failes in_1 : IsEmpty & Size ");
		flag = FALSE;	
	}
		
	status1 = HeapSchedulerRun(sch1);
	/*printf(" status1 = %d \n", status1);*/
	if(HeapSchedulerSize(sch1) != 0 || !HeapSchedulerIsEmpty(sch1))
	{
		puts("Failes in : Run & Size & IsEmpty");
		flag = FALSE;
	}
	
	
	
	uid1 = HeapSchedulerAdd(sch1, op_func1, sch1, 2);	
	uid2 = HeapSchedulerAdd(sch1, op_func2, sch1, 3);
	uid3 = HeapSchedulerAdd(sch1, op_func3, sch1, 3);	
	uid4 = HeapSchedulerAdd(sch1, op_func1, sch1, 3);

	sch44.sch = sch1;
	sch44.uid = uid2;
	
	/*printf("sch44->uid = %p \n", sch44.uid);	*/
	/*HeapSchedulerStop(sch1);*/
	/*printf(" status1 = %d \n", status1);*/
	if(UIDIsSame(uid2, BADUID) )
	{
		puts("Failes in  :Add -> BADUID Process");		
		flag = FALSE;	
	}
	
	if( HeapSchedulerIsEmpty(sch1)  || HeapSchedulerSize(sch1) != 4)
	{
		puts("Failes in_2 : IsEmpty & Size ");
		flag = FALSE;	
	}
	
	status1 = HeapSchedulerRun(sch1);		
	
	if(HeapSchedulerSize(sch1) != 1 || HeapSchedulerIsEmpty(sch1) || STOPPED != status1)
	{
		puts("Failes in : Size & IsEmpty & Add & Stop");
		flag = FALSE;
	}
		
	/*printf(" status1 = %d \n", status1);*/

	/*printf("sch44->uid = %p \n", sch44.uid);*/
/*	
	sch44.sch = sch1;
	sch44.uid = &uid2;	
*/	
	uid5 = HeapSchedulerAdd(sch1, op_func4, &sch44, 1);	
	
	sch44.uid1 = uid5;	
	
	/*printf("sch44->uid = %p \n", sch44.uid);*/
	if( HeapSchedulerIsEmpty(sch1)  || HeapSchedulerSize(sch1) != 2)
	{
		puts("Failes in_3 : IsEmpty & Size ");
		flag = FALSE;	
	}	
	
	status1 = HeapSchedulerRun(sch1);
				
	/*printf(" status1 = %d \n", status1);*/
	/*printf("size0 = %lu \n", HeapSchedulerSize(sch1));*/
						
	if( HeapSchedulerSize(sch1) != 0)
	{
		puts("Failes in_4 : Size ");
		flag = FALSE;	
	}
	

	uid3 = HeapSchedulerAdd(sch1, op_func2, sch1, 4);
	uid4 = HeapSchedulerAdd(sch1, op_func5, sch1, 1);
		
	if( HeapSchedulerSize(sch1) != 2)
	{
		puts("Failes in_5 : Size ");
		flag = FALSE;	
	}	
	
	status1 = HeapSchedulerRun(sch1);

	if( HeapSchedulerSize(sch1) != 0 || SUCCESS != status1)
	{
		puts("Failes in_4 : Size ");
		flag = FALSE;	
	}

	sch11.sch = sch1;
	sch11.uid = uid3;
	sch11.uid1 = uid4;		

	/*printf(" status1 = %d \n", status1);	*/
	/*printf("size5 = %lu \n", HeapSchedulerSize(sch1));*/					
	/*puts(RESET);*/	
	if(flag)
	{		
		puts("HeapSchedulerTest: Success");
	}
		
	puts(RESET);
	
	HeapSchedulerDestroy(sch1);	

}

/*******************op_function*********************/

static int op_func1(void *user_param )
{
	static int count = 0;
	(void)user_param;
	if(5 != count)
	{
		count++;
		/*printf("count1 = %d \n", count);*/
		return SHOULD_REPEAT;
	}
	 
	return FINISHED;	
}

static int op_func2(void *user_param )
{
	static int count = 0;
	(void)user_param;
	if(2 == count)
	{
		/*puts("enter_stop2");*/
		/*HeapSchedulerStop((scheduler_t*)user_param);*/
	}		
	/*	printf("size = %lu \n", HeapSchedulerSize((scheduler_t*)user_param));*/	
	if(5 != count)
	{
		

		count++;
		/*printf("count2 = %d \n", count);*/
		return SHOULD_REPEAT;
	}
	
	return FINISHED;	
}
	

static int op_func3(void *user_param )
{
	static int count = 0;

	if(2 == count)
	{
		/*printf("count3_stop = %d \n", count);		*/
		HeapSchedulerStop((scheduler_t*)user_param);
		/*printf("size = %lu \n", HeapSchedulerSize((scheduler_t*)user_param));	*/
		return FINISHED;

	}
		 	
	if(5 != count)
	{
		/*printf("count3 = %d \n", count);*/		
		count++;
		
		return SHOULD_REPEAT;
	}	 

	return FINISHED;	
}

static int op_func4(void *user_param )
{
	static int count = 0;
	int to_remove = -5;
	size_t size = 0;
	op_sch_t* remove_1 = (op_sch_t*)(user_param);
	size = HeapSchedulerSize(remove_1->sch);
	
	/*printf("remove_1->uid = %p \n", remove_1->uid);*/
	if(1 == count)
	{
		if(  2 != size )
		{
			puts("Failes in_5 : size ");
			flag = FALSE;	
		}
		
		/*printf("count4_stop = %d \n", count);	*/
		/*printf("size1 = %lu \n", HeapSchedulerSize(remove_1->sch));	*/			
		to_remove = HeapSchedulerRemove(remove_1->sch, remove_1->uid );
		size = HeapSchedulerSize(remove_1->sch);
		
		if(  1 != size ||   0 != to_remove)
		{
			puts("Failes in_1 : Remove ");
			flag = FALSE;	
		}
		/*printf(" to_remove = %d \n", to_remove);*/
		/*printf("size2 = %lu \n", HeapSchedulerSize(remove_1->sch));*/	
		/*return FINISHED;*/

	}

	to_remove = -5;	
	if (4 == count )
	{
		/*printf("size3 = %lu \n", HeapSchedulerSize(remove_1->sch));*/				
		to_remove = HeapSchedulerRemove(remove_1->sch, remove_1->uid1 );
		
		if(  1 != size ||   0 != to_remove)
		{
			puts("Failes in_2: Remove ");
			flag = FALSE;	
		}
		/*printf("size4 = %lu \n", HeapSchedulerSize(remove_1->sch));	*/			
	}	 	
	if(5 != count)
	{
		/*printf("count4 = %d \n", count);	*/	
		count++;
		
		return SHOULD_REPEAT;
	}	 

	return FINISHED;	
}

static int op_func5(void *user_param )
{
	static int count = 0;
	
	size_t size = 0;
	/*printf("size5 = %lu \n", HeapSchedulerSize((scheduler_t*)user_param));*/	
	if(2 == count)
	{
	
		size = HeapSchedulerSize((scheduler_t*)user_param);
	/*printf("size6 = %lu \n", HeapSchedulerSize((scheduler_t*)user_param));*/	
	/*	printf("count5_stop = %d \n", count);*/
		
		if(  2 != size )
		{
			puts("Failes in_1 : Clear ");
			flag = FALSE;	
		}
				
		HeapSchedulerClear((scheduler_t*)user_param);
		
		size = HeapSchedulerSize((scheduler_t*)user_param);		
		if(  1 != size )
		{
			puts("Failes in_2 : Clear ");
			flag = FALSE;	
		}
	/*printf("size7 = %lu \n", HeapSchedulerSize((scheduler_t*)user_param));*/	
		/*return FINISHED;*/

	}
		 	
	if(5 != count)
	{
		/*printf("count5 = %d \n", count);	*/	
		count++;
		
		return SHOULD_REPEAT;
	}	 

	return FINISHED;	
}





