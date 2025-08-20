#include "smt/window.h"

static void error_callback(int error, const char* description)
{
    printf("Error: %d : %s\n", error, description);
}

void smtWindowOpen(int width, int height, const char* title, SMT_Window* window) 
{
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
    {
        smtSetErrorMessage("SMT: failed to init glfw");
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    GLFWwindow* glfwWindow = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!glfwWindow)
    {
        glfwTerminate();
        smtSetErrorMessage("SMT: failed to create glfw window");
        return;
    }
    window->glfwWindow = glfwWindow;
}

int smtWindowShouldClose(SMT_Window* window) 
{
    if(!window || glfwWindowShouldClose(window->glfwWindow) == GLFW_TRUE) return SMT_TRUE;
    return SMT_FALSE;
}

void smtWindowCleanup(SMT_Window* window) 
{
    if(!window || !window->glfwWindow) return;
    glfwDestroyWindow(window->glfwWindow);
    memset(window, 0, sizeof(SMT_Window));
}

void smtWindowUpdate(SMT_Window* window) 
{
    glfwSwapBuffers(window->glfwWindow);
    glfwPollEvents();
}