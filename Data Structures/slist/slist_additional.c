/*
* File Name - slist_additional.c
* Developer - Itay Adi Yosef
*/

#include <stdio.h> /* NULL */
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc, free */

#include "slist_additional.h"

enum mode{NO_LOOP = 0, LOOP = 1};

/******************************************************************************/

node_t *Flip(node_t *head)
{
	node_t *prev = NULL;
	node_t *curr = NULL;
	node_t *next = NULL;

	assert (head);

	curr = head;

	while(curr)
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}

	head = prev;

	return (head);
}

/******************************************************************************/

node_t *RecursiveFlip(node_t *head)
{
	node_t *temp = NULL;

	if(NULL == head || NULL == head->next)
	{
		return (head);
	}

	temp = RecursiveFlip(head->next);
	head->next->next = head;
	head->next = NULL;

	return (temp);
}

/******************************************************************************/

node_t *CreateNode(void)
{
	node_t *node_ptr = NULL;

	if(!(node_ptr = (node_t *)malloc(sizeof(node_t))))
	{
		return (NULL);
	}

	return (node_ptr);
}

/******************************************************************************/

int HasLoop(node_t *head)
{
	node_t *slow = NULL;
	node_t *quick = NULL;

	assert(head);

	slow = head;
	quick = head;

	while (quick && quick->next)
	{
		slow = slow->next;
		quick = quick->next->next;
		
		if(slow == quick)
		{
			return (LOOP);
		}
	}

	return (NO_LOOP);
}

/******************************************************************************/

node_t *FindIntersection(node_t *head_1, node_t *head_2)
{
	int i = 0;
	int delta = 0;

	assert(head_1);
	assert(head_2);

	delta = SListCount(head_1) - SListCount(head_2);

	if(delta >= 0)
	{
		for(i = 0; i < delta; ++i)
		{
			head_1 = head_1->next;
		} 
	}

	else
	{
		delta *= -1;

		for(i = 0; i < delta; ++i)
		{
			head_2 = head_2->next;
		}
	}

	while(head_1 != head_2)
	{
		head_1 = head_1->next;
		head_2 = head_2->next;
	}

	return (head_1);	
}

/******************************************************************************/

size_t SListCount(node_t *head)
{
	size_t count = 0;

	assert(head);

	while(head)
	{
		++count;
		head = 	head->next;
	}

	return (count);
}

/******************************************************************************/















