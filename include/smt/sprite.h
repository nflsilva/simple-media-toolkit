#include <glad/glad.h>

#include "cvec/vec2.h"
#include "smt/color.h"
#include "smt/shader.h"

typedef struct SMT_Sprite {
    GLuint textureId;
} SMT_Sprite;

SMT_Sprite* smtSpriteCreateFromFile(const char* path);

void smtSpriteDestroy(SMT_Sprite* sprite);

/*!
 * Creates a shader for sprites.
 * @returns A pointer to the newly created shader. `NULL` if an error occurred.
 */
SMT_Shader* smtShaderCreateSpiteShader();