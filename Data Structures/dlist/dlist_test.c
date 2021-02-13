/*
* File Name - dlist_test.c
* Developer - Itay Adi Yosef
*/

/***************************User's declarations********************************/

#include <stdio.h>

#include "dlist.h"

/****************************assistance functions******************************/

/*Find comparison between two void pointers*/ 
int IsMatch(const void *data, void *param);
/*If data > param return 1 else 0*/
int IsSmaller(void *data, void *param);
/*Prints the data from the list. works only if all the data are ints*/ 
void DlistIntPrint(const dlist_t *dlist);

/************************Test function declarations****************************/

void DListBeginTest(const dlist_t *dlist);
void DListEndTest(const dlist_t *dlist);
void DListNextTest(const dlist_iter_t iter);
void DListPrevTest(const dlist_iter_t iter);
void DListGetDataTest(const dlist_t *dlist);
void DlistSetDataTest(dlist_iter_t iter, void *data);
void DListIterIsEqualTest(const dlist_iter_t iter1, const dlist_iter_t iter2);
void DListIsEmptyTest(dlist_t *dlist);
void DListSizeTest(dlist_t *dlist);

void DListInserRemovetTestCase(void);
void DListSpliceTestCase(void);


/**********************************main****************************************/

int main(void)
{
	printf("------------------------------------------\n");
	DListInserRemovetTestCase();
	printf("------------------------------------------\n");
	DListSpliceTestCase();
	printf("------------------------------------------\n");

	return (0);
}

/************************Test function implemintations*************************/

void DListBeginTest(const dlist_t *dlist)
{
	dlist_iter_t new_iterator = DListBegin(dlist);

	printf("The first element in the list is: %d\n", *(int *)new_iterator);
}

/**********************************************************************/

void DListEndTest(const dlist_t *dlist)
{
	dlist_iter_t new_iterator = DListEnd(dlist);

	printf("The last element in the list is: %d\n", *(int *)new_iterator);
}

/**********************************************************************/

void DListNextTest(const dlist_iter_t iter)
{
	printf("Dlist next:\n");
	printf("The Adress of the iterator to the next element is: %p\n",
		   (DListGetData(DListNext(iter))));
}

/**********************************************************************/

void DListPrevTest(const dlist_iter_t iter)
{
	printf("Dlist prev:\n");
	printf("The Adress of the iterator to the prev element is: %p\n",
		   (DListGetData(DListPrev(iter))));

}

/**********************************************************************/

void DListGetDataTest(const dlist_t *dlist)
{
	dlist_iter_t new_iterator = DListBegin(dlist);

	printf("Get data:\n");
	printf("The data in the given iterator is: %d\n", 
		   *(int *)DListGetData(new_iterator));
}

/**********************************************************************/

void DlistSetDataTest(dlist_iter_t iter, void *data)
{
	printf("Set Data.\n");
	DListSetData(iter, data);
}

/**********************************************************************/

void DListIterIsEqualTest(const dlist_iter_t iter1, const dlist_iter_t iter2)
{
	printf("Is equal:\n");
	printf("The two nodes are");
	DListIterIsEqual(iter1, iter2) ? printf(" ") : printf(" not ");
	printf("equal.\n");
}

/**********************************************************************/

void DListIsEmptyTest(dlist_t *dlist)
{
	printf("Is empty:\n");
	printf("The list is");
	DListIsEmpty(dlist) ? printf (" ") : printf (" not ");
	printf("empty\n");
}

/**********************************************************************/

void DListInserRemovetTestCase(void)
{
	dlist_t *dl_list = NULL;
	int num1 = 5;
	int *num_ptr1 = &num1;
	int num2 = 2;
	int *num_ptr2 = &num2;
	int num3 = 4;
	int *num_ptr3 = &num3;

	/*creates a list*/
	dl_list = DListCreate();
	/*checks if its empty*/
	DListIsEmptyTest(dl_list);
	/*insert an elemtent*/ 
	DListInsert(dl_list, DListBegin(dl_list), num_ptr1);
	/*checking the size*/
	DListSizeTest(dl_list);
	/*insert an elemtent*/ 
	DListInsert(dl_list, DListBegin(dl_list), num_ptr2);
	/*insert an elemtent*/ 
	DListInsert(dl_list, DListBegin(dl_list), num_ptr3);
	/*insert an elemtent to the front*/ 
	DListPushFront(dl_list, num_ptr2);
	/*print the list*/
	DlistIntPrint(dl_list);
	/*insert an elemtent to the back*/ 
	DListPushBack(dl_list, num_ptr2);
	/*print the list*/
	DlistIntPrint(dl_list);
	/*find a specific element inside the list*/
	DListFind(DListBegin(dl_list), DListEnd(dl_list), IsMatch, num_ptr3);
	printf("****%d****\n", DListForEach(DListBegin(dl_list), DListEnd(dl_list),
						   IsSmaller, num_ptr3));
	/*checking the size*/
	DListSizeTest(dl_list);
	/*removes an element from the beginning of the list*/ 
	DListPopFront(dl_list);
	/*checking the size*/
	DListSizeTest(dl_list);
	/*print the list*/
	DlistIntPrint(dl_list);
	/*removes an element from the beginning of the list*/ 
	DListPopBack(dl_list);
	/*checking the size*/
	DListSizeTest(dl_list);
	/*print the list*/
	DlistIntPrint(dl_list);
	/*gets a data*/
	DListGetDataTest(dl_list);
	/*checking the size*/
	DListSizeTest(dl_list);
	/*removes an element from the list*/
	DListRemove(DListBegin(dl_list));
	/*checking the size*/
	DListSizeTest(dl_list);
	/*print the list*/
	DlistIntPrint(dl_list);
	/*checking the size*/
	DListSizeTest(dl_list);
	/*gets a data*/
	DListGetDataTest(dl_list);
	/*destroy the list*/
	DListDestroy(dl_list);
}

/**********************************************************************/

void DListSizeTest(dlist_t *dlist)
{
	printf("Number of elements in the list is: %ld\n", DListSize(dlist));
}

/**********************************************************************/

int IsMatch(const void *data, void *param)
{
	return (data == param);
}

/**********************************************************************/

int IsSmaller(void *data, void *param)
{
	return (*(int *)data > *(int *)param);
}

/**********************************************************************/

void DListSpliceTestCase(void)
{
	dlist_t *dl_list1 = NULL;
	dlist_t *dl_list2 = NULL;
	int num1 = 1;
	int num2 = 2; 
	int num3 = 3;
	int num4 = 4;
	int num5 = 5;
	int *num1_ptr = &num1;
	int *num2_ptr = &num2;
	int *num3_ptr = &num3;
	int *num4_ptr = &num4;
	int *num5_ptr = &num5;

	/*creats two lists*/
	dl_list1 = DListCreate();
	dl_list2 = DListCreate();

	/*entering elements to the first list*/
	printf("***Splice Test Case***\n");
	DListPushFront(dl_list1, num3_ptr);
	DListPushFront(dl_list1, num2_ptr);
	DListPushFront(dl_list1, num1_ptr);

	printf("\nFirst list:\n");
	/*checking the size of the list*/
	DListSizeTest(dl_list1);
	/*prints the elements*/
	DlistIntPrint(dl_list1);
	/*push an element to the front*/
	DListPushFront(dl_list2, num5_ptr);
	/*push an element to the front*/
	DListPushFront(dl_list2, num4_ptr);

	printf("\nSecond list:\n");
	/*checking the size of the list*/
	DListSizeTest(dl_list2);
	/*prints the elements*/
	DlistIntPrint(dl_list2);
	/*splicing the 2nd list*/ 
	DListSplice(DListBegin(dl_list1), DListPrev(DListEnd(dl_list1)),
				DListPrev(DListEnd(dl_list2)));
	printf("\nFirst list:\n");
	/*checking the size*/
	DListSizeTest(dl_list1);
	/*prints the elements*/
	DlistIntPrint(dl_list1);
	printf("\nSecond list:\n");
	/*checking the size*/
	DListSizeTest(dl_list2);
	/*prints the elements*/
	DlistIntPrint(dl_list2);

	/*destroys the lists*/
	DListDestroy(dl_list1);
	DListDestroy(dl_list2);
}

/**********************************************************************/

void DlistIntPrint(const dlist_t *dlist)
{
	dlist_iter_t temp = DListBegin(dlist);

	while (temp != DListEnd(dlist))
	{
		printf("%d, ", *(int *)DListGetData(temp));
		temp = DListNext(temp);
	}

	printf("\n");
}

/**********************************************************************/




























