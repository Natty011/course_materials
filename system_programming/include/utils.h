/***************************************
 * Author : Natty
 * Reviewer : 
 * File : system_programming/include/utils.h  
 * version : 1.2
 * Date : 26 / 03 / 2025
 * Last update: 14 / 04 / 2025
 *****************************************/

#ifndef __UTILS__     /* __UTILS__  */
#define __UTILS__     /* __UTILS__  */

#include <stdio.h>  /* perror */
#include <stdlib.h> /* exit, abort */
#include <errno.h>	/*perror*/
#include <assert.h>

/*  example: #x is prints as a string like: 
DEBUG_VAR(myvar); equal to ->
printf("Value of myvar is %d\n", myvar);*/

#define DEBUG_VAR(x) printf("Value of " #x " is %d\n", x);

	#ifndef NDEBUG
	    #define PRINT_IF_DEBUG(fmt, val) \
		    fprintf(stderr, "" fmt " at line %d:\n",val,  __LINE__)
    #else
        #define PRINT_IF_DEBUG(fmt, val) ((void)0)
        
#endif

/* Returns 'ret_val' if 'cond' is false, prints msg to stderr */
#define RETURN_IF_BAD(cond, ret_val, msg) \
    if (!(cond))                          \
    {                                     \
		fprintf(stderr, "[ERROR] %s() at line %d: %s\n" ,__LINE__, msg); \
        return (ret_val);                 \
	}
/* Exits the program if 'cond' is false, prints msg */
#define EXIT_IF_BAD(cond, msg)   \
    if (!(cond))                 \
    {                            \
		fprintf(stderr, "[EXIT] at line %d: %s\n", __LINE__, msg); \
        exit(FAIL);              \
    }

/* Aborts if 'cond' is false, prints msg */
#define ABORT_IF_BAD(cond, msg) \
    if (!(cond))                \
    {                           \
        fprintf(stderr, "[ABORT] at line %d: %s\n", __LINE__, msg); \
        abort();                \
    }


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




