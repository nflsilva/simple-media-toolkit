#include "smt/render.h"

#include <glad/glad.h>

static void smtRendererSetupViewMatrix(CVECMat4F_t* matrix, float zoom, float x, float y) {
    assert(matrix);

    cvecMat4FSetIdentity(matrix);

    matrix->data[0][0] = zoom;
    matrix->data[1][1] = zoom;
    matrix->data[3][0] = -zoom * x;
    matrix->data[3][1] = -zoom * y;
}

void smtRendererInitialise(SMT_Window* window, SMT_Renderer* renderer) {
    assert(renderer);
    glfwMakeContextCurrent(window->glfwWindow);
    gladLoadGL();
    glfwSwapInterval(1);

    smtSpriteInitialiseSpiteShader(&renderer->spriteShader);
    smtSpriteInitialiseSpriteBatch(&renderer->spriteBatch);
    cutilHashTableInitialise(&renderer->filePerTexture, sizeof(SMT_Sprite_t));

    int width, height;
    glfwGetWindowSize(window->glfwWindow, &width, &height);
    cvecMat4FSetOrthographicProjection(&renderer->projectionMatrix, -1.0f, 1.0f, 0.0f, width, height, 0.0f);

    smtRendererSetupViewMatrix(&renderer->viewMatrix, 1.0f, 0.0f, 0.0f);
}

void smtRendererCleanup(SMT_Renderer* renderer) {
    assert(renderer);
    smtShaderCleanup(&renderer->spriteShader);
    smtBatchCleanup(&renderer->spriteBatch);
}

void smtRendererDraw(SMT_Renderer* renderer) {
    assert(renderer);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    smtSpriteDrawBatches(renderer);
}