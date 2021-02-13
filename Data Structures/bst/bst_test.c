/*
* File Name - bst_test.c
* Developer - Itay Adi Yosef
*/

/***************************User's declarations********************************/
#include <stdio.h> /* printf */
#include <assert.h> /* assert */

#include "bst.h"

/**********************assistance functions declarations***********************/

int IntCompare(const void *data1, const void *data2, void *param);
int AddOne(void *data, void *param);
void PrintList(const bst_t *bst);

/************************Test function declarations****************************/

void BSTIsEmptyTest(const bst_t *bst);
void BSTBeginTest(const bst_t *bst);
void BSTEndTest(const bst_t *bst);
void BSTGetDataTest(bst_iter_t iter);
void BSTIterIsEqualTest(bst_iter_t iter1, bst_iter_t iter2);
bst_iter_t BSTInsertTest(bst_t *bst, void *data);
void BSTSizeTest(const bst_t *bst);
void BSTDestroyTest(bst_t *bst);
void BSTPrevTest(bst_iter_t iter);
void BSTNextTest(bst_iter_t iter);
void BSTRemoveTest(bst_iter_t iter);
void BSTFindTest(const bst_t *bst, const void *data);
void BSTForEachTest(bst_iter_t from, bst_iter_t to,
					bst_do_action_func_t do_action, void *param);

/**********************Test case function declarations*************************/

void TestCase(void);

/**********************************main****************************************/

int main(void)
{
	printf("---------------------------------------\n");
	TestCase();
	printf("---------------------------------------\n");

	return (0);
}

/************************Test function implemintations*************************/

void BSTIsEmptyTest(const bst_t *bst)
{
	assert(bst);

	printf("\nIs Empty:\nThe list is");

	BSTIsEmpty(bst) ? printf(" ") : printf(" not ");
	
	printf("empty.\n");
}

/**********************************************************************/

void BSTBeginTest(const bst_t *bst)
{
	bst_iter_t iter = {0};
	int *num = NULL;
	
	printf("The first iterator to the smallest element is: ");

	iter = BSTBegin(bst);
	num = (int *)BSTGetData(iter);
	
	if(NULL == num)
	{
		printf("The list is empty\n\n");
	}

	else
	{
		printf("%d\n", *num);
	}
}

/**********************************************************************/

void BSTEndTest(const bst_t *bst)
{
	bst_iter_t iter = {0};

	printf("\nBST End:\n");

	if(BSTIsEmpty(bst))
	{
		printf("The list is empty\n\n");
	}

	else
	{
		iter = BSTEnd(bst);

		if (BSTGetData(iter) == NULL)
		{
			printf("You have received the end of the list.\n");
		}
	}
}

/**********************************************************************/

void BSTGetDataTest(bst_iter_t iter)
{
	printf("The integer stored in the given iter is: %d\n",
			*(int *)BSTGetData(iter));
}

/**********************************************************************/

void BSTIterIsEqualTest(bst_iter_t iter1, bst_iter_t iter2)
{
	printf("**Is Equal:**\nThe both iters are");
	BSTIterIsEqual(iter1, iter2) ? printf(" ") : printf(" not ");
	printf("The same.\n");
}

/**********************************************************************/

bst_iter_t BSTInsertTest(bst_t *bst, void *data)
{
	bst_iter_t iter = {0};

	iter = BSTInsert(bst, data);

	if(BSTIterIsEqual(iter ,BSTEnd(bst)))
	{
		printf("Insertion has been failed\n");
	}

	else
	{
		printf("Insertion of element %d has been successful\n", 
		*(int *)BSTGetData(iter));
	}

	return (iter);
}

/**********************************************************************/

void BSTSizeTest(const bst_t *bst)
{
	printf("\nYou have %ld elements in your list.\n\n", BSTSize(bst));
}

/**********************************************************************/

void BSTDestroyTest(bst_t *bst)
{
	BSTDestroy(bst);
	printf("\nThe list has been destroyed.\n"); 
}

/**********************************************************************/

void BSTPrevTest(bst_iter_t iter)
{
	bst_iter_t temp = {0};

	temp = BSTPrev(iter);

	printf("\nPrev Test:\nYour iter is: %d\n", *(int *)BSTGetData(iter));

	if(BSTGetData(temp))
	{
		printf("The prev iter is: %d\n", *(int *)BSTGetData(temp));
	}

	else
	{
		printf("You have entered an invalid iter\n");
	}
}

/**********************************************************************/

void BSTNextTest(bst_iter_t iter)
{
	bst_iter_t temp = {0};

	temp = BSTNext(iter);

	printf("\nNext Test:\nYour iter is: %d\n", *(int *)BSTGetData(iter));

	if(BSTGetData(temp))
	{
		printf("The next iter is: %d\n", *(int *)BSTGetData(temp));
	}

	else
	{
		printf("You have entered an invalid iter\n");
	}
}

/**********************************************************************/

void BSTRemoveTest(bst_iter_t iter)
{
	printf("\nRemove:\n%d has been removed from the list.\n", 
		*(int *)BSTGetData(iter));

	BSTRemove(iter);
}

/**********************************************************************/

void BSTFindTest(const bst_t *bst, const void *data)
{
	bst_iter_t temp = {0};

	printf("Find Test:\n");

	temp = BSTFind(bst, data);

	if(BSTIterIsEqual(temp, BSTEnd(bst)))
	{
		printf("The wanted data %d was not found\n", *(int *)data);
	}

	else
	{
		printf("%d was found in the list.\n", *(int *)BSTGetData(temp));
	}
}

/**********************************************************************/

void BSTForEachTest(bst_iter_t from, bst_iter_t to,
					bst_do_action_func_t do_action, void *param)
{
	if(BSTForEach(from, to, do_action, param) == 0)
	{
		printf("\nThe action was successful for all the elements\n");
	}

	else
	{
		printf("\nThe action was NOT successful for all the elements\n");
	}
}

/**********************assistance functions Implementations********************/

int IntCompare(const void *data1, const void *data2, void *param)
{
	assert(data1);
	assert(data2);

	(void)param;

	if(*(int *)data1 < *(int *)data2)
	{
		return (1);
	}

	if(*(int *)data1 == *(int *)data2)
	{
		return (0);
	}

	return (-1);
}

/**********************************************************************/

int AddOne(void *data, void *param)
{
	(void)param;

	if(data == NULL)
	{
		return (0);
	}

	*(int *)data += 1;

	return (1);
}

/**********************************************************************/

void PrintList(const bst_t *bst)
{
	bst_iter_t temp = {0};
	bst_iter_t end = {0};

	assert(bst);

	temp = BSTBegin(bst);
	end = BSTEnd(bst);

	while(!BSTIterIsEqual(temp, end))
	{
		printf("%d, ", *(int *)BSTGetData(temp));
		temp = BSTNext(temp);
	}

	printf("\n\n");
}

/********************Test case function Implementations************************/

void TestCase(void)
{
	/*variable declarations*/
	bst_t *bst = NULL;

	int num3 = 3;
	int num5 = 5;
	int num7 = 7;
	int num1 = 1;
	int num4 = 4;
	int num2 = 2;

	int *num3_ptr = &num3;
	int *num5_ptr = &num5;
	int *num7_ptr = &num7;
	int *num1_ptr = &num1;
	int *num4_ptr = &num4;
	int *num2_ptr = &num2;

	bst_iter_t iter3 = {0};
	bst_iter_t iter5 = {0};
	bst_iter_t iter7 = {0};
	bst_iter_t iter1 = {0};
	bst_iter_t iter4 = {0};
	bst_iter_t iter2 = {0};
	
	/*create the list*/
	bst = BSTtCreate(IntCompare, NULL);
	BSTIsEmptyTest(bst);

	/*insert the elements*/
	iter3 = BSTInsertTest(bst, num3_ptr);
	iter5 = BSTInsertTest(bst, num5_ptr);
	iter7 = BSTInsertTest(bst, num7_ptr);
	iter1 = BSTInsertTest(bst, num1_ptr);
	iter4 = BSTInsertTest(bst, num4_ptr);
	iter2 = BSTInsertTest(bst, num2_ptr);

	BSTIsEmptyTest(bst);
	BSTSizeTest(bst);
	/*prints the list*/
	PrintList(bst);
	/*finding an element*/
	BSTFindTest(bst, num4_ptr);
	/*removes an element*/
	BSTRemoveTest(iter7);
	BSTSizeTest(bst);
	/*prints the list*/
	PrintList(bst);
	/*finding an element*/
	BSTFindTest(bst, num4_ptr);

	/*Add one to each of the elements*/
	BSTForEachTest(BSTBegin(bst), BSTEnd(bst), AddOne, NULL);
	/*prints the list*/
	PrintList(bst);

	BSTPrevTest(iter3);
	BSTPrevTest(iter1);
	BSTNextTest(iter5);
	BSTPrevTest(iter7);
	
	BSTBeginTest(bst);
	BSTEndTest(bst);

	BSTDestroyTest(bst);
}

/******************************************************************************/























