#ifndef _SMT_BATCH_H
#define _SMT_BATCH_H

#include <cutil/list.h>
#include <glad/glad.h>
#include <stdlib.h>

#include "smt/utils.h"

#define SMT_BATCH_MAX_ATTRIBUTES 20
#define SMT_BATCH_MAX_ENTITIES 2000
#define SMT_BATCH_MAX_TEXTURES 16

/*!
 * 
 */
typedef struct SMT_BatchAttribute {
    GLuint glVBO;
    unsigned int index, size, type;
    void* buffer;
    unsigned int bufferLength;
} SMT_BatchAttribute_t;

/*!
 * Represents a batch of entities to render
 */
typedef struct SMT_Batch {
    GLuint glVAO;
    unsigned int nEntities, nVertexPerEntity, maxEntities, type;
    SMT_BatchAttribute_t attributes[SMT_BATCH_MAX_ATTRIBUTES];
    GLuint textures[SMT_BATCH_MAX_TEXTURES];
    unsigned int nAttributes, nTextures;
} SMT_Batch_t;

/*!
 * Creates a new entities batch.
 */
void smtBatchInitialise(unsigned int maxEntities, unsigned int nVertexPerEntity, unsigned int type, SMT_Batch_t* batch);

void smtBatchCleanup(SMT_Batch_t* batch);

void smtBatchDraw(SMT_Batch_t* batch);

void smtBatchUnbind(SMT_Batch_t* batch);

void smtBatchResetBuffers(SMT_Batch_t* batch);

int smtBatchAddAttribute(SMT_Batch_t* batch, unsigned int index, unsigned int size, int type);

void smtBatchAddAttributeData(SMT_Batch_t* batch, unsigned int index, void* data);

#endif