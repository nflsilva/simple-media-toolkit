#ifndef _SMT_RENDER_H
#define _SMT_RENDER_H

#include "cvec/vec2.h"
#include "smt/batch.h"
#include "smt/color.h"
#include "smt/shader.h"
#include "smt/sprite.h"
#include "smt/window.h"

typedef SMT_Color Color;
typedef CVECVec2f Vec2f;

struct SMT_Shader;

/*!
 * Represents the current renderer context
 * @param spriteShader The selected shader for sprites
 * @param uniformLocations The map which stores the location for each uniform.
 */
typedef struct SMT_Renderer {
    SMT_Shader_t spriteShader;
    SMT_Batch_t spriteBatch;
    CUTILHashTable_t filePerTexture;

} SMT_Renderer;

void smtRendererInitialise(SMT_Window* window, SMT_Renderer* renderer);

void smtRendererCleanup(SMT_Renderer* renderer);

void smtRendererDraw(SMT_Renderer* renderer);

#endif