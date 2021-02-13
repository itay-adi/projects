#ifndef ILRD_QUEUE_H
#define ILRD_QUEUE_H

#include <stddef.h>	/* size_t */

/* C file
#include "slist.h"

struct queue
{
    slist_t *slist;
}
*/

typedef struct queue queue_t;

/*---------------------------------------------------------------------------*/
/* QCreate:
*   - Creates an empty queue.
*
* Return Value:
*   - if succeeded, return a pointer to a queue.
*   - if failed, return NULL.
*/
queue_t *QCreate(void);

/*---------------------------------------------------------------------------*/
/* QDestroy:
*   - Destory a given queue.
*
* Args:
*   - queue - pointer to queue given by a user.
*
* Comments: 
*   - in case of invalid queue - undefined behavior.
*
*/
void QDestroy(queue_t *queue);

/*---------------------------------------------------------------------------*/
/* QSize:
*   - Counts the number of elements in a given queue.
*
* Args:
*   - queue - pointer to queue given by a user.
*
* Return Value:
*   - Number of elemnts in the queue.
*
* Comments: 
*   - in case of invalid queue - undefined behavior.
*
*/
size_t QSize(const queue_t *queue);

/*---------------------------------------------------------------------------*/
/* QIsEmpty
*   - Checks if a given queue is empty.
*
* Args:
*   - queue - pointer to queue given by a user.
*
* Return Value - boolean:
*   - 1 - the queue is empty (TRUE).
*   - 0 - the queue is not empty (FALSE).
*
* Comments: 
*   - in case of invalid queue - undefined behavior.
*
*/
int QIsEmpty(const queue_t *queue);

/*---------------------------------------------------------------------------*/
/* QEnqueue:
*   - Inserts a new element to the end of a given queue.
*
* Args:
*   - queue - pointer to a queue given by a user.
*   - data - data to store.
*  
* Return Value - status:
*   - 0 - on success.
*   - 1 - on failure. 
*
* Comments: 
*   - in case of invalid queue - undefined behavior.
*  
*/
int QEnqueue(queue_t *queue, void *data);

/*---------------------------------------------------------------------------*/
/* QDequeue:
*   - Remove an element from the beginning of a given queue.
*
* Args:
*   - queue - pointer to a queue given by a user.
*
* Comments: 
*   - in case of invalid queue - undefined behavior.
*   - in case of empty queue - undefined behaviour.
*/
void QDequeue(queue_t *queue);

/*---------------------------------------------------------------------------*/
/* QPeek:
*   - retrieves data which is set on the beginning of a given queue.
*
* Args:
*   - queue - pointer to a queue given by a user.
*
* Return Value:
*   - returns a pointer to the data.
*
* Comments: 
*   - in case of invalid queue - undefined behavior.
*/
void *QPeek(const queue_t *queue);

/*---------------------------------------------------------------------------*/
/* QAppend:
*   - Appends the src queue to the end of dest queue.
*
* Args:
*   - dest - pointer to a queue given by a user.
*   - src - pointer to a queue given by a user.
*
* Comments: 
*   - in case of invalid pointers - undefined behavior.
*   - src - becomes a pointer to an empty queue.
*   
*/
void QAppend(queue_t *dest, queue_t *src);

/*---------------------------------------------------------------------------*/

#endif /* ILRD_QUEUE_H */ 
