#ifndef _SMT_SPRITE_H
#define _SMT_SPRITE_H

#include <glad/glad.h>

#include "cvec/vec2.h"

struct SMT_Shader;
struct SMT_Batch;

typedef struct SMT_Sprite {
    GLuint textureId;
} SMT_Sprite_t;

void smtSpriteInitialiseFromFile(const char* path, SMT_Sprite_t* sprite);

void smtSpriteCleanup(SMT_Sprite_t* sprite);

/*!
 * Creates a shader for sprites.
 * @returns A pointer to the newly created shader. `NULL` if an error occurred.
 */
void smtSpriteInitialiseSpiteShader(struct SMT_Shader* shader);

void smtSpriteInitialiseSpriteBatch(struct SMT_Batch* batch);

#endif