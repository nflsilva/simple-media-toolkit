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

    while(!smtShouldClose()) {
        smtDrawSprite(&sprite0);
        smtDrawSprite(&sprite1);
        smtUpdate();
    }

    smtSpriteCleanup(&sprite0);
    smtSpriteCleanup(&sprite1);
    smtDestroy();


    exit(EXIT_SUCCESS);
}