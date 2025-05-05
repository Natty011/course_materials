/***************************************
* Author : Natty
* Reviewer : Chen
* Date : 18 / 12 / 2024
* Last update: 18 / 12 / 2024
*****************************************/

#include <stdio.h> 		/* printf, puts,  */
#include <string.h> 	/* strcpy, strncmp */
#include "cbuffer.h" 


/***************************function declaration**************************/
static void TestString(void);
/***************************End of function declaration******************/

int main ()
{

	puts("=====================================================");
    puts("'TestString()'");
    TestString();
    puts("=====================================================");
     
return 0;
}


static void TestString(void)
{

	size_t res = 0;
	char* arr[4] = {"blabla", "NattyLevi", "Hello", "World" };
	char dest1[10] = { 0 };
	size_t cap1 = 10;
	
	cbuffer_t* cbuff1 = CBufferCreate(cap1);
	
	if( CBufferBuffSiz(cbuff1) != cap1 || CBufferIsEmpty(cbuff1) != 1  || 
	    CBufferFreeSpace(cbuff1) != cap1 )
	{
		puts("Failes in TestString: BuffSiz & IsEmpty & FreeSpace");
	}
	
	res = CBufferRead(cbuff1, dest1, 4);
	
	if( 0 != res  )
	{
		puts("Failes in TestString: Read");	
	}

	res = CBufferWrite(cbuff1, arr[0], 7);

	if(  7 != res || CBufferIsEmpty(cbuff1) != 0  || 
	    CBufferFreeSpace(cbuff1) != cap1 - 7 )
	{
		puts("Failes in TestString: Write & IsEmpty & FreeSpace");
	}
	
	res = CBufferRead(cbuff1, dest1, 4);
	
	if( 4 != res || strncmp("blab" , dest1, 4) || 
	    CBufferFreeSpace(cbuff1) != cap1 - 3 )
	{
		puts("Failes in TestString: Write & Read & res & FreeSpace");	
	}
	

	res = CBufferWrite(cbuff1, arr[1], 10);


	if(  7 != res || CBufferIsEmpty(cbuff1) != 0  || 
	    CBufferFreeSpace(cbuff1) != 0 )
	{
		puts("Failes in TestString: Write & IsEmpty & FreeSpace");
	}
	

	res = CBufferRead(cbuff1, dest1, 15);
		
	if( 10 != res || strncmp("la\0NattyLe" , dest1, 10) || 
	    CBufferFreeSpace(cbuff1) != cap1 || CBufferIsEmpty(cbuff1) != 1 )
	{
		puts("Failes in TestString: Write & Read & res & FreeSpace");	
	}		
		
	CBufferDestroy(cbuff1);

	puts("TestString Successed");				
}



