#include "smt/render.h"

#include <glad/glad.h>

SMT_Renderer* smtRendererInit(SMT_Window* window)
{
    glfwMakeContextCurrent(window->glfwWindow);
    gladLoadGL();
    glfwSwapInterval(1);

    return NULL;
}

void smtRendererDestroy()
{

}

void smtRendererDraw()
{

}

void smtRenderSprite(SMT_Renderer* renderer, SMT_Sprite* sprite)
{
    
}
