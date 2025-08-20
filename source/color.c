#include "smt/color.h"

#include <assert.h>
#include <cutil/math.h>

void smtColorInitialise(float r, float g, float b, float a, SMT_Color* color)
{
    assert(color);
    color->red = cutilMathClipf(r, 0.0, 1.0);
    color->blue = cutilMathClipf(g, 0.0, 1.0);
    color->green = cutilMathClipf(b, 0.0, 1.0);
    color->alpha = cutilMathClipf(a, 0.0, 1.0);
}
