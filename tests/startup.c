#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "smt/shader.h"
#include "smt/window.h"

int main()
{

    assert(smtWindowOpen(10, 10, "startupTest") == SMT_SUCCESS);

    SMT_Shader* shapeShader = smtShaderCreateShapeShader();
    if(!shapeShader)
        printf("Error creating shaderShapeShader: %s\n", smtGetErrorMessage());
    assert(shapeShader != NULL);

    smtShaderDestroy(shapeShader);
    
    smtWindowClose();

    exit(EXIT_SUCCESS);
}