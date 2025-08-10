#include "smt/smt.h"

#include "smt/window.h"
#include "smt/render.h"

static SMT_Window* window = NULL;
static SMT_Renderer* renderer = NULL;
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
    window = smtWindowOpen(width, height, title);
    renderer = smtRendererInit(window);

    return SMT_SUCCESS;
}

int smtDestroy() {
    smtRendererDestroy();
    smtWindowDestroy(window);
}