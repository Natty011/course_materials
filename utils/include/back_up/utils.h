/***************************************
 * Author : Natty
 * Reviewer : 
 * Date : 26 / 03 / 2025
 * Last update: 26 / 03 / 2025
 *****************************************/

#ifndef __UTILS__     /* __UTILS__  */
#define __UTILS__     /* __UTILS__  */

#include <stdlib.h>    /* exit */
#include <stdio.h>
#include <errno.h>

#define RETURN_IF_BAD(cond, retval, msg) \
    if (!(cond)) { perror(msg); return (retval); }

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

extern char *msg[];  /* declared here, defined in utils.c */

void ExitIfBad(int is_good, const char *msg);


 
#endif                  /* ___UTILS___  */




