/***************************************
* Author : Natty
* Reviewer : ???
* Date : 05 / 03 / 2025
* Last update: 09 / 03 / 2025
*****************************************/

/*#define PRINTS*/
#ifdef PRINTS
	#include <stdio.h> /* printf, puts  */
#endif

#include <stdint.h>		/*uint8_t, uint32_t */
#include <assert.h> 	/* assert */
#include <stdlib.h> 	/* malloc, free */
#include <string.h> 	/* memcpy, memset, strcat,
							 strncat, strcpy, strcmp, strncpy */
#include <unistd.h> 	/* fork, execvp, chdir, close, dup2, pipe */
#include <sys/wait.h> 	/* waitpid */
#include <sys/types.h> 	/* pid_t */
#include <fcntl.h> 		/* open */
#include <errno.h> 		/* perror */
#include "simple_shell.h"

#define UNUSED( var )       ( (void)var )

#define BUFFER_SIZE			( 501 )
#define MAX_WORDS			( 20 )

/******************************************************************************/
/*********************  Typedef ip array  *************************************/
/******************************************************************************/


/******************************************************************************/
/***************************** Success / Fail Enum ****************************/
/******************************************************************************/

typedef enum
{
	SUCCESS = 0,
	FAIL = 1,
} result_t;

/******************************************************************************/
/******************************* True / False Enum ****************************/
/******************************************************************************/

typedef enum
{
	FALSE = 0,
	TRUE = 1
	
} op_result_t;


/******************************************************************************/
/***************************** Management struct ******************************/
/******************************************************************************/


/******************************************************************************/
/************************ static globals variables ****************************/
/******************************************************************************/



/******************************************************************************/
/************************ static functions declartions ************************/
/******************************************************************************/
void GetInput(char* buffer[BUFFER_SIZE] , size_t buff_len);
void Tokenizer(char *buffer, char *myargv[], size_t argv_size);
int RunProgram(char **myargv);

/******************************************************************************/
/*******************End Of Static Functions declartions************************/
/******************************************************************************/



int main(  ) /* int argc, char *argv[] */
{
	char buffer[BUFFER_SIZE] = {0};
	char *myargv[MAX_WORDS] = {0};
	while( 1 )
	{
		GetInput(buffer, BUFFER_SIZE);
		Tokenizer(buffer, myargv, MAX_WORDS);

	}


 /*argc will be the number of strings pointed to by argv( argument count ).
This will (in practice) be 1 plus the number of arguments.( with null in the end.
 argv = (argument vector)  
ret_val0 =  MakeProgramRunAndwaitForIt()

	*/

return 0;
}


/*
 Read a line of input from stdin.
 return: void
 param: char* buffer[BUFFER_SIZE] , size_t buff_len

*/

void GetInput(char* buffer[BUFFER_SIZE] , size_t buff_len)
{


}

void Tokenizer(char *buffer, char *myargv[], size_t argv_size)
{
	
}

int RunProgram(char **myargv)
{

}
/*
	Description: Store the arrguments in the array of strings.
	Return Value: ret_val3 
	
	
	ret_val3 SaperateIntputArgumetes (  char *argv[]  )  /
	{
	
	/* Using strtok( char *argv[], int delimeter )

	1.  get the start of the string into char* ptr token 
	2. strtok can get several tokens 
		saperate in comma. add '\n' delimeter.
	3. copy the strings  to arrays of parameter
		of token ( allocate with malloc for each token )
	while( token )
	{

	}

	/* 





/*
phase1: psudo  

/*
int main( int argc, char *argv[] ) 
{

/*
 argc will be the number of strings pointed to by argv( argument count ).
This will (in practice) be 1 plus the number of arguments.( with null in the end.
/* argv = (argument vector)  
ret_val0 =  MakeProgramRunAndwaitForIt()

	

return 0;
}
*/

/*

Description: Make running of the program the user typing.
Return Value: ret_val1 
 
ret_val1 MakeProgramRunAndwaitForIt(  args1  )
{

 ret_val2 GetInput (  args2  );



}

*/

/*
Description: get the commands that the user typing into the shell .
Return Value: ret_val2 
tokenayzer
/* buffer of 256 number of characther.
	create on the stack
ret_val2 GetInput (  args2  ) 
{
 
	/* read from stdout buffer 
	 
	}
	*/
	/*
	Description: Store the arrguments in the array of strings.
	Return Value: ret_val3 
	
	
	ret_val3 SaperateIntputArgumetes (  char *argv[]  )  /
	{
	
	/* Using strtok( char *argv[], int delimeter )

	1.  get the start of the string into char* ptr token 
	2. strtok can get several tokens 
		saperate in comma. add '\n' delimeter.
	3. copy the strings  to arrays of parameter
		of token ( allocate with malloc for each token )
	while( token )
	{

	}

	/* 
	
	}
	
	*/
	

	/*
	Description: create proccess child for execute 
		the command of the user .
	Return Value: ret_val4 
	
	
	ret_val4 CreateExecute (  args4  ) 
	{
	/* Using using 
	
	}
	
	*/
	
	/*
	phase2: sharping 


	while( 1 ):


	*/