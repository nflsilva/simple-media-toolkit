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

/*!
 * Represents the current renderer context
 * @param spriteShader The selected shader for sprites
 * @param uniformLocations The map which stores the location for each uniform.
 */
typedef struct SMT_Renderer {
    SMT_Shader* spriteShader;
    SMT_Batch* spriteBatch;

} SMT_Renderer;

SMT_Renderer* smtRendererInit(SMT_Window* window);

void smtRendererDestroy();

void smtRendererDraw();

void smtRenderSprite(SMT_Renderer* renderer, SMT_Sprite* sprite);

#endif