#include "smt/window.h"

int smtOpenWindow(int width, int height, const char *title) {

    if (!glfwInit())
    {
        return SMT_FAILURE;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return SMT_FAILURE;
    }

    glfwMakeContextCurrent(window);
    gladLoadGL();
    glfwSwapInterval(1);
}

int smtWindowShouldClose() {
    if(!window || glfwWindowShouldClose(window) == GLFW_TRUE) return SMT_TRUE;
    return SMT_FALSE;
}

void smtCloseWindow() {
    if(!window) return;
    glfwDestroyWindow(window);
}

void smtUpdateWindow() {
    glfwSwapBuffers(window);
    glfwPollEvents();
}
