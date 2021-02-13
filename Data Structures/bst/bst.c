/*
* File Name - bst.c
* Developer - Itay Adi Yosef
*/

/******************************************************************************/

#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */

#include "bst.h"

typedef struct bst_node node_t;

struct bst
{
	void *param;
	bst_cmp_func_t cmp;
	node_t *dummy;
};

struct bst_node
{
	void *data;
	node_t *parent;
	node_t *left;
	node_t *right;
};

/******************************************************************************/

/*Removes a leaf*/
static void FreeLeaf(node_t *leaf);

/*Removes parent for one*/
static void FreeParentForOne(node_t *temp);

/*Removes parent for two*/
static void FreeParentForTwo(node_t *temp);

/*count how many children a node has*/
static int ChildrenCount(node_t *node);

/******************************************************************************/

bst_t *BSTtCreate(bst_cmp_func_t cmp, void *param)
{
	bst_t *bst = NULL;
	node_t *dummy = NULL;

	bst = (bst_t *)malloc(sizeof(bst_t));
	
	if(NULL == bst)
	{
		return (NULL);
	}

	dummy = (node_t *)malloc(sizeof(node_t));

	if(NULL == dummy)
	{
		free (bst);
		return (NULL);
	}

	bst->param = param;
	bst->cmp = cmp;
	bst->dummy = dummy;
	
	dummy->data = NULL;
	dummy->parent = NULL;
	dummy->left = NULL;
	dummy->right = NULL;

	return (bst);
}

/******************************************************************************/

int BSTIsEmpty(const bst_t *bst)
{
	assert(bst);
	
	return (bst->dummy->left == NULL);
}

/******************************************************************************/

bst_iter_t BSTBegin(const bst_t *bst)
{
	bst_iter_t iter = {0};
	node_t *temp = NULL;

	assert(bst);

	temp = bst->dummy;

	while (temp->left)
	{
		temp = temp->left;
	}

	iter.node = temp;

	return (iter);
}

/******************************************************************************/

bst_iter_t BSTEnd(const bst_t *bst)
{
	bst_iter_t iter = {0};

	assert(bst);

	iter.node = bst->dummy;

	return (iter);
}

/******************************************************************************/

void *BSTGetData(bst_iter_t iter)
{
	return (iter.node->data);
}

/******************************************************************************/

int BSTIterIsEqual(bst_iter_t iter1, bst_iter_t iter2)
{
	return (iter1.node == iter2.node);
}

/******************************************************************************/

bst_iter_t BSTInsert(bst_t *bst, void *data)
{
	bst_iter_t iter = {0};
	node_t *node = NULL;
	node_t *temp = NULL;
	/*left_turn helps to realize if we inserted the biggest element*/
	size_t left_turn = 0;

	assert(bst);

	temp = bst->dummy;
	node = (node_t *)malloc(sizeof(node_t));

	if(NULL == node)
	{
		iter.node = bst->dummy;
	}

	else
	{
		/*finding the right place to put the new element*/
		while (ChildrenCount(temp) && (temp->right != bst->dummy))
		{
			if(temp == bst->dummy || (bst->cmp(data, temp->data, NULL) == 1))
			{
				if(temp->left)
				{
					temp = temp->left;
					++left_turn;
				}

				else
				{
					break;
				}
			}

			else if (temp->right && (temp->right != bst->dummy))
			{
				temp = temp->right;
			}
		}

		/*decide to which leg do we want to connect the new element*/
		if(temp == bst->dummy || bst->cmp(data, temp->data, NULL) == 1)
		{
			temp->left = node;
			++left_turn;
		}

		else
		{
			temp->right = node;
		}

		node->data = data;
		node->right = NULL;
		node->left = NULL;
		node->parent = temp;
		
		/*checking if we received the biggest element so far*/
		if(1 == left_turn)
		{
			node->right = bst->dummy;
		}

		iter.node = node;
	}

	return (iter);
}

/******************************************************************************/

size_t BSTSize(const bst_t *bst)
{
	size_t count = 0;
	bst_iter_t iter = {0};
	bst_iter_t iter_end = {0};

	assert(bst);

	iter = BSTBegin(bst);
	iter_end = BSTEnd(bst);

	while(!BSTIterIsEqual(iter, iter_end))
	{
		iter = BSTNext(iter);
		++count;
	}
	
	return (count);
}

/******************************************************************************/

void BSTDestroy(bst_t *bst)
{
	node_t *temp = NULL;
	node_t *temp_free = NULL;

	assert(bst);

	temp = bst->dummy;

	while (!BSTIsEmpty(bst))
	{
		if(temp == bst->dummy || temp->left)
		{
			temp = temp->left;
		}

		else if (temp->right)
		{
			temp = temp->right;
		}

		if((ChildrenCount(temp) == 0) || 
		  ((ChildrenCount(temp) == 1) && (temp->right == bst->dummy)))
		{
			temp_free = temp;
			temp = temp->parent;

			FreeLeaf(temp_free);
		}
	}

	free(temp);
	free(bst);
	temp = NULL;
	temp_free = NULL;
	bst = NULL;
}

/******************************************************************************/

bst_iter_t BSTPrev(bst_iter_t iter)
{
	node_t *temp = iter.node;
	node_t *temp_parent = temp->parent;

	if(temp->left)
	{
		temp = temp->left;
		
		while (temp->right)
		{
			temp = temp->right;
		}
	}

	else if (temp_parent->right == temp)
	{
		temp = temp_parent;
	}

	else
	{
		while (temp_parent->right != temp && temp_parent->data)
		{
			temp = temp_parent;
			temp_parent = temp_parent->parent;
		}

		temp = temp_parent;
	}

	iter.node = temp;

	return (iter);
	
}

/******************************************************************************/

bst_iter_t BSTNext(bst_iter_t iter)
{
	node_t *temp = iter.node;
	node_t *temp_parent = temp->parent;

	if(temp->right && temp->right->data)
	{
		temp = temp->right;
		
		while (temp->left)
		{
			temp = temp->left;
		}
	}

	else if (temp_parent->left == temp)
	{
		temp = temp_parent;
	}

	else
	{
		while (temp_parent->left != temp && temp_parent->data)
		{
			temp = temp_parent;
			temp_parent = temp_parent->parent;
		}

		temp = temp_parent;
	}

	iter.node = temp;

	return (iter);
}

/******************************************************************************/

void BSTRemove(bst_iter_t iter)
{
	node_t *temp = iter.node;
	
	assert(BSTGetData(iter));

	if(ChildrenCount(temp) == 0)
	{
		FreeLeaf(temp);
	}

	else if(ChildrenCount(temp) == 1 || temp->right->data == NULL)
	{
		FreeParentForOne(temp);
	}

	else if(ChildrenCount(temp) == 2 && temp->right->data != NULL)
	{
		FreeParentForTwo(temp);
	}
}

/******************************************************************************/

bst_iter_t BSTFind(const bst_t *bst, const void *data)
{
	bst_iter_t iter = {0};
	bst_iter_t iter_end = {0};

	assert(bst);

	iter = BSTBegin(bst);
	iter_end = BSTEnd(bst);

	while(!BSTIterIsEqual(iter, iter_end))
	{
		if(bst->cmp(BSTGetData(iter), data, bst->param) == 0)
		{
			return (iter);
		}

		iter = BSTNext(iter);
	}

	return (iter_end);
}

/******************************************************************************/

int BSTForEach(bst_iter_t from, bst_iter_t to, bst_do_action_func_t do_action
			   ,void *param)
{
	bst_iter_t iter = {0};
	int flag = 0;

	(void)param;

	iter = from;
	
	while(!BSTIterIsEqual(iter, to))
	{
		if(do_action(BSTGetData(iter), param) == 0)
		{
			++flag;
		}
		
		iter = BSTNext(iter);
	}

	return (!!flag);
}

/*****************************Developer functions******************************/

static void FreeLeaf(node_t *leaf)
{	
	node_t *leaf_parent = NULL;

	assert(leaf);
	assert(!leaf->left);

	leaf_parent = leaf->parent;

	if(leaf_parent->left == leaf)
	{
		leaf_parent->left = NULL;
	}
	
	else
	{
		leaf_parent->right = NULL;
	}

	free(leaf);
	leaf = NULL;
	leaf_parent = NULL;
}

/******************************************************************************/

static void FreeParentForOne(node_t *temp)
{
	node_t *temp_parent = temp->parent;
	node_t *temp_child = NULL;

	assert(temp);
	
	if(temp->left)
	{
		temp_child = temp->left;
	}

	else
	{
		temp_child = temp->right;
	}

	if(temp_parent->left == temp)
	{
		temp_parent->left = temp_child;
	}

	else
	{
		temp_parent->right = temp_child;
	}

	if(temp_child->data != NULL)
	{
		temp_child->parent = temp_parent;
	}

	free (temp);
	temp = NULL;
}

/******************************************************************************/

static void FreeParentForTwo(node_t *temp)
{
	node_t *temp_parent = temp->parent;
	node_t *temp_right = NULL;
	node_t *temp_left = NULL;

	assert(temp);

	temp_right = temp->right;
	temp_left = temp->left;
	temp_left->parent = temp_parent;
		
	if(temp == temp_parent->right)
	{
		temp_parent->right = temp_left;
	}
		
	else
	{
		temp_parent->left = temp_left;
	}

	while(temp_left->right)
	{
		temp_left = temp_left->right;
	}

	temp_left->right = temp_right;
	temp_right->parent = temp_left;

	free(temp);
	temp = NULL;
}

/******************************************************************************/

static int ChildrenCount(node_t *node)
{
	int children = 0;

	if(node->right)
	{
		++children;
	}

	if(node->left)
	{
		++children;
	}

	return (children);
}

/******************************************************************************/







