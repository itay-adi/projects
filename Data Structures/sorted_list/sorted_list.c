/*
* File Name - sorted_list.c
* Developer - Itay Adi Yosef
*/

/******************************************************************************/

#include <stdlib.h> /*malloc, free*/
#include <assert.h> /* assert */
#include <stdbool.h> /* true, false */

#include "sorted_list.h"
#include "dlist.c"

struct sorted_list
{
	dlist_t *dlist;
	sorted_list_is_before_func_t is_before;
	void *param;
};

/******************************************************************************/

sorted_list_t *SortedListCreate(sorted_list_is_before_func_t is_before,
								void *param)
{
	sorted_list_t *s_dlist = NULL;

	assert(is_before);

	s_dlist = (sorted_list_t *)malloc(sizeof(sorted_list_t));

	if(!s_dlist)
	{
		return (NULL);
	}

	s_dlist->dlist = DListCreate();

	if(!(s_dlist->dlist))
	{
		free (s_dlist);

		s_dlist = NULL;

		return (NULL);
	}

	s_dlist->is_before = is_before;

	s_dlist->param = param;
	
	return (s_dlist);
}

/******************************************************************************/

void SortedListDestroy(sorted_list_t *sorted_list)
{
	assert(sorted_list);
	
	DListDestroy(sorted_list->dlist);

	sorted_list->is_before = NULL;

	free(sorted_list);
	
	sorted_list = NULL;
}

/******************************************************************************/

sorted_list_iter_t SortedListBegin(const sorted_list_t *sorted_list)
{
	sorted_list_iter_t iter = {0};
	
	assert(sorted_list);

	iter.internal_iter = DListBegin(sorted_list->dlist);

	return (iter);
}

/******************************************************************************/

sorted_list_iter_t SortedListEnd(const sorted_list_t *sorted_list)
{
	sorted_list_iter_t iter = {0};
	
	assert(sorted_list);

	iter.internal_iter = DListEnd(sorted_list->dlist);

	return (iter);
}

/******************************************************************************/

sorted_list_iter_t SortedListNext(sorted_list_iter_t iter)
{
	sorted_list_iter_t sorted_iter = {0};

	sorted_iter.internal_iter = DListNext(iter.internal_iter);
	
	return (sorted_iter);
}

/******************************************************************************/

sorted_list_iter_t SortedListPrev(const sorted_list_iter_t iter)
{
	sorted_list_iter_t sorted_iter = {0};

	sorted_iter.internal_iter = DListPrev(iter.internal_iter);
	
	return (sorted_iter);
}

/******************************************************************************/

void *SortedListGetData(sorted_list_iter_t iter)
{
	return (DListGetData(iter.internal_iter));
}

/******************************************************************************/

int SortedListIterIsEqual(sorted_list_iter_t iter1, sorted_list_iter_t iter2)
{
	return (DListIterIsEqual(iter1.internal_iter,iter2.internal_iter));
}

/******************************************************************************/

int SortedListIsEmpty(const sorted_list_t *sorted_list)
{
	assert(sorted_list);

	return (DListIsEmpty(sorted_list->dlist));
}

/******************************************************************************/

sorted_list_iter_t SortedListInsert(sorted_list_t *sorted_list, void *data)
{
	sorted_list_iter_t where = {0};

	assert(sorted_list);

	where = SortedListBegin(sorted_list);

	/*keep going as long as you are not at the end of the list*/
	while (SortedListNext(where).internal_iter)
	{
		/*checks if the data needs to get inside this iteration*/
		if (sorted_list->is_before(data, SortedListGetData(where), sorted_list->param))
		{
			break;
		}

		where = SortedListNext(where);
	}

	where.internal_iter = DListInsert(sorted_list->dlist, where.internal_iter, data);

	if (DListIterIsEqual(where.internal_iter, DListEnd(sorted_list->dlist)))
    {
        return (SortedListEnd(sorted_list));
    }

	return (where);
}

/******************************************************************************/

sorted_list_iter_t SortedListRemove(sorted_list_iter_t iter)
{
	sorted_list_iter_t iter_temp = {0};
	
	iter_temp.internal_iter = DListRemove(iter.internal_iter);

	return (iter_temp);
}

/******************************************************************************/

void *SortedListPopFront(sorted_list_t *sorted_list)
{
	assert(sorted_list);

	return (DListPopFront(sorted_list->dlist));
}

/******************************************************************************/

void *SortedListPopBack(sorted_list_t *sorted_list)
{
	assert(sorted_list);

	return (DListPopBack(sorted_list->dlist));
}

/******************************************************************************/

size_t SortedListSize(const sorted_list_t *sorted_list)
{
	assert(sorted_list);

	return (DListSize(sorted_list->dlist));
}

/******************************************************************************/

sorted_list_iter_t SortedListFind(sorted_list_t *sorted_list,
 								  sorted_list_iter_t from,
								  sorted_list_iter_t to,
								  void *to_find)
{
	assert(sorted_list);

	while (!SortedListIterIsEqual(from, to) &&
		   sorted_list->is_before(SortedListGetData(from), to_find, sorted_list->param))
	{
		if (SortedListGetData(from) == to_find)
		{
			return (from);
		}

		from = SortedListNext(from);
	}

	return (to);
}

/******************************************************************************/

sorted_list_iter_t SortedListFindIf(sorted_list_iter_t from, 
									sorted_list_iter_t to,
									sorted_list_is_match_func_t is_match, 
									void *param)
{
	sorted_list_iter_t temp = {0};

	temp.internal_iter = DListFind(from.internal_iter, to.internal_iter,
								   is_match, param);

	return (temp);
}

/******************************************************************************/

int SortedListForEach(sorted_list_iter_t from, 
					  sorted_list_iter_t to, 
					  sorted_list_do_action_func_t do_action, 
					  void *param)
{
	while (from.internal_iter != to.internal_iter)
	{
		if (!(do_action(SortedListGetData(from), param)))
		{
			return (false);
		}

		from = SortedListNext(from);
	}

	return (true);
}

/******************************************************************************/

void SortedListMerge(sorted_list_t *dest, sorted_list_t *src)
{
	void *data_popped = NULL;
	void *data_last_node_dest = NULL;
	sorted_list_iter_t dest_last_node = {NULL};
	
	assert(dest);
	assert(dest->dlist);
	assert(src);
	assert(src->dlist);
	assert(src != dest);

	/* if both empty, does nothing */
	if (SortedListIsEmpty(dest) && SortedListIsEmpty(src))
	{
		return;
	}
	
	/* if dest is empty - splices src into dest */
	else if (SortedListIsEmpty(dest))
	{
		DListSplice(SortedListBegin(src).internal_iter, 
						SortedListEnd(src).internal_iter, 
						SortedListEnd(dest).internal_iter);
		
		return;
	} 
	
	else
	{
		dest_last_node = SortedListPrev(SortedListEnd(dest));
		data_last_node_dest = SortedListGetData(dest_last_node);
		
		while (!SortedListIsEmpty(src))
		{
			/* if data in src is not greater than in the last element of 
				dest - splices src into dest */
			if (dest->is_before(data_last_node_dest, 
								SortedListGetData(SortedListBegin(src)), dest->param))
			{
				DListSplice(SortedListBegin(src).internal_iter, 
							SortedListEnd(src).internal_iter, 
							SortedListEnd(dest).internal_iter);
				
				return;
			}
		
			data_popped = SortedListPopFront(src);	
			SortedListInsert(dest, data_popped);	
		}
	}
}

/******************************************************************************/




