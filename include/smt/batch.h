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
typedef struct SMTBatchAttribute {
    GLuint glVBO;
    unsigned int index, size;
    void* buffer;
    unsigned int bufferSize;
} SMTBatchAttribute;

/*!
 * Represents a batch of entities to render
 */
typedef struct SMTBatch {
    GLuint glVAO;
    unsigned int nEntities;
    unsigned int nVertexPerEntity;
    unsigned int maxEntities;
    CUTILList* attributes;

    SMTBatchAttribute* indexBuffer;
} SMTBatch;

SMTBatchAttribute* smtBatchAttributeCreate(SMTBatch* batch, unsigned int index, unsigned int size, void* buffer, int type);

void smtBatchAttributeDestroy(SMTBatchAttribute* attribute);

/*!
 * Creates a new entities batch.
 */
SMTBatch* smtBatchCreate(unsigned int maxEntities, unsigned int nVertexPerEntity);

void smtBatchDestroy(SMTBatch* batch);

void smtBatchAddAttributei(SMTBatch* batch, unsigned int index, unsigned int size);

void smtBatchAddAttributef(SMTBatch* batch, unsigned int index, unsigned int size);

void smtBatchAddAttributeiData(SMTBatch* batch, unsigned int index, int* data, unsigned int size);

void smtBatchAddAttributefData(SMTBatch* batch, unsigned int index, float* data, unsigned int size);

#endif