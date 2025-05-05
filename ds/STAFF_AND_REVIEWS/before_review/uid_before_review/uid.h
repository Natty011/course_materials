/******************************************************************************
*	Version 0.5
******************************************************************************/
#ifndef __UID_H__       /* __UID_H__    			*/
#define __UID_H__       /* __UID_H__    			*/

#include <sys/types.h>  /* pid_t, time_t, size_t	*/

typedef struct uid
{
    pid_t pid;
    time_t time;
    size_t counter;
    char ip_addr[14];
} ilrd_uid_t;

/******************************************************************************
 * 
*   Description: A "bad" UID object, used to compare with other UID objects
*                In-order to check their validity
* 
*/  extern const ilrd_uid_t BADUID;
/*
******************************************************************************/

/******************************************************************************
*
*       Description: Creates a UID object
*       Arguments: N\A
*       Complexity: Dependant on system complexity
*       Return: A new unique identifier
*
*/      ilrd_uid_t UIDCreate(void);
/*
******************************************************************************/

/******************************************************************************
*
*       Description: Checks if two UID objects are equal
*       Arguments: Pointer to a priority function
*       Complexity: Dependant on system complexity
*       Return: A new empty priority queue, returns NULL on failure
*
*/      int UIDIsSame(ilrd_uid_t uid_1, ilrd_uid_t uid_2);
/*
******************************************************************************/

#endif                  /* __UID_H__    			*/
