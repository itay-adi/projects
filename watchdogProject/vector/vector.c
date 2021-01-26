/*
* File Name - vector.c
* Description - Exercises from ds
* Developer - Itay Adi Yosef
* Reviewer - Ori K
* Review Date - 8/6/20
*/

#include <stddef.h>	/* size_t */
#include <stdlib.h> /* malloc, realloc, free */
#include <assert.h> /* assert */
#include <stdio.h>

#include "vector.h"


#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))


/*Once we need to shrink the vector, we devide it by 2*/
#define SHRINK_FACTOR 2

/*Once we need to expend the vector, we double it by 2*/
#define GROWTH_FACTOR 2

/*In order to understand if we need to shrink the vector,
  we need this number as a parameter*/
#define DEVIDE_FACTOR 4


struct vector{
    void** data;
    size_t size;
    size_t initial_capacity;
    size_t current_capacity;
};

enum mode {SUCCESS = 0, FAIL = 1};

/******************************************************************************/

vector_t *VectorCreate(size_t capacity)
{
	vector_t *vector_ptr = NULL;

	/*allocating memory for the vector*/
	if(!(vector_ptr = (vector_t *)malloc(sizeof(vector_t))))
	{
		return(NULL);
	}
	
	/*allocation memory for the data pointer*/
	if(!(vector_ptr->data = (void **)malloc(sizeof(void *) *capacity)))
	{
		/*in case the allocation for the data poiner fail, we free the vector*/
		free(vector_ptr);
		
		return(NULL);
	}

	vector_ptr->initial_capacity = capacity;
	vector_ptr->current_capacity = capacity;
	vector_ptr->size = 0;

	return(vector_ptr);
}

/******************************************************************************/

void VectorDestroy(vector_t *vector)
{
	assert(vector);
	
	free(vector->data);
	vector->data = NULL;

	free(vector);
	vector = NULL;
}

/******************************************************************************/

void *VectorGetElement(const vector_t *vector, size_t index)
{
	assert(vector);

	/*If there is no such an element, we will return NULL*/ 
	if(index >= vector->size)
	{
		return (NULL);
	}

	return (vector-> data[index]);
}

/******************************************************************************/

void VectorSetElement(vector_t *vector, size_t index, void *element)
{
	assert(vector);
	assert(index < vector->size);
	
	vector-> data[index] = element;
}

/******************************************************************************/

int VectorPushBack(vector_t *vector, void *element)
{
	size_t index = vector->size;
	void **temp = NULL;

	assert(vector);
	assert(element);

	/*Checking if additional memory is needed, if so we will do realloc*/
	if(vector->size == vector->current_capacity)
	{
		vector->current_capacity *= GROWTH_FACTOR;

		/*checks if the realloc has failed*/
		if(!(temp = (void **)realloc(vector->data, sizeof(void *) *
			(vector->current_capacity))))
		{
			return (FAIL);
		}

		vector->data = temp;
	}

	vector-> data[index] = element;
	++(vector->size);

	return(SUCCESS);
}

/******************************************************************************/

size_t VectorSize(const vector_t *vector)
{
	assert(vector);

	return(vector->size);
}

/******************************************************************************/

size_t VectorCapacity(const vector_t *vector)
{
	assert(vector);

	return(vector->current_capacity);
}

/******************************************************************************/

void VectorPopBack(vector_t *vector)
{
	size_t qrtr = (vector-> current_capacity)/DEVIDE_FACTOR;
	size_t min_size = MAX(vector->current_capacity / SHRINK_FACTOR,
						  vector->initial_capacity);
	
	assert(vector);
	
	/*checks if the we have elements in the vector*/
	if(vector->size > 0)
	{
		--(vector->size);
	
		/*Checking if there is a need to minimize the capacity*/
		if(vector->size <= qrtr &&
	   	   vector->current_capacity > vector->initial_capacity)
		{
			vector->current_capacity = min_size;
			vector->data = (void **)realloc(vector->data, 
							sizeof(void *) * min_size);
		}
	}
}

/******************************************************************************/

int VectorReserve(vector_t *vector, size_t new_capacity)
{
	void **temp = NULL;

	assert(vector);

	/*checking if the new capacity is a valid value*/
	if(new_capacity > vector->current_capacity)
	{

		/*checks if the realloc has failed*/
		if(!(temp = (void **)realloc(vector->data, sizeof(void *) *
			new_capacity)))
			{
				return (FAIL);
			}

		vector->data = temp;
		
		vector->current_capacity = new_capacity;
		
		return (SUCCESS);
	}
	
	else 
	{
		return (FAIL);
	}
}

/******************************************************************************/

void VectorShrinkToFit(vector_t *vector)
{
	size_t min_size = MAX(vector->size, vector->initial_capacity);

	assert(vector);

	vector->data = (void **)realloc(vector->data, sizeof(void *) * min_size);
	vector->current_capacity = min_size;
}

/******************************************************************************/

void **VectorGetArr(vector_t *vector)
{
	return (vector->data);
}

/******************************************************************************/








