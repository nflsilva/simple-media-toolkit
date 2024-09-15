#ifndef _SMT_RENDER_H
#define _SMT_RENDER_H

#include "cvec/vec2.h"
#include "smt/color.h"
#include "smt/shader.h"
#include "smt/sprite.h"

typedef SMT_Color Color;
typedef CVECVec2f Vec2f;

/*!
 * Represents the current renderer context
 * @param spriteShader The selected shader for sprites
 * @param sprites A list of sprites to render
 * @param uniformLocations The map which stores the location for each uniform.
 */
typedef struct SMT_Renderer {
    SMT_Shader spriteShader;
    SMT_Sprite sprite;
    int nShapes;
} SMT_Renderer;

SMT_Renderer* smtRendererInit();

void smtRendererDestroy();

void smtRendererDraw();

void smtRenderSprite(SMT_Sprite* sprite);

#endif