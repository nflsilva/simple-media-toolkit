#ifndef _SMT_RENDER_H
#define _SMT_RENDER_H

#include "cvec/vec2.h"
#include "smt/color.h"
#include "smt/shader.h"

typedef SMTColor Color;
typedef CVECVec2f Vec2f;

typedef struct SMTShape {
    int type;
    Vec2f* point0;
    Vec2f* point1;
    Color* color;
} SMTShape;

/*!
 * Represents the current renderer context
 * @param shapeShader The selected shader for shapes
 * @param shaderList A list of shader codes which compose this shader.
 * @param uniformLocations The map which stores the location for each uniform.
 */
typedef struct SMTRenderer {
    SMTShader* shapeShader;
    SMTShape* shapes;
    int nShapes;
} SMTRenderer;

SMTRenderer* smtRendererInit();

void smtRendererDestroy();

void smtRendererDraw();

void smtRenderRectangle(Vec2f* topLeft, Vec2f* bottomRight, Color* fillColor);

#endif