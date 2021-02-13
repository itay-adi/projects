/*
* File Name - stack_test.c
* Developer - Itay Adi Yosef
*/

/******************************User declarations*******************************/

#include <stdio.h> /* printf */
#include <stddef.h> /* size_t */

#include "stack.h"

struct stack
    {
        void **head;
        void **top;
        size_t size;
		size_t capacity;
    };

/************************Test function declarations****************************/  

stack_t *StackCreateTest(stack_t *stack_ptr);
void StackPushTest(stack_t *stack_ptr);
void StackPopTest(stack_t *stack_ptr);
void StackPeekTest(stack_t *stack);
void StackDestroyTest(stack_t *stack_ptr);
void StackIsEmptyTest(stack_t *stack_ptr);
void StackSizeTest(stack_t *stack_ptr);

/***********************************main***************************************/

int main()
{
	stack_t *stack_ptr = NULL;

	stack_ptr = StackCreateTest(stack_ptr);
	printf("--------------------------------------------------\n");
	StackIsEmptyTest(stack_ptr);
	printf("--------------------------------------------------\n");
	StackPushTest(stack_ptr);
	printf("--------------------------------------------------\n");
	StackIsEmptyTest(stack_ptr);
	StackSizeTest(stack_ptr);
	printf("--------------------------------------------------\n");
	StackPeekTest(stack_ptr);
	printf("--------------------------------------------------\n");
	StackPopTest(stack_ptr);
	printf("--------------------------------------------------\n");
	StackDestroyTest(stack_ptr);
	printf("--------------------------------------------------\n");

	return (0);
}

/************************Test function implemintations*************************/  

stack_t *StackCreateTest(stack_t *stack_ptr)
{
	size_t capacity = 6;

	stack_ptr = StackCreate(capacity);
	printf("Stack of %ld elements has been created successfully. \n", capacity);
	
	return(stack_ptr);
}

/***********************************************************/

void StackPushTest(stack_t *stack_ptr)
{
	size_t num1 = 8;
	size_t num2 = 65;
	char *str = "Hello";

	size_t *num_ptr1 = &num1;
	size_t *num_ptr2 = &num2;

	if(StackPush(stack_ptr, (void *)num_ptr1))
	{
		printf("Stack is full, cannot push additional elements.\n");
	}
	
	else
	{
		printf("%ld Pushed successfully to the stack.\n", num1); 
	}

	if(StackPush(stack_ptr, (void *)num_ptr2))
	{
		printf("Stack is full, cannot push additional elements.\n");
	}
	
	else
	{
		printf("%ld Pushed successfully to the stack.\n", num2); 
	}

	if(StackPush(stack_ptr, (void *)str))
	{
		printf("Stack is full, cannot push additional elements.\n");
	}
	
	else
	{
		printf("%s Pushed successfully to the stack.\n", str); 
	}
}

/***********************************************************/

void StackDestroyTest(stack_t *stack_ptr)
{
	StackDestroy(stack_ptr);
	printf("The stack's memory has been freed successfully. \n");
}

/***********************************************************/

void StackPopTest(stack_t *stack_ptr)
{
	printf("Pop\n");
	StackPop(stack_ptr);
}

/***********************************************************/

void StackPeekTest(stack_t *stack)
{
	printf("The address on the top of the stack is: %p\n", StackPeek(stack));
}

/***********************************************************/

void StackIsEmptyTest(stack_t *stack_ptr)
{
	printf("Stuck is");
	StackIsEmpty(stack_ptr)? printf(" ") : printf(" not ");
	printf("empty.\n");
}

/***********************************************************/

void StackSizeTest(stack_t *stack_ptr)
{
	printf("The number of elements in the stuck is: %ld\n", stack_ptr -> size);
}

/***********************************************************/





