#include <assert.h>
#include <stdio.h>

#include "heapify.h"
#include "heap.h"

/******************************************************************************/

static void Swap(void *element1, void *element2, size_t size);

/******************************************************************************/

void HeapSort(void *base, size_t nmemb, size_t size, heap_cmp_func_t cmp, 
               void *arg)
{
    int i = 0;

    for(i = nmemb / 2 - 1; i >= 0; --i)
    {
        HeapifyDown(base, nmemb, i, size, cmp, arg);
    }

    for(i = nmemb - 1; i > 0 ; --i)
    {
        HeapifyDown(base, i, 0, size, cmp, arg);
        Swap((char *)base, (char *)base + i * size, size);      
    }
}

/******************************************************************************/

static void Swap(void *element1, void *element2, size_t size)
{
	char *dest = NULL;
	char *src = NULL;
	char temp = 0;
	size_t i = 0;
	
	assert(element1);
	assert(element2);

	dest = element1;
	src = element2;

	for (i = 0; i < size; ++i)
	{ 
		temp = *dest;
		*dest = *src;
		*src = temp;

		++dest;
		++src;
	}
}

/******************************************************************************/
