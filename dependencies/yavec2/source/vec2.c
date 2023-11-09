#include "vec2.h"

void vec2_add(Vec2* vec0, Vec2* vec1){
    vec0->x += vec1->x;
    vec0->y += vec1->y;
};

void vec2_mul(Vec2* vec0, Vec2* vec1){
    vec0->x *= vec1->x;
    vec0->y *= vec1->y;
};