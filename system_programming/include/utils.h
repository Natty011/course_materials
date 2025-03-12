/******************************************************************************
*	Version         0.2
*   Last Update:    15/01/25    17:17
******************************************************************************/

#ifndef __UTILS__     /* __UTILS__  */
#define __UTILS__     /* __UTILS__  */

#include <stddef.h>     /* size_t       */

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


 char *msg[] = {"fork failed\n", "fgets failed\n", "strtok failed\n",
	"execvp failed\n", "Too many arguments\n",
 "Empty line is not allowed\n", "SIGINT terminated the proccess\n"};



/*
    Description: 
    Arguments: 
    Return: 
    Note: 

*/
void ExitIfBad(int is_good, const char *msg)
{
	if (FALSE == is_good) 
	{
		perror(msg);
		exit(0);
	}
}

    
#endif                  /* ___UTILS___  */




