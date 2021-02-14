/*
* File Name - c_buffer.c
* Developer - Itay Adi Yosef
*/

#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */
#include <errno.h> /* errno */

#include "c_buffer.h"

#define MIN(a,b) (a)<(b) ? (a):(b) 

struct c_buffer 
{
    size_t read;
    size_t size;
    size_t capacity;
    char buffer[1];
};

/******************************************************************************/

c_buffer_t *CBufferCreate(size_t capacity)
{
	c_buffer_t *cbuffer = NULL;

	cbuffer = (c_buffer_t*)malloc(offsetof(c_buffer_t, buffer) + 
			   sizeof(char) * capacity);

	if (NULL == cbuffer)
	{
		return (NULL);
	}

	cbuffer->capacity = capacity;
	cbuffer->size = 0;
	cbuffer->read = 0;

	return (cbuffer);
}

/******************************************************************************/

void CBufferDestroy(c_buffer_t *c_buffer)
{
	assert(c_buffer);

	free(c_buffer);
	
	c_buffer = NULL;
}

/******************************************************************************/

int CBufferIsEmpty(const c_buffer_t *c_buffer)
{
	assert(c_buffer);

	return(!(c_buffer->size));
}

/******************************************************************************/

size_t CBufferCapacity(const c_buffer_t *c_buffer)
{
	assert(c_buffer);

	return (c_buffer->capacity);
}

/******************************************************************************/

size_t CBufferFreeSpace(const c_buffer_t *c_buffer)
{
	assert (c_buffer);

	return(c_buffer->capacity - c_buffer->size);
}

/******************************************************************************/

ssize_t CBufferRead(c_buffer_t *c_buffer, void *dest, size_t count)
{	
	size_t index = 0;
	size_t real_count = 0;
	size_t bytes_copied = 0;

	assert(c_buffer);
	assert(dest);

	if (!(c_buffer->size))
	{
		errno = ENODATA;
		
		return (-1);
	}

	/*Real_count represents the real count we will do, which is the minimum
	between the "count" from the user and the "size" of the buffer*/
	real_count = MIN(count, c_buffer->size);

	while(real_count && dest)
	{
		/*We are in a circual struct, therefore we need to use % in order to
		turn the index back to zero*/
		index = (c_buffer->read) % (c_buffer->capacity);
		*(char *)dest = c_buffer->buffer[index];
		++(*(char *)&dest);
		--(c_buffer->size);
		++(c_buffer->read);
		--real_count;
		++bytes_copied;
	}

	return (bytes_copied);
}

/******************************************************************************/

ssize_t CBufferWrite(c_buffer_t *c_buffer, const void *src, size_t count)
{
	size_t index = 0;
	size_t real_count = 0;
	size_t bytes_copied = 0;

	assert(c_buffer);
	assert(src);

	if (c_buffer->capacity == c_buffer->size)
	{
		errno = ENOBUFS;
		
		return (-1);
	}

	/*real_count represents the real count we will do, which is the minimum
	between the "count" from the user and the free space left in the buffer*/
	real_count = MIN(count, CBufferFreeSpace(c_buffer));
	
	while (real_count && src)
	{
		/*We are in a circual struct, therefore we need to use % in order to
		turn the index back to zero*/
		index = (c_buffer->read + c_buffer->size) % (c_buffer->capacity);
		c_buffer->buffer[index] = *(char *)src;
		++(*(char *)&src);
		++(c_buffer->size);
		--real_count;
		++bytes_copied;
	}

	return (bytes_copied);
}


/******************************************************************************/

















