/******************************************************************************
*	Version 1.0
******************************************************************************/
#ifndef __QUEUE_H__     /* __QUEUE_H__  */
#define __QUEUE_H__     /* __QUEUE_H__  */

#include <stddef.h>     /* size_t       */
typedef struct queue queue_t;

/******************************************************************************
*
*       Name: QueueCreate
*       Description: Creates a queue data structure object
*       Arguments: N\A
*       Complexity: O(1)
*       Return: A newly initialized 'queue_t' struct or NULL  
*               if allocation fails
* 
******************************************************************************/
queue_t *QCreate(void);

/******************************************************************************
*       Name: QueueDestroy
*       Description: Destroys a queue data structure 
*       Arguments:  * 'queue' - The queue object to destroy
*       Complexity: O(n) + system call complexity
*       Return: N\A
*       Notes:  if 'queue' is a NULL no operations will be performed
* 
******************************************************************************/
void QDestroy(queue_t *queue);

/******************************************************************************
*       Name : QueueEnqueue
*       Description: Inserts an element to the back of a queue
*       Arguments:  * 'queue' - The queue to be inserted into
*                   * 'data' - The data of the new element
*       Complexity: O(1)
*       Return: Returns SUCCESS (0) if successful, FAIL (1) if not
*       Notes: Undefined behaviour if 'queue' is  NULL 
* 
******************************************************************************/
int QEnqueue(queue_t *queue, const void *data);



/******************************************************************************
*
*       Name: QueueDequeue
*       Description: Removes the first element in the front of a queue
*       Arguments:  * 'queue' - The queue object
*       Complexity: O(1)
*       Return: N\A
*       Notes: Undefined behaviour if 'queue' is a NULL object or
*               if 'queue' is empty
* 
******************************************************************************/
void QDequeue(queue_t *queue);

/******************************************************************************
*
*       Name: QueueAppend
*       Description: Appends two queues together
*       Arguments:  * 'dest' - The main queue object
*                   * 'src' - The concatinated queue , 
*       Complexity: O(1)
*       Return: Returns the start of the queue ('dest')
*       Notes: Undefined behaviour if 'queue' is a NULL object
*              src remains a valid empty queue
******************************************************************************/
queue_t *QAppend(queue_t *dest, queue_t *src);



/******************************************************************************
*
*       Name: QueuePeek
*       Description: Gets the data of the first element from the front
*       Arguments:  * 'queue' - The queue object
*       Complexity: O(1)
*       Return: Returns the data of the first element from the front
*       Notes: Undefined behaviour if 'queue' is a NULL object
* 
******************************************************************************/
void *QPeek(const queue_t *queue);



/******************************************************************************
*
*       Name: QueueIsEmpty
*       Description: Checks if a queue is empty
*       Arguments:  * 'queue' - The queue object
*       Complexity: O(1)
*       Return: Returns 'TRUE' (1) if empty, 'FALSE' (0) if not
*       Notes: Undefined behaviour if 'queue' is a NULL object
* 
******************************************************************************/
int QIsEmpty(const queue_t *queue);



/******************************************************************************
*
*       Name: QueueSize
*       Description: Gets the element count of a queue
*       Arguments:  * 'queue' - The queue object
*       Complexity: O(n)
*       Return: Returns the number of elements of a queue
*       Notes: Undefined behaviour if 'queue' is a NULL object
* 
******************************************************************************/
size_t QSize(const queue_t *queue);


#endif                  /* __QUEUE_H__  */
