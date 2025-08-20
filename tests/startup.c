#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "smt/smt.h"
#include "smt/sprite.h"

int main() {
    
    assert(smtInit(200, 200, "startupTest") == SMT_SUCCESS);

    
    SMT_Sprite_t sprite;
    smtSpriteInitialiseFromFile("../../tests/assets/fx/sample.png", &sprite);

    while(!smtShouldClose()) {
        smtDrawSprite(&sprite);
        smtDrawSprite(&sprite);
        smtUpdate();
    }

    smtSpriteCleanup(&sprite);
    smtDestroy();


    exit(EXIT_SUCCESS);
}