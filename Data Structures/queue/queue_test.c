/*
* File Name - queue_test.c
* Developer - Itay Adi Yosef
*/

#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc, free */

#include "queue.h"
#include "slist.h"

struct queue
{
    slist_t *slist;
};

/*----------------------Test case function declarations-----------------------*/

void QCreateTestCase(void);
void QIsEmptyTest(queue_t *queue);
void QPeekTest(queue_t *queue);
void QAppendTestCase(void);

/*----------------------------------main--------------------------------------*/

int main(void)
{
	QCreateTestCase();
	printf("--------------------------------------------------\n");
	QAppendTestCase();
	printf("--------------------------------------------------\n");
		
	return (0);
}

/*--------------------Test case function implementations----------------------*/

void QCreateTestCase(void)
{
	int num1 = 3;
	int num2 = 5;
	int *num1_ptr = &num1;
	int *num2_ptr = &num2;
	queue_t *que = NULL;

	printf("Queue Create.\n");
	que = QCreate();
	printf("The number of elements in the queue is: %ld\n", QSize(que));
	QIsEmptyTest(que);
	printf("\nEntering a new element:\n");

	if(!(QEnqueue(que, num1_ptr)))
	{
		printf("The number of elements in the queue is: %ld\n", QSize(que));
	}

	QPeekTest(que);
	printf("\nEntering a new element:\n");

	if(!(QEnqueue(que, num2_ptr)))
	{
		printf("The number of elements in the queue is: %ld\n", QSize(que));
	}

	QPeekTest(que);
	printf("\nRemove:\n");
	QDequeue(que);
	QPeekTest(que);	
	printf("The number of elements in the queue is: %ld\n", QSize(que));
	QDestroy(que);
}

/*------------------------------------------------------*/

void QIsEmptyTest(queue_t *queue)
{
	printf("\nIs empty?\n");
	printf("The queue is");
	QIsEmpty(queue) ? printf(" ") : printf(" not ");
	printf("empty.\n");
}

/*------------------------------------------------------*/

void QPeekTest(queue_t *queue)
{
	printf("The first element in the queue is: %d\n", *(int *)QPeek(queue));
}

/*------------------------------------------------------*/

void QAppendTestCase(void)
{
	int num1 = 3;
	int num2 = 5;
	int num3 = 7;
	int num4 = 9;
	int *num1_ptr = &num1;
	int *num2_ptr = &num2;
	int *num3_ptr = &num3;
	int *num4_ptr = &num4;
	queue_t *que1 = NULL;
	queue_t *que2 = NULL;

	printf("Queues Create.\n");
	que1 = QCreate();
	que2 = QCreate();
	printf("\nEntering elements to the first queue:\n");

	if((!(QEnqueue(que1, num1_ptr))) && (!(QEnqueue(que1, num2_ptr))))
	{
		printf("The number of elements in the queue is: %ld\n", QSize(que1));
	}

	printf("\nEntering elements to the second queue:\n");

	if((!(QEnqueue(que2, num3_ptr))) && (!(QEnqueue(que2, num4_ptr))))
	{
		printf("The number of elements in the queue is: %ld\n", QSize(que2));
	}

	printf("\nAppend:\n");
	QAppend(que1,que2);
	printf("\nThe number of elements in the queue is: %ld\n", QSize(que1));
	QDestroy(que1);
	QDestroy(que2);
}

/*------------------------------------------------------*/



















