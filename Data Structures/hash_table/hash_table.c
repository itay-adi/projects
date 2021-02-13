/*
* File Name - hash_table.c
* Developer - Itay Adi Yosef
*/

#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */

#include "hash_table.h"
#include "dlist.h"

typedef struct bucket bucket_t;

struct hash
{
    dlist_t **bucket;
    hash_table_func_t hash_func;
    hash_is_match_func_t Is_match;
    void *param;
    size_t size;
};

enum exit_status
{
    success, fail
};

/****************************Assistance functions******************************/

size_t FindIndex(hash_t *hash, void *data);

/******************************************************************************/

hash_t *HashCreate(hash_table_func_t hash_func,hash_is_match_func_t match_func, void *param, size_t table_size)
{
    hash_t *hash = NULL;
    size_t i = 0;

    hash = (hash_t *)malloc(sizeof(hash_t));

    if(NULL == hash)
    {
        return (NULL);
    }

    hash->bucket = (dlist_t **)malloc(sizeof(dlist_t *) * table_size);

    if(NULL == hash->bucket)
    {
        free(hash);

        return (NULL);
    }

    hash->hash_func = hash_func;
    hash->Is_match = match_func;
    hash->param = param;
    hash->size = table_size;

    for(i = 0; i < table_size; ++i)
    {
        hash->bucket[i] = NULL;
    }

    return (hash);
}

/******************************************************************************/

size_t HashSize(const hash_t *hash)
{
    size_t size = 0;
    size_t i = 0;

    assert(hash);

    for(i = 0; i < hash->size; ++i)
    {
        if(hash->bucket[i])
        {
            size += DListSize(hash->bucket[i]);
        }
    }

    return (size);
}

/******************************************************************************/

void HashDestroy(hash_t *hash)
{
    size_t i = 0;

    assert(hash);

    for(i = 0; i < hash->size; ++i)
    {
        if(hash->bucket[i])
        {
            DListDestroy(hash->bucket[i]);
        }
    }

    free(hash->bucket);
    hash->bucket = NULL;
    
    free(hash);
    hash = NULL;
}

/******************************************************************************/

size_t HashTableSize(const hash_t *hash)
{
    assert(hash);

    return(hash->size);
}

/******************************************************************************/

size_t HashBucketSize(const size_t index, const hash_t *hash)
{
    assert(hash);

    if(hash->bucket[index])
    {
        return(DListSize(hash->bucket[index]));
    }

    return (0);
}

/******************************************************************************/

int HashIsEmpty(const hash_t *hash)
{
    size_t i = 0;

    assert(hash);

    for(i = 0; i < hash->size; ++i)
    {
        if(hash->bucket[i])
        {
            return (success);
        }
    }

    return (fail);
}

/******************************************************************************/

int HashInsert(hash_t *hash, void *data)
{
    int index = 0;
    dlist_iter_t end = {0};

    assert(hash);

    index = FindIndex(hash, data);

    if(hash->bucket[index] == NULL)
    {
        hash->bucket[index] = DListCreate();

        if(hash->bucket[index] == NULL)
        {
            return (fail);
        }
    }

    if(HashFind(hash, data))
    {
        return (fail);
    }
   
    end = DListEnd(hash->bucket[index]);

    if(DListIterIsEqual(DListPushBack(hash->bucket[index], data), end))
    {
        return (fail);
    }

    return (success);
}

/******************************************************************************/

void *HashFind(const hash_t *hash, const void *data)
{
    dlist_iter_t begin = {0};
    dlist_iter_t end = {0};
    dlist_iter_t data_iterator = {0};
    size_t index = 0;

    assert(hash);

    index = FindIndex((hash_t *)hash, (void *)data);
    begin = DListBegin(hash->bucket[index]);
    end = DListEnd(hash->bucket[index]);
    data_iterator = DListFind(begin, end, hash->Is_match, (void *)data);

    if(DListIterIsEqual(data_iterator, end))
    {
        return (NULL);
    }

    return(data_iterator);
}

/******************************************************************************/

void HashRemove(hash_t *hash, void *data)
{
    dlist_iter_t temp = {0};

    temp = HashFind(hash, data);

    if(temp)
    {
        DListRemove(temp);

    }
}

/******************************************************************************/

int HashForEach(hash_t *hash, hash_do_action_func_t do_action ,void *param)
{
    size_t i = 0;
    int problem = 0;
    dlist_iter_t begin = {0};
    dlist_iter_t end = {0};

    assert(hash);

    for(i = 0; i < hash->size; ++i)
    {
        if(hash->bucket[i])
        {
            begin = DListBegin(hash->bucket[i]);
            end = DListEnd(hash->bucket[i]);
            problem = DListForEach(begin, end, do_action, param);
            
            if(problem)
            {
                return (problem);
            }
        }
    }

    return (success);
}

/*************************Assistance functions*********************************/

size_t FindIndex(hash_t *hash, void *data)
{
    size_t index = 0;

    assert(hash);

    index = hash->hash_func(data, hash->param ) % hash->size;

    return (index);
}

/******************************************************************************/
