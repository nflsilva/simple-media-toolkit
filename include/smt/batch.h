#ifndef _SMT_BATCH_H
#define _SMT_BATCH_H

#include <stdlib.h>

#include "cutil/hashTable.h"

/*!
 * 
 */
typedef struct SMT_BatchAttribute {
    int glVBO;
    void* data;
} SMT_BatchAttribute;

/*!
 * Represents a batch of entities to render
 */
typedef struct SMT_Batch {
    int glVAO;
    SMT_BatchAttribute** attributes;
    SMT_BatchAttribute* indexBuffer;
} SMT_Batch;

/*!
 * Creates a new entities batch.
 */
void smtBatchCreate(const unsigned int maxEntities);

void smtBatchDestroy(SMT_Batch* batch);

void smtBatchAddAttributei();

void smtBatchAddAttributef();

#endif