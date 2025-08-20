#ifndef _SMT_WINDOW_H
#define _SMT_WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>

#include "smt/smt.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SMT_Window {
    GLFWwindow* glfwWindow;
} SMT_Window;

/*!
 *  Opens the application window with a valid OpenGL context.
 * @param width The window width to set.
 * @param height The window height to set.
 * @param title The window height to set.
 * @returns `SMT_SUCCESS` if successfull. `SMT_FAILURE` if an error occurred
 * or the window is already opened.
 */
void smtWindowOpen(int width, int height, const char* title, SMT_Window* window);

/*!
 *  Indicates if the applicatin window will close.
 * @returns `SMT_TRUE` if the window will close. `SMT_FALSE` otherwise.
 */
int smtWindowShouldClose(SMT_Window* window);

/*!
 *  Destroys window context.
 */
void smtWindowCleanup(SMT_Window* window);

/*!
 *  Updates window context.
 */
void smtWindowUpdate(SMT_Window* window);

#ifdef __cplusplus
}
#endif

#endif