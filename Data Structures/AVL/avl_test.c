/*
* File Name - avl_test.c
* Developer - Itay Adi Yosef
*/

#include <stdio.h> /* printf */
#include <assert.h> /* assert */ 

#include "avl.h"

/************************Test function declarations****************************/

avl_t *AVLCreateTest(avl_cmp_func_t cmp, void *param);
void AVLInsertTest(avl_t *avl, void *data);
void AVLFindTest(const avl_t *avl, const void *data);
void AVLForEachTest(avl_t *avl, avl_do_action_func_t do_action ,void *param);
void AVLSizeTest(const avl_t *avl);
void BSTIsEmptyTest(const avl_t *avl);
void AVLDestroyTest(avl_t *avl);
void AVLRemoveTest(avl_t *avl, void *data);

/**********************assistance functions declarations***********************/

int IntCompare(const void *data1, const void *data2, void *param);
int AddOne(void *data, void *param);
void AVL_PostOrder_Print(const avl_t *avl);

/*******************************Test Case**************************************/

void TestCase(void);

/**********************************main****************************************/

int main(void)
{
    printf("------------------------------------------\n");
    TestCase();
    printf("------------------------------------------\n");

    return (0);
}

/************************Test function implemintations*************************/

avl_t *AVLCreateTest(avl_cmp_func_t cmp, void *param)
{
    avl_t *avl = NULL;

    avl = AVLCreate(cmp, param);

    if(NULL == avl)
    {
        printf("AVL Creation was failed.\n");

        return(NULL);
    }

    printf("AVL Creation was successful.\n");

    return(avl);
}

/**********************************************************************/

void AVLInsertTest(avl_t *avl, void *data)
{
    if(AVLInsert(avl, data) == 0)
    {
        printf("Insertion of element %d has been successful.\n", *(int *)data);
    }

    else
    {
        printf("Insertion of element %d has been failed.\n", *(int *)data);
    }
}

/**********************************************************************/

void AVLFindTest(const avl_t *avl, const void *data)
{
    if(AVLFind(avl, data))
    {
        printf("The wanted data %d was found\n", *(int *)data);
    }

    else
    {
        printf("The wanted data %d was not found\n", *(int *)data);
    }
}

/**********************************************************************/

void AVLForEachTest(avl_t *avl, avl_do_action_func_t do_action ,void *param)
{
    if(0 == AVLForEach(avl, do_action, param))
    {
        printf("\nThe action was successful for all the elements\n");
    }

    else
    {
        printf("\nThe action was NOT successful for all the elements\n");
    } 
}

/**********************************************************************/

void AVLSizeTest(const avl_t *avl)
{
    printf("\nYou have %ld elements in your list.\n", AVLSize(avl));
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
		return (1);
	}

	*(int *)data += 1;

	return (0);
}

/**********************************************************************/

void BSTIsEmptyTest(const avl_t *avl)
{
	assert(avl);

	printf("\nIs Empty:\nThe list is");

	AVLIsEmpty(avl) ? printf(" ") : printf(" not ");
	
	printf("empty.\n");
}

/******************************************************************************/

void AVLDestroyTest(avl_t *avl)
{
	AVLDestroy(avl);
	printf("\nThe list has been destroyed.\n"); 
}

/******************************************************************************/

void AVLRemoveTest(avl_t *avl, void *data)
{
    printf("\nRemove:\n%d has been removed from the list.\n", *(int *)data);

    AVLRemove(avl, data);
}

/******************************************************************************/

void TestCase(void)
{
    avl_t *avl = NULL;

    int num3 = 3;
    int num4 = 4;
    int num6 = 6;
    int num7 = 7;
    int num8 = 8;
    int num9 = 9;
    int num12 = 12;

    int *num3_ptr = &num3;
    int *num4_ptr = &num4;
    int *num6_ptr = &num6;
    int *num7_ptr = &num7;
    int *num8_ptr = &num8;
    int *num9_ptr = &num9;
    int *num12_ptr = &num12;
    
    avl = AVLCreateTest(IntCompare, NULL);
    AVLSizeTest(avl);
    BSTIsEmptyTest(avl);

    printf("\ninsert elements:\n");
    AVLInsertTest(avl, num3_ptr);
    AVLInsertTest(avl, num6_ptr);
    AVLInsertTest(avl, num8_ptr);
	AVLInsertTest(avl, num8_ptr);
    AVLInsertTest(avl, num12_ptr);
    AVLInsertTest(avl, num4_ptr);
    AVLInsertTest(avl, num9_ptr);
	AVL_PostOrder_Print(avl);
        
    AVLSizeTest(avl);
    printf("-------------------------------\n");
    
    BSTIsEmptyTest(avl);

    printf("\n");
    AVLFindTest(avl, num6_ptr);
    AVLFindTest(avl, num7_ptr);

    printf("Before adding 1 to each of the elements:\n");
    AVL_PostOrder_Print(avl);
    AVLForEachTest(avl, AddOne, NULL);
    printf("After adding 1 to each of the elements:\n");
    AVL_PostOrder_Print(avl);
    
    AVLRemoveTest(avl, num12_ptr);
    AVLRemoveTest(avl, num6_ptr);
    AVLFindTest(avl, num6_ptr);
    AVL_PostOrder_Print(avl);
    AVLSizeTest(avl);

    AVLDestroyTest(avl);
}

/******************************************************************************/
