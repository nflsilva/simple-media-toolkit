#ifndef _SMT_H
#define _SMT_H

#include <stdlib.h>

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

char *errorMessage = NULL;

/*!
 * Gets the last error message from SMT.
 * @param message The error message to set.
 */
char* smtGetErrorMessage(const char *message) {
    return errorMessage;
}

/*!
 * Sets the last error message for SMT.
 * @param message The error message to set.
 */
void smtSetErrorMessage(const char *message) {
    errorMessage = message;
}

#endif