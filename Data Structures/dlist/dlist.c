/*
* File Name - dlist.c
* Developer - Itay Adi Yosef
*/

/******************************************************************************/

#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */
#include <stdio.h>

#include "dlist.h"

#define SUCCESS 0
#define FAIL 1

#define INVALID_DATA (void *)0xBADC0FFEE0DDF00D

struct dlist_node
{
    void *data;
    dlist_iter_t next;
    dlist_iter_t prev;	
};

struct dlist
{
	dlist_iter_t head;
    dlist_iter_t tail;
};

/******************************************************************************/

/*Function which helps us tp create a iter*/
static dlist_iter_t IterCreate(void);

/******************************************************************************/

dlist_t *DListCreate(void)
{
	dlist_t *dl_list = NULL;
	dlist_iter_t dl_node_head = NULL;
	dlist_iter_t dl_node_tail = NULL;

	if (!(dl_list = (dlist_t *)malloc(sizeof(dlist_t))))
	{
		return (NULL);
	}

	if (!(dl_node_head = IterCreate()))
	{
		free(dl_list);
		
		dl_list = NULL;

		return (NULL);
	}

	if (!(dl_node_tail = IterCreate()))
	{
		free(dl_list);
		free(dl_node_head);
		
		dl_list = NULL;
		dl_node_head = NULL;

		return (NULL);
	}

	dl_list->head = dl_node_head;
	dl_list->tail = dl_node_tail;

	dl_node_head->data = INVALID_DATA;
	dl_node_head->next = dl_node_tail;
	dl_node_head->prev = NULL;

	dl_node_tail->data = INVALID_DATA;
	dl_node_tail->next = NULL;
	dl_node_tail->prev = dl_node_head;

	return (dl_list);
}

/******************************************************************************/

void DListDestroy(dlist_t *dlist)
{
	dlist_iter_t curr_node = NULL;
	dlist_iter_t next_node = NULL;

	assert(dlist);

	curr_node = dlist->head;
	next_node = dlist->head;

	while (curr_node != dlist->tail)
	{
		next_node = next_node->next;

		free(curr_node);

		curr_node = next_node;	
	}

	free(next_node);
	free(dlist);

	dlist = NULL;
	curr_node = NULL;
	next_node = NULL;
}

/******************************************************************************/

dlist_iter_t DListBegin(const dlist_t *dlist)
{
	assert(dlist);

	return (dlist->head->next);
}

/******************************************************************************/

dlist_iter_t DListEnd(const dlist_t *dlist)
{
	assert(dlist);

	return (dlist->tail);
}

/******************************************************************************/

dlist_iter_t DListNext(dlist_iter_t iter)
{
	assert(iter);

	return (iter->next);
}

/******************************************************************************/

dlist_iter_t DListPrev(dlist_iter_t iter)
{
	assert(iter);

	return (iter->prev);
}

/******************************************************************************/

void *DListGetData(dlist_iter_t iter)
{
	assert(iter);

	return (iter->data);
}

/******************************************************************************/

void DListSetData(dlist_iter_t iter, void *data)
{
	assert(iter);
	assert(data);

	iter->data = data;
}

/******************************************************************************/

int DListIterIsEqual(dlist_iter_t iter1, dlist_iter_t iter2)
{
	assert(iter1);
	assert(iter2);

	return (iter1 == iter2);
}

/******************************************************************************/

int DListIsEmpty(const dlist_t *dlist)
{
	assert(dlist);

	return (dlist->head->next == dlist->tail);
}

/******************************************************************************/

dlist_iter_t DListInsert(dlist_t *dlist, dlist_iter_t where, void *data)
{
	dlist_iter_t new_iter = NULL;
	dlist_iter_t back_iter = NULL;

	assert(dlist);
	assert(where);
	
	if(!(new_iter = IterCreate()))
	{
		return (DListEnd(dlist));
	}

	new_iter->data = data;
	back_iter = DListPrev(where);
	back_iter->next = new_iter;
	new_iter->prev = back_iter;

	where->prev = new_iter;
	new_iter->next = where;

	return (new_iter);
}

/******************************************************************************/

static dlist_iter_t IterCreate(void)
{
	dlist_iter_t new_iter = NULL;

	if (!(new_iter = (dlist_iter_t)malloc(sizeof(struct dlist_node))))
	{
		return (NULL);
	}

	return (new_iter);
}

/******************************************************************************/

dlist_iter_t DListRemove(dlist_iter_t iter)
{
	dlist_iter_t iter_prev = NULL;
	dlist_iter_t iter_next = NULL;

	assert(iter);

	iter_prev = DListPrev(iter);
	iter_next = DListNext(iter);
	iter_prev->next = iter_next;
	iter_next->prev = iter_prev;

	free(iter);
	
	iter = NULL;

	return(iter_next);
}

/**********************************************************************/

dlist_iter_t DListPushFront(dlist_t *dlist, void *data)
{
	assert(dlist);
	
	return (DListInsert(dlist, DListBegin(dlist), data));
}

/**********************************************************************/

dlist_iter_t DListPushBack(dlist_t *dlist, void *data)
{
	assert(dlist);

	return (DListInsert(dlist, DListEnd(dlist), data));
}

/**********************************************************************/

void *DListPopFront(dlist_t *dlist)
{
	void *data = NULL;

	assert(dlist);

	data = DListGetData(DListBegin(dlist));
	DListRemove(DListBegin(dlist));

	return (data);
}

/**********************************************************************/

void *DListPopBack(dlist_t *dlist)
{
	void *data = NULL;

	assert(dlist);

	data = DListGetData(DListEnd(dlist)->prev);
	DListRemove(DListEnd(dlist)->prev);

	return (data);
}

/**********************************************************************/

size_t DListSize(const dlist_t *dlist)
{
	size_t count = 0;
	dlist_iter_t temp_iter = NULL;

	assert(dlist);

	temp_iter = DListBegin(dlist);

	while (temp_iter != DListEnd(dlist))
	{
		++count;
		temp_iter = DListNext(temp_iter);
	}

	return (count);
}

/**********************************************************************/

dlist_iter_t DListFind(dlist_iter_t from, dlist_iter_t to,
					   dlist_is_match_func_t is_match, void *param)
{
	dlist_iter_t temp_iter = NULL;
	
	assert(from);
	assert(to);

	temp_iter = from;

	while(temp_iter != to)
	{
		if(is_match(DListGetData(temp_iter), param))
		{
			return (temp_iter);
		}

		temp_iter = DListNext(temp_iter);
	}

	return(temp_iter);
}

/**********************************************************************/

int DListForEach(dlist_iter_t from, dlist_iter_t to, 
				 dlist_do_action_func_t do_action, void *param)
{
	dlist_iter_t temp_iter = NULL;
	
	assert(from);
	assert(to);

	temp_iter = from;

	while(temp_iter != to)
	{
		if(do_action(DListGetData(temp_iter), param))
		{
			return (FAIL);
		}
		
		temp_iter = DListNext(temp_iter);
	}

	return(SUCCESS);
}

/**********************************************************************/

dlist_iter_t DListSplice(dlist_iter_t from, dlist_iter_t to, dlist_iter_t where)
{
	dlist_iter_t from_prev = NULL;
	dlist_iter_t to_prev = NULL;
	dlist_iter_t where_prev = NULL;

	assert(from);
	assert(to);
	assert(where);

	from_prev = DListPrev(from);
	to_prev = DListPrev(to);
	from_prev->next = to;
	to->prev = from_prev;

	where_prev = DListPrev(where);
	where_prev->next = from;
	from->prev = where_prev;

	where->prev = to_prev;
	to_prev->next = where;

	return (to_prev);
}

/**********************************************************************/

