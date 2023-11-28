#ifndef _SMT_KEYBOARD_H
#define _SMT_KEYBOARD_H

#include <GLFW/glfw3.h>
#include "smt/smt.h"

#define SMT_KEY_0 48
#define SMT_KEY_1 49
#define SMT_KEY_2 50
#define SMT_KEY_3 51
#define SMT_KEY_4 52
#define SMT_KEY_5 53
#define SMT_KEY_6 54
#define SMT_KEY_7 55
#define SMT_KEY_8 56
#define SMT_KEY_9 57

#define SMT_KEY_A 65
#define SMT_KEY_B 66
#define SMT_KEY_C 67
#define SMT_KEY_D 68
#define SMT_KEY_E 69
#define SMT_KEY_F 70
#define SMT_KEY_G 71
#define SMT_KEY_H 72
#define SMT_KEY_I 73
#define SMT_KEY_J 74
#define SMT_KEY_K 75
#define SMT_KEY_L 76
#define SMT_KEY_M 77
#define SMT_KEY_N 78
#define SMT_KEY_O 79
#define SMT_KEY_P 80
#define SMT_KEY_Q 81
#define SMT_KEY_R 82
#define SMT_KEY_S 83
#define SMT_KEY_T 84
#define SMT_KEY_U 85
#define SMT_KEY_V 86
#define SMT_KEY_W 87
#define SMT_KEY_X 88
#define SMT_KEY_Y 89
#define SMT_KEY_Z 90

#define SMT_KEY_RIGHT 262
#define SMT_KEY_LEFT 263
#define SMT_KEY_DOWN 264
#define SMT_KEY_UP 265

extern GLFWwindow* smlWindow;
static int currentKeyboardStateIndex = 0;
static int keyboardStates[2][25];

/*!
 *  Starts scanning for key inputs from keyboard
 * @returns `SMT_SUCCESS` if successfull. `SMT_FAILURE` if an error occurred
 * or the window is not opened.
 */
int smtStartKeyboard();

/*!
 * Checks if a given key was pressed.
 * @param key The key to check for press.
 * @returns `SMT_TRUE` if key was pressed. `SMT_FALSE` otherwise.
 */
int smtKeyIsPressed(int key);

/*!
 * Checks if a given key was released.
 * @param key The key to check for release.
 * @returns `SMT_TRUE` if key was release. `SMT_FALSE` otherwise.
 */
int smtKeyIsReleased(int key);

/*!
 * Checks if a given key is being hold.
 * @param key The key to check for hold.
 * @returns `SMT_TRUE` if key is being hold. `SMT_FALSE` otherwise.
 */
int smtKeyIsHold(int key);

/*!
 *  Updates keyboard context.
 */
void smtUpdateKeyboard();

#endif