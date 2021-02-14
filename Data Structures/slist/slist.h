/*
* File Name - slist.h
* Developer - Itay Adi Yosef
*/

#ifndef ILRD_SLIST_H
#define ILRD_SLIST_H

#include <stddef.h>	/* size_t */

/* typedefs for the slist and the iterator  */
typedef struct slist_node* slist_iter_t;  
typedef struct slist slist_t; 

/* typedefs of functions to be implemented by the user */

/* return value is boolean - 1 for match, 0 if not matched */
typedef int (*slist_is_match_func_t)(void *data, void *param);
/* return value is status - 0 for success, 1 for fail */
typedef int (*slist_do_action_func_t)(void *data, void *param);

/*---------------------------------------------------------------------------*/
/* SListCreate:
*   - creates an empty list.
*
* Return Value:
*   - pointer to the slist.
*/
slist_t *SListCreate(void);

/*---------------------------------------------------------------------------*/
/* SListDestroy:
*   - destroys the list
*
* Args:
*   - slist - pointer to slist given by user
*/
void SListDestroy(slist_t *slist);

/*---------------------------------------------------------------------------*/
/* SListBegin
*   - returns an iterator to the first element in the list.
*
* Args:
*	- slist - pointer to slist
*
* Return value:
*   - an iterator to the first element in the list
*/
slist_iter_t SListBegin(const slist_t *slist);

/*---------------------------------------------------------------------------*/
/* SListEnd
*   - returns an iterator to the end of the list
*
* Args:
*	- slist - pointer to slist
*
* Return value:
*   - iterator to the end of the list
*/

slist_iter_t SListEnd(const slist_t *slist);

/*---------------------------------------------------------------------------*/
/* SlistNext
*   - returns an iterator to the element after the iterator given by the user
*
* Args:
*   - iter - iterator to get the element after
*
* Return value:
*   - an iterator to the next element after the iterator given.
*
* Comments: 
*   - in case of invalid iterator given - undefined behavior.
*/

slist_iter_t SListNext(const slist_iter_t iter);

/*---------------------------------------------------------------------------*/
/* SlistGetData
* - returns the data stored in the given iterator.
*
* Args:
*   - iter - iterator to retrieve data from
*
* Return value:
*   - Data stored in the iterator
*
* Comments: 
*   - in case of invalid iterator - undefined behavior.
*/
void *SListGetData(const slist_iter_t iter);

/*---------------------------------------------------------------------------*/
/* SListSetData
* - sets data in a given iterator
*
* Args:
*   -  iter - iterator in which we want to set the data

* Comments: 
*	- in case of invalid iterator - undefined behavior.
*/
void SListSetData(slist_iter_t iter, void *data);

/*---------------------------------------------------------------------------*/
/* SListIterIsEqual
* - checks if two iterators are equal
*
* Args:
*   - iter1 - first iterator to compare
*   - iter2 - second iterator to compare 
*
* Return value:
*   - 1 - equal 
*   - 0 - not equal
*/
int SListIterIsEqual(const slist_iter_t iter1, const slist_iter_t iter2);

/*---------------------------------------------------------------------------*/
/* SListIsEmpty:
*   - checks if the slist is empty or not
* 
* Args:
*   - slist - pointer to slist given by user
*  
* Return Value:
*   1 - empty
*   0 - not empty.       
*/
int SListIsEmpty(const slist_t *slist);

/*---------------------------------------------------------------------------*/
/* SListInsert:
* - inserts new element before the iterator given by the user.
* 
* Args:
*   - slist - pointer to slist
*   - where - iterator before which we want to store the data
*   - data - data to store
*
* Return value:
*   - if succeeded, returns an iterator to the data
*	- if failed, returns the end of the list
*
* Comments: 
*	- in case of invalid iterator - undefined behavior.
*	- User should compare the return value to the end of the list to determine
*	  if function succeeded.
*	- In case list is empty, provide the end of the list (SListEnd) as "where"
*	- After using Insert the iterator will no longer be valid
*/
slist_iter_t SListInsert(slist_t *slist, slist_iter_t where, void *data);

/*---------------------------------------------------------------------------*/
/* SListInsertAfter:
*   - inserts new element after the iterator given by the user.
* 
* Args:
*   - slist - pointer to slist given by user
*   - where - iterator after which we want to store the data
*   - data - data to store
*
* Return value:
*   - if succeeded, returns an iterator to the element
*	- if failed, returns the end of the list
*
* Comments: 
*	- in case of invalid iterator - undefined behavior.
*	  asserts when compiling.
*	- User should compare the return value to the end of the list to determine
*	  if function succeeded.
*   - In case list is empty, call SListBefore (see comments)
*/
slist_iter_t SListInsertAfter(slist_t *slist, slist_iter_t where, void *data);

/*---------------------------------------------------------------------------*/
/* SListRemove:
*   - removes an element from the linked list.
* 
* Args:
*	- slist - pointer to slist given by user
*   - iter - iterator to the element to remove
* 
* Return value:
*	- an iterator to the next element
*/
slist_iter_t SListRemove(slist_t *slist, slist_iter_t iter);

/*---------------------------------------------------------------------------*/
/* SListCount:
*   - counts the number of elements in the slist.
* 
* Args:
*   - slist - pointer to slist
*  
* Return Value:
*   - number of elements in the slist         
*/
size_t SListCount(const slist_t *slist);

/*---------------------------------------------------------------------------*/
/* SListFind:
*   - finds data stored in list.
* 
* Args:
*   - from - iterator to the beginning of the range
*   - to - iterator to the end of the range
*   - is_match - function pointer to perform comparison
*	- param - parameter to pass to match function (optional)
*
* Return Value: 
*	- if succeeded, returns iterator to the first element matched
*	- if failed, returns the iterartor "to". 
*
* Comments: 
*	- Range includes "from" and excludes "to".
*	- User should compare the return value to the "to" iterator, to determine
*	  whether function succeeded.
*	- is_match is a function to be implemeneted by the user. See signature 
*	  in typedef.
*/
slist_iter_t SListFind(const slist_iter_t from, 
                       const slist_iter_t to,
					   slist_is_match_func_t is_match, 
                       void *param);

/*---------------------------------------------------------------------------*/
/* SListForEach
*   - performes action in a function given by the user on all list elements
*
* Args:
*   - from - iterator to the beginning of range
*   - to - iterator to the end of range
*   - do_action - function pointer to the action pointer
*	- param - parameter to pass to action function (optional)
*   
* Return value:
*   - 1 - the action succeeds for all the elements in the range
*   - 0 - the action failed in at least one element.
*
* Comments: 
*	- Range includes "from" and excludes "to".
*	- do_action is a function to be implemeneted by the user. See signature 
*	  in typedef.
*/
int SListForEach(const slist_iter_t from, 
                 const slist_iter_t to, 
				 slist_do_action_func_t do_action, 
                 void *param);
                 
/*---------------------------------------------------------------------------*/
/* SListAppend:
*   - appends the src list to the end of dest list.
*
* Args:
*   - dest - pointer to slist given by user.
*   - src - pointer to slist given by user.
*
* Comments: 
*   - in case of invalid slists - undefined behavior.
*   
*/
void SListAppend(slist_t *dest, slist_t *src);

/*---------------------------------------------------------------------------*/

#endif /* ILRD_SLIST_H*/
