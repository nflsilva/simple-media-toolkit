#ifndef _SMT_H
#define _SMT_H

#include <stdlib.h>
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

static int errorMessageSize = 0;
char *errorMessage = NULL;

/*!
 * Gets the last error message from SMT.
 * @param message The error message to set.
 */
char* smtGetErrorMessage() 
{
    return errorMessage;
}

/*!
 * Sets the last error message for SMT.
 * @param message The error message to set.
 */
void smtSetErrorMessage(const char* message) 
{
    int newMessageSize = strlen(message);
    if(newMessageSize > errorMessageSize) {
        if(errorMessageSize != 0) {
            free(errorMessage);
        }
        errorMessage = (char*) malloc(sizeof(char) * newMessageSize + 1);
    }
    errorMessageSize = newMessageSize;
    strcpy(errorMessage, message);
}

#endif