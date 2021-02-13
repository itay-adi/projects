/*
* File Name - stack.c
* Developer - Itay Adi Yosef
*/


#include <stdlib.h> /* malloc, free */
#include <stddef.h> /* size_t */
#include <assert.h> /* assert */

#include "stack.h"

struct stack
{
	void **head;
	void **top;
	size_t size;
	size_t capacity;
};

enum mode {SUCCESS = 0, FAIL = 1};

/******************************************************************************/

stack_t* StackCreate(size_t capacity)
{
	stack_t *stack_ptr = NULL;

	/*allocating memory for the stack itself*/
	if(!(stack_ptr = (stack_t *)malloc(sizeof(stack_t))))
	{
		return(NULL);
	}

	/*allocation memory for the top pointer*/
	if(!(stack_ptr->head = (void **)malloc(sizeof(void **) * capacity)))
	{
		free(stack_ptr);
	
		return(NULL);
	}
	
	stack_ptr->capacity = capacity;
	stack_ptr->top = stack_ptr->head - 1;
	stack_ptr->size = 0;
	
	return(stack_ptr);
}

/******************************************************************************/

int StackPush(stack_t *stack, void *element)
{
	assert(element);
	assert(stack);

	/*checks if the stack is full*/
	if(stack->size == stack->capacity)
	{
		return (FAIL);
	}
	
	++(stack->top);
	++(stack->size);
	*(stack->top) = element;

	return(SUCCESS);
}

/******************************************************************************/

void StackDestroy(stack_t *stack)
{
	assert(stack);

	free(stack->head);
	stack->head = NULL;

	free(stack);
	stack = NULL;
}

/******************************************************************************/

void StackPop(stack_t *stack)
{
	assert(stack);

	/*checks if the stack is not empty*/
	if(stack->size)
	{
		--(stack->top);
		--(stack->size);
	}
}

/******************************************************************************/

void *StackPeek(const stack_t *stack)
{
	assert(stack);

	/*checks if the stack is empty*/
	if(!(stack->size))
	{
		return (NULL);
	}

	return (stack->top);
}

/******************************************************************************/

int StackIsEmpty(const stack_t *stack)
{
	assert(stack);

    return (!(stack->size)); 
}

/******************************************************************************/

size_t StackSize(const stack_t *stack)
{
	assert(stack);

	return(stack->top - stack->head);
}

/******************************************************************************/












