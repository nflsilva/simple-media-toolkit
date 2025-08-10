#ifndef _SMT_BATCH_H
#define _SMT_BATCH_H

#include <glad/glad.h>
#include <stdlib.h>

#include "smt/smt.h"
#include "cutil/list.h"

#define SMT_BATCH_MAX_ATTRIBUTES 20
#define SMT_BATCH_MAX_ENTITIES 2000

/*!
 * 
 */
typedef struct SMT_BatchAttribute {
    GLuint glVBO;
    unsigned int index, size;
    void* buffer;
    unsigned int bufferSize;
} SMT_BatchAttribute;

/*!
 * Represents a batch of entities to render
 */
typedef struct SMT_Batch {
    GLuint glVAO;
    unsigned int nEntities;
    unsigned int nVertexPerEntity;
    unsigned int maxEntities;
    CUTILList* attributes;

    SMT_BatchAttribute* indexBuffer;
} SMT_Batch;

SMT_BatchAttribute* SMT_BatchAttributeCreate(SMT_Batch* batch, unsigned int index, unsigned int size, void* buffer, int type);

void SMT_BatchAttributeDestroy(SMT_BatchAttribute* attribute);

/*!
 * Creates a new entities batch.
 */
SMT_Batch* SMT_BatchCreate(unsigned int maxEntities, unsigned int nVertexPerEntity);

void SMT_BatchDestroy(SMT_Batch* batch);

void SMT_BatchAddAttributei(SMT_Batch* batch, unsigned int index, unsigned int size);

void SMT_BatchAddAttributef(SMT_Batch* batch, unsigned int index, unsigned int size);

void SMT_BatchAddAttributeiData(SMT_Batch* batch, unsigned int index, int* data, unsigned int size);

void SMT_BatchAddAttributefData(SMT_Batch* batch, unsigned int index, float* data, unsigned int size);

#endif