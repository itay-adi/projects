/*
* File Name - slist_test.c
* Developer - Itay Adi Yosef
*/

/***************************User's declarations********************************/

#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc, free */

#include "slist.h"

struct slist
{
	slist_iter_t *head;
    slist_iter_t *tail;
};


struct slist_node
{
    void *data;
    slist_iter_t *next;
};

/************************Test function declarations****************************/

slist_t *SListCreateTest(slist_t *slist_ptr);
void SListDestroyTest(slist_t *slist);
void SListBeginTest(slist_t *slist);
void SListEndTest(slist_t *slist);
void SListNextTest(slist_iter_t iter);
void SListGetDataTest(slist_t *slist);
void SListIsEmptyTest(slist_t *slist);
void SListInsertTest(slist_t *slist, slist_iter_t where, void *data);
void SlistSetDataTest(slist_iter_t iter, void *data);
void SListInsertAfterTest(slist_t *slist, slist_iter_t where, void *data);
void SListIterIsEqualTest(const slist_iter_t iter1, const slist_iter_t iter2);
void SListRemoveTest(slist_t *slist, slist_iter_t iter);
void SListCountTest(const slist_t *slist);
void SListFindTest(slist_t *slist);
void SListForEachTest(slist_t *slist);

/*function which is used in "FindTest" function in order to find matches*/
static int is_match(void *data, void *param);

/*******************************Test cases*************************************/

void SListAppendCaseTest(void);
void AddAndRemoveCase(void);

/**********************************main****************************************/

int main(void)
{
	int num1 = 5;
	int num2 = 9;
	int num3 = 12;
	int *ptr_num1 = &num1;
	int *ptr_num2 = &num2;
	int *ptr_num3 = &num3;

	slist_t *slist_ptr = NULL;

	slist_ptr = SListCreateTest(slist_ptr);
	printf("--------------------------------------------------\n");
	SListInsertTest(slist_ptr, SListEnd(slist_ptr), ptr_num1);
	SListNextTest(SListBegin(slist_ptr));
	SListInsertTest(slist_ptr, SListEnd(slist_ptr), ptr_num2);
	printf("--------------------------------------------------\n");
	SListBeginTest(slist_ptr);
	printf("--------------------------------------------------\n");
	SListCountTest(slist_ptr);
	printf("--------------------------------------------------\n");
	SListIterIsEqualTest(SListBegin(slist_ptr), SListEnd(slist_ptr));
	printf("--------------------------------------------------\n");
	SlistSetDataTest(SListBegin(slist_ptr), ptr_num3);
	printf("--------------------------------------------------\n");
	SListBeginTest(slist_ptr);
	printf("--------------------------------------------------\n");
	SListGetDataTest(slist_ptr);
	printf("--------------------------------------------------\n");
	SListInsertAfterTest(slist_ptr, SListBegin(slist_ptr), ptr_num2);
	printf("--------------------------------------------------\n");
	SListNextTest(SListBegin(slist_ptr));
	printf("--------------------------------------------------\n");
	SListFindTest(slist_ptr);
	printf("--------------------------------------------------\n");
	SListEndTest(slist_ptr);
	printf("--------------------------------------------------\n");
	SListForEachTest(slist_ptr);
	printf("--------------------------------------------------\n");
	SListDestroyTest(slist_ptr);
	printf("--------------------------------------------------\n");
	SListAppendCaseTest();
	printf("--------------------------------------------------\n");
	AddAndRemoveCase();
	printf("--------------------------------------------------\n");

	return (0);
}

/************************Test function implemintations*************************/

slist_t *SListCreateTest(slist_t *slist_ptr)
{
	printf("Create:\n");

	slist_ptr = SListCreate();
	
	printf("Single linked list has been created.\n");

	return (slist_ptr);
}

/**********************************************************************/

void SListDestroyTest(slist_t *slist)
{
	printf("Destroy:\n");

	SListDestroy(slist);

	printf("The list has been freed.\n");
}

/**********************************************************************/

void SListBeginTest(slist_t *slist)
{
	slist_iter_t new_iterator = SListBegin(slist);
	
	printf("Slist beginning:\n");
	printf("The first element in the list is: %d\n",
		   *(int *)new_iterator->data);
}

/**********************************************************************/

void SListEndTest(slist_t *slist)
{
	slist_iter_t new_iterator = SListEnd(slist);

	printf("Slist end:\n");
	printf("The last element in the list is: %d\n", *(int *)new_iterator);
}

/**********************************************************************/

void SListNextTest(slist_iter_t iter)
{
	printf("Slist next:\n");
	printf("The Adress of the iterator to the next element is: %p\n",
		   (SListNext(iter)->data));
}

/**********************************************************************/

void SListGetDataTest(slist_t *slist)
{
	slist_iter_t new_iterator = SListBegin(slist);

	printf("Get data:\n");
	printf("The data in the given iterator is: %d\n",
		   *(int *)SListGetData(new_iterator));
}

/**********************************************************************/

void SListIsEmptyTest(slist_t *slist)
{
	printf("Is empty:\n");
	printf("The list is");
	SListIsEmpty(slist) ? printf (" ") : printf (" not ");
	printf("empty\n");
}

/**********************************************************************/

void SListInsertTest(slist_t *slist, slist_iter_t where, void *data)
{
	printf("Add element.\n");
	SListInsert(slist, where, data);
}

/**********************************************************************/

void SlistSetDataTest(slist_iter_t iter, void *data)
{
	printf("Set Data.\n");
	SListSetData(iter, data);
}

/**********************************************************************/

void SListInsertAfterTest(slist_t *slist, slist_iter_t where, void *data)
{
	printf("Add After element.\n");
	SListInsertAfter(slist, where, data);
}

/**********************************************************************/

void SListIterIsEqualTest(const slist_iter_t iter1, const slist_iter_t iter2)
{
	printf("Is equal:\n");
	printf("The two nodes are");
	SListIterIsEqual(iter1, iter2) ? printf(" ") : printf(" not ");
	printf("equal.\n");
}

/**********************************************************************/

void SListRemoveTest(slist_t *slist, slist_iter_t iter)
{
	printf("Remove.\n");
	SListRemove(slist, iter); 
}

/**********************************************************************/

void SListCountTest(const slist_t *slist)
{
	printf("SList Count:\n");
	printf("You have %ld elements in the slist\n", SListCount(slist));
}

/**********************************************************************/

void SListFindTest(slist_t *slist)
{
	int num = 12;
	int *ptr_num = &num;

	printf("SList Find\n");

	if(SListFind(SListBegin(slist), SListEnd(slist), is_match, ptr_num)
	   == SListEnd(slist))
	{
		printf("Element was not found.\n");
	}

	else
	{
		printf("Element was found.\n");
	}
}

/**********************************************************************/

static int is_match(void *data, void *param)
{
	if (*(int*)(data) > (*(int*)(param)))
	{
		return(0);
	}

	return (1);
}

/**********************************************************************/

void SListForEachTest(slist_t *slist)
{
	int num = 1;
	int *ptr_num = &num;

	printf("SList for each:\n");

	if(!(SListForEach(SListBegin(slist), SListEnd(slist), is_match, ptr_num)))
	{
		printf("Action was succeeded.\n");
	}

	else
	{
		printf("Action was not succeeded.\n");
	}
}

/**********************************************************************/

void SListAppendCaseTest(void)
{
	int num1 = 5;
	int num2 = 9;
	int num3 = 12;
	int *ptr_num1 = &num1;
	int *ptr_num2 = &num2;
	int *ptr_num3 = &num3;

	slist_t *slist_ptr1 = NULL;
	slist_t *slist_ptr2 = NULL;

	printf("Append case:\n\n");

	slist_ptr1 = SListCreateTest(slist_ptr1);
	slist_ptr2 = SListCreateTest(slist_ptr2);

	printf("\n*First list:*\n");
	SListInsertTest(slist_ptr1, SListEnd(slist_ptr1), ptr_num1);
	SListInsertTest(slist_ptr1, SListEnd(slist_ptr1), ptr_num2);
	SListInsertTest(slist_ptr1, SListEnd(slist_ptr1), ptr_num3);
	printf("\n");
	SListCountTest(slist_ptr1);

	printf("\n*Second list:*\n");
	SListInsertTest(slist_ptr2, SListEnd(slist_ptr2), ptr_num1);
	SListInsertTest(slist_ptr2, SListEnd(slist_ptr2), ptr_num2);
	SListInsertTest(slist_ptr2, SListEnd(slist_ptr2), ptr_num3);
	printf("\n");
	SListCountTest(slist_ptr2);
	
	printf("\n*Append lists:*\n");
	SListAppend(slist_ptr1, slist_ptr2);
	SListCountTest(slist_ptr1);

	SListEndTest(slist_ptr1);
	printf("\n*free:*\n");
	SListDestroyTest(slist_ptr1);
	SListDestroyTest(slist_ptr2);
}

/**********************************************************************/

void AddAndRemoveCase(void)
{
	int num1 = 5;
	int num2 = 9;
	int *ptr_num1 = &num1;
	int *ptr_num2 = &num2;
	slist_t *slist_ptr = NULL;

	slist_ptr = SListCreateTest(slist_ptr);

	SListIsEmptyTest(slist_ptr);
	printf("\n");
	SListCountTest(slist_ptr);

	printf("\nPutting the first element in the list.\n");	
	SListInsertTest(slist_ptr, SListEnd(slist_ptr), ptr_num1);
	SListBeginTest(slist_ptr);
	SListCountTest(slist_ptr);
	SListIsEmptyTest(slist_ptr);
	
	printf("\nPutting the second element in the list.\n");	
	SListInsertTest(slist_ptr, SListBegin(slist_ptr), ptr_num2);
	SListCountTest(slist_ptr);

	printf("\nRemoving the head of the list:\n");
	SListRemoveTest(slist_ptr, SListBegin(slist_ptr));
	SListCountTest(slist_ptr);
	printf("\n");
	SListDestroyTest(slist_ptr);
}

/**********************************************************************/













