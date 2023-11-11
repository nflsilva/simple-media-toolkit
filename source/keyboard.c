#include "smt/keyboard.h"

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) 
{
    if(window != smlWindow) return;

    switch (action)
    {
        case GLFW_PRESS:
            keyboardStates[currentKeyboardStateIndex][key - SMT_KEY_A] = SMT_TRUE;
            break;
        case GLFW_RELEASE:
            keyboardStates[currentKeyboardStateIndex][key - SMT_KEY_A] = SMT_FALSE;
            break;
        default:
            break;
    }
}

int smtStartKeyboard() 
{
    if(!smlWindow) return SMT_FAILURE;
    glfwSetKeyCallback(smlWindow, key_callback);
    return SMT_SUCCESS;
}

int smtKeyIsPressed(int key) 
{
    return keyboardStates[currentKeyboardStateIndex][key - SMT_KEY_A];
}

int smtKeyIsReleased(int key) 
{
    int lastKeyboarStateIndex = (currentKeyboardStateIndex + 1) % 2;
    int lastKeyState = keyboardStates[lastKeyboarStateIndex][key - SMT_KEY_A];
    int currentKeyState = keyboardStates[currentKeyboardStateIndex][key];
    return lastKeyState && !currentKeyState;
}

int smtKeyIsHold(int key) 
{
    int lastKeyboarStateIndex = (currentKeyboardStateIndex + 1) % 2;
    int lastKeyState = keyboardStates[lastKeyboarStateIndex][key - SMT_KEY_A];
    int currentKeyState = keyboardStates[currentKeyboardStateIndex][key - SMT_KEY_A];
    return lastKeyState && currentKeyState;
}

void smtUpdateKeyboard() 
{
    currentKeyboardStateIndex++;
    currentKeyboardStateIndex = currentKeyboardStateIndex % 2;
    memset(keyboardStates[currentKeyboardStateIndex], SMT_FALSE, sizeof(keyboardStates[currentKeyboardStateIndex]));
}
