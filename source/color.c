#include "smt/color.h"

#include "cutil/math.h"

SMT_Color* smtColorCreate(float r, float g, float b, float a)
{
    SMT_Color* color = (SMT_Color*)malloc(sizeof(SMT_Color));
    color->red = cutilMathClipf(r, 0.0, 1.0);
    color->blue = cutilMathClipf(g, 0.0, 1.0);
    color->green = cutilMathClipf(b, 0.0, 1.0);
    color->alpha = cutilMathClipf(a, 0.0, 1.0);
    return color;
}
