#include "smt/window.h"

int smtOpenWindow(int width, int height, const char* title) 
{

    if (!glfwInit())
    {
        return SMT_FAILURE;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    smlWindow = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!smlWindow)
    {
        glfwTerminate();
        return SMT_FAILURE;
    }

    glfwMakeContextCurrent(smlWindow);
    gladLoadGL();
    glfwSwapInterval(1);

    return SMT_SUCCESS;
}

int smtWindowShouldClose() 
{
    if(!smlWindow || glfwWindowShouldClose(smlWindow) == GLFW_TRUE) return SMT_TRUE;
    return SMT_FALSE;
}

void smtCloseWindow() 
{
    if(!smlWindow) return;
    glfwDestroyWindow(smlWindow);
}

void smtUpdateWindow() 
{
    glfwSwapBuffers(smlWindow);
    glfwPollEvents();
}