#ifndef _HASHTABLE_H
#define _HASHTABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cutil/list.h"

#define _CUTIL_TABLE_SIZE 50000

typedef struct CUTILHashTableBucketChainNode {
    const char* key;
    void* data;
} CUTILHashTableBucketChainNode;

typedef struct CUTILHashTableBucket {
    const char* key;
    void* data;
    CUTILList* chain;
} CUTILHashTableBucket;

typedef struct CUTILHashTable {
    CUTILHashTableBucket* buckets;
} CUTILHashTable;

/*!
 * Creates a new empty hash table.
 * @returns A pointer to a new hash table.
 */
CUTILHashTable* cutilHashTableCreate();

/*!
 * Destroy a hash table and its buckets.
 * @param hashTable A pointer to the hash table.
 * @param cleanData Set to anything other than `0` to free all the stored data. `0` otherwise.
 */
void cutilHashTableDestroy(CUTILHashTable* hashTable, int cleanData);

/*!
 * Adds new element to the list.
 * @param hashTable A pointer to the hash table.
 * @param key A hash table key to store the data.
 * @param data A pointer to the data to store.
 */
void cutilHashTableAddElement(CUTILHashTable* hashTable, const char* key, void* data);

/*!
 * Gets an element from the hash table.
 * @param hashTable A pointer to the hash table.
 * @param key A key for the element to get.
 * @return The data from element. `NULL` if no element exists for given key.
 */
void* cutilHashTableGetElement(CUTILHashTable* hashTable, const char* key);

/*!
 * Removes an element from the hash table.
 * @param hashTable A pointer to the hash table.
 * @param key A key for the element to get.
 * @return The data from element. `NULL` if no element exists for given key.
 */
void* cutilHashTableRemoveElement(CUTILHashTable* hashTable, const char* key);

#endif