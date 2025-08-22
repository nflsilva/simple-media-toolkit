#include "smt/smt.h"

#include "smt/window.h"
#include "smt/render.h"

static SMT_Window window;
SMT_Renderer renderer;
static int smtErrorMessageSize = 0;
char *smtErrorMessage = NULL;

char* smtGetErrorMessage() 
{
    return smtErrorMessage;
}

void smtSetErrorMessage(const char* message) 
{
    int newMessageSize = strlen(message);
    if(newMessageSize >= smtErrorMessageSize) 
    {
        if(smtErrorMessageSize != 0) 
            free(smtErrorMessage);

        smtErrorMessage = (char*)malloc(sizeof(char) * newMessageSize + 1);
    }
    smtErrorMessageSize = newMessageSize;
    strcpy(smtErrorMessage, message);
    printf("smt_error: %s\n", smtErrorMessage);
}

int smtInit(int width, int height, const char* title) {

    smtWindowOpen(width, height, title, &window);
    smtRendererInitialise(&window, &renderer);

    return SMT_SUCCESS;
}

void smtDestroy() {
    smtRendererCleanup(&renderer);
    smtWindowCleanup(&window);
}

int smtShouldClose() {
    return smtWindowShouldClose(&window);
}

void smtUpdate() {
    smtRendererDraw(&renderer);
    smtWindowUpdate(&window);
}

void smtDrawSprite(SMT_Sprite_t* sprite) {
    smtSpriteAddToBatch(&renderer.spriteBatch, sprite);
}