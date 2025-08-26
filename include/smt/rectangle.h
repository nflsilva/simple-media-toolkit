#ifndef _SMT_RECTANGLE_H
#define _SMT_RECTANGLE_H

#include <cvec/vec2.h>

typedef struct SMT_Rectangle {
    float x, y, width, height;
} SMT_Rectangle_t;

void smtRectangleInitialise(float x, float y, float w, float h, SMT_Rectangle_t* rectangle);

#endif