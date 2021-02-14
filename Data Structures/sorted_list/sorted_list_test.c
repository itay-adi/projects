/*
* File Name - sorted_list_test.c
* Developer - Itay Adi Yosef
*/

/***************************User's declarations********************************/

#include <stdio.h> /* printf */

#include "sorted_list.h"

/**********************assistance functions declarations***********************/

int SortedDlistIsBefore(const void *data1, const void *data2, void *param);
int SortedDlistIsMatch(const void *data, void *param);
int SortedDlistDoAction(void *data, void *param);
void SortedDlistIntPrint(const sorted_list_t *sorted_list);

/************************Test function declarations****************************/

void SortedListBeginTest(sorted_list_t *s_dlist);
void SortedListEndTest(sorted_list_t *s_dlist);
void SortedListIsEmptyTest(sorted_list_t *sorted_list);
void SortedListSizeTest(const sorted_list_t *sorted_list);
void SortedListDestroyTest(sorted_list_t *sorted_list);
void SortedListGetDataTest(sorted_list_t *sorted_list);
void SortedListFindTest(sorted_list_t *sorted_list, void *to_find);
void SortedListForEachTest(sorted_list_t *sorted_list, void *to_find);

/**********************Test case function declarations*************************/

void InsertDestroyTestCase(void);
void SortedListFindTestCase(void);
void SortedListMergeTestCase(void);

/**********************************main****************************************/

int main()
{
	printf("------------------------------------------\n");
	InsertDestroyTestCase();
	printf("------------------------------------------\n");
	SortedListFindTestCase();
	printf("------------------------------------------\n");
	SortedListMergeTestCase();
	printf("------------------------------------------\n");

	return (0);
}

/************************Test function implemintations*************************/

void SortedListIsEmptyTest(sorted_list_t *sorted_list)
{
	printf("\nIs empty:\n");
	printf("The list is");
	SortedListIsEmpty(sorted_list) ? printf (" ") : printf (" not ");
	printf("empty\n");
}

/**********************************************************************/

void SortedListSizeTest(const sorted_list_t *sorted_list)
{
	printf("\nNumber of elements in the list is: %ld\n",
			SortedListSize(sorted_list));
}

/**********************************************************************/

void SortedListDestroyTest(sorted_list_t *sorted_list)
{
	SortedListDestroy(sorted_list);

	printf("\nList has been cleared.\n");
}

/**********************************************************************/

void SortedListGetDataTest(sorted_list_t *sorted_list)
{
	sorted_list_iter_t new_iterator = SortedListBegin(sorted_list);

	printf("\nGet data:\n");
	printf("The data in the given iterator is: %d\n", 
		   *(int *)SortedListGetData(new_iterator));
}

/**********************************************************************/

void SortedListEndTest(sorted_list_t *s_dlist)
{
	sorted_list_iter_t new_iterator = SortedListPrev(SortedListEnd(s_dlist));

	printf("The last element in the list is: %d\n", 
     *(int *)SortedListGetData(new_iterator));
}

/**********************************************************************/

void SortedListBeginTest(sorted_list_t *s_dlist)
{
	sorted_list_iter_t new_iterator = SortedListBegin(s_dlist);

	printf("The first element in the list is: %d\n", 
     *(int *)SortedListGetData(new_iterator));
}

/**********************************************************************/

void SortedListFindTest(sorted_list_t *sorted_list, void *to_find)
{
	sorted_list_iter_t temp = {0};

	temp = SortedListFind(sorted_list, SortedListBegin(sorted_list),
						  SortedListEnd(sorted_list), to_find);

	printf("\nFind Test: \nThe data %d was", *(int *)to_find);
	(temp.internal_iter != SortedListEnd(sorted_list).internal_iter)?
	printf (" ") : printf (" not ");
	printf("found\n");
}

/**********************************************************************/

void SortedListFindIfTest(sorted_list_t *sorted_list, void *to_find)
{
	sorted_list_iter_t temp = {0};

	temp = SortedListFindIf(SortedListBegin(sorted_list),
							SortedListEnd(sorted_list),
							SortedDlistIsMatch,
							to_find);

	printf("\nFind IF Test: \nThe data %d was", *(int *)to_find);
	(temp.internal_iter != SortedListEnd(sorted_list).internal_iter)?
	printf (" ") : printf (" not ");
	printf("found\n");
}

/**********************************************************************/

void SortedListForEachTest(sorted_list_t *sorted_list, void *to_find)
{
	int temp = 0;

	temp = SortedListForEach(SortedListBegin(sorted_list),
							SortedListEnd(sorted_list),
							SortedDlistDoAction,
							to_find);

	printf("\nThe action was a ");
	temp ? printf ("success.\n") : printf ("failure.\n");
}

/**********************assistance functions Implementations********************/

void SortedDlistIntPrint(const sorted_list_t *sorted_list)
{
	sorted_list_iter_t temp = SortedListBegin(sorted_list);

	while (temp.internal_iter != SortedListEnd(sorted_list).internal_iter)
	{
		printf("%d, ", *(int *)SortedListGetData(temp));
		temp = SortedListNext(temp);
	}

	printf("\n");
}

/**********************************************************************/

int SortedDlistIsBefore(const void *data1, const void *data2, void *param)
{
	(void)param;

	return(*(int *)data1 < *(int *)data2);
}

/**********************************************************************/

int SortedDlistIsMatch(const void *data, void *param)
{
	return(*(int *)data == *(int *)param);
}

/**********************************************************************/

int SortedDlistDoAction(void *data, void *param)
{
	return(*(int *)data <= *(int *)param);
}

/********************Test case function Implementations************************/

void InsertDestroyTestCase(void)
{
	sorted_list_t *s_dlist = NULL;
	sorted_list_iter_t temp = {0};
	int num1 = 1;
	int num2 = 2;
	int num3 = 3;
	int num4 = 4;
	int num5 = 5;
	int num6 = 6;
	int *ptr1 = &num1;
	int *ptr2 = &num2;
	int *ptr3 = &num3;
	int *ptr4 = &num4;
	int *ptr5 = &num5;
	int *ptr6 = &num6;

	printf("*****Insert And Destroy Test Case*****\n");

	/*List creation*/
	s_dlist = SortedListCreate(SortedDlistIsBefore, NULL);
	/*Checks if the list is indeed empty*/
	SortedListIsEmptyTest(s_dlist);
	/*insert 6 elements, not in a specific order*/
	SortedListInsert(s_dlist, ptr3);
	SortedListInsert(s_dlist, ptr1);
	SortedListInsert(s_dlist, ptr2);
	SortedListInsert(s_dlist, ptr4);
	SortedListInsert(s_dlist, ptr5);
	SortedListInsert(s_dlist, ptr6);
	/*checking the list size*/
	SortedListSizeTest(s_dlist);
	/*print the list*/
	SortedDlistIntPrint(s_dlist);
	/*removing a random element from the list*/
	temp = SortedListBegin(s_dlist);
	SortedListRemove(temp);
	SortedDlistIntPrint(s_dlist);
	/*removing an element from the beginning of the list*/
	SortedListPopFront(s_dlist);
	SortedDlistIntPrint(s_dlist);
	/*removing an element from the end of the list*/
	SortedListPopBack(s_dlist);
	SortedDlistIntPrint(s_dlist);
	SortedListGetDataTest(s_dlist);
	SortedListBeginTest(s_dlist);
	SortedListEndTest(s_dlist);
	/*List Destroy*/
	SortedListDestroyTest(s_dlist);
}

/**********************************************************************/

void SortedListFindTestCase(void)
{
	sorted_list_t *s_dlist = NULL;
	int num1 = 1;
	int num2 = 2;
	int num3 = 3;
	int num4 = 4;
	int num5 = 5;
	int num6 = 6;
	int *ptr1 = &num1;
	int *ptr2 = &num2;
	int *ptr3 = &num3;
	int *ptr4 = &num4;
	int *ptr5 = &num5;
	int *ptr6 = &num6;

	printf("*****Find and Each Test Case*****\n\n");

	/*List creation*/
	s_dlist = SortedListCreate(SortedDlistIsBefore, NULL);
	/*insert 6 elements, not in a specific order*/
	SortedListInsert(s_dlist, ptr3);
	SortedListInsert(s_dlist, ptr1);
	SortedListInsert(s_dlist, ptr2);
	SortedListInsert(s_dlist, ptr4);
	SortedListInsert(s_dlist, ptr5);
	/*print the list*/
	SortedDlistIntPrint(s_dlist);
	/*Find*/
	SortedListFindTest(s_dlist, ptr1);
	SortedListFindTest(s_dlist, ptr6);
	/*Find IF*/
	SortedListFindIfTest(s_dlist, ptr1);
	SortedListFindIfTest(s_dlist, ptr6);
	/*checks if all the data is smaller than 1*/
	SortedListForEachTest(s_dlist, ptr1);
	/*checks if all the data is smaller than 6*/
	SortedListForEachTest(s_dlist, ptr6);
	/*List Destroy*/
	SortedListDestroyTest(s_dlist);
}

/**********************************************************************/

void SortedListMergeTestCase(void)
{
	sorted_list_t *s_dlist1 = NULL;
	sorted_list_t *s_dlist2 = NULL;
	int num1 = 1;
	int num2 = 2;
	int num3 = 3;
	int num4 = 4;
	int num5 = 5;
	int num6 = 6;
	int *ptr1 = &num1;
	int *ptr2 = &num2;
	int *ptr3 = &num3;
	int *ptr4 = &num4;
	int *ptr5 = &num5;
	int *ptr6 = &num6;

	printf("*****Merge Test Case*****\n\n");

	/*Lists creation*/
	s_dlist1 = SortedListCreate(SortedDlistIsBefore, NULL);
	s_dlist2 = SortedListCreate(SortedDlistIsBefore, NULL);

	/*insert 3 elements, not in a specific order to the first list*/
	SortedListInsert(s_dlist1, ptr3);
	SortedListInsert(s_dlist1, ptr5);
	SortedListInsert(s_dlist1, ptr6);
	/*insert 3 elements, not in a specific order to the second list*/
	SortedListInsert(s_dlist2, ptr2);
	SortedListInsert(s_dlist2, ptr1);
	SortedListInsert(s_dlist2, ptr4);
	/*print the lists*/
	printf("First list:\n");
	SortedDlistIntPrint(s_dlist1);
	printf("Second list:\n");
	SortedDlistIntPrint(s_dlist2);
	/*doing the merge*/
	printf("\nMerging:\n");
	SortedListMerge(s_dlist1, s_dlist2);

	/*print the lists*/
	printf("First list:\n");
	SortedDlistIntPrint(s_dlist1);
	printf("Second list:\n");
	SortedDlistIntPrint(s_dlist2);

	/*Lists Destroy*/
	SortedListDestroyTest(s_dlist1);
	SortedListDestroyTest(s_dlist2);
}

/******************************************************************************/
















