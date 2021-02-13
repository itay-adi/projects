/*
* File Name - slist_additional.h
* Developer - Itay Adi Yosef
*/

#ifndef ILRD_SLIST_ADD_H
#define ILRD_SLIST_ADD_H

#include <stddef.h> /* size_t */

typedef struct node
{
	void *data;
	struct node *next;
} node_t;

/******************************************************************************/

/*Flip:
  Revercse the order of the given slist.

  Return value: A pointer to the new flipped list.
*/ 
node_t *Flip(node_t *head);

/******************************************************************************/

node_t *RecursiveFlip(node_t *head);

/******************************************************************************/

/*HasLoop:
  Tells whether a given slist has loop.

  Return value: An integer which: 1 is loop, 0 no loop.
*/	
int HasLoop(node_t *head);


/******************************************************************************/
/*FindIntersection:
  Checks if two lists have a common element

  Return value: A pointer to the first common element, NULL if none.
*/
node_t *FindIntersection(node_t *head_1, node_t *head_2);


/******************************************************************************/

/*CreateNode:
  creates a node pointer

  Return value: A pointer to the new node.
*/ 
node_t *CreateNode(void);

/******************************************************************************/

/*SListCount
  counts how many elements we have in the list

  Return value: the number of elements we have in the list.
*/
size_t SListCount(node_t *head);

/******************************************************************************/

#endif /* ILRD_SLIST_ADD_H*/






















