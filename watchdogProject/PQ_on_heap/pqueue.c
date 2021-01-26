/*
* File Name - pqueue.c
* Description - Exercises from ds
* Developer - Itay Adi Yosef
* Reviewer - Matan Y
* Review Date - 29/6/20
*/

/******************************************************************************/

#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */
#include <stdbool.h> /* true, false */

#include "pqueue.h"
#include "heap.h"

struct pqueue
{
    heap_t *heap;
	pqueue_cmp_func_t cmpare;
	void *param;
};

/******************************************************************************/

int IsBefore(const void *data1, const void *data2, void *param);

/******************************************************************************/

pqueue_t *PQCreate(pqueue_cmp_func_t cmpare, void *param)
{
	pqueue_t *pq = NULL;

	pq = (pqueue_t *)malloc(sizeof(pqueue_t));

	if (!pq)
	{
		return (NULL);
	}

	pq->heap = HeapCreate(cmpare, NULL);

	if (NULL == pq->heap)
	{
		free (pq);
		pq = NULL;

		return (NULL);
	}

	pq->cmpare = cmpare;
	pq->param = param;

	return (pq);
}

/******************************************************************************/

void PQDestroy(pqueue_t *pqueue)
{
	assert (pqueue);

	HeapDestroy(pqueue->heap);
	
	free(pqueue);

	pqueue = NULL;
}

/******************************************************************************/

size_t PQSize(const pqueue_t *pqueue)
{
	assert(pqueue);

	return (HeapSize(pqueue->heap));
}

/******************************************************************************/

int PQIsEmpty(const pqueue_t *pqueue)
{
	assert(pqueue);

	return (HeapIsEmpty(pqueue->heap));
}

/******************************************************************************/

int PQEnqueue(pqueue_t *pqueue, void *data)
{
	assert(pqueue);

	return (HeapPush(pqueue->heap, data));
}

/******************************************************************************/

void *PQDequeue(pqueue_t *pqueue)
{
	assert(pqueue);

	return (HeapPop(pqueue->heap));
}

/******************************************************************************/

void *PQPeek(const pqueue_t *pqueue)
{
	assert(pqueue);

	return (HeapPeek(pqueue->heap));
}

/******************************************************************************/

void PQClear(pqueue_t *pqueue)
{
	assert(pqueue);
	
	while (!PQIsEmpty(pqueue))
	{
		PQDequeue(pqueue);
	}
}

/******************************************************************************/

void *PQErase(pqueue_t *pqueue, void *data, pqueue_is_match_func_t is_match, void *param)
{
	assert (pqueue);

	return (HeapRemove(pqueue->heap, data, is_match, param));
}

/******************************************************************************/




















