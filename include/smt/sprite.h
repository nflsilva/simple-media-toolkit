#ifndef _SMT_SPRITE_H
#define _SMT_SPRITE_H

#include <glad/glad.h>

#include <cvec/vec2.h>

#include "smt/rectangle.h"

struct SMT_Shader;
struct SMT_Batch;
struct SMT_Renderer;

typedef struct SMT_Sprite {
    GLuint textureId;
    int width, height;
} SMT_Sprite_t;

void smtSpriteInitialiseFromFile(const char* path, SMT_Sprite_t* sprite);

void smtSpriteCleanup(SMT_Sprite_t* sprite);

/*!
 * Creates a shader for sprites.
 * @returns A pointer to the newly created shader. `NULL` if an error occurred.
 */
void smtSpriteInitialiseSpiteShader(struct SMT_Shader* shader);

void smtSpriteInitialiseSpriteBatch(struct SMT_Batch* batch);

void smtSpriteAddToBatch(struct SMT_Batch* batch, SMT_Sprite_t* sprite, SMT_Rectangle_t* targetRect, SMT_Rectangle_t* subRect);

void smtSpriteDrawBatches(struct SMT_Renderer* renderer);

#endif