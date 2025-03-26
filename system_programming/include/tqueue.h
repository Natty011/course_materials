/******************************************************************************
*	Version         0.2
*   Last Update:    15/01/25    17:17
******************************************************************************/

#ifndef TQUEUE_H    /* TQUEUE_H */
#define TQUEUE_H    /* TQUEUE_H */
#include <stddef.h> /* size_t */

/*
* Data type to represent the FSQ that several
* comsumers and producers using it.
*/
typedef struct fsq tq_t;

/*
* Creat new  Fixed Size Queue
* Return pointer to the queue if seccess, else NULL.
*/
tq_t* TQCreate(size_t size);

/*
* Add number to the qeueue, waiting if the qeueue full.
*/
void TQEnqueue(tq_t *fsq, int num);

/*
* Take a number from the qeueue, waiting if there is
  an empty qeueue
*/
int TQDequeue(tq_t *fsq);

/*
*Free all the reasurce related to the qeueue
*/
void TQDestroy(tq_t *fsq);

#endif /* TQUEUE_H */
