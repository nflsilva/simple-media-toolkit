#include "smt/window.h"

static void error_callback(int error, const char* description)
{
    printf("Error: %d : %s\n", error, description);
}

SMT_Window* smtWindowOpen(int width, int height, const char* title) 
{
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
    {
        smtSetErrorMessage("SMT: failed to init glfw");
        return NULL;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    GLFWwindow* glfwWindow = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!glfwWindow)
    {
        glfwTerminate();
        smtSetErrorMessage("SMT: failed to create glfw window");
        return NULL;
    }

    SMT_Window* window = (SMT_Window*)malloc(sizeof(SMT_Window));
    window->glfwWindow = glfwWindow;

    return window;
}

int smtWindowShouldClose(SMT_Window* window) 
{
    if(!window || glfwWindowShouldClose(window->glfwWindow) == GLFW_TRUE) return SMT_TRUE;
    return SMT_FALSE;
}

void smtWindowDestroy(SMT_Window* window) 
{
    if(!window) return;
    glfwDestroyWindow(window->glfwWindow);
}

void smtWindowUpdate(SMT_Window* window) 
{
    glfwSwapBuffers(window->glfwWindow);
    glfwPollEvents();
}