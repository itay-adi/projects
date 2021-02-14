/*
* File Name - pqueue_test.c
* Developer - Itay Adi Yosef
*/

/***************************User's declarations********************************/

#include <stdio.h> /*printf*/

#include "pqueue.h"

/**********************assistance functions declarations***********************/

int PQCompare(const void *data1, const void *data2, void *param);
int PQIsMatch(const void *data1, const void *data2, void *param);

/************************Test function declarations****************************/

void PQSizeTest(const pqueue_t *pqueue);
void PQIsEmptyTest(const pqueue_t *pqueue);
void PQPeekTest(const pqueue_t *pqueue);
void PQClearTest(pqueue_t *pqueue);
void PQEraseTest(pqueue_t *pqueue, void *data, pqueue_is_match_func_t is_match, void *param);
void PQEnqueueTest(pqueue_t *pqueue, void *data);
void PQDequeueTest(pqueue_t *pqueue);

/**********************Test case function declarations*************************/

void PQTestCase(void);

/**********************************main****************************************/

int main(void)
{
	printf("--------------------------------------------\n");
	PQTestCase();
	printf("--------------------------------------------\n");

	return (0);
}

/************************Test function implemintations*************************/

void PQSizeTest(const pqueue_t *pqueue)
{
	printf("\nNumber of elements in the list is: %ld\n", PQSize(pqueue));
}

/**********************************************************************/

void PQIsEmptyTest(const pqueue_t *pqueue)
{
	printf("\nIs empty:\n");
	printf("The list is");
	PQIsEmpty(pqueue) ? printf (" ") : printf (" not ");
	printf("empty\n");
}

/**********************************************************************/

void PQPeekTest(const pqueue_t *pqueue)
{
	if(PQIsEmpty(pqueue))
	{
		printf("No elements to show.\n");
	}

	else
	{
		printf("The first element in the list is: %d\n",
		*(int *)PQPeek(pqueue));
	}
}

/**********************************************************************/

void PQClearTest(pqueue_t *pqueue)
{
	PQClear(pqueue);

	printf("\nClear: List has been cleared.\n");
}

/**********************************************************************/

void PQEraseTest(pqueue_t *pqueue, void *data, pqueue_is_match_func_t is_match, void *param)
{
	printf("\nErase:\n");	

	if (PQErase(pqueue, data, is_match, param))
	{
		printf("The data was found and removed.\n");
	}

	else
	{
		printf("The data was not found.\n");
	}
}

/**********************************************************************/

void PQEnqueueTest(pqueue_t *pqueue, void *data)
{
	printf("\nPQ Enqueue:\n");
	printf("Enqueue has been ");
	!PQEnqueue(pqueue, data) ? printf("succeeded.\n") : printf("failed.\n");
}

/**********************************************************************/

void PQDequeueTest(pqueue_t *pqueue)
{
	printf("\nPQ Dequeue:\n");

	printf("%d was removed successfully.\n", *(int *)PQDequeue(pqueue));
}

/**********************assistance functions Implementations********************/

int PQCompare(const void *data1, const void *data2, void *param)
{
	(void)param;

	if(*(int *)data1 > *(int *)data2)
	{
		return (1);
	}

	else if(*(int *)data1 < *(int *)data2)
	{
		return (-1);
	}

	return (0);
}

/**********************************************************************/

int PQIsMatch(const void *data1, const void *data2, void *param)
{
	(void)param;

	return(*(int *)data1 == *(int *)data2);
}

/********************Test case function Implementations************************/

void PQTestCase(void)
{
	pqueue_t *pq = NULL;
	int num1 = 1;
	int num2 = 2;
	int num3 = 3;
	int num4 = 4;
	int *num_ptr1 = &num1;
	int *num_ptr2 = &num2;
	int *num_ptr3 = &num3;
	int *num_ptr4 = &num4;
	
	/*creates a new pqueue*/
	pq = PQCreate(PQCompare, NULL);
	PQSizeTest(pq);
	PQIsEmptyTest(pq);
	PQPeekTest(pq);

	/*insert new elements*/
	PQEnqueueTest(pq, num_ptr1);
	PQEnqueueTest(pq, num_ptr2);
	PQEnqueueTest(pq, num_ptr3);
	PQEnqueueTest(pq, num_ptr4);
	PQSizeTest(pq);
	PQIsEmptyTest(pq);
	PQPeekTest(pq);

	/*using Erase function*/
	PQEraseTest(pq, num_ptr4, PQIsMatch, NULL);
	PQEraseTest(pq, num_ptr4, PQIsMatch, NULL);

	/*removing one element*/
	PQDequeueTest(pq);
	PQSizeTest(pq);
	PQIsEmptyTest(pq);
	PQPeekTest(pq);

	/*cleares the queue*/
	PQClearTest(pq);
	PQSizeTest(pq);
	PQIsEmptyTest(pq);

	/*Destroy the pqueue*/
	PQDestroy(pq);
}

/******************************************************************************/






























