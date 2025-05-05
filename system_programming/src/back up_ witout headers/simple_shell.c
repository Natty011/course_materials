/***************************************
 * Author : Natty
 * Reviewer : Sauser
 * Date : 05 / 10 / 2025
 * Last update: 15 / 03 / 2025
 *****************************************/

#include <stdio.h>	 	 /* printf, fgets  */
#include <stdlib.h>	  	 /* exit, EXIT_SECCESS, EXIT_FAILURE */
#include <string.h>	  	 /* strcmp */
#include <unistd.h>	  	 /* fork, execv*/
#include <sys/wait.h> 	 /* wait */
#include <sys/types.h> 	 /* pid_t */
#include "utils.h"		 /* ExitIfBad, msg */

#define UNUSED(var) ((void)var)

#define BUFFER_SIZE (501)
#define MAX_STRINGS (20)

void GetInput(char buffer[], size_t buff_len);
void Tokenizer(char *buffer, char *myargv[], size_t my_argc);
int RunProgram(char **myargv);
void ExitIfBad(int is_good, const char *msg);
void IsExit(char *buffer);
/*
 Read a line of input from stdin.
*/

int main() 
{
	char buffer[BUFFER_SIZE] = {0};
	char *my_argv[MAX_STRINGS] = {NULL};

	while ( 1 )
	{
		GetInput(buffer, BUFFER_SIZE); /* read*/

		IsExit(buffer);

		Tokenizer(buffer, my_argv, MAX_STRINGS); /* parse*/

		RunProgram(my_argv); /* execute*/

	}

	return 0;
}

/* Read a line of input from stdin. */

void GetInput(char buffer[], size_t buff_len)
{
	fgets(buffer, buff_len, stdin);
	ExitIfBad( ('\n' == buffer[strlen(buffer) - 1]),  msg[1] );
}
/* If the user want to exit from the shell */

void IsExit(char *buffer)
{
	char *token = NULL;
	token = strtok(buffer, " ,\n");

	if (0 == strcmp(token, "exit")) 
	{
		ExitIfBad(FALSE, "");
	}
}

/* Store the arrguments in the array of strings. */

void Tokenizer(char *buffer, char *my_argv[], size_t my_argc)
{
	char *token = NULL;
	int i = 0;
	token = strtok(buffer, " ,\n");

	ExitIfBad(NULL != token, msg[5]);

	while (NULL != token)
	{
		ExitIfBad(i < (int)my_argc, msg[4]);
		my_argv[i++] = token;
		token = strtok(NULL, " ,\n");

	}
}
/* create proccess child for execute the command of the user . */

int RunProgram(char **my_argv)
{
	pid_t pid = fork();

	if (0 == pid)
	{
		execv(my_argv[0], my_argv);
		ExitIfBad(FALSE , msg[3]);
	}

	else if( pid > 0 )
	{
		wait(NULL);
	}

	else
	{
		ExitIfBad(FALSE, msg[0]);
	}

	return SUCCESS; 
}
