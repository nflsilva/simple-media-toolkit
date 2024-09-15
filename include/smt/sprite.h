#include <glad/glad.h>

#include "cvec/vec2.h"
#include "smt/color.h"

typedef struct SMT_Sprite {
    GLuint textureId;
} SMT_Sprite;

SMT_Sprite* smtSpriteCreateFromFile(const char* path);

void smtSpriteDestroy(SMT_Sprite* sprite);