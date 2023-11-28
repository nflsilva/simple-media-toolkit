#include "smt/smt.h"

static int smtErrorMessageSize = 0;
char *smtErrorMessage = NULL;

char* smtGetErrorMessage() 
{
    return smtErrorMessage;
}

void smtSetErrorMessage(const char* message) 
{
    int newMessageSize = strlen(message);
    if(newMessageSize >= smtErrorMessageSize) 
    {
        if(smtErrorMessageSize != 0) 
            free(smtErrorMessage);

        smtErrorMessage = (char*)malloc(sizeof(char) * newMessageSize + 1);
    }
    smtErrorMessageSize = newMessageSize;
    strcpy(smtErrorMessage, message);
    printf("smt_error: %s\n", smtErrorMessage);
}