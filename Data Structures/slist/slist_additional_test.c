/*
* File Name - slist_additional_test.c
* Developer - Itay Adi Yosef
*/

/***************************User's declarations********************************/

#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc, free */

#include "slist_additional.h"

/*******************************Test cases*************************************/

void FlipTestCase(void);
void LoopTestCase(void);
void IntersectionTestCase(void);

/**********************************main****************************************/

int main(void)
{
	FlipTestCase();
	printf("--------------------------------------------------\n");
	LoopTestCase();
	printf("--------------------------------------------------\n");
	IntersectionTestCase();
	printf("--------------------------------------------------\n");

	return (0);
}

/************************Test function implemintations*************************/

void FlipTestCase(void)
{
	int num1 = 5;
	int num2 = 9;
	int num3 = 12;

	int *ptr_num1 = &num1;
	int *ptr_num2 = &num2;
	int *ptr_num3 = &num3;

	node_t *node1 = NULL;
	node_t *node2 = NULL;
	node_t *node3 = NULL;
	node_t *temp = NULL;

	node1 = CreateNode();
	node2 = CreateNode();
	node3 = CreateNode();

	node1->data = ptr_num1;
	node2->data = ptr_num2;
	node3->data = ptr_num3;

	node1->next = node2;
	node2->next = node3;
	node3->next = NULL;

	printf("Before the flip:\n");
	printf("The elements are:\n");

	temp = node1;

	while(temp)
	{
		printf("%d, ", *(int *)temp->data);
		temp = temp->next;
	}

	RecursiveFlip(node1);
	printf("\n\nAfter the flip:\n");
	printf("The elements are:\n");
	
	temp = node3;

	while(temp)
	{
		printf("%d, ", *(int *)temp->data);
		temp = temp->next;
	}

	printf("\n");
	
	free(node1);
	free(node2);
	free(node3);
}

/******************************************************************************/

void LoopTestCase(void)
{
	int num1 = 5;
	int num2 = 9;
	int num3 = 12;

	int *ptr_num1 = &num1;
	int *ptr_num2 = &num2;
	int *ptr_num3 = &num3;

	node_t *node1 = NULL;
	node_t *node2 = NULL;
	node_t *node3 = NULL;

	node1 = CreateNode();
	node2 = CreateNode();
	node3 = CreateNode();

	node1->data = ptr_num1;
	node2->data = ptr_num2;
	node3->data = ptr_num3;

	node1->next = node2;
	node2->next = node3;
	node3->next = NULL;

	printf("\nFirst try:\nThere is");
	HasLoop(node1) ? printf(" a loop.\n") : printf(" no loop.\n");

	node3->next = node1;

	printf("\nSecond try:\nThere is");
	HasLoop(node1) ? printf(" a loop.\n") : printf(" no loop.\n");
	
	free(node1);
	free(node2);
	free(node3);
}

/******************************************************************************/

void IntersectionTestCase(void)
{
	int num1 = 5;
	int num2 = 9;
	int num3 = 12;
	int num4 = 15;
	int num5 = 16;

	int *ptr_num1 = &num1;
	int *ptr_num2 = &num2;
	int *ptr_num3 = &num3;
	int *ptr_num4 = &num4;
	int *ptr_num5 = &num5;

	node_t *node1 = NULL;
	node_t *node2 = NULL;
	node_t *node3 = NULL;
	node_t *node4 = NULL;
	node_t *node5 = NULL;

	node1 = CreateNode();
	node2 = CreateNode();
	node3 = CreateNode();
	node4 = CreateNode();
	node5 = CreateNode();

	node1->data = ptr_num1;
	node2->data = ptr_num2;
	node3->data = ptr_num3;

	node4->data = ptr_num4;
	node5->data = ptr_num5;

	node1->next = node2;
	node2->next = node3;
	node3->next = NULL;

	node4->next = node5;
	node5->next = node1;
	

	if(FindIntersection(node1, node4))
	{
		printf("The first element which is an intersection is: %d\n", 
		*(int*)(FindIntersection(node1, node4)->data));
	}

	else
	{
		printf("There is no intersection.\n");
	}	
}

/******************************************************************************/



















