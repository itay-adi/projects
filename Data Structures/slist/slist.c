/*
* File Name - slist.c
* Developer - Itay Adi Yosef
*/

#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */

#include "slist.h"

enum mode {SUCCESS=0, FAIL=1};

struct slist
{
	slist_iter_t head;
    slist_iter_t tail;
};

struct slist_node
{
    void *data;
    slist_iter_t next;
};

/******************************************************************************/

/*Function which helps us tp create a node*/
static slist_iter_t CreateNode(void);

/******************************************************************************/

slist_t *SListCreate(void)
{
	slist_t *slist_ptr = NULL;
	slist_iter_t node_ptr = NULL;

	if(!(slist_ptr = (slist_t *)malloc(sizeof(slist_t))))
	{
		return (NULL);
	}

	if(!(node_ptr = CreateNode()))
	{
		free(slist_ptr);
		slist_ptr = NULL;

		return (NULL);
	}
	
	slist_ptr->head = node_ptr;
	slist_ptr->tail = node_ptr;
	node_ptr->data = NULL;
	node_ptr->next = NULL;

	return (slist_ptr);
}

/******************************************************************************/

void SListDestroy(slist_t *slist)
{
	slist_iter_t curr_node = NULL;
	slist_iter_t next_node = NULL;
	
	assert(slist);

	curr_node = slist->head;
	next_node = slist->head;

	while (curr_node != slist->tail)
	{
		next_node = next_node->next;

		free(curr_node);
		
		curr_node = next_node;
	}

	
	free(next_node);
	free(slist);

	slist = NULL;
	curr_node = NULL;
	next_node = NULL;
}

/******************************************************************************/

slist_iter_t SListBegin(const slist_t *slist)
{
	assert(slist);

	return (slist->head);
}

/******************************************************************************/

slist_iter_t SListEnd(const slist_t *slist)
{
	assert(slist);

	return (slist->tail);
}

/******************************************************************************/

slist_iter_t SListNext(const slist_iter_t iter)
{
	assert(iter);

	return (iter->next);
}

/******************************************************************************/

void *SListGetData(const slist_iter_t iter)
{
	assert(iter);

	return (iter->data);
}

/******************************************************************************/

int SListIsEmpty(const slist_t *slist)
{
	assert(slist);

	return (slist->head == slist->tail);
}

/******************************************************************************/

slist_iter_t SListInsert(slist_t *slist, slist_iter_t where, void *data)
{
	slist_iter_t new_iterator = NULL;

	assert(slist);
	assert(where);
	
	if(!(new_iterator = CreateNode()))
	{
		return (SListEnd(slist));
	}

	new_iterator->data = where->data;
	new_iterator->next = where->next;
	
	where->data = data;
	where->next = new_iterator;
	
	/*For the case the user entered the dummy*/
	if(slist->tail == where)
	{
		slist->tail = new_iterator;
	}

	return (where);
}

/******************************************************************************/

void SListSetData(slist_iter_t iter, void *data)
{
	assert(iter);
	assert(data);

	iter->data = data;	
}

/******************************************************************************/

slist_iter_t SListInsertAfter(slist_t *slist, slist_iter_t where, void *data)
{
	slist_iter_t new_iterator = NULL;

	assert(slist);
	assert(where);
	assert(!(SListIterIsEqual(where, SListEnd(slist))));

	if(where == slist->tail)
	{
		return (SListEnd(slist));
	}

	if(!(new_iterator = CreateNode()))
	{
		return (SListEnd(slist));
	}
	
	new_iterator->next = where->next;
	where->next = new_iterator;
	new_iterator->data = data;

	return (new_iterator);
}

/******************************************************************************/

int SListIterIsEqual(const slist_iter_t iter1, const slist_iter_t iter2)
{
	assert(iter1);
	assert(iter2);

	return(iter1 == iter2);
}

/******************************************************************************/

slist_iter_t SListRemove(slist_t *slist, slist_iter_t iter)
{
	slist_iter_t next_iter = NULL;

	assert(slist);
	assert(iter != SListEnd(slist));

	next_iter = SListNext(iter);
	iter->data = next_iter->data;
	iter->next = next_iter->next;

	if(next_iter == SListEnd(slist))
	{
		slist->tail = iter;
	}

	free(next_iter);

	next_iter = NULL;

	return(iter);
}

/******************************************************************************/

size_t SListCount(const slist_t *slist)
{
	size_t count = 0;
	slist_iter_t iter = NULL;

	assert(slist);

	iter = SListBegin(slist);
	
	while(iter != SListEnd(slist))
	{
		++count;
		iter = 	SListNext(iter);	
	}

	return (count);
}

/******************************************************************************/

slist_iter_t SListFind(const slist_iter_t from, const slist_iter_t to,
					   slist_is_match_func_t is_match, void *param)
{
	slist_iter_t iter = NULL;

	assert(from);
	assert(to);
	
	iter = from;

	while(iter != to)
	{
		if(!(is_match(param, iter->data)))
		{
			return (iter);
		}

		iter = SListNext(iter);
	}

	return (to);
}

/******************************************************************************/

int SListForEach(const slist_iter_t from, const slist_iter_t to, 
				 slist_do_action_func_t do_action, void *param)
{
	slist_iter_t iter = NULL;

	assert(from);
	assert(to);
	
	iter = from;

	while(iter != to)
	{
		if(do_action(iter->data, param))
		{
			return (FAIL);
		}
		
		iter = SListNext(iter);
	}

	return (SUCCESS);

}

/******************************************************************************/

void SListAppend(slist_t *dest, slist_t *src)
{
	assert(dest);
	assert(src);

	*(dest->tail) = *(src->head);

	dest->tail = src->tail;
	src->tail = src->head;
	src->head->data = NULL;
	src->head->next = NULL;
}

/******************************************************************************/

static slist_iter_t CreateNode(void)
{
	slist_iter_t node_ptr = NULL;

	if(!(node_ptr = (slist_iter_t)malloc(sizeof(struct slist_node))))
	{
		return (NULL);
	}

	return (node_ptr);
}

/******************************************************************************/














