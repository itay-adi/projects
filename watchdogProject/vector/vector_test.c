/*
* File Name - vector_test.c
* Description - Exercises from ds
* Developer - Itay Adi Yosef
* Reviewer - Ori K
* Review Date - 8/6/20
*/

/***************************User's declarations********************************/

#include <stdio.h>

#include "vector.h" 

struct vector{
    void** data;
    size_t size;
    size_t initial_capacity;
    size_t current_capacity;
};

/************************Test function declarations****************************/

vector_t* VectorCreateTest(vector_t *vector_ptr);
void VectorDestroyTest(vector_t *vector);
void VectorGetElementTest(vector_t *vector);
void VectorSetElementTest(vector_t *vector);
void VectorSizeTest(vector_t *vector);
void VectorCapacityTest(vector_t *vector);
void VectorPopBackTest(vector_t *vector);
void VectorReserveTest(vector_t *vector);
void VectorShrinkToFitTest(vector_t *vector);

/**********************************main****************************************/

int main(void)
{
	vector_t *vector_ptr = NULL;
	int x = 2;
	int *a = &x;

	vector_ptr = VectorCreateTest(vector_ptr);
	printf("--------------------------------------------------\n");
	VectorCapacityTest(vector_ptr);
	printf("--------------------------------------------------\n");
	printf("--------------------------------------------------\n");
	if(VectorPushBack(vector_ptr, a))
	{
		printf("FAIL!!!\n");
	}
	VectorPushBack(vector_ptr, a);
	VectorPushBack(vector_ptr, a);
	printf("--------------------------------------------------\n");
	VectorPushBack(vector_ptr, a);
	VectorPushBack(vector_ptr, a);
	VectorPushBack(vector_ptr, a);
	VectorPushBack(vector_ptr, a);
	VectorPushBack(vector_ptr, a);
	VectorPushBack(vector_ptr, a);
	printf("--------------------------------------------------\n");
	VectorReserveTest(vector_ptr);	
	VectorShrinkToFitTest(vector_ptr);
	printf("--------------------------------------------------\n");
	VectorPushBack(vector_ptr, a);
	VectorPushBack(vector_ptr, a);
	VectorPushBack(vector_ptr, a);
	printf("--------------------------------------------------\n");
	VectorGetElementTest(vector_ptr);
	printf("--------------------------------------------------\n");
	VectorPopBackTest(vector_ptr);
	printf("--------------------------------------------------\n");
	VectorSizeTest(vector_ptr);
	VectorCapacityTest(vector_ptr);
	printf("--------------------------------------------------\n");
	VectorGetElementTest(vector_ptr);
	printf("--------------------------------------------------\n");
	VectorSetElementTest(vector_ptr);
	printf("--------------------------------------------------\n");
	VectorGetElementTest(vector_ptr);
	printf("--------------------------------------------------\n");
	VectorSizeTest(vector_ptr);
	printf("--------------------------------------------------\n");
	VectorDestroyTest(vector_ptr);
	printf("--------------------------------------------------\n");

	return (0);
}

/************************Test function implemintations*************************/

vector_t* VectorCreateTest(vector_t *vector_ptr)
{
	size_t capacity = 2;

	vector_ptr = VectorCreate(capacity);

	printf("Vector of %ld elements has been created.\n", capacity);

	return (vector_ptr);
}

/**********************************************************************/

void VectorDestroyTest(vector_t *vector)
{
	printf("Vector Destroy: \n");
	VectorDestroy(vector);
	printf("The vector's memory has been freed successfully. \n");
}

/**********************************************************************/

void VectorGetElementTest(vector_t *vector)
{
	size_t index = 0;
	void *element = NULL;

	printf("Get Element:\n");

	if(index >= vector->size)
	{
		printf("The index is too big.\n");
	}

	else
	{
		element = VectorGetElement(vector, index);
		printf("The address of the %ld index in the array is: %p.\n",
			   index, element);
	}
}

/**********************************************************************/

void VectorSetElementTest(vector_t *vector)
{
	size_t index = 0;
	int num = 65;
	int *element = &num;

	printf("Set Element: \n");
	
	if(index < vector->size)
	{
		VectorSetElement(vector, index, element);
		printf("The element was set successfully.\n");
	}

	else
	{
		printf("Error: the index is bigger or equal to the size.\n");
	}
}

/**********************************************************************/

void VectorSizeTest(vector_t *vector)
{
	printf("The size of the vector is: %ld elements.\n", VectorSize(vector));
}

/**********************************************************************/

void VectorCapacityTest(vector_t *vector)
{
	printf("The capacity of the vector is: %ld elements.\n",
			VectorCapacity(vector));
}

/**********************************************************************/

void VectorPopBackTest(vector_t *vector)
{
	VectorPopBack(vector);
	printf("Vector was popped.\n");
}

/**********************************************************************/

void VectorReserveTest(vector_t *vector)
{
	size_t new_capacity = 20;
	
	printf("Reserve Test:\n");
	printf("The old capacity is : %ld\n", VectorCapacity(vector));
	VectorReserve(vector, new_capacity);
	printf("The capacity is now: %ld\n", VectorCapacity(vector));
}

/**********************************************************************/

void VectorShrinkToFitTest(vector_t *vector)
{
	printf("Shrink to fit:\n");
	printf("The old capacity is: %ld\n", VectorCapacity(vector)); 
	VectorShrinkToFit(vector);
	printf("The new capacity is now: %ld\n", VectorCapacity(vector));
}

/**********************************************************************/


