#include "smt/window.h"

static GLFWwindow* smlWindow = NULL;

static void error_callback(int error, const char* description)
{
    printf("Error: %s\n", description);
}

int smtWindowOpen(int width, int height, const char* title) 
{
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
    {
        smtSetErrorMessage("");
        return SMT_FAILURE;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    smlWindow = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!smlWindow)
    {
        glfwTerminate();
        smtSetErrorMessage("");
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

void smtWindowClose() 
{
    if(!smlWindow) return;
    glfwDestroyWindow(smlWindow);
}

void smtWindowUpdate() 
{
    glfwSwapBuffers(smlWindow);
    glfwPollEvents();
}