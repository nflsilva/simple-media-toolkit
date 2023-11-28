#ifndef _SMT_RENDER_H
#define _SMT_RENDER_H

#include "cvec/vec2.h"
#include "smt/color.h"
#include "smt/shader.h"

typedef SMT_Color Color;
typedef CVEC_Vec2f Vec2f;

typedef struct SMT_Shape {
    int type;
    Vec2f* point0;
    Vec2f* point1;
    Color* color;
} SMT_Shape;

/*!
 * Represents the current renderer context
 * @param shapeShader The selected shader for shapes
 * @param shaderList A list of shader codes which compose this shader.
 * @param uniformLocations The map which stores the location for each uniform.
 */
typedef struct SMT_Renderer {
    SMT_Shader* shapeShader;
    SMT_Shape* shapes;
    int nShapes;
} SMT_Renderer;

SMT_Renderer* smtRendererInit();

void smtRendererDestroy();

void smtRendererDraw();

void smtRenderRectangle(Vec2f* topLeft, Vec2f* bottomRight, Color* fillColor);

#endif