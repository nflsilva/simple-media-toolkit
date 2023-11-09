#pragma once

typedef struct Vec2 {
    int x;
    int y;
} Vec2;

void vec2_add(Vec2* vec0, Vec2* vec1);
void vec2_mul(Vec2* vec0, Vec2* vec1);