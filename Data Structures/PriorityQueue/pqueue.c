/*
* File Name - pqueue.c
* Developer - Itay Adi Yosef
*/

/******************************************************************************/

#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */
#include <stdbool.h> /* true, false */

#include "pqueue.h"
#include "sorted_list.h"
#include "sorted_list.c"

struct pqueue
{
    sorted_list_t *sorted_list;
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

	pq->sorted_list = SortedListCreate(IsBefore, pq);

	if (!pq->sorted_list)
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

	SortedListDestroy(pqueue->sorted_list);
	
	free(pqueue);
	pqueue = NULL;
}

/******************************************************************************/

size_t PQSize(const pqueue_t *pqueue)
{
	assert(pqueue);

	return (SortedListSize(pqueue->sorted_list));
}

/******************************************************************************/

int PQIsEmpty(const pqueue_t *pqueue)
{
	assert(pqueue);

	return (SortedListIsEmpty(pqueue->sorted_list));
}

/******************************************************************************/

int PQEnqueue(pqueue_t *pqueue, void *data)
{
	assert(pqueue);

	return (SortedListIterIsEqual(SortedListInsert(pqueue->sorted_list, data), 
							  SortedListEnd(pqueue->sorted_list)));
}

/******************************************************************************/

void *PQDequeue(pqueue_t *pqueue)
{
	assert(pqueue);

	return (SortedListPopFront(pqueue->sorted_list));
}

/******************************************************************************/

void *PQPeek(const pqueue_t *pqueue)
{
	assert(pqueue);

	return (SortedListGetData(SortedListBegin(pqueue->sorted_list)));
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

void *PQErase(pqueue_t *pqueue, pqueue_is_match_func_t is_match, void *param)
{
	sorted_list_iter_t iter = {0};
	void *data = NULL; 

	assert (pqueue);

	iter = SortedListBegin(pqueue->sorted_list);

	while(!SortedListIterIsEqual(iter, SortedListEnd(pqueue->sorted_list)))
	{
		if ((is_match(param, SortedListGetData(iter))))
		{
			data = SortedListGetData(iter);
			SortedListRemove(iter);

			break;
		}

		iter = SortedListNext(iter);
	}

	return (data);
}

/******************************************************************************/

int IsBefore(const void *data1, const void *data2, void *param)
{
	pqueue_t *pq = (pqueue_t *)param;

	if (pq->cmpare(data1, data2, pq->param) == -1)
	{
		return (true);
	}

	return (false);
}

/******************************************************************************/




















