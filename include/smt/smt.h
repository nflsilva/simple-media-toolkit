#ifndef _SMT_H
#define _SMT_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
 *  Semantic sugar for the number `1`.
 */
#define SMT_TRUE 1
/*
 *  Semantic sugar for the number `0`.
 */
#define SMT_FALSE 0
/*
 *  Semantic sugar for the number `1`.
 */
#define SMT_SUCCESS 1
/*
 *  Semantic sugar for the number `0`.
 */
#define SMT_FAILURE 0

/*!
 * Gets the last error message from SMT.
 * @param message The error message to set.
 */
char* smtGetErrorMessage();

/*!
 * Sets the last error message for SMT.
 * @param message The error message to set.
 */
void smtSetErrorMessage(const char* message);

/*!
 * Inits SMT.
 * @param width The window width to set.
 * @param height The window height to set.
 * @param title The window height to set.
 * @returns `SMT_SUCCESS` if successfull. `SMT_FAILURE` if an error occurred
 */
int smtInit(int width, int height, const char* title);

#endif