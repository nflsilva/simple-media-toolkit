#include "smt/render.h"

#include <glad/glad.h>

void smtRendererInitialise(SMT_Window* window, SMT_Renderer* renderer)
{
    assert(renderer);
    glfwMakeContextCurrent(window->glfwWindow);
    gladLoadGL();
    glfwSwapInterval(1);

    smtSpriteInitialiseSpiteShader(&renderer->spriteShader);
    smtSpriteInitialiseSpriteBatch(&renderer->spriteBatch);
}

void smtRendererCleanup(SMT_Renderer* renderer)
{
    assert(renderer);
    smtShaderCleanup(&renderer->spriteShader);
    smtBatchCleanup(&renderer->spriteBatch);
}

void smtRendererDraw(SMT_Renderer* renderer)
{
    assert(renderer);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    smtShaderBind(&renderer->spriteShader);
    smtBatchDraw(&renderer->spriteBatch);
}