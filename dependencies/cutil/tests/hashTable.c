#include <stdlib.h>
#include <assert.h>

#include "cutil/hashTable.h"

#define LIST_SIZE 10

int main() 
{
    // setup elements array
    int elements[LIST_SIZE];
    for(int i = 0; i < LIST_SIZE; i++) 
        elements[i] = i;

    // setup list
    CUTILHashTable* table = cutilHashTableCreate();
    cutilHashTableAddElement(table, "abc", &elements[0]);
    cutilHashTableAddElement(table, "bca", &elements[1]);
    cutilHashTableAddElement(table, "cab", &elements[2]);

    // test insert
    assert(*(int*)cutilHashTableGetElement(table, "bca") == elements[1]);
    assert(*(int*)cutilHashTableGetElement(table, "cab") == elements[2]);
    assert(cutilHashTableGetElement(table, "aaa") == NULL);

    // test update
    cutilHashTableAddElement(table, "cab", &elements[0]);
    assert(*(int*)cutilHashTableGetElement(table, "cab") == elements[0]);

    // test remove
    assert(*(int*)cutilHashTableRemoveElement(table, "abc") == elements[0]);
    assert(cutilHashTableRemoveElement(table, "abc") == NULL);

    exit(EXIT_SUCCESS);
}