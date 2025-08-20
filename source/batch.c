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
    glGenVertexArrays(1, &batch->glVAO);
    batch->nEntities = 0;
    batch->maxEntities = maxEntities;
    batch->nVertexPerEntity = nVertexPerEntity;
    batch->type = type;
    cutilListInitialise(&batch->attributes, sizeof(SMT_BatchAttribute_t));

    // TODO: will we need this? 🤔
    batch->indexBuffer = NULL;
}

void smtBatchCleanup(SMT_Batch_t* batch)
{
    if(!batch) return;
    glDeleteVertexArrays(1, &batch->glVAO);

    CUTILListNode_t *node = batch->attributes.head;
    while(node) {
        smtBatchAttributeCleanup(node->data);
        node = node->next;
    }
    cutilListCleanup(&batch->attributes);
    memset(batch, 0, sizeof(SMT_Batch_t));
}

void smtBatchDraw(SMT_Batch_t* batch) {
    assert(batch);
    CUTILListNode_t *node = batch->attributes.head;
    while(node) {
        SMT_BatchAttribute_t* attribute = node->data;
        assert(attribute);

        glBindBuffer(GL_ARRAY_BUFFER, attribute->glVBO);
        glBufferData(GL_ARRAY_BUFFER, attribute->bufferLength * sizeof(attribute->type), attribute->buffer, GL_DYNAMIC_DRAW);
        glVertexAttribPointer(attribute->index, attribute->size, attribute->type, GL_FALSE, 0, (void*)0);
        glEnableVertexAttribArray(attribute->index);

        node = node->next;
    }
    glBindVertexArray(batch->glVAO);
    glDrawArrays(batch->type, 0, batch->nEntities * batch->nVertexPerEntity);

    //smtBatchUnbind(batch);
    smtBatchResetBuffers(batch);
}

void smtBatchUnbind(SMT_Batch_t* batch) {
    assert(batch);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    CUTILListNode_t *node = batch->attributes.head;
    while(node) {
        SMT_BatchAttribute_t* attribute = node->data;
        glDisableVertexAttribArray(attribute->index);
        node = node->next;
    }
}

void smtBatchResetBuffers(SMT_Batch_t* batch) {
    assert(batch);
    CUTILListNode_t *node = batch->attributes.head;
    while(node) {
        SMT_BatchAttribute_t* attribute = node->data;
        attribute->bufferLength = 0;
        node = node->next;
    }
    batch->nEntities = 0;
}

static void smtBatchAttributeInitialise(SMT_Batch_t* batch, unsigned int index, unsigned int size, int type, SMT_BatchAttribute_t* attribute)
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
    attribute->bufferLength = 0;
    attribute->buffer = malloc(sizeof(type) * batch->maxEntities * batch->nVertexPerEntity * size);
}

int smtBatchAddAttribute(SMT_Batch_t* batch, unsigned int index, unsigned int size, int type)
{
    glBindVertexArray(batch->glVAO);

    SMT_BatchAttribute_t* attribute = (SMT_BatchAttribute_t*)malloc(sizeof(SMT_BatchAttribute_t));
    smtBatchAttributeInitialise(batch, index, size, type, attribute);
    if(!attribute) return SMT_FAILURE;

    cutilListAppend(&batch->attributes, attribute);
    return SMT_SUCCESS;
}

void smtBatchAddAttributeData(SMT_Batch_t* batch, unsigned int index, void* data)
{
    if(!batch || index > SMT_BATCH_MAX_ATTRIBUTES || batch->attributes.size == 0) return;

    CUTILListNode_t* node = batch->attributes.head;
    while (node != NULL) {
        if(((SMT_BatchAttribute_t*)(node->data))->index == index) break;
        node = node->next;
    }

    assert(node);
    SMT_BatchAttribute_t* attribute = (SMT_BatchAttribute_t*)node->data;

    memcpy(attribute->buffer + sizeof(attribute->type) * attribute->bufferLength, data, sizeof(attribute->type) * batch->nVertexPerEntity * attribute->size);
    attribute->bufferLength += batch->nVertexPerEntity * attribute->size;
}