/***************************************
 * Author : Natty
 * Reviewer : 
 * Date : 26 / 03 / 2025
 * Last update: 05 / 04 / 2025
 *****************************************/

#ifndef __UTILS__     /* __UTILS__  */
#define __UTILS__     /* __UTILS__  */

#include <stdio.h>  /* perror */
#include <stdlib.h> /* exit, abort */
#include <errno.h>	/*perror*/
#include <assert.h>

#define SUCCESS (0)
#define FAIL    (1)

/*
int x = 42;
PRINT_IF_DEBUG("x is %d", x);
*/
#ifndef NDEBUG
	#define PRINT_IF_DEBUG(fmt, val) \
		fprintf(stderr, "[DEBUG] " fmt " at line %d:\n",val,  __LINE__)
#endif

/* Returns 'ret_val' if 'cond' is false, prints msg to stderr */
#define RETURN_IF_BAD(cond, ret_val, msg) \
    if (!(cond))                          \
    {                                     \
		fprintf(stderr, "[ERROR] at line %d: %s\n", __LINE__, msg); \
        return (ret_val);                 \
	}
/* Exits the program if 'cond' is false, prints msg */
#define EXIT_IF_BAD(cond, msg)   \
    if (!(cond))                 \
    {                            \
		fprintf(stderr, "[ABORT] at line %d: %s\n", __LINE__, msg); \
        exit(FAIL);              \
    }

/* Aborts if 'cond' is false, prints msg */
#define ABORT_IF_BAD(cond, msg) \
    if (!(cond))                \
    {                           \
        fprintf(stderr, "[EXIT] at line %d: %s\n", __LINE__, msg); \
        abort();                \
    }


enum
{
	FALSE = 0,
	TRUE = 1
};

/* declared here, defined in utils.c */
/*
extern char *msg[];  

void ExitIfBad(int is_good, const char *msg);
*/

 
#endif                  /* ___UTILS___  */




