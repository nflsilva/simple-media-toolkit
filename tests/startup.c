#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "smt/smt.h"
#include "smt/sprite.h"

int main() {
    
    assert(smtInit(200, 200, "startupTest") == SMT_SUCCESS);

    
    SMT_Sprite_t sprite0, sprite1;
    smtSpriteInitialiseFromFile("../../tests/assets/fx/sample.png", &sprite0);
    smtSpriteInitialiseFromFile("../../tests/assets/fx/sample2.png", &sprite1);

    SMT_Rectangle_t sprite0Rect, sprite1Rect;
    SMT_Rectangle_t sprite1SubRect;
    smtRectangleInitialise(0.0f, 0.0f, 32.0f, 32.0f, &sprite0Rect);
    smtRectangleInitialise(64.0f, 64.0f, 32.0f, 32.0f, &sprite1Rect);
    smtRectangleInitialise(0.0f, 0.0f, 32.0f, 32.0f, &sprite1SubRect);

    while(!smtShouldClose()) {
        smtDrawSprite(&sprite0, &sprite0Rect);
        smtDrawSubSprite(&sprite1, &sprite1Rect, &sprite1SubRect);
        smtUpdate();
    }

    smtSpriteCleanup(&sprite0);
    smtSpriteCleanup(&sprite1);
    smtDestroy();


    exit(EXIT_SUCCESS);
}