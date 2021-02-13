/*
* File Name - queue.c
* Developer - Itay Adi Yosef
*/

#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */

#include "slist.h"
#include "queue.h"

struct queue
{
    slist_t *slist;
};

/*---------------------------------------------------------------------------*/

queue_t *QCreate(void)
{
	queue_t *que = NULL;

	if (!(que = (queue_t *)malloc(sizeof(queue_t))))
	{
		return (NULL);
	}

	if (!(que->slist = SListCreate()))
	{
		free (que);
		que = NULL;

		return (NULL);
	}

	return (que);
}

/*---------------------------------------------------------------------------*/

void QDestroy(queue_t *queue)
{
	assert(queue);
	
	SListDestroy(queue->slist);

	queue->slist = NULL;

	free(queue);
	
	queue = NULL;
}

/*---------------------------------------------------------------------------*/

size_t QSize(const queue_t *queue)
{
	assert(queue);

	return (SListCount(queue->slist));
}

/*---------------------------------------------------------------------------*/

int QIsEmpty(const queue_t *queue)
{
	assert(queue);

	return(QSize(queue) == 0);
}

/*---------------------------------------------------------------------------*/

int QEnqueue(queue_t *queue, void *data)
{
	slist_iter_t rear = NULL;
	slist_iter_t result = NULL;

	assert(queue);

	rear = SListEnd(queue->slist);
	result = SListInsert(queue->slist, rear, data);

	return (rear != result);
}

/*---------------------------------------------------------------------------*/

void QDequeue(queue_t *queue)
{
	slist_iter_t front = NULL;

	assert(queue);

	front = SListBegin(queue->slist);

	SListRemove(queue->slist, front);
}

/*---------------------------------------------------------------------------*/

void *QPeek(const queue_t *queue)
{
	slist_iter_t front = NULL;

	assert(queue);
	
	front = SListBegin(queue->slist);

	return (SListGetData(front));
}

/*---------------------------------------------------------------------------*/

void QAppend(queue_t *dest, queue_t *src)
{
	assert(dest);
	assert(src);

	SListAppend(dest->slist, src->slist);
}

/*---------------------------------------------------------------------------*/








































