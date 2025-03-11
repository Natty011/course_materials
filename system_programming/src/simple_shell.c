/***************************************
 * Author : Natty
 * Reviewer : ???
 * Date : 05 / 10 / 2025
 * Last update: 11 / 03 / 2025
 *****************************************/

#ifdef PRINTS
#endif

#include <stdio.h>	   /* printf, fgets  */
#include <stdlib.h>	   /* exit, EXIT_SECCESS, EXIT_FAILURE */
#include <string.h>	   /* strcmp */
#include <unistd.h>	   /* fork, execv*/
#include <sys/wait.h>  /* wait */
#include <sys/types.h> /* pid_t */

/*#include "simple_shell.h"*/

#define UNUSED(var) ((void)var)

#define BUFFER_SIZE (501)
#define MAX_STRINGS (20)



enum
{
	BAD_PID = -1,
	SUCCESS = 0,
	FAIL = 1
};

enum
{
	FALSE = 0,
	TRUE = 1

};


static char *msg[] = {"fork failed\n", "fgets failed\n", "strtok failed\n",
					   "execvp failed\n", "Too many arguments\n",
					"Empty line is not allowed\n"};

void GetInput(char buffer[], size_t buff_len);
void Tokenizer(char *buffer, char *myargv[], size_t my_argc);
int RunProgram(char **myargv);
void ExitIfBad(int is_good, const char *msg);

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

		Tokenizer(buffer, my_argv, MAX_STRINGS); /* parse*/

		RunProgram(my_argv); /* execute*/

	}


	return 0;
}

/*
 Read a line of input from stdin.
*/

void GetInput(char buffer[], size_t buff_len)
{
	fgets(buffer, buff_len, stdin);
	ExitIfBad( ('\n' == buffer[strlen(buffer) - 1]),  msg[1] );
}
/*
Store the arrguments in the array of strings.
*/
void Tokenizer(char *buffer, char *my_argv[], size_t my_argc)
{
	char *token = NULL;
	int i = 0;
	token = strtok(buffer, " ,\n");

	ExitIfBad(NULL != token, msg[5]);

	/* להכניס את זה לפונקציה במטפלת בזה בנפרד ולא בפונקציית טוקנייזר*/
	/*למשל לא נכניס פקודת היסטורי לכן לא נרצה שיהיה בטוקיינזר לכן  נכניס את הבדיקה בפונקציה שהיא אחרי פונקציית הטוקיינזייר
	כי יתווספו לי בעתיד עוד פקוודת נוספות לא נרצה לטפל בהן בטוקינייזר */
	/*  למשל פונקציה שתטפל בזה  IfIsExit */
		/*  למשל פונקציה שתטפל בזה  IfIsHistory */

	if (0 == strcmp(token, "exit")) 
	{
		exit(EXIT_SUCCESS);
	}

	while (NULL != token)
	{
		ExitIfBad(i < (int)my_argc, msg[4]);
		my_argv[i++] = token;
		token = strtok(NULL, " ,\n");

	}
}
/*
Description: create proccess child for execute
		the command of the user .
*/
int RunProgram(char **my_argv)
{
	pid_t pid = fork();

	/*TODO: need to fix some codes lines */
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

void ExitIfBad(int is_good, const char *msg)
{
	if (FALSE == is_good) 
	{
		printf("%s", msg);
		exit(EXIT_FAILURE);
	}
}

