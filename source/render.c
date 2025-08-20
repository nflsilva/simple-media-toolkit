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

void smtRenderDrawSprite(SMT_Renderer* renderer, SMT_Sprite_t* sprite)
{
    assert(renderer);
    float triangle_vertices[] = {
        //   X      Y     Z
         0.0f,  0.5f, 0.0f,             // Top
        -0.5f, -0.5f, 0.0f,             // Bottom left
         0.5f, -0.5f, 0.0f              // Bottom right
    };

    float triangle_color[] = {
        //   R      G     B     A
         0.0f,  0.0f, 1.0f, 1.0f,       // Top
         0.0f,  1.0f, 0.0f, 1.0f,       // Bottom left
         1.0f,  0.0f, 0.0f, 1.0f        // Bottom right
    };

    smtBatchAddAttributeData(&renderer->spriteBatch, 0, triangle_vertices, 3);
    smtBatchAddAttributeData(&renderer->spriteBatch, 1, triangle_color, 4);
}
