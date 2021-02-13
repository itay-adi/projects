/*
* File Name - c_buffer_test.c
* Developer - Itay Adi Yosef
*/

#include <stdio.h> /* printf */
#include <stddef.h> /* size_t */
#include <string.h> /* strerror */
#include <errno.h> /* errno */

#include "c_buffer.h"

struct c_buffer 
{
    size_t read;
    size_t size;
    size_t capacity;
    char buffer[1];
};

/*----------------------Test case function declarations-----------------------*/

void CBufferIsEmptyTest(const c_buffer_t *c_buffer);
void CBufferCapacityTest(const c_buffer_t *c_buffer);
void CBufferFreeSpaceTest(const c_buffer_t *c_buffer);
void CBufferWriteTestCase(void);
void CBufferWriteErrorTestCase(void);
void CBufferReadTestCase(void);
void CBufferReadErrorTestCase(void);

/*----------------------------------main--------------------------------------*/

int main(void)
{
	printf("----------------------------------\n\n");
	CBufferWriteTestCase();
	printf("\n----------------------------------\n\n");
	CBufferWriteErrorTestCase();
	printf("\n----------------------------------\n\n");
	CBufferReadTestCase();
	printf("\n----------------------------------\n\n");
	CBufferReadErrorTestCase();
	printf("\n----------------------------------\n\n");
	
	return (0);
}

/*--------------------Test case function implementations----------------------*/

void CBufferIsEmptyTest(const c_buffer_t *c_buffer)
{
	printf("The circular buffer is");
	CBufferIsEmpty(c_buffer) ? printf(" ") : printf(" not ");
	printf("empty.\n");
}

/*------------------------------------------------------*/

void CBufferCapacityTest(const c_buffer_t *c_buffer)
{
	printf("The capacity of the buffer is: %ld bytes\n", 
			CBufferCapacity(c_buffer));
}

/*------------------------------------------------------*/

void CBufferFreeSpaceTest(const c_buffer_t *c_buffer)
{
	printf("You have %ld bytes left in the buffer\n", 
			CBufferFreeSpace(c_buffer));
}

/*------------------------------------------------------*/

void CBufferWriteTestCase(void)
{
	c_buffer_t *cbuffer = NULL;
	char *ch = "abcd";
	ssize_t bytes_number = 0;
	size_t capacity = 8;

	printf("**Write**\n\n");
	cbuffer = CBufferCreate(capacity);
	CBufferIsEmptyTest(cbuffer);
	CBufferCapacityTest(cbuffer);
	CBufferFreeSpaceTest(cbuffer);
	bytes_number = CBufferWrite(cbuffer, ch, 4);

	if(bytes_number == -1)
	{
		printf("\n***Error: %s***\n\n", strerror(errno));
	}

	else
	{
		printf("The buffer is now contains: %s\n", cbuffer->buffer);
		printf("Number of bytes copied: %ld\n\n", bytes_number);
	}

	CBufferIsEmptyTest(cbuffer);
	CBufferCapacityTest(cbuffer);
	CBufferFreeSpaceTest(cbuffer);
	CBufferDestroy(cbuffer);
}

/*------------------------------------------------------*/

void CBufferReadTestCase(void)
{
	c_buffer_t *cbuffer = NULL;
	char *ch1 = "abcd";
	char ch2[10] = {'0'};
	ssize_t bytes_number1 = 0;
	ssize_t bytes_number2 = 0;
	size_t capacity = 8;

	printf("**Read**\n\n");
	cbuffer = CBufferCreate(capacity);
	bytes_number1 = CBufferWrite(cbuffer, ch1, 4);

	if(bytes_number1 == -1)
	{
		printf("\n***Error: %s***\n\n", strerror(errno));
	}

	else
	{
		printf("Number of bytes written: %ld\n\n", bytes_number1);
	}

	CBufferIsEmptyTest(cbuffer);
	CBufferFreeSpaceTest(cbuffer);
	CBufferCapacityTest(cbuffer);
	bytes_number2 = CBufferRead(cbuffer, ch2, 5);

	if(bytes_number2 == -1)
	{
		printf("\n***Error: %s***\n\n", strerror(errno));
	}

	else
	{
		printf("Number of bytes read: %ld\n\n", bytes_number2);
		printf("The alternative buffer is now contains: %s\n", ch2);
	}

	CBufferIsEmptyTest(cbuffer);
	CBufferCapacityTest(cbuffer);
	CBufferFreeSpaceTest(cbuffer);
	CBufferDestroy(cbuffer);
}

/*------------------------------------------------------*/

void CBufferWriteErrorTestCase(void)
{
	c_buffer_t *cbuffer = NULL;
	char *ch = "abcd";
	ssize_t bytes_number = 0;
	size_t capacity = 8;

	printf("**Write with error**\n\n");
	cbuffer = CBufferCreate(capacity);
	CBufferIsEmptyTest(cbuffer);
	CBufferCapacityTest(cbuffer);
	CBufferFreeSpaceTest(cbuffer);
	bytes_number = CBufferWrite(cbuffer, ch, 4);
	bytes_number = CBufferWrite(cbuffer, ch, 4);
	bytes_number = CBufferWrite(cbuffer, ch, 4);

	if(bytes_number == -1)
	{
		printf("\n***Error: %s***\n\n", strerror(errno));
	}

	else
	{
		printf("The buffer is now contains: %s\n", cbuffer->buffer);
		printf("Number of bytes copied: %ld\n\n", bytes_number);
	}

	CBufferIsEmptyTest(cbuffer);
	CBufferCapacityTest(cbuffer);
	CBufferFreeSpaceTest(cbuffer);
	CBufferDestroy(cbuffer);
}

/*------------------------------------------------------*/

void CBufferReadErrorTestCase(void)
{
	c_buffer_t *cbuffer = NULL;
	char ch2[10] = {'0'};
	ssize_t bytes_number = 0;
	size_t capacity = 8;

	printf("**Read with error:**\n\n");
	cbuffer = CBufferCreate(capacity);
	CBufferIsEmptyTest(cbuffer);
	CBufferFreeSpaceTest(cbuffer);
	CBufferCapacityTest(cbuffer);
	bytes_number = CBufferRead(cbuffer, ch2, 5);

	if(bytes_number == -1)
	{
		printf("\n***Error: %s***\n\n", strerror(errno));
	}

	else
	{
		printf("Number of bytes read: %ld\n\n", bytes_number);
		printf("The alternative buffer is now contains: %s\n", ch2);
	}

	CBufferDestroy(cbuffer);
}

/*------------------------------------------------------*/



