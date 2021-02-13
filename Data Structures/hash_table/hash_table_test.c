/*
* File Name - hash_table_test.c
* Developer - Itay Adi Yosef
*/

#include <stdio.h> /* printf */
#include <string.h> /* strcmp */
#include <stdlib.h> /* exit */

#include "hash_table.h"

typedef struct worker worker_t;

struct worker
{
    char *name;
    char *address;
    char *phone;
    int age;
};

/************************Test function declarations****************************/

hash_t *HashCreateTest(hash_table_func_t hash_func,hash_is_match_func_t match_func, void *param, size_t table_size);
void HashSizeTest(const hash_t *hash);
void HashDestroyTest(hash_t *hash);
void HashTableSizeTest(const hash_t *hash);
void HashBucketSizeTest(const size_t index, const hash_t *hash);
void HashIsEmptyTest(const hash_t *hash);
void HashFindTest(const hash_t *hash, const void *data);
void HashInsertTest(hash_t *hash, void *data);
void HashRemoveTest(hash_t *hash, void *data);
void HashForEachTest(hash_t *hash, hash_do_action_func_t do_action ,void *param);

/************************User function declarations****************************/

static int HashFunction(const void *data1, void *param);
int IsStrEqual(const void *data, void *param);
int IsIntEqual(const void *data, void *param);
int AgePlusOne(void *data, void *param);
static int HashFunctionDictionary(const void *data1, void *param);
int IsWordEqual(const void *data, void *param);
void SpellCheck(hash_t *hash);

/********************************Test Cases************************************/

void TestCase1(void);
void DictionaryTest(void);

/*********************************main*****************************************/

int main(void)
{
    printf("---------------------------------\n");
    TestCase1();
    printf("---------------------------------\n");
    DictionaryTest();
    printf("---------------------------------\n");

    return (0);
}

/************************Test function implemintations*************************/

hash_t *HashCreateTest(hash_table_func_t hash_func,hash_is_match_func_t match_func, void *param, size_t table_size)
{
    hash_t *hash = NULL;

    hash = HashCreate(hash_func, match_func, param, table_size);

    if(NULL == hash)
    {
        printf("Hash Creation was failed.\n");

        return(NULL); 
    }

    printf("Hash Creation was successful.\n");

    return(hash);
}

/**********************************************************************/

void HashSizeTest(const hash_t *hash)
{
    printf("The total no of elements in the hash is: %ld\n", HashSize(hash));
}

/**********************************************************************/

void HashDestroyTest(hash_t *hash)
{
    HashDestroy(hash);
    printf("The Hash table has been destroyed\n");
}

/**********************************************************************/

void HashTableSizeTest(const hash_t *hash)
{
    printf("The Table size is: %ld buckets\n", HashTableSize(hash));
}

/**********************************************************************/

void HashBucketSizeTest(const size_t index, const hash_t *hash)
{
    printf("No of elements in bucket[%ld] is %ld\n"
            , index, HashBucketSize(index, hash));
}

/**********************************************************************/

void HashIsEmptyTest(const hash_t *hash)
{
    printf("Hash is");
    HashIsEmpty(hash) ? printf(" ") : printf(" not ");
    printf("empty\n");
}

/**********************************************************************/

void HashFindTest(const hash_t *hash, const void *data)
{
    if(HashFind(hash, data) == NULL)
    {
        printf("Element was not found\n");
    }

    else
    {
        printf("Element was found\n");
    }
}

/**********************************************************************/

void HashInsertTest(hash_t *hash, void *data)
{
    if(HashInsert(hash, data))
    {
        printf("Insertion was failed.\n");
    }

    else
    {
        printf("Insertion was successful.\n");
    }
}

/**********************************************************************/

void HashRemoveTest(hash_t *hash, void *data)
{
    HashRemove(hash, data);
    printf("Your data was removed\n");
}

/**********************************************************************/

void HashForEachTest(hash_t *hash, hash_do_action_func_t do_action ,void *param)
{
    if(HashForEach(hash, do_action, param))
    {
        printf("The action was not successful for all of the elements.\n");
    }

    printf("The action was successful for all of the elements.\n");
}

/****************************User Functions************************************/

static int HashFunction(const void *data1, void *param)
{
    unsigned long hash = 5381;
    char *str = NULL;
    int c = 0;

    (void)param;

    str = ((worker_t *)data1)->name;

    while ((c = *str++))
    {    
        hash = ((hash << 5) + hash) + c;
    }

    return (hash);
}

/**********************************************************************/

int IsStrEqual(const void *data, void *param)
{
    char *name1 = NULL;
    char *name2 = NULL;

    name1 = ((worker_t *)data)->name;
    name2 = ((worker_t *)param)->name;
    
    if(strcmp(name1,name2) == 0)
    {
        return (1);
    }

    return (0);
}

/**********************************************************************/

int IsWordEqual(const void *data, void *param)
{
    char *name1 = NULL;
    char *name2 = NULL;

    name1 = (char *)data;
    name2 = (char *)param;
    
    if(strcmp(name1,name2) == 0)
    {
        return (1);
    }

    return (0);
}

/**********************************************************************/

static int HashFunctionDictionary(const void *data1, void *param)
{
    unsigned long hash = 5381;
    char *str = NULL;
    int c = 0;

    (void)param;

    str = (char *)data1;

    while ((c = *str++))
    {    
        hash = ((hash << 5) + hash) + c;
    }

    return (hash);
}

/**********************************************************************/

int IsIntEqual(const void *data, void *param)
{
    return (*(int *)data == *(int *)param);
}

/**********************************************************************/

int AgePlusOne(void *data, void *param)
{
    (void)param;

    ((worker_t *)data)->age += 1;

    return(0);
}

/********************************Test Cases************************************/

void TestCase1(void)
{
    worker_t worker1 = {"itay", "Haifa", "123456", 30};
    worker_t worker2 = {"Guy", "Ramat Gan", "987654", 29};
    worker_t worker3 = {"Ori", "Ramat Gan", "456873", 27};

    worker_t *worker1_ptr = &worker1;
    worker_t *worker2_ptr = &worker2;
    worker_t *worker3_ptr = &worker3;

    hash_t *hash = NULL;
    size_t table_size = 15;

    hash = HashCreateTest(HashFunction, IsStrEqual, NULL, table_size);
    HashSizeTest(hash);
    HashTableSizeTest(hash);
    HashBucketSizeTest(0, hash);

    printf("\n");
    HashInsertTest(hash, worker1_ptr);
    HashInsertTest(hash, worker2_ptr);
    HashInsertTest(hash, worker3_ptr);
    /*insertion worker 1 again in order to fail*/
    HashInsertTest(hash, worker1_ptr);
    printf("\n");

    HashSizeTest(hash);
    HashBucketSizeTest(0, hash);

    printf("Ages before ForEach function:\n");
    printf("worker1: %s, age: %d\n", worker1.name, worker1.age);
    printf("worker2: %s, age: %d\n", worker2.name, worker2.age);
    printf("worker3: %s, age: %d\n\n", worker3.name, worker3.age);
    HashForEachTest(hash, AgePlusOne, NULL);
    printf("Ages after ForEach function:\n");
    printf("worker1: %s, age: %d\n", worker1.name, worker1.age);
    printf("worker2: %s, age: %d\n", worker2.name, worker2.age);
    printf("worker3: %s, age: %d\n", worker3.name, worker3.age);

    printf("\n");
    HashRemoveTest(hash, worker2_ptr);
    HashSizeTest(hash);
    printf("\n");
   
    HashDestroyTest(hash);
}

/**********************************************************************/

void DictionaryTest(void)
{
    size_t i = 0;
    hash_t *hash = NULL;
    size_t table_size = 10000;
    FILE *dictionary = NULL;
    char **word_arr = NULL; 
    size_t words_in_dictionary = 102305;

    hash = HashCreateTest(HashFunctionDictionary, IsWordEqual, NULL, table_size);

    dictionary = fopen("/usr/share/dict/words", "r");

    if(dictionary == NULL)
    {
        printf("Open file was failed.\n");
        exit(1);
    }

    word_arr = (char **)malloc(sizeof(char *) * words_in_dictionary);

    if(NULL == word_arr)
    {
        printf("Allocation failed.\n");
        exit (1);
    }

    for (i = 0; i < words_in_dictionary; ++i)
    {
        word_arr[i] = (char *)malloc(sizeof(char) * 50);

        if (NULL == word_arr[i])
        {
            printf("Allocation failed.\n");
            exit(1);
        }

        fscanf(dictionary, "%s", word_arr[i]);
        HashInsert(hash, word_arr[i]);    
    }
    
    HashSizeTest(hash);

    SpellCheck(hash);

    for(i = 0; i < words_in_dictionary; ++i)
    {
        free(word_arr[i]);
        word_arr[i] = NULL;
    }

    free (word_arr);
    word_arr = NULL;
    fclose(dictionary);

    HashDestroyTest(hash);
}

/**********************************************************************/

void SpellCheck(hash_t *hash)
{
    char word[20] = {0};

    printf("Please enter a word, '0' to exit:\n");
    scanf("%s", word);
    printf("\n");

    while(!(word[0] == '0' && word[1] == '\0'))
    {
        if(HashFind(hash, word) == NULL)
        {
            printf("\"%s\" is not a word\n", word);
        }

        else
        {
            printf("\"%s\" is a word\n", word);
        }

        printf("\nPlease enter a word:\n");
        scanf("%s", word);
        printf("\n");
    }
}

/**********************************************************************/
