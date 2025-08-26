#include "smt/rectangle.h"

#include <assert.h>

void smtRectangleInitialise(float x, float y, float w, float h, SMT_Rectangle_t* rectangle)
{
    assert(rectangle);
    rectangle->x = x;
    rectangle->y = y;
    rectangle->width = w;
    rectangle->height = h;
}
