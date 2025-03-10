/***************************************
* Author : Natty
* Reviewer : ???
* Date : 05 / 03 / 2025
* Last update: 09 / 03 / 2025
*****************************************/


#ifdef PRINTS
#endif

#include <stdio.h> 		/* printf, fgets  */
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
#define MAX_STRINGS			( 20 )

/******************************************************************************/
/*********************  Typedef ip array  *************************************/
/******************************************************************************/


/******************************************************************************/
/***************************** Success / Fail Enum ****************************/
/******************************************************************************/

typedef enum
{
	BAD_PID = -1,
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

static char *msg[2] = { "Fork failed\n", "fgets failed\n", "strtok failed\n" };


/******************************************************************************/
/************************ static functions declartions ************************/
/******************************************************************************/
void GetInput(char buffer[] , size_t buff_len);
void Tokenizer(char *buffer, char *myargv[], size_t argv_size);
int RunProgram(char **myargv);
void ExitIfBad(int is_good, const char* msg);
/******************************************************************************/
/*******************End Of Static Functions declartions************************/
/******************************************************************************/

/*
 Read a line of input from stdin.

*/

int main(  ) /* int argc, char *argv[] */
{
	char buffer[BUFFER_SIZE] = {0};
	char *myargv[MAX_STRINGS] = {0};
	int res = 0;

	while( 1 )
	{
		GetInput(buffer, BUFFER_SIZE); /* read*/

		Tokenizer(buffer, myargv, MAX_STRINGS); /* parse*/

		RunProgram(myargv); /* execute*/

		ExitIfBad(res, msg[0]);

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

void GetInput(char buffer[] , size_t buff_len)
{
	ExitIfBad(  NULL != fgets(buffer, (int)buff_len, stdin), msg[1]);
}
/*
	Description: Store the arrguments in the array of strings.
*/
void Tokenizer(char *buffer, char *myargv[], size_t argv_size)
{
	char *token = NULL;
	token = strtok(buffer, " ,\n");
	int i = 1;

	ExitIfBad(NULL != token  , msg[2]);

	if( 0 == strcmp( token, "exit") )
	{
		exit(EXIT_SUCCESS);
	}
	myargv[0] = token;

	while (NULL != token)
	{
		token = strtok(NULL, " ,\n");
		/*ExitIfBad(NULL != token  , msg[2]);*/

		myargv[i++] = token;
	}
	
	myargv[i] = NULL;

}
/*
Description: create proccess child for execute 
		the command of the user .
	Return Value: ret_val4 
*/
int RunProgram(char **myargv)
{
	pid_t pid  = fork();

	ExitIfBad(BAD_PID != pid, msg[0]);

}

void ExitIfBad(int is_good, const char* msg)
{
	if ( FALSE == is_good) /* */
	{
		perror(msg);
		exit(EXIT_FAILURE);
	}
}

/*

pid_t pid = fork();
	int status = 0;

	if (BAD_PID == pid)
	{
		perror(msg[0]);
		return FAIL;
	}
	else if (0 == pid)
	{
		execvp(myargv[0], myargv);
		perror("execvp failed\n");
		return FAIL;
	}
	else
	{
		waitpid(pid, &status, 0);
	}

	return SUCCESS;
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