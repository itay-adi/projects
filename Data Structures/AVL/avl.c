/*
* File Name - avl.c
* Developer - Itay Adi Yosef
*/

#include <stdlib.h> /* malloc, free */
#include <stdio.h>
#include <assert.h> /* assert */

#include "avl.h"

typedef struct node node_t;

struct avl
{
    void *param;
    avl_cmp_func_t cmp;
    node_t *root;
};

struct node
{
    node_t *child[2];
    void *data;
};

enum child
{
    left, right
};

/**********************assistance functions declarations***********************/

static node_t *Rec_Insert(node_t *node, avl_t *avl, void *data);
static void *Rec_Find(node_t *node, const avl_t *avl, const void *data);
static int Rec_ForEach(node_t *node, avl_do_action_func_t do_action ,void *param);
static node_t* CreateNode(void *data);
void AVL_PostOrder_Print(const avl_t *avl);
static void Rec_PostOrderPrint(node_t *node);
static size_t Rec_Size(node_t *node, size_t size);
static size_t Tree_Height(node_t *node);
static int IsBalanced(node_t *node);
static node_t *RightRotate(node_t *node);
static node_t *LeftRotate(node_t *node);
static node_t *LeftRightRotation(node_t *node);
static node_t *RightLeftRotation(node_t *node);
static node_t *BalanceTheTree(node_t *node);
static void Rec_Destory(node_t *node);
static node_t *Rec_Remove(node_t *node, avl_t *avl, void *data);
static void FreeNode(node_t *node);
static void Cpy_Node_Properties(node_t *src, node_t *dest);

/******************************************************************************/

avl_t *AVLCreate(avl_cmp_func_t cmp, void *param)
{
    avl_t *avl = NULL;

    avl = (avl_t *)malloc(sizeof(avl_t));

    if (NULL == avl)
    {
        return (NULL);
    }

    avl->param = param;
    avl->cmp = cmp;
    avl->root = NULL;

    return (avl);
}

/******************************************************************************/

int AVLInsert(avl_t *avl, void *data)
{
    assert(avl);

    if(!AVLFind(avl, data))
    {
        if (Rec_Insert(avl->root, avl, data))
        {
            return (0);
        }
    }

    return (1);
}

/******************************************************************************/

void *AVLFind(const avl_t *avl, const void *data)
{
    assert(avl);
    assert(data);

    return (Rec_Find(avl->root, avl, data));
}

/******************************************************************************/

int AVLForEach(avl_t *avl, avl_do_action_func_t do_action ,void *param)
{
    assert(avl);

    return (Rec_ForEach(avl->root, do_action, param));
}

/******************************************************************************/

size_t AVLSize(const avl_t *avl)
{
    size_t size = 0;

    assert(avl);

    size = Rec_Size(avl->root, size);

    return (size);
}

/******************************************************************************/

int AVLIsEmpty(const avl_t *avl)
{
    if (NULL == avl->root)
    {
        return (1);
    }

    return (0);
}

/******************************************************************************/

void AVLDestroy(avl_t *avl)
{
    assert(avl);

    Rec_Destory(avl->root);

    free(avl);

    avl = NULL;
}

/******************************************************************************/

void AVLRemove(avl_t *avl, void *data)
{
    Rec_Remove(avl->root, avl, data);
}

/**********************assistance functions Implementations********************/

node_t *Rec_Insert(node_t *node, avl_t *avl, void *data)
{
    int index = 0;
	/*If we arrived to an empty leaf, we create a new one*/
    if (NULL == node)
    {
        node = CreateNode(data);
        
        if (NULL == avl->root)
        {
            avl->root = node;
        }
    }

    else
    {
        index = avl->cmp(data, node->data, NULL) < 0;
        node->child[index] = Rec_Insert(node->child[index], avl, data); 
    }

	/*here we balance the tree*/
    if (((IsBalanced(node) > 1) || (IsBalanced(node) < -1)))
    {
		/*if we changed the root, update it*/
        if (avl->root == node)
        {
            avl->root = BalanceTheTree(node);
        }

        else
        {
            node = BalanceTheTree(node);
        }
    }

    return (node);
}

/************************************************************/

void *Rec_Find(node_t *node, const avl_t *avl, const void *data)
{
    int index = 0;

    if (NULL == node)
    {
        return (NULL);
    }

	/*once we found the match, return it*/
    else if (avl->cmp(data, node->data, NULL) == 0)
    {
        return (node->data);
    }

    else
    {
        index = avl->cmp(data, node->data, NULL) < 1;

        return(Rec_Find(node->child[index], avl, data));
    }
}

/************************************************************/

node_t* CreateNode(void *data)
{
    node_t *node = NULL;

    node = (node_t *)malloc(sizeof(node_t));

    if (NULL == node)
    {
        return (NULL);
    }

    node->data = data;
    node->child[right] = NULL;
    node->child[left] = NULL;

    return (node); 
}

/************************************************************/

int Rec_ForEach(node_t *node, avl_do_action_func_t do_action ,void *param)
{
	/*if we arrived to a NULL, return without looking back*/
    if (NULL == node)
    {
        return (1);
    }

	/*if we have a left child, turn left*/
    if (node->child[left])
    {
        Rec_ForEach(node->child[left], do_action, param);
    }

	/*if we have a right child, turn right*/
    if (node->child[right])
    {
        Rec_ForEach(node->child[right], do_action, param);
    }

	/*do the action itself*/
    return (do_action(node->data, param));
}

/************************************************************/

void AVL_PostOrder_Print(const avl_t *avl)
{
    assert(avl);

    Rec_PostOrderPrint(avl->root);
    printf("\n");
}

/************************************************************/

void Rec_PostOrderPrint(node_t *node)
{
    if (node->child[left])
    {
        Rec_PostOrderPrint(node->child[left]);
    }

    if (node->child[right])
    {
        Rec_PostOrderPrint(node->child[right]);
    }

    printf("%d, ", *(int *)node->data);
}

/************************************************************/

size_t Rec_Size(node_t *node, size_t size)
{
	/*if we arrived to a NULL, return without looking back*/
    if (NULL == node)
    {
        return (size);
    }

	/*if we have a left child, turn left*/
    if (node->child[left])
    {
        size = Rec_Size(node->child[left], size);
    }

	/*if we have a right child, turn right*/
    if (node->child[right])
    {
        size = Rec_Size(node->child[right], size);
    }

    return (size + 1);
}

/************************************************************/

size_t Tree_Height(node_t *node)
{
    size_t height1 = 0;
    size_t height2 = 0;

    if (NULL == node)
    {
        return (0);
    }

    height1 = Tree_Height(node->child[left]);
    height2 = Tree_Height(node->child[right]);
    
    if (height1 > height2)
    {
        return (height1 + 1);
    }

    else
    {
        return (height2 + 1);
    }
}

/************************************************************/

int IsBalanced(node_t *node)
{
    return (Tree_Height(node->child[0]) - Tree_Height(node->child[1]));
}

/************************************************************/

node_t *RightRotate(node_t *node) 
{ 
    node_t *new_head = node->child[left]; 
    node_t *temp = new_head->child[right]; 
  
    new_head->child[right] = node; 
    node->child[left] = temp;

    return (new_head); 
}

/************************************************************/

node_t *LeftRotate(node_t *node) 
{ 
    node_t *new_head = node->child[right]; 
    node_t *temp = new_head->child[left]; 
  
    new_head->child[left] = node; 
    node->child[right] = temp; 

    return (new_head); 
}

/************************************************************/

node_t *RightLeftRotation(node_t *node)
{
    node_t *temp = node->child[right];
    node_t *new_head = temp->child[left];

    new_head->child[left] = node;
    new_head->child[right] = temp;

    node->child[right] = NULL;
    node->child[left] = NULL;
    temp->child[right] = NULL;
    temp->child[left] = NULL;
    
    return (new_head);
}

/************************************************************/

node_t *LeftRightRotation(node_t *node)
{
    node_t *temp = node->child[left];
    node_t *new_head = temp->child[right];

    new_head->child[right] = node;
    new_head->child[left] = temp;

    node->child[right] = NULL;
    node->child[left] = NULL;
    temp->child[right] = NULL;
    temp->child[left] = NULL;
    
    return (new_head);
}

/************************************************************/

node_t *BalanceTheTree(node_t *node)
{
    node_t * temp = NULL;

    /*Heavy right case*/
    if (IsBalanced(node) < -1)
    {
        temp = node->child[right];

        if (IsBalanced(temp) <= 0)
        {
            return (LeftRotate(node));
        }

        else
        {
            return (RightLeftRotation(node));
        }
    }

    /*Heavy left case*/
    else if (IsBalanced(node) > 1)
    {
        temp = node->child[left];

        if (IsBalanced(temp) >= 0)
        {
            return (RightRotate(node));
        }

        else
        {
            return (LeftRightRotation(node));
        }
    }

    return (node);
}

/************************************************************/

void Rec_Destory(node_t *node)
{
    if (node->child[left])
    {
        Rec_Destory(node->child[left]);
        node->child[left] = NULL;
    }

    if (node->child[right])
    {
        Rec_Destory(node->child[right]);
        node->child[right] = NULL;
    }

    free(node);
    node = NULL;
}

/************************************************************/

node_t *Rec_Remove(node_t *node, avl_t *avl, void *data)
{
    int index = 0;
    node_t *new_head = NULL;

    /*checks if we arrived to the wanted node*/
    if (avl->cmp(node->data, data, NULL) == 0)
    {
        /*if node has 2 children*/
        if ((node->child[right] != NULL) && (node->child[left] != NULL))
        {
            new_head = node->child[left];

            while (new_head->child[right])
            {
                new_head = new_head->child[right];
            }

            Cpy_Node_Properties(new_head, node);

            node->child[left] = Rec_Remove(node->child[left], avl, new_head->data);

            return (node);
        }

        /*if node has no kids*/
        else if ((node->child[right] == NULL) && (node->child[left] == NULL))
        {
            FreeNode(node);

            return (NULL);
        }

        /*if has only one child, 0=left, 1=right*/
        else
        {
            index = node->child[right] != NULL;

            new_head = node->child[index];

            FreeNode(node);

            return (new_head); 
        }
    }

    else
    {
        index = avl->cmp(node->data, data, NULL) == 1;
        node->child[index] = Rec_Remove(node->child[index], avl, data);
    }

    /*balancing the tree*/
    if (((IsBalanced(node) > 1) || (IsBalanced(node) < -1)))
    {
        if (avl->root == node)
        {
            avl->root = BalanceTheTree(node);
        }

        else
        {
            node = BalanceTheTree(node);
        }
    }

    return (node);
}

/************************************************************/

void FreeNode(node_t *node)
{
    free(node);

    node = NULL;
}

/************************************************************/

void Cpy_Node_Properties(node_t *src, node_t *dest)
{
    dest->data = src->data;
}

/************************************************************/
