#include "smt/batch.h"

#include <string.h>
#include "smt/utils.h"

void smtBatchAttributeCleanup(SMT_BatchAttribute_t* attribute)
{
    if(!attribute) return;
    glDeleteBuffers(1, &attribute->glVBO);
    free(attribute->buffer);
}

void smtBatchInitialise(unsigned int maxEntities, unsigned int nVertexPerEntity, unsigned int type, SMT_Batch_t* batch)
{
    assert(batch);
    memset(batch, 0, sizeof(SMT_Batch_t));
    glGenVertexArrays(1, &batch->glVAO);
    batch->maxEntities = maxEntities;
    batch->nVertexPerEntity = nVertexPerEntity;
    batch->type = type;
}

void smtBatchCleanup(SMT_Batch_t* batch)
{
    if(!batch) return;
    glDeleteVertexArrays(1, &batch->glVAO);

    for(unsigned int i = 0; i < batch->nAttributes; i++) {
        smtBatchAttributeCleanup(&batch->attributes[i]);
    }

    memset(batch, 0, sizeof(SMT_Batch_t));
}

void smtBatchDraw(SMT_Batch_t* batch) {
    assert(batch);

    for(unsigned int  i = 0; i < batch->nAttributes; i++) {
        SMT_BatchAttribute_t* attribute = &batch->attributes[i];
        assert(attribute);

        glEnableVertexAttribArray(attribute->index); 
        glBindBuffer(GL_ARRAY_BUFFER, attribute->glVBO);
        glVertexAttribPointer(attribute->index, attribute->size, attribute->type, GL_FALSE, 0, (void*)0);
        glVertexAttribDivisor(attribute->index, attribute->divisor);
        glBufferData(GL_ARRAY_BUFFER, attribute->bufferLength * sizeof(attribute->type), attribute->buffer, GL_DYNAMIC_DRAW);
    }

    for (unsigned int i = 0; i < batch->nTextures; i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, batch->textures[i]);
    }

    glBindVertexArray(batch->glVAO);
    glDrawArrays(batch->type, 0, batch->nEntities * batch->nVertexPerEntity);
        
    smtBatchUnbind(batch);
    smtBatchResetBuffers(batch);
}

void smtBatchUnbind(SMT_Batch_t* batch) {
    assert(batch);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    for(unsigned int  i = 0; i < batch->nAttributes; i++) {
        glDisableVertexAttribArray(batch->attributes[i].index);; 
    }
}

void smtBatchResetBuffers(SMT_Batch_t* batch) {
    assert(batch);

    for(unsigned int  i = 0; i < batch->nAttributes; i++) {
        batch->attributes[i].bufferLength = 0; 
    }

    batch->nEntities = 0;
    batch->nTextures = 0;
}

static void smtBatchAttributeInitialise(SMT_Batch_t* batch, unsigned int index, unsigned int size, int type, int divisor, SMT_BatchAttribute_t* attribute)
{
    assert(attribute);
    glBindVertexArray(batch->glVAO);

    GLuint glVBO;
    glGenBuffers(1, &glVBO);
    glBindBuffer(GL_ARRAY_BUFFER, glVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(type) * batch->maxEntities, NULL, GL_DYNAMIC_DRAW);
    glVertexAttribIPointer(index, size, type, GL_FALSE, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    attribute->glVBO = glVBO;
    attribute->index = index;
    attribute->size = size;
    attribute->type = type;
    attribute->divisor = divisor;
    attribute->bufferLength = 0;
    attribute->buffer = malloc(sizeof(type) * batch->maxEntities * batch->nVertexPerEntity * size);
}

int smtBatchAddAttribute(SMT_Batch_t* batch, unsigned int index, unsigned int size, int type, int divisor)
{
    glBindVertexArray(batch->glVAO);
    smtBatchAttributeInitialise(batch, index, size, type, divisor, &batch->attributes[batch->nAttributes]);
    batch->nAttributes++;
    return SMT_SUCCESS;
}

void smtBatchAddAttributeData(SMT_Batch_t* batch, unsigned int index, void* data)
{
    assert(batch);
    if(index > SMT_BATCH_MAX_ATTRIBUTES || batch->nAttributes == 0) return;

    SMT_BatchAttribute_t* attribute = NULL;
    for(unsigned int  i = 0; i < batch->nAttributes; i++) {
        attribute = &batch->attributes[i];
        if(attribute->index == index) break;
    }

    memcpy(attribute->buffer + sizeof(attribute->type) * attribute->bufferLength, data, sizeof(attribute->type) * batch->nVertexPerEntity * attribute->size);
    attribute->bufferLength += batch->nVertexPerEntity * attribute->size;
}