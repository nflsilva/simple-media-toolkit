#include "smt/batch.h"

#include "smt/utils.h"

SMT_BatchAttribute* SMT_BatchAttributeCreate(SMT_Batch* batch, unsigned int index, unsigned int size, void* buffer, int type)
{
    glBindVertexArray(batch->glVAO);

    GLuint glVBO;
    glGenBuffers(1, &glVBO);
    glBindBuffer(GL_ARRAY_BUFFER, glVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(int) * batch->maxEntities, buffer, GL_DYNAMIC_DRAW);
    glVertexAttribIPointer(index, size, type, GL_FALSE, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    SMT_BatchAttribute* attribute = (SMT_BatchAttribute*)malloc(sizeof(SMT_BatchAttribute));
    attribute->glVBO = glVBO;
    attribute->index = index;
    attribute->size = size;
    attribute->buffer = buffer;
    attribute->bufferSize = 0;

    return attribute;
}

void SMT_BatchAttributeDestroy(SMT_BatchAttribute* attribute)
{
    if(!attribute) return;
    glDeleteBuffers(1, &attribute->glVBO);
    free(attribute->buffer);
    free(attribute);
}

SMT_Batch* SMT_BatchCreate(unsigned int maxEntities, unsigned int nVertexPerEntity)
{
    SMT_Batch* batch = (SMT_Batch*)malloc(sizeof(SMT_Batch));
    glGenVertexArrays(1, &batch->glVAO);
    batch->nEntities = 0;
    batch->maxEntities = maxEntities;
    batch->nVertexPerEntity = nVertexPerEntity;
    batch->attributes = cutilListCreate();

    // TODO: will we need this? 🤔
    batch->indexBuffer = NULL;

    return batch;
}

void SMT_BatchDestroy(SMT_Batch* batch)
{
    if(!batch) return;
    glDeleteVertexArrays(1, &batch->glVAO);

    SMT_BatchAttribute* attribute = NULL;
    do {
        attribute = cutilListPopElement(batch->attributes);
        if(attribute == NULL) break;
        SMT_BatchAttributeDestroy(attribute);
    } while (attribute != NULL);
    free(batch->attributes);
    free(batch);
}

int SMT_BatchAddAttribute(SMT_Batch* batch, unsigned int index, unsigned int size, void* buffer, int type)
{
    glBindVertexArray(batch->glVAO);
    SMT_BatchAttribute* attribute = SMT_BatchAttributeCreate(batch, index, size, buffer, type);
    if(!attribute) return SMT_FAILURE;
    cutilListAppendElement(batch->attributes, attribute);
    return SMT_SUCCESS;
}

void SMT_BatchAddAttributei(SMT_Batch* batch, unsigned int index, unsigned int size)
{
    if(!batch) return;
    int* buffer = (int*)malloc(sizeof(int) * batch->maxEntities * batch->nVertexPerEntity * size);
    if(!SMT_BatchAddAttribute(batch, index, size, buffer, GL_INT))
        free(buffer);
}

void SMT_BatchAddAttributef(SMT_Batch* batch, unsigned int index, unsigned int size)
{
    if(!batch) return;
    float* buffer = (float*)malloc(sizeof(float) * batch->maxEntities * batch->nVertexPerEntity * size);
    if(!SMT_BatchAddAttribute(batch, index, size, buffer, GL_FLOAT))
        free(buffer);
}

void SMT_BatchAddAttributeiData(SMT_Batch* batch, unsigned int index, int* data, unsigned int size)
{
    ASSERT_MSG(0, "batch.c SMT_BatchAddAttributeiData not implemented");
}

void SMT_BatchAddAttributefData(SMT_Batch* batch, unsigned int index, float* data, unsigned int size)
{
    if(!batch || index > SMT_BATCH_MAX_ATTRIBUTES || batch->attributes->size == 0) return;

    CUTILListNode* node = batch->attributes->head;

    do {
        if(((SMT_BatchAttribute*)(node->data))->index == index) break;
        node = node->next;
    } while (node != NULL);

    if(node == NULL) return;

    SMT_BatchAttribute* attribute = (SMT_BatchAttribute*)node->data;

    memcpy(&((float*)attribute->buffer)[attribute->bufferSize], data, sizeof(float) * size * attribute->size);
    attribute->bufferSize += size * attribute->size;
}